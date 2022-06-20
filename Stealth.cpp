void Program::InitStealth()
{
    current_music = 255;

    game_mode = stealth_mode;
    prev_game_mode = stealth_mode;

    sprite_bottom = 160;

    MuteAllMusic();
    ClearScreen();
    ClearActualObjectsList();
    statusbar = InitScreensProject("j_bar");

    for (int32_t i = 0; i < stealth_flags.size(); i++)
    {
        stealth_flags[i] = false;
    }

    //инициализация статусбара
    InitJIcon(im_noise);
    InitStelthStatusbar();
    hero_life = 77;
    hero_energy = 77;
    hero_weapon = 77;
    hero_path = 0;

    start_slot = 0;
    LoadLocationProject(35);

    alarm_on = false;
    init_alarm = false;
    alarm_cntr = 0;

    ObjectAnimations.clear();
    LoadAnimations("Jacqueline");

    hero_object = CreateObject(idJacqueline, 0, 0, false, true);
    hero_object->Animations = FindObjectAnimation("Jacqueline");
    InitAnimation(hero_object, "J_Idle0", true);
    hero_object->Priority = normal_priority;
    lift_moves = 0;
    next_lift_num = 1;
    j_game_over = false;
    j_win = false;
    hero_invisible = false;
    InitRoom(true);
    stealth_pause = false;
}

bool Program::GetStealth(int32_t num)
{
    return stealth_flags[num - 1];
}

void Program::SetStealth(int32_t num)
{
    stealth_flags[num - 1] = true;
}

void Program::InitStelthStatusbar()
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

void Program::UpdateStealth()
{
    //установка/снятие с паузы
    if (GetKey(Key_Jump) && !GetLastKey(Key_Jump))
    {
        InitSFX(sfx_switch);
        stealth_pause = !stealth_pause;
        if (stealth_pause)
        {
            DrawScreen(statusbar, 10);
            PauseGameMusic();
        }
        else
        {
            ResumeGameMusic();
        }
        FullRoomRedraw();
    }
    if (stealth_pause)
    {
        return;
    }

    //включение сирены
    if (init_alarm && !alarm_on)
    {
        bool f = false;
        for (const auto &obj : actual_objects)
        {
            if (obj->Name == 0)
            {
                break;
            }
            if (obj->Name == idBullet)
            {
                f = true;
                break;
            }
        }
        if (!f && !hero_object->NoInterruptAnim)
        {
            alarm_on = true;
            init_alarm = false;
            alarm_cntr = 200;
            current_music = 13;
            InitGameMusic(current_music, true);
        }
    }

    if (alarm_cntr != 0)
    {
        alarm_cntr--;
        if (alarm_cntr == 0)
        {
            current_music = 14;
            InitGameMusic(current_music, true);
        }
    }


    //скроллирование экрана
    if (scroll_cntr != 0)
    {
        ScrollRoom();
        return;
    }

    if (lift_moves != 0 && !lift_object->AnimationPlayed)
    {
        //вверх
        if (lift_moves >= 129)
        {
            lift_moves++;
            if (lift_moves == 256)
            {
                lift_moves = 0;
            }
            screen_copy->Blit(*screen, Point(0, 0));
            current_xy_room -= 16;
            scroll_direction = 1;
            scroll_cntr = 8;
            InitRoom(true);
        }
        //вниз
        else
        {
            lift_moves--;
            screen_copy->Blit(*screen, Point(0, 0));
            current_xy_room += 16;
            scroll_direction = 3;
            scroll_cntr = 8;
            InitRoom(true);
        }

        //окончание движения лифта
        if (lift_moves == 0)
        {
            //находим объект лифта
            for (const auto &obj : actual_objects)
            {
                if (obj->Name == 0)
                {
                    break;
                }
                if (obj->Name == idJLift)
                {
                    StealthSpawn(obj);
                    std::string anim = "JLift_FinishUp";
                    if (lift_object->Counter < 128)
                    {
                        anim = "JLift_FinishDown";
                    }
                    InitJAnimation(obj, anim, true);
                    break;
                }
            }
        }
    }
    else
    {
        NeedScrollRoom();
    }

    for (const auto &obj : actual_objects)
    {
        if (obj->Name == 0)
        {
            break;
        }
        if (obj->NoActivated)
        {
            StealthSpawn(obj);
        }
        else
        {
            if (!obj->NoInterruptAnim || obj->Name == idJacqueline)
            {
                switch (obj->Name)
                {
                case idJacqueline:
                    Jacqueline(obj);
                    break;
                case idJLift:
                    JLift(obj);
                    break;
                case idJDoor:
                    JDoor(obj);
                    break;
                case idJTerminal:
                    JTerminal(obj);
                    break;
                case idBullet:
                    JBullet(obj);
                    break;
                case idJPolice1:
                case idJPolice2:
                case idJPolice3:
                    JPolice(obj);
                    break;
                case idJOffice1:
                case idJOffice2:
                case idJOffice3:
                    JOffice(obj);
                    break;
                }
            }
            PlayAnimation(obj);
        }
    }
    DrawRoom();
    DrawGameObjects();

    if (scroll_cntr != 0)
    {
        scroll_screen->Blit(*screen, Point(0, 0));
        screen->Blit(*screen_copy, Point(0, 0));
    }

    IncGameCicleCounter();

    //обновление статус-бара
    UpdateJIcon();
    hero_life_current = UpdateBar(hero_life_current, hero_life, 19, 166);
    hero_weapon_current = UpdateBar(hero_weapon_current, hero_weapon, 19, 182);
    hero_path_current = UpdateBar(hero_path_current, hero_path, 160, 166);
    hero_energy_current = UpdateBar(hero_energy_current, hero_energy, 160, 182);

    //смерть Жаклин
    if (j_game_over && !hero_object->AnimationPlayed)
    {
        InitGameOver();
    }

    //уровень пройден
    if (j_win && game_cicle_counter >= 64)
    {
        levels_complete |= 8;
        InitScene(1);
    }

    //выход в меню
    if (GetKey(Key_Pause) && !GetLastKey(Key_Pause))
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

    if (start_stealth_music != 0)
    {
        start_stealth_music--;
        if (start_stealth_music == 0)
        {
            current_music = 12;
            InitGameMusic(current_music, true);
        }
    }
}

void Program::Jacqueline(const std::shared_ptr<GameObject> &obj)
{
    if (j_skip_cicle)
    {
        j_skip_cicle = false;
        return;
    }

    //завершение уровня
    if (current_xy_room == 0x01)
    {
        if (obj->X < 384)
        {
            pressed_keys = Key_Right;

        }
        else
        {
            pressed_keys = 0;
            if (!j_win)
            {
                game_cicle_counter = 0;
                j_win = true;
            }
        }
    }

    hero_moved = false;

    //шкала невидимости
    if (hero_invisible)
    {
        if ((game_cicle_counter & 31) == 0)
        {
            if (hero_energy != 0)
            {
                hero_energy--;
                if (hero_energy == 0)
                {
                    hero_invisible = false;
                    if (!obj->NoVisible)
                    {
                        InitJAnimation(obj, "J_Invisible", true);
                        obj->NoInterruptAnim = true;
                        InitSFX(sfx_stealth);
                    }
                    return;
                }
                else if (hero_energy < 16 && (game_cicle_counter & 63) == 0)
                {
                    InitSFX(sfx_lowpower);
                }
            }
        }
    }

    if ((game_cicle_counter & 127) == 0)
    {
        if (hero_energy < 77 && !hero_invisible)
        {
            hero_energy++;
        }
        if (hero_weapon < 77)
        {
            hero_weapon++;
        }
    }

    //разворот, кроме мёртвой
    if (hero_life != 0)
    {
        if (GetKey(Key_Right))
        {
            obj->Direction = false;
        }
        if (GetKey(Key_Left))
        {
            obj->Direction = true;
        }
    }

    if (obj->NoVisible || obj->NoInterruptAnim)
    {
        return;
    }

    std::string anim = "JIdle";
    bool hard_anim = false;

    if (GetKey(Key_Fire) && !GetLastKey(Key_Fire) && hero_weapon >= 12)
    {
        anim = "JShoot";
        obj->NoInterruptAnim = true;
        hard_anim = true;
    }
    else if (GetKey(Key_Left + Key_Right))
    {
        obj->Direction = false;
        if (GetKey(Key_Left))
        {
            obj->Direction = true;
        }
        if (MoveObjectForward(obj, 3))
        {
            anim = "JRun";
            hero_moved = true;
        }
    }

    if (GetKey(Key_Select) && !GetLastKey(Key_Select))
    {
        if ((!hero_invisible && hero_energy != 0) || (hero_invisible))
        {
            hero_invisible = !hero_invisible;
            anim = "J_Invisible";
            obj->NoInterruptAnim = true;
            InitSFX(sfx_stealth);
        }
    }

    InitJAnimation(obj, anim, hard_anim);
}

void Program::JPolice(const std::shared_ptr<GameObject> &obj)
{
    if (obj->Status == 255)
    {
        return;
    }

    std::string anim = "Police1_Idle";
    int32_t d = 32;
    if (hero_moved && (hero_object->X < obj->X && !hero_object->Direction || hero_object->X >= obj->X && hero_object->Direction))
    {
        d = 56;
    }

    if (obj->Name == idJPolice2)
    {
        anim = "Police2_Idle";
        d = 80;
    }
    if (obj->Name == idJPolice3)
    {
        anim = "Police3_Idle";
        d = 80;
    }
    bool hard_anim = false;

    //атака Жаклин
    if (alarm_on && !hero_invisible && obj->Y == hero_object->Y && SeeOnHero(obj) && GetXDistance(obj) < d && InCurrentRoom(obj) && hero_life != 0 && !hero_object->NoVisible && obj->Status == 1)
    {
        anim = "Police1_Attack";
        if (obj->Name == idJPolice2)
        {
            anim = "Police2_Attack";
        }
        if (obj->Name == idJPolice3)
        {
            anim = "Police3_Attack";
        }
        hard_anim = true;
        obj->NoInterruptAnim = true;
        JOfficePanic();
    }
    else
    {

        //статус - охрана
        if (alarm_on && obj->Status == 0)
        {
            //заметил Жаклин, проверяем что между полицейским и Жаклин нет офисного работника
            if (!hero_invisible && hero_object->Y == obj->Y && (SeeOnHero(obj) || obj->Name == idJPolice3) && hero_life != 0 && InCurrentRoom(obj) && !hero_object->NoVisible && !JCover(obj))
            {
                if (obj->Name == idJPolice3)
                {
                    TurnObject(obj);
                    InitSFX(sfx_droid);
                }
                obj->Status++;
                JOfficePanic();
            }
        }

        //статус - преследование
        else if (obj->Status == 1)
        {
            if (hero_life != 0)
            {
                if (MoveObjectForward(obj, 3))
                {
                    anim = "Police1_Walk";
                    if (obj->Name == idJPolice2)
                    {
                        anim = "Police2_Walk";
                    }
                    if (obj->Name == idJPolice3)
                    {
                        anim = "Police3_Walk";
                    }
                }
                else
                {
                    ChangeDirection(obj);
                }
            }
        }
    }

    InitAnimation(obj, anim, hard_anim);
}

void Program::JOffice(const std::shared_ptr<GameObject> &obj)
{
    if (obj->Status == 255)
    {
        return;
    }

    std::string anim = "Office1_Idle";
    if (obj->Name == idJOffice2)
    {
        anim = "Office2_Idle";
    }
    if (obj->Name == idJOffice3)
    {
        anim = "Office3_Idle";
    }
    bool hard_anim = false;

    //движение по направлению
    if (obj->Status == 1)
    {
        if (MoveObjectForward(obj, 3))
        {
            anim = "Office1_Walk";
            if (obj->Name == idJOffice2)
            {
                anim = "Office2_Walk";
            }
            if (obj->Name == idJOffice3)
            {
                anim = "Office3_Walk";
            }
        }
        else
        {
            ChangeDirection(obj);
        }
    }

    //паника
    else if (obj->Status == 2)
    {
        anim = "Office1_Fear";
        if (obj->Name == idJOffice2)
        {
            anim = "Office2_Fear";
        }
        if (obj->Name == idJOffice3)
        {
            anim = "Office3_Fear";
        }
        if (!InCurrentRoom(obj))
        {
            obj->Status = 1;
        }
    }

    InitAnimation(obj, anim, hard_anim);
}

void Program::JBullet(const std::shared_ptr<GameObject> &obj)
{
    if (obj->Counter != 0)
    {
        obj->Counter--;
    }
    if (!MoveObjectForward(obj, 8) || obj->Counter == 0 || !InCurrentRoom(obj))
    {
        RemoveObject(obj);
    }

    for (const auto &o : actual_objects)
    {
        if (obj->Name == 0)
        {
            break;
        }
        if (o != obj && std::abs(obj->Y - o->Y) < 64 && std::abs(obj->X - o->X) < 10 && !(o->Name == idJacqueline && !obj->isDamageable))
        {
            if (JDamage(o))
            {
                RemoveObject(obj);
                break;
            }
        }
    }
}

void Program::JLift(const std::shared_ptr<GameObject> &obj)
{
    if (lift_pause != 0)
    {
        lift_pause--;
        if (lift_pause == 0)
        {
            InitJAnimation(obj, "JLift_FinishUp", true);
        }
    }

    if (obj->Counter == 0)
    {
        return;
    }

    int32_t t = 6;

    if (obj->Status == next_lift_num && GetStealth(obj->Status))
    {
        if ((game_cicle_counter & 8) != 0)
        {
            t = 7;
        }
    }
    else if (GetStealth(obj->Status))
    {
        t = 7;
    }

    NewTile(obj->XTile, obj->YTile - 3, t);

    if (!GetStealth(obj->Status))
    {
        return;
    }

    if (lift_moves == 0 && !hero_object->NoVisible)
    {
        if (GetKey(Key_Up))
        {
            int32_t dist = GetXDistance(obj);
            if (dist < 16)
            {
                if (dist >= 2)
                {
                    ObjCentrum(obj, 0);
                    Jacqueline(hero_object);
                    j_skip_cicle = true;
                }
                else
                {
                    hero_object->NoVisible = true;
                    lift_moves = obj->Counter;
                    lift_object = obj;
                    std::string anim = "JLift_StartUp";
                    if (obj->Counter < 128)
                    {
                        anim = "JLift_StartDown";
                    }
                    InitJAnimation(obj, anim, true);

                    if (next_lift_num == obj->Status)
                    {
                        next_lift_num++;
                        hero_path += 3 + (next_lift_num & 1);
                        if (hero_path >= 78)
                        {
                            hero_path = 77;
                        }
                    }
                }
            }
        }
    }
}

void Program::JDoor(const std::shared_ptr<GameObject> &obj)
{
    if (GetKey(Key_Up))
    {
        if (!hero_object->NoVisible && !hero_object->NoInterruptAnim)
        {
            int32_t d = GetXDistance(obj);
            if (d < 16)
            {
                if (d >= 2)
                {
                    ObjCentrum(obj, 0);
                    Jacqueline(hero_object);
                    j_skip_cicle = true;
                }
                else
                {
                    hero_object->X = obj->X;
                    hero_object->NoInterruptAnim = true;
                    if (obj->Counter != 0 && (obj->Counter & 16) == 0)
                    {
                        InitJAnimation(hero_object, "JHack", false);
                    }
                    else
                    {
                        InitJAnimation(obj, "JDoor_Open", true);
                        hero_object->NoVisible = true;
                        terminal_num = obj->Status;
                        current_door = obj;
                    }
                }
            }
        }
    }
}

std::shared_ptr<Program::GameObject> Program::FindDoor()
{
    for (const auto &obj : actual_objects)
    {
        if (obj->Name == 0)
        {
            break;
        }
        if (obj->Name == idJDoor)
        {
            return obj;
        }
    }
    return nullptr;
}

void Program::JTerminal(const std::shared_ptr<GameObject> &obj)
{
    if (terminal_num == 0)
    {
        return;
    }

    int32_t t = 2;
    int32_t d = std::abs(hero_object->X - (obj->X + 8));

    if (d >= 41)
    {
        if ((game_cicle_counter & 8) != 0)
        {
            t = 4;
        }
    }
    else
    {
        if ((game_cicle_counter & 2) != 0)
        {
            t = 1;
        }

        if (GetKey(Key_Up) && d < 16)
        {
            if (d >= 2)
            {
                ObjCentrum(obj, 8);
                Jacqueline(hero_object);
                j_skip_cicle = true;
            }
            else
            {
                hero_object->NoInterruptAnim = true;
                InitJAnimation(hero_object, "J_Terminal", true);
                if (terminal_num != 0)
                {
                    SetStealth(terminal_num);
                }
                t = 2;
                terminal_num = 0;
                current_door->Status = 0;
                hero_path += 3;

                if (!alarm_on)
                {
                    init_alarm = true;
                }
            }
        }
    }

    for (int32_t i = 0; i < 2; i++)
    {
        NewTile(obj->XTile + i, obj->YTile - 2, t);
        if (t != 1)
        {
            t++;
        }
    }
}

void Program::InitJAnimation(const std::shared_ptr<GameObject> &obj, const std::string &anim, bool hard)
{
    std::string animationName(anim);

    if (!hero_invisible)
    {
        animationName += "_0";
    }
    else
    {
        animationName += "_1";
    }
    InitAnimation(obj, anim, hard);
}

void Program::StealthSpawn(const std::shared_ptr<GameObject> &obj)
{
    if (obj->Name != 0 && obj->XYRoom == current_xy_room)
    {
        std::string anim;
        obj->Fixed = false;
        obj->NoActivated = false;
        obj->NoInterruptAnim = false;
        obj->Animations = FindObjectAnimation("Jacqueline");
        obj->Life = 1;
        switch (obj->Name)
        {
        case idJLift:
            anim = "JLift";
            obj->Fixed = true;
            JLift(obj);
            break;
        case idJDoor:
            anim = "JDoor";
            obj->Fixed = true;
            break;
        case idJTerminal:
            obj->Fixed = true;
            obj->NoVisible = true;
            break;
        case idJPolice1:
            obj->Life = 2;
            anim = "Police1_Idle";
            if (obj->Status == 255)
            {
                anim = "Police1_Dead";
                obj->Fixed = true;
            }
            obj->Priority = high_priority;
            break;
        case idJPolice2:
            obj->Life = 2;
            anim = "Police2_Idle";
            if (obj->Status == 255)
            {
                anim = "Police2_Dead";
                obj->Fixed = true;
            }
            obj->Priority = high_priority;
            break;
        case idJPolice3:
            obj->Life = 3;
            anim = "Police3_Idle";
            if (obj->Status == 255)
            {
                anim = "Police3_Dead";
                obj->Fixed = true;
            }
            obj->Priority = high_priority;
            break;
        case idJOffice1:
            anim = "Office1_Idle";
            if (obj->Status == 255)
            {
                anim = "Office1_Dead";
                obj->Fixed = true;
            }
            obj->Priority = high_priority;
            break;
        case idJOffice2:
            anim = "Office2_Idle";
            if (obj->Status == 255)
            {
                anim = "Office2_Dead";
                obj->Fixed = true;
            }
            obj->Priority = high_priority;
            break;
        case idJOffice3:
            anim = "Office3_Idle";
            if (obj->Status == 255)
            {
                anim = "Office3_Dead";
                obj->Fixed = true;
            }
            obj->Priority = high_priority;
            break;
        }
        InitAnimation(obj, anim, true);
    }
}

bool Program::JDamage(const std::shared_ptr<GameObject> &obj)
{
    //если это Жаклин
    if (obj->Name == idJacqueline && hero_life != 0 && !hero_object->NoVisible)
    {
        std::string anim = "J_Damage";
        if (!immortal_mode)
        {
            hero_life -= 9;
        }
        if (hero_life < 1)
        {
            hero_life = 0;
            obj->NoInterruptAnim = true;
            anim = "J_Die";
            j_game_over = true;
            InitJIcon(im_noise);
        }
        else
        {
            InitJIcon(im_damage);
        }

        hero_object->NoInterruptAnim = true;
        InitAnimation(hero_object, anim, true);
        InitSFX(sfx_shocker);
        return true;
    }

    //если это охрана и офисные работники
    else if ((obj->Name == idJPolice1 || obj->Name == idJPolice2 || obj->Name == idJPolice3 || obj->Name == idJOffice1 || obj->Name == idJOffice2 || obj->Name == idJOffice3) && obj->Status != 255)
    {
        obj->Status = 255;
        obj->Life--;
        std::string anim;
        switch (obj->Name)
        {
        case idJPolice1:
            if (obj->Life != 0)
            {
                anim = "Police1_Damage";
            }
            else
            {
                anim = "Police1_Die";
            }
            break;
        case idJPolice2:
            if (obj->Life != 0)
            {
                anim = "Police2_Damage";
            }
            else
            {
                anim = "Police2_Die";
            }
            break;
        case idJPolice3:
            if (obj->Life != 0)
            {
                anim = "Police3_Damage";
            }
            else
            {
                anim = "Police3_Die";
            }
            break;
        case idJOffice1:
            anim = "Office1_Die";
            break;
        case idJOffice2:
            anim = "Office2_Die";
            break;
        case idJOffice3:
            anim = "Office3_Die";
            break;
        }

        if (obj->Life == 0)
        {
            obj->XYRoom = current_xy_room;
            obj->Fixed = true;
        }
        else
        {
            obj->Status = 1;
            obj->NoInterruptAnim = true;
        }

        InitAnimation(obj, anim, true);
        InitSFX(sfx_shocker);
        return true;
    }

    return false;
}

void Program::JOfficePanic()
{
    if (!alarm_on)
    {
        init_alarm = true;
    }

    for (const auto &obj : actual_objects)
    {
        if (obj->Name == 0)
        {
            break;
        }
        if (obj->Status != 255 && hero_object->Y == obj->Y)
        {
            if (obj->Name == idJPolice1 || obj->Name == idJPolice2 || obj->Name == idJPolice3)
            {
                obj->Status = 1;
                TurnObject(obj);
            }

            if (obj->Name == idJOffice1 || obj->Name == idJOffice2 || obj->Name == idJOffice3)
            {
                obj->Status = 2;
                obj->Counter = 255;
            }
        }
    }

}

bool Program::JCover(const std::shared_ptr<GameObject> &obj)
{
    for (const auto &o : actual_objects)
    {
        if (obj->Name == 0)
        {
            break;
        }
        if ((o->Name == idJOffice1 || o->Name == idJOffice2 || o->Name == idJOffice3) && o->Status != 255 && o->Y == obj->Y)
        {
            if ((obj->X < o->X && o->X < hero_object->X) || (hero_object->X < o->X && o->X < obj->X) || GetXDistance(o) < 8)
            {
                return true;
            }
        }
    }
    return false;
}

void Program::InitJIcon(int32_t command)
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

void Program::UpdateJIcon()
{
    icon_timer++;
    if (icon_timer >= 3)
    {
        icon_timer = 0;
        int32_t scr = 4;
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