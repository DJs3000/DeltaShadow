#include "Text.h"

void Program::InitFonts()
{
    std::string langStr = language;
    toLower(langStr);

    std::string path = "./res/fonts/font_" + langStr + ".ch8";

    std::vector<uint8_t> f;
    File::ReadAllBytes(path, f);

    next_mini_powerups = std::make_shared<Surface>("./res/fonts/platformer_mode_font.png");

    int32_t n = 0;
    for (int32_t j = 0; j < 256; j++)
    {
        for (int32_t i = 0; i < 8; i++)
        {
            int32_t a = f[n++];

            for (int32_t s = 0; s < 8; s++)
            {
                font32[j][s][i] = (((a << s) & 128) == 0) ? false : true;
            }
        }
    }
}

void Program::DrawSymbol32(int32_t x, int32_t y, uint8_t symbol, uint8_t attr)
{
    Color paper = GetAttrColor(attr, false);
    Color ink = GetAttrColor(attr, true);
    if (attr == 0)
    {
        paper = attr_layer[0][x * 8][y * 8];
        ink = attr_layer[1][x * 8][y * 8];
    }
    Color pix;
    for (int32_t j = 0; j < 8; j++)
    {
        for (int32_t i = 0; i < 8; i++)
        {
            pix = font32[symbol][i][j] ^ invert_print ? ink : paper;
            screen->Draw(Point(x * 8 + i, y * 8 + j), pix);
        }
    }
}

void Program::PrintString32(int32_t x, int32_t y, const std::string &text)
{
    for (size_t i = 0; i < text.length(); i++)
    {
        DrawSymbol32(x + i, y, static_cast<uint8_t>(text[i]), 0);
    }
}

void Program::LoadTexts()
{
    InitFonts();

    std::string path = "./res/texts/" + language + ".bin";

    File::ReadAllBytes(path, texts);
}

int32_t Program::FindText(int32_t num)
{
    int32_t i = 0;
    int32_t pos = 0;
    while (num != i)
    {
        if (static_cast<uint8_t>(texts[pos]) == 255)
        {
            i++;
        }
        pos++;
    }
    return pos;
}

int32_t Program::NextString(int32_t pos)
{
    while (static_cast<uint8_t>(texts[pos]) != 255)
    {
        pos++;
        if (texts[pos] == '\0')
        {
            break;
        }
    }
    pos++;
    return pos;
}

int32_t Program::PrintString(int32_t pos, int32_t x, int32_t y)
{
    while (static_cast<uint8_t>(texts[pos]) != 255)
    {
        DrawSymbol32(x, y, texts[pos], 0);
        x++;
        pos++;
        if (texts[pos] == '\0')
        {
            break;
        }
    }
    pos++;
    return pos;
}

void Program::InitText(int32_t text_num, int32_t x, int32_t y, int32_t width, int32_t height, uint8_t attr)
{
    text_pos = FindText(text_num);
    text_x = x;
    text_y = y;
    x_win = x;
    y_win = y;
    width_win = width;
    height_win = height;
    if (attr != 0)
    {
        FillAttrRect(x, y, width, height, attr);
    }
}

bool Program::PrintSymbol()
{
    uint8_t sym = texts[text_pos];
    if (sym == 255)
    {
        return false;
    }

    if (sym != 0)
    {
        DrawSymbol32(text_x, text_y, sym, 0);
        if (type_with_sound)
        {
            InitSFX(sfx_type);
        }
    }
    text_pos++;
    sym = texts[text_pos];
    text_x++;
    if (text_x == 33 || sym == 0)
    {
        text_x = x_win - 1;
        text_y++;
        if (text_y == y_win + height_win)
        {
            text_y--;
            ScrollWindow(x_win, y_win, width_win, height_win);
        }
    }
    return true;
}

void Program::PrintText(int32_t num, int32_t x, int32_t y, int32_t width, int32_t height, uint8_t attr)
{
    InitText(num, x, y, width, height, attr);
    while (PrintSymbol())
    {

    }
}

void Program::ScrollWindow(int32_t x, int32_t y, int32_t width, int32_t height)
{
    x = x * 8;
    y = y * 8;
    width = width * 8;
    height = height * 8;

    screen->CopyPixels( Point(x, y), SdlDotNetCompat::Drawing::Rectangle(x, y + 8, width, height - 8) );
    ///screen->SetPixels(Point(x, y), screen->GetColors(System::Drawing::Rectangle(x, y + 8, width, height - 8)));
    screen->Fill(SdlDotNetCompat::Drawing::Rectangle(x, y + height - 8, width, 8), Color::Black);
}

void Program::DrawSymbolLine(int32_t x, int32_t y, uint8_t symbol, int32_t line)
{
    Color paper = Color::Black; // attr_layer[0, x * 8, y];
    Color ink = Color::White; // attr_layer[1, x * 8, y];
    Color pix;
    for (int32_t i = 0; i < 8; i++)
    {
        pix = font32[symbol][i][line] ? ink : paper;
        screen->Draw(Point(x * 8 + i, y), pix);
    }
}

int32_t Program::PrintStringLine()
{
    int32_t p = text_pos;
    int32_t x = titles_x;
    while (texts[p] != 0 && texts[p] != 0xFF)
    {
        DrawSymbolLine(x, 183, texts[p], text_counter);

        x++;
        p++;
    }
    if (texts[p] != 0xFF)
    {
        p++;
    }
    return p;
}

void Program::ScrollCredits()
{
    int32_t x = titles_x * 8;
    int32_t y = titles_y * 8;
    int32_t width = titles_width * 8;
    int32_t height = titles_height * 8;

    screen->CopyPixels( Point(x, y), SdlDotNetCompat::Drawing::Rectangle(x, y + 1, width, height - 1) );
    ///screen->SetPixels(Point(x, y), screen->GetColors(System::Drawing::Rectangle(x, y + 1, width, height - 1)));
    screen->Fill(SdlDotNetCompat::Drawing::Rectangle(x, y + height - 1, width, 1), Color::Black);
}