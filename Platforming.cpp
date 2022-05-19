#include "Platforming.h"

void Program::InitPlatforming(bool boss)
{
    statusbar = InitScreensProject("bar");
    select_menu = InitScreensProject("select_suit");

    game_mode = platforming_mode;
    prev_game_mode = platforming_mode;
    sprite_bottom = 160;

    InitFonts();
    ObjectAnimations.clear();
    LoadAnimations("Nova");
    LoadAnimations("Suit");
    LoadAnimations("Items");
    LoadAnimations("Dron");
    LoadAnimations("Tankette");
    LoadAnimations("Spider");
    LoadAnimations("Piranha");
    LoadAnimations("Jelly");
    LoadAnimations("Bug");
    LoadAnimations("DronBomber");
    LoadAnimations("Gun");
    LoadAnimations("Dragonfly");
    LoadAnimations("FighterBomber");
    LoadAnimations("AlienClaw");
    LoadAnimations("AlienWorm");
    LoadAnimations("Slime");
    LoadAnimations("SonusVenator");

    LoadAnimations("BigSpider");
    LoadAnimations("Craken");
    LoadAnimations("Moth");
    LoadAnimations("Rocketman");
    LoadAnimations("CrabBoss");
    LoadAnimations("FlyBoss");
    LoadAnimations("AlienPet");
    LoadAnimations("AlienSliderman");
    LoadAnimations("Megabrain");

    LoadAnimations("DLCJacqueline");
    LoadAnimations("DLCBoss");

    InitLocation(boss);
}

void Program::InitPlatformingStatusbar()
{
    DrawScreen(statusbar, 12);
    InitIcon(im_none);
    for (int32_t i = 0; i < 77; i++)
    {
        ResScaleCol(19 + i, 166);
        ResScaleCol(19 + i, 182);
        ResScaleCol(160 + i, 166);
        ResScaleCol(160 + i, 182);
    }
    hero_life_current = 0;
    hero_energy_current = 0;
    hero_weapon_current = 0;
    hero_path_current = 0;
}

void Program::InitLocation(bool boss)
{
    current_music = 255;

    ClearScreen();
    hero_path = 0;
    boss_mode = boss;
    in_boss_room = boss;
    room_cntr = 2;
    secret_boss_enabled = false;

    if (current_level != 5)
    {
        int32_t name;
        int32_t b = current_level - 1;
        int32_t c = current_location - 1;
        if (!boss_mode)
        {
            last_boss_fase = 0;
            name = b * 6 + c;
            if (b == 3)
            {
                level_music = 9;
            }
            else
            {
                if (c == 3)
                {
                    c = 0;
                }
                level_music = b * 3 + c;
            }
        }
        else
        {
            level_music = 10;

            if (b != 3)
            {
                name = b * 6 + 4;
                if (c != 0)
                {
                    name++;
                }
            }
            else
            {
                if (c < 6)
                {
                    name = c + 26;
                }
                else
                {
                    if (last_boss_fase == 3)
                    {
                        last_boss_fase--;
                        secret_boss_enabled = true;
                    }
                    name = 32 + last_boss_fase;
                    level_music++;
                }
            }
        }

        LoadLocationProject(name);


        int32_t prev_slot = start_slot;
        start_slot = 0;

        hero_object = CreateObject(idNova, 0, 0, false, true);
        hero_object->Animations = FindObjectAnimation("Nova");
        InitAnimation(hero_object, "Nova_Idle", true);
        hero_object->Priority = normal_priority;
        hero_object->haveGravity = true;

        on_ladder = false;
        is_jump = false;
        is_fly = false;
        hero_die = false;
        attack_cntr = 0;
        slide_cntr = 0;
        disable_control = false;

        if (secret_boss_enabled)
        {
            current_xy_room += 2;
        }
        InitRoom(true);
        MuteGameMusic();

        if (prev_slot != 0 || boss_mode)
        {
            if (secret_boss_enabled)
            {
                level_music = 249;
            }
            InitGameMusic(level_music, true);
            current_music = level_music;
        }

        location_status = 0;
        location_counter = 0;

        //загрузка показателей героя
        if (difficulty == 0)
        {
            start_weapon = 20;
            start_life = 77;
            start_energy = 77;
        }

        hero_life = start_life;
        if (hero_weapon_max < start_weapon)
        {
            hero_weapon_max = start_weapon;
        }
        if (hero_energy < start_energy)
        {
            hero_energy = start_energy;
        }
        if (hero_life == 0)
        {
            hero_life = 10;
        }

        //if (last_boss_fase == 0)
        //    current_suit = 0;
        SwitchSuite(true);

        //инициализация статусбара
        InitPlatformingStatusbar();
    }
    else

    {
        //DLC с Жаклин
        gun_on = false;
        double_jump_on = gun_on;
        on_ladder = false;
        is_jump = false;
        hero_die = false;
        attack_cntr = 0;
        disable_control = false;

        statusbar = InitScreensProject("j_bar");
        int32_t i = 36;
        int32_t m = 247;
        if (current_location != 1)
        {
            i++;
            boss_mode = true;
            m = 249;
            gun_on = true;
            double_jump_on = true;
        }
        LoadLocationProject(i);
        hero_object = CreateObject(idJacqueline, 0, 0, false, true);
        hero_object->Animations = FindObjectAnimation("DLCJacqueline");
        InitAnimation(hero_object, "JIdle", true);
        hero_object->Priority = normal_priority;
        hero_object->haveGravity = true;
        InitRoom(true);

        hero_life = 77;
        hero_weapon = 77;
        hero_weapon_max = 77;
        hero_energy = 0;
        InitDLCStatusbar();
        InitGameMusic(m, true);
    }
}

void Program::InitDLCStatusbar()
{
    DrawScreen(statusbar, 8);
    for (int32_t i = 0; i < 77; i++)
    {
        ResScaleCol(19 + i, 166);
        ResScaleCol(19 + i, 182);
        ResScaleCol(160 + i, 166);
        ResScaleCol(160 + i, 182);
    }
    hero_life_current = 0;
    hero_energy_current = 0;
    hero_weapon_current = 0;
    hero_path_current = 0;
}

void Program::TestKonamiCode()
{
    if (TestKonamiCode_cnt != 0)
    {
        TestKonamiCode_cnt--;
        if (TestKonamiCode_cnt == 0)
        {
            TestKonamiCode_pos = 0;
            return;
        }
    }
    if (GetLastKey(255))
    {
        return;
    }
    if (pressed_keys == TestKonamiCode_txt[TestKonamiCode_pos])
    {
        TestKonamiCode_pos++;
        TestKonamiCode_cnt = 30;
    }
    else if (TestKonamiCode_txt[TestKonamiCode_pos] == 0xff)
    {
        cheats_enabled = true;
        TestKonamiCode_pos = 0;
    }
}

void Program::UpdatePlatforming()
{
    //SetBorder(GetColor(ObjectsCount(idExplosion)));

    //скроллирование экрана
    if (scroll_cntr != 0)
    {
        ScrollRoom();
        return;
    }

    NeedScrollRoom();

    for (size_t i = 0; i < actual_objects.size(); i++)
    {
        std::shared_ptr<GameObject> obj = actual_objects[i];
        if (obj->Name == 0)
        {
            break;
        }
        ProcessingGameObject(obj);
        PlayAnimation(obj);
        if (obj->Name == 0)
        {
            i--;
        }
    }

    if (game_mode != platforming_mode || pause_cnt != 0)
    {
        return;
    }

    //эффект падения вниз
    if (secret_boss_enabled)
    {
        for (int32_t j = 0; j < 10; j++)
        {
            for (int32_t i = 0; i < 16; i++)
            {
                if (fall_down_effect[i][j] == 1)
                {
                    fall_down_effect[i][j] = 0;
                    Room[i][j] = 0;
                    screen_refresh_tab[i][j] = true;
                    if (j != 0)
                    {
                        fall_down_effect[i][j - 1] = 1;
                        Room[i][j - 1] = 1;
                        screen_refresh_tab[i][j - 1] = true;
                    }
                }
            }
        }
        fall_down_effect[rnd->Next() & 15][9] = 1;
    }


    DrawRoom();
    DrawGameObjects();

    if (scroll_cntr != 0)
    {
        scroll_screen->Blit(*screen, Point(0, 0));
        screen->Blit(*screen_copy, Point(0, 0));
    }

    IncGameCicleCounter();
    if (cntr_enter_in_room != 0)
    {
        cntr_enter_in_room--;
    }

    //обновление статус-бара
    UpdateIcon();
    if (hero_weapon < hero_weapon_max)
    {
        hero_weapon++;
    }
    hero_life_current = UpdateBar(hero_life_current, hero_life, 19, 166);
    hero_weapon_current = UpdateBar(hero_weapon_current, hero_weapon, 19, 182);
    hero_path_current = UpdateBar(hero_path_current, hero_path, 160, 166);
    hero_energy_current = UpdateBar(hero_energy_current, hero_energy, 160, 182);

    TestKonamiCode();

    //уменьшение батарейки
    if (!hero_die && hero_life != 0)
    {
        if (battery_cntr != 0)
        {
            battery_cntr--;
        }
        else if (current_suit != 0)
        {
            battery_cntr = 45;

            if (!immortal_mode)
            {
                hero_energy--;
            }
            if (hero_energy == 0)
            {
                prev_suit = current_suit;
                current_suit = 0;
                SwitchSuite(true);
                pause_cnt = 100;
                PauseGameMusic();
            }

            //предупреждение, что мало заряда батарей
            else if (hero_energy < 8)
            {
                InitSFX(sfx_lowpower);
            }
        }
    }

    //конец игры
    if (hero_life == 0 && !hero_object->AnimationPlayed)
    {
        InitGameOver();
    }

    //режим переключения костюмов
    if (GetKey(Key_Select) && !GetLastKey(Key_Select) && !hero_object->NoInterruptAnim)
    {
        if (current_level != 5)
        {
            InitSFX(sfx_switch);
            InitSuit();
        }
    }

    //выход в меню
    if ((pressed_keys & Key_Pause) != 0 && !GetLastKey(Key_Pause) && (in_boss_room == false || boss_mode == true))
    {
        MuteAllMusic();
        if (debug_mode)
        {
            InitDebugMenu();
        }
        else
        {
            InitMainMenu(true);
        }
    }

    //битва с финальным боссом
    if (last_boss_fase != 0 && !boss_mode && location_status == 1)
    {
        if (location_counter == 100)
        {
            disable_control = true;
            MuteAllMusic();
        }
        location_counter--;
        if (location_counter == 0)
        {
            if (last_boss_fase != 3 || stars_num == 48)
            {
                InitFinalBoss(last_boss_fase);
            }
            //финальный ролик
            else
            {
                if (difficulty == 1 && max_difficulty == 1)
                {
                    max_difficulty++;
                }
                if (difficulty != 2)
                {
                    InitNewGame();
                    SaveProgress();
                    InitScene(9);
                }
                else
                {
                    reverse_way = true;
                    current_location = 8;
                    InitLocation(false);
                }
            }
        }
    }

    //победа над драконом или боссом
    if (in_boss_room && !boss_mode && hero_path_current == 0)
    {
        //уровни 1-3
        if (current_level < 4)
        {

            //дракон
            if (current_location == 1)
            {
                if (location_status == 0)
                {
                    std::shared_ptr<GameObject> o = CreateObject(idMultiExplosions, 128, 96, false, true);
                    if (current_level == 2)
                    {
                        o->Y = 80;
                    }
                    o->Counter = 127;
                    o->NoVisible = true;
                    location_status++;
                }
                else if (location_status == 2)
                {
                    //взрыв колбы
                    int32_t x = 7;
                    int32_t y = 6;
                    if (current_level == 2)
                    {
                        y = 4;
                    }
                    int32_t t = 250;
                    for (int32_t j = 0; j < 3; j++)
                    {
                        for (int32_t i = 0; i < 2; i++)
                        {
                            NewTile(x + i, y + j, t);
                            t++;
                        }
                    }

                    std::shared_ptr<GameObject> o = CreateObject(idSuit, 128, 80, false, true);
                    if (current_level != 2)
                    {
                        o->Y = 112;
                    }
                    o->Type = 13;
                    o->Width = 7;
                    o->Height = -16;
                    o->haveGravity = true;
                    o->Fixed = true;
                    location_status++;
                }
                else if (location_status == 5)
                {
                    if (location_counter != 0)
                    {
                        location_counter--;
                        disable_control = true;
                    }
                    else
                    {
                        start_slot = 2;
                        InitLocation(false);
                    }
                }
            }

            //босс
            else
            {
                if (location_status == 1)
                {
                    if (location_counter != 0)
                    {
                        location_counter--;
                        disable_control = true;
                    }
                    else
                    {
                        if (difficulty != 2)
                        {
                            LevelComlete();
                        }
                        else
                        {
                            current_location = 4;
                            reverse_way = true;
                            InitLocation(false);
                        }
                        return;
                    }
                }
            }
        }

        //уровень 4
        else
        {
            if (current_location < 7)
            {
                if (location_status == 1)
                {
                    if (location_counter != 0)
                    {
                        location_counter--;
                    }
                    else
                    {
                        location_status++;
                    }
                }
                else if (location_status == 2)
                {
                    current_location++;
                    InitLocation(false);
                }
            }
        }
    }
}

void Program::LevelComlete()
{
    switch (current_level)
    {
    case 1:
        levels_complete |= 1;
        break;
    case 2:
        levels_complete |= 2;
        break;
    case 3:
        levels_complete |= 4;
        break;
    }
    InitScene(current_level + 1);
}

void Program::InitIcon(int32_t command)
{
    icon_mode = command;
    int32_t scr = 4;
    switch (command)
    {
    case im_damage:
        icon_cntr = 6;
        break;
    case im_noise:
        icon_cntr = 0;
        scr = 0;
        break;
    }
    DrawScreen(statusbar, scr);
}

void Program::UpdateIcon()
{
    icon_timer++;
    if (icon_timer >= 3)
    {
        icon_timer = 0;
        int32_t scr = 4;
        if (current_suit != 0)
        {
            scr = 8;
        }
        switch (icon_mode)
        {
        case im_noise:
            icon_cntr++;
            if (icon_cntr >= 4)
            {
                icon_cntr = 0;
            }
            scr = icon_cntr;
            break;
        case im_damage:
            switch (icon_cntr)
            {
            case 6:
            case 2:
                scr = 5;
                break;
            case 5:
            case 3:
                scr = 6;
                break;
            case 4:
                scr = 7;
                break;
            case 1:
                scr = 4;
                break;
            }
            if (current_suit != 0)
            {
                scr += 4;
            }
            icon_cntr--;
            if (icon_cntr == 0)
            {
                icon_mode = im_none;
            }
            break;
        }
        DrawScreen(statusbar, scr);
    }
}

void Program::InitFinalBoss(int32_t fase)
{
    start_life = 77;
    start_energy = 77;

    if (fase < final_scens_show || fase == 3)
    {
        current_level = 4;
        current_location = 7;
        if (difficulty != 0)
        {
            current_location++;
        }
        InitPlatforming(true);

        disable_control = false;
        InitRoom(true);
        location_status = 0;
    }
    else
    {
        if (fase >= 4)
        {
            fase = 3;
        }
        if (fase == 3 && difficulty == 2)
        {
            reverse_way = true;
            current_location = 8;
            InitLocation(false);
        }
        else
        {
            if (fase == 3 && difficulty == 1 && max_difficulty == 1)
            {
                max_difficulty++;
            }
            InitScene(fase + 6);
        }
        final_scens_show++;
    }
}
