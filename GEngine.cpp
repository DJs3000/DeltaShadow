void Program::InitGEngine()
{
    screen = std::make_shared<SdlDotNetCompat::Graphics::Surface>(256, 192);
    screen_copy = std::make_shared<SdlDotNetCompat::Graphics::Surface>(256, 160);
    scroll_screen = std::make_shared<SdlDotNetCompat::Graphics::Surface>(256, 160);

    InitFonts();

    ClearScreen();

    //загрузка некстовской палитры
    BinaryStreamReader f("./res/palettes/NextPalette.bin");

    for (int32_t i = 0; i < 256; i++)
    {
        next_palette[i] = Color::FromArgb(f.ReadInt32());
    }
}

SdlDotNetCompat::Drawing::Color Program::GetColor(int32_t zxcolor)
{
    int32_t bright = (zxcolor & 8) == 0 ? 192 : 255;
    int32_t r = (zxcolor & 2) == 0 ? 0 : bright;
    int32_t g = (zxcolor & 4) == 0 ? 0 : bright;
    int32_t b = (zxcolor & 1) == 0 ? 0 : bright;
    return SdlDotNetCompat::Drawing::Color::FromArgb(r, g, b);
}

void Program::ClearScreen()
{
    screen->Fill(Color::Black);
    for (int32_t y = 0; y < 192; y++)
    {
        for (int32_t x = 0; x < 256; x++)
        {
            attr_layer[0][x][y] = attr_palette[0][0];
            attr_layer[1][x][y] = attr_palette[1][15];
        }
    }
}

void Program::FillAttrRect(int32_t x, int32_t y, int32_t width, int32_t height, uint8_t attr)
{
    for (int32_t j = 0; j < height * 8; j++)
    {
        for (int32_t i = 0; i < width * 8; i++)
        {
            attr_layer[0][x * 8 + i][y * 8 + j] = GetAttrColor(attr, false);
            attr_layer[1][x * 8 + i][y * 8 + j] = GetAttrColor(attr, true);
        }
    }
    screen->Fill(SdlDotNetCompat::Drawing::Rectangle(x * 8, y * 8, width * 8, height * 8), GetAttrColor(attr, false));
}

void Program::InitRoomTiles()
{
    int32_t cx = current_xy_room & 0x0f;
    int32_t cy = (current_xy_room & 0xf0) / 16;

    x_home_tile = cx * 14;
    y_home_tile = cy * 8;
    x_home = x_home_tile * 16;
    y_home = y_home_tile * 16;

    RoomAnimTiles.clear();
    for (int32_t j = 0; j < 10; j++)
    {
        for (int32_t i = 0; i < 16; i++)
        {
            Room[i][j] = Loc[x_home_tile + i][y_home_tile + j];
            int32_t p = TilesetProperty[Room[i][j]];
            int32_t pp = (p >> 5) & 7;
            if ((p & 0x0c) != 0 && (graphics_quality != 0 || p == 104 || p == 105 || (pp != 0 && pp != isPlatform && pp != isRails && pp != isFloor && pp != isWater)))
            {
                std::shared_ptr<AnimTile> a = std::make_shared<AnimTile>();
                a->num = Room[i][j];
                a->property = TilesetProperty[Room[i][j]];
                a->x = i;
                a->y = j;
                RoomAnimTiles.push_back(a);
            }
        }
    }
    FullRoomRedraw();
}

void Program::InitRoom(bool new_hero_cord)
{
    game_cicle_counter = 0;
    cntr_enter_in_room = 2;
    if (room_cntr != 0)
    {
        room_cntr--;
    }
    InitRoomTiles();

    //устанавливаем новые координаты объекту героя
    if (new_hero_cord)
    {
        for (auto &obj : game_objects)
        {
            if ((obj->Name == idNova || obj->Name == idDoor || obj->Name == idJLift || obj->Name == idJDoor || obj->Name == idJacqueline) && obj->NoActivated && obj->XYRoom == current_xy_room)
            {
                //if ((obj.Name == idNova || obj.Name == idDoor || obj.Name == idJLift || obj.Name == idJDoor) && obj.NoActivated && obj.XYRoom == current_xy_room)
                hero_object->X = obj->X;
                hero_object->Y = obj->Y;
                hero_object->Direction = obj->Direction;
                hero_object->YAccel = 0;
                hero_object->NoInterruptAnim = false;

                //стартовый лифт локации Жаклин
                if (obj->Name == idJLift && obj->Counter == 0)
                {
                    hero_object->NoVisible = true;
                    StealthSpawn(obj);
                    AddActualObject(obj);
                    lift_pause = 150;
                }

                if (obj->Name == idDoor && obj->Status == 0)
                {
                    disable_control = true;
                    obj->Counter = 100;
                    hero_object->Direction = hero_start_direction;
                }

                //if (obj.Name == idNova)
                if (obj->Name == idNova || obj->Name == idJacqueline)
                {
                    RemoveObject(obj);
                }
                break;
            }
        }
    }

    //проверяем комнату на безопасность респавна для героя
    if (!hero_object->NoInterruptAnim && !in_boss_room)
    {
        int32_t x = 0;
        if (slide_cntr != 0)
        {
            while (GetProperty(hero_object, x - 8, -32) == isFloor)
            {
                x += 16;
            }
            if (hero_object->Direction)
            {
                x = -x;
            }
        }

        int32_t yoffset = 1;
        while (hero_object->Y + yoffset - (current_xy_room & 0xf0) * 8 < 160)
        {
            int32_t t1 = GetProperty(hero_object, 8, yoffset);
            int32_t t2 = GetProperty(hero_object, -8, yoffset);

            if (t1 == isShift || t2 == isShift || t1 == isSpike || t2 == isSpike)
            {
                break;
            }

            if (t1 == isPlatform || t1 == isFloor || t2 == isPlatform || t2 == isFloor)
            {
                if (GetProperty(hero_object, 0, yoffset - 40) == isFloor)
                {
                    break;
                }

                last_safe_xy_room = current_xy_room;
                last_safe_x = hero_object->X + x;
                last_safe_y = (hero_object->Y + yoffset - 1) & 0xfff0;
                last_safe_direction = hero_object->Direction;
                break;
            }
            yoffset += 16;
        }
    }

    //обновление статусов объектов

    //удаление неактуальных объектов из списка
    for (size_t i = 0; i < actual_objects.size(); i++)
    {
        if (actual_objects[i]->Name != 0)
        {
            if ((actual_objects[i]->Name != idPlatform && (GetXDistance(actual_objects[i]) == 255 || GetYDistance(actual_objects[i]) == 159)) || (actual_objects[i]->Fixed && actual_objects[i]->Name != idExplosion && actual_objects[i]->Name != idDust && actual_objects[i]->Name != idRocketSmoke) || actual_objects[i]->NoActivated || (graphics_quality == 0 && isEnemy(actual_objects[i]) && !InCurrentRoom(actual_objects[i])))
            {
                actual_objects[i]->NoActivated = true;
                RemoveActualObject(actual_objects[i]);
                i--;
            }
        }
    }

    //добавление актуальных объектов в список
    for (auto &obj : game_objects)
    {
        if (obj->XYRoom == current_xy_room && obj->NoActivated && obj->Name != 0 && obj->Name != idNova)
        {
            if (((obj->Name != idJPolice1 && obj->Name != idJPolice2 && obj->Name != idJPolice3) || lift_moves == 0) && ((obj->Left && obj->Down && obj->Up && obj->Right) || (!obj->Left && !obj->Down && !obj->Up && !obj->Right) || (obj->Left && scroll_direction == 2) || (obj->Right && scroll_direction == 4) || (obj->Up && scroll_direction == 3) || (obj->Down && scroll_direction == 1)))
            {
                AddActualObject(obj);
                obj->AnimationPlayed = false;
            }
        }
    }
}

void Program::NewTile(int32_t x, int32_t y, int32_t num)
{
    Loc[x][y] = num;
    int32_t i = x - x_home_tile;
    int32_t j = y - y_home_tile;
    if (i < 0 || i >= 16 || j < 0 || j >= 10)
    {
        return;
    }
    Room[i][j] = num;
    screen_refresh_tab[i][j] = true;
}

void Program::FullRoomRedraw()
{
    for (int32_t j = 0; j < 10; j++)
    {
        for (int32_t i = 0; i < 16; i++)
        {
            screen_refresh_tab[i][j] = true;
        }
    }
}

void Program::DrawRoom()
{
    //анимируем тайлы
    for (const auto &a : RoomAnimTiles)
    {
        int32_t mask;
        int32_t tile = a->num;
        //обычная анимация
        if ((a->property & 0x10) == 0 || (a->property & 0xf0) == 0xf0)
        {
            mask = 7;
            if ((a->property & 12) == 4)
            {
                mask = 1;
            }
            if ((a->property & 12) == 8)
            {
                mask = 3;
            }
            tile += TimerTiles[a->property & 3] & mask;
        }
        //случайная анимация
        else
        {
            mask = 8;
            if ((a->property & 12) == 4)
            {
                mask = 2;
            }
            if ((a->property & 12) == 8)
            {
                mask = 4;
            }
            if (RndTimerTiles[a->property & 3] < mask)
            {
                tile += RndTimerTiles[a->property & 3];
            }
        }
        Room[a->x][a->y] = tile;
        screen_refresh_tab[a->x][a->y] = true;
    }

    //прорисовываем тайлы
    for (int32_t j = 0; j < 10; j++)
    {
        for (int32_t i = 0; i < 16; i++)
        {
            if (screen_refresh_tab[i][j])
            {
                const auto room = Room[i][j];
                screen->Blit(*(Tileset[tiles_mode][room]), Point(i * 16, j * 16));
                if (tiles_mode == 0)
                {
                    for (int32_t ya = 0; ya < 16; ya++)
                    {
                        for (int32_t xa = 0; xa < 16; xa++)
                        {
                            attr_layer[0][i * 16 + xa][j * 16 + ya] = TilesetAttr[0][room][xa][ya];
                            attr_layer[1][i * 16 + xa][j * 16 + ya] = TilesetAttr[1][room][xa][ya];
                        }
                    }
                }
                screen_refresh_tab[i][j] = false;
            }
        }
    }
}

void Program::DrawTileObject(const std::shared_ptr<GameObject> &obj)
{
    int32_t i = ((obj->X - x_home) - 8) / 8;
    int32_t j = ((obj->Y - y_home) - 16) / 8;
    if (tiles_mode == zx_classic_mode)
    {
        screen->Blit(*Tileset[tiles_mode][obj->XAccel], Point(i * 8, j * 8));
        for (int32_t ya = 0; ya < 16; ya++)
        {
            for (int32_t xa = 0; xa < 16; xa++)
            {
                attr_layer[0][i * 8 + xa][j * 8 + ya] = TilesetAttr[0][obj->XAccel][xa][ya];
                attr_layer[1][i * 8 + xa][j * 8 + ya] = TilesetAttr[1][obj->XAccel][xa][ya];
            }
        }
    }
    else
    {
        screen->Blit(*Tileset[tiles_mode][obj->XAccel], Point(i * 8, j * 8));
    }
    screen_refresh_tab[i / 2][j / 2] = true;
    screen_refresh_tab[(i + 1) / 2][j / 2] = true;
    screen_refresh_tab[i / 2][(j + 1) / 2] = true;
    screen_refresh_tab[(i + 1) / 2][(j + 1) / 2] = true;
}

void Program::DrawSymbolObject(const std::shared_ptr<GameObject> &obj)
{
    int32_t i, j;
    if (tiles_mode == zx_classic_mode)
    {
        i = ((obj->X - x_home) - 4) / 8;
        j = ((obj->Y - y_home) - 8) / 8;
        if (i < 0 || i >= 31 || j < 0 || j >= 19)
        {
            return;
        }
        DrawSymbol32(i, j, static_cast<uint8_t>(obj->XAccel), obj->Status);
    }
    else
    {
        i = (obj->X - x_home) - 4;
        j = (obj->Y - y_home) - 8;
        if (i < 0 || i >= 248 || j < 0 || j >= 152)
        {
            return;
        }
        screen->Blit(*next_mini_powerups, Point(i, j), SdlDotNetCompat::Drawing::Rectangle(obj->XAccel * 8, 0, 8, 8));
        i = i / 8;
        j = j / 8;
    }
    screen_refresh_tab[i / 2][j / 2] = true;
    screen_refresh_tab[(i + 1) / 2][j / 2] = true;
    screen_refresh_tab[i / 2][(j + 1) / 2] = true;
    screen_refresh_tab[(i + 1) / 2][(j + 1) / 2] = true;
}

void Program::DrawGameObject(const std::shared_ptr<GameObject> &obj)
{
    const auto &composition = obj->Animations[sprite_mode]->Animations[obj->CurrentAnimation]->Frames[obj->Frame]->Composition;
    for (const auto &e : composition)
    {
        int32_t xpos = obj->X;
        int32_t ypos = obj->Y + e->YOffset;

        if (game_mode != stealth_mode && obj->Fixed)
        {
            xpos &= 0xfff8;
        }

        int32_t xoffset = e->XOffset;
        if (obj->Direction)
        {
            xoffset = -e->ElemSprite->Width - e->XOffset;
        }
        xpos += xoffset;

        xpos -= x_home;
        ypos -= y_home;

        int32_t x;
        int32_t y;
        int32_t width = e->ElemSprite->Width;
        int32_t height = e->ElemSprite->Height;

        if (!(width == 1 && height == 1))
        {
            //помечаем экран на перерисовку
            for (int32_t j = 0; j < (height + 15 + (ypos & 15)) / 16; j++)
            {
                for (int32_t i = 0; i < (width + 15 + (xpos & 15)) / 16; i++)
                {
                    x = xpos / 16 + i;
                    y = ypos / 16 + j;
                    if (x >= 0 && x < 16 && y >= 0 && y < 10)
                    {
                        screen_refresh_tab[x][y] = true;
                    }
                }
            }

            //рисуем спрайт
            for (int32_t j = 0; j < height; j++)
            {
                for (int32_t i = 0; i < width; i++)
                {
                    if (obj->Direction)
                    {
                        x = xpos + width - i - 1;
                    }
                    else
                    {
                        x = xpos + i;
                    }

                    y = ypos + j;
                    if (x >= 0 && x < 256 && y >= 0 && y < sprite_bottom)
                    {
                        //монохромный спрайт с маской
                        if (e->ElemSprite->Type == 0)
                        {
                            if (tiles_mode == 0)
                            {
                                if (e->ElemSprite->ClassicLayer[i][j] == 1)
                                {
                                    screen->Draw(Point(x, y), attr_layer[0][x][y]);
                                }
                                else if (e->ElemSprite->ClassicLayer[i][j] == 2)
                                {
                                    screen->Draw(Point(x, y), attr_layer[1][x][y]);
                                }
                            }
                            else
                            {
                                if (e->ElemSprite->ClassicLayer[i][j] == 1)
                                {
                                    screen->Draw(Point(x, y), Color::Black);
                                }
                                else if (e->ElemSprite->ClassicLayer[i][j] == 2)
                                {
                                    screen->Draw(Point(x, y), Color::White);
                                }
                            }
                        }
                        //спрайт в палитре Next
                        if (e->ElemSprite->Type == 1)
                        {
                            if (e->ElemSprite->NextLayer[i][j].A() == 255)
                            {
                                screen->Draw(Point(x, y), e->ElemSprite->NextLayer[i][j]);
                            }
                        }
                    }
                }
            }
        }
    }
}

void Program::DrawGameObjects()
{
    for (int32_t l = 0; l < 3; l++)
    {
        for (const auto &obj : actual_objects)
        {
            if (obj->Name == 0)
            {
                break;
            }

            if (obj->Type == 0)
            {
                if (!obj->NoActivated && !obj->NoVisible && obj->Priority == l && (obj->UndeadCounter == 0 || (obj->UndeadCounter != 0 && (interrupt_counter & 4) == 0)))
                {
                    DrawGameObject(obj);
                }
            }
            else if (l == 2)
            {
                if ((obj->Type & 0x80) == 0)
                {
                    DrawTileObject(obj);
                }
                else
                {
                    DrawSymbolObject(obj);
                }
            }
        }
    }
}

void Program::ScrollRoom()
{
    if (!scroll_on)
    {
        FullRoomRedraw();
        scroll_cntr = 0;
        return;
    }

    //if ((interrupt_counter & 1) == 0)
    //    return;

    screen->SetClipRectangle(SdlDotNetCompat::Drawing::Rectangle(0, 0, 256, 160));

    switch (scroll_direction)
    {
    case 1:
        screen->Blit(*scroll_screen, Point(0, (1 - scroll_cntr) * 16));
        screen->Blit(*screen_copy, Point(0, (9 - scroll_cntr) * 16));
        break;

    case 2:
        screen->Blit(*scroll_screen, Point((scroll_cntr - 1) * 16, 0));
        screen->Blit(*screen_copy, Point((scroll_cntr - 15) * 16, 0));
        break;

    case 3:
        screen->Blit(*scroll_screen, Point(0, (scroll_cntr - 1) * 16));
        screen->Blit(*screen_copy, Point(0, (scroll_cntr - 9) * 16));
        break;

    case 4:
        screen->Blit(*scroll_screen, Point((1 - scroll_cntr) * 16, 0));
        screen->Blit(*screen_copy, Point((15 - scroll_cntr) * 16, 0));
        break;
    }

    screen->SetClipRectangle(SdlDotNetCompat::Drawing::Rectangle(0, 0, 256, 192));

    scroll_cntr--;
    if (scroll_cntr == 0)
    {
        FullRoomRedraw();
    }
}

void Program::SetScale(int32_t x, int32_t y, int32_t value)
{
    for (int32_t j = 0; j < 77; j++)
    {
        if (value < j)
        {
            ResScaleCol(x + j, y);
        }
        else
        {
            SetScaleCol(x + j, y);
        }
    }
}

void Program::SetScaleCol(int32_t x, int32_t y)
{
    for (int32_t i = 0; i < 5; i++)
    {
        if (tiles_mode == 0)
        {
            if (i != 3)
            {
                screen->Draw(Point(x, y + i), attr_layer[0][x][y + i]);
            }
        }
        else
        {
            int32_t c = 17;
            if (i == 3)
            {
                c = 20;
            }
            screen->Draw(Point(x, y + i), next_palette[c]);
        }
    }
}

void Program::ResScaleCol(int32_t x, int32_t y)
{
    for (int32_t i = 0; i < 5; i++)
    {
        if (tiles_mode == 0)
        {
            if (i != 3)
            {
                screen->Draw(Point(x, y + i), attr_layer[1][x][y + i]);
            }
        }
        else
        {
            screen->Draw(Point(x, y + i), next_palette[130]);
        }
    }
}

void Program::LoadLocationProject(int32_t num)
{
    scroll_direction = 0;
    std::string name = levels_names[num];

    std::string locFile = std::string("./res/locations/") + name + ".loc";

    BinaryStreamReader f(locFile.c_str());

    //загрузка локации
    int32_t v = f.ReadByte();
    if (v != 0)
    {        
        Quit(this, new QuitEventArgs());
    }
    f.ReadByte();
    LocWidth  = f.ReadByte() + 1;
    LocHeight = f.ReadByte() + 1;

    Loc = AllocateDynamicArray<int32_t>(LocHeight, LocWidth);
    for (int32_t y = 0; y < LocHeight; y++)
    {
        for (int32_t x = 0; x < LocWidth; x++)
        {
            Loc[x][y] = f.ReadByte();
        }
    }

    //загрузка тайлсетов
    for (int32_t k = 0; k < 2; k++)
    {
        for (int32_t i = 0; i < 256; i++)
        {
            for (int32_t j = 0; j < 37; j++)
            {
                current_tilesets[k][i][j] = f.ReadByte();
            }
        }
    }

    //загрузка палитры Next
    for (int32_t i = 0; i < 2; i++)
    {
        for (int32_t j = 0; j < 16; j++)
        {
            f.ReadInt32();
        }
    }

    //загрузка координат стартовой комнаты локации
    int32_t cx = f.ReadInt32();
    int32_t cy = f.ReadInt32();
    current_xy_room = static_cast<uint8_t>(cx + cy * 16);

    //загрузка объектов локации
    ClearAllObjects();
    std::shared_ptr<GameObject> temp = CreateObject(idNova, 0, 0, false, false);
    int32_t room_x = (LocWidth - 16) / 14 + 1;
    int32_t room_y = (LocHeight - 10) / 8 + 1;
    for (int32_t y = 0; y < (LocHeight - 10) / 8 + 1; y++)
    {
        for (int32_t x = 0; x < (LocWidth - 16) / 14 + 1; x++)
        {
            int32_t xh = x * 14;
            int32_t yh = y * 8;
            int32_t obj_num = f.ReadByte();
            for (int32_t i = 0; i < obj_num; i++)
            {
                std::shared_ptr<GameObject> obj = CreateObject(objects_names[f.ReadString()], 0, 0, false, false);
                int32_t x1 = f.ReadByte();
                int32_t y1 = f.ReadByte();
                int32_t x2 = f.ReadByte();
                int32_t y2 = f.ReadByte();
                if (x1 == 0 && x2 == 0 && y1 == 0 && y2 == 0)
                {
                    obj->X1Trigger = -1;
                }
                else
                {
                    obj->X1Trigger = (x1 + xh) * 16;
                    obj->Y1Trigger = (y1 + yh) * 16;
                    obj->X2Trigger = (x2 + xh) * 16 + 16;
                    obj->Y2Trigger = (y2 + yh) * 16 + 16;
                }
                int32_t q = f.ReadByte();
                if (q == 0)
                {
                    q--;
                }
                else if (q == 15)
                {
                    q++;
                }
                obj->X = (q + xh) * 16 + 8;
                obj->Y = (f.ReadByte() + yh + 1) * 16;
                obj->XTile = obj->X / 16;
                obj->YTile = obj->Y / 16;
                obj->Direction = f.ReadBoolean();
                obj->Counter   = f.ReadByte();
                obj->Status    = f.ReadByte();
                obj->Left      = f.ReadBoolean();
                obj->Down      = f.ReadBoolean();
                obj->Up        = f.ReadBoolean();
                obj->Right     = f.ReadBoolean();

                obj->NoActivated = true;
                obj->XYRoom = static_cast<uint8_t>(y * 16 + x);

                if (reverse_way && obj->Name == idDoor && obj->Status != 2)
                {
                    obj->Status = static_cast<uint8_t>(1 - obj->Status);
                }

                if (obj->Name == idDoor && obj->Status == start_slot)
                {
                    current_xy_room = obj->XYRoom;
                    hero_start_direction = obj->Direction;
                }
                obj->Fixed = true;
            }
        }
    }
    RemoveObject(temp);

    //загрузка слоёв комнат локации
    RoomsLayers = std::vector<std::vector<std::shared_ptr<RoomLayers>>>(room_x + room_y * 16);
    for (int32_t y = 0; y < room_y; y++)
    {
        for (int32_t x = 0; x < room_x; x++)
        {
            RoomsLayers[x + y * 16] = std::vector<std::shared_ptr<RoomLayers>>();
            int32_t layers_num = f.ReadByte();
            for (int32_t i = 0; i < layers_num; i++)
            {
                std::shared_ptr<RoomLayers> l = std::make_shared<RoomLayers>();

                l->Name = f.ReadString();
                int32_t tiles_num = f.ReadInt32();
                for (int32_t j = 0; j < tiles_num; j++)
                {
                    std::shared_ptr<RoomLayers::LayerTile> t = std::make_shared<RoomLayers::LayerTile>();
                    t->X    = f.ReadByte();
                    t->Y    = f.ReadByte();
                    t->Tile = f.ReadByte();
                    l->LayerTiles.push_back(t);
                }
                RoomsLayers[x + y * 16].push_back(l);
            }
        }
    }

    //загрузка некстовских тайлов
    Color tileset256[256][256];
    if (f.PeekChar() != -1)
    {
        for (int32_t j = 0; j < 256; j++)
        {
            for (int32_t i = 0; i < 256; i++)
            {
                tileset256[j][i] = Color::FromArgb(f.ReadInt32());
            }
        }
    }

    //прорисовка тайлсета в палитре некста
    for (int32_t i = 0; i < 256; i++)
    {
        Tileset[1][i] = std::make_shared<Surface>(16, 16);
        for (int32_t y = 0; y < 16; y++)
        {
            for (int32_t x = 0; x < 16; x++)
            {
                Tileset[1][i]->Draw(Point(x, y), tileset256[i][x + y * 16]);
            }
        }
    }

    //инициализируем свойства тайлсета
    for (int32_t i = 0; i < 256; i++)
    {
        TilesetProperty[i] = current_tilesets[0][i][36];
    }

    //прорисовка классического тайлсета
    DrawClassicTileset();
}

void Program::DrawClassicTileset()
{
    for (int32_t i = 0; i < 256; i++)
    {
        Tileset[0][i] = std::make_shared<Surface>(16, 16);
        for (int32_t y = 0; y < 16; y++)
        {
            for (int32_t x = 0; x < 16; x++)
            {
                uint8_t a = current_tilesets[0][i][y / 8 * 2 + x / 8 + 32];
                Color ink = attr_palette[0][(a & 7) + ((a >> 3) & 8)];
                Color paper = attr_palette[1][(a >> 3) & 15];

                if (bw_color_mode && TilesetProperty[i] != 1)
                {
                    ink = Color::Black;
                    paper = Color::White;
                }

                TilesetAttr[1][i][x][y] = paper;
                TilesetAttr[0][i][x][y] = ink;

                uint8_t p = current_tilesets[0][i][y * 2 + x / 8];
                const Color &c = ((p << (x % 8)) & 0x80) == 0 ? paper : ink;
                Tileset[0][i]->Draw(Point(x, y), c);
            }
        }
    }
}

void Program::NeedScrollRoom()
{
    int32_t x = hero_object->X - x_home;
    int32_t y = hero_object->Y - y_home;

    //вверх
    if (y < 31)
    {
        screen_copy->Blit(*screen, Point(0, 0));
        current_xy_room -= 16;
        scroll_direction = 1;
        scroll_cntr = 8;
    }
    //вниз
    else if (y >= 160)
    {
        screen_copy->Blit(*screen, Point(0, 0));
        current_xy_room += 16;
        scroll_direction = 3;
        scroll_cntr = 8;
    }
    //вправо
    else if (x >= 240)
    {
        screen_copy->Blit(*screen, Point(0, 0));
        current_xy_room++;
        scroll_direction = 2;
        scroll_cntr = 14;
    }
    //влево
    else if (x < 16)
    {
        screen_copy->Blit(*screen, Point(0, 0));
        current_xy_room--;
        scroll_direction = 4;
        scroll_cntr = 14;
    }
    if (scroll_cntr != 0)
    {
        InitRoom(false);
    }
}

void Program::IncGameCicleCounter()
{
    game_cicle_counter = (game_cicle_counter + 1) & 0xff;
}

void Program::SetBorder(const Color &c)
{
    Video::Screen().Fill(c);
}
