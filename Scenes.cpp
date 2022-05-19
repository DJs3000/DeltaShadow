#include "Scenes.h"

void Program::InitScene(int32_t num)
{
    MuteAllMusic();
    SetBorder(Color::Black);
    scene_num = num;
    LoadTexts();
    game_mode = clip_mode;
    std::string scene_name = "";
    pictogramm_y = 10;
    switch (scene_num)
    {
    case 1:
        scene_name = "j_escape";
        pictogramm_y = 17;
        break;
    case 2:
        scene_name = "escape_1";
        break;
    case 3:
        scene_name = "escape_2";
        break;
    case 4:
        scene_name = "escape_3";
        break;
    case 5:
        scene_name = "intro";
        pictogramm_y = 18;
        break;
    case 6:
    case 7:
    case 8:
        scene_name = "final_boss";
        pictogramm_y = 18;
        break;
    case 9:
        scene_name = "finalcut";
        pictogramm_y = 18;
        break;
    }
    scene_scr = InitScreensProject(scene_name);
    pictogramm_screens = scene_scr;
    game_cicle_counter = 0;
    scene_cntr = 0;
    scene_music_timer = 0;
    scene_status = 0;
    disable_control = false;
    ClearScreen();


    if (scene_num != 5)
    {
        if (scene_num == 9)
        {
            text_pos = FindText(24);
            titles_x = 4;
            titles_y = 15;
            titles_width = 24;
            titles_height = 8;
            InitMenuMusic(250, false);
        }
        else
        {
            if (scene_num < 5)
            {
                DrawScreen(scene_scr, 0);
            }
            InitMenuMusic(254, true);
        }
    }
    else
    {
        InitMenuMusic(251, false);
    }
    pressed_key_symbol = 0;
}

void Program::UpdateScene()
{
    if ((interrupt_counter & 3) != 0)
    {
        return;
    }

    bool scene_skip = pressed_key_symbol != 0;
    if (!scene_skip && GetKey(255))
    {
        scene_skip = true;
    }

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------

    //сцена Жаклин
    if (scene_num == 1)
    {

        //вертолёт
        if (scene_status != 0)
        {
            DrawScreen(scene_scr, (scene_cntr & 3) + 13);
        }

        //приближение вертолёта
        if (scene_status == 0)
        {
            DrawScreen(scene_scr, ((scene_cntr >> 1) & 3) + 1);
            if (scene_cntr >= 46)
            {
                DrawScreen(scene_scr, (scene_cntr & 1) + (((scene_cntr - 46) / 6) & 6) + 5);
            }

            if (scene_cntr == 92)
            {
                scene_status++;
                scene_cntr = 255;
                InitSay(0, 17);
            }
        }

        //текст Жаклин
        else if (scene_status == 1)
        {
            if (scene_cntr >= 8)
            {
                UpdateJacquelineSay();
            }
            if (scene_cntr == 184)
            {
                scene_status++;
                scene_cntr = 255;
                InitSay(1, 20);
            }
        }

        //текст Новы
        else if (scene_status == 2)
        {
            if (scene_cntr >= 8)
            {
                UpdateNovaSay();
            }
            if (scene_cntr == 92)
            {
                scene_status++;
                FillAttrRect(0, 16, 32, 7, 0x47);
                DrawScreen(scene_scr, 22);
            }
        }

        if (scene_skip)
        {
            InitSelectLevel();
            return;
        }
    }


    //-------------------------------------------------------------------------------------------------------------------------------------------------------------

    //победа в обычном уровне
    else if (scene_num >= 2 && scene_num < 5)
    {
        //минирование здания
        if (scene_status < 3)
        {
            SetBorder(Color::Black);
            if (scene_cntr == 0)
            {
                DrawScreen(scene_scr, scene_status);
                SetBorder(Color::Blue);
            }
            else if ((scene_status < 2 && scene_cntr == 21) || scene_cntr == 46)
            {
                scene_status++;
                scene_cntr = 255;
            }
            else if (scene_status == 2 && scene_cntr >= 2)
            {
                DrawScreen(scene_scr, 3 + ((scene_cntr >> 1) & 1));
            }
        }

        //Нова говорит
        else if (scene_status == 3)
        {
            if (scene_cntr == 0)
            {
                ClearScreen();
                InitSay(2, 65);
            }
            else if (scene_cntr == 91)
            {
                scene_status++;
                scene_cntr = 255;
            }
            else if (scene_cntr >= 8)
            {
                UpdateNovaSay();
            }
        }
        //побег
        else
        {
            if (scene_cntr == 0)
            {
                DrawScreen(scene_scr, 5);
            }
            else if (scene_cntr < 80)
            {
                DrawScreen(scene_scr, scene_cntr / 2 + 25);
            }
            else if (scene_cntr == 100)
            {
                DrawScreen(scene_scr, 67);
            }
            else if (scene_cntr == 101)
            {
                scene_cntr--;
            }

            scene_status += game_cicle_counter & 1;
            if (scene_status == 25)
            {
                scene_status = 22;
            }
        }

        //взрыв здания и фонари
        if (scene_status >= 9)
        {
            DrawScreen(scene_scr, scene_status);
        }
        if (scene_status >= 5)
        {
            int32_t n = 7;
            switch ((game_cicle_counter >> 1) & 3)
            {
            case 0:
                n = 6;
                break;
            case 2:
                n = 8;
                break;
            }
            DrawScreen(scene_scr, n);
        }

        //ожидание нажатия кнопки
        if (scene_skip)
        {
            SetBorder(Color::Black);
            InitSelectLevel();
            return;
        }
    }

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------

    //интро
    else if (scene_num == 5)
    {
        //едущий мотоцикл
        if (scene_status > 4)
        {
            if (scene_cntr >= 4)
            {
                scene_cntr = 1;
            }
            DrawScreen(scene_scr, scene_cntr + 4);
        }

        //цитата, лого Sanchez crew, лого sincLair, PRESENT
        if (scene_status >= 0 && scene_status < 3)
        {
            if (scene_status == 0 && game_cicle_counter == 30)
            {
                DrawScreen(scene_scr, 16);
            }

            int32_t e = 45;
            if (scene_status == 0)
            {
                e = 135;
            }
            if (game_cicle_counter == e)
            {
                ClearScreen();
            }
            else if (game_cicle_counter == e + 15)
            {
                DrawScreen(scene_scr, scene_status + 13);
                scene_status++;
                game_cicle_counter = 0;
            }

        }
        else if (scene_status == 3)
        {
            if (game_cicle_counter == 70)
            {
                ClearScreen();
            }
            if (game_cicle_counter == 90)
            {
                DrawScreen(scene_scr, 0);
                PrintText(14, 0, 17, 32, 1, 0);
                game_cicle_counter = 0;
                scene_cntr = 0;
                scene_status++;
            }
        }

        //город
        else if (scene_status == 4)
        {
            int32_t n = (game_cicle_counter >> 1) & 3;
            if (n == 3)
            {
                n = 1;
            }
            n++;
            DrawScreen(scene_scr, n);

            if (game_cicle_counter == 70)
            {
                ClearScreen();
                DrawScreen(scene_scr, 4);
                scene_status++;
                scene_cntr = 0;
                game_cicle_counter = 0;
            }
        }

        //диалог Жаклин и Новы
        else if (scene_status >= 5 && scene_status < 11)
        {
            if (game_cicle_counter == 90)
            {
                if ((scene_status & 1) == 1)
                {
                    InitSay(10 + scene_status, 8);
                }
                else
                {
                    InitSay(10 + scene_status, 11);
                }
            }
            if (game_cicle_counter >= 95)
            {
                if ((scene_status & 1) == 1)
                {
                    UpdateJacquelineSay();
                }
                else
                {
                    UpdateNovaSay();
                }
            }

            if (scene_status == 10 && game_cicle_counter == 185)
            {
                scene_status++;
                FillAttrRect(0, 17, 32, 7, 0x47);
                game_cicle_counter = 0;
            }

            int32_t e = 195;
            if (scene_status == 9)
            {
                e = 230;
            }

            if (game_cicle_counter == e)
            {
                scene_status++;
                game_cicle_counter = 89;
            }
        }

        if (scene_skip || (scene_status == 11 && game_cicle_counter == 55))
        {
            game_mode = load_screen_mode;
            ClearScreen();
            MuteAllMusic();
            LoadTexts();
            main_menu_scr = InitScreensProject("main_menu");
            DrawScreen(main_menu_scr, 50);
            InitMenuMusic(7, true);
            pressed_key_symbol = 0;
        }
    }

    //финальный босс
    else if (scene_num >= 6 && scene_num < 9)
    {
        int32_t f = scene_num - 6;
        int32_t n = (game_cicle_counter >> 1) & 3;
        if (n == 3)
        {
            n = 1;
        }
        n = f * 3 + n;
        DrawScreen(scene_scr, n);

        if (scene_cntr == 44)
        {
            if (scene_num == 6)
            {
                InitSay(21, 9);
            }
            else if (scene_num == 8)
            {
                InitSay(23, 12);
            }
            else
            {
                InitText(22, 0, 20, 32, 3, 0x47);
                pictogramm_pos = 14;
            }
        }
        else if (scene_cntr >= 52)
        {
            if (scene_num < 8)
            {
                UpdateJacquelineSay();
            }
            else
            {
                UpdateNovaSay();
            }
        }

        if (scene_cntr == 54)
        {
            scene_cntr = 52;
        }

        if (scene_skip)
        {
            MuteMenuMusic();
            InitFinalBoss(f);
        }
    }

    //финалкат
    else if (scene_num == 9)
    {
        int32_t n = (game_cicle_counter >> 1) & 3;
        if (n == 3)
        {
            n = 1;
        }

        //инициализация
        if (scene_status == 0)
        {
            if (scene_cntr == 0)
            {
                DrawScreen(scene_scr, 6);
                DrawScreen(scene_scr, 8);
            }
            else if (scene_cntr == 31)
            {
                scene_cntr = 0;
                scene_status++;
            }
        }
        //башня гаснет
        else if (scene_status == 1)
        {
            if (scene_cntr < 15)
            {
                DrawScreen(scene_scr, final_explode[scene_cntr] + 7);
            }
            if (scene_cntr == 48)
            {
                scene_cntr = 0;
                scene_status++;
            }
        }
        //мелкие взрывы
        else if (scene_status == 2)
        {
            int32_t c = scene_cntr / 2;
            if (c < 16)
            {
                if (c >= 12)
                {
                    c -= 12;
                }
                DrawScreen(scene_scr, 12 + c);
            }
            else
            {
                DrawScreen(scene_scr, 7);
            }
            if (scene_cntr == 45)
            {
                scene_cntr = 0;
                scene_status++;
            }
        }
        //два больших взрыва
        else if (scene_status == 3 || scene_status == 4)
        {
            int32_t b = (scene_status - 3) * 5;
            int32_t c = scene_cntr / 2;

            if (c < 5)
            {
                DrawScreen(scene_scr, b + c + 24);
            }

            if (scene_status == 4 || c >= 5)
            {
                DrawScreen(scene_scr, 34 + n);
            }

            if (scene_status == 4 && c >= 5)
            {
                DrawScreen(scene_scr, 37 + n);
            }

            if (scene_cntr == b + 23)
            {
                if (scene_status == 4)
                {
                    ClearScreen();
                    DrawScreen(scene_scr, 40);
                }
                scene_cntr = 0;
                scene_status++;
            }
        }
        //Нова бежит по коридору
        else if (scene_status == 5)
        {
            DrawScreen(scene_scr, ((scene_cntr / 2) & 7) + 40);
            if (scene_cntr == 58)
            {
                DrawScreen(scene_scr, 6);
                scene_cntr = 0;
                scene_status++;
            }
        }
        //мега-взрыв
        else if (scene_status == 6)
        {
            if (scene_cntr < 16)
            {
                DrawScreen(scene_scr, 34 + n);
                DrawScreen(scene_scr, 37 + n);
            }
            else if (scene_cntr >= 16 && scene_cntr < 19)
            {
                DrawScreen(scene_scr, 32 + scene_cntr);
            }
            else if (scene_cntr == 21)
            {
                ClearScreen();
            }
            else if (scene_cntr == 105)
            {
                DrawScreen(scene_scr, 51);
                scene_cntr = 0;
                scene_status++;
            }
        }
        //Нова на мотоцикле
        else if (scene_status == 7)
        {
            DrawScreen(scene_scr, 54 + n);

            if (scene_cntr == 48)
            {
                DrawScreen(scene_scr, 52);
            }
            else if (scene_cntr == 50)
            {
                DrawScreen(scene_scr, 53);
            }
            else if (scene_cntr == 58)
            {
                DrawScreen(scene_scr, 57);
                scene_cntr = 0;
                scene_status++;
            }
        }
        //анимация приборной панели
        else if (scene_status == 8)
        {
            if (scene_cntr >= 10 && scene_cntr < 21)
            {
                int32_t b = (scene_cntr - 10) / 2;
                DrawScreen(scene_scr, b + 58);
            }
            else if (scene_cntr >= 38 && scene_cntr < 60)
            {
                DrawScreen(scene_scr, 64 + ((scene_cntr >> 2) & 1));
            }
            else if (scene_cntr == 80)
            {
                DrawScreen(scene_scr, 66);
                scene_cntr = 0;
                scene_status++;
            }
        }
        //Нова уезжает
        else if (scene_status == 9)
        {
            DrawScreen(scene_scr, 54 + n);

            if (scene_cntr == 4)
            {
                DrawScreen(scene_scr, 67);
            }
            else if (scene_cntr >= 10 && scene_cntr < 47)
            {
                int32_t b = (scene_cntr - 10) / 2;
                DrawScreen(scene_scr, b + 68);
            }
            else if (scene_cntr == 47)
            {
                ClearScreen();
                DrawScreen(scene_scr, 87);
                scene_cntr = 0;
                scene_status++;
            }
        }
        //голова Новы сбоку
        else if (scene_status == 10)
        {
            DrawScreen(scene_scr, 87 + (scene_cntr & 3));
            if (scene_cntr == 25)
            {
                ClearScreen();
                DrawScreen(scene_scr, 0);
                DrawScreen(scene_scr, 3);
                scene_cntr = 0;
                scene_status++;
                text_counter = 0;
            }
        }
        //Нова уезжает в закат
        else if (scene_status == 11)
        {
            if (scene_cntr >= 3)
            {
                scene_cntr = 0;
            }
            DrawScreen(scene_scr, scene_cntr);

            DrawScreen(scene_scr, n + 3);

            if ((game_cicle_counter & 1) == 1)
            {
                int32_t p = PrintStringLine();
                text_counter = (text_counter + 1) & 7;
                if (text_counter == 0)
                {
                    text_pos = p;
                }
                ScrollCredits();
            }

            if (texts[text_pos] == 255)
            {
                ClearScreen();
                int32_t tn = 25;
                if (no_suit_run)
                {
                    tn = 86;
                }
                text_pos = FindText(tn);
                titles_x = 7;
                titles_y = 0;
                titles_width = 18;
                titles_height = 24;
                text_counter = 0;
                DrawScreen(scene_scr, 91);
                scene_cntr = 0;
                scene_status++;
            }
        }
        //финальные титры
        else if (scene_status >= 12)
        {
            if (texts[text_pos] != 255)
            {
                if ((game_cicle_counter & 1) == 1)
                {
                    int32_t p = PrintStringLine();
                    text_counter = (text_counter + 1) & 7;
                    if (text_counter == 0)
                    {
                        text_pos = p;
                    }
                    ScrollCredits();
                }
            }
            else if (scene_status == 12 && no_suit_run)
            {
                text_pos = FindText(25);
                scene_status++;
            }
        }

        if (scene_skip && scene_status >= 12)
        {
            last_keys = pressed_keys;
            InitNewGame();
            InitMainMenu(true);
        }
    }

    //-------------------------------------------------------------------------------------------------------------------------------------------------------------

    //if (scene_num != 5 && scene_num != 9 && scene_music_timer ==  495)
    //    MuteAllMusic();
    scene_cntr = (scene_cntr + 1) & 0xff;
    IncGameCicleCounter();
    scene_music_timer++;
    pressed_key_symbol = 0;
}
