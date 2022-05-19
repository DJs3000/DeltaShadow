#include "EventsObjects.h"

void Program::DoEvent(const std::shared_ptr<GameObject> &obj, const std::string &e)
{
    //C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string and was converted to C++ 'if-else' logic:
    //		switch (e)
    //ORIGINAL LINE: case "event_safepoint":
    if (e == "event_safepoint")
    {
        Event_safepoint(obj);
    }
    //ORIGINAL LINE: case "event_fraction":
    else if (e == "event_fraction")
    {
        Event_fraction(obj);
    }
    //ORIGINAL LINE: case "event_steam":
    else if (e == "event_steam")
    {
        HeroDamage(obj, 24);
    }
    //ORIGINAL LINE: case "event_door_open":
    else if (e == "event_door_open")
    {
        Event_door_open(obj);
    }
    //ORIGINAL LINE: case "event_door_close":
    else if (e == "event_door_close")
    {
        Event_door_close(obj);
    }
    //ORIGINAL LINE: case "event_tankshoot":
    else if (e == "event_tankshoot")
    {
        Event_tankshoot(obj);
    }
    //ORIGINAL LINE: case "event_gunshoot":
    else if (e == "event_gunshoot")
    {
        Event_gunshoot(obj);
    }
    //ORIGINAL LINE: case "event_dronshoot0":
    else if (e == "event_dronshoot0")
    {
        Event_dronshoot0(obj);
    }
    //ORIGINAL LINE: case "event_dronshoot1":
    else if (e == "event_dronshoot1")
    {
        Event_dronshoot1(obj);
    }
    //ORIGINAL LINE: case "event_show_hero":
    else if (e == "event_show_hero")
    {
        Event_show_hero(obj);
    }
    //ORIGINAL LINE: case "event_jdoor":
    else if (e == "event_jdoor")
    {
        Event_jdoor(obj);
    }
    //ORIGINAL LINE: case "event_jshoot":
    else if (e == "event_jshoot")
    {
        Event_jshoot(obj);
    }
    //ORIGINAL LINE: case "event_obj_remove":
    else if (e == "event_obj_remove")
    {
        RemoveObject(obj);
    }
    //ORIGINAL LINE: case "event_police_attack":
    else if (e == "event_police_attack")
    {
        Event_police_attack(obj);
    }
    //ORIGINAL LINE: case "event_police_shoot":
    else if (e == "event_police_shoot")
    {
        Event_police_shoot(obj);
    }
    //ORIGINAL LINE: case "event_police_seeback":
    else if (e == "event_police_seeback")
    {
        Event_police_seeback(obj);
    }
    //ORIGINAL LINE: case "event_in_door":
    else if (e == "event_in_door")
    {
        Event_in_door(obj);
    }
    //ORIGINAL LINE: case "event_sfx_elevator":
    else if (e == "event_sfx_elevator")
    {
        Event_sfx_elevator();
    }
    //ORIGINAL LINE: case "event_sfx_doors":
    else if (e == "event_sfx_doors")
    {
        Event_sfx_doors();
    }
    //ORIGINAL LINE: case "event_sfx_terminal":
    else if (e == "event_sfx_terminal")
    {
        Event_sfx_terminal();
    }
    //ORIGINAL LINE: case "event_lounchrocket":
    else if (e == "event_lounchrocket")
    {
        Event_lounchrocket(obj);
    }
    //ORIGINAL LINE: case "event_jump":
    else if (e == "event_jump")
    {
        Event_jump(obj, 20);
    }
    //ORIGINAL LINE: case "event_smalljump":
    else if (e == "event_smalljump")
    {
        Event_jump(obj, 13);
    }
    //ORIGINAL LINE: case "event_jelly_shoot":
    else if (e == "event_jelly_shoot")
    {
        Event_jelly_shoot(obj);
    }
    //ORIGINAL LINE: case "event_crab_shoot":
    else if (e == "event_crab_shoot")
    {
        Event_crab_shoot(obj);
    }
    //ORIGINAL LINE: case "event_crab_upshoot":
    else if (e == "event_crab_upshoot")
    {
        Event_crab_upshoot(obj);
    }
    //ORIGINAL LINE: case "event_ray_shot":
    else if (e == "event_ray_shot")
    {
        Event_ray_shot(obj, 255, 24);
    }
    //ORIGINAL LINE: case "event_scream":
    else if (e == "event_scream")
    {
        InitSFX(sfx_dogscream);
        Event_ray_shot(obj, 64, 24);
    }
    //ORIGINAL LINE: case "event_pet_hit":
    else if (e == "event_pet_hit")
    {
        Event_ray_shot(obj, 32, 24);
    }
    //ORIGINAL LINE: case "event_slider_attack":
    else if (e == "event_slider_attack")
    {
        Event_slider_attack(obj);
    }
    //ORIGINAL LINE: case "event_slider_magnit_on":
    else if (e == "event_slider_magnit_on")
    {
        Event_slider_magnit_on();
    }
    //ORIGINAL LINE: case "event_slider_magnit_off":
    else if (e == "event_slider_magnit_off")
    {
        Event_slider_magnit_off();
    }
    //ORIGINAL LINE: case "event_dragonfire":
    else if (e == "event_dragonfire")
    {
        Event_dragonfire(obj);
    }
}

void Program::Event_safepoint(const std::shared_ptr<GameObject> &obj)
{
    if (hero_life != 0)
    {
        current_xy_room = last_safe_xy_room;
        hero_object->X = last_safe_x;
        hero_object->Y = last_safe_y;
        hero_object->Direction = last_safe_direction;
        on_roof = false;
        on_wall = false;
        hero_die = false;
        hero_object->UndeadCounter = 100;
        hero_object->NoInterruptAnim = false;
        hero_object->haveGravity = true;
        InitRoom(false);
        InitIcon(im_none);
    }
}

void Program::Event_fraction(const std::shared_ptr<GameObject> &obj)
{
    CreateFractions(obj, 4);
}

void Program::Event_door_open(const std::shared_ptr<GameObject> &obj)
{
    obj->Priority = static_cast<uint8_t>(2 - obj->Priority);
    if (obj->Priority == 0)
    {
        disable_control = false;
        InitIcon(im_none);
    }
}

void Program::Event_door_close(const std::shared_ptr<GameObject> &obj)
{
    //сохранение показателей героя при входе для хардмода
    if (difficulty != 0)
    {
        start_weapon = hero_weapon_max;
        start_life = hero_life;
        start_energy = hero_energy;
    }

    //следующая локация
    bool b = false;
    if (obj->Status == 0)
    {
        InitGameMusic(level_music, true);
        current_music = level_music;
        return;
    }
    else if (obj->Status == 1)
    {
        int32_t p = 3;
        if (current_level == 4)
        {
            p = 7;
        }
        if (difficulty != 0)
        {
            p++;
        }

        //обычное направление
        if (!reverse_way)
        {
            if (current_location != p)
            {
                if (current_level == 4 && current_location != 7)
                {
                    b = true;
                }
                else
                {
                    current_location++;
                }
            }
            else
            {
                //финальный босс
                if (current_level == 4)
                {
                    last_boss_fase = 0;
                    InitFinalBoss(0);
                    return;
                }
                else
                {
                    b = true;
                }
            }
        }
        //реверсивное направление
        else
        {
            if (current_location == 1)
            {
                if (current_level != 4)
                {
                    LevelComlete();
                }
                else
                {
                    InitNewGame();
                    SaveProgress();
                    InitScene(9);
                }
                return;
            }
            current_location--;
        }
    }

    //дракон-паук
    else if (obj->Status == 2)
    {
        b = true;
    }

    InitLocation(b);
}

void Program::Event_tankshoot(const std::shared_ptr<GameObject> &obj)
{
    if (obj->NoActivated)
    {
        return;
    }
    CreateBullet(obj, "Tankette", "Tankette_Bullet", 20, -20, 4, 0, false);
    InitSFX(sfx_tanketteshoot);
}

void Program::Event_gunshoot(const std::shared_ptr<GameObject> &obj)
{
    if (obj->NoActivated)
    {
        return;
    }
    CreateBullet(obj, "Gun", "Gun_Bullet", 24, -12, 4, 0, true);
    InitSFX(sfx_tanketteshoot);
}

void Program::Event_dronshoot0(const std::shared_ptr<GameObject> &obj)
{
    if (obj->NoActivated)
    {
        return;
    }
    CreateBullet(obj, "Dron", "Dron_Bullet0", 16, 0, 4, 0, false);
    InitSFX(sfx_tanketteshoot);
}

void Program::Event_dronshoot1(const std::shared_ptr<GameObject> &obj)
{
    if (obj->NoActivated)
    {
        return;
    }
    CreateBullet(obj, "Dron", "Dron_Bullet1", 12, 0, 3, 3, false);
    InitSFX(sfx_tanketteshoot);
}

void Program::Event_show_hero(const std::shared_ptr<GameObject> &obj)
{
    hero_object->NoVisible = false;
    hero_object->Direction = false;
    InitJAnimation(hero_object, "JIdle", true);
    InitJIcon(im_none);
    if (obj->Counter == 0)
    {
        start_stealth_music = 2;
    }
}

void Program::Event_jdoor(const std::shared_ptr<GameObject> &obj)
{
    //выход из кабинета
    int32_t cnt = obj->Counter & 15;
    if (cnt == 0)
    {
        current_xy_room = static_cast<uint8_t>(current_xy_room + return_room);
    }
    //вход в кабинет
    else
    {
        return_room = static_cast<uint8_t>(current_xy_room - cnt);
        current_xy_room = static_cast<uint8_t>(cnt);
        obj->Counter = obj->Counter | 16;
    }

    InitRoom(true);

    //находим объект двери
    std::shared_ptr<GameObject> obj2 = FindDoor();
    obj2->Counter = obj2->Counter | 16;
    StealthSpawn(obj2);
    InitJAnimation(obj2, "JDoor_Close", true);
}

void Program::Event_in_door(const std::shared_ptr<GameObject> &obj)
{
    std::shared_ptr<GameObject> obj2 = FindDoor();
    InitJAnimation(obj2, "JDoor_Open", true);
    obj->NoVisible = true;
    terminal_num = obj2->Status;
    current_door = obj2;
}

void Program::Event_jshoot(const std::shared_ptr<GameObject> &obj)
{
    std::shared_ptr<GameObject> o = CreateChild(obj, idBullet, 20, -20);
    o->Animations = FindObjectAnimation("Jacqueline");
    InitAnimation(o, "JBullet", true);
    InitSFX(sfx_stungun);
    o->Counter = 24;
    hero_weapon -= 12;
    if (hero_weapon < 0)
    {
        hero_weapon = 0;
    }
    JOfficePanic();
}

void Program::Event_police_attack(const std::shared_ptr<GameObject> &obj)
{
    for (const auto &o : actual_objects)
    {
        if (obj->Name == 0)
        {
            break;
        }
        if (obj != o && SeeOnObject(obj, o) && std::abs(obj->X - o->X) < 32 && obj->Y == o->Y)
        {
            JDamage(o);
        }
    }
}

void Program::Event_police_shoot(const std::shared_ptr<GameObject> &obj)
{
    std::shared_ptr<GameObject> o = CreateChild(obj, idBullet, 20, -25);
    o->Animations = FindObjectAnimation("Jacqueline");
    InitAnimation(o, "JBullet", true);
    InitSFX(sfx_stungun);
    o->Counter = 24;
    o->isDamageable = true;
}

void Program::Event_police_seeback(const std::shared_ptr<GameObject> &obj)
{
    if (alarm_on && !hero_invisible && hero_object->Y == obj->Y && !SeeOnHero(obj) && hero_life != 0 && InCurrentRoom(obj))
    {
        //проверяем что между полицейским и Жаклин нет офисного работника
        if (!JCover(obj))
        {
            obj->Status++;
            ChangeDirection(obj);
            JOfficePanic();
        }
    }
}

void Program::Event_sfx_elevator()
{
    InitSFX(sfx_elevator);
}

void Program::Event_sfx_doors()
{
    InitSFX(sfx_doors);
}

void Program::Event_sfx_terminal()
{
    InitSFX(sfx_terminal);
}

void Program::Event_lounchrocket(const std::shared_ptr<GameObject> &obj)
{
    std::shared_ptr<GameObject> o = CreateChild(obj, idRocket, -4, -36);
    o->Animations = FindObjectAnimation("Items");
    InitAnimation(o, "Rocket0", true);
    o->XAccel = 0;
    o->YAccel = -3;
    o->Counter = 4;
    o->isDamageable = true;
    o->Fixed = true;
    InitSFX(sfx_rocket);
}

void Program::Event_jump(const std::shared_ptr<GameObject> &obj, int32_t accel)
{
    obj->YAccel = -accel;
    obj->NoInterruptAnim = false;
    if (obj->Name == idSlime)
    {
        InitSFX(sfx_slime);
    }
}

void Program::Event_jelly_shoot(const std::shared_ptr<GameObject> &obj)
{
    CreateBullet(obj, "Jelly", "Jelly_Bomb", 0, -24, 0, -2, false);
    CreateBullet(obj, "Jelly", "Jelly_Bomb", 12, -20, 2, -1, false);
    CreateBullet(obj, "Jelly", "Jelly_Bomb", -12, -20, -2, -1, false);
    InitSFX(sfx_tanketteshoot);
}

void Program::Event_crab_shoot(const std::shared_ptr<GameObject> &obj)
{
    CreateBullet(obj, "CrabBoss", "Crab_Claw", 16, -24, 4, 0, false);
    InitSFX(sfx_rocket);
}

void Program::Event_crab_upshoot(const std::shared_ptr<GameObject> &obj)
{
    CreateBullet(obj, "CrabBoss", "Crab_Claw1", 8, -32, 3, -3, false);
    InitSFX(sfx_rocket);
}

void Program::Event_ray_shot(const std::shared_ptr<GameObject> &obj, int32_t x_distance, int32_t y_distance)
{
    if (hero_object->UndeadCounter == 0 && SeeOnHero(obj) && GetXDistance(obj) < x_distance && std::abs(obj->Y - hero_object->Y) < y_distance)
    {
        if (obj->Name == idFlyBoss)
        {
            CreateExplosion(hero_object, 0, -24);
        }
        DecreaseHeroLife();
    }
    else if (obj->Name == idFlyBoss)
    {
        InitSFX(sfx_explosion);
    }
}

void Program::Event_slider_attack(const std::shared_ptr<GameObject> &obj)
{
    CreateBullet(obj, "AlienSliderman", "Slider_Plasma", 0, 8, 0, 3, true);
    CreateBullet(obj, "AlienSliderman", "Slider_Plasma", 12, 4, 2, 3, true);
    CreateBullet(obj, "AlienSliderman", "Slider_Plasma", -12, 4, -2, 3, true);
    CreateBullet(obj, "AlienSliderman", "Slider_Plasma", 16, 0, 3, 2, true);
    CreateBullet(obj, "AlienSliderman", "Slider_Plasma", -16, 0, -3, 2, true);
    InitSFX(sfx_tanketteshoot);
}

void Program::Event_slider_magnit_on()
{
    on_wall = false;
    on_roof = false;
    is_fly = false;
    hero_object->haveGravity = true;
    boss_magnit_on = true;
}

void Program::Event_slider_magnit_off()
{
    boss_magnit_on = false;
}

void Program::Event_dragonfire(const std::shared_ptr<GameObject> &obj)
{
    CreateBullet(obj, "DLCBoss", "Plasma", 24, -32, 5, 1, false);
    InitSFX(sfx_rocket);
}