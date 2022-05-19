#include "ScreensProject.h"

std::shared_ptr<Program::ScreensProject> Program::InitScreensProject(const std::string &name)
{
    std::string smprojFile;

    int32_t len = 9;
    if (tiles_mode == 0)
    {
        smprojFile = "classic_" + name;
    }
    else
    {
        smprojFile = "next_" + name;
        len = 64;
    }
    std::shared_ptr<ScreensProject> obj = std::make_shared<ScreensProject>();

    smprojFile = "./res/screens/" + smprojFile + ".smproj";

    BinaryStreamReader proj(smprojFile.c_str());

    //загружаем тайлы
    if (tiles_mode != 0)
    {
        proj.ReadInt32();
    }

    int32_t tiles_count = proj.ReadInt32();
    obj->Tileset.clear();
    for (int32_t i = 0; i < tiles_count; i++)
    {
        std::vector<uint8_t> data(len);
        for (int32_t j = 0; j < len; j++)
        {
            data[j] = proj.ReadByte();
        }
        AddTile(obj, data);
    }

    //загружаем спрайты
    int32_t spr_count = proj.ReadInt32();
    obj->Sprites.clear();
    for (int32_t i = 0; i < spr_count; i++)
    {
        std::shared_ptr<Sprite> spr = std::make_shared<Sprite>();
        spr->name   = proj.ReadString();
        spr->width  = proj.ReadInt32();
        spr->height = proj.ReadInt32();

        spr->tiles = AllocateDynamicArray<std::shared_ptr<Tile>>(spr->height, spr->width);
        for (int32_t y = 0; y < spr->height; y++)
        {
            for (int32_t x = 0; x < spr->width; x++)
            {
                int32_t tileIdx = proj.ReadInt32();
                std::shared_ptr<Tile> &tile = obj->Tileset[tileIdx];
                spr->tiles[x][y] = tile;
            }
        }
        obj->Sprites.push_back(spr);
    }

    //загружаем скрины
    int32_t scr_count = proj.ReadInt32();
    obj->Screens.clear();
    for (int32_t i = 0; i < scr_count; i++)
    {
        std::shared_ptr<Screen> scr = std::make_shared<Screen>();
        scr->name    = proj.ReadString();
        scr->visible = proj.ReadBoolean();
        int32_t scrspr_count = proj.ReadInt32();
        for (int32_t j = 0; j < scrspr_count; j++)
        {
            std::shared_ptr<ScreenSprite> scrspr = std::make_shared<ScreenSprite>();
            scrspr->sprite = FindSprite(obj, proj.ReadString());
            scrspr->x_cord = proj.ReadInt32();
            scrspr->y_cord = proj.ReadInt32();
            scr->sprites.push_back(scrspr);
        }
        obj->Screens.push_back(scr);
    }

    return obj;
}

std::shared_ptr<Program::Tile> Program::AddTile(const std::shared_ptr<Program::ScreensProject> &obj, std::vector<uint8_t> &data)
{
    int32_t len = 9;
    if (tiles_mode != 0)
    {
        len = 64;
    }

    for (const auto &te : obj->Tileset)
    {
        bool e = true;
        for (int32_t j = 0; j < len; j++)
        {
            if (data[j] != te->data[j])
            {
                e = false;
                break;
            }
        }
        if (e)
        {
            return te;
        }
    }

    std::shared_ptr<Tile> t = std::make_shared<Tile>();
    t->data = std::vector<uint8_t>(len);
    for (int32_t j = 0; j < len; j++)
    {
        t->data[j] = data[j];
    }


    t->img = std::make_shared<Surface>(8, 8);
    for (int32_t y = 0; y < 8; y++)
    {
        for (int32_t x = 0; x < 8; x++)
        {
            if (tiles_mode == 0)
            {
                t->img->Draw(Point(x, y), GetAttrColor(data[0], ((data[y + 1] << x) & 128) != 0));
            }
            else
            {
                t->img->Draw(Point(x, y), next_palette[data[x + y * 8]]);
            }
        }
    }

    obj->Tileset.push_back(t);
    return t;
}

SdlDotNetCompat::Drawing::Color Program::GetAttrColor(uint8_t attr, bool enable)
{
    if (!bw_color_mode || game_mode != race_mode)
    {
        if (tiles_mode == 0)
        {
            if (enable)
            {
                return attr_palette[1][(attr & 0x07) + ((attr >> 3) & 0x08)];
            }
            else
            {
                return attr_palette[0][(attr >> 3) & 0x0f];
            }
        }
        else
        {
            if (enable)
            {
                return attr_palette[1][(attr & 0x07) + ((attr >> 3) & 0x08)];
            }
            else
            {
                return attr_palette[0][(attr >> 3) & 0x0f];
            }
        }
    }
    else
    {
        if (!enable)
        {
            return Color::Black;
        }
        else
        {
            return Color::White;
        }
    }
}

std::shared_ptr<Program::Sprite> Program::FindSprite(const std::shared_ptr<Program::ScreensProject> &proj, const std::string &name)
{
    for (const auto &s : proj->Sprites)
    {
        if (s->name == name)
        {
            return s;
        }
    }
    return nullptr;
}

std::shared_ptr<Program::Screen> Program::FindScreen(const std::shared_ptr<Program::ScreensProject> &proj, const std::string &name)
{
    for (const auto &s : proj->Screens)
    {
        if (s->name == name)
        {
            return s;
        }
    }
    return nullptr;
}

void Program::DrawScreen(const std::shared_ptr<ScreensProject> &proj, int32_t num)
{
    std::shared_ptr<Screen> scr = proj->Screens[num];
    for (const auto &scr_spr : scr->sprites)
    {
        int32_t x_cord = scr_spr->x_cord;
        int32_t y_cord = scr_spr->y_cord;
        for (int32_t y = 0; y < scr_spr->sprite->height; y++)
        {
            for (int32_t x = 0; x < scr_spr->sprite->width; x++)
            {
                screen->Blit(*(scr_spr->sprite->tiles[x][y]->img), Point((x_cord + x) * 8, (y_cord + y) * 8));
                //if (tiles_mode == 0)
                {
                    Color ink = GetAttrColor(scr_spr->sprite->tiles[x][y]->data[0], true);
                    Color paper = GetAttrColor(scr_spr->sprite->tiles[x][y]->data[0], false);
                    for (int32_t j = 0; j < 8; j++)
                    {
                        for (int32_t i = 0; i < 8; i++)
                        {
                            attr_layer[0][(x_cord + x) * 8 + i][(y_cord + y) * 8 + j] = ink;
                            attr_layer[1][(x_cord + x) * 8 + i][(y_cord + y) * 8 + j] = paper;
                        }
                    }
                }
            }
        }
    }
}

void Program::DrawScreenSprite(const std::shared_ptr<ScreensProject> &proj, const std::string &name, int32_t xcord, int32_t ycord, int32_t xwin, int32_t ywin, int32_t width, int32_t height)
{
    std::shared_ptr<Sprite> spr = FindSprite(proj, name);
    for (int32_t y = 0; y < height; y++)
    {
        for (int32_t x = 0; x < width; x++)
        {
            screen->Blit(*(spr->tiles[x + xwin][y + ywin]->img), Point((xcord + x) * 8, (ycord + y) * 8));
            {
                Color ink   = GetAttrColor(spr->tiles[x][y]->data[0], true);
                Color paper = GetAttrColor(spr->tiles[x][y]->data[0], false);
                for (int32_t j = 0; j < 8; j++)
                {
                    for (int32_t i = 0; i < 8; i++)
                    {
                        attr_layer[0][(xcord + x) * 8 + i][(ycord + y) * 8 + j] = ink;
                        attr_layer[1][(xcord + x) * 8 + i][(ycord + y) * 8 + j] = paper;
                    }
                }
            }

        }
    }
}
