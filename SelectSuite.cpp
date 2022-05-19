#include "SelectSuite.h"

void Program::InitSuit()
{
    prev_suit = current_suit;
    game_mode = suit_mode;
    ShowSelectMenu();
    PauseGameMusic();
}

void Program::UpdateSuit()
{
    if (hero_energy != 0)
    {
        if (GetKey(Key_Right) && !GetLastKey(Key_Right))
        {
            current_suit++;
            SelectTest(1);
        }
        else if (GetKey(Key_Left) && !GetLastKey(Key_Left))
        {
            current_suit--;
            SelectTest(-1);
        }
        else if (GetKey(Key_Down) && !GetLastKey(Key_Down))
        {
            current_suit += 2;
            SelectTest(1);
        }
        else if (GetKey(Key_Up) && !GetLastKey(Key_Up))
        {
            current_suit -= 2;
            SelectTest(-1);
        }
    }

    if (GetKey(Key_Fire + Key_Jump + Key_Select) && !GetLastKey(Key_Fire + Key_Jump + Key_Select))
    {
        if (prev_suit != current_suit)
        {
            InitSFX(sfx_start);
        }
        else
        {
            InitSFX(sfx_switch);
        }
        SwitchSuite(false);
    }

    ShowSelectMenu();
}

void Program::ShowSelectMenu()
{
    DrawScreen(select_menu, 10);
    if (current_suit == 0)
    {
        DrawScreen(select_menu, 9);
    }
    else
    {
        DrawScreen(select_menu, 8);
    }

    for (int32_t i = 0; i < 4; i++)
    {
        if (have_suit[i])
        {
            if (current_suit == i && (hero_energy != 0 || i == 0))
            {
                DrawScreen(select_menu, i * 2);
            }
            else
            {
                DrawScreen(select_menu, i * 2 + 1);
            }
        }
    }
}

void Program::SelectTest(int32_t delta)
{
    InitSFX(sfx_switch);
    current_suit &= 3;
    for (int32_t i = 0; i < 4; i++)
    {
        if (have_suit[current_suit])
        {
            return;
        }
        else
        {
            current_suit = (current_suit + delta) & 3;
        }
    }
}

void Program::SwitchSuite(bool hard_enable)
{
    //тут должна быть подгрузка спрайтов
    if (prev_suit != current_suit || hard_enable)
    {
        if (!hard_enable && ((prev_suit == 0 && current_suit != 0) || (prev_suit != 0 && current_suit == 0)))
        {
            pause_cnt = 10;
        }
        else
        {
            ResumeGameMusic();
        }

        if (current_suit == 0)
        {
            hero_object->Animations = FindObjectAnimation("Nova");
        }
        else
        {
            hero_object->Animations = FindObjectAnimation("Suit");
        }

        on_roof = false;
        on_wall = false;
        is_fly  = false;
        is_jump = false;
        hero_object->haveGravity = true;

        hero_object->NoInterruptAnim = false;
        hero_object->YAccel = 0;
        InitAnimation(hero_object, "Nova_Idle", true);

        for (const auto &obj : actual_objects)
        {
            if (obj->Name == idBumerang || obj->Name == idWave || obj->Name == idDust)
            {
                RemoveObject(obj);
            }
        }
    }
    else
    {
        ResumeGameMusic();
    }
    FullRoomRedraw();
    game_mode = platforming_mode;
    InitIcon(im_none);
}