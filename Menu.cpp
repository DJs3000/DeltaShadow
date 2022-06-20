void Program::InitDebugMenu()
{
    SetBorder(Color::Black);
    game_mode = debug_menu_mode;
    MuteAllMusic();
    ClearScreen();
    DrawDebugMenu();
    pressed_key_symbol = 0;
    NextPressedKey();
    last_keys = pressed_keys;
    reverse_way = false;
}

void Program::DrawDebugMenu()
{
    ClearScreen();
    int32_t x = 0;
    int32_t y = 0;
    int32_t n = 0;
    for (const auto &l : level_names)
    {
        invert_print = n == menu_pos;
        PrintString32(x, y, l);
        y++;
        if (y >= level_names.size() / 2)
        {
            y = 0;
            x += 16;
        }
        n++;
    }

    invert_print = n == menu_pos;
    std::string s = "Classic";
    if (sprite_mode == zx_next_mode)
    {
        s = "Next";
    }
    PrintString32(0, 16, "Sprites: " + s);
    n++;
    invert_print = n == menu_pos;
    s = "Classic";
    if (tiles_mode == zx_next_mode)
    {
        s = "Next";
    }
    PrintString32(0, 17, "Tiles: " + s);
    n++;
    invert_print = n == menu_pos;
    s = "AY";
    if (sound_mode == ts_mode)
    {
        s = "TS";
    }
    PrintString32(0, 18, "Music: " + s);
    n++;
    invert_print = n == menu_pos;
    if (have_suit[1] == true && have_suit[2] == true && have_suit[3] == true)
    {
        s = "YES";
    }
    else
    {
        s = "NO";
    }
    PrintString32(0, 19, "All suits enabled: " + s);
    n++;
    invert_print = n == menu_pos;
    if (immortal_mode)
    {
        s = "YES";
    }
    else
    {
        s = "NO";
    }
    PrintString32(0, 20, "Immortal mode: " + s);
    invert_print = false;

    PrintString32(0, 22, "ESC. Return to this menu");
    PrintString32(0, 23, "+/- change screen size");
}

void Program::UpdateDebugMenu()
{
    start_weapon = 20;
    start_life = 77;
    start_energy = 77;

    disable_control = false;

    if (GetPressedKey(Key_Down))
    {
        menu_pos++;
        if (menu_pos == 35)
        {
            menu_pos = 0;
        }
        if (menu_pos == 15)
        {
            menu_pos = 30;
        }
        DrawDebugMenu();
    }

    if (GetPressedKey(Key_Up))
    {
        menu_pos--;
        if (menu_pos < 0)
        {
            menu_pos = 34;
        }
        DrawDebugMenu();
    }

    if (GetPressedKey(Key_Right))
    {
        if (menu_pos < 15)
        {
            menu_pos = menu_pos + 15;
        }
        DrawDebugMenu();
    }

    if (GetPressedKey(Key_Left))
    {
        if (menu_pos >= 15 && menu_pos < 30)
        {
            menu_pos = menu_pos - 15;
        }
        DrawDebugMenu();
    }

    if (GetPressedKey(Key_Fire + Key_Jump + Key_Pause + Key_Select))
    {
        switch (menu_pos)
        {
        case 0:
            current_level = 4;
            InitRace();
            break;
        case 1:
            InitStealth();
            break;

            //level 1
        case 2:
            current_level = 1;
            current_location = 1;
            InitPlatforming(false);
            break;
        case 3:
            current_level = 1;
            current_location = 2;
            InitPlatforming(false);
            break;
        case 4:
            current_level = 1;
            current_location = 3;
            InitPlatforming(false);
            break;
        case 5:
            current_level = 1;
            current_location = 1;
            InitPlatforming(true);
            break;
        case 6:
            current_level = 1;
            current_location = 3;
            InitPlatforming(true);
            break;

            //level 2
        case 7:
            current_level = 2;
            current_location = 1;
            InitPlatforming(false);
            break;
        case 8:
            current_level = 2;
            current_location = 2;
            InitPlatforming(false);
            break;
        case 9:
            current_level = 2;
            current_location = 3;
            InitPlatforming(false);
            break;
        case 10:
            current_level = 2;
            current_location = 1;
            InitPlatforming(true);
            break;
        case 11:
            current_level = 2;
            current_location = 3;
            InitPlatforming(true);
            break;

            //level 3
        case 12:
            current_level = 3;
            current_location = 1;
            InitPlatforming(false);
            break;
        case 13:
            current_level = 3;
            current_location = 2;
            InitPlatforming(false);
            break;
        case 14:
            current_level = 3;
            current_location = 3;
            InitPlatforming(false);
            break;
        case 15:
            current_level = 3;
            current_location = 1;
            InitPlatforming(true);
            break;
        case 16:
            current_level = 3;
            current_location = 3;
            InitPlatforming(true);
            break;

            //level 4
        case 17:
            current_level = 4;
            current_location = 1;
            InitPlatforming(false);
            break;
        case 18:
            current_level = 4;
            current_location = 2;
            InitPlatforming(false);
            break;
        case 19:
            current_level = 4;
            current_location = 3;
            InitPlatforming(false);
            break;
        case 20:
            current_level = 4;
            current_location = 4;
            InitPlatforming(false);
            break;
        case 21:
            current_level = 4;
            current_location = 5;
            InitPlatforming(false);
            break;
        case 22:
            current_level = 4;
            current_location = 6;
            InitPlatforming(false);
            break;
        case 23:
            current_level = 4;
            current_location = 7;
            InitPlatforming(false);
            break;

        case 24:
            difficulty = max_difficulty;
            last_boss_fase = 0;
            InitFinalBoss(last_boss_fase);
            break;

        case 25:
            difficulty = max_difficulty;
            current_level = 1;
            current_location = 4;
            InitPlatforming(false);
            break;
        case 26:
            difficulty = max_difficulty;
            current_level = 2;
            current_location = 4;
            InitPlatforming(false);
            break;
        case 27:
            difficulty = max_difficulty;
            current_level = 3;
            current_location = 4;
            InitPlatforming(false);
            break;
        case 28:
            difficulty = max_difficulty;
            current_level = 4;
            current_location = 8;
            InitPlatforming(false);
            break;
        case 29:
            difficulty = 0;
            current_level = 5;
            current_location = 1;
            InitPlatforming(false);
            break;

        case 30:
            sprite_mode = 1 - sprite_mode;
            DrawDebugMenu();
            break;
        case 31:
            tiles_mode = 1 - tiles_mode;
            DrawDebugMenu();
            break;
        case 32:
            sound_mode = 1 - sound_mode;
            DrawDebugMenu();
            break;
        case 33:
            have_suit[1] = !have_suit[1];
            have_suit[2] = !have_suit[2];
            have_suit[3] = !have_suit[3];
            DrawDebugMenu();
            break;
        case 34:
            immortal_mode = !immortal_mode;
            DrawDebugMenu();
            break;
        }
    }

    if (pressed_key_symbol == L'1')
    {
        InitScene(1);
        return;
    }

    if (pressed_key_symbol == L'2')
    {
        InitScene(2);
        return;
    }

    if (pressed_key_symbol == L'3')
    {
        InitScene(3);
        return;
    }

    if (pressed_key_symbol == L'4')
    {
        InitScene(4);
        return;
    }

    if (pressed_key_symbol == L'5')
    {
        LoadProgress();
        InitScene(5);
        return;
    }

    if (pressed_key_symbol == L'6')
    {
        InitScene(6);
        return;
    }

    if (pressed_key_symbol == L'7')
    {
        InitScene(7);
        return;
    }

    if (pressed_key_symbol == L'8')
    {
        InitScene(8);
        return;
    }

    if (pressed_key_symbol == L'9')
    {
        InitScene(9);
        return;
    }


    if (pressed_key_symbol == 0xf4 && game_mode == debug_menu_mode)
    {
        LoadProgress();
        InitScene(5);
        return;
    }

    pressed_key_symbol = 0;
    NextPressedKey();
}

void Program::InitGameOver()
{
    game_mode = game_over_mode;
    MuteGameMusic();
    ClearScreen();
    statusbar = InitScreensProject("bar");
    DrawScreen(statusbar,13);
    InitGameMusic(248, false);
    game_cicle_counter = 0;
}

void Program::UpdateGameOver()
{
    if (GetKey(0x0ff))
    {
        if (!debug_mode)
        {
            if (prev_game_mode == platforming_mode)
            {
                if (boss_mode)
                {
                    boss_mode = false;
                    if (current_location == 1 && current_level < 4)
                    {
                        start_slot = 2;
                    }
                    else
                    {
                        start_slot = 1;
                    }
                }
                InitLocation(boss_mode);
            }
            else if (prev_game_mode == race_mode)
            {
                InitRace();
            }
            else if (prev_game_mode == stealth_mode)
            {
                InitStealth();
            }
        }
        else
        {
            InitDebugMenu();
        }
    }
}

void Program::InitSelectLevel()
{
    current_suit = 0;
    SaveProgress();
    pictogramm_y = 18;
    disable_control = false;

    game_mode = select_level_mode;
    prev_game_mode = select_level_mode;
    ClearScreen();
    MuteAllMusic();
    LoadTexts();
    select_level_screens = InitScreensProject("select_level");
    pictogramm_screens = select_level_screens;

    select_level_status = 0;

    current_level = 1;
    if (levels_complete != 15)
    {
        if ((levels_complete & 1) != 0)
        {
            current_level++;
            if ((levels_complete & 2) != 0)
            {
                current_level++;
            }
        }

        if ((levels_complete & 8) != 0)
        {
            if (difficulty == 0)
            {
                select_level_status = 2;
            }
            else
            {
                InitRace();
            }
        }
        else
        {
            InitMenuMusic(253, true);
        }
    }
    else
    {
        current_level = 4;
        InitMenuMusic(254, true);
    }

    game_cicle_counter = 0;
    scene_music_timer = 0;
    menu_keys = 255;
}

void Program::UpdateSelectLevel()
{
    if ((interrupt_counter & 3) != 0)
    {
        return;
    }

    last_keys = menu_keys;
    menu_keys = pressed_keys;
    bool skip = GetKey(Key_Fire + Key_Jump + Key_Select) && !GetLastKey(255);
    int32_t t = (game_cicle_counter >> 1) & 3;
    int32_t a = t;
    if (a == 3)
    {
        a = 1;
    }
    if (select_level_status == 1)
    {
        t = game_cicle_counter & 3;
    }

    //прорисовка задника города
    if (select_level_status < 2 && !last_tower)
    {
        DrawScreen(select_level_screens, 0);

        for (int32_t i = 0; i < 3; i++)
        {
            if (((levels_complete >> i) & 1) == 0)
            {
                DrawScreen(select_level_screens, i + 1);
            }
            else
            {
                DrawScreen(select_level_screens, i * 3 + 4 + a);
            }
        }

        if (!demo_version)
        {
            if (levels_complete != 15)
            {
                DrawScreen(select_level_screens, 4 * (current_level - 1) + 18 + t);
            }
        }
        else
        {
            if (levels_complete == 0)
            {
                DrawScreen(select_level_screens, 4 * (current_level - 1) + 18 + t);
            }
        }

        if (GetKey(Key_Pause))
        {
            InitMainMenu(true);
            return;
        }
    }

    //разговор перед выбором уровня
    if (select_level_status == 0)
    {
        if (levels_complete != 15)
        {
            //Жаклин говорит
            if (game_cicle_counter < 8)
            {
                if (!demo_version)
                {
                    if (levels_complete == 0)
                    {
                        InitSay(4, 48);
                    }
                    else if (levels_complete == 1 || levels_complete == 2 || levels_complete == 4)
                    {
                        InitSay(6, 48);
                    }
                    else if (levels_complete != 15)
                    {
                        InitSay(8, 48);
                    }
                }
                else
                {
                    if (levels_complete == 0)
                    {
                        InitSay(87, 48);
                    }
                    else
                    {
                        InitSay(89, 48);
                    }
                }
            }
            else if (game_cicle_counter == 128)
            {
                game_cicle_counter = 112;
            }

            else if (game_cicle_counter >= 8)
            {
                UpdateJacquelineSay();
            }

            if (!demo_version)
            {

                //уровень от 1 до 3
                if ((GetKey(Key_Left) && !GetLastKey(Key_Left)) || (GetKey(Key_Up) && !GetLastKey(Key_Up)))
                {
                    do
                    {
                        current_level++;
                        if (current_level == 4)
                        {
                            current_level = 1;
                        }
                    } while (((levels_complete >> (current_level - 1)) & 1) != 0);
                    InitSFX(sfx_switch);
                }

                if ((GetKey(Key_Right) && !GetLastKey(Key_Right)) || (GetKey(Key_Down) && !GetLastKey(Key_Down)))
                {
                    do
                    {
                        current_level--;
                        if (current_level == 0)
                        {
                            current_level = 3;
                        }
                    } while (((levels_complete >> (current_level - 1)) & 1) != 0);
                    InitSFX(sfx_switch);
                }
            }
        }

        //появление башни
        else
        {
            no_suit_run = !have_suit[1] && !have_suit[2] && !have_suit[3];
            if (select_level_fase != 2)
            {
                DrawScreen(select_level_screens, 13);
            }
            else
            {
                DrawScreen(select_level_screens, 17);
            }

            if (select_level_fase == 0)
            {
                if (game_cicle_counter == 47 || skip)
                {
                    game_cicle_counter = -1;
                    select_level_fase++;
                    if (skip)
                    {
                        select_level_fase++;
                    }
                    skip = false;
                }
            }
            else if (select_level_fase == 1)
            {
                int32_t n = 13;
                switch (game_cicle_counter)
                {
                case 0:
                case 16:
                case 30:
                case 42:
                case 52:
                case 60:
                case 66:
                case 70:
                case 72:
                case 74:
                case 76:
                    n = 14;
                    break;
                case 71:
                case 73:
                case 75:
                case 77:
                case 79:
                case 81:
                    n = 15;
                    break;
                case 78:
                case 80:
                case 82:
                case 84:
                case 86:
                case 88:
                    n = 16;
                    break;
                case 83:
                case 85:
                case 87:
                case 89:
                    n = 17;
                    break;
                }
                if (game_cicle_counter >= 90)
                {
                    n = 17;
                }

                DrawScreen(select_level_screens, n);

                if (game_cicle_counter == 141 || skip)
                {
                    game_cicle_counter = -1;
                    select_level_fase++;
                    skip = false;
                }
            }

            //Нова говорит
            else if (select_level_fase == 2)
            {
                if (game_cicle_counter < 8)
                {
                    DrawScreen(select_level_screens, 17);
                    InitSay(3, 46);
                }
                else if (game_cicle_counter == 128)
                {
                    game_cicle_counter = 112;
                }
                else if (game_cicle_counter >= 8)
                {
                    UpdateNovaSay();
                }
            }

            if (scene_music_timer == 495)
            {
                MuteAllMusic();
            }
            scene_music_timer++;
        }

        //выбор
        if (skip)
        {
            if (!demo_version)
            {
                game_cicle_counter = -1;
                select_level_status++;
                InitSFX(sfx_switch);
            }
            else
            {
                if (levels_complete == 0)
                {
                    game_cicle_counter = -1;
                    select_level_status++;
                    InitSFX(sfx_switch);
                }
            }
        }
    }


    else if (select_level_status == 1)
    {
        //вторая фраза Жаклин или включение уровня Жаклин
        if (levels_complete != 15)
        {
            //Жаклин говорит
            if (game_cicle_counter < 8)
            {
                if (!demo_version)
                {
                    if (levels_complete == 0)
                    {
                        InitSay(5, 48);
                    }
                    else if (levels_complete == 1 || levels_complete == 2 || levels_complete == 4)
                    {
                        InitSay(7, 48);
                    }
                    else if (levels_complete != 15)
                    {
                        ClearScreen();
                        InitText(9, 0, 11, 32, 2, 0x47);
                        last_tower = true;
                        MuteAllMusic();
                        type_with_sound = true;
                    }
                }
                else
                {
                    InitSay(88, 48);
                }
            }
            else if (game_cicle_counter == 128)
            {
                game_cicle_counter = 112;
            }

            else if (game_cicle_counter >= 8)
            {
                if (last_tower)
                {
                    PrintSymbol();
                    if (skip)
                    {
                        type_with_sound = false;
                        InitStealth();
                        last_tower = false;
                        return;
                    }
                }
                else
                {
                    UpdateJacquelineSay();
                }

                if (skip)
                {
                    if (difficulty == 0)
                    {
                        InitSFX(sfx_start);
                        select_level_status++;
                        game_cicle_counter = -1;
                        ClearScreen();
                        MuteAllMusic();
                    }
                    else
                    {
                        InitRace();
                    }
                }
            }
        }

        //включение гонки
        else
        {
            current_level = 4;
            InitRace();
            return;
        }
    }

    //анимация проезда к уровню
    else if (select_level_status == 2)
    {
        if (game_cicle_counter == 64 || skip || levels_complete == 15)
        {
            MuteAllMusic();
            current_location = 1;
            InitPlatforming(false);
            current_location = 1;
            reverse_way = false;
        }
        else
        {
            if (game_cicle_counter == 0)
            {
                DrawScreen(select_level_screens, 30);
                DrawScreen(select_level_screens, 32 + current_level);
                DrawScreen(select_level_screens, 36);
            }

            DrawScreen(select_level_screens, 31 + ((game_cicle_counter >> 3) & 1));

            if (game_cicle_counter == 18)
            {
                InitMenuMusic(252, true);
            }
            if (game_cicle_counter == 38)
            {
                MuteAllMusic();
            }

            if (game_cicle_counter >= 25)
            {
                int32_t n = game_cicle_counter - 25;
                if (n >= 10)
                {
                    n = 0;
                }
                DrawScreen(select_level_screens, 36 + n);
            }
        }
    }
    IncGameCicleCounter();
}

void Program::InitSay(int32_t text_num, int32_t pictogramm)
{
    pictogramm_pos = pictogramm;
    DrawScreen(pictogramm_screens, pictogramm);
    InitText(text_num, 8, pictogramm_y, 24, 6, 0x47);
}

bool Program::UpdateNovaSay()
{
    if (PrintSymbol())
    {
        if (texts[text_pos] == 32)
        {
            DrawScreen(pictogramm_screens, pictogramm_pos);
        }
        else
        {
            if ((game_cicle_counter & 1) != 0)
            {
                DrawScreen(pictogramm_screens, pictogramm_pos);
            }
            else
            {
                DrawScreen(pictogramm_screens, pictogramm_pos + 1);
            }
        }
        return true;
    }
    else
    {
        DrawScreen(pictogramm_screens, pictogramm_pos);
        return false;
    }
}

bool Program::UpdateJacquelineSay()
{
    if (PrintSymbol())
    {
        if (texts[text_pos] == 32)
        {
            DrawScreen(pictogramm_screens, pictogramm_pos + 2);
        }
        else
        {
            if ((game_cicle_counter & 1) != 0)
            {
                DrawScreen(pictogramm_screens, pictogramm_pos);
            }
            else
            {
                DrawScreen(pictogramm_screens, pictogramm_pos + 1);
            }
        }
        return true;
    }
    else
    {
        DrawScreen(pictogramm_screens, pictogramm_pos);
        return false;
    }
}

void Program::UpdateLoadScreen()
{
    int32_t i = (game_cicle_counter >> 3) & 3;
    if (i == 3)
    {
        i = 1;
    }
    DrawScreen(main_menu_scr, 63 + i);

    i = game_cicle_counter >> 1;
    if (i < 12)
    {
        DrawScreen(main_menu_scr, 51 + i);
    }
    else
    {
        DrawScreen(main_menu_scr, 62);
    }

    i = (i >> 1) & 7;
    if (i == 5)
    {
        i = 3;
    }
    else if (i == 6)
    {
        i = 2;
    }
    else if (i == 7)
    {
        i = 1;
    }
    DrawScreen(main_menu_scr, 66 + i);

    if ((game_cicle_counter & 63) == 0)
    {
        i = 71;
        if ((game_cicle_counter & 64) != 0)
        {
            i++;
            if ((rnd->Next() & 7) == 0)
            {
                i++;
            }
        }
        DrawScreen(main_menu_scr, i);
    }

    if (pressed_key_symbol != 0 && lspp == 0)
    {
        InitMainMenu(false);
        ClearScreen();
        DrawScreen(main_menu_scr, 0);
        InitSFX(sfx_switch);
    }
    lspp = pressed_key_symbol;
    IncGameCicleCounter();
}

void Program::InitMainMenu(bool hard_init)
{
    debug_mode = false; // NOTE: configure mode here
    game_mode = main_menu_mode;
    main_menu_pos = 0;
    SaveProgress();
    LoadTexts();

    if (hard_init)
    {
        ClearScreen();
        MuteMenuMusic();
        main_menu_scr = InitScreensProject("main_menu");
        DrawScreen(main_menu_scr, 0);
        InitMenuMusic(7, true);
    }

    main_menu_pos = 0;
    if (prev_game_mode == 0)
    {
        main_menu_pos = 2;
    }
    NextPressedKey();
    last_keys = pressed_keys;

    if (demo_version)
    {
        PrintDemoVersion();
    }
}

void Program::UpdateMainMenu()
{
    FillAttrRect(6, 9, 20, 6, 0x44);
    if (prev_game_mode == 0)
    {
        FillAttrRect(6, 9, 20, 2, 0x01);
    }

    if (noreaded_stars == 0)
    {
        FillAttrRect(6, 13, 20, 1, 0x01);
    }

    if (main_menu_pos != 4 || noreaded_stars != 0)
    {
        FillAttrRect(6, 9 + main_menu_pos, 20, 1, 0x60);
    }
    else
    {
        FillAttrRect(6, 9 + main_menu_pos, 20, 1, 0x48);
    }
    PrintText(10, 6, 9, 20, 6, 0);

    int32_t min = 0;
    if (prev_game_mode == 0)
    {
        min = 2;
    }
    main_menu_pos = MenuNavigation(main_menu_pos, min, 5);
    if (single_keys && GetPressedKey(Key_Fire + Key_Jump + Key_Select + Key_Pause))
    {
        if (GetPressedKey(Key_Pause) && prev_game_mode != platforming_mode && prev_game_mode != stealth_mode && prev_game_mode != race_mode && prev_game_mode != select_level_mode)
        {
            NextPressedKey();
            return;
        }

        //продолжить
        if (main_menu_pos == 0 || GetPressedKey(Key_Pause))
        {
            MuteMenuMusic();
            InitSFX(sfx_start);
            if (prev_game_mode == select_level_mode)
            {
                InitSelectLevel();
            }
            if (prev_game_mode == platforming_mode)
            {
                statusbar = InitScreensProject("bar");
                select_menu = InitScreensProject("select_suit");
                game_mode = platforming_mode;
                DrawClassicTileset();
                InitRoomTiles();
                InitFonts();
                InitPlatformingStatusbar();
                InitGameMusic(current_music, true);
            }
            if (prev_game_mode == stealth_mode)
            {
                statusbar = InitScreensProject("j_bar");
                game_mode = stealth_mode;
                DrawClassicTileset();
                InitRoomTiles();
                InitStelthStatusbar();
                InitGameMusic(current_music, true);
            }
            if (prev_game_mode == race_mode)
            {
                race_imgs = InitScreensProject("race");
                game_mode = race_mode;
                game_cicle_counter = 0;
                ClearScreen();
                DrawScreen(race_imgs, 0);
                for (int32_t i = 0; i < 77; i++)
                {
                    ResScaleCol(19 + i, 6);
                    ResScaleCol(160 + i, 6);
                }
                hero_life_current = 0;
                hero_path_current = 0;
                DrawRaceTop();
                ResumeGameMusic();
            }
            return;
        }

        InitSFX(sfx_switch);

        //отмена миссии
        if (main_menu_pos == 1)
        {
            game_mode = cancel_mission_mode;
            cancel_mission_pos = 1;
        }

        //новая игра
        else if (main_menu_pos == 2)
        {
            if (prev_game_mode == 0)
            {
                InitSelectDiff();
            }
            else
            {
                game_mode = new_game_mode;
                new_game_pos = 1;
                NextPressedKey();
                last_keys = pressed_keys;
            }
        }

        //настройки
        else if (main_menu_pos == 3)
        {
            InitSettings();
        }

        //входяшие
        else if (main_menu_pos == 4)
        {
            InitSelectMessage();
        }

        //об игре
        else if (main_menu_pos == 5)
        {
            game_mode = read_message_mode;
            DrawScreen(main_menu_scr, 1);
            read_message_home = 0;
            read_message_scroll = false;
            read_message_num = 75;
        }
    }

    IncGameCicleCounter();
    NextPressedKey();

    if (demo_version)
    {
        PrintDemoVersion();
    }
}

void Program::UpdateNewGame()
{
    FillAttrRect(6, 9, 20, 6, 0x44);
    if (new_game_pos == 0)
    {
        FillAttrRect(11, 14, 4, 1, 0x60);
    }
    else
    {
        FillAttrRect(16, 14, 4, 1, 0x60);
    }
    PrintText(11, 6, 9, 20, 6, 0);

    new_game_pos = MenuNavigation(new_game_pos, 0, 1);
    if (GetPressedKey(Key_Fire + Key_Jump + Key_Select + Key_Pause))
    {
        InitSFX(sfx_switch);
        if (new_game_pos != 0 || GetPressedKey(Key_Pause))
        {
            InitMainMenu(false);
        }
        else
        {
            InitSelectDiff();
        }
    }
    NextPressedKey();
}

void Program::UpdateCancelMission()
{
    FillAttrRect(6, 9, 20, 6, 0x44);
    if (cancel_mission_pos == 0)
    {
        FillAttrRect(11, 14, 4, 1, 0x60);
    }
    else
    {
        FillAttrRect(16, 14, 4, 1, 0x60);
    }
    PrintText(13, 6, 9, 20, 6, 0);

    cancel_mission_pos = MenuNavigation(cancel_mission_pos, 0, 1);
    if (GetPressedKey(Key_Fire + Key_Jump + Key_Select + Key_Pause))
    {
        if (cancel_mission_pos != 0 || GetPressedKey(Key_Pause))
        {
            InitSFX(sfx_switch);
            InitMainMenu(false);
        }
        else
        {
            InitSFX(sfx_start);
            InitSelectLevel();
        }
    }

    NextPressedKey();
}

void Program::InitSelectDiff()
{
    game_mode = select_diff_mode;
    difficulty = 0;
    NextPressedKey();
    last_keys = pressed_keys;
}

void Program::UpdateSelectDiff()
{
    FillAttrRect(6, 9, 20, 6, 0x44);
    int32_t y = 11;
    if (max_difficulty == 1)
    {
        y++;
    }
    FillAttrRect(6, y + difficulty, 20, 1, 0x60);
    int32_t pos = FindText(12);
    pos = PrintString(pos, 6, 9);
    pos = PrintString(pos, 6, 10);

    for (int32_t i = 0; i < 1 + max_difficulty; i++)
    {
        pos = PrintString(pos, 6, y);
        y++;
    }
    if (max_difficulty != 2)
    {
        pos = NextString(pos);
    }
    PrintString(pos, 6, y);

    difficulty = MenuNavigation(difficulty, 0, max_difficulty + 1);
    bool ret = false;
    if (GetPressedKey(Key_Fire + Key_Jump + Key_Select))
    {
        if (difficulty == max_difficulty + 1)
        {
            ret = true;
        }
        else
        {
            InitSFX(sfx_start);
            InitNewGame();
            InitSelectLevel();
            return;
        }
    }
    if (GetPressedKey(Key_Pause) || ret)
    {
        InitSFX(sfx_switch);
        InitMainMenu(false);
        return;
    }
    NextPressedKey();
}

void Program::InitSelectMessage()
{
    game_mode = select_message_mode;
    DrawScreen(main_menu_scr, 1);
    NextPressedKey();
    last_keys = pressed_keys;

    if (demo_version)
    {
        PrintDemoVersion();
    }
}

void Program::UpdateSelectMessage()
{
    if ((interrupt_counter & 3) == 0 || GetPressedKey(255))
    {

        FillAttrRect(5, 3, 22, 17, 0x44);

        int32_t empty_str = FindText(26);
        int32_t str = NextString(empty_str);
        for (int32_t i = 0; i < select_message_home; i++)
        {
            str = NextString(str);
        }
        int32_t y = 3;
        int32_t pos = select_message_home;
        for (int32_t i = 0; i < 17; i++)
        {
            if (pos == 48)
            {
                if (i != select_message_pos)
                {
                    FillAttrRect(5, y, 22, 1, 0x44);
                }
                else
                {
                    FillAttrRect(5, y, 22, 1, 0x60);
                }
                PrintString(str, 5, y);
            }
            else if (pos < stars_num)
            {
                if ((noreaded_stars & static_cast<uint64_t>(1) << pos) == 0)
                {
                    if (i != select_message_pos)
                    {
                        FillAttrRect(5, y, 22, 1, 0x01);
                    }
                    else
                    {
                        FillAttrRect(5, y, 22, 1, 0x48);
                    }
                }
                else if (i == select_message_pos)
                {
                    FillAttrRect(5, y, 22, 1, 0x60);
                }
                str = PrintString(str, 5, y);
            }
            else
            {
                if (i == select_message_pos)
                {
                    FillAttrRect(5, y, 22, 1, 0x48);
                }
                else
                {
                    FillAttrRect(5, y, 22, 1, 0x01);
                }
                PrintString(empty_str, 5, y);
                str = NextString(str);
            }
            y++;
            pos++;
        }

        if (select_message_home != 32 && (game_cicle_counter & 4) != 0)
        {
            uint8_t c = 0x44;
            if (select_message_pos == 16)
            {
                c = 0x4c;
            }
            FillAttrRect(26, 19, 1, 1, c);
            DrawSymbol32(26, 19, 95, 0);
        }

        if (select_message_home != 0 && (game_cicle_counter & 4) != 0)
        {
            uint8_t c = 0x44;
            if (select_message_pos == 0)
            {
                c = 0x4c;
            }
            FillAttrRect(26, 3, 1, 1, c);
            DrawSymbol32(26, 3, 94, 0);
        }

        if (GetPressedKey(Key_Pause) || (select_message_home + select_message_pos == 48 && GetPressedKey(Key_Fire + Key_Jump + Key_Select)))
        {
            select_message_home = 0;
            select_message_pos = 0;
            InitSFX(sfx_switch);
            InitMainMenu(false);
            main_menu_pos = 4;
            DrawScreen(main_menu_scr, 0);
        }

        if (GetPressedKey(Key_Down) && select_message_home + select_message_pos < 48)
        {
            if (select_message_pos >= 16)
            {
                select_message_home++;
            }
            else
            {
                select_message_pos++;
            }
            InitSFX(sfx_switch);
        }

        if (GetPressedKey(Key_Up) && select_message_home + select_message_pos > 0)
        {
            if (select_message_pos == 0)
            {
                select_message_home--;
            }
            else
            {
                select_message_pos--;
            }
            InitSFX(sfx_switch);
        }

        if (GetPressedKey(Key_Left) && select_message_home + select_message_pos != 0)
        {
            select_message_home = 0;
            select_message_pos = 0;
            InitSFX(sfx_switch);
        }

        if (GetPressedKey(Key_Right) && select_message_home + select_message_pos != 48)
        {
            select_message_home = 32;
            select_message_pos = 16;
            InitSFX(sfx_switch);
        }

        int32_t n = select_message_home + select_message_pos;
        if (GetPressedKey(Key_Fire + Key_Jump + Key_Select) && n < stars_num)
        {
            noreaded_stars &= ~(static_cast<uint64_t>(1) << n);
            InitSFX(sfx_switch);
            last_keys = pressed_keys;
            DrawScreen(main_menu_scr, 1);
            game_mode = read_message_mode;
            read_message_home = 0;
            read_message_scroll = false;

            //инициализация сообщения
            read_message_num = n + 27;
            str = FindText(read_message_num);
            uint8_t q = 0;
            while (static_cast<uint8_t>(texts[str]) != 255)
            {
                if (texts[str] == '*')
                {
                    texts[str] = q;
                    q++;
                    if (q == 32)
                    {
                        q = 176;
                    }
                }
                str++;
            }

            std::shared_ptr<Program::Sprite> spr = FindSprite(main_menu_scr, std::to_string(n + 1));
            int32_t symbol = 0;
            for (int32_t j = 0; j < 8; j++)
            {
                for (int32_t i = 0; i < 8; i++)
                {
                    for (int32_t y2 = 0; y2 < 8; y2++)
                    {
                        for (int32_t x = 0; x < 8; x++)
                        {
                            if (tiles_mode == 0)
                            {
                                font32[symbol][x][y2] = (spr->tiles[i][j]->data[y2 + 1] & (128 >> x)) != 0;
                            }
                            else
                            {
                                font32[symbol][x][y2] = (spr->tiles[i][j]->data[y2 * 8 + x]) != 130;
                            }
                        }
                    }
                    symbol++;
                    if (symbol == 32)
                    {
                        symbol = 176;
                    }
                }
            }

        }
        IncGameCicleCounter();
    }
    NextPressedKey();

    if (demo_version)
    {
        PrintDemoVersion();
    }
}

void Program::UpdateReadMessage()
{
    if ((interrupt_counter & 3) == 0 || GetPressedKey(255))
    {
        read_message_scroll = false;
        read_message_down = false;
        FillAttrRect(5, 3, 22, 17, 0x44);
        int32_t str = FindText(read_message_num);
        for (int32_t i = 0; i < read_message_home; i++)
        {
            str = NextString(str);
        }
        int32_t y = 3;
        for (int32_t i = 0; i < 17; i++)
        {
            str = PrintString(str, 5, y);
            y++;
            if (texts[str - 1] == 255)
            {
                break;
            }
        }
        if (texts[str - 1] != 255)
        {
            read_message_scroll = true;
            read_message_down = true;
        }


        if (read_message_down && (game_cicle_counter & 4) != 0)
        {
            DrawSymbol32(26, 19, 95, 0);
        }

        if (read_message_home != 0 && (game_cicle_counter & 4) != 0)
        {
            DrawSymbol32(26, 3, 94, 0);
        }

        if (GetPressedKey(Key_Up + Key_Left) && read_message_home != 0)
        {
            read_message_home--;
            InitSFX(sfx_switch);
        }

        if (GetPressedKey(Key_Down + Key_Right) && read_message_scroll)
        {
            read_message_home++;
            InitSFX(sfx_switch);
            read_message_scroll = false;
        }

        if (GetPressedKey(Key_Pause + Key_Fire + Key_Jump + Key_Select))
        {
            InitSFX(sfx_switch);
            if (read_message_num != 75)
            {
                InitSelectMessage();
            }
            else
            {
                InitMainMenu(false);
                main_menu_pos = 5;
                DrawScreen(main_menu_scr, 0);
            }
        }


        IncGameCicleCounter();
    }
    NextPressedKey();
}

void Program::InitSettings()
{
    game_mode = settings_mode;
    NextPressedKey();
    last_keys = pressed_keys;
}

void Program::UpdateSettings()
{
    FillAttrRect(6, 8, 20, 8, 0x44);
    FillAttrRect(6, 10 + settings_pos, 20, 1, 0x60);
    PrintText(77, 6, 10, 20, 5, 0);

    settings_pos = MenuNavigation(settings_pos, 0, 4);
    bool ret = false;
    if (GetPressedKey(Key_Fire + Key_Jump + Key_Select))
    {
        if (settings_pos == 4)
        {
            ret = true;
        }
        else
        {
            InitSFX(sfx_switch);

            //графика
            if (settings_pos == 0)
            {
                game_mode = graphic_settings_mode;
            }
            //управление
            else if (settings_pos == 1)
            {
                game_mode = control_settings_mode;
            }
            //звук
            else if (settings_pos == 2)
            {
                game_mode = sound_settings_mode;
            }
            //система
            else if (settings_pos == 3)
            {
                game_mode = system_settings_mode;
            }
            NextPressedKey();
            last_keys = pressed_keys;
        }
    }

    if (GetPressedKey(Key_Pause) || ret)
    {
        settings_pos = 0;
        InitSFX(sfx_switch);
        InitMainMenu(false);
        main_menu_pos = 3;
    }
    NextPressedKey();
}

void Program::UpdateControlsSettings()
{
    FillAttrRect(6, 8, 20, 8, 0x44);
    FillAttrRect(6, 10 + control_pos, 20, 1, 0x60);
    int32_t t = FindText(78);
    t = PrintString(t, 6, 10);
    t = PrintString(t, 6, 11);
    bool joystick_off = false;
    bool c = false;
    if (joystick_off)
    {
        FillAttrRect(6, 12, 20, 1, 0x01);
        c = true;
    }
    //if (kempston_on)
    //{
    //    t = NextString(t);
    //}
    //t = PrintString(t, 6, 12);
    //if (!kempston_on)
    //{
    //    t = NextString(t);
    //}
    t = NextString(t);
    t = NextString(t);
    PrintString(t, 6, 12);


    control_pos = MenuNavigation(control_pos, 0, 2);
    if (c && control_pos == 2)
    {
        if (GetPressedKey(Key_Up))
        {
            control_pos--;
        }
        else if (GetPressedKey(Key_Down))
        {
            control_pos++;
        }
    }

    bool ret = false;
    if (GetPressedKey(Key_Fire + Key_Jump + Key_Select))
    {
        if (control_pos == 2)
        {
            ret = true;
        }
        else
        {
            InitSFX(sfx_switch);

            //переопределить
            if (control_pos == 0)
            {
                game_mode = redefine_mode;
                redefine_pos = 0;
                pressed_key_symbol = 0;
                redefine_pause = 50;

                FillAttrRect(6, 8, 20, 8, 0x44);
            }
            //сброс на стандарт
            else if (control_pos == 1)
            {
                for (int32_t i = 0; i < 8; i++)
                {
                    KeysMap[i] = KeysMapStandart[i];
                    PressedKeysStatus = 0;
                }
                NextPressedKey();
                last_keys = pressed_keys;
                InitSFX(sfx_switch);
                InitSettings();

            }
        }
    }

    if (GetPressedKey(Key_Pause) || ret)
    {
        control_pos = 0;
        InitSFX(sfx_switch);
        InitSettings();
    }
    NextPressedKey();
}

void Program::UpdateRedefine()
{
    FillAttrRect(6, 8, 19, 8, 0x44);
    if (redefine_pos != 8)
    {
        FillAttrRect(6, 8 + redefine_pos, 20, 1, 0x60);
        PrintText(79, 6, 8, 19, 8, 0);
    }
    else
    {
        PrintText(79, 6, 8, 19, 8, 0);
        redefine_pause--;
        if (redefine_pause == 0)
        {
            game_mode = areyousure_mode;
            FillAttrRect(6, 8, 20, 8, 0x44);
            PrintText(83, 6, 11, 20, 2, 0);
            pressed_key_symbol = 0;
        }
        return;
    }

    if (pressed_key_symbol != 0)
    {
        bool e = false;
        for (const auto &k : KeysMapNew)
        {
            if (k == pressed_key)
            {
                e = true;
                break;
            }
        }
        if (!e)
        {
            KeysMapNew[redefine_tab[redefine_pos]] = pressed_key;
            InitSFX(sfx_switch);
            DrawSymbol32(25, 8 + redefine_pos, static_cast<uint8_t>(pressed_key_symbol), 0x44);
            redefine_pos++;
        }
        pressed_key_symbol = 0;
    }
}

void Program::UpdateGraphicSettings()
{
    FillAttrRect(6, 8, 20, 8, 0x44);
    FillAttrRect(6, 10 + graphic_pos, 20, 1, 0x60);

    int32_t b;
    if (release_type == classic_version)
    {
        b = 0;
    }
    else
    {
        b = 1;
        if (tiles_mode != 0)
        {
            b = 2;
        }
        FillAttrRect(6, 10, 20, b, 0x01);
    }

    int32_t t = FindText(80);
    for (int32_t i = 0; i < graphics_quality; i++)
    {
        t = NextString(t);
    }
    PrintString(t, 6, 10);
    for (int32_t i = 0; i < 3 - graphics_quality; i++)
    {
        t = NextString(t);
    }
    if (!bw_color_mode)
    {
        t = NextString(t);
    }
    t = PrintString(t, 6, 11);
    if (bw_color_mode)
    {
        t = NextString(t);
    }
    if (scroll_on)
    {
        t = NextString(t);
    }
    t = PrintString(t, 6, 12);
    if (!scroll_on)
    {
        t = NextString(t);
    }
    PrintString(t, 6, 13);

    graphic_pos = MenuNavigation(graphic_pos, b, 3);

    bool ret = false;

    if (GetPressedKey(Key_Fire + Key_Jump + Key_Select))
    {
        if (graphic_pos == 3)
        {
            ret = true;
        }
        else
        {
            InitSFX(sfx_switch);
            if (graphic_pos == 0)
            {
                graphics_quality++;
                if (graphics_quality == 3)
                {
                    graphics_quality = 0;
                }
            }
            else if (graphic_pos == 1)
            {
                bw_color_mode = !bw_color_mode;
            }
            else if (graphic_pos == 2)
            {
                scroll_on = !scroll_on;
            }
        }
    }

    if (GetPressedKey(Key_Pause) || ret)
    {
        graphic_pos = 0;
        InitSFX(sfx_switch);
        InitSettings();
    }

    NextPressedKey();
}

void Program::UpdateSoundSettings()
{
    FillAttrRect(6, 8, 20, 8, 0x44);
    FillAttrRect(6, 10 + sound_pos, 20, 1, 0x60);


    bool c = false;
    if (!music_on)
    {
        c = true;
        FillAttrRect(6, 12, 20, 1, 0x01);
    }

    int32_t t = FindText(81);
    if (music_on)
    {
        t = NextString(t);
    }
    t = PrintString(t, 6, 10);
    if (!music_on)
    {
        t = NextString(t);
    }
    if (sound_on)
    {
        t = NextString(t);
    }
    t = PrintString(t, 6, 11);
    if (!sound_on)
    {
        t = NextString(t);
    }
    t = PrintString(t, 6, 12);
    PrintString(t, 6, 13);


    sound_pos = MenuNavigation(sound_pos, 0, 3);
    if (c && sound_pos == 2)
    {
        if (GetPressedKey(Key_Up))
        {
            sound_pos--;
        }
        else if (GetPressedKey(Key_Down))
        {
            sound_pos++;
        }
    }

    bool ret = false;

    if (GetPressedKey(Key_Fire + Key_Jump + Key_Select))
    {
        if (sound_pos == 3)
        {
            ret = true;
        }
        else
        {
            if (sound_pos == 0)
            {
                music_on = !music_on;
                if (!music_on)
                {
                    MuteMenuMusic();
                }
                else
                {
                    InitMenuMusic(7, true);
                }
            }
            else if (sound_pos == 1)
            {
                sound_on = !sound_on;
            }
            else if (sound_pos == 2)
            {
                game_mode = player_mode;
                DrawScreen(main_menu_scr, 1);
                NextPressedKey();
                last_keys = pressed_keys;
                InitSFX(sfx_switch);
                MuteMenuMusic();
                return;
            }
            InitSFX(sfx_switch);
        }
    }

    if (GetPressedKey(Key_Pause) || ret)
    {
        sound_pos = 0;
        InitSFX(sfx_switch);
        InitSettings();
    }

    NextPressedKey();

    if (demo_version)
    {
        PrintDemoVersion();
    }
}

void Program::UpdateSystemSettings()
{
    FillAttrRect(6, 8, 20, 8, 0x44);
    FillAttrRect(6, 9 + system_pos, 20, 1, 0x60);

    int32_t b;
    if (release_type == classic_version)
    {
        b = 3;
        FillAttrRect(6, 9, 20, 3, 0x01);
    }
    else
    {
        b = 0;
    }

    int32_t t = FindText(82);
    t = PrintString(t, 6, 9);
    t = NextString(t);
    t = NextString(t);

    if (sprite_mode != 0)
    {
        t = NextString(t);
    }
    t = PrintString(t, 6, 10);
    if (sprite_mode == 0)
    {
        t = NextString(t);
    }

    if (tiles_mode != 0)
    {
        t = NextString(t);
    }
    t = PrintString(t, 6, 11);
    if (tiles_mode == 0)
    {
        t = NextString(t);
    }

    if (sound_mode != 0)
    {
        t = NextString(t);
    }
    t = PrintString(t, 6, 12);
    if (sound_mode == 0)
    {
        t = NextString(t);
    }

    t = PrintString(t, 6, 13);
    PrintString(t, 6, 14);

    system_pos = MenuNavigation(system_pos, b, 5);
    bool ret = false;

    if (GetPressedKey(Key_Fire + Key_Jump + Key_Select))
    {
        if (system_pos == 5)
        {
            ret = true;
        }
        else
        {
            if (system_pos == 0)
            {
                //C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string and was converted to C++ 'if-else' logic:
                //					switch (language)
                //ORIGINAL LINE: case "English":
                if (language == "English")
                {
                    language = "Russian";
                }
                //ORIGINAL LINE: case "Russian":
                else if (language == "Russian")
                {
                    language = "Polish";
                }
                //ORIGINAL LINE: case "Polish":
                else if (language == "Polish")
                {
                    language = "Spanish";
                }
                //ORIGINAL LINE: case "Spanish":
                else if (language == "Spanish")
                {
                    language = "English";
                }
                LoadTexts();
            }
            else if (system_pos == 1)
            {
                sprite_mode = 1 - sprite_mode;
                if (sprite_mode != 0)
                {
                    graphics_quality = 2;
                    bw_color_mode = false;
                }
            }
            else if (system_pos == 2)
            {
                tiles_mode = 1 - tiles_mode;
                if (tiles_mode != 0)
                {
                    graphics_quality = 2;
                    bw_color_mode = false;
                }
                main_menu_scr = InitScreensProject("main_menu");
                DrawScreen(main_menu_scr, 0);
            }
            else if (system_pos == 3)
            {
                MuteMenuMusic();
                sound_mode = 1 - sound_mode;
                InitMenuMusic(7, true);
            }
            else if (system_pos == 4)
            {
                game_mode = reset_mode;
                reset_pos = 1;
            }
            InitSFX(sfx_switch);
        }
    }
    if (GetPressedKey(Key_Pause) || ret)
    {
        system_pos = 0;
        InitSFX(sfx_switch);
        InitSettings();
    }
    NextPressedKey();
}

void Program::UpdateAreYouSure()
{
    if (pressed_key_symbol == 0)
    {
        return;
    }
    else if (pressed_key_symbol == L'Y')
    {
        for (int32_t i = 0; i < 8; i++)
        {
            KeysMap[i] = KeysMapNew[i];
        }
        InitSFX(sfx_switch);
        game_mode = control_settings_mode;
    }
    else if (pressed_key_symbol == L'N')
    {
        InitSFX(sfx_switch);
        game_mode = control_settings_mode;
    }
    NextPressedKey();
    last_keys = pressed_keys;
    pressed_key_symbol = 0;
}

void Program::UpdateReset()
{
    FillAttrRect(6, 9, 20, 6, 0x44);
    if (reset_pos == 0)
    {
        FillAttrRect(11, 14, 4, 1, 0x60);
    }
    else
    {
        FillAttrRect(16, 14, 4, 1, 0x60);
    }
    PrintText(84, 6, 9, 20, 6, 0);

    reset_pos = MenuNavigation(reset_pos, 0, 1);
    if (GetPressedKey(Key_Fire + Key_Jump + Key_Select + Key_Pause))
    {
        InitSFX(sfx_switch);
        if (reset_pos != 0 || GetPressedKey(Key_Pause))
        {
            game_mode = system_settings_mode;
        }
        else
        {
            InitNewGame();

            collected_stars = 1;
            noreaded_stars = 1;
            stars_num = 1;
            max_difficulty = 1;

            last_keys = pressed_keys;
            InitMainMenu(true);
        }
    }

    NextPressedKey();
}

void Program::UpdatePlayer()
{
    if ((interrupt_counter & 3) == 0)
    {
        FillAttrRect(5, 3, 22, 17, 0x44);

        int32_t str = FindText(85);
        for (int32_t i = 0; i < player_home; i++)
        {
            str = NextString(str);
        }
        int32_t y = 3;
        int32_t pos = player_home;
        for (int32_t i = 0; i < 17; i++)
        {
            if (i == player_pos)
            {
                FillAttrRect(5, y, 22, 1, 0x60);
            }
            str = PrintString(str, 5, y);
            y++;
            pos++;
        }

        if (player_home != 3 && (game_cicle_counter & 4) != 0)
        {
            DrawSymbol32(26, 19, 95, 0);
        }

        if (player_home != 0 && (game_cicle_counter & 4) != 0)
        {
            DrawSymbol32(26, 3, 94, 0);
        }

        IncGameCicleCounter();
    }

    if (GetPressedKey(Key_Pause) || (GetPressedKey(Key_Fire + Key_Jump + Key_Select) && player_home + player_pos == 19))
    {
        player_home = 0;
        player_pos = 0;
        InitSFX(sfx_switch);
        game_mode = sound_settings_mode;
        sound_pos = 2;
        DrawScreen(main_menu_scr, 0);
        MuteMenuMusic();
        InitMenuMusic(7, true);
        NextPressedKey();
        return;
    }

    if (GetPressedKey(Key_Down) && player_home + player_pos < 19)
    {
        if (player_pos >= 16)
        {
            player_home++;
        }
        else
        {
            player_pos++;
        }
        InitSFX(sfx_switch);
    }

    if (GetPressedKey(Key_Up) && player_home + player_pos > 0)
    {
        if (player_pos == 0)
        {
            player_home--;
        }
        else
        {
            player_pos--;
        }
        InitSFX(sfx_switch);
    }

    if (GetPressedKey(Key_Left) && player_home + player_pos != 0)
    {
        player_home = 0;
        player_pos = 0;
        InitSFX(sfx_switch);
    }

    if (GetPressedKey(Key_Right) && player_home + player_pos != 19)
    {
        player_home = 3;
        player_pos = 16;
        InitSFX(sfx_switch);
    }

    if (GetPressedKey(Key_Fire + Key_Jump + Key_Select))
    {
        MuteMenuMusic();
        int32_t n = player_home + player_pos;
        if (n < 14)
        {
            if (n >= 12)
            {
                n += 2;
            }

        }
        else if (n == 14)
        {
            n = 248;
        }
        else
        {
            n = n - 15 + 250;
            if (n >= 252)
            {
                n++;
            }
        }

        //альтернатива без зацикливания
        InitMenuMusic(n, false);
    }
    NextPressedKey();

    if (demo_version)
    {
        PrintDemoVersion();
    }
}

void Program::InitNewGame()
{
    prev_game_mode = 0;
    levels_complete = 0;
    final_scens_show = 0;
    last_boss_fase = 0;
    for (int32_t i = 1; i < 4; i++)
    {
        have_suit[i] = false;
    }
    current_suit = 0;
    reverse_way = false;
}

int32_t Program::MenuNavigation(int32_t current_pos, int32_t min, int32_t max)
{
    if (current_pos < min)
    {
        current_pos = min;
    }
    if (current_pos >= max)
    {
        current_pos = max;
    }
    if (GetPressedKey(Key_Down) && current_pos < max)
    {
        current_pos++;
        InitSFX(sfx_switch);
    }
    if (GetPressedKey(Key_Up) && current_pos >= min + 1)
    {
        current_pos--;
        InitSFX(sfx_switch);
    }
    if (GetPressedKey(Key_Right) && current_pos != max)
    {
        current_pos = max;
        InitSFX(sfx_switch);
    }
    if (GetPressedKey(Key_Left) && current_pos != min)
    {
        current_pos = min;
        InitSFX(sfx_switch);
    }

    return current_pos;
}

void Program::PrintDemoVersion()
{
    FillAttrRect(0, 0, 12, 1, 7);
    FillAttrRect(20, 23, 12, 1, 7);
    PrintString32(0, 0, "Demo version");
    PrintString32(20, 23, "Demo version");
}
