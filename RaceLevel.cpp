#include "RaceLevel.h"

void Program::InitRace()
{
    MuteAllMusic();
    switch (current_level)
    {
    case 1:
        trace = trace_1;
        top_name = "top1_";
        break;
    case 2:
        trace = trace_2;
        top_name = "top2_";
        break;
    case 3:
        trace = trace_3;
        top_name = "top3_";
        break;
    case 4:
        trace = trace_4;
        top_name = "top4_";
        break;
    }

    game_mode = race_mode;
    prev_game_mode = race_mode;

    x_home = 0;
    y_home = 0;
    hero_path = 0;

    bike_y_pos = 184;
    bike_y_accel = 0;
    bike_y_offset = 0;
    bike_down_counter = 0;
    bike_undead = 0;

    race_win = false;
    race_lose = false;
    race_exit_timer = 0;
    race_turn_counter = 0;
    turn_direction = false;
    top_x = 0;
    race_pos = 0;
    top_fase = 0;
    trace_pos = 0;
    trace_pause = 0;

    ObjectAnimations.clear();
    LoadAnimations("Race");
    race_imgs = InitScreensProject("race");

    ClearAllObjects();

    ClearScreen();
    DrawScreen(race_imgs, 0);
    for (int32_t i = 0; i < 77; i++)
    {
        ResScaleCol(19 + i, 6);
        ResScaleCol(160 + i, 6);
    }
    hero_life_current = 0;
    hero_path_current = 0;

    hero_object = CreateObject(idNovaBike, 128, bike_y_pos, false, true);
    hero_object->Animations = FindObjectAnimation("Race");
    hero_object->Life = 77;
    InitAnimation(hero_object, "Ride", true);

    DrawScreen(race_imgs, current_level + 2);
    DrawScreen(race_imgs, 7);

    sprite_bottom = 192;
    game_cicle_counter = 0;
    InitGameMusic(15, false);
    race_pause = false;
}

void Program::DrawRaceTop()
{
    if (top_x >= 0)
    {
        DrawScreenSprite(race_imgs, top_name + std::to_string(top_fase), top_x, 2, 0, 0, 32 - top_x, 8);
        DrawScreenSprite(race_imgs, "back_top", 0, 2, 32 - top_x, 0, top_x, 8);
    }
    else
    {
        DrawScreenSprite(race_imgs, top_name + std::to_string(top_fase), 0, 2, -top_x, 0, 32 + top_x, 8);
        DrawScreenSprite(race_imgs, "back_top", 32 + top_x, 2, 0, 0, -top_x, 8);
    }
}

void Program::UpdateRace()
{
    //установка/снятие с паузы
    if (GetKey(Key_Fire + Key_Jump + Key_Select) && !GetLastKey(Key_Fire + Key_Jump + Key_Select))
    {
        InitSFX(sfx_switch);
        race_pause = !race_pause;
        if (race_pause)
        {
            DrawScreen(race_imgs, 106);
            PauseGameMusic();
        }
        else
        {
            ResumeGameMusic();
        }
    }
    if (race_pause)
    {
        return;
    }

    PlayAnimation(hero_object);

    if ((interrupt_counter & 3) != 0)
    {
        return;
    }

    for (int32_t i = 0; i < 2; i++)
    {
        hero_life_current = UpdateBar(hero_life_current, hero_object->Life, 19, 6);
    }
    hero_path_current = UpdateBar(hero_path_current, hero_path, 160, 6);

    race_pos++;
    hero_path = race_pos / 16;

    //мигание красной лампочки при низком уровне жизни
    int32_t alert = 1;
    if (hero_object->Life != 0 && hero_object->Life < 15 && (race_pos & 2) == 0)
    {
        alert++;
    }
    DrawScreen(race_imgs, alert);

    if (race_turn_counter != 0)
    {
        race_turn_counter--;
    }

    //прорисовка трассы
    if (race_turn_counter == 0)
    {
        DrawScreen(race_imgs, 7 + game_cicle_counter);
    }
    else
    {
        if (turn_direction)
        {
            DrawScreen(race_imgs, 10 + turn_faze[turn_faze.size() - race_turn_counter]);
            top_x--;
            hero_object->X += -8;
            hero_object->Direction = false;
        }
        else
        {
            DrawScreen(race_imgs, 22 + turn_faze[turn_faze.size() - race_turn_counter]);
            top_x++;
            hero_object->X += 8;
            hero_object->Direction = true;
        }

        //прорисовка верха
        DrawRaceTop();
    }

    game_cicle_counter++;
    if (game_cicle_counter == 3)
    {
        game_cicle_counter = 0;
    }

    //спавним объект
    if (game_cicle_counter == 0 && race_turn_counter == 0)
    {
        int32_t t = trace[trace_pos];
        if (t != 0 && trace_pause == 0)
        {
            //пауза
            if ((t & t_pause) != 0)
            {
                trace_pause = t & 0x7f;
            }

            //повороты
            else if ((t & (t_turn_left + t_turn_right)) != 0)
            {
                if (top_x != 0)
                {
                    top_fase = race_pos / 420;
                }
                race_turn_counter = turn_faze.size();
                if ((t & t_turn_left) != 0)
                {
                    turn_direction = false;
                }
                else
                {
                    turn_direction = true;
                }
                trace_pause = 12;
            }
            //блоки и трамплины
            else if ((t & (t_left + t_right + t_center)) != 0)
            {
                int32_t i = 0;
                while (race_objects[i] != 0)
                {
                    i += 2;
                }
                race_objects[i] = t;
                race_objects[i + 1] = -12;
                trace_pause = 7;
            }

            trace_pos++;
        }
    }
    if (trace_pause != 0)
    {
        trace_pause--;
    }

    //обработка объектов
    for (int32_t i = 0; i < 32; i += 2)
    {
        race_objects[i + 1]++;
        if (race_objects[i + 1] == 12)
        {
            race_objects[i] = 0;
        }
    }

    //вывод объектов
    int32_t o = 30;
    while (o >= 0)
    {
        if (race_objects[o] != 0)
        {
            int32_t obst = race_objects[o];
            int32_t dist = race_objects[o + 1];

            if (dist < 0)
            {
                if (game_cicle_counter != 0 && (obst & t_tramplin) == 0)
                {
                    obst = 0;
                }
                dist = 0;
            }

            if (obst != 0)
            {
                int32_t s = 34;
                if ((obst & t_tramplin) != 0)
                {
                    s = 70;
                }

                if ((obst & t_left) != 0)
                {
                    DrawScreen(race_imgs, s + 0 + dist * 3);
                }
                if ((obst & t_right) != 0)
                {
                    DrawScreen(race_imgs, s + 2 + dist * 3);
                }
                if ((obst & t_center) != 0)
                {
                    DrawScreen(race_imgs, s + 1 + dist * 3);
                }

                //взаимодействие элементов дороги с мотоциклом
                if (dist == 11 && hero_object->Life != 0 && bike_y_offset == 0 && bike_y_pos >= 184 && bike_y_pos < 192)
                {
                    int32_t pos = 4;
                    if (hero_object->X >= 81 && hero_object->X < 175)
                    {
                        pos = 2;
                    }
                    if (hero_object->X >= 176)
                    {
                        pos = 1;
                    }

                    if ((obst & pos) != 0)
                    {
                        //трамплины
                        if ((obst & t_tramplin) != 0)
                        {
                            bike_y_accel = -7;
                            InitAnimation(hero_object, "Jump", false);
                            hero_object->NoInterruptAnim = true;
                            if (hero_object->Life >= 78)
                            {
                                hero_object->Life = 77;
                            }
                            InitSFX(sfx_race_jump);
                        }

                        //бетонные блоки
                        else if (bike_undead == 0)
                        {
                            bike_down_counter = 3;
                            DecLife(hero_object, 25);
                            InitSFX(sfx_race_block_hit);
                        }
                    }
                }
            }
        }
        o -= 2;
    }

    //управление Новой
    if (hero_object->Life != 0 && !race_win && !race_lose)
    {
        std::string a = "Ride";
        if (GetKey(Key_Left))
        {
            hero_object->X += -8;
            if (hero_object->Y >= bike_y_pos)
            {
                a = "Turn";
            }
            hero_object->Direction = true;
        }

        if (GetKey(Key_Right))
        {
            hero_object->X += 8;
            if (hero_object->Y >= bike_y_pos)
            {
                a = "Turn";
            }
            hero_object->Direction = false;
        }

        if (hero_object->X < 32 || hero_object->X >= 225)
        {
            if (hero_object->X < 32)
            {
                hero_object->X = 32;
            }
            if (hero_object->X >= 225)
            {
                hero_object->X = 224;
            }
            if (bike_undead == 0)
            {
                DecLife(hero_object, 3);
                if (hero_object->Life == 0)
                {
                    bike_down_counter = 3;
                }
                a = "Damage";
                InitSFX(sfx_race_wall_hit);
            }
        }

        if (!hero_object->NoInterruptAnim)
        {
            InitAnimation(hero_object, a, false);
        }
    }

    //Нова уезжает в закат
    if (race_win)
    {
        std::string a = "Ride";
        if (race_pos >= 1240)
        {
            a = "Burn";
        }
        if (hero_object->X < 123)
        {
            hero_object->X += 8;
            hero_object->Direction = false;
            a = "Turn";
        }
        if (hero_object->X >= 134)
        {
            hero_object->X += -8;
            hero_object->Direction = true;
            a = "Turn";
        }

        InitAnimation(hero_object, a, false);
    }

    //гравитация Новы
    bike_y_accel++;
    int32_t last = bike_y_offset;
    bike_y_offset -= (bike_y_accel * 2);

    if (bike_y_offset < 0)
    {
        bike_y_offset = 0;
        bike_y_accel = 0;
    }
    hero_object->Y = bike_y_pos - bike_y_offset;
    if (last != 0 && bike_y_offset == 0)
    {
        InitSFX(sfx_race_down);
    }

    //откат вниз
    if (bike_down_counter != 0)
    {
        bike_down_counter--;
        bike_y_pos += 32;
        bike_undead = 30;
    }
    else if (bike_y_pos >= 192 && hero_object->Life != 0)
    {
        bike_y_pos -= 8;
    }

    //гонка проигранна
    if (race_exit_timer == 0 && hero_object->Life == 0)
    {
        race_lose = true;
        race_exit_timer = 30;
    }

    //гонка пройдена
    if (race_pos == 1210 && hero_object->Life != 0)
    {
        race_win = true;
        race_exit_timer = 90;
    }

    //выход из гонки
    if (race_exit_timer != 0)
    {
        race_exit_timer--;
        if (race_exit_timer == 0)
        {
            if (!race_win)
            {
                InitGameOver();
            }
            else
            {
                start_life = hero_object->Life;
                current_location = 1;
                reverse_way = false;
                InitPlatforming(false);
            }
            return;
        }
    }

    if (bike_undead != 0)
    {
        bike_undead--;
    }

    if (race_pos == 1300)
    {
        MuteAllMusic();
    }

    if (bike_undead == 0 || game_cicle_counter == 0)
    {
        DrawGameObject(hero_object);
    }

    //выход в меню
    if (GetKey(Key_Pause))
    {
        PauseGameMusic();
        if (debug_mode)
        {
            InitDebugMenu();
        }
        else
        {
            InitMainMenu(true);
        }
    }
}

void Program::DecLife(const std::shared_ptr<GameObject> &obj, int32_t value)
{
    if (immortal_mode)
    {
        return;
    }
    obj->Life -= value;
    if (obj->Life < 0)
    {
        obj->Life = 0;
    }
}
