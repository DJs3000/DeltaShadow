#include "SpawnObjects.h"

bool Program::isEnemy(const std::shared_ptr<GameObject> &obj)
{
    std::vector<int32_t> e = {idTankette, idDron, idSpider, idPiranha, idBigPiranha, idJelly, idBug, idDronBomber, idGun, idDragonfly, idFighterBomber, idAlienWorm, idSlime, idSonusVenator};
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
        int32_t c = 0;
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
        int32_t sfx = 255;
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
            int32_t a = reverse_way ? 0 : 1;
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
            int32_t n = 0;
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
                if ((collected_stars & (static_cast<uint64_t>(1) << obj->Status)) == 0)
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
            obj->Type = static_cast<uint8_t>(n);
            obj->XAccel = static_cast<uint8_t>(n);
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
            int32_t t = 0;
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
            obj->Type = static_cast<uint8_t>(t);
            obj->XAccel = static_cast<uint8_t>(t);
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