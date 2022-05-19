#include "GameObjectsSubprog.h"

bool Program::Gravity(const std::shared_ptr<Program::GameObject> &obj)
{
    ga = 0;
    gb = 0;
    if (obj->PlatformObject != nullptr && obj->YAccel >= 0)
    {
        return false;
    }

    int32_t v = 24;
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

    int32_t ydelta = obj->YAccel / 4;
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
            int32_t temp_y = obj->Y;
            int32_t temp_ya = obj->YAccel;
            obj->Y &= 0xfff0;
            obj->YAccel = 0;

            int32_t a = GetProperty(obj, -obj->Width, -1);
            int32_t b = GetProperty(obj, obj->Width, -1);
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

bool Program::MoveObjectForward(const std::shared_ptr<Program::GameObject> &obj, int32_t speed)
{
    if (obj->Direction)
    {
        speed = -speed;
    }

    if (obj->Name == idNova && current_suit != 2 && !on_roof && GetProperty(obj, 0, -1) == isWater)
    {
        speed = speed * 6 / 8;
    }

    int32_t delta = speed / 2;
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

    int32_t dx = obj->Width + std::abs(delta);
    int32_t dy = -1;
    int32_t t;
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

bool Program::SimpleMoveObjectForward(const std::shared_ptr<GameObject> &obj, int32_t speed)
{
    int32_t b = 0;
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

void Program::CreateBullet(const std::shared_ptr<GameObject> &obj, const std::string &animations, const std::string &anim_name, int32_t xoffset, int32_t yoffset, int32_t xdelta, int32_t ydelta, bool damageble)
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

bool Program::TestShoot(const std::shared_ptr<GameObject> &obj, int32_t xoffset, int32_t yoffset, int32_t direct)
{
    if (!InCurrentRoom(obj))
    {
        return false;
    }
    int32_t i;
    int32_t x = (obj->X + xoffset) / 16;
    int32_t y = (obj->Y + yoffset) / 16;
    int32_t h_x = hero_object->X / 16;
    int32_t h_y1 = (hero_object->Y + hero_object->Height) / 16;
    int32_t h_y2 = hero_object->Y / 16;
    if (direct == 0)
    {
        if (!SeeOnHero(obj) || y < h_y1 || y >= h_y2)
        {
            return false;
        }

        int32_t dx = 1;
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

        int32_t dy = 1;
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

        int32_t dx = 1;
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

int32_t Program::ObjectsCount(int32_t name)
{
    int32_t i = 0;
    for (const auto &obj : actual_objects)
    {
        if (obj->Name == name)
        {
            i++;
        }
    }
    return i;
}

void Program::CreateExplosion(const std::shared_ptr<GameObject> &obj, int32_t xoffset, int32_t yoffset)
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

uint8_t Program::GetXDistance(const std::shared_ptr<GameObject> &obj)
{
    int32_t dist = std::abs(hero_object->X - obj->X);
    if (dist >= 256)
    {
        return 255;
    }
    else
    {
        return static_cast<uint8_t>(dist);
    }

}

uint8_t Program::GetYDistance(const std::shared_ptr<GameObject> &obj)
{
    int32_t dist = obj->Y - hero_object->Y;
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
        return static_cast<uint8_t>(dist);
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

int32_t Program::GetProperty(const std::shared_ptr<GameObject> &obj, int32_t xoffset, int32_t yoffset)
{
    if (obj->Direction)
    {
        xoffset = -xoffset;
    }

    return (GetFullProperty(obj, xoffset, yoffset) >> 5) & 7;
}

int32_t Program::GetFullProperty(const std::shared_ptr<GameObject> &obj, int32_t xoffset, int32_t yoffset)
{
    int32_t x = (obj->X + xoffset) / 16;
    int32_t y = (obj->Y + yoffset) / 16;
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

int32_t Program::GetXYProperty(int32_t x, int32_t y)
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

void Program::CreateFractions(const std::shared_ptr<GameObject> &obj, int32_t num)
{
    if (graphics_quality == 0)
    {
        return;
    }

    int32_t max = 8;
    if (graphics_quality == 1)
    {
        max = 3;
        num /= 2;
    }
    for (int32_t i = 0; i < num; i++)
    {
        if (particle_cntr < max)
        {
            int32_t x = 3 - (rnd->Next() & 7);
            for (int32_t j = 0; j < 8; j++)
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

    uint8_t b = 0;
    uint8_t c = 0;
    uint8_t d = 0;

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
    int32_t a = GetProperty(obj, -obj->Width, 1);
    int32_t b = GetProperty(obj, obj->Width, 1);
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

bool Program::HeroDamage(const std::shared_ptr<GameObject> &obj, int32_t yoffset)
{
    if (disable_control || hero_object->UndeadCounter != 0 || hero_life == 0 || hero_die)
    {
        return false;
    }

    int32_t w = obj->Width;
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

std::shared_ptr<Program::GameObject> Program::EnemyDamage(const std::shared_ptr<Program::GameObject> &obj, int32_t xdist)
{
    std::shared_ptr<GameObject> r = nullptr;
    int32_t ra = 6;
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

bool Program::InRange(int32_t a, int32_t b, int32_t value)
{
    if (std::abs(a - b) < value)
    {
        return true;
    }
    return false;
}

bool Program::ObjCentrum(const std::shared_ptr<GameObject> &obj, int32_t xoffset)
{
    if (GetKey(Key_Left + Key_Right))
    {
        return true;
    }

    if (hero_object->X < obj->X + xoffset)
    {
        pressed_keys = static_cast<uint8_t>(pressed_keys | Key_Right);
    }
    else
    {
        pressed_keys = static_cast<uint8_t>(pressed_keys | Key_Left);
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
        for (int32_t i = 0; i < 256; i++)
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
