#include "DeltaShadow.Program.h"

#include "Environment/PrimaryScreen.h"
#include "Environment/SpecialFolder.h"

#include "Util/File.h"
#include "Util/BinaryStreamReader.h"
#include "Util/BinaryStreamWriter.h"

using namespace SdlDotNetCompat::Core;
using namespace SdlDotNetCompat::Graphics;
using namespace SdlDotNetCompat::Audio;
using namespace SdlDotNetCompat::Input;
using namespace SdlDotNetCompat::Drawing;
using namespace Util;

namespace DeltaShadow
{

template <typename T>
T **AllocateDynamicArray(int nRows, int nCols)
{
    T **array = new T*[nCols];
    for (int i = 0; i < nCols; ++i)
    {
        array[i] = new T[nRows];
    }
    return array;
}

template <typename T>
void FreeDynamicArray(T** array)
{
    delete [] *array;
    delete []  array;
}

void toLower(std::string &str)
{
   for (auto &c : str)
   {
      c = tolower(c);
   }
}

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
    obj->Priority = static_cast<std::uint8_t>(2 - obj->Priority);
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
        std::int32_t p = 3;
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
    std::int32_t cnt = obj->Counter & 15;
    if (cnt == 0)
    {
        current_xy_room = static_cast<std::uint8_t>(current_xy_room + return_room);
    }
    //вход в кабинет
    else
    {
        return_room = static_cast<std::uint8_t>(current_xy_room - cnt);
        current_xy_room = static_cast<std::uint8_t>(cnt);
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

void Program::Event_jump(const std::shared_ptr<GameObject> &obj, std::int32_t accel)
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

void Program::Event_ray_shot(const std::shared_ptr<GameObject> &obj, std::int32_t x_distance, std::int32_t y_distance)
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

std::shared_ptr<Program::GameObject> Program::CreateObject(std::uint8_t name, std::int32_t x, std::int32_t y, bool direction, bool actual_object)
{
    //ищем пустой слот объекта
    for (std::uint32_t i = 0; i < game_objects.size(); i++)
    {
        if (game_objects[i]->Name == 0)
        {
            std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
            obj->Name = name;
            obj->X = x;
            obj->Y = y;
            obj->Direction = direction;
            game_objects[i] = obj;
            if (actual_object)
            {
                AddActualObject(obj);
            }
            return obj;
        }
    }
    return game_objects[127];
}

void Program::RemoveObject(const std::shared_ptr<GameObject> &obj)
{
    RemoveActualObject(obj);
    obj->Name = 0;
}

void Program::ClearAllObjects()
{
    for (size_t i = 0; i < game_objects.size(); i++)
    {
        std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
        obj->Name = 0;
        game_objects[i] = obj;
    }
    ClearActualObjectsList();
    particle_cntr = 0;
}

void Program::ClearActualObjectsList()
{
    for (size_t i = 0; i < actual_objects.size(); i++)
    {
        std::shared_ptr<GameObject> obj = std::make_shared<GameObject>();
        obj->Name = 0;
        actual_objects[i] = obj;
    }
}

void Program::AddActualObject(const std::shared_ptr<GameObject> &obj)
{
    for (size_t i = 0; i < actual_objects.size(); i++)
    {
        if (actual_objects[i]->Name == 0)
        {
            actual_objects[i] = obj;
            break;
        }
    }
}

void Program::RemoveActualObject(const std::shared_ptr<GameObject> &obj)
{
    for (size_t i = 0; i < actual_objects.size(); i++)
    {
        if (actual_objects[i] == obj)
        {
            for (size_t j = i; j < actual_objects.size() - 1; j++)
            {
                if (actual_objects[j]->Name == 0)
                {
                    break;
                }
                actual_objects[j] = actual_objects[j + 1];
            }
            break;
        }
    }
}

std::shared_ptr<Program::GameObject> Program::CreateChild(const std::shared_ptr<Program::GameObject> &obj, std::uint8_t name, std::int32_t xoffset, std::int32_t yoffset)
{
    if (obj->Direction)
    {
        xoffset = -xoffset;
    }
    return CreateObject(name, obj->X + xoffset, obj->Y + yoffset, obj->Direction, true);
}

bool Program::Gravity(const std::shared_ptr<Program::GameObject> &obj)
{
    ga = 0;
    gb = 0;
    if (obj->PlatformObject != nullptr && obj->YAccel >= 0)
    {
        return false;
    }

    std::int32_t v = 24;
    if (GetProperty(obj, 0, -1) == isWater || GetProperty(obj, 0, -18) == isWater)
    {
        v = 6;
    }

    if (v != 6 || (game_cicle_counter & 3) != 0)
    {
        obj->YAccel++;
    }

    if (obj->YAccel >= v)
    {
        obj->YAccel = v;
    }

    std::int32_t ydelta = obj->YAccel / 4;
    obj->Y += ydelta;

    if (obj->YAccel < 0)
    {
        ga = GetProperty(obj, -obj->Width, obj->Height);
        gb = GetProperty(obj, obj->Width, obj->Height);
        if (ga == isFloor || gb == isFloor || ga == isSpike || gb == isSpike)
        {
            obj->Y -= ydelta;
            obj->YAccel = 0;
        }
    }
    else
    {
        ga = GetProperty(obj, -obj->Width, 0);
        gb = GetProperty(obj, obj->Width, 0);
        if ((obj->Y & 0x0f) < 8 && (ga == isFloor || gb == isFloor || ga == isPlatform || gb == isPlatform || (ga == isSpike && gb == isSpike) || ga == isShift || gb == isShift))
        {
            std::int32_t temp_y = obj->Y;
            std::int32_t temp_ya = obj->YAccel;
            obj->Y &= 0xfff0;
            obj->YAccel = 0;

            std::int32_t a = GetProperty(obj, -obj->Width, -1);
            std::int32_t b = GetProperty(obj, obj->Width, -1);
            if (obj->Name == idNova && !hero_die && (a == isFloor || b == isFloor))
            {
                obj->Y = temp_y;
                obj->YAccel = temp_ya;

                if (a == isFloor && b != isFloor)
                {
                    MoveObjectForward(obj, 3);
                }
                if (a != isFloor && b == isFloor)
                {
                    MoveObjectForward(obj, -3);
                }

                return true;
            }

            if (ga == isShift || gb == isShift)
            {
                a = GetFullProperty(obj, -obj->Width, 0) & 0xf0;
                b = GetFullProperty(obj, obj->Width, 0) & 0xf0;

                //сдвиг на транспортёре вправо
                if (a == 0xe0 || b == 0xe0)
                {
                    ga = (GetFullProperty(obj, obj->Width + 1, obj->Height) >> 5) & 7;
                    gb = (GetFullProperty(obj, obj->Width + 1, -1) >> 5) & 7;
                    if (ga != isFloor && gb != isFloor)
                    {
                        obj->X++;
                    }
                    gb = ga;
                }

                //сдвиг на транспортёре влево
                if (a == 0xf0 || b == 0xf0)
                {
                    ga = (GetFullProperty(obj, -obj->Width - 1, obj->Height) >> 5) & 7;
                    gb = (GetFullProperty(obj, -obj->Width - 1, -1) >> 5) & 7;
                    if (ga != isFloor && gb != isFloor)
                    {
                        obj->X--;
                    }
                    gb = ga;
                }
            }
            return false;
        }
    }
    return true;
}

void Program::ChangeDirection(const std::shared_ptr<Program::GameObject> &obj)
{
    obj->Direction = !obj->Direction;
}

bool Program::MoveObjectForward(const std::shared_ptr<Program::GameObject> &obj, std::int32_t speed)
{
    if (obj->Direction)
    {
        speed = -speed;
    }

    if (obj->Name == idNova && current_suit != 2 && !on_roof && GetProperty(obj, 0, -1) == isWater)
    {
        speed = speed * 6 / 8;
    }

    std::int32_t delta = speed / 2;
    if ((speed & 1) != 0 && (game_cicle_counter & 1) == 0)
    {
        if (speed >= 0)
        {
            delta++;
        }
        else
        {
            delta--;
        }
    }

    std::int32_t dx = obj->Width + std::abs(delta);
    std::int32_t dy = -1;
    std::int32_t t;
    bool i = false;
    while (obj->Height < dy)
    {
        t = GetProperty(obj, dx, dy);
        if (t == isFloor || t == isShift || t == isSpike)
        {
            i = true;
            break;
        }
        dy -= 16;
    }
    t = GetProperty(obj, dx, obj->Height);
    if (t == isFloor || t == isShift || t == isSpike)
    {
        i = true;
    }
    if (!i)
    {
        obj->X += delta;
        return true;
    }

    if (GetProperty(obj, 0, 1) == isShift)
    {
        return true;
    }
    return false;
}

bool Program::SimpleMoveObjectForward(const std::shared_ptr<GameObject> &obj, std::int32_t speed)
{
    std::int32_t b = 0;
    if ((speed & 1) == 1)
    {
        b = game_cicle_counter & 1;
    }
    speed = speed / 2 + b;

    if (obj->Direction)
    {
        speed = -speed;
    }

    if (GetProperty(obj, 16, -1) == isFloor || GetProperty(obj, 16, -1) == isSpike)
    {
        return false;
    }
    else
    {
        obj->X += speed;
        return true;
    }
}

void Program::CreateBullet(const std::shared_ptr<GameObject> &obj, const std::string &animations, const std::string &anim_name, std::int32_t xoffset, std::int32_t yoffset, std::int32_t xdelta, std::int32_t ydelta, bool damageble)
{
    std::shared_ptr<GameObject> o = CreateChild(obj, idBullet, xoffset, yoffset);
    o->Animations = FindObjectAnimation(animations);
    InitAnimation(o, anim_name, true);
    o->XTarget = xdelta;
    o->YTarget = ydelta;
    o->isDamageable = damageble;
    o->haveGravity = damageble;
    //o.Fixed = true;
}

bool Program::TestShoot(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset, std::int32_t yoffset, std::int32_t direct)
{
    if (!InCurrentRoom(obj))
    {
        return false;
    }
    std::int32_t i;
    std::int32_t x = (obj->X + xoffset) / 16;
    std::int32_t y = (obj->Y + yoffset) / 16;
    std::int32_t h_x = hero_object->X / 16;
    std::int32_t h_y1 = (hero_object->Y + hero_object->Height) / 16;
    std::int32_t h_y2 = hero_object->Y / 16;
    if (direct == 0)
    {
        if (!SeeOnHero(obj) || y < h_y1 || y >= h_y2)
        {
            return false;
        }

        std::int32_t dx = 1;
        if (obj->Direction)
        {
            dx = -1;
        }

        do
        {
            if (x == h_x)
            {
                return true;
            }
            x += dx;
        } while ((i = (TilesetProperty[ Loc[x][y] ] >> 5) & 7) == isEmpty || i == isLadder || i == isWater);
    }
    else if (direct == 1)
    {
        if (x != h_x)
        {
            return false;
        }

        do
        {
            if (y >= h_y1)
            {
                return true;
            }
            y++;
            //} while ((i = (TilesetProperty[Loc[x, y]] >> 5) & 7) == isEmpty || i == isLadder || i == isWater);
        } while ((i = (TilesetProperty[ Loc[x][y] ] >> 5) & 7) == isEmpty || i == isWater);
    }
    else
    {
        if (!SeeOnHero(obj))
        {
            return false;
        }

        std::int32_t dy = 1;
        if (direct == 2)
        {
            if (y < h_y1)
            {
                return false;
            }
            else
            {
                dy = -1;
            }
        }
        if (direct == 3 && y >= h_y2)
        {
            return false;
        }

        std::int32_t dx = 1;
        if (obj->Direction)
        {
            dx = -1;
        }

        do
        {
            if (x == h_x && y == h_y1 + 1)
            {
                return true;
            }
            x += dx;
            y += dy;
        } while ((i = (TilesetProperty[ Loc[x][y] ] >> 5) & 7) == isEmpty || i == isLadder || i == isWater);

    }
    return false;
}

std::int32_t Program::ObjectsCount(std::int32_t name)
{
    std::int32_t i = 0;
    for (const auto &obj : actual_objects)
    {
        if (obj->Name == name)
        {
            i++;
        }
    }
    return i;
}

void Program::CreateExplosion(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset, std::int32_t yoffset)
{
    if (ObjectsCount(idExplosion) < 6)
    {
        std::shared_ptr<GameObject> o = CreateObject(idExplosion, obj->X + xoffset, obj->Y + yoffset, false, true);
        o->Animations = FindObjectAnimation("Items");
        InitAnimation(o, "Explosion", true);
        o->Priority = high_priority;
        o->Fixed = true;
        InitSFX(sfx_explosion);
    }
}

void Program::TurnObject(const std::shared_ptr<GameObject> &obj)
{
    if (obj->X < hero_object->X)
    {
        obj->Direction = false;
    }
    else
    {
        obj->Direction = true;
    }
}

std::uint8_t Program::GetXDistance(const std::shared_ptr<GameObject> &obj)
{
    std::int32_t dist = std::abs(hero_object->X - obj->X);
    if (dist >= 256)
    {
        return 255;
    }
    else
    {
        return static_cast<std::uint8_t>(dist);
    }

}

std::uint8_t Program::GetYDistance(const std::shared_ptr<GameObject> &obj)
{
    std::int32_t dist = obj->Y - hero_object->Y;
    if (dist < 0)
    {
        dist = -dist - 32;
        if (dist < 1)
        {
            dist = 1;
        }
    }

    if (dist >= 160)
    {
        return 159;
    }
    else
    {
        return static_cast<std::uint8_t>(dist);
    }

}

bool Program::SeeOnObject(const std::shared_ptr<GameObject> &obj1, const std::shared_ptr<GameObject> &obj2)
{
    if (obj1->X < obj2->X && !obj1->Direction)
    {
        return true;
    }
    if (obj1->X >= obj2->X + 1 && obj1->Direction)
    {
        return true;
    }
    return false;
}

bool Program::SeeOnHero(const std::shared_ptr<GameObject> &obj)
{
    if (obj->X < hero_object->X && !obj->Direction)
    {
        return true;
    }
    if (obj->X >= hero_object->X + 1 && obj->Direction)
    {
        return true;
    }
    return false;
}

bool Program::InCurrentRoom(const std::shared_ptr<GameObject> &obj)
{
    if (obj->X >= x_home && obj->X < x_home + 255 && obj->Y >= y_home && obj->Y < y_home + 159)
    {
        return true;
    }
    return false;
}

std::int32_t Program::GetProperty(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset, std::int32_t yoffset)
{
    if (obj->Direction)
    {
        xoffset = -xoffset;
    }

    return (GetFullProperty(obj, xoffset, yoffset) >> 5) & 7;
}

std::int32_t Program::GetFullProperty(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset, std::int32_t yoffset)
{
    std::int32_t x = (obj->X + xoffset) / 16;
    std::int32_t y = (obj->Y + yoffset) / 16;
    if (x >= 128)
    {
        x = 0;
        y++;
        if (y >= 58)
        {
            y = 57;
        }
    }
    return TilesetProperty[ Loc[x][y] ];
}

std::int32_t Program::GetXYProperty(std::int32_t x, std::int32_t y)
{
    return (TilesetProperty[ Loc[x / 16][y / 16] ] >> 5) & 7;
}

bool Program::GetRailsTile(const std::shared_ptr<GameObject> &obj)
{
    bool i = false;
    obj->YAccel = obj->YAccel & 3;
    if (obj->YAccel == 0 && GetProperty(obj, 0, -16) == isRails)
    {
        i = true;
    }
    if (obj->YAccel == 1 && GetProperty(obj, 16, 0) == isRails)
    {
        i = true;
    }
    if (obj->YAccel == 2 && GetProperty(obj, 0, 16) == isRails)
    {
        i = true;
    }
    if (obj->YAccel == 3 && GetProperty(obj, -16, 0) == isRails)
    {
        i = true;
    }
    return i;
}

void Program::CreateFractions(const std::shared_ptr<GameObject> &obj, std::int32_t num)
{
    if (graphics_quality == 0)
    {
        return;
    }

    std::int32_t max = 8;
    if (graphics_quality == 1)
    {
        max = 3;
        num /= 2;
    }
    for (std::int32_t i = 0; i < num; i++)
    {
        if (particle_cntr < max)
        {
            std::int32_t x = 3 - (rnd->Next() & 7);
            for (std::int32_t j = 0; j < 8; j++)
            {
                if (GetProperty(obj, x, 0) == isEmpty)
                {
                    break;
                }
                x = 3 - (rnd->Next() & 7);
            }
            std::shared_ptr<GameObject> o = CreateChild(obj, idFraction, x, 0);
            o->Animations = FindObjectAnimation("Items");
            InitAnimation(o, "Fraction", true);
            o->Direction = x < 0 ? false : true;
            o->YAccel = -(rnd->Next() & 15);
            o->Priority = high_priority;
            o->Counter = 100;
            particle_cntr++;
        }
    }
}

void Program::CreateMiniBonus(const std::shared_ptr<GameObject> &obj)
{
    if (!mini_bonus_ready)
    {
        mini_bonus_ready = true;
        return;
    }

    std::uint8_t b = 0;
    std::uint8_t c = 0;
    std::uint8_t d = 0;

    switch (rnd->Next() & 15)
    {
    case 1:
        b = 128;
        c = 0x45;
        d = idMiniBattery;
        break;

    case 3:
        b = 132;
        c = 0x42;
        d = idMiniHeart;
        break;

    case 5:
        b = 136;
        c = 0x46;
        d = idMiniPowerup;
        break;

    case 0:
    case 4:
    case 7:
        if (hero_life < 35)
        {
            b = 132;
            c = 0x42;
            d = idMiniHeart;
        }
        else if (hero_weapon < 35)
        {
            b = 136;
            c = 0x46;
            d = idMiniPowerup;
        }
        else if (hero_energy < 35)
        {
            b = 128;
            c = 0x45;
            d = idMiniBattery;
        }
        break;
    }

    if (b == 0)
    {
        return;
    }

    if (current_level == 5)
    {
        b = 128;
        c = 0x45;
        d = idMiniBattery;
    }

    mini_bonus_ready = false;

    std::shared_ptr<GameObject> o = CreateChild(obj, d, 0, 0);
    o->Type = b;
    o->Status = c;
    o->Width = 4;
    o->Height = -8;
    o->haveGravity = true;
    o->YAccel = -15;
}

bool Program::EnemyWaterSpikeTest(const std::shared_ptr<GameObject> &obj)
{
    std::int32_t a = GetProperty(obj, -obj->Width, 1);
    std::int32_t b = GetProperty(obj, obj->Width, 1);
    if ((a == isSpike && b == isSpike) || (a == isWater && b == isWater))
    {
        CreateExplosion(obj, 0, 0);
        RemoveObject(obj);
        return true;
    }
    return false;
}

void Program::InitHeroSpike()
{
    if (hero_die)
    {
        return;
    }
    if (!immortal_mode)
    {
        hero_life -= 26;
    }
    if (hero_life < 0 || boss_mode)
    {
        hero_life = 0;
    }
    is_fly = false;
    on_wall = false;
    on_roof = false;
    on_ladder = false;
    attack_cntr = 0;
    hero_object->YAccel = 0;
    hero_object->haveGravity = false;
    hero_die = true;
    hero_object->NoInterruptAnim = true;
    hero_object->PlatformObject = nullptr;
    std::string anim = "Nova_Damage";
    if (current_level == 5)
    {
        anim = "J_Die";
    }
    InitAnimation(hero_object, anim, true);
    InitSFX(sfx_damage);
    InitIcon(im_noise);
}

bool Program::HeroDamage(const std::shared_ptr<GameObject> &obj, std::int32_t yoffset)
{
    if (disable_control || hero_object->UndeadCounter != 0 || hero_life == 0 || hero_die)
    {
        return false;
    }

    std::int32_t w = obj->Width;
    if (w < 12)
    {
        w = 12;
    }

    if (yoffset != 0)
    {
        if (!InRange(obj->X, hero_object->X, w) || hero_object->Y < obj->Y + yoffset || obj->Y + yoffset < hero_object->Y + hero_object->Height)
        {
            return false;
        }
    }
    else
    {
        if (!InRange(obj->X, hero_object->X, w) || hero_object->Y < obj->Y + obj->Height || obj->Y < hero_object->Y + hero_object->Height)
        {
            return false;
        }
    }

    DecreaseHeroLife();
    return true;
}

void Program::DecreaseHeroLife()
{
    if (!immortal_mode)
    {
        if (current_level != 5)
        {
            hero_weapon_max -= 10;
            if (hero_weapon_max < 20)
            {
                hero_weapon_max = 20;
            }
        }
        else
        {
            if (hero_energy != 0)
            {
                hero_energy -= 16;
                if (hero_energy < 0)
                {
                    hero_energy = 0;
                }
                std::shared_ptr<GameObject> obj = CreateChild(hero_object, idJBubble, 0, 0);
                obj->Animations = hero_object->Animations;
                obj->Priority = high_priority;
                InitAnimation(obj, "JBubble", true);
                hero_object->UndeadCounter = 50;
                InitSFX(sfx_damage);
                return;
            }
        }

        hero_life -= 16;
        if (hero_life < 0)
        {
            hero_life = 0;
        }
    }

    if (hero_life != 0)
    {
        hero_object->UndeadCounter = 50;
        InitSFX(sfx_damage);
        InitIcon(im_damage);
    }
    else
    {
        InitHeroSpike();
    }
}

std::shared_ptr<Program::GameObject> Program::EnemyDamage(const std::shared_ptr<Program::GameObject> &obj, std::int32_t xdist)
{
    std::shared_ptr<GameObject> r = nullptr;
    std::int32_t ra = 6;
    if (obj->Name == idWave)
    {
        ra = 10;
    }
    for (auto &o : actual_objects)
    {
        if (!o->NoActivated && o != hero_object && obj != o && o->isDamageable && o->UndeadCounter == 0 && InRange(obj->X, o->X, xdist) && o->Y + ra >= obj->Y && obj->Y >= o->Y + o->Height - ra)
        {
            o->isDamageable = false;
            r = o;
        }
    }
    return r;
}

void Program::ObjWiggle(const std::shared_ptr<GameObject> &obj)
{
    if ((game_cicle_counter & 3) == 0)
    {
        if ((game_cicle_counter & 32) != 0)
        {
            FlyUp(obj);
        }
        else
        {
            FlyDown(obj);
        }
    }
}

bool Program::FlyUp(const std::shared_ptr<GameObject> &obj)
{
    obj->Y--;
    ga = GetProperty(obj, -obj->Width, obj->Height - 8);
    gb = GetProperty(obj, obj->Width, obj->Height - 8);
    if (ga == isFloor || gb == isFloor || ga == isSpike || gb == isSpike || ga == isShift || gb == isShift)
    {
        obj->Y++;
        return false;
    }
    return true;
}

bool Program::FlyDown(const std::shared_ptr<GameObject> &obj)
{
    obj->Y++;
    ga = GetProperty(obj, -obj->Width, 0);
    gb = GetProperty(obj, obj->Width, 0);
    if (ga == isFloor || gb == isFloor || (ga == isSpike && gb == isSpike) || ga == isShift || gb == isShift || (obj->Name == idNova && GetProperty(obj, 0, -4) != isPlatform && GetProperty(obj, 0, 0) == isPlatform))
    {
        if (obj->Name == idNova && GetKey(Key_Down) && !secret_boss_enabled)
        {
            obj->haveGravity = true;
            obj->YAccel = 0;
            is_fly = false;
        }
        else
        {
            obj->Y--;
            return false;
        }
    }
    return true;
}

void Program::HeroOnRoof()
{
    if (GetProperty(hero_object, -8, -36) == isFloor && GetProperty(hero_object, 8, -36) == isFloor)
    {
        on_roof = true;
        on_wall = false;
        hero_object->haveGravity = false;
        hero_object->Y = (hero_object->Y & 0xfff0) + 9;
        hero_object->YAccel = 0;
        InitSFX(sfx_gotonthewall);
    }
}

bool Program::InRange(std::int32_t a, std::int32_t b, std::int32_t value)
{
    if (std::abs(a - b) < value)
    {
        return true;
    }
    return false;
}

bool Program::ObjCentrum(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset)
{
    if (GetKey(Key_Left + Key_Right))
    {
        return true;
    }

    if (hero_object->X < obj->X + xoffset)
    {
        pressed_keys = static_cast<std::uint8_t>(pressed_keys | Key_Right);
    }
    else
    {
        pressed_keys = static_cast<std::uint8_t>(pressed_keys | Key_Left);
    }
    return false;
}

bool Program::BossDie(const std::shared_ptr<GameObject> &obj)
{
    if (obj->isDamageable)
    {
        return false;
    }

    if (obj->Life != 0)
    {
        obj->isDamageable = true;
        obj->UndeadCounter = 50;
        CreateExplosion(obj, 0, obj->Height / 2);
        obj->Life -= 5;
        if (obj->Life < 0)
        {
            obj->Life = 0;
        }
        hero_path = obj->Life;
    }

    if (obj->Life == 0)
    {
        for (std::int32_t i = 0; i < 256; i++)
        {
            if (((TilesetProperty[i] >> 5) & 7) == isSpike)
            {
                TilesetProperty[i] = isFloor << 5;
            }
        }

        obj->isDamageable = false;
        if (!secret_boss_enabled)
        {
            InitAnimation(obj, 1, true);
        }
        if (secret_boss_enabled || !Gravity(obj))
        {
            MuteAllMusic();
            std::shared_ptr<GameObject> o = CreateChild(obj, idMultiExplosions, 0, -32);
            o->Counter = 100;
            o->NoVisible = true;
            obj->Name = idExplosion;
            boss_mode = false;
            obj->UndeadCounter = 0;
        }
    }
    return true;
}

void Program::InitGEngine()
{
    screen = std::make_shared<SdlDotNetCompat::Graphics::Surface>(256, 192);
    screen_copy = std::make_shared<SdlDotNetCompat::Graphics::Surface>(256, 160);
    scroll_screen = std::make_shared<SdlDotNetCompat::Graphics::Surface>(256, 160);

    InitFonts();

    ClearScreen();

    //загрузка некстовской палитры
    BinaryStreamReader f("./res/palettes/NextPalette.bin");

    for (std::int32_t i = 0; i < 256; i++)
    {
        next_palette[i] = Color::FromArgb(f.ReadInt32());
    }
}

SdlDotNetCompat::Drawing::Color Program::GetColor(std::int32_t zxcolor)
{
    std::int32_t bright = (zxcolor & 8) == 0 ? 192 : 255;
    std::int32_t r = (zxcolor & 2) == 0 ? 0 : bright;
    std::int32_t g = (zxcolor & 4) == 0 ? 0 : bright;
    std::int32_t b = (zxcolor & 1) == 0 ? 0 : bright;
    return SdlDotNetCompat::Drawing::Color::FromArgb(r, g, b);
}

void Program::ClearScreen()
{
    screen->Fill(Color::Black);
    for (std::int32_t y = 0; y < 192; y++)
    {
        for (std::int32_t x = 0; x < 256; x++)
        {
            attr_layer[0][x][y] = attr_palette[0][0];
            attr_layer[1][x][y] = attr_palette[1][15];
        }
    }
}

void Program::FillAttrRect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, std::uint8_t attr)
{
    for (std::int32_t j = 0; j < height * 8; j++)
    {
        for (std::int32_t i = 0; i < width * 8; i++)
        {
            attr_layer[0][x * 8 + i][y * 8 + j] = GetAttrColor(attr, false);
            attr_layer[1][x * 8 + i][y * 8 + j] = GetAttrColor(attr, true);
        }
    }
    screen->Fill(SdlDotNetCompat::Drawing::Rectangle(x * 8, y * 8, width * 8, height * 8), GetAttrColor(attr, false));
}

void Program::InitRoomTiles()
{
    std::int32_t cx = current_xy_room & 0x0f;
    std::int32_t cy = (current_xy_room & 0xf0) / 16;

    x_home_tile = cx * 14;
    y_home_tile = cy * 8;
    x_home = x_home_tile * 16;
    y_home = y_home_tile * 16;

    RoomAnimTiles.clear();
    for (std::int32_t j = 0; j < 10; j++)
    {
        for (std::int32_t i = 0; i < 16; i++)
        {
            Room[i][j] = Loc[x_home_tile + i][y_home_tile + j];
            std::int32_t p = TilesetProperty[Room[i][j]];
            std::int32_t pp = (p >> 5) & 7;
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
        std::int32_t x = 0;
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

        std::int32_t yoffset = 1;
        while (hero_object->Y + yoffset - (current_xy_room & 0xf0) * 8 < 160)
        {
            std::int32_t t1 = GetProperty(hero_object, 8, yoffset);
            std::int32_t t2 = GetProperty(hero_object, -8, yoffset);

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

void Program::NewTile(std::int32_t x, std::int32_t y, std::int32_t num)
{
    Loc[x][y] = num;
    std::int32_t i = x - x_home_tile;
    std::int32_t j = y - y_home_tile;
    if (i < 0 || i >= 16 || j < 0 || j >= 10)
    {
        return;
    }
    Room[i][j] = num;
    screen_refresh_tab[i][j] = true;
}

void Program::FullRoomRedraw()
{
    for (std::int32_t j = 0; j < 10; j++)
    {
        for (std::int32_t i = 0; i < 16; i++)
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
        std::int32_t mask;
        std::int32_t tile = a->num;
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
    for (std::int32_t j = 0; j < 10; j++)
    {
        for (std::int32_t i = 0; i < 16; i++)
        {
            if (screen_refresh_tab[i][j])
            {
                const auto room = Room[i][j];
                screen->Blit(*(Tileset[tiles_mode][room]), Point(i * 16, j * 16));
                if (tiles_mode == 0)
                {
                    for (std::int32_t ya = 0; ya < 16; ya++)
                    {
                        for (std::int32_t xa = 0; xa < 16; xa++)
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
    std::int32_t i = ((obj->X - x_home) - 8) / 8;
    std::int32_t j = ((obj->Y - y_home) - 16) / 8;
    if (tiles_mode == zx_classic_mode)
    {
        screen->Blit(*Tileset[tiles_mode][obj->XAccel], Point(i * 8, j * 8));
        for (std::int32_t ya = 0; ya < 16; ya++)
        {
            for (std::int32_t xa = 0; xa < 16; xa++)
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
    std::int32_t i, j;
    if (tiles_mode == zx_classic_mode)
    {
        i = ((obj->X - x_home) - 4) / 8;
        j = ((obj->Y - y_home) - 8) / 8;
        if (i < 0 || i >= 31 || j < 0 || j >= 19)
        {
            return;
        }
        DrawSymbol32(i, j, static_cast<std::uint8_t>(obj->XAccel), obj->Status);
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
        std::int32_t xpos = obj->X;
        std::int32_t ypos = obj->Y + e->YOffset;

        if (game_mode != stealth_mode && obj->Fixed)
        {
            xpos &= 0xfff8;
        }

        std::int32_t xoffset = e->XOffset;
        if (obj->Direction)
        {
            xoffset = -e->ElemSprite->Width - e->XOffset;
        }
        xpos += xoffset;

        xpos -= x_home;
        ypos -= y_home;

        std::int32_t x;
        std::int32_t y;
        std::int32_t width = e->ElemSprite->Width;
        std::int32_t height = e->ElemSprite->Height;

        if (!(width == 1 && height == 1))
        {
            //помечаем экран на перерисовку
            for (std::int32_t j = 0; j < (height + 15 + (ypos & 15)) / 16; j++)
            {
                for (std::int32_t i = 0; i < (width + 15 + (xpos & 15)) / 16; i++)
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
            for (std::int32_t j = 0; j < height; j++)
            {
                for (std::int32_t i = 0; i < width; i++)
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
    for (std::int32_t l = 0; l < 3; l++)
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

void Program::SetScale(std::int32_t x, std::int32_t y, std::int32_t value)
{
    for (std::int32_t j = 0; j < 77; j++)
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

void Program::SetScaleCol(std::int32_t x, std::int32_t y)
{
    for (std::int32_t i = 0; i < 5; i++)
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
            std::int32_t c = 17;
            if (i == 3)
            {
                c = 20;
            }
            screen->Draw(Point(x, y + i), next_palette[c]);
        }
    }
}

void Program::ResScaleCol(std::int32_t x, std::int32_t y)
{
    for (std::int32_t i = 0; i < 5; i++)
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

void Program::LoadLocationProject(std::int32_t num)
{
    scroll_direction = 0;
    std::string name = levels_names[num];

    std::string locFile = std::string("./res/locations/") + name + ".loc";

    BinaryStreamReader f(locFile.c_str());

    //загрузка локации
    std::int32_t v = f.ReadByte();
    if (v != 0)
    {        
        Quit(this, new QuitEventArgs());
    }
    f.ReadByte();
    LocWidth  = f.ReadByte() + 1;
    LocHeight = f.ReadByte() + 1;

    Loc = AllocateDynamicArray<std::int32_t>(LocHeight, LocWidth);
    for (std::int32_t y = 0; y < LocHeight; y++)
    {
        for (std::int32_t x = 0; x < LocWidth; x++)
        {
            Loc[x][y] = f.ReadByte();
        }
    }

    //загрузка тайлсетов
    for (std::int32_t k = 0; k < 2; k++)
    {
        for (std::int32_t i = 0; i < 256; i++)
        {
            for (std::int32_t j = 0; j < 37; j++)
            {
                current_tilesets[k][i][j] = f.ReadByte();
            }
        }
    }

    //загрузка палитры Next
    for (std::int32_t i = 0; i < 2; i++)
    {
        for (std::int32_t j = 0; j < 16; j++)
        {
            f.ReadInt32();
        }
    }

    //загрузка координат стартовой комнаты локации
    std::int32_t cx = f.ReadInt32();
    std::int32_t cy = f.ReadInt32();
    current_xy_room = static_cast<std::uint8_t>(cx + cy * 16);

    //загрузка объектов локации
    ClearAllObjects();
    std::shared_ptr<GameObject> temp = CreateObject(idNova, 0, 0, false, false);
    std::int32_t room_x = (LocWidth - 16) / 14 + 1;
    std::int32_t room_y = (LocHeight - 10) / 8 + 1;
    for (std::int32_t y = 0; y < (LocHeight - 10) / 8 + 1; y++)
    {
        for (std::int32_t x = 0; x < (LocWidth - 16) / 14 + 1; x++)
        {
            std::int32_t xh = x * 14;
            std::int32_t yh = y * 8;
            std::int32_t obj_num = f.ReadByte();
            for (std::int32_t i = 0; i < obj_num; i++)
            {
                std::shared_ptr<GameObject> obj = CreateObject(objects_names[f.ReadString()], 0, 0, false, false);
                std::int32_t x1 = f.ReadByte();
                std::int32_t y1 = f.ReadByte();
                std::int32_t x2 = f.ReadByte();
                std::int32_t y2 = f.ReadByte();
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
                std::int32_t q = f.ReadByte();
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
                obj->XYRoom = static_cast<std::uint8_t>(y * 16 + x);

                if (reverse_way && obj->Name == idDoor && obj->Status != 2)
                {
                    obj->Status = static_cast<std::uint8_t>(1 - obj->Status);
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
    for (std::int32_t y = 0; y < room_y; y++)
    {
        for (std::int32_t x = 0; x < room_x; x++)
        {
            RoomsLayers[x + y * 16] = std::vector<std::shared_ptr<RoomLayers>>();
            std::int32_t layers_num = f.ReadByte();
            for (std::int32_t i = 0; i < layers_num; i++)
            {
                std::shared_ptr<RoomLayers> l = std::make_shared<RoomLayers>();

                l->Name = f.ReadString();
                std::int32_t tiles_num = f.ReadInt32();
                for (std::int32_t j = 0; j < tiles_num; j++)
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
        for (std::int32_t j = 0; j < 256; j++)
        {
            for (std::int32_t i = 0; i < 256; i++)
            {
                tileset256[j][i] = Color::FromArgb(f.ReadInt32());
            }
        }
    }

    //прорисовка тайлсета в палитре некста
    for (std::int32_t i = 0; i < 256; i++)
    {
        Tileset[1][i] = std::make_shared<Surface>(16, 16);
        for (std::int32_t y = 0; y < 16; y++)
        {
            for (std::int32_t x = 0; x < 16; x++)
            {
                Tileset[1][i]->Draw(Point(x, y), tileset256[i][x + y * 16]);
            }
        }
    }

    //инициализируем свойства тайлсета
    for (std::int32_t i = 0; i < 256; i++)
    {
        TilesetProperty[i] = current_tilesets[0][i][36];
    }

    //прорисовка классического тайлсета
    DrawClassicTileset();
}

void Program::DrawClassicTileset()
{
    for (std::int32_t i = 0; i < 256; i++)
    {
        Tileset[0][i] = std::make_shared<Surface>(16, 16);
        for (std::int32_t y = 0; y < 16; y++)
        {
            for (std::int32_t x = 0; x < 16; x++)
            {
                std::uint8_t a = current_tilesets[0][i][y / 8 * 2 + x / 8 + 32];
                Color ink = attr_palette[0][(a & 7) + ((a >> 3) & 8)];
                Color paper = attr_palette[1][(a >> 3) & 15];

                if (bw_color_mode && TilesetProperty[i] != 1)
                {
                    ink = Color::Black;
                    paper = Color::White;
                }

                TilesetAttr[1][i][x][y] = paper;
                TilesetAttr[0][i][x][y] = ink;

                std::uint8_t p = current_tilesets[0][i][y * 2 + x / 8];
                const Color &c = ((p << (x % 8)) & 0x80) == 0 ? paper : ink;
                Tileset[0][i]->Draw(Point(x, y), c);
            }
        }
    }
}

void Program::NeedScrollRoom()
{
    std::int32_t x = hero_object->X - x_home;
    std::int32_t y = hero_object->Y - y_home;

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

// NOTE: preferences (tile mode - zx_classic_mode OR zx_next_mode)
std::string Program::language = "English";
std::int32_t Program::sprite_mode = zx_classic_mode;
std::int32_t Program::tiles_mode = zx_classic_mode;

void Program::MainInit()
{
    start_weapon = 20;
    start_life   = 77;
    start_energy = 77;

    for (std::int32_t i = 0; i < 16; i++)
    {
        attr_palette[0][i] = GetColor(i);
        attr_palette[1][i] = GetColor(i);
    }

    //инициализация словаря
    objects_names.emplace("none", 0);
    objects_names.emplace("Nova", idNova);
    objects_names.emplace("Dust", idDust);
    objects_names.emplace("Explosion", idExplosion);
    objects_names.emplace("RocketSmoke", idRocketSmoke);
    objects_names.emplace("MultiExplosions", idMultiExplosions);
    objects_names.emplace("Blower", idBlower);
    objects_names.emplace("Bubble", idBubble);
    objects_names.emplace("Bumerang", idBumerang);
    objects_names.emplace("Wave", idWave);
    objects_names.emplace("Battery", idBattery);
    objects_names.emplace("Heart", idHeart);
    objects_names.emplace("Powerup", idPowerup);
    objects_names.emplace("MiniBattery", idMiniBattery);
    objects_names.emplace("MiniHeart", idMiniHeart);
    objects_names.emplace("MiniPowerup", idMiniPowerup);
    objects_names.emplace("Suit", idSuit);
    objects_names.emplace("Star", idStar);
    objects_names.emplace("Platform", idPlatform);
    objects_names.emplace("Steam", idSteam);
    objects_names.emplace("Fraction", idFraction);
    objects_names.emplace("Door", idDoor);
    objects_names.emplace("Tankette", idTankette);
    objects_names.emplace("Dron", idDron);
    objects_names.emplace("Bullet", idBullet);
    objects_names.emplace("Spider", idSpider);
    objects_names.emplace("Piranha", idPiranha);
    objects_names.emplace("BigPiranha", idBigPiranha);
    objects_names.emplace("Jelly", idJelly);
    objects_names.emplace("SpiderNest", idSpiderNest);
    objects_names.emplace("Bug", idBug);
    objects_names.emplace("Gun", idGun);
    objects_names.emplace("Dragonfly", idDragonfly);
    objects_names.emplace("FighterBomber", idFighterBomber);
    objects_names.emplace("DronBomber", idDronBomber);
    objects_names.emplace("AlienClawBottom", idAlienClawBottom);
    objects_names.emplace("AlienClawTop", idAlienClawTop);
    objects_names.emplace("AlienWorm", idAlienWorm);
    objects_names.emplace("Slime", idSlime);
    objects_names.emplace("SonusVenator", idSonusVenator);
    objects_names.emplace("BigSpider", idBigSpider);
    objects_names.emplace("Craken", idCraken);
    objects_names.emplace("Moth", idMoth);
    objects_names.emplace("Rocketman", idRocketman);
    objects_names.emplace("CrabBoss", idCrabBoss);
    objects_names.emplace("FlyBoss", idFlyBoss);
    objects_names.emplace("AlienPet", idAlienPet);
    objects_names.emplace("AlienSliderman", idAlienSliderman);
    objects_names.emplace("Megabrain", idMegabrain);
    objects_names.emplace("Rocket", idRocket);
    objects_names.emplace("MiniBrain", idMiniBrain);
    objects_names.emplace("Bomb", idBomb);
    objects_names.emplace("FlyBomb", idFlyBomb);
    objects_names.emplace("WaterFun", idWaterFun);
    objects_names.emplace("BubbleGenerator", idBubbleGenerator);
    objects_names.emplace("Jacqueline", idJacqueline);
    objects_names.emplace("JLift", idJLift);
    objects_names.emplace("JDoor", idJDoor);
    objects_names.emplace("JTerminal", idJTerminal);
    objects_names.emplace("JPolice1", idJPolice1);
    objects_names.emplace("JPolice2", idJPolice2);
    objects_names.emplace("JPolice3", idJPolice3);
    objects_names.emplace("JOffice1", idJOffice1);
    objects_names.emplace("JOffice2", idJOffice2);
    objects_names.emplace("JOffice3", idJOffice3);
    objects_names.emplace("NovaBike", idNovaBike);
    objects_names.emplace("JDJump", idJDJump);
    objects_names.emplace("JGun", idJGun);
    objects_names.emplace("JShield", idJShield);
    objects_names.emplace("Dragon", idDragon);

    levels_names.emplace(0, "level 1-1");
    levels_names.emplace(1, "level 1-2");
    levels_names.emplace(2, "level 1-3");
    levels_names.emplace(3, "level 1-4");
    levels_names.emplace(4, "dragon 1");
    levels_names.emplace(5, "boss 1");
    levels_names.emplace(6, "level 2-1");
    levels_names.emplace(7, "level 2-2");
    levels_names.emplace(8, "level 2-3");
    levels_names.emplace(9, "level 2-4");
    levels_names.emplace(10, "dragon 2");
    levels_names.emplace(11, "boss 2");
    levels_names.emplace(12, "level 3-1");
    levels_names.emplace(13, "level 3-2");
    levels_names.emplace(14, "level 3-3");
    levels_names.emplace(15, "level 3-4");
    levels_names.emplace(16, "dragon 3");
    levels_names.emplace(17, "boss 3");
    levels_names.emplace(18, "level 4-1");
    levels_names.emplace(19, "level 4-2");
    levels_names.emplace(20, "level 4-3");
    levels_names.emplace(21, "level 4-4");
    levels_names.emplace(22, "level 4-5");
    levels_names.emplace(23, "level 4-6");
    levels_names.emplace(24, "level 4-7");
    levels_names.emplace(25, "level 4-8");
    levels_names.emplace(26, "subboss 1");
    levels_names.emplace(27, "subboss 2");
    levels_names.emplace(28, "subboss 3");
    levels_names.emplace(29, "subboss 4");
    levels_names.emplace(30, "subboss 5");
    levels_names.emplace(31, "subboss 6");
    levels_names.emplace(32, "finalboss 0");
    levels_names.emplace(33, "finalboss 1");
    levels_names.emplace(34, "finalboss 2");
    levels_names.emplace(35, "Jacqueline");
    levels_names.emplace(36, "DLC");
    levels_names.emplace(37, "DLCBoss");

    music_names.emplace(0, "1-1");
    music_names.emplace(1, "1-2");
    music_names.emplace(2, "1-3");
    music_names.emplace(3, "2-1");
    music_names.emplace(4, "2-2");
    music_names.emplace(5, "2-3");
    music_names.emplace(6, "3-1");
    music_names.emplace(7, "3-2");
    music_names.emplace(8, "3-3");
    music_names.emplace(9, "4-1");
    music_names.emplace(10, "boss");
    music_names.emplace(11, "finalboss");
    music_names.emplace(12, "stealth_1");
    music_names.emplace(13, "stealth_2");
    music_names.emplace(14, "stealth_3");
    music_names.emplace(15, "race");

    music_names.emplace(247, "5-1");
    music_names.emplace(248, "game_over");
    music_names.emplace(249, "Secret boss");
    music_names.emplace(250, "finalcut");
    music_names.emplace(251, "intro");
    music_names.emplace(252, "motorbike");
    music_names.emplace(253, "menu");
    music_names.emplace(254, "clip");

    have_suit[0] = true;
    have_suit[1] = true;
    have_suit[2] = true;
    have_suit[3] = true;
    InitSFXBank();
    InitGEngine();

    if (external_resource)
    {
        InitDebugMenu();
    }
    else
    {
        LoadProgress();
        InitScene(5);
    }
}

std::string Program::current_save_version = "1.5";

void Program::SaveProgress()
{
    const std::string savePath = Environment::SpecialFolder::ApplicationData() + "/blade_project.saves";

    BinaryStreamWriter f(savePath.c_str());

    //номер версии
    f.Write(current_save_version);

    //сохраняем настройки
    for (std::int32_t i = 0; i < 8; i++)
    {
        f.Write(static_cast<std::uint8_t>(KeysMap[i]));
    }
    f.Write(kempston_on);
    f.Write(graphics_quality);
    f.Write(bw_color_mode);
    f.Write(music_on);
    f.Write(sound_on);
    f.Write(scroll_on);
    f.Write(sprite_mode);
    f.Write(tiles_mode);
    f.Write(sound_mode);

    //сохраняем прогресс
    f.Write(difficulty);
    f.Write(max_difficulty);
    f.Write(collected_stars);
    f.Write(noreaded_stars);
    f.Write(stars_num);
    for (std::int32_t i = 0; i < 4; i++)
    {
        f.Write(have_suit[i]);
    }
    f.Write(levels_complete);
}

void Program::LoadProgress()
{

    if (loaded_progress)
    {
        return;
    }

    loaded_progress = true;

    const std::string savePath = Environment::SpecialFolder::ApplicationData() + "/blade_project.saves";
    if ( !File::Exists( savePath ) )
    {
        return;
    }

    BinaryStreamReader f(savePath.c_str());

    //проверяем версию
    std::string ver = f.ReadString();
    if (ver != current_save_version)
    {        
        return;
    }

    //загружаем настройки
    for (std::int32_t i = 0; i < 8; i++)
    {
        KeysMap[i] = static_cast<Key>(f.ReadByte());
    }

    kempston_on      = f.ReadBoolean();
    graphics_quality = f.ReadInt32();

    bw_color_mode    = f.ReadBoolean();
    music_on         = f.ReadBoolean();
    sound_on         = f.ReadBoolean();
    scroll_on        = f.ReadBoolean();
    sprite_mode      = f.ReadInt32();
    tiles_mode       = f.ReadInt32();
    sound_mode       = f.ReadInt32();

    //загружаем прогресс
    difficulty       = f.ReadInt32();
    max_difficulty   = f.ReadInt32();
    collected_stars  = f.ReadUInt64();
    noreaded_stars   = f.ReadUInt64();
    stars_num        = f.ReadInt32();
    for (std::int32_t i = 0; i < 4; i++)
    {
        have_suit[i] = f.ReadBoolean();
    }
    levels_complete = f.ReadByte();

    if (levels_complete == 0)
    {
        prev_game_mode = 0;
    }
    else
    {
        prev_game_mode = select_level_mode;
    }

    //collected_stars = 0xffffff;
    //noreaded_stars = 0xffffff;
    //stars_num = 48;

}

//void Program::StartTimer_Tick(const std::shared_ptr<void> &sender, const std::shared_ptr<SdlDotNetCompat::EventArgs> &e)
//{
//
//}

void Program::MainCicle()
{
    if (pause_cnt == 0)
    {
        Interrupt();

        switch (game_mode)
        {
        case debug_menu_mode:
            UpdateDebugMenu();
            break;
        case race_mode:
            UpdateRace();
            break;
        case stealth_mode:
            UpdateStealth();
            break;
        case platforming_mode:
            UpdatePlatforming();
            break;
        case game_over_mode:
            UpdateGameOver();
            break;
        case clip_mode:
            UpdateScene();
            break;
        case suit_mode:
            UpdateSuit();
            break;
        case select_level_mode:
            UpdateSelectLevel();
            break;
        case main_menu_mode:
            UpdateMainMenu();
            break;
        case new_game_mode:
            UpdateNewGame();
            break;
        case select_diff_mode:
            UpdateSelectDiff();
            break;
        case cancel_mission_mode:
            UpdateCancelMission();
            break;
        case load_screen_mode:
            UpdateLoadScreen();
            break;
        case select_message_mode:
            UpdateSelectMessage();
            break;
        case read_message_mode:
            UpdateReadMessage();
            break;
        case settings_mode:
            UpdateSettings();
            break;
        case control_settings_mode:
            UpdateControlsSettings();
            break;
        case redefine_mode:
            UpdateRedefine();
            break;
        case graphic_settings_mode:
            UpdateGraphicSettings();
            break;
        case sound_settings_mode:
            UpdateSoundSettings();
            break;
        case system_settings_mode:
            UpdateSystemSettings();
            break;
        case areyousure_mode:
            UpdateAreYouSure();
            break;
        case reset_mode:
            UpdateReset();
            break;
        case player_mode:
            UpdatePlayer();
            break;
        }
    }
    else
    {
        pause_cnt--;
        if (pause_cnt == 50)
        {
           //NOTE: SFX_Player has been removed
            ///SFX_Player->Stop();
        }
        if (pause_cnt == 0)
        {
            ResumeGameMusic();
        }
    }
}

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
    std::int32_t x = 0;
    std::int32_t y = 0;
    std::int32_t n = 0;
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
    std::int32_t t = (game_cicle_counter >> 1) & 3;
    std::int32_t a = t;
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

        for (std::int32_t i = 0; i < 3; i++)
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
                std::int32_t n = 13;
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
                std::int32_t n = game_cicle_counter - 25;
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

void Program::InitSay(std::int32_t text_num, std::int32_t pictogramm)
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
    std::int32_t i = (game_cicle_counter >> 3) & 3;
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
    debug_mode = true; // NOTE: configure mode here
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

    std::int32_t min = 0;
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
                for (std::int32_t i = 0; i < 77; i++)
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
    std::int32_t y = 11;
    if (max_difficulty == 1)
    {
        y++;
    }
    FillAttrRect(6, y + difficulty, 20, 1, 0x60);
    std::int32_t pos = FindText(12);
    pos = PrintString(pos, 6, 9);
    pos = PrintString(pos, 6, 10);

    for (std::int32_t i = 0; i < 1 + max_difficulty; i++)
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

        std::int32_t empty_str = FindText(26);
        std::int32_t str = NextString(empty_str);
        for (std::int32_t i = 0; i < select_message_home; i++)
        {
            str = NextString(str);
        }
        std::int32_t y = 3;
        std::int32_t pos = select_message_home;
        for (std::int32_t i = 0; i < 17; i++)
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
                if ((noreaded_stars & static_cast<std::uint64_t>(1) << pos) == 0)
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
            std::uint8_t c = 0x44;
            if (select_message_pos == 16)
            {
                c = 0x4c;
            }
            FillAttrRect(26, 19, 1, 1, c);
            DrawSymbol32(26, 19, 95, 0);
        }

        if (select_message_home != 0 && (game_cicle_counter & 4) != 0)
        {
            std::uint8_t c = 0x44;
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

        std::int32_t n = select_message_home + select_message_pos;
        if (GetPressedKey(Key_Fire + Key_Jump + Key_Select) && n < stars_num)
        {
            noreaded_stars &= ~(static_cast<std::uint64_t>(1) << n);
            InitSFX(sfx_switch);
            last_keys = pressed_keys;
            DrawScreen(main_menu_scr, 1);
            game_mode = read_message_mode;
            read_message_home = 0;
            read_message_scroll = false;

            //инициализация сообщения
            read_message_num = n + 27;
            str = FindText(read_message_num);
            std::uint8_t q = 0;
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
            std::int32_t symbol = 0;
            for (std::int32_t j = 0; j < 8; j++)
            {
                for (std::int32_t i = 0; i < 8; i++)
                {
                    for (std::int32_t y2 = 0; y2 < 8; y2++)
                    {
                        for (std::int32_t x = 0; x < 8; x++)
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
        std::int32_t str = FindText(read_message_num);
        for (std::int32_t i = 0; i < read_message_home; i++)
        {
            str = NextString(str);
        }
        std::int32_t y = 3;
        for (std::int32_t i = 0; i < 17; i++)
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
    std::int32_t t = FindText(78);
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
                for (std::int32_t i = 0; i < 8; i++)
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
            DrawSymbol32(25, 8 + redefine_pos, static_cast<std::uint8_t>(pressed_key_symbol), 0x44);
            redefine_pos++;
        }
        pressed_key_symbol = 0;
    }
}

void Program::UpdateGraphicSettings()
{
    FillAttrRect(6, 8, 20, 8, 0x44);
    FillAttrRect(6, 10 + graphic_pos, 20, 1, 0x60);

    std::int32_t b;
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

    std::int32_t t = FindText(80);
    for (std::int32_t i = 0; i < graphics_quality; i++)
    {
        t = NextString(t);
    }
    PrintString(t, 6, 10);
    for (std::int32_t i = 0; i < 3 - graphics_quality; i++)
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

    std::int32_t t = FindText(81);
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

    std::int32_t b;
    if (release_type == classic_version)
    {
        b = 3;
        FillAttrRect(6, 9, 20, 3, 0x01);
    }
    else
    {
        b = 0;
    }

    std::int32_t t = FindText(82);
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
        for (std::int32_t i = 0; i < 8; i++)
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

        std::int32_t str = FindText(85);
        for (std::int32_t i = 0; i < player_home; i++)
        {
            str = NextString(str);
        }
        std::int32_t y = 3;
        std::int32_t pos = player_home;
        for (std::int32_t i = 0; i < 17; i++)
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
        std::int32_t n = player_home + player_pos;
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
    for (std::int32_t i = 1; i < 4; i++)
    {
        have_suit[i] = false;
    }
    current_suit = 0;
    reverse_way = false;
}

std::int32_t Program::MenuNavigation(std::int32_t current_pos, std::int32_t min, std::int32_t max)
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

void Program::LoadAnimations(const std::string &name)
{
    LoadAnimationsProject(name + "Classic.scproj");
    LoadAnimationsProject(name + "Next.scproj");
}

void Program::LoadAnimationsProject(const std::string &name)
{
    std::shared_ptr<ObjectAnimation> anim = std::make_shared<ObjectAnimation>();
    anim->Name = name;

    std::string animFileName = "./res/animations/" + name;
    BinaryStreamReader f(animFileName.c_str());

    f.ReadString(); //пропуск номера версии проекта

    //спрайты
    anim->Sprites.clear();
    std::int32_t spr_count = f.ReadInt32();
    for (std::int32_t i = 0; i < spr_count; i++)
    {
        std::shared_ptr<ObjectAnimation::Sprite> s = std::make_shared<ObjectAnimation::Sprite>();
        s->Name   = f.ReadString();
        s->Type   = f.ReadByte();
        s->Width  = f.ReadInt32();
        s->Height = f.ReadInt32();

        //монохромный спрайт с маской
        if (s->Type == 0)
        {
            s->ClassicLayer = AllocateDynamicArray<int32_t>(s->Height, s->Width);
            for (std::int32_t y = 0; y < s->Height; y++)
            {
                for (std::int32_t x = 0; x < s->Width; x++)
                {
                    s->ClassicLayer[x][y] = f.ReadInt32();
                }
            }
        }

        //255-цветный спрайт в палитре Next
        if (s->Type == 1)
        {
            s->NextLayer = AllocateDynamicArray<SdlDotNetCompat::Drawing::Color>(s->Height, s->Width);
            for (std::int32_t y = 0; y < s->Height; y++)
            {
                for (std::int32_t x = 0; x < s->Width; x++)
                {
                    s->NextLayer[x][y] = Color::FromArgb(f.ReadInt32());
                }
            }
        }
        anim->Sprites.push_back(s);
    }

    //анимации
    anim->Animations.clear();
    std::int32_t anim_count = f.ReadInt32();
    for (std::int32_t i = 0; i < anim_count; i++)
    {
        std::shared_ptr<ObjectAnimation::Animation> a = std::make_shared<ObjectAnimation::Animation>();
        a->Name = f.ReadString();

        //кадры
        std::int32_t frame_count = f.ReadInt32();
        a->Frames = std::vector<std::shared_ptr<ObjectAnimation::Frame>>();
        for (std::int32_t j = 0; j < frame_count; j++)
        {
            std::shared_ptr<ObjectAnimation::Frame> fr = std::make_shared<ObjectAnimation::Frame>();

            //композиции
            std::int32_t comp_count = f.ReadInt32();
            fr->Composition = std::vector<std::shared_ptr<ObjectAnimation::CompositionElement>>();
            for (std::int32_t k = 0; k < comp_count; k++)
            {
                std::shared_ptr<ObjectAnimation::CompositionElement> c = std::make_shared<ObjectAnimation::CompositionElement>();
                c->ElemSprite = FindSprite(f.ReadString(), anim);
                c->XOffset = f.ReadInt32();
                c->YOffset = f.ReadInt32();
                f.ReadBoolean(); //пропуск свойста View композиции
                fr->Composition.push_back(c);
            }
            fr->DX1   = f.ReadInt32();
            fr->DY1   = f.ReadInt32();
            fr->DX2   = f.ReadInt32();
            fr->DY2   = f.ReadInt32();
            fr->HX1   = f.ReadInt32();
            fr->HY1   = f.ReadInt32();
            fr->HX2   = f.ReadInt32();
            fr->HY2   = f.ReadInt32();
            fr->Time  = f.ReadInt32();
            fr->Event = f.ReadString();
            a->Frames.push_back(fr);
        }
        a->Loop = f.ReadBoolean();
        anim->Animations.push_back(a);
    }

    ObjectAnimations.push_back(anim);
}

std::shared_ptr<Program::ObjectAnimation::Sprite> Program::FindSprite(const std::string &name, const std::shared_ptr<ObjectAnimation> &anim)
{
    for (const auto &s : anim->Sprites)
    {
        if (s->Name == name)
        {
            return s;
        }
    }
    return nullptr;
}

void Program::InitAnimation(const std::shared_ptr<GameObject> &obj, const std::string &name, bool hard_enable)
{
    std::int32_t i = 0;
    for (const auto &a : obj->Animations[sprite_mode]->Animations)
    {
        if (a->Name == name && (obj->CurrentAnimation != i || hard_enable))
        {
            obj->CurrentAnimation = static_cast<std::uint8_t>(i);
            obj->Frame = 0;
            obj->AnimCounter = static_cast<std::uint8_t>(obj->Animations[sprite_mode]->Animations[i]->Frames[0]->Time);
            obj->AnimationPlayed = true;
            GetObjSize(obj);
            break;
        }
        i++;
    }
}

void Program::InitAnimation(const std::shared_ptr<GameObject> &obj, std::uint8_t id_anim, bool hard_enable)
{
    if (obj->CurrentAnimation != id_anim || hard_enable)
    {
        obj->CurrentAnimation = id_anim;
        obj->Frame = 0;
        obj->AnimCounter = static_cast<std::uint8_t>(obj->Animations[sprite_mode]->Animations[id_anim]->Frames[0]->Time);
        obj->AnimationPlayed = true;
        GetObjSize(obj);
    }
}

void Program::PlayAnimation(const std::shared_ptr<GameObject> &obj)
{
    if (!obj->AnimationPlayed || obj->NoVisible)
    {
        obj->NoInterruptAnim = false;
        return;
    }
    obj->AnimCounter--;
    if (obj->AnimCounter != 0)
    {
        return;
    }
    obj->Frame++;
    if (obj->Frame == obj->Animations[sprite_mode]->Animations[obj->CurrentAnimation]->Frames.size())
    {
        if (obj->Animations[sprite_mode]->Animations[obj->CurrentAnimation]->Loop)
        {
            obj->Frame = 0;
        }
        else
        {
            obj->Frame--;
            obj->AnimationPlayed = false;
            return;
        }
    }
    obj->AnimCounter = static_cast<std::uint8_t>(obj->Animations[sprite_mode]->Animations[obj->CurrentAnimation]->Frames[obj->Frame]->Time);
    std::string e = obj->Animations[sprite_mode]->Animations[obj->CurrentAnimation]->Frames[obj->Frame]->Event;
    GetObjSize(obj);

    //обработка событий
    DoEvent(obj, e);
}

void Program::GetObjSize(const std::shared_ptr<Program::GameObject> &obj)
{
    obj->Width = obj->Animations[sprite_mode]->Animations[obj->CurrentAnimation]->Frames[obj->Frame]->DX2;
    obj->Height = obj->Animations[sprite_mode]->Animations[obj->CurrentAnimation]->Frames[obj->Frame]->DY1;
}

std::vector<std::shared_ptr<Program::ObjectAnimation>> Program::FindObjectAnimation(const std::string &name)
{
    std::vector<std::shared_ptr<ObjectAnimation>> anim(2);
    for (const auto &a : ObjectAnimations)
    {
        if (a->Name == name + "Classic.scproj")
        {
            anim[0] = a;
        }
    }
    for (const auto &a : ObjectAnimations)
    {
        if (a->Name == name + "Next.scproj")
        {
            anim[1] = a;
        }
    }
    return anim;
}

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
    for (std::int32_t i = 0; i < 77; i++)
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
        std::int32_t name;
        std::int32_t b = current_level - 1;
        std::int32_t c = current_location - 1;
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


        std::int32_t prev_slot = start_slot;
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
        std::int32_t i = 36;
        std::int32_t m = 247;
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
    for (std::int32_t i = 0; i < 77; i++)
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
        for (std::int32_t j = 0; j < 10; j++)
        {
            for (std::int32_t i = 0; i < 16; i++)
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
                    std::int32_t x = 7;
                    std::int32_t y = 6;
                    if (current_level == 2)
                    {
                        y = 4;
                    }
                    std::int32_t t = 250;
                    for (std::int32_t j = 0; j < 3; j++)
                    {
                        for (std::int32_t i = 0; i < 2; i++)
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

void Program::InitIcon(std::int32_t command)
{
    icon_mode = command;
    std::int32_t scr = 4;
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
        std::int32_t scr = 4;
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

void Program::InitFinalBoss(std::int32_t fase)
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

void Program::ProcessingGameObject(const std::shared_ptr<GameObject> &obj)
{
    if (obj->NoActivated)
    {
        SpawnObjects(obj);
        return;
    }

    //счётчики объекта
    if (obj->UndeadCounter != 0)
    {
        obj->UndeadCounter--;
    }

    switch (obj->Name)
    {
    case idNova:
        Nova(obj);
        break;
    case idDust:
    case idExplosion:
    case idRocketSmoke:
        KillWhileStopAnimation(obj);
        break;
    case idMultiExplosions:
        MultiExplosions(obj);
        break;
    case idBlower:
        Blower(obj);
        break;
    case idBubble:
        Bubble(obj);
        break;
    case idBumerang:
        Bumerang(obj);
        break;
    case idWave:
        Wave(obj);
        break;
    case idBattery:
    case idHeart:
    case idPowerup:
    case idMiniBattery:
    case idMiniHeart:
    case idMiniPowerup:
    case idSuit:
    case idStar:
        PowerUp(obj);
        break;
    case idPlatform:
        Platform(obj);
        break;
    case idSteam:
        Steam(obj);
        break;
    case idFraction:
        Fraction(obj);
        break;
    case idDoor:
        Door(obj);
        break;
    case idTankette:
        Tankette(obj);
        break;
    case idDron:
        Dron(obj);
        break;
    case idBullet:
        Bullet(obj);
        break;
    case idSpider:
        Spider(obj);
        break;
    case idPiranha:
    case idBigPiranha:
        Piranha(obj);
        break;
    case idJelly:
        Jelly(obj);
        break;
    case idSpiderNest:
        SpiderNest(obj);
        break;
    case idBug:
        Bug(obj);
        break;
    case idGun:
        Gun(obj);
        break;
    case idDragonfly:
    case idFighterBomber:
    case idDronBomber:
        FlyEnemy(obj);
        break;
    case idAlienClawBottom:
    case idAlienClawTop:
        AlienClaw(obj);
        break;
    case idAlienWorm:
        AlienWorm(obj);
        break;
    case idSlime:
        Slime(obj);
        break;
    case idSonusVenator:
        SonusVenator(obj);
        break;

    case idBigSpider:
        BigSpider(obj);
        break;
    case idCraken:
        Craken(obj);
        break;
    case idMoth:
        Moth(obj);
        break;
    case idRocketman:
        Rocketman(obj);
        break;
    case idCrabBoss:
        CrabBoss(obj);
        break;
    case idFlyBoss:
        FlyBoss(obj);
        break;
    case idAlienPet:
        AlienPet(obj);
        break;
    case idAlienSliderman:
        AlienSliderman(obj);
        break;
    case idMegabrain:
        Megabrain(obj);
        break;

    case idRocket:
        Rocket(obj);
        break;
    case idMiniBrain:
        MiniBrain(obj);
        break;
    case idBomb:
        Bomb(obj);
        break;
    case idFlyBomb:
        FlyBomb(obj);
        break;
    case idWaterFun:
        Magnit(obj, 8, 64, 1);
        break;
    case idBubbleGenerator:
        BubbleGenerator(obj, 0, 0);
        break;

    case idJacqueline:
        DLCJacqueline(obj);
        break;
    case idDLCBullet:
        DLCBullet(obj);
        break;
    case idJDJump:
    case idJGun:
    case idJShield:
        DLCPowerUp(obj);
        break;
    case idJBubble:
        DLCBubble(obj);
        break;
    case idDragon:
        Dragon(obj);
        break;
    }
}

void Program::Nova(const std::shared_ptr<GameObject> &obj)
{
    //костыли
    if (on_roof && GetProperty(obj, -8, -44) == isEmpty && GetProperty(obj, 8, -44) == isEmpty)
    {
        on_roof = false;
    }
    if (on_wall && GetProperty(obj, 12, -36) == isEmpty)
    {
        on_wall = false;
        if (pressed_keys == Key_Up)
        {
            obj->YAccel = 0;
        }
    }

    ga = 0;
    gb = 0;

    in_water = GetProperty(obj, 0, 0) == isWater || GetProperty(obj, 0, -16) == isWater || GetProperty(obj, 0, -33) == isWater;

    bool on_air = false;
    bool is_crouch = false;

    //инициализация анимаций
    std::string anim = "Nova_Idle";

    if (!secret_boss_enabled)
    {
        if (!on_ladder && !is_fly && !on_wall && !on_roof)
        {
            on_air = Gravity(obj);
        }

        if (on_air)
        {
            if (obj->YAccel < 0)
            {
                anim = "Nova_Jump";
            }
            else
            {
                anim = "Nova_FallDown";
            }
        }
        else
        {
            is_jump = false;
        }

        //прицепление к потолку
        if (current_suit == 1 && obj->YAccel < 0)
        {
            HeroOnRoof();
        }

        //полёт
        if (is_fly)
        {
            on_air = true;
            anim = "Nova_Fly";
            if (GetKey(Key_Up) && !GetKey(Key_Jump))
            {
                FlyUp(obj);
            }
            else if (GetKey(Key_Down) && !GetKey(Key_Jump))
            {
                FlyDown(obj);
                FlyDown(obj);
            }
            else
            {
                ObjWiggle(obj);
            }

            if (GetProperty(obj, 0, -16) == isWater)
            {
                obj->haveGravity = true;
                obj->YAccel = 0;
                is_fly = false;
            }
        }

        //на стене
        if (on_wall)
        {
            anim = "Nova_WallIdle";
        }

        //на потолке
        if (on_roof)
        {
            anim = "Nova_RoofIdle";
        }

        std::int32_t xt = obj->X & 15;

        //разворот
        if (!obj->NoInterruptAnim)
        {
            if (!on_wall)
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
        }
        else
        {
            if (hero_die && !on_air)
            {
                InitAnimation(obj, "Nova_Die", false);
            }
            return;
        }

        //проверка на шипы
        if (ga == isSpike && gb == isSpike && (!is_fly || GetKey(Key_Up)))
        {
            InitHeroSpike();
            return;
        }

        if (on_ladder)
        {
            anim = "Nova_OnLadder";
        }

        //генерация пузырей, если Нова под водой
        if (GetProperty(obj, 0, obj->Height) == isWater)
        {
            BubbleGenerator(obj, 4, obj->Height);
        }

        //скольжение
        if (slide_cntr != 0)
        {
            bool in_tonnel = GetProperty(obj, -obj->Width, obj->Height - 8) == isFloor || GetProperty(obj, obj->Width, obj->Height - 8) == isFloor;
            anim = "Nova_Slide";
            if (slide_cntr != 0)
            {
                slide_cntr--;
            }

            if (current_suit != 0)
            {
                std::shared_ptr<GameObject> e = EnemyDamage(obj, 20);
                if (e != nullptr && e->Life >= 2)
                {
                    slide_cntr = 24;
                    ChangeDirection(obj);
                }
            }

            if (!MoveObjectForward(obj, 4))
            {
                //разрушаемые стены
                std::int32_t d = obj->Width + 8;
                if (obj->Direction)
                {
                    d = -d;
                }
                if ((GetFullProperty(obj, d, -1) & 0x10) != 0)
                {
                    CreateExplosion(obj, d, -1);
                    NewTile((obj->X + d) / 16, (obj->Y - 1) / 16, 0);
                }

                //разворот в тоннеле
                else if (in_tonnel)
                {
                    ChangeDirection(obj);
                }
                else
                {
                    slide_cntr = 0;
                }
            }

            if (in_tonnel && slide_cntr == 0)
            {
                slide_cntr++;
            }
            if (on_air)
            {
                slide_cntr = 0;
            }

            //объекты пыли
            if (graphics_quality == 2 && (~slide_cntr & 7) == 0 && GetProperty(obj, 0, obj->Height) != isWater)
            {
                std::shared_ptr<GameObject> o = CreateChild(obj, idDust, -8, 0);
                o->Animations = FindObjectAnimation("Nova");
                o->Fixed = true;
                InitAnimation(o, "Nova_Dust", true);
            }
        }

        else
        {
            //прыжок
            if (GetKey(Key_Jump) && !GetLastKey(Key_Jump) && (!on_air || on_ladder || on_wall || on_roof || (!is_jump && obj->YAccel < 8 && GetProperty(obj, 0, -1) != isWater)) && GetProperty(obj, -obj->Width, -1) != isFloor && GetProperty(obj, obj->Width, -1) != isFloor && (!in_water || current_suit != 2))
            {
                if (!GetKey(Key_Down))
                {
                    if (!on_roof)
                    {
                        obj->YAccel = -20;
                    }
                    on_wall = false;
                    on_roof = false;
                    is_jump = true;
                    obj->haveGravity = true;
                }
                else if (on_ladder)
                {
                    on_air = true;
                }
                on_ladder = false;
            }

            //плывёт в костюме
            if (GetKey(Key_Jump) && !GetKey(Key_Down) && current_suit == 2 && in_water)
            {
                anim = "Nova_Swim";
                std::int32_t a = GetProperty(obj, obj->Width, obj->Height - 2);
                std::int32_t b = GetProperty(obj, -obj->Width, obj->Height - 2);
                if (a != isFloor && b != isFloor)
                {
                    obj->Y--;
                    obj->YAccel = -1;
                }
                if (a == isSpike || b == isSpike)
                {
                    InitHeroSpike();
                    return;
                }

                if (GetProperty(obj, 0, -16) != isWater && GetProperty(obj, 0, -33) != isWater)
                {
                    obj->YAccel = -20;
                }
            }

            //вверх по лестнице
            if (GetKey(Key_Up))
            {
                if (!on_ladder && !is_fly && GetProperty(obj, 0, -33) == isLadder && GetProperty(obj, 0, -8) == isLadder)
                {
                    if (obj->YAccel >= -10)
                    {
                        if (xt == 7 || xt == 8)
                        {
                            obj->X = (obj->X & 0xfff0) + 8;
                            obj->Y -= 4;
                            on_ladder = true;
                            obj->YAccel = 0;
                        }
                        else
                        {
                            if (xt < 8)
                            {
                                pressed_keys = static_cast<std::uint8_t>(pressed_keys | Key_Right);
                            }
                            else
                            {
                                pressed_keys = static_cast<std::uint8_t>(pressed_keys | Key_Left);
                            }
                        }
                    }
                }
                else if (on_ladder && attack_cntr == 0)
                {
                    obj->Y--;
                    anim = "Nova_Climb";
                    if (GetProperty(obj, 0, -33) != isLadder)
                    {
                        on_ladder = false;
                    }
                }

                //начало полёта в костюме
                else if (current_suit == 3 && !in_water && !on_ladder)
                {
                    is_fly = true;
                    obj->haveGravity = false;
                }

                //ползёт вверх по стене
                else if (on_wall && !GetKey(Key_Left + Key_Right))
                {
                    std::int32_t p = GetProperty(obj, 12, -40);
                    if (p == isFloor || (p == isEmpty && GetProperty(obj, 12, -64) == isFloor))
                    {
                        if (GetProperty(obj, 0, -36) != isFloor)
                        {
                            obj->Y--;
                            anim = "Nova_WallMove";
                        }
                        HeroOnRoof();
                    }
                    else if (GetProperty(obj, obj->Width + 4, obj->Height - 26) == isEmpty || GetProperty(obj, obj->Width + 4, obj->Height - 26) == isWater)
                    {
                        obj->NoInterruptAnim = true;
                        obj->Y -= 40;
                        obj->YAccel = 0;
                        on_wall = false;
                        MoveObjectForward(obj, 8);
                        InitAnimation(obj, "Nova_WallUp", false);
                        return;
                    }

                    //проверка на шипы
                    if (GetProperty(obj, 0, -40) == isSpike)
                    {
                        InitHeroSpike();
                        return;
                    }
                }
            }

            //вниз по лестнице
            if (GetKey(Key_Down))
            {
                if (!on_ladder && !is_fly)
                {
                    if (GetProperty(obj, 0, 1) == isLadder && !on_air && !on_roof)
                    {
                        if (xt == 7 || xt == 8)
                        {
                            obj->X = (obj->X & 0xfff0) + 8;
                            obj->Y += 4;
                            on_ladder = true;
                            obj->YAccel = 0;
                        }
                        else
                        {
                            if (xt < 8)
                            {
                                pressed_keys = static_cast<std::uint8_t>(Key_Right);
                            }
                            else
                            {
                                pressed_keys = static_cast<std::uint8_t>(Key_Left);
                            }
                        }
                    }
                    else if (!on_air && !on_wall && !on_roof)
                    {
                        //инициализация скольжения
                        if (GetKey(Key_Jump) && !GetLastKey(Key_Jump) && attack_cntr == 0)
                        {
                            slide_cntr = 24;
                            anim = "Nova_Slide";
                            InitSFX(sfx_slide);
                        }

                        //приседание
                        else
                        {
                            is_crouch = true;
                            anim = "Nova_Crouch";
                        }
                    }

                    //ползёт вниз по стене
                    else if (on_wall && GetProperty(obj, 10, 0) != isSpike)
                    {
                        obj->Y++;
                        anim = "Nova_WallMove";
                        std::int32_t a = GetProperty(obj, 0, 0);
                        if (a == isFloor || a == isPlatform || a == isSpike || a == isShift)
                        {
                            on_wall = false;
                            obj->YAccel = 0;
                            obj->haveGravity = true;
                        }

                        else if (GetProperty(obj, 10, -28) != isFloor && GetProperty(obj, 10, -12) != isFloor && GetProperty(obj, 10, 4) != isFloor)
                        {
                            obj->NoInterruptAnim = true;
                            on_wall = false;
                            on_roof = true;

                            std::int32_t last_y = obj->Y;
                            obj->Y = (obj->Y & 0xfff0) + 9 + 16;
                            std::int32_t q = 16;
                            if (obj->Direction)
                            {
                                q = -16;
                            }
                            obj->X += q;
                            InitAnimation(obj, "Nova_CornerRoof", false);

                            if (GetProperty(obj, -12, 0) == isFloor || GetProperty(obj, 12, 0) == isFloor)
                            {
                                on_roof = false;
                                obj->Y = last_y;
                            }
                            return;
                        }
                    }
                }
                else if (on_ladder && attack_cntr == 0)
                {
                    obj->Y++;
                    anim = "Nova_Climb";
                    if (GetProperty(obj, 0, 1) != isLadder)
                    {
                        on_ladder = false;
                    }
                }

                //плывёт в костюме
                if (current_suit == 2 && on_air && GetProperty(obj, 0, 0) == isWater)
                {
                    obj->Y++;
                }
            }

            //инициализация бросока бумеранга
            if (GetKey(Key_Fire) && !GetLastKey(Key_Fire) && attack_cntr < 3 && hero_weapon >= 20)
            {
                attack_cntr = 11;
            }

            //движение по горизонтали
            if (GetKey(Key_Left + Key_Right) && (!on_air || !GetKey(Key_Jump) || current_suit != 3 || !is_fly))
            {
                if ((!GetKey(Key_Down) || on_air) && !on_ladder && (attack_cntr == 0 || on_air) && !on_wall)
                {
                    obj->Direction = false;
                    if (GetKey(Key_Left))
                    {
                        obj->Direction = true;
                    }

                    std::int32_t spd = 3;
                    if (on_roof)
                    {
                        spd--;
                    }
                    if (MoveObjectForward(obj, spd) || extern_move)
                    {
                        if (!on_air && !on_roof)
                        {
                            anim = "Nova_Run";
                        }
                        else if (on_roof)
                        {
                            anim = "Nova_RoofMove";
                            std::int32_t q = GetProperty(obj, 2, -48);
                            if (q != isFloor)
                            {
                                if (q != isSpike)
                                {
                                    obj->NoInterruptAnim = true;
                                    ChangeDirection(obj);
                                    on_roof = false;
                                    on_wall = true;

                                    q = 7 - 16;
                                    if (obj->Direction)
                                    {
                                        q = 8 + 16;
                                    }
                                    ;
                                    obj->X = (obj->X & 0xfff0) + q;
                                    obj->Y -= 16;

                                    InitAnimation(obj, "Nova_CornerWall", false);
                                    return;
                                }
                                else
                                {
                                    MoveObjectForward(obj, -spd);
                                    anim = "Nova_RoofIdle";
                                }
                                InitSFX(sfx_gotonthewall);
                            }
                        }
                    }
                    else if (current_suit == 1 && GetProperty(obj, 12, -40) == isFloor && GetProperty(obj, 8, -36) != isFloor)
                    {
                        std::int32_t q = 7;
                        if (obj->Direction)
                        {
                            q++;
                        }
                        obj->X = (obj->X & 0xfff0) + q;

                        on_roof = false;
                        on_wall = true;
                        obj->haveGravity = false;
                        if (obj->YAccel < 0)
                        {
                            obj->YAccel = 0;
                        }
                        InitSFX(sfx_gotonthewall);
                    }

                    //проверка на шипы
                    if (GetProperty(obj, 9, -4) == isSpike)
                    {
                        InitHeroSpike();
                        return;
                    }
                }
                else
                {
                    if (!GetLastKey(Key_Left + Key_Right) && on_wall && GetProperty(obj, -obj->Width - 4, obj->Height - 8) == isFloor && GetProperty(obj, -obj->Width - 4, obj->Height + 8) == isFloor)
                    {
                        ChangeDirection(obj);
                        std::int32_t q = 7;
                        if (obj->Direction)
                        {
                            q++;
                        }
                        obj->X = (obj->X & 0xfff0) + q;
                    }
                }
            }
        }
    }

    else
    {
        ObjWiggle(obj);

        //инициализация броска бумеранга
        if (GetKey(Key_Fire) && !GetLastKey(Key_Fire) && attack_cntr < 3 && hero_weapon >= 20)
        {
            attack_cntr = 11;
        }

        if (GetKey(Key_Left + Key_Right))
        {
            obj->Direction = false;
            if (GetKey(Key_Left))
            {
                obj->Direction = true;
            }
            MoveObjectForward(obj, 2);
        }
        if (GetKey(Key_Down))
        {
            FlyDown(obj);
        }
        if (GetKey(Key_Up))
        {
            FlyUp(obj);
        }

        on_air = true;
        anim = "Nova_FallDown";
    }

    //обработка броска бумеранга
    if (attack_cntr != 0)
    {
        anim = "Nova_Attack";
        std::int32_t xw = 10;
        std::int32_t yw = -20;
        std::int32_t xd = 5;
        std::int32_t yd = 0;
        std::int32_t dir = 2;
        if (GetKey(Key_Left + Key_Right))
        {
            if (GetKey(Key_Up))
            {
                xd = 4;
                yd = -4;
                dir = 1;
            }

            if (GetKey(Key_Down))
            {
                xd = 4;
                yd = 4;
                dir = 3;
            }
        }

        if (on_wall)
        {
            anim = "Nova_WallAttack";
            xw = -xw;
            xd = -xd;
        }

        if (on_air)
        {
            anim = "Nova_JumpAttack";
        }
        if (is_crouch)
        {
            anim = "Nova_CrouchAttack";
            yw = -10;
        }
        if (on_ladder || on_roof)
        {
            anim = "Nova_LadderAttack";
        }
        if (GetKey(Key_Up) && !GetKey(Key_Left + Key_Right))
        {
            anim = "Nova_UpAttack";
            xw = 0;
            yw = -33;
            xd = 0;
            yd = -5;
            dir = 0;
        }
        if (GetKey(Key_Down) && !GetKey(Key_Left + Key_Right) && (on_air || on_ladder || on_wall || on_roof))
        {
            if (!on_roof)
            {
                anim = "Nova_DownAttack";
            }
            else
            {
                anim = "Nova_RoofAttack";
            }
            xw = 0;
            yw = 0;
            xd = 0;
            yd = 5;
            dir = 4;
        }

        //создание бумеранга
        if (attack_cntr == 3)
        {
            if (obj->Direction)
            {
                xd = -xd;
            }

            if (current_suit == 0)
            {
                std::shared_ptr<GameObject> o = CreateChild(obj, idBumerang, xw, yw);
                o->XTarget = o->X + xd * 16;
                o->YTarget = o->Y + yd * 16;
                o->Status = 0;
                o->YAccel = 16;
                o->Animations = FindObjectAnimation("Nova");
                InitAnimation(o, "Nova_Bumerang", true);
                InitSFX(sfx_bumerang);
            }
            else
            {
                std::shared_ptr<GameObject> o = CreateChild(obj, idWave, xw, yw);
                if (on_wall)
                {
                    o->Direction = !o->Direction;
                }
                o->XTarget = xd;
                o->YTarget = yd;
                o->Counter = 24;
                o->Animations = FindObjectAnimation("Suit");
                o->Fixed = true;
                InitAnimation(o, "Nova_Wave" + std::to_string(dir), true);
                InitSFX(sfx_wave);
            }

            //уменьшение шкалы оружия
            hero_weapon -= 20;
            if (hero_weapon < 0)
            {
                hero_weapon = 0;
            }
            hero_weapon_current = hero_weapon;
            SetScale(19, 182, hero_weapon);
        }

        anim += std::to_string(attack_cntr / 3);
        attack_cntr--;
    }

    InitAnimation(obj, anim, false);
    extern_move = false;
}

void Program::DLCJacqueline(const std::shared_ptr<GameObject> &obj)
{
    obj->Priority = high_priority;
    bool on_air = true;
    if (on_ladder == false)
    {
        on_air = Gravity(obj);
        if (on_air == false)
        {
            is_jump = false;
            is_double_jump = false;
        }
    }

    if (obj->NoInterruptAnim == true)
    {
        return;
    }

    std::string anim = "JIdle";
    bool hard_anim = false;

    if (on_ladder == true)
    {
        anim = "J_OnLadder";
    }

    in_water = GetProperty(obj, 0, 0) == isWater || GetProperty(obj, 0, -16) == isWater || GetProperty(obj, 0, -33) == isWater;

    if (GetKey(Key_Jump) == true && GetLastKey(Key_Jump) == false && (is_jump == false || (is_double_jump == false && double_jump_on == true && in_water == false)))
    {
        if (GetKey(Key_Down) == false)
        {
            if (on_air == false || (obj->YAccel > 0 && obj->YAccel < 5) || on_ladder == true)
            {
                obj->YAccel = -20;
            }
            else if (double_jump_on == true && in_water == false)
            {
                obj->YAccel = -20;
                is_jump = true;
            }
        }
        on_ladder = false;
        if (is_jump == true)
        {
            is_double_jump = true;
        }
        is_jump = true;
    }

    std::int32_t xt = obj->X & 15;

    //вверх по лестнице
    if (GetKey(Key_Up))
    {
        if (!on_ladder)
        {
            if (GetProperty(obj, 0, -33) == isLadder && GetProperty(obj, 0, -8) == isLadder)
            {
                if (obj->YAccel >= -10)
                {
                    if (xt == 7 || xt == 8)
                    {
                        obj->X = (obj->X & 0xfff0) + 8;
                        obj->Y -= 4;
                        on_ladder = true;
                        obj->YAccel = 0;
                        is_jump = false;
                        is_double_jump = false;
                    }
                    else
                    {
                        if (xt < 8)
                        {
                            pressed_keys = static_cast<std::uint8_t>(pressed_keys | Key_Right);
                        }
                        else
                        {
                            pressed_keys = static_cast<std::uint8_t>(pressed_keys | Key_Left);
                        }
                    }
                }
            }
        }
        else
        {
            obj->Y--;
            if (GetProperty(obj, 0, -33) != isLadder)
            {
                on_ladder = false;
            }
            anim = "J_LadderMove";
        }
    }

    //вниз по лестнице
    if (GetKey(Key_Down))
    {
        if (!on_ladder)
        {
            if (GetProperty(obj, 0, 1) == isLadder && !on_air && obj->YAccel == 0)
            {
                if (xt == 7 || xt == 8)
                {
                    obj->X = (obj->X & 0xfff0) + 8;
                    obj->Y += 4;
                    on_ladder = true;
                    obj->YAccel = 0;
                    is_jump = false;
                    is_double_jump = false;
                }
                else
                {
                    if (xt < 8)
                    {
                        pressed_keys = static_cast<std::uint8_t>(Key_Right);
                    }
                    else
                    {
                        pressed_keys = static_cast<std::uint8_t>(Key_Left);
                    }
                }
            }
            else
            {
                anim = "J_Sitting";
            }
        }
        else
        {
            obj->Y++;
            if (GetProperty(obj, 0, 1) != isLadder)
            {
                on_ladder = false;
            }
            anim = "J_LadderMove";
        }
    }

    if (GetKey(Key_Left + Key_Right))
    {
        obj->Direction = false;
        if (GetKey(Key_Left))
        {
            obj->Direction = true;
        }

        std::int32_t speed = 3;
        if (in_water)
        {
            speed = 2;
        }

        if ((attack_cntr == 0 || on_air) && (GetKey(Key_Down) == false || on_air == true) && on_ladder == false && MoveObjectForward(obj, speed))
        {
            anim = "JRun";
        }
    }

    if (on_air == true && on_ladder == false)
    {
        if (obj->YAccel < 0)
        {
            if (is_double_jump == false)
            {
                anim = "J_Jump";
            }
            else
            {
                anim = "J_DJump";
            }
        }
        else
        {
            anim = "J_Fall_Down";
        }
    }

    //инициализация выстрела
    if (gun_on == true && attack_cntr == 0 && GetKey(Key_Fire) == true && hero_weapon >= 30 && GetLastKey(Key_Fire) == false)
    {
        attack_cntr = 11;
    }

    //обработка выстрела
    if (attack_cntr != 0)
    {
        std::int32_t high = -26;
        if (on_air || on_ladder)
        {
            anim = "JJumpShoot";
        }
        else
        {
            if (GetKey(Key_Down))
            {
                anim = "JSittingShoot";
                high = -16;
            }
            else
            {
                anim = "JShoot";
            }
        }

        //создание пули
        if (attack_cntr == 3)
        {
            std::shared_ptr<GameObject> o = CreateChild(obj, idDLCBullet, 14, high);
            o->Animations = obj->Animations;
            InitAnimation(o, "JBullet", true);
            InitSFX(sfx_stungun);
            o->Counter = 24;

            //уменьшение шкалы оружия
            hero_weapon -= 30;
            if (hero_weapon < 0)
            {
                hero_weapon = 0;
            }
            hero_weapon_current = hero_weapon;
            SetScale(19, 182, hero_weapon);
        }

        anim += std::to_string(attack_cntr / 3);
        attack_cntr--;
    }

    InitAnimation(obj, anim, hard_anim);

    //проверка на шипы
    if (GetProperty(obj, 9, -4) == isSpike || GetProperty(obj, -9, -4) == isSpike || GetProperty(obj, 0, 1) == isSpike || GetProperty(obj, 0, -34) == isSpike)
    {
        hero_energy -= 16;
        if (hero_energy < 0)
        {
            hero_energy = 0;
        }
        InitHeroSpike();
        return;
    }
}

void Program::PowerUp(const std::shared_ptr<GameObject> &obj)
{
    Gravity(obj);

    if (GetProperty(obj, 0, 1) == isSpike)
    {
        CreateExplosion(obj, 0, 0);
        RemoveObject(obj);
        return;
    }

    obj->Counter++;
    if (obj->Counter == 128)
    {
        obj->Counter = 0;
    }

    std::int32_t i = obj->Type & 0x7f;
    if (obj->Counter >= 113)
    {
        i += (obj->Counter & 15) / 4;
    }
    obj->XAccel = i;

    std::int32_t d = 5;
    std::int32_t e = 20;
    if (difficulty != 0)
    {
        d = 6;
        e = 22;
    }

    if (hero_life != 0 && InRange(obj->X, hero_object->X, 12) && InRange(obj->Y, hero_object->Y, 12))
    {
        switch (obj->Name)
        {
        case idBattery:
            hero_energy += e;
            if (hero_energy >= 78)
            {
                hero_energy = 77;
            }
            break;
        case idMiniBattery:
            hero_energy += d;
            if (hero_energy >= 78)
            {
                hero_energy = 77;
            }
            break;
        case idHeart:
            hero_life += e;
            if (hero_life >= 78)
            {
                hero_life = 77;
            }
            break;
        case idMiniHeart:
            hero_life += d;
            if (hero_life >= 78)
            {
                hero_life = 77;
            }
            break;
        case idPowerup:
            hero_weapon_max += e;
            if (hero_weapon_max >= 78)
            {
                hero_weapon_max = 77;
            }
            break;
        case idMiniPowerup:
            hero_weapon_max += d;
            if (hero_weapon_max >= 78)
            {
                hero_weapon_max = 77;
            }
            break;
        case idStar:
            collected_stars |= (static_cast<std::uint64_t>(1) << obj->Status);
            stars_num++;
            noreaded_stars |= (static_cast<std::uint64_t>(1) << (stars_num - 1));
            DrawScreen(statusbar, 14);
            InitSFX(sfx_star);
            RemoveObject(obj);
            PauseGameMusic();
            SaveProgress();
            pause_cnt = 100;
            FullRoomRedraw();
            return;
        case idSuit:
            have_suit[current_level] = true;
            location_status++;
            location_counter = 100;
            break;
        }
        RemoveObject(obj);
        InitSFX(sfx_powerup);
    }
}

void Program::KillWhileStopAnimation(const std::shared_ptr<GameObject> &obj)
{
    if (!obj->AnimationPlayed)
    {
        RemoveObject(obj);
    }
    if (secret_boss_enabled)
    {
        obj->Y--;
    }
}

void Program::MultiExplosions(const std::shared_ptr<GameObject> &obj)
{
    if (obj->Counter == 0)
    {
        RemoveObject(obj);
        location_status++;
        location_counter = 100;
    }

    obj->Counter--;

    std::int32_t x = rnd->Next() & 31 - 15;
    std::int32_t y = rnd->Next() & 31 - 15;
    if ((obj->Counter & 15) == 0)
    {
        CreateExplosion(obj, x, y);
    }
}

void Program::Blower(const std::shared_ptr<GameObject> &obj)
{
    obj->Counter = (obj->Counter + 1) & 0xff;
    if (obj->Counter < 128 || obj->Status == 0)
    {
        std::int32_t x = obj->XTile;
        std::int32_t y = obj->YTile;
        std::int32_t i = game_cicle_counter / 2;
        if ((obj->Counter < 20 || obj->Counter >= 104) && obj->Status != 0)
        {
            i = i / 2;
        }
        else if (hero_life != 0 && !on_wall && !on_roof && InRange(hero_object->X, obj->X + 16, 24) && GetYDistance(obj) < 80 && obj->Y >= hero_object->Y)
        {
            FlyUp(hero_object);
            if (hero_object->YAccel < 0)
            {
                hero_object->YAccel--;
            }
            else
            {
                hero_object->YAccel = -1;
            }
            ObjWiggle(hero_object);

            //проверка на шипы
            if (GetProperty(hero_object, 0, -41) == isSpike && !hero_die)
            {
                InitHeroSpike();
                return;
            }
        }
        i = (i & 3) * 3;

        NewTile(x, y, 32 + i);
        NewTile(x + 1, y, 33 + i);
        NewTile(x + 2, y, 34 + i);
    }
}

void Program::Bubble(const std::shared_ptr<GameObject> &obj)
{
    if ((game_cicle_counter & 15) == 0)
    {
        if ((game_cicle_counter & 16) == 0)
        {
            obj->X--;
        }
        else
        {
            obj->X++;
        }
    }
    if (obj->YAccel == 1 || (game_cicle_counter & 1) == 0)
    {
        obj->Y -= 1;
    }

    if (GetProperty(obj, 0, -8) != isWater || !InCurrentRoom(obj))
    {
        RemoveObject(obj);
        particle_cntr--;
    }
}

void Program::Bumerang(const std::shared_ptr<GameObject> &obj)
{
    if (std::max(std::abs(obj->X - obj->XTarget), std::abs(obj->Y - obj->YTarget)) < 29)
    {
        if (obj->YAccel >= 2 && obj->Status == 0)
        {
            obj->YAccel--;
        }
    }
    else
    {
        if (obj->YAccel < 16)
        {
            obj->YAccel++;
        }
    }

    std::int32_t speed = std::min(4, obj->YAccel / 4);
    if (obj->X != obj->XTarget && obj->Y != obj->YTarget)
    {
        speed = std::min(3, speed);
    }

    if (obj->X < obj->XTarget)
    {
        obj->X += speed;
    }
    if (obj->X >= obj->XTarget + 1)
    {
        obj->X -= speed;
    }
    if (obj->Y < obj->YTarget)
    {
        obj->Y += speed;
    }
    if (obj->Y >= obj->YTarget + 1)
    {
        obj->Y -= speed;
    }

    if (std::abs(obj->X - obj->XTarget) < 5 && std::abs(obj->Y - obj->YTarget) < 5)
    {
        obj->XTarget = hero_object->X;
        obj->YTarget = hero_object->Y + hero_object->Height + 8;
        obj->Status = 1;
    }

    //вернулся к Нове или попал во врага
    if ((InRange(obj->X, hero_object->X, 12) && InRange(obj->Y, hero_object->Y - 16, 12) && obj->Status != 0) || EnemyDamage(obj, 17) != nullptr)
    {
        RemoveObject(obj);
    }

    //Нова умер
    if (hero_life == 0)
    {
        CreateExplosion(obj, 0, 0);
        RemoveObject(obj);
    }

    //столкнулся со стеной
    std::int32_t a = GetProperty(obj, 0, 0);
    if (a == isFloor || a == isShift || a == isSpike)
    {
        if (a == isFloor && (GetFullProperty(obj, 0, 0) & 0x10) != 0)
        {
            CreateExplosion(obj, 0, 0);
            NewTile(obj->X / 16, obj->Y / 16, 0);
        }
        else if (!secret_boss_enabled)
        {
            CreateFractions(obj, 3);
            InitSFX(sfx_missshoot);
        }
        RemoveObject(obj);
        return;
    }
}

void Program::Wave(const std::shared_ptr<GameObject> &obj)
{
    EnemyDamage(obj, 17);

    if (obj->Counter != 0)
    {
        obj->Counter--;
    }
    if (obj->Counter == 0)
    {
        RemoveObject(obj);
        return;
    }

    //разрушаемые тайлы
    if (!in_boss_room)
    {
        std::int32_t x = obj->X / 16;
        std::int32_t y = obj->Y / 16;

        if (x < 1 || x >= 127)
        {
            x = 126;
        }
        if (y < 1 || y >= 57)
        {
            y = 56;
        }
        x--;
        y--;
        std::int32_t dx = -16;
        std::int32_t dy = -16;
        for (std::int32_t j = 0; j < 3; j++)
        {
            for (std::int32_t i = 0; i < 3; i++)
            {
                std::int32_t p = TilesetProperty[ Loc[x][y] ];
                if (((p >> 5) & 7) == isFloor && (p & 0x10) != 0)
                {
                    CreateExplosion(obj, dx, dy);
                    NewTile(x, y, 0);
                }
                x++;
                dx += 16;
            }
            x -= 3;
            dx = -16;
            y++;
            dy += 16;
        }
    }

    obj->X += obj->XTarget;
    obj->Y += obj->YTarget;
}

void Program::Platform(const std::shared_ptr<GameObject> &obj)
{
    std::int32_t xoffset = 0;
    std::int32_t yoffset = 0;

    //движение по рельсам
    if (obj->XAccel != 0)
    {
        //определение стороны движения
        if (obj->Counter == 0)
        {
            if (!GetRailsTile(obj))
            {
                obj->YAccel++;
            }
            if (!GetRailsTile(obj))
            {
                obj->YAccel -= 2;
            }
            if (!GetRailsTile(obj))
            {
                obj->YAccel--;
            }
            obj->YAccel = obj->YAccel & 3;
            obj->Counter = 16;
        }

        //движение по направлению
        obj->Counter--;
        if (obj->YAccel == 0)
        {
            yoffset = -1;
        }
        else if (obj->YAccel == 1)
        {
            xoffset = 1;
        }
        else if (obj->YAccel == 2)
        {
            yoffset = 1;
        }
        else
        {
            xoffset = -1;
        }
    }

    //поиск объектов на платформе
    if (GetXDistance(obj) != 255 && GetYDistance(obj) != 159)
    {
        for (const auto &o : actual_objects)
        {
            bool have_garvity = o->haveGravity || (o->Name == idNova && current_suit == 3 && GetKey(Key_Down));
            if (have_garvity && std::abs(o->Y - obj->Y) < 8 && o->Y >= obj->Y && obj->Y >= o->Y + o->Height && obj->X + obj->Width >= o->X - o->Width && o->X + o->Width >= obj->X - obj->Width)
            {
                //включение движения
                if (obj->XAccel == 0 && (o->Name == idNova || o->Name == idJacqueline) && o->YAccel == 0)
                {
                    InitAnimation(obj, "Platform_Move", false);

                    obj->XAccel = 255;
                    obj->Fixed = false;

                    //поиск и уничтожение парной платформы
                    for (const auto &obj2 : game_objects)
                    {
                        if (obj2->Name == idPlatform && obj != obj2 && obj->Status == obj2->Status)
                        {
                            RemoveObject(obj2);
                        }
                    }
                }

                o->PlatformObject = obj;
                if (o->YAccel >= 1)
                {
                    o->YAccel = 0;
                }
                o->Y = obj->Y + yoffset;
                std::int32_t a = (GetFullProperty(o, o->Width + 1, o->Height) >> 5) & 7;
                std::int32_t b = (GetFullProperty(o, o->Width + 1, -1) >> 5) & 7;
                std::int32_t c = (GetFullProperty(o, -o->Width - 1, o->Height) >> 5) & 7;
                std::int32_t d = (GetFullProperty(o, -o->Width - 1, -1) >> 5) & 7;
                if ((xoffset >= 1 && a != isFloor && b != isFloor) || (xoffset < 0 && c != isFloor && d != isFloor))
                {
                    o->X += xoffset;
                }

                if (o->Name == idNova && GetKey(Key_Down))
                {
                    o->haveGravity = true;
                    o->YAccel = 0;
                    is_fly = false;
                }
            }
            else if (o->PlatformObject == obj)
            {
                o->PlatformObject = nullptr;
            }
        }
    }

    obj->X += xoffset;
    obj->Y += yoffset;
}

void Program::Steam(const std::shared_ptr<GameObject> &obj)
{
    if (obj->Counter == 0)
    {
        obj->Counter = obj->Status;
        InitAnimation(obj, "Steam", true);
        InitSFX(sfx_steam);
        obj->NoVisible = false;
    }
    else
    {
        obj->Counter--;
    }

    if (!obj->AnimationPlayed)
    {
        obj->NoVisible = true;
    }
}

void Program::Fraction(const std::shared_ptr<GameObject> &obj)
{
    if (!secret_boss_enabled)
    {
        Gravity(obj);
    }
    else
    {
        obj->Y--;
    }
    MoveObjectForward(obj, 1);
    if (obj->Counter != 0)
    {
        obj->Counter--;
    }
    std::int32_t i = GetProperty(obj, 0, 0);
    if (i == isFloor || i == isSpike || i == isPlatform || i == isShift || obj->Counter == 0)
    {
        RemoveObject(obj);
        particle_cntr--;
    }
}

void Program::Door(const std::shared_ptr<GameObject> &obj)
{
    if (room_cntr == 1 && obj->Counter != 0)
    {
        if (obj->Counter == 100)
        {
            InitIcon(im_noise);
        }
        obj->Counter--;
        if (obj->Counter == 0)
        {
            InitAnimation(obj, "Door_Open", false);
            InitSFX(sfx_dooropen);
        }
        return;
    }

    if (obj->Status == 0 || (obj->Status == 2 && have_suit[current_level]))
    {
        return;
    }

    std::int32_t d = GetXDistance(obj);
    if (GetKey(Key_Up) == true && d < 16 && GetYDistance(obj) < 3)
    {
        hero_object->Y = obj->Y;
        if (d >= 2)
        {
            if (!ObjCentrum(obj, 0))
            {
                Nova(hero_object);
            }
        }
        else if (!obj->AnimationPlayed)
        {
            InitAnimation(obj, "Door_Open", true);
            InitAnimation(hero_object, "Nova_Idle", true);
            disable_control = true;
            is_fly = false;
            MuteAllMusic();
            InitSFX(sfx_dooropen);
        }
    }
}

void Program::Tankette(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (!obj->isDamageable)
    {
        obj->isDamageable = true;
        obj->UndeadCounter = 15;
        CreateExplosion(obj, 0, 0);

        if (!SeeOnHero(obj) && GetYDistance(obj) < 16)
        {
            TurnObject(obj);
            InitAnimation(obj, "Tankette_Turn", false);
            obj->NoInterruptAnim = true;
        }

        obj->Life--;
        if (obj->Life == 0)
        {
            CreateMiniBonus(obj);
            RemoveObject(obj);
        }
        return;
    }

    //проверка на шипы и воду
    if (EnemyWaterSpikeTest(obj))
    {
        return;
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    if (obj->NoInterruptAnim)
    {
        return;
    }

    std::string anim = "Tankette_Move";
    bool hard_anim = false;
    bool can_shoot = TestShoot(obj, 0, -18, 0);

    if (can_shoot || obj->Counter != 0)
    {
        if (obj->Status == 0)
        {
            obj->Status++;
            anim = "Tankette_Activate";
            obj->Counter = 4;
        }
        else
        {
            anim = "Tankette_Shoot";
            hard_anim = true;
        }
        obj->NoInterruptAnim = true;
    }
    else
    {
        if (obj->Status != 0)
        {
            obj->Status--;
            anim = "Tankette_Dectivate";
            obj->NoInterruptAnim = true;
        }

        else if (!SimpleMoveObjectForward(obj, 2) || GetProperty(obj, 16, 1) == isEmpty || GetProperty(obj, 16, 1) == isWater)
        {
            anim = "Tankette_Turn";
            obj->NoInterruptAnim = true;
            ChangeDirection(obj);
        }
    }

    InitAnimation(obj, anim, hard_anim);

    if (obj->Counter != 0)
    {
        obj->Counter--;
    }
}

void Program::Dron(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (!obj->isDamageable && !obj->haveGravity)
    {
        CreateExplosion(obj, 0, 0);
        obj->haveGravity = true;
        obj->isDamageable = true;
        InitAnimation(obj, "Dron_Idle", true);
        return;
    }

    if (obj->haveGravity)
    {
        MoveObjectForward(obj, 2);
        if (!Gravity(obj))
        {
            CreateExplosion(obj, 0, 0);
            CreateMiniBonus(obj);
            RemoveObject(obj);
        }
        return;
    }

    //проверка на шипы и воду
    if (EnemyWaterSpikeTest(obj))
    {
        return;
    }

    //столкновение с героем
    else
    {
        HeroDamage(obj, 0);
    }

    if (obj->Status == 0 && obj->AnimationPlayed)
    {
        return;
    }

    ObjWiggle(obj);

    if (obj->NoInterruptAnim)
    {
        return;
    }

    std::string anim = "Dron_Move";
    bool hard_anim = false;

    //появление дрона
    if (obj->Status == 0)
    {
        obj->Status++;
        anim = "Dron_Idle";
        MoveObjectForward(obj, 10);
        obj->Y += 3;
    }

    //патрулирование
    else if (obj->Status == 1)
    {

        if (!obj->haveGravity && TestShoot(obj, -16, 0, 0))
        {
            anim = "Dron_Shoot0";
            obj->NoInterruptAnim = true;
            hard_anim = true;
        }

        else if (!obj->haveGravity && TestShoot(obj, 0, 0, 3))
        {
            anim = "Dron_Shoot1";
            obj->NoInterruptAnim = true;
            hard_anim = true;
            obj->Status++;
        }

        else if (!MoveObjectForward(obj, 2))
        {
            anim = "Dron_Turn";
            obj->NoInterruptAnim = true;
            ChangeDirection(obj);
            obj->Status++;
        }
    }

    //снижение или взлёт на уровень героя
    else if (obj->Status == 2)
    {
        if (SeeOnHero(obj))
        {
            std::int32_t h = obj->Y - hero_object->Y + 16;
            if (h < 0)
            {
                if (!FlyDown(obj))
                {
                    obj->Status = 1;
                }
            }
            else if (h == 0)
            {
                obj->Status = 1;
            }
            else
            {
                if (!FlyUp(obj))
                {
                    obj->Status = 1;
                }
            }
        }
        else
        {
            if (GetXDistance(obj) >= 32)
            {
                TurnObject(obj);
                anim = "Dron_Turn";
                obj->NoInterruptAnim = true;
            }
            obj->Status = 1;
        }
    }

    InitAnimation(obj, anim, hard_anim);
}

void Program::Bullet(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (!obj->isDamageable && obj->haveGravity)
    {
        CreateExplosion(obj, 0, 0);
        RemoveObject(obj);
        return;
    }

    //столкновение с героем
    if (HeroDamage(obj, 0))
    {
        RemoveObject(obj);
        return;
    }

    if (!obj->Direction)
    {
        obj->X += obj->XTarget;
    }
    else
    {
        obj->X -= obj->XTarget;
    }
    obj->Y += obj->YTarget;

    if (GetProperty(obj, 0, 0) == isFloor)
    {
        CreateFractions(obj, 4);
        RemoveObject(obj);
        InitSFX(sfx_missshoot);
    }

    if (!InCurrentRoom(obj))
    {
        RemoveObject(obj);
    }
}

void Program::Spider(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (!obj->isDamageable)
    {
        //генерируем бонус, если паук предустановлен
        if (obj->haveGravity)
        {
            CreateMiniBonus(obj);
        }

        CreateExplosion(obj, 0, 0);
        RemoveObject(obj);
        return;
    }

    //проверка на шипы и воду
    if (EnemyWaterSpikeTest(obj))
    {
        return;
    }

    bool on_air = Gravity(obj);

    if (!SimpleMoveObjectForward(obj, 3))
    {
        if (!on_air)
        {
            if (hero_object->Y >= obj->Y)
            {
                ChangeDirection(obj);
            }
            else
            {
                obj->YAccel = -20;
                obj->Counter++;
            }
        }
    }
    else
    {
        if (hero_object->Y < obj->Y + 1 && !on_air && SeeOnHero(obj))
        {
            if (GetXDistance(obj) < 16 || GetProperty(obj, 16, 1) == isEmpty)
            {
                obj->YAccel = -20;
                obj->Counter++;
            }
        }
    }


    //столкновение с героем
    if (HeroDamage(obj, 0) || hero_life == 0 || obj->Counter >= 3)
    {
        CreateExplosion(obj, 0, 0);
        RemoveObject(obj);
    }
}

void Program::Piranha(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (!obj->isDamageable)
    {
        obj->NoInterruptAnim = false;
        CreateExplosion(obj, 0, 0);
        obj->Life--;
        if (obj->Life != 0)
        {
            obj->UndeadCounter = 15;
            obj->isDamageable = true;
        }
        else
        {
            CreateExplosion(obj, 0, 0);
            CreateMiniBonus(obj);
            RemoveObject(obj);
            return;
        }
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    std::string anim = "SmallPiranha_Swim";
    if (obj->Name == idBigPiranha)
    {
        anim = "Piranha_Swim";
    }
    std::int32_t speed = 2;

    if (SeeOnHero(obj) && GetXDistance(obj) < 64 && GetYDistance(obj) < 32)
    {
        anim = "SmallPiranha_Attack";
        if (obj->Name == idBigPiranha)
        {
            anim = "Piranha_Attack";
        }
        speed = 4;

        if (obj->Y >= hero_object->Y + 1)
        {
            if (GetProperty(obj, 0, -20) == isWater)
            {
                FlyUp(obj);
            }
        }
        else
        {
            FlyDown(obj);
        }
    }

    if (!SimpleMoveObjectForward(obj, speed))
    {
        ChangeDirection(obj);
    }

    InitAnimation(obj, anim, false);
}

void Program::Jelly(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (!obj->isDamageable)
    {
        obj->NoInterruptAnim = false;
        CreateExplosion(obj, 0, 0);
        obj->Life--;
        if (obj->Life != 0)
        {
            obj->UndeadCounter = 15;
            obj->isDamageable = true;
        }
        else
        {
            CreateExplosion(obj, 0, 0);
            CreateMiniBonus(obj);
            RemoveObject(obj);
            return;
        }
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    //взрыв на воздухе
    if (GetProperty(obj, 0, -20) == isEmpty)
    {
        obj->isDamageable = false;
        obj->Life = 1;
    }

    //отмена прыжка при выходе из воды
    if (GetProperty(obj, 0, obj->Height) != isWater && obj->YAccel < 0)
    {
        obj->YAccel = 0;
    }

    if (obj->NoInterruptAnim)
    {
        return;
    }

    std::string anim = "";
    bool on_air = Gravity(obj);
    if (!on_air)
    {
        if (obj->Counter != 0)
        {
            obj->Counter--;
            anim = "Jelly_Idle";
        }
        else
        {
            obj->Counter = 100;
            if (obj->Status == 0 && obj->Y >= hero_object->Y + 1)
            {
                anim = "Jelly_Fire";
            }
            else
            {
                TurnObject(obj);
                anim = "Jelly_Jump";
                obj->YAccel = -25;
            }

            obj->NoInterruptAnim = true;
            obj->Status++;
            if (obj->Status >= 3)
            {
                obj->Status = 0;
            }
        }

    }
    else if (obj->YAccel >= 0)
    {
        if ((game_cicle_counter & 1) == 0)
        {
            FlyUp(obj);
        }
        anim = "Jelly_Swim";
        MoveObjectForward(obj, 1);
    }

    if (anim != "")
    {
        InitAnimation(obj, anim, false);
    }
}

void Program::SpiderNest(const std::shared_ptr<GameObject> &obj)
{
    std::int32_t x = obj->XTile - 1;
    std::int32_t y = obj->YTile - 2;

    //повреждение
    if (!obj->isDamageable)
    {
        obj->isDamageable = true;
        obj->UndeadCounter = 15;
        CreateExplosion(obj, 0, 0);
        obj->Life--;

        if (obj->Life == 0)
        {
            NewTile(x, y, 0);
            NewTile(x + 1, y + 1, 0);
            NewTile(x, y + 1, 0);
            NewTile(x + 1, y, 0);
            CreateMiniBonus(obj);
            RemoveObject(obj);
        }
        return;
    }

    std::int32_t i = (game_cicle_counter >> 2) & 3;
    NewTile(x, y, 21 + i);
    NewTile(x + 1, y, 25);
    NewTile(x, y + 1, 26 + ((i >> 1) & 1));
    NewTile(x + 1, y + 1, 28 + i);

    if (obj->Counter != 0)
    {
        obj->Counter--;
    }

    //считаем кол-во пауков на экране
    std::int32_t c = 0;
    for (const auto &o : actual_objects)
    {
        if (o->Name == idSpider)
        {
            c++;
        }
    }

    //рожаем паука
    if (c < 3 && obj->Counter == 0 && hero_life != 0)
    {
        std::shared_ptr<GameObject> o = CreateChild(obj, idSpider, 0, 16);
        o->Animations = FindObjectAnimation("Spider");
        InitAnimation(o, "Spider_Run", true);
        o->Priority = normal_priority;
        o->isDamageable = true;
        TurnObject(o);
        obj->Counter = 100;
    }
}

void Program::Bug(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (!obj->isDamageable)
    {
        obj->isDamageable = true;
        CreateExplosion(obj, 0, -16);
        obj->Life--;
        if (obj->Life == 0)
        {
            CreateMiniBonus(obj);
            RemoveObject(obj);
        }
        else
        {
            obj->UndeadCounter = 15;
        }
        return;
    }

    //проверка на шипы и воду
    if (EnemyWaterSpikeTest(obj))
    {
        return;
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    if (obj->NoInterruptAnim)
    {
        return;
    }

    std::string anim = "Bug_Idle";
    bool on_air = Gravity(obj);

    if (obj->Status == 0)
    {
        if (GetXDistance(obj) < 128)
        {
            obj->Status++;
        }
    }

    else
    {
        if (!SimpleMoveObjectForward(obj, 2))
        {
            ChangeDirection(obj);
        }
        if (on_air)
        {
            anim = "Bug_Roll";
        }
        else
        {
            anim = "Bug_Run";
        }
    }

    InitAnimation(obj, anim, false);
}

void Program::Gun(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (!obj->isDamageable)
    {
        obj->isDamageable = true;
        obj->UndeadCounter = 15;
        CreateExplosion(obj, 0, 0);
        obj->Life--;
        if (obj->Life == 0)
        {
            CreateMiniBonus(obj);
            RemoveObject(obj);
        }
        return;
    }

    if (obj->NoInterruptAnim)
    {
        return;
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    std::string anim = "Gun_Idle";
    bool hard_anim = false;


    if (!SeeOnHero(obj))
    {
        anim = "Gun_Turn";
        hard_anim = true;
        obj->NoInterruptAnim = true;
        ChangeDirection(obj);
    }
    else if ((game_cicle_counter & 15) == 0 && (game_cicle_counter & 64) == 0)
    {
        anim = "Gun_Shot";
        hard_anim = true;
        obj->NoInterruptAnim = true;
    }

    InitAnimation(obj, anim, hard_anim);
}

void Program::FlyEnemy(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (!obj->isDamageable && !obj->haveGravity)
    {
        CreateExplosion(obj, 0, -20);
        obj->Life--;
        if (obj->Life == 0)
        {
            obj->haveGravity = true;
        }
        else
        {
            obj->isDamageable = true;
            obj->UndeadCounter = 15;
        }
    }

    if (obj->haveGravity)
    {
        SimpleMoveObjectForward(obj, 2);
        if (!Gravity(obj))
        {
            CreateExplosion(obj, 0, -20);
            CreateMiniBonus(obj);
            RemoveObject(obj);
        }

        //проверка на шипы и воду
        EnemyWaterSpikeTest(obj);
        return;
    }

    //столкновение с героем
    else
    {
        HeroDamage(obj, 0);
    }


    ObjWiggle(obj);


    if (obj->NoInterruptAnim)
    {
        if (!SimpleMoveObjectForward(obj, 2))
        {
            ChangeDirection(obj);
        }
        return;
    }

    std::string anim;

    if (obj->Name == idDragonfly)
    {
        anim = "Dragonfly_Fly";

        if (obj->Counter == 0 && GetXDistance(obj) >= 64 && GetXDistance(obj) < 112 && GetYDistance(obj) < 32 && SeeOnHero(obj) && InCurrentRoom(obj))
        {
            obj->Counter = 40;
        }


        if (obj->Counter != 0)
        {
            obj->Counter--;
            if (obj->Counter == 0)
            {
                std::shared_ptr<GameObject> o = CreateChild(obj, idRocket, 20, -20);
                o->Animations = FindObjectAnimation("Items");
                InitAnimation(o, "Rocket2", true);
                o->XAccel = 3;
                o->Counter = 4;
                o->isDamageable = true;
                o->Fixed = true;
                InitSFX(sfx_rocket);
            }
        }
        else
        {
            if (!SimpleMoveObjectForward(obj, 2))
            {
                ChangeDirection(obj);
            }
        }
    }
    else if (obj->Name == idFighterBomber)
    {
        if (!SimpleMoveObjectForward(obj, 2))
        {
            ChangeDirection(obj);
        }

        anim = "FighterBomber_Fly";
        if (obj->Counter != 0)
        {
            obj->Counter--;
        }
        else if (GetXDistance(obj) < 32 && obj->Y < hero_object->Y && SeeOnHero(obj))
        {
            anim = "FighterBomber_Throw";
            obj->NoInterruptAnim = true;
            obj->Counter = 25;

            std::shared_ptr<GameObject> o = CreateChild(obj, idBomb, 24, -32);
            o->Fixed = true;
            o->Animations = obj->Animations;
            InitAnimation(o, "Bomb", true);
            InitSFX(sfx_gotonthewall);
        }
    }
    else
    {
        if (!SimpleMoveObjectForward(obj, 2))
        {
            ChangeDirection(obj);
        }

        anim = "DronBomber_Fly";
        if (obj->Counter != 0)
        {
            obj->Counter--;
        }
        else if (GetXDistance(obj) < 8 && obj->Y < hero_object->Y && TestShoot(obj, 0, 0, 1))
        {
            obj->Counter = 15;

            std::shared_ptr<GameObject> o = CreateChild(obj, idBomb, 0, 0);
            o->Fixed = true;
            o->Animations = FindObjectAnimation("DronBomber");
            InitAnimation(o, "DronBomber_Bomb", true);
            InitSFX(sfx_gotonthewall);
        }
    }

    InitAnimation(obj, anim, false);
}

void Program::AlienClaw(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (!obj->isDamageable)
    {
        obj->isDamageable = true;
        CreateFractions(obj, 3);
        InitSFX(sfx_missshoot);
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    if (!MoveObjectForward(obj, 2) || (obj->Name == idAlienClawTop && GetProperty(obj, 20, -34) != isFloor))
    {
        ChangeDirection(obj);
    }
}

void Program::AlienWorm(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (!obj->isDamageable)
    {
        CreateExplosion(obj, 0, 0);
        CreateMiniBonus(obj);
        RemoveObject(obj);
        return;
    }

    //столкновение с героем
    HeroDamage(obj, 0);


    if (obj->Status == 0)
    {
        if (!obj->AnimationPlayed)
        {
            obj->Status++;
        }
        return;
    }

    std::string anim = "";

    if (obj->Status == 1)
    {
        if (GetXDistance(obj) < 128 && GetYDistance(obj) < 96)
        {
            obj->Status++;
            anim = "AlienWorm_MoveDown";
            obj->Y += 16;
        }
        else
        {
            anim = "AlienWorm_Idle";
        }
    }
    else if (obj->Status == 2)
    {
        if (!FlyDown(obj))
        {
            obj->Status++;
            anim = "AlienWorm_MoveUp";
        }
    }
    else
    {
        if (!FlyUp(obj))
        {
            obj->Status--;
            anim = "AlienWorm_MoveDown";
        }
    }

    if (obj->Status >= 2)
    {
        if (!MoveObjectForward(obj, 2))
        {
            ChangeDirection(obj);
        }
    }

    if (anim != "")
    {
        InitAnimation(obj, anim, false);
    }
}

void Program::Slime(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (!obj->isDamageable)
    {
        CreateExplosion(obj, 0, 0);
        if (obj->Life != 0)
        {
            for (std::int32_t i = 0; i < 2; i++)
            {
                std::shared_ptr<GameObject> o = CreateChild(obj, idSlime, 0, 0);
                o->Animations = FindObjectAnimation("Slime");
                o->Life = obj->Life - 1;
                InitAnimation(o, "Walk" + std::to_string(o->Life), true);
                o->Direction = i == 0;
                o->YAccel = -17;
                o->isDamageable = true;
                o->UndeadCounter = 15;
            }
            CreateMiniBonus(obj);
        }

        RemoveObject(obj);
        return;
    }

    //проверка на шипы и воду
    if (EnemyWaterSpikeTest(obj))
    {
        return;
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    bool on_air = Gravity(obj);

    if (obj->NoInterruptAnim)
    {
        return;
    }

    std::string anim;

    if (obj->Status == 0)
    {
        if (!on_air)
        {
            anim = "Walk" + std::to_string(obj->Life);
        }

        if (!MoveObjectForward(obj, 2))
        {
            ChangeDirection(obj);
        }

        if (SeeOnHero(obj) && GetXDistance(obj) < 32 && GetYDistance(obj) < 16)
        {
            anim = "Jump" + std::to_string(obj->Life);
            obj->Status++;
            obj->Counter = 0;
        }
    }

    else if (obj->Status == 1)
    {
        if (on_air)
        {
            if (!MoveObjectForward(obj, 2))
            {
                ChangeDirection(obj);
            }
        }
        else if (obj->Counter >= 25)
        {
            anim = "Fall" + std::to_string(obj->Life);
            obj->NoInterruptAnim = true;
            obj->Status--;
            TurnObject(obj);
        }
        obj->Counter++;
    }

    if (anim != "")
    {
        InitAnimation(obj, anim, false);
    }
}

void Program::SonusVenator(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (!obj->isDamageable)
    {
        obj->isDamageable = true;
        CreateExplosion(obj, 0, -16);
        obj->Life--;
        if (obj->Life == 0)
        {
            CreateMiniBonus(obj);
            RemoveObject(obj);
        }
        else
        {
            obj->UndeadCounter = 15;
            TurnObject(obj);
        }
        return;
    }

    //проверка на шипы и воду
    if (EnemyWaterSpikeTest(obj))
    {
        return;
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    Gravity(obj);

    if (obj->NoInterruptAnim)
    {
        return;
    }

    std::string anim = "Venator_Idle";
    bool hard_anim = false;

    if (hero_life != 0)
    {
        if (GetXDistance(obj) < 64 && std::abs(obj->Y - hero_object->Y) < 16 && SeeOnHero(obj))
        {
            anim = "Venator_Attack";
            hard_anim = true;
            obj->NoInterruptAnim = true;
        }
        else
        {
            anim = "Venator_Walk";
            if (!SimpleMoveObjectForward(obj, 2) || GetProperty(obj, 16, 4) == isEmpty)
            {
                ChangeDirection(obj);
            }
        }
    }

    InitAnimation(obj, anim, hard_anim);
}

void Program::BigSpider(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (BossDie(obj))
    {
        return;
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    std::string anim;
    bool on_air = false;
    if (obj->haveGravity)
    {
        on_air = Gravity(obj);
    }

    if (obj->Status < 3)
    {
        if (obj->Counter != 0)
        {
            obj->Counter--;
            return;
        }

        if (!on_air && obj->Status == 0)
        {
            anim = "BigSpider_RunFloor";
            if (!MoveObjectForward(obj, 4))
            {
                obj->Status++;
                obj->Counter = 4;
                obj->haveGravity = false;
                anim = "BigSpider_MoveOnWall";
            }
        }
        else if (obj->Status == 1)
        {
            anim = "BigSpider_RunWall";
            obj->Y -= 2;
            if (GetProperty(obj, 0, -44) == isFloor)
            {
                obj->Status++;
                ChangeDirection(obj);
                obj->Counter = 4;
                anim = "BigSpider_MoveOnRoof";
            }
        }
        else if (obj->Status == 2)
        {
            anim = "BigSpider_RunRoof";

            if (!MoveObjectForward(obj, 4) || GetXDistance(obj) < 32)
            {
                obj->haveGravity = true;
                anim = "BigSpider_Attack";
                if (GetXDistance(obj) >= 32)
                {
                    ChangeDirection(obj);
                }
                obj->Status = 3;
                obj->Counter = 1;
            }
        }
    }
    else
    {
        if (!MoveObjectForward(obj, 4))
        {
            ChangeDirection(obj);
            if (obj->Counter != 0)
            {
                obj->Counter--;
                return;
            }
            else
            {
                obj->Status = 0;
            }
        }

        if (!on_air)
        {
            obj->YAccel = 15;
        }
    }
    if (anim != "") // TODO: isEmpty?
    {
        InitAnimation(obj, anim, false);
    }
}

void Program::Craken(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (BossDie(obj))
    {
        return;
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    Gravity(obj);
    std::string anim = "Craken_Idle";

    if (obj->Counter != 0)
    {
        obj->Counter--;
    }
    else
    {
        anim = "Craken_Swim";
        if (!MoveObjectForward(obj, 3))
        {
            ChangeDirection(obj);
            obj->Status++;
            if (obj->Status == 3)
            {
                obj->Status = 0;
                obj->Counter = 75;
            }
        }
        else
        {
            if (GetXDistance(obj) < 32 && (game_cicle_counter & 31) == 0 && ObjectsCount(idBomb) < 2)
            {
                std::shared_ptr<GameObject> o = CreateChild(obj, idBomb, 0, 0);
                o->Animations = FindObjectAnimation("Craken");
                InitAnimation(o, "Craken_Bomb", true);
                o->YAccel = -15;
                o->Fixed = true;
                InitSFX(sfx_gotonthewall);
            }
        }
    }
    InitAnimation(obj, anim, false);
}

void Program::Moth(const std::shared_ptr<GameObject> &obj)
{
    if (obj->Counter != 0)
    {
        obj->Counter--;
        if (obj->Counter == 0)
        {
            InitAnimation(obj, "Moth_Fly", true);
            obj->Priority = normal_priority;
            obj->isDamageable = true;
        }
        return;
    }

    //повреждение
    if (BossDie(obj))
    {
        return;
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    ObjWiggle(obj);

    if (obj->Status == 0)
    {
        if (MoveObjectForward(obj, 3))
        {
            if ((game_cicle_counter & 1) == 0)
            {
                FlyDown(obj);
            }

            if (obj->XAccel != 0 && obj->YAccel == 0 && ObjectsCount(idFlyBomb) < 2)
            {
                std::shared_ptr<GameObject> o = CreateChild(obj, idFlyBomb, 0, 0);
                o->Animations = FindObjectAnimation("Moth");
                InitAnimation(o, "Moth_Bomb", true);
                o->isDamageable = true;
                obj->XAccel--;
                obj->YAccel = 48;
                InitSFX(sfx_gotonthewall);
            }

            if (obj->YAccel != 0)
            {
                obj->YAccel--;
            }
        }
        else
        {
            ChangeDirection(obj);
            obj->Status++;
        }
    }
    else
    {
        if (!FlyUp(obj))
        {
            obj->Status = 0;
            obj->XAccel = 3;
            obj->YAccel = 16;
        }
    }

}

void Program::Rocketman(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (BossDie(obj))
    {
        return;
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    bool on_air = Gravity(obj);

    if (obj->Counter != 0)
    {
        obj->Counter--;
        return;
    }
    if (obj->NoInterruptAnim)
    {
        return;
    }


    std::string anim = "Rocketman_Idle";
    if (on_air)
    {
        anim = "Rocketman_Fall";
    }

    if (obj->Status == 0 && !on_air && GetProperty(obj, -16, -64) != isFloor && GetXDistance(obj) >= 33)
    {
        anim = "Rocketman_Fire";
        obj->NoInterruptAnim = true;
        obj->Status++;
    }

    else
    {
        if (!MoveObjectForward(obj, 3) && !on_air)
        {
            ChangeDirection(obj);
            obj->Status++;
            if (obj->Status == 4)
            {
                obj->Status = 0;
            }
        }
        if (!on_air)
        {
            anim = "Rocketman_Walk";
            if (GetProperty(obj, 16, -32) == isPlatform && obj->Y != hero_object->Y && (obj->Status & 1) != 0)
            {
                anim = "Rocketman_Jump";
                obj->NoInterruptAnim = true;
            }
        }
    }

    if (anim != "")
    {
        InitAnimation(obj, anim, false);
    }

}

void Program::CrabBoss(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (BossDie(obj))
    {
        return;
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    if (obj->Counter != 0)
    {
        obj->Counter--;
        return;
    }
    if (obj->NoInterruptAnim)
    {
        return;
    }


    std::string anim = "Crab_Walk";
    bool hard_anim = false;
    bool on_air = Gravity(obj);

    if (MoveObjectForward(obj, 2))
    {
        if (!on_air)
        {

            if (TestShoot(obj, 16, -24, 0))
            {
                anim = "Crab_Attack";
                obj->NoInterruptAnim = true;
                hard_anim = true;
            }

            else if (TestShoot(obj, 16, -24, 2))
            {
                anim = "Crab_Attack1";
                obj->NoInterruptAnim = true;
                hard_anim = true;
            }
        }
    }
    else
    {
        if (!on_air)
        {
            if (GetProperty(obj, 0, -2) != isWater)
            {
                ChangeDirection(obj);
            }
            else
            {
                obj->YAccel = -20;
            }
        }
    }

    InitAnimation(obj, anim, hard_anim);
}

void Program::FlyBoss(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (BossDie(obj))
    {
        return;
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    if (obj->Counter != 0)
    {
        obj->Counter--;
        return;
    }
    if (obj->NoInterruptAnim)
    {
        return;
    }


    std::string anim = "FlyBoss_Idle";
    bool hard_anim = false;
    bool on_air = false;
    if (obj->haveGravity)
    {
        on_air = Gravity(obj);
    }
    else
    {
        if (obj->Status != 2)
        {
            ObjWiggle(obj);
            anim = "FlyBoss_Fly";
        }
        else
        {
            anim = "FlyBoss_Wall";
        }
    }

    std::int32_t dx = GetXDistance(obj);
    std::int32_t dy = std::abs(obj->Y - hero_object->Y);
    if (obj->haveGravity || obj->Status == 2)
    {
        if (!on_air)
        {
            //выстрел
            if (dy < 24 && SeeOnHero(obj))
            {
                if (hero_object->UndeadCounter == 0 && hero_life != 0)
                {
                    if (obj->Status != 2)
                    {
                        anim = "FlyBoss_Fire";
                    }
                    else
                    {
                        anim = "FlyBoss_FireWall";
                    }
                    hard_anim = true;
                    obj->NoInterruptAnim = true;
                }
            }
            else
            {
                obj->haveGravity = false;
            }
        }

        if (obj->Status == 2)
        {
            obj->XAccel--;
            if (obj->XAccel == 0 || dx >= 129)
            {
                obj->Status = 1;
            }
        }
    }
    else
    {
        if (obj->Status == 0)
        {
            if ((dx == 127 || dx == 128) && dy < 24)
            {
                obj->Status++;
            }
            else
            {
                if (dy < 8 && GetProperty(obj, 0, 0) != isEmpty)
                {
                    obj->haveGravity = true;
                }
                if (obj->Y >= hero_object->Y + 1)
                {
                    FlyUp(obj);
                }
                else if (obj->Y < hero_object->Y)
                {
                    obj->Y++;
                }
                if (dx >= 128)
                {
                    MoveObjectForward(obj, 3);
                }
                else
                {
                    ChangeDirection(obj);
                    bool f = MoveObjectForward(obj, 3);
                    ChangeDirection(obj);
                    if (!f)
                    {
                        if (dy >= 24)
                        {
                            obj->Status++;
                        }
                        else
                        {
                            obj->Status = 2;
                            obj->XAccel = 50;
                        }
                    }
                }
            }
        }

        else if (obj->Status == 1)
        {
            if ((game_cicle_counter & 1) == 0)
            {
                if (obj->Y >= hero_object->Y + 1)
                {
                    FlyUp(obj);
                }
                else if ((obj->Y < hero_object->Y))
                {
                    obj->Y++;
                    if (GetProperty(obj, 0, 0) == isFloor)
                    {
                        obj->Status = 0;
                    }
                }
            }
            if (!MoveObjectForward(obj, 2))
            {
                obj->Status = 0;
            }
        }
    }

    if (obj->Status == 0)
    {
        TurnObject(obj);
    }
    InitAnimation(obj, anim, hard_anim);
}

void Program::AlienPet(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    /*if (!obj.isDamageable)
                {
                    TurnObject(obj);
                    obj.isDamageable = true;
                    obj.UndeadCounter = 50;
                    CreateExplosion(obj, 0, -24);
                    obj.Life -= 8;
                    if (obj.Life < 0)
                        obj.Life = 0;
                    hero_path = obj.Life;

                    if (obj.Life == 0)
                    {
                        RemoveObject(obj);
                        boss_mode = false;
                        location_counter = 150;
                    }
                    return;
                }*/

    //повреждение
    if (BossDie(obj))
    {
        return;
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    bool on_air = false;
    if (obj->haveGravity)
    {
        on_air = Gravity(obj);
    }

    if (obj->Counter != 0)
    {
        obj->Counter--;
        return;
    }

    if (obj->NoInterruptAnim)
    {
        return;
    }

    std::string anim = "";
    bool hard_anim = false;

    std::int32_t dx = std::abs(obj->X - obj->XTarget);
    if (!on_air)
    {
        if (obj->Status == 0)
        {
            obj->XTarget = hero_object->X;
            obj->YTarget = hero_object->Y;
            TurnObject(obj);
            obj->Status++;
            anim = "Pet_Walk";
            obj->haveGravity = true;
        }
        else if (obj->Status == 1)
        {
            if (dx >= 32)
            {
                if (!MoveObjectForward(obj, 4))
                {
                    obj->Status = 0;
                }
                if (dx < 48 && obj->Y >= obj->YTarget + 1)
                {
                    anim = "Pet_Jump";
                    obj->NoInterruptAnim = true;
                    hard_anim = true;
                }
            }
            else
            {
                if (GetXDistance(obj) < 32 && GetYDistance(obj) < 16 && SeeOnHero(obj) && hero_life != 0)
                {
                    anim = "Pet_Attack";
                    obj->NoInterruptAnim = true;
                    hard_anim = true;
                    InitSFX(sfx_slime);
                }
                else
                {
                    if (dx < 16)
                    {
                        ChangeDirection(obj);
                    }
                    obj->Status++;
                    obj->Counter = 50;
                    anim = "Pet_Idle";
                }
            }
        }
        else if (obj->Status == 2)
        {
            anim = "Pet_Walk";
            if (!MoveObjectForward(obj, 4))
            {
                obj->Status = 0;
            }

            if (dx < 48 && obj->Y >= obj->YTarget + 1)
            {
                anim = "Pet_Jump";
                obj->NoInterruptAnim = true;
                hard_anim = true;
            }
        }
        else if (obj->Status == 3)
        {
            obj->haveGravity = true;
            obj->Status = 0;
            if (obj->Y >= hero_object->Y + 1)
            {
                obj->YAccel = -20;
                anim = "Pet_OnJump";
            }
        }
    }
    else
    {
        if (!MoveObjectForward(obj, 4))
        {
            anim = "Pet_Wall";
            obj->haveGravity = false;
            ChangeDirection(obj);
            obj->Counter = 15;
            obj->Status = 3;
        }
        else
        {
            obj->Status = 0;
        }
    }

    if (anim != "")
    {
        InitAnimation(obj, anim, hard_anim);
    }
}

void Program::AlienSliderman(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (!obj->isDamageable)
    {
        if (obj->Status != 3)
        {
            TurnObject(obj);
            obj->isDamageable = true;
            obj->UndeadCounter = 50;
            CreateExplosion(obj, 0, -24);
            obj->Status++;
            if (obj->Status == 3)
            {
                obj->Counter = 150;
                obj->XAccel = 0;
                obj->NoInterruptAnim = false;
                boss_magnit_on = false;
            }
        }
        else
        {
            obj->isDamageable = true;
            obj->UndeadCounter = 50;
            CreateExplosion(obj, 0, -24);
            obj->Life -= 5;
            if (obj->Life < 0)
            {
                obj->Life = 0;
            }
            hero_path = obj->Life;

            if (obj->Life == 0)
            {
                obj->isDamageable = false;
                BossDie(obj);
            }
        }
        return;
    }

    if (boss_magnit_on)
    {
        Magnit(obj, 2, 255, 2);
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    bool on_air = false;
    if (obj->haveGravity)
    {
        on_air = Gravity(obj);
    }

    if (obj->NoInterruptAnim)
    {
        return;
    }

    std::string anim;
    if (obj->Status != 3)
    {
        if (obj->Counter != 0)
        {
            obj->Counter--;
            return;
        }

        anim = "Slider_Fly";
        obj->haveGravity = false;
        ObjWiggle(obj);

        if (obj->UndeadCounter == 0)
        {
            FlyUp(obj);
        }
        else
        {
            FlyDown(obj);
        }

        if (!MoveObjectForward(obj, 2))
        {
            ChangeDirection(obj);
        }

        obj->XAccel++;
        if (obj->XAccel >= 64)
        {
            obj->XAccel = 0;

            if (GetYDistance(obj) >= 24)
            {
                anim = "Slider_Attack";
            }
            else
            {
                TurnObject(obj);
                anim = "Slider_Magnit";
                InitSFX(sfx_steam);
            }
            obj->NoInterruptAnim = true;
        }

    }
    else
    {
        obj->haveGravity = true;
        if (on_air)
        {
            anim = "Slider_Fall";
        }
        else
        {
            anim = "Slider_Damageble";
        }

        if (obj->Counter != 0)
        {
            obj->Counter--;
        }
        else
        {
            obj->Status = 0;
        }
    }


    if (anim != "")
    {
        InitAnimation(obj, anim, false);
    }
}

void Program::Megabrain(const std::shared_ptr<GameObject> &obj)
{
    if (!secret_boss_enabled)
    {
        //повреждение
        if (!obj->isDamageable)
        {
            obj->isDamageable = true;
            obj->UndeadCounter = 50;
            CreateExplosion(obj, 0, 0);
            if (obj->Status >= 17)
            {
                obj->Life -= 3;
                if (obj->Life < 0)
                {
                    obj->Life = 0;
                }
                hero_path = obj->Life;
            }
            else
            {
                obj->Status++;
            }

            std::int32_t n = obj->Status / 4;
            if (n >= 5)
            {
                n = 4;
            }
            InitAnimation(obj, "Megabrain_" + std::to_string(n), false);

            if (obj->Status == 16)
            {
                std::shared_ptr<GameObject> o = CreateChild(obj, idMultiExplosions, 0, 0);
                o->Counter = 127;
                o->NoVisible = true;
            }

            if (obj->Life == 0)
            {
                location_status--;

                std::shared_ptr<GameObject> o = CreateChild(obj, idMultiExplosions, 0, 0);
                o->Counter = 127;
                o->NoVisible = true;

                MuteAllMusic();
                RemoveObject(obj);
                boss_mode = false;
                location_counter = 150;
            }
            return;
        }

        //столкновение с героем
        HeroDamage(obj, 0);

        if (obj->Counter != 0)
        {
            obj->Counter--;
            if (obj->Counter == 0)
            {
                obj->Counter = 60;
                if (ObjectsCount(idMiniBrain) < 3)
                {
                    std::int32_t x = -96;
                    if ((rnd->Next() & 1) == 0)
                    {
                        x = 80;
                    }
                    std::int32_t y = -32;
                    if ((rnd->Next() & 1) == 0)
                    {
                        y = 40;
                    }

                    std::shared_ptr<GameObject> o = CreateChild(obj, idMiniBrain, x, y);
                    o->Animations = FindObjectAnimation("Megabrain");
                    InitAnimation(o, "MiniBrain", true);
                    o->isDamageable = true;
                    InitSFX(sfx_gotonthewall);
                }
            }
        }
    }
    //секретная фаза финального босса
    else
    {
        obj->Fixed = false;

        //повреждение
        if (!obj->isDamageable)
        {
            obj->Direction = (rnd->Next() & 1) == 1 ? true : false;
            obj->YAccel = (rnd->Next() & 1) == 1 ? 255 : 0;

            std::shared_ptr<GameObject> o = CreateChild(obj, idMiniBrain, 0, 0);
            o->Animations = FindObjectAnimation("Megabrain");
            InitAnimation(o, "MiniBrain", true);
            o->isDamageable = true;
            InitSFX(sfx_gotonthewall);
        }
        if (BossDie(obj))
        {
            last_boss_fase++;
            return;
        }

        //столкновение с героем
        HeroDamage(obj, 0);

        if (!MoveObjectForward(obj,2))
        {
            ChangeDirection(obj);
        }
        if (obj->YAccel == 0)
        {
            if (!FlyDown(obj))
            {
                obj->YAccel = 255;
            }
        }
        else
        {
            if (!FlyUp(obj))
            {
                obj->YAccel = 0;
            }
        }

        InitAnimation(obj, "Megabrain_4", false);
    }
}

void Program::Rocket(const std::shared_ptr<GameObject> &obj)
{
    if ((game_cicle_counter & 3) == 0)
    {
        std::shared_ptr<GameObject> o = CreateChild(obj, idRocketSmoke, 0, 0);
        o->Animations = FindObjectAnimation("Items");
        o->Fixed = true;
        InitAnimation(o, "Smoke", true);
    }

    obj->X += obj->XAccel;
    obj->Y += obj->YAccel;


    //столкновение с героем
    if (HeroDamage(obj, 0))
    {
        CreateExplosion(obj, 0, 0);
        RemoveObject(obj);
        return;
    }
    if (!InCurrentRoom(obj))
    {
        RemoveObject(obj);
        return;
    }
    else if (GetProperty(obj, 0, 0) == isFloor || !obj->isDamageable)
    {
        CreateExplosion(obj, 0, 0);
        RemoveObject(obj);
        return;
    }

    if (obj->Counter != 0)
    {
        obj->Counter--;
    }
    else
    {
        obj->Counter = 4 + (rnd->Next() & 3);

        std::int32_t d;
        std::int32_t x = obj->X - hero_object->X;
        if (std::abs(x) < 8)
        {
            x = 0;
        }
        std::int32_t y = obj->Y - (hero_object->Y + hero_object->Height + 8);
        if (std::abs(y) < 16)
        {
            y = 0;
        }

        if (y == 0)
        {
            if (x < 0)
            {
                d = 2;
            }
            else
            {
                d = 6;
            }
        }
        else if (y >= 0)
        {
            if (x == 0)
            {
                d = 0;
            }
            else if (x < 0)
            {
                d = 1;
            }
            else
            {
                d = 7;
            }
        }
        else
        {
            if (x == 0)
            {
                d = 4;
            }
            else if (x < 0)
            {
                d = 3;
            }
            else
            {
                d = 5;
            }
        }

        std::int32_t a;
        if (d >= 5)
        {
            a = 8 - d;
            obj->Direction = true;
        }
        else
        {
            a = d;
            obj->Direction = false;
        }
        InitAnimation(obj, "Rocket" + std::to_string(a), false);

        d = (obj->Status - d) & 7;
        if (d != 0)
        {
            if (d < 4)
            {
                obj->Status--;
            }
            else
            {
                obj->Status++;
            }
        }

        obj->Status &= 7;

        switch (obj->Status)
        {
        case 0:
            obj->XAccel = 0;
            obj->YAccel = -3;
            break;
        case 1:
            obj->XAccel = 2;
            obj->YAccel = -2;
            break;
        case 2:
            obj->XAccel = 3;
            obj->YAccel = 0;
            break;
        case 3:
            obj->XAccel = 2;
            obj->YAccel = 2;
            break;
        case 4:
            obj->XAccel = 0;
            obj->YAccel = 3;
            break;
        case 5:
            obj->XAccel = -2;
            obj->YAccel = 2;
            break;
        case 6:
            obj->XAccel = -3;
            obj->YAccel = 0;
            break;
        case 7:
            obj->XAccel = -2;
            obj->YAccel = -2;
            break;
        }
    }
}

void Program::MiniBrain(const std::shared_ptr<GameObject> &obj)
{
    //повреждение или столкновение с героем
    if (!obj->isDamageable || !boss_mode || HeroDamage(obj, 0))
    {
        CreateExplosion(obj, 0, 0);
        RemoveObject(obj);
        return;
    }

    if ((game_cicle_counter & 1) == 0)
    {
        std::int32_t dx = obj->X - hero_object->X;
        std::int32_t dy = obj->Y - hero_object->Y + 20;
        if (dx >= 1)
        {
            obj->X--;
        }
        else if (dx < 0)
        {
            obj->X++;
        }
        if (dy >= 1)
        {
            obj->Y--;
        }
        else if (dy < 0)
        {
            obj->Y++;
        }
    }
}

void Program::Bomb(const std::shared_ptr<GameObject> &obj)
{
    //столкновение с героем
    if (HeroDamage(obj, 0))
    {
        CreateExplosion(obj, 0, 0);
        RemoveObject(obj);
        return;
    }
    if (!InCurrentRoom(obj))
    {
        RemoveObject(obj);
        return;
    }
    else if (!Gravity(obj))
    {
        CreateExplosion(obj, 0, 0);
        RemoveObject(obj);
        return;
    }
}

void Program::FlyBomb(const std::shared_ptr<GameObject> &obj)
{
    //столкновение с героем
    if (HeroDamage(obj, 0) || !boss_mode || GetProperty(obj, 0, 8) == isFloor || !obj->isDamageable)
    {
        CreateExplosion(obj, 0, 0);
        RemoveObject(obj);
        return;
    }

    if (GetXDistance(obj) >= 3)
    {
        TurnObject(obj);
        MoveObjectForward(obj, 1);
    }

    if ((game_cicle_counter & 3) == 0)
    {
        FlyDown(obj);
    }
}

void Program::Magnit(const std::shared_ptr<GameObject> &obj, std::int32_t x_dist, std::int32_t x_area, std::int32_t x_force)
{
    for (const auto &o : actual_objects)
    {
        if ((o->Name == idNova && !on_roof && !on_wall) || o->Name == idBubble)
        {
            std::int32_t dx = obj->X - o->X + 8;
            if (std::abs(dx) >= x_dist && std::abs(dx) < x_area)
            {
                bool t = o->Direction;
                std::uint8_t n = o->Name;
                o->Name = 0;
                if (dx >= 0)
                {
                    o->Direction = false;
                }
                else
                {
                    o->Direction = true;
                }
                MoveObjectForward(o, x_force);
                o->Direction = t;
                o->Name = n;
                if (n == idNova)
                {
                    extern_move = true;
                }
            }
        }
    }
}

void Program::BubbleGenerator(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset, std::int32_t yoffset)
{
    if (graphics_quality == 0)
    {
        return;
    }

    std::int32_t max = 3;
    if (graphics_quality == 2)
    {
        max = 8;
    }
    if (particle_cntr < max && (rnd->Next() & 31) == 0)
    {
        std::shared_ptr<GameObject> o = CreateChild(obj, idBubble, xoffset, yoffset);
        o->Animations = FindObjectAnimation("Nova");
        o->YAccel = rnd->Next() & 1;
        std::string a = "Nova_Bubble0";
        if ((rnd->Next() & 1) == 0)
        {
            a = "Nova_Bubble1";
        }
        InitAnimation(o, a, true);
        particle_cntr++;
    }
}

void Program::DLCBullet(const std::shared_ptr<GameObject> &obj)
{
    if (EnemyDamage(obj, 17) != nullptr)
    {
        RemoveObject(obj);
        return;
    }

    if (!obj->Direction)
    {
        obj->X += 5;
    }
    else
    {
        obj->X -= 5;
    }

    if (GetProperty(obj, 0, 0) == isFloor)
    {
        //столкнулся со стеной
        if ((GetFullProperty(obj, 0, 0) & 0x10) != 0)
        {
            CreateExplosion(obj, 0, 0);
            NewTile(obj->X / 16, obj->Y / 16, 0);
        }
        else
        {
            CreateFractions(obj, 4);
            InitSFX(sfx_missshoot);
        }
        RemoveObject(obj);
    }

    if (!InCurrentRoom(obj))
    {
        RemoveObject(obj);
    }
}

void Program::DLCBubble(const std::shared_ptr<GameObject> &obj)
{
    obj->X = hero_object->X;
    obj->Y = hero_object->Y;
    if (!obj->AnimationPlayed)
    {
        RemoveObject(obj);
    }
}

void Program::DLCPowerUp(const std::shared_ptr<GameObject> &obj)
{
    Gravity(obj);

    if (GetProperty(obj, 0, 1) == isSpike)
    {
        CreateExplosion(obj, 0, 0);
        RemoveObject(obj);
        return;
    }

    obj->Counter++;
    if (obj->Counter == 128)
    {
        obj->Counter = 0;
    }

    std::int32_t i = obj->Type & 0x7f;
    if (obj->Counter >= 113)
    {
        i += (obj->Counter & 15) / 4;
    }
    obj->XAccel = i;

    if (hero_life != 0 && InRange(obj->X, hero_object->X, 12) && InRange(obj->Y, hero_object->Y, 12))
    {
        switch (obj->Name)
        {
        case idJDJump:
            double_jump_on = true;
            break;
        case idJGun:
            gun_on = true;
            break;
        case idJShield:
            hero_energy = 77;
            break;
        }
        RemoveObject(obj);
        InitSFX(sfx_powerup);
    }
}

void Program::Dragon(const std::shared_ptr<GameObject> &obj)
{
    //повреждение
    if (BossDie(obj))
    {
        return;
    }

    //столкновение с героем
    HeroDamage(obj, 0);

    std::string anim = "";
    bool on_air = Gravity(obj);

    if (obj->Status == 0)
    {
        if (obj->Counter != 0)
        {
            obj->Counter--;
            return;
        }
        else
        {
            obj->Status++;
            obj->Counter = 3;
        }
    }
    else if (obj->Status == 1)
    {
        if (obj->NoInterruptAnim)
        {
            return;
        }

        if (obj->Counter != 0)
        {
            obj->Counter--;
            anim = "Fire";
            obj->NoInterruptAnim = true;
        }
        else
        {
            obj->Status++;
            anim = "Attack";
            obj->YAccel = -20;
            obj->Counter = 2;
        }
    }
    else if (obj->Status == 2)
    {
        if (!on_air)
        {
            if (!MoveObjectForward(obj, 5))
            {
                ChangeDirection(obj);
                obj->Counter--;
                if (obj->Counter == 0)
                {
                    obj->Status++;
                    obj->Counter = 3;
                }
            }
        }
    }
    else if (obj->Status == 3)
    {
        if (!on_air)
        {
            obj->YAccel = -24;
        }
        if (!MoveObjectForward(obj, 5))
        {
            ChangeDirection(obj);
            obj->Counter--;
            if (obj->Counter == 0)
            {
                obj->Counter = 50;
                obj->Status = 0;
                anim = "Idle";
            }
        }
    }

    if (anim != "")
    {
        InitAnimation(obj, anim, true);
    }
}

std::int32_t Program::screen_width = 0;
std::int32_t Program::screen_height = 0;
double Program::screen_scale = 3;
bool Program::full_screen_mode = false;
bool Program::prev_full_screen_mode = true;

std::shared_ptr<Joystick> Program::kempston = nullptr;
std::array<std::shared_ptr<DeltaShadow::joy_button>, 8> Program::kempston_buttons;
float Program::kempston_ax_v = 0;
float Program::kempston_ax_h = 0;
std::vector<SdlDotNetCompat::Input::ButtonKeyState> Program::kempston_btns;

#ifndef NOT_PORTED_YET
std::shared_ptr<Controller> Program::x_input_controller;
Gamepad Program::x_input_gamepad;
#endif

void Program::Main()
{
    LoadSettings();

    std::shared_ptr<Program> Game = std::make_shared<Program>();

    Game->Run();
}

Program::Program()
{
    InitVideo();

#ifndef NOT_PORTED_YET
    Video::WindowIcon(std::make_shared<Surface>(std::make_shared<Bitmap>(Properties->Resources::getIco32()->ToBitmap())));
#endif

    Video::SetWindowCaption("Delta's Shadow");

    MainInit();

#ifndef NOT_PORTED_YET
    x_input_controller = std::make_shared<Controller>(UserIndex::One);
#endif
}

void Program::Run()
{
    using namespace std::placeholders;

    StartKempston();

    Events::Quit         += std::bind(&Program::Quit        , this, _1, _2);
    Events::Tick         += std::bind(&Program::Update      , this, _1, _2);
    Events::SetTargetFps(50);
    Events::KeyboardDown += std::bind(&Program::KeyboardDown, this, _1, _2);
    Events::KeyboardUp   += std::bind(&Program::KeyboardUp  , this, _1, _2);
    Events::MouseMotion  += std::bind(&Program::MouseMotion , this, _1, _2);
    Events::VideoResize  += std::bind(&Program::VideoResize , this, _1, _2);

    Events::Run();
}

void Program::Quit(void *, QuitEventArgs *)
{
    //if (setup_form != nullptr && setup_form->getActiveControl() != nullptr)
#ifndef NOT_PORTED_YET
    if (m_setup_form != nullptr)
    {
        full_screen_mode = prev_full_screen_mode;
    }
#endif
    SaveSettings();

    Mouse::ShowCursor = true;

    Events::QuitApplication();
}

std::int32_t Program::x_screen_home = 16;
std::int32_t Program::y_screen_home = 16;

void Program::Update(void *, TickEventArgs *)
{
    if (show_cursor_timer != 0)
    {
        show_cursor_timer--;
    }

    if (hide_cursor_timer != 0)
    {
        hide_cursor_timer--;
        if (hide_cursor_timer == 0)
        {
            Mouse::ShowCursor = false;
            show_cursor_timer = 1;
        }
    }

    MainCicle();

    //чтение джойстика
#ifndef NOT_PORTED_YET
    if (kempston != nullptr)
    {
        kempston_ax_v = kempston->GetAxisPosition(JoystickAxis::Vertical);
        kempston_ax_h = kempston->GetAxisPosition(JoystickAxis::Horizontal);
        for (std::int32_t i = 0; i < kempston->NumberOfButtons(); i++)
        {
            kempston_btns[i] = kempston->GetButtonState(i);
        }
    }
#endif

    double s = screen_scale;

    if (full_screen_mode)
    {
        Size win;
        Environment::PrimaryScreen::Size(win.Width, win.Height);
        std::int32_t sx = win.Width / 256;
        std::int32_t sy = win.Height / 192;
        s = static_cast<double>(std::min(sx, sy));
    }

    Surface sur = screen->CreateScaledSurface(s);
    Video::Screen().Blit(sur, Point(static_cast<std::int32_t>(x_screen_home * s), static_cast<std::int32_t>(y_screen_home * s)));
    Video::Screen().Update();
    sur.Dispose();
}

void Program::MouseMotion(void*, MouseMotionEventArgs*)
{
    if (show_cursor_timer != 0)
    {
        return;
    }
    Mouse::ShowCursor = true;
    hide_cursor_timer = 150;
}

void Program::KeyboardDown(void *, KeyboardEventArgs *e)
{
    SdlDotNetCompat::Input::Key key = e->Key();

    //TODO: replace with switch...

    if (key == Key::UpArrow)
    {
        key = KeysMap[0];
    }
    if (key == Key::DownArrow)
    {
        key = KeysMap[1];
    }
    if (key == Key::LeftArrow)
    {
        key = KeysMap[2];
    }
    if (key == Key::RightArrow)
    {
        key = KeysMap[3];
    }
    if (key == Key::Escape)
    {
        key = KeysMap[7];
    }

    if (key == KeysMap[0])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus | Key_Up);
    }
    if (key == KeysMap[1])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus | Key_Down);
    }
    if (key == KeysMap[2])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus | Key_Left);
    }
    if (key == KeysMap[3])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus | Key_Right);
    }
    if (key == KeysMap[4])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus | Key_Select);
    }
    if (key == KeysMap[5])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus | Key_Fire);
    }
    if (key == KeysMap[6])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus | Key_Jump);
    }
    if (key == KeysMap[7])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus | Key_Pause);
    }

    pressed_key_symbol = static_cast<std::int32_t>(key);
    pressed_key = key;
#ifndef NOT_PORTED_YET
    if (pressed_key_symbol > static_cast<std::int32_t>('9'))
    {
        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        pressed_key_symbol = static_cast<std::int32_t>(key.ToString().ToUpper()[0]);
    }
#endif
    if ((key >= Key::Zero && key <= Key::Nine)
            || (key >= Key::A && key <= Key::Z)
            ||  key == Key::Return
            ||  key == Key::KeypadEnter
            ||  key == Key::LeftShift
            ||  key == Key::LeftControl
            ||  key == Key::RightShift
            ||  key == Key::RightControl
            ||  key == Key::Space
            ||  key == Key::Escape )
    {
        switch (key)
        {
        case Key::Return:
        case Key::KeypadEnter:
            pressed_key_symbol = 0xf4;
            break;
        case Key::RightShift:
        case Key::LeftShift:
            pressed_key_symbol = 0xf5;
            break;
        case Key::RightControl:
        case Key::LeftControl:
            pressed_key_symbol = 0xf6;
            break;
        case Key::Escape:
            pressed_key_symbol = 0;
            break;
        case Key::Space:
            pressed_key_symbol = 0xf7;
            break;

        default:
            break;
        }
    }
    else
    {
        pressed_key_symbol = 0;
    }

    //настройки
    if (e->Key() == Key::F1)
    {
        prev_full_screen_mode = full_screen_mode;

        if (full_screen_mode)
        {
            full_screen_mode = false;
            InitVideo();
        }

#ifndef NOT_PORTED_YET
        if (m_setup_form == nullptr)
            //if (setup_form == nullptr || setup_form->getActiveControl() == nullptr)
        {
            StartKempston();

            //setup_form = std::make_shared<SetupForm>();
            m_setup_form = new SetupDialog();
            m_setup_form->open();
            //setup_form->Show();
        }
        else
        {
            m_setup_form->close();
            //setup_form->Close();
        }
#endif
    }

    if (e->Key() == Key::LeftWindows || e->Key() == Key::RightWindows)
    {
        if (full_screen_mode)
        {
            full_screen_mode = false;
            InitVideo();
        }
    }

    //пропуск локации
    if (cheats_enabled && e->Key() == Key::F2)
    {
        if (game_mode == platforming_mode)
        {
            if (!boss_mode)
            {
                std::shared_ptr<GameObject> t = std::make_shared<GameObject>();
                t->Status = 1;
                Event_door_close(t);
            }
            else if (last_boss_fase == 0)
            {
                in_boss_room = true;
                boss_mode = false;
                hero_path = 0;
                hero_path_current = 0;
                location_status = 1;
            }
            else
            {
                for (const auto &obj : actual_objects)
                {
                    if (obj->Name != idNova)
                    {
                        obj->isDamageable = false;
                        obj->Status = 3;
                        obj->Life = 0;
                        if (obj->Name == idMegabrain && !secret_boss_enabled)
                        {
                            std::shared_ptr<GameObject> o = CreateChild(obj, idMultiExplosions, 0, 0);
                            o->Counter = 127;
                            o->NoVisible = true;
                        }
                    }
                }
            }
        }
        if (game_mode == stealth_mode)
        {
            j_win = true;
            game_cicle_counter = 64;
        }

        if (game_mode == race_mode)
        {
            MuteAllMusic();
            race_win = true;
            race_exit_timer = 1;
        }

        if (game_mode == select_level_mode && current_level < 4)
        {
            std::uint8_t a = static_cast<std::uint8_t>(1 << (current_level - 1));
            levels_complete |= a;
            if (levels_complete == 7)
            {
                levels_complete = 15;
            }
            InitSelectLevel();
        }
    }

    if (cheats_enabled && e->Key() == Key::F3)
    {
        if (game_mode == platforming_mode || game_mode == stealth_mode)
        {
            InitSFX(sfx_powerup);
            hero_life_current = hero_life;
            hero_life = 77;
            hero_energy = 77;
        }
        else if (game_mode == race_mode)
        {
            hero_life_current = hero_object->Life;
            hero_object->Life = 77;
        }
    }

    if (( (e->Mod() & ModifierKeys::LeftAlt) | (e->Mod() & ModifierKeys::RightAlt) ) != 0 && e->Key() == Key::Return) // TODO: check condition
    {
        full_screen_mode = !full_screen_mode;
        InitVideo();
    }

    if (( (e->Mod() & ModifierKeys::LeftAlt) | (e->Mod() & ModifierKeys::RightAlt) ) != 0 && e->Key() == Key::F4) // TODO: check condition
    {
        Quit(this, new QuitEventArgs());
    }
}

void Program::KeyboardUp(void *, KeyboardEventArgs *e)
{
    if (e->Key() == KeysMap[0])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus & (~Key_Up));
    }
    if (e->Key() == KeysMap[1])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus & (~Key_Down));
    }
    if (e->Key() == KeysMap[2])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus & (~Key_Left));
    }
    if (e->Key() == KeysMap[3])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus & (~Key_Right));
    }
    if (e->Key() == KeysMap[4])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus & (~Key_Select));
    }
    if (e->Key() == KeysMap[5])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus & (~Key_Fire));
    }
    if (e->Key() == KeysMap[6])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus & (~Key_Jump));
    }
    if (e->Key() == KeysMap[7])
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus & (~Key_Pause));
    }
    if (e->Key() == Key::UpArrow)
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus & (~Key_Up));
    }
    if (e->Key() == Key::DownArrow)
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus & (~Key_Down));
    }
    if (e->Key() == Key::LeftArrow)
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus & (~Key_Left));
    }
    if (e->Key() == Key::RightArrow)
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus & (~Key_Right));
    }
    if (e->Key() == Key::Escape)
    {
        PressedKeysStatus = static_cast<std::uint8_t>(PressedKeysStatus & (~Key_Pause));
    }
}

void Program::InitVideo()
{
    double s = screen_scale;
    if (full_screen_mode)
    {
        Size win;
        Environment::PrimaryScreen::Size(win.Width, win.Height);

        std::int32_t sx = win.Width / 256;
        std::int32_t sy = win.Height / 192;
        s = static_cast<double>(std::min(sx, sy));
        screen_width = win.Width;
        screen_height = win.Height;
        x_screen_home = static_cast<std::int32_t>((screen_width - 256 * s) / 2 / s);
        y_screen_home = static_cast<std::int32_t>((screen_height - 192 * s) / 2 / s);
    }
    else
    {
        screen_width = static_cast<std::int32_t>(288 * s);
        screen_height = static_cast<std::int32_t>(224 * s);
        x_screen_home = 16;
        y_screen_home = 16;
    }
    Video::Initialize();
    std::int32_t bpp = Video::BestBitsPerPixel(screen_width, screen_height, full_screen_mode);
    Video::SetVideoMode(screen_width, screen_height, bpp, true, false, full_screen_mode, true);
}

void Program::VideoResize(void *, VideoResizeEventArgs *e)
{
    Size win;
    Environment::PrimaryScreen::Size(win.Width, win.Height);
    if (e->Width() >= win.Width || e->Height() >= win.Height)
    {
        full_screen_mode = true;
    }
    else
    {
        double x = e->Width();
        double y = e->Height();
        x = std::max(x, 288.0);
        y = std::max(y, 224.0);

        std::int32_t dx = std::abs(screen_width  - e->Width());
        std::int32_t dy = std::abs(screen_height - e->Height());

        if (dx > dy)
        {
            screen_scale = x / 288;
        }
        else
        {
            screen_scale = y / 224;
        }
    }
    InitVideo();
}

void Program::SaveSettings()
{
    try
    {
        const std::string settingsPath = Environment::SpecialFolder::ApplicationData() + "/blade_project.settings";

        BinaryStreamWriter f(settingsPath.c_str());

        f.Write(current_save_version);

        for (std::int32_t i = 0; i < 8; i++)
        {
            std::shared_ptr<joy_button> k = kempston_buttons[i];
            f.Write(k->isAxis);
            f.Write(k->isButton);
            f.Write(k->AxisNum);
            f.Write(k->AxisDirection);
            f.Write(k->ButtonNum);
        }
        f.Write(full_screen_mode);
        f.Write(language);
    }
    catch (...)
    {
    }
}

void Program::LoadSettings()
{
    for (std::int32_t i = 0; i < 8; i++)
    {
        kempston_buttons[i] = std::make_shared<joy_button>();
    }
    try
    {
        const std::string settingsPath = Environment::SpecialFolder::ApplicationData() + "/blade_project.settings";

        BinaryStreamReader f(settingsPath.c_str());

        std::string ver = f.ReadString();
        if (ver != current_save_version)
        {        
            return;
        }

        for (std::int32_t i = 0; i < 8; i++)
        {
            std::shared_ptr<joy_button> k = std::make_shared<joy_button>();
            k->isAxis        = f.ReadBoolean();
            k->isButton      = f.ReadBoolean();
            k->AxisNum       = f.ReadInt32();
            k->AxisDirection = f.ReadSingle();
            k->ButtonNum     = f.ReadInt32();
            kempston_buttons[i] = k;
        }
        full_screen_mode = f.ReadBoolean();
        language = f.ReadString();
    }
    catch (...)
    {
    }
}

void Program::StartKempston()
{
#ifndef NOT_PORTED_YET
    Joysticks::Close();
    if (kempston != nullptr)
    {
        kempston->Close();
        kempston = nullptr;
    }

    Joysticks::Initialize();
    if (Joysticks::NumberOfJoysticks != 0)
    {
        Joysticks::OpenJoystick(0);
        kempston = std::make_shared<Joystick>(0);
        kempston_btns = std::vector<ButtonKeyState>(kempston->NumberOfButtons());
    }
    else
    {
        kempston = nullptr;
    }
#endif
}

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
    for (std::int32_t i = 0; i < 77; i++)
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

    for (std::int32_t i = 0; i < 2; i++)
    {
        hero_life_current = UpdateBar(hero_life_current, hero_object->Life, 19, 6);
    }
    hero_path_current = UpdateBar(hero_path_current, hero_path, 160, 6);

    race_pos++;
    hero_path = race_pos / 16;

    //мигание красной лампочки при низком уровне жизни
    std::int32_t alert = 1;
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
        std::int32_t t = trace[trace_pos];
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
                std::int32_t i = 0;
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
    for (std::int32_t i = 0; i < 32; i += 2)
    {
        race_objects[i + 1]++;
        if (race_objects[i + 1] == 12)
        {
            race_objects[i] = 0;
        }
    }

    //вывод объектов
    std::int32_t o = 30;
    while (o >= 0)
    {
        if (race_objects[o] != 0)
        {
            std::int32_t obst = race_objects[o];
            std::int32_t dist = race_objects[o + 1];

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
                std::int32_t s = 34;
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
                    std::int32_t pos = 4;
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
    std::int32_t last = bike_y_offset;
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

void Program::DecLife(const std::shared_ptr<GameObject> &obj, std::int32_t value)
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

void Program::InitScene(std::int32_t num)
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
            std::int32_t n = 7;
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

            std::int32_t e = 45;
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
            std::int32_t n = (game_cicle_counter >> 1) & 3;
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

            std::int32_t e = 195;
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
        std::int32_t f = scene_num - 6;
        std::int32_t n = (game_cicle_counter >> 1) & 3;
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
        std::int32_t n = (game_cicle_counter >> 1) & 3;
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
            std::int32_t c = scene_cntr / 2;
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
            std::int32_t b = (scene_status - 3) * 5;
            std::int32_t c = scene_cntr / 2;

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
                std::int32_t b = (scene_cntr - 10) / 2;
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
                std::int32_t b = (scene_cntr - 10) / 2;
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
                std::int32_t p = PrintStringLine();
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
                std::int32_t tn = 25;
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
                    std::int32_t p = PrintStringLine();
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

std::shared_ptr<Program::ScreensProject> Program::InitScreensProject(const std::string &name)
{
    std::string smprojFile;

    std::int32_t len = 9;
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

    std::int32_t tiles_count = proj.ReadInt32();
    obj->Tileset.clear();
    for (std::int32_t i = 0; i < tiles_count; i++)
    {
        std::vector<std::uint8_t> data(len);
        for (std::int32_t j = 0; j < len; j++)
        {
            data[j] = proj.ReadByte();
        }
        AddTile(obj, data);
    }

    //загружаем спрайты
    std::int32_t spr_count = proj.ReadInt32();
    obj->Sprites.clear();
    for (std::int32_t i = 0; i < spr_count; i++)
    {
        std::shared_ptr<Sprite> spr = std::make_shared<Sprite>();
        spr->name   = proj.ReadString();
        spr->width  = proj.ReadInt32();
        spr->height = proj.ReadInt32();

        spr->tiles = AllocateDynamicArray<std::shared_ptr<Tile>>(spr->height, spr->width);
        for (std::int32_t y = 0; y < spr->height; y++)
        {
            for (std::int32_t x = 0; x < spr->width; x++)
            {
                int32_t tileIdx = proj.ReadInt32();
                std::shared_ptr<Tile> &tile = obj->Tileset[tileIdx];
                spr->tiles[x][y] = tile;
            }
        }
        obj->Sprites.push_back(spr);
    }

    //загружаем скрины
    std::int32_t scr_count = proj.ReadInt32();
    obj->Screens.clear();
    for (std::int32_t i = 0; i < scr_count; i++)
    {
        std::shared_ptr<Screen> scr = std::make_shared<Screen>();
        scr->name    = proj.ReadString();
        scr->visible = proj.ReadBoolean();
        std::int32_t scrspr_count = proj.ReadInt32();
        for (std::int32_t j = 0; j < scrspr_count; j++)
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

std::shared_ptr<Program::Tile> Program::AddTile(const std::shared_ptr<Program::ScreensProject> &obj, std::vector<std::uint8_t> &data)
{
    std::int32_t len = 9;
    if (tiles_mode != 0)
    {
        len = 64;
    }

    for (const auto &te : obj->Tileset)
    {
        bool e = true;
        for (std::int32_t j = 0; j < len; j++)
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
    t->data = std::vector<std::uint8_t>(len);
    for (std::int32_t j = 0; j < len; j++)
    {
        t->data[j] = data[j];
    }


    t->img = std::make_shared<Surface>(8, 8);
    for (std::int32_t y = 0; y < 8; y++)
    {
        for (std::int32_t x = 0; x < 8; x++)
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

SdlDotNetCompat::Drawing::Color Program::GetAttrColor(std::uint8_t attr, bool enable)
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

void Program::DrawScreen(const std::shared_ptr<ScreensProject> &proj, std::int32_t num)
{
    std::shared_ptr<Screen> scr = proj->Screens[num];
    for (const auto &scr_spr : scr->sprites)
    {
        std::int32_t x_cord = scr_spr->x_cord;
        std::int32_t y_cord = scr_spr->y_cord;
        for (std::int32_t y = 0; y < scr_spr->sprite->height; y++)
        {
            for (std::int32_t x = 0; x < scr_spr->sprite->width; x++)
            {
                screen->Blit(*(scr_spr->sprite->tiles[x][y]->img), Point((x_cord + x) * 8, (y_cord + y) * 8));
                //if (tiles_mode == 0)
                {
                    Color ink = GetAttrColor(scr_spr->sprite->tiles[x][y]->data[0], true);
                    Color paper = GetAttrColor(scr_spr->sprite->tiles[x][y]->data[0], false);
                    for (std::int32_t j = 0; j < 8; j++)
                    {
                        for (std::int32_t i = 0; i < 8; i++)
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

void Program::DrawScreenSprite(const std::shared_ptr<ScreensProject> &proj, const std::string &name, std::int32_t xcord, std::int32_t ycord, std::int32_t xwin, std::int32_t ywin, std::int32_t width, std::int32_t height)
{
    std::shared_ptr<Sprite> spr = FindSprite(proj, name);
    for (std::int32_t y = 0; y < height; y++)
    {
        for (std::int32_t x = 0; x < width; x++)
        {
            screen->Blit(*(spr->tiles[x + xwin][y + ywin]->img), Point((xcord + x) * 8, (ycord + y) * 8));
            {
                Color ink   = GetAttrColor(spr->tiles[x][y]->data[0], true);
                Color paper = GetAttrColor(spr->tiles[x][y]->data[0], false);
                for (std::int32_t j = 0; j < 8; j++)
                {
                    for (std::int32_t i = 0; i < 8; i++)
                    {
                        attr_layer[0][(xcord + x) * 8 + i][(ycord + y) * 8 + j] = ink;
                        attr_layer[1][(xcord + x) * 8 + i][(ycord + y) * 8 + j] = paper;
                    }
                }
            }

        }
    }
}

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

    for (std::int32_t i = 0; i < 4; i++)
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

void Program::SelectTest(std::int32_t delta)
{
    InitSFX(sfx_switch);
    current_suit &= 3;
    for (std::int32_t i = 0; i < 4; i++)
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

void Program::InitSFXBank()
{    
    SFX_Bank.resize(32);

    LoadSFX("./res/SFX/sfx_beetle.wav"   , sfx_beetle, high_priority);
    LoadSFX("./res/SFX/sfx_bumerang.wav" , sfx_bumerang, high_priority);
    LoadSFX("./res/SFX/sfx_damage.wav"   , sfx_damage, normal_priority);
    LoadSFX("./res/SFX/sfx_dogscream.wav", sfx_dogscream, high_priority);
    LoadSFX("./res/SFX/sfx_dooropen.wav" , sfx_dooropen, high_priority);
    LoadSFX("./res/SFX/sfx_doors.wav"    , sfx_doors, normal_priority);
    LoadSFX("./res/SFX/sfx_droid.wav"    , sfx_droid, normal_priority);
    LoadSFX("./res/SFX/sfx_elevator.wav" , sfx_elevator, high_priority);
    LoadSFX("./res/SFX/sfx_explosion.wav", sfx_explosion, high_priority);
    LoadSFX("./res/SFX/sfx_gotonthewall.wav", sfx_gotonthewall, high_priority);
    LoadSFX("./res/SFX/sfx_lowpower.wav"    , sfx_lowpower, high_priority);
    LoadSFX("./res/SFX/sfx_missshoot.wav"   , sfx_missshoot, high_priority);
    LoadSFX("./res/SFX/sfx_powerup.wav", sfx_powerup, high_priority);
    LoadSFX("./res/SFX/sfx_race_block_hit.wav", sfx_race_block_hit, high_priority);
    LoadSFX("./res/SFX/sfx_race_down.wav", sfx_race_down, high_priority);
    LoadSFX("./res/SFX/sfx_race_jump.wav", sfx_race_jump, high_priority);
    LoadSFX("./res/SFX/sfx_race_wall_hit.wav", sfx_race_wall_hit, high_priority);
    LoadSFX("./res/SFX/sfx_rocket.wav", sfx_rocket, high_priority);
    LoadSFX("./res/SFX/sfx_shocker.wav", sfx_shocker, high_priority);
    LoadSFX("./res/SFX/sfx_slide.wav", sfx_slide, high_priority);
    LoadSFX("./res/SFX/sfx_slime.wav", sfx_slime, high_priority);
    LoadSFX("./res/SFX/sfx_start.wav", sfx_start, high_priority);
    LoadSFX("./res/SFX/sfx_stealth.wav", sfx_stealth, normal_priority);
    LoadSFX("./res/SFX/sfx_steam.wav", sfx_steam, normal_priority);
    LoadSFX("./res/SFX/sfx_stungun.wav", sfx_stungun, high_priority);
    LoadSFX("./res/SFX/sfx_switch.wav", sfx_switch, high_priority);
    LoadSFX("./res/SFX/sfx_tanketteborn.wav", sfx_tanketteborn, normal_priority);
    LoadSFX("./res/SFX/sfx_tanketteshoot.wav", sfx_tanketteshoot, normal_priority);
    LoadSFX("./res/SFX/sfx_terminal.wav", sfx_terminal, normal_priority);
    LoadSFX("./res/SFX/sfx_type.wav", sfx_type, low_priority);
    LoadSFX("./res/SFX/sfx_wave.wav", sfx_wave, high_priority);
    LoadSFX("./res/SFX/sfx_star.wav", sfx_star, high_priority);
}

void Program::LoadSFX(const std::string &filePath, std::int32_t num, std::int32_t priority)
{
    SFX_Priority[num] = priority;
    SFX_Bank[num] = std::make_shared<SdlDotNetCompat::Audio::Sound>(filePath);
}

void Program::InitSFX(std::int32_t num)
{
    if (!sound_on)
    {
        return;
    }

    const int32_t requestedSfxPriority = SFX_Priority[num];
    if (sfx_busy == 0 || requestedSfxPriority >= current_sfx_priority)
    {
        current_sfx_priority = requestedSfxPriority;
        sfx_busy = 20;

        SFX_Bank[num]->Play();
    }
}

void Program::InitGameMusic(std::int32_t num, bool looped)
{
    if (num == 255 || !music_on)
    {
        MuteGameMusic();
        return;
    }

    std::string name = music_names[num];
    if (sound_mode == ts_mode)
    {
        name += "_ts";
    }

    std::string path = "./res/music/" + name + ".ogg";

    GameSoundTheme = std::make_shared<SdlDotNetCompat::Audio::Music>(path);

    MusicPlayer::SetCurrentMusic(*GameSoundTheme);

    MusicPlayer::Play(looped);
}

void Program::MuteGameMusic()
{
    if (MusicPlayer::CurrentMusic())
    {
        MusicPlayer::Stop();
    }
}

void Program::PauseGameMusic()
{
    if (MusicPlayer::CurrentMusic())
    {
        MusicPlayer::Pause();
    }
}

void Program::ResumeGameMusic()
{
    if (MusicPlayer::CurrentMusic())
    {
        MusicPlayer::Resume();
    }
}

void Program::InitMenuMusic(std::int32_t num, bool looped)
{
    if (num == 255 || !music_on)
    {
        MuteMenuMusic();
        return;
    }

    std::string name = music_names[num];
    if (sound_mode == ts_mode)
    {
        name += "_ts";
    }
    std::string path = "./res/music/" + name + ".ogg";

    MenuSoundTheme = std::make_shared<Sound>(path);
    MenuSoundTheme->Play(looped);
}

void Program::MuteMenuMusic()
{
    if (MenuSoundTheme != nullptr)
    {
        MenuSoundTheme->Dispose();
    }
    MenuSoundTheme = nullptr;
}

void Program::MuteAllMusic()
{
    MuteGameMusic();
    MuteMenuMusic();
}

bool Program::isEnemy(const std::shared_ptr<GameObject> &obj)
{
    std::vector<std::int32_t> e = {idTankette, idDron, idSpider, idPiranha, idBigPiranha, idJelly, idBug, idDronBomber, idGun, idDragonfly, idFighterBomber, idAlienWorm, idSlime, idSonusVenator};
    for (auto i : e)
    {
        if (obj->Name == i)
        {
            return true;
        }
    }
    return false;
}

void Program::SpawnObjects(const std::shared_ptr<GameObject> &obj)
{
    if (graphics_quality == 0 && isEnemy(obj))
    {
        std::int32_t c = 0;
        for (const auto &o : actual_objects)
        {
            if (!o->NoActivated && isEnemy(o))
            {
                c++;
            }
        }
        if (c >= 2)
        {
            return;
        }
    }

    if (obj->Name != 0 && obj->Name != idNova && obj->XYRoom == current_xy_room && ((obj->X1Trigger < hero_object->X + 1 && obj->X2Trigger >= hero_object->X && obj->Y1Trigger < hero_object->Y + 1 && obj->Y2Trigger >= hero_object->Y) || (obj->X1Trigger == -1 && cntr_enter_in_room != 0)))
    {

        std::string anim = "";
        std::int32_t sfx = 255;
        std::vector<std::shared_ptr<ObjectAnimation>> prev_anims = obj->Animations;

        obj->X = obj->XTile * 16 + 8;
        obj->Y = obj->YTile * 16;
        obj->Fixed = false;
        obj->NoInterruptAnim = false;
        obj->Priority = normal_priority;

        switch (obj->Name)
        {
        case idPlatform:
            obj->Animations = FindObjectAnimation("Items");
            anim = "Platform_Idle";
            obj->Fixed = true;
            break;
        case idSteam:
            obj->Animations = FindObjectAnimation("Items");
            obj->NoVisible = true;
            obj->Priority = high_priority;
            obj->Fixed = true;
            break;
        case idDoor:
        {
            obj->Animations = FindObjectAnimation("Items");
            if (obj->Counter != 0 && room_cntr == 1)
            {
                obj->Priority = high_priority;
                hero_object->Y = obj->Y;
                hero_object->haveGravity = true;
                is_fly = false;
                disable_control = true;
            }
            else
            {
                obj->Priority = low_priority;
            }
            anim = "Door_Close";
            obj->Fixed = true;
            obj->Direction = false;
            //включение таблички над дверью для хардмода
            std::int32_t a = reverse_way ? 0 : 1;
            if (a == obj->Status && current_level < 4 && current_location == 3 && difficulty != 0)
            {
                NewTile(obj->XTile, obj->YTile - 3, 255);
            }
            break;
        }
        case idTankette:
            obj->Animations = FindObjectAnimation("Tankette");
            if (!InCurrentRoom(obj))
            {
                anim = "Tankette_Move";
            }
            else
            {
                anim = "Tankette_Uprise";
                obj->NoInterruptAnim = true;
                sfx = sfx_tanketteborn;
            }
            obj->isDamageable = true;
            obj->Life = 2;
            obj->haveGravity = true;
            break;
        case idDron:
            obj->Animations = FindObjectAnimation("Dron");
            if (!InCurrentRoom(obj))
            {
                anim = "Dron_Move";
                obj->Status = 1;
            }
            else
            {
                anim = "Dron_Born";
                obj->NoInterruptAnim = true;
                sfx = sfx_tanketteborn;
            }
            obj->isDamageable = true;
            break;
        case idSpiderNest:
            obj->X -= 8;
            obj->Counter = 25;
            obj->NoVisible = true;
            obj->Width = 16;
            obj->Height = -32;
            obj->isDamageable = true;
            obj->Life = 2;
            obj->Fixed = true;
            break;
        case idWaterFun:
        case idBubbleGenerator:
        case idBlower:
            obj->NoVisible = true;
            obj->Fixed = true;
            break;
        case idSpider:
            obj->Animations = FindObjectAnimation("Spider");
            anim = "Spider_Run";
            obj->isDamageable = true;
            obj->haveGravity = true; //это признак, что паук предустановлен
            break;
        case idPiranha:
        case idBigPiranha:
            obj->Life = 1;
            obj->Animations = FindObjectAnimation("Piranha");
            anim = "SmallPiranha_Swim";
            if (obj->Name == idBigPiranha)
            {
                anim = "Piranha_Swim";
                obj->Life++;
            }
            obj->isDamageable = true;

            if (current_level == 5)
            {
                if ((obj->Status == 1 && gun_on == false) || (obj->Status == 2 && (gun_on == false || double_jump_on == false)))
                {
                    return;
                }
            }

            break;
        case idJelly:
            obj->Animations = FindObjectAnimation("Jelly");
            anim = "Jelly_Idle";
            obj->isDamageable = true;
            obj->Counter = 100;
            obj->Life = 2;
            break;
        case idBug:
            obj->Animations = FindObjectAnimation("Bug");
            if (!InCurrentRoom(obj))
            {
                anim = "Bug_Run";
                obj->Status = 1;
            }
            else
            {
                anim = "Bug_Born";
                obj->NoInterruptAnim = true;
                sfx = sfx_beetle;
            }
            obj->isDamageable = true;
            obj->haveGravity = true;
            obj->Life = 3;
            break;
        case idDronBomber:
            obj->Animations = FindObjectAnimation("DronBomber");
            anim = "DronBomber_Fly";
            obj->isDamageable = true;
            obj->Life = 1;
            obj->haveGravity = false;

            if (current_level == 5)
            {
                if ((obj->Status == 1 && gun_on == false) || (obj->Status == 2 && (gun_on == false || double_jump_on == false)))
                {
                    return;
                }
            }

            break;
        case idGun:
            obj->Animations = FindObjectAnimation("Gun");
            anim = "Gun_Born";
            obj->NoInterruptAnim = true;
            obj->isDamageable = true;
            obj->Fixed = true;
            obj->Life = 3;
            TurnObject(obj);
            break;
        case idDragonfly:
            obj->Animations = FindObjectAnimation("Dragonfly");
            anim = "Dragonfly_Fly";
            obj->isDamageable = true;
            obj->haveGravity = false;
            obj->Life = 1;
            break;
        case idFighterBomber:
            obj->Animations = FindObjectAnimation("FighterBomber");
            anim = "FighterBomber_Fly";
            obj->isDamageable = true;
            obj->haveGravity = false;
            obj->Life = 2;
            break;
        case idAlienClawBottom:
        case idAlienClawTop:
            obj->Animations = FindObjectAnimation("AlienClaw");
            anim = "Claw_Bottom";
            if (obj->Name == idAlienClawTop)
            {
                anim = "Claw_Top";
            }
            obj->isDamageable = true;
            break;
        case idAlienWorm:
            obj->Status = 0;
            obj->Animations = FindObjectAnimation("AlienWorm");
            anim = "AlienWorm_Born";
            obj->isDamageable = true;
            break;
        case idSlime:
            obj->Animations = FindObjectAnimation("Slime");
            anim = "Walk2";
            obj->isDamageable = true;
            obj->Life = 2;
            obj->haveGravity = true;
            break;
        case idSonusVenator:
            obj->Animations = FindObjectAnimation("SonusVenator");
            anim = "Venator_Idle";
            obj->isDamageable = true;
            obj->Life = 3;
            obj->haveGravity = true;
            break;
        case idBigSpider:
            boss_mode = true;
            obj->Animations = FindObjectAnimation("BigSpider");
            anim = "BigSpider_Idle";
            obj->isDamageable = true;
            obj->Life = 77;
            hero_path = 77;
            obj->Counter = 100;
            break;
        case idCraken:
            boss_mode = true;
            obj->Animations = FindObjectAnimation("Craken");
            anim = "Craken_Idle";
            obj->isDamageable = true;
            obj->Life = 77;
            hero_path = 77;
            obj->Counter = 75;
            break;
        case idMoth:
            boss_mode = true;
            obj->Animations = FindObjectAnimation("Moth");
            anim = "Moth_Idle";
            obj->Priority = low_priority;
            obj->Life = 77;
            hero_path = 77;
            obj->Counter = 100;
            obj->XAccel = 3;
            break;
        case idRocketman:
            boss_mode = true;
            obj->Animations = FindObjectAnimation("Rocketman");
            anim = "Rocketman_Idle";
            obj->isDamageable = true;
            obj->Status = 1;
            obj->Life = 77;
            hero_path = 77;
            obj->Counter = 100;
            break;
        case idCrabBoss:
            boss_mode = true;
            obj->Animations = FindObjectAnimation("CrabBoss");
            anim = "Crab_Idle";
            obj->isDamageable = true;
            obj->Life = 77;
            hero_path = 77;
            obj->Counter = 100;
            break;
        case idFlyBoss:
            boss_mode = true;
            obj->Animations = FindObjectAnimation("FlyBoss");
            anim = "FlyBoss_Idle";
            obj->isDamageable = true;
            obj->Life = 77;
            hero_path = 77;
            obj->Counter = 100;
            obj->haveGravity = true;
            break;
        case idAlienPet:
            boss_mode = true;
            obj->Animations = FindObjectAnimation("AlienPet");
            anim = "Pet_Idle";
            obj->isDamageable = true;
            obj->Life = 77;
            hero_path = 77;
            obj->Counter = 100;
            obj->haveGravity = true;
            last_boss_fase++;
            break;
        case idAlienSliderman:
            boss_mode = true;
            obj->Animations = FindObjectAnimation("AlienSliderman");
            anim = "Slider_Idle";
            obj->isDamageable = true;
            obj->Life = 77;
            hero_path = 77;
            obj->Counter = 100;
            obj->haveGravity = true;
            boss_magnit_on = false;
            last_boss_fase++;
            break;
        case idMegabrain:
            boss_mode = true;
            obj->Animations = FindObjectAnimation("Megabrain");
            anim = "Megabrain_0";
            obj->Priority = low_priority;
            obj->isDamageable = true;
            obj->Life = 77;
            hero_path = 77;
            obj->Counter = 100;
            last_boss_fase++;
            obj->Fixed = true;
            obj->YAccel = 1;
            break;
        case idBattery: //бонусы
        case idHeart:
        case idPowerup:
        case idStar:
        {
            std::int32_t n = 0;
            switch (obj->Name)
            {
            case idBattery:
                n = 1;
                break;
            case idHeart:
                n = 5;
                break;
            case idPowerup:
                n = 9;
                break;
            case idStar:
                if ((collected_stars & (static_cast<std::uint64_t>(1) << obj->Status)) == 0)
                {
                    n = 13;
                }
                else
                {
                    RemoveActualObject(obj);
                    obj->Name = 0;
                }
                break;
            }
            obj->Type = static_cast<std::uint8_t>(n);
            obj->XAccel = static_cast<std::uint8_t>(n);
            obj->Width = 7;
            obj->Height = -16;
            obj->haveGravity = true;
            obj->Fixed = true;
            break;
        }
        case idJDJump:
        case idJGun:
        case idJShield:
        {
            std::int32_t t = 0;
            switch (obj->Name)
            {
            case idJDJump:
                t = 1;
                break;
            case idJGun:
                t = 9;
                break;
            case idJShield:
                t = 13;
                break;
            }
            obj->Type = static_cast<std::uint8_t>(t);
            obj->XAccel = static_cast<std::uint8_t>(t);
            obj->Width = 7;
            obj->Height = -16;
            obj->haveGravity = true;
            obj->Fixed = true;
            break;
        }
        case idDragon:
            boss_mode = true;
            obj->Animations = FindObjectAnimation("DLCBoss");
            anim = "Idle";
            obj->isDamageable = true;
            obj->Life = 77;
            hero_path = 77;
            obj->Counter = 100;
            break;
        }

        if (!obj->Fixed && obj->Name != idPlatform)
        {
            //враг появляется слишком близко
            if (GetXDistance(obj) < 64 && !boss_mode && prev_anims.empty())
            {
                //удаляем объект, если он не за краем экрана
                if (InCurrentRoom(obj))
                {
                    RemoveObject(obj);
                }
                return;
            }
            //разворачиваем в сторону героя
            else if (!boss_mode)
            {
                TurnObject(obj);
            }
        }

        if (sfx != 255)
        {
            InitSFX(sfx);
        }

        obj->NoActivated = false;
        if (anim != "")
        {
            InitAnimation(obj, anim, true);
        }
    }
}

std::int32_t Program::UpdateBar(std::int32_t current, std::int32_t value, std::int32_t x, std::int32_t y)
{
    if (value >= 78)
    {
        value = 77;
    }
    if (current < value)
    {
        SetScaleCol(x + current, y);
        current++;
    }
    else if (current >= value + 1)
    {
        current--;
        ResScaleCol(x + current, y);
    }
    return current;
}

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

    for (std::int32_t i = 0; i < stealth_flags.size(); i++)
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

bool Program::GetStealth(std::int32_t num)
{
    return stealth_flags[num - 1];
}

void Program::SetStealth(std::int32_t num)
{
    stealth_flags[num - 1] = true;
}

void Program::InitStelthStatusbar()
{
    DrawScreen(statusbar, 8);
    for (std::int32_t i = 0; i < 77; i++)
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
    std::int32_t d = 32;
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

    std::int32_t t = 6;

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
            std::int32_t dist = GetXDistance(obj);
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
            std::int32_t d = GetXDistance(obj);
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

    std::int32_t t = 2;
    std::int32_t d = std::abs(hero_object->X - (obj->X + 8));

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

    for (std::int32_t i = 0; i < 2; i++)
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

void Program::InitJIcon(std::int32_t command)
{
    icon_mode = command;
    std::int32_t scr = 4;
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
        std::int32_t scr = 4;
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

void Program::Interrupt()
{
    single_keys |= static_cast<std::uint8_t>(pressed_keys & (~last_keys));
    last_keys = pressed_keys;

    pressed_keys = PressedKeysStatus;

#ifndef NOT_PORTED_YET
    //if (kempston != nullptr && (setup_form == nullptr || setup_form->getActiveControl() == nullptr))
    if (kempston != nullptr && m_setup_form == nullptr)
    {

        for (std::int32_t i = 0; i < 8; i++)
        {
            bool is_press = false;
            if (kempston_buttons[i]->isAxis)
            {
                float val = 0.5f;
                if (kempston_buttons[i]->AxisNum == 0)
                {
                    val = kempston->GetAxisPosition(JoystickAxis::Horizontal);
                }
                else if (kempston_buttons[i]->AxisNum == 1)
                {
                    val = kempston->GetAxisPosition(JoystickAxis::Vertical);
                }
                if (val == kempston_buttons[i]->AxisDirection)
                {
                    is_press = true;
                }
            }
            else if (kempston_buttons[i]->isButton && kempston->GetButtonState(kempston_buttons[i]->ButtonNum) == ButtonKeyState::Pressed)
            {
                is_press = true;
            }
            if (is_press)
            {
                std::int32_t nn = i;
                if (i == 4)
                {
                    nn = 5;
                }
                else if (i == 5)
                {
                    nn = 6;
                }
                else if (i == 6)
                {
                    nn = 4;
                }
                pressed_keys |= static_cast<std::uint8_t>(1 << nn);
            }
        }
    }
#endif

#ifndef NOT_PORTED_YET
    if (x_input_controller->IsConnected)
    {
        x_input_gamepad = x_input_controller->GetState().Gamepad;

        if (x_input_gamepad.LeftThumbY > 15000 || x_input_gamepad.Buttons == GamepadButtonFlags::DPadUp)
        {
            pressed_keys |= 1;
        }

        if (x_input_gamepad.LeftThumbY < -15000 || x_input_gamepad.Buttons == GamepadButtonFlags::DPadDown)
        {
            pressed_keys |= 2;
        }

        if (x_input_gamepad.LeftThumbX < -15000 || x_input_gamepad.Buttons == GamepadButtonFlags::DPadLeft)
        {
            pressed_keys |= 4;
        }

        if (x_input_gamepad.LeftThumbX > 15000 || x_input_gamepad.Buttons == GamepadButtonFlags::DPadRight)
        {
            pressed_keys |= 8;
        }

        if (x_input_gamepad.Buttons == GamepadButtonFlags::X)
        {
            pressed_keys |= 32;
            pressed_key_symbol = 1;
        }

        if (x_input_gamepad.Buttons == GamepadButtonFlags::A)
        {
            pressed_keys |= 64;
            pressed_key_symbol = 1;
        }

        if (x_input_gamepad.Buttons == GamepadButtonFlags::B)
        {
            pressed_keys |= 16;
            pressed_key_symbol = 1;
        }

        if (x_input_gamepad.Buttons == GamepadButtonFlags::Back)
        {
            pressed_keys |= 128;
            pressed_key_symbol = 1;
        }

    }
#endif

    if (pressed_keys != 0)
    {
        keys_repeat_counter++;
        if (keys_repeat_counter == 40)
        {
            keys_repeat_counter = 35;
            single_keys = pressed_keys;
        }
    }
    else
    {
        keys_repeat_counter = 0;
    }

    interrupt_counter++;
    if (interrupt_counter == 256)
    {
        interrupt_counter = 0;
    }

    if ((interrupt_counter & 1) == 0)
    {
        //инициализация для случайной анимации
        if ((rnd->Next() & 31) == 0)
        {
            for (std::int32_t i = 0; i < 4; i++)
            {
                if (RndTimerTiles[i] == 8)
                {
                    RndTimerTiles[i] = 0;
                }
            }
        }

        //счётчики анимации
        for (std::int32_t i = 0; i < 4; i++)
        {
            TimerCounters[i]++;
            if (TimerCounters[i] == i + 1)
            {
                TimerCounters[i] = 0;
                TimerTiles[i]++;
                if (TimerTiles[i] == 8)
                {
                    TimerTiles[i] = 0;
                }
            }
        }

        //счётчики случайной анимации
        for (std::int32_t i = 0; i < 4; i++)
        {
            RndTimerCounters[i]++;
            if (RndTimerCounters[i] == i + 1)
            {
                RndTimerCounters[i] = 0;
                if (RndTimerTiles[i] != 8)
                {
                    RndTimerTiles[i]++;
                }
            }
        }
    }

    //приоритеты воспроизведения звуковых эффектов
    if (sfx_busy != 0)
    {
        sfx_busy--;
        if (sfx_busy == 0)
        {
            current_sfx_priority = 0;
        }
    }
}

bool Program::GetKey(std::uint8_t key)
{
    std::int32_t mask = disable_control ? 0 : 255;
    mask |= 0x80;
    return (pressed_keys & key & mask) != 0;
}

bool Program::GetLastKey(std::uint8_t key)
{
    return (last_keys & key) != 0;
}

bool Program::GetPressedKey(std::uint8_t key)
{
    return (single_keys & key) != 0;
}

void Program::NextPressedKey()
{
    single_keys = 0;
}

void Program::InitFonts()
{
    std::string langStr = language;
    toLower(langStr);

    std::string path = "./res/fonts/font_" + langStr + ".ch8";

    std::vector<uint8_t> f;
    File::ReadAllBytes(path, f);

    next_mini_powerups = std::make_shared<Surface>("./res/fonts/platformer_mode_font.png");

    std::int32_t n = 0;
    for (std::int32_t j = 0; j < 256; j++)
    {
        for (std::int32_t i = 0; i < 8; i++)
        {
            std::int32_t a = f[n++];

            for (std::int32_t s = 0; s < 8; s++)
            {
                font32[j][s][i] = (((a << s) & 128) == 0) ? false : true;
            }
        }
    }
}

void Program::DrawSymbol32(std::int32_t x, std::int32_t y, std::uint8_t symbol, std::uint8_t attr)
{
    Color paper = GetAttrColor(attr, false);
    Color ink = GetAttrColor(attr, true);
    if (attr == 0)
    {
        paper = attr_layer[0][x * 8][y * 8];
        ink = attr_layer[1][x * 8][y * 8];
    }
    Color pix;
    for (std::int32_t j = 0; j < 8; j++)
    {
        for (std::int32_t i = 0; i < 8; i++)
        {
            pix = font32[symbol][i][j] ^ invert_print ? ink : paper;
            screen->Draw(Point(x * 8 + i, y * 8 + j), pix);
        }
    }
}

void Program::PrintString32(std::int32_t x, std::int32_t y, const std::string &text)
{
    for (size_t i = 0; i < text.length(); i++)
    {
        DrawSymbol32(x + i, y, static_cast<std::uint8_t>(text[i]), 0);
    }
}

void Program::LoadTexts()
{
    InitFonts();

    std::string path = "./res/texts/" + language + ".bin";

    File::ReadAllBytes(path, texts);
}

std::int32_t Program::FindText(std::int32_t num)
{
    std::int32_t i = 0;
    std::int32_t pos = 0;
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

std::int32_t Program::NextString(std::int32_t pos)
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

std::int32_t Program::PrintString(std::int32_t pos, std::int32_t x, std::int32_t y)
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

void Program::InitText(std::int32_t text_num, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, std::uint8_t attr)
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
    std::uint8_t sym = texts[text_pos];
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

void Program::PrintText(std::int32_t num, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, std::uint8_t attr)
{
    InitText(num, x, y, width, height, attr);
    while (PrintSymbol())
    {

    }
}

void Program::ScrollWindow(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height)
{
    x = x * 8;
    y = y * 8;
    width = width * 8;
    height = height * 8;

    screen->CopyPixels( Point(x, y), SdlDotNetCompat::Drawing::Rectangle(x, y + 8, width, height - 8) );
    ///screen->SetPixels(Point(x, y), screen->GetColors(System::Drawing::Rectangle(x, y + 8, width, height - 8)));
    screen->Fill(SdlDotNetCompat::Drawing::Rectangle(x, y + height - 8, width, 8), Color::Black);
}

void Program::DrawSymbolLine(std::int32_t x, std::int32_t y, std::uint8_t symbol, std::int32_t line)
{
    Color paper = Color::Black; // attr_layer[0, x * 8, y];
    Color ink = Color::White; // attr_layer[1, x * 8, y];
    Color pix;
    for (std::int32_t i = 0; i < 8; i++)
    {
        pix = font32[symbol][i][line] ? ink : paper;
        screen->Draw(Point(x * 8 + i, y), pix);
    }
}

std::int32_t Program::PrintStringLine()
{
    std::int32_t p = text_pos;
    std::int32_t x = titles_x;
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
    std::int32_t x = titles_x * 8;
    std::int32_t y = titles_y * 8;
    std::int32_t width = titles_width * 8;
    std::int32_t height = titles_height * 8;

    screen->CopyPixels( Point(x, y), SdlDotNetCompat::Drawing::Rectangle(x, y + 1, width, height - 1) );
    ///screen->SetPixels(Point(x, y), screen->GetColors(System::Drawing::Rectangle(x, y + 1, width, height - 1)));
    screen->Fill(SdlDotNetCompat::Drawing::Rectangle(x, y + height - 1, width, 1), Color::Black);
}
}
