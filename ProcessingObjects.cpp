#include "ProcessingObjects.h"

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

        int32_t xt = obj->X & 15;

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
                int32_t d = obj->Width + 8;
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
                int32_t a = GetProperty(obj, obj->Width, obj->Height - 2);
                int32_t b = GetProperty(obj, -obj->Width, obj->Height - 2);
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
                                pressed_keys = static_cast<uint8_t>(pressed_keys | Key_Right);
                            }
                            else
                            {
                                pressed_keys = static_cast<uint8_t>(pressed_keys | Key_Left);
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
                    int32_t p = GetProperty(obj, 12, -40);
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
                                pressed_keys = static_cast<uint8_t>(Key_Right);
                            }
                            else
                            {
                                pressed_keys = static_cast<uint8_t>(Key_Left);
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
                        int32_t a = GetProperty(obj, 0, 0);
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

                            int32_t last_y = obj->Y;
                            obj->Y = (obj->Y & 0xfff0) + 9 + 16;
                            int32_t q = 16;
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

                    int32_t spd = 3;
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
                            int32_t q = GetProperty(obj, 2, -48);
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
                        int32_t q = 7;
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
                        int32_t q = 7;
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
        int32_t xw = 10;
        int32_t yw = -20;
        int32_t xd = 5;
        int32_t yd = 0;
        int32_t dir = 2;
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

    int32_t xt = obj->X & 15;

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
                            pressed_keys = static_cast<uint8_t>(pressed_keys | Key_Right);
                        }
                        else
                        {
                            pressed_keys = static_cast<uint8_t>(pressed_keys | Key_Left);
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
                        pressed_keys = static_cast<uint8_t>(Key_Right);
                    }
                    else
                    {
                        pressed_keys = static_cast<uint8_t>(Key_Left);
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

        int32_t speed = 3;
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
        int32_t high = -26;
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

    int32_t i = obj->Type & 0x7f;
    if (obj->Counter >= 113)
    {
        i += (obj->Counter & 15) / 4;
    }
    obj->XAccel = i;

    int32_t d = 5;
    int32_t e = 20;
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
            collected_stars |= (static_cast<uint64_t>(1) << obj->Status);
            stars_num++;
            noreaded_stars |= (static_cast<uint64_t>(1) << (stars_num - 1));
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

    int32_t x = rnd->Next() & 31 - 15;
    int32_t y = rnd->Next() & 31 - 15;
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
        int32_t x = obj->XTile;
        int32_t y = obj->YTile;
        int32_t i = game_cicle_counter / 2;
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

    int32_t speed = std::min(4, obj->YAccel / 4);
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
    int32_t a = GetProperty(obj, 0, 0);
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
        int32_t x = obj->X / 16;
        int32_t y = obj->Y / 16;

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
        int32_t dx = -16;
        int32_t dy = -16;
        for (int32_t j = 0; j < 3; j++)
        {
            for (int32_t i = 0; i < 3; i++)
            {
                int32_t p = TilesetProperty[ Loc[x][y] ];
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
    int32_t xoffset = 0;
    int32_t yoffset = 0;

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
                int32_t a = (GetFullProperty(o, o->Width + 1, o->Height) >> 5) & 7;
                int32_t b = (GetFullProperty(o, o->Width + 1, -1) >> 5) & 7;
                int32_t c = (GetFullProperty(o, -o->Width - 1, o->Height) >> 5) & 7;
                int32_t d = (GetFullProperty(o, -o->Width - 1, -1) >> 5) & 7;
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
    int32_t i = GetProperty(obj, 0, 0);
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

    int32_t d = GetXDistance(obj);
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
            int32_t h = obj->Y - hero_object->Y + 16;
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
    int32_t speed = 2;

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
    int32_t x = obj->XTile - 1;
    int32_t y = obj->YTile - 2;

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

    int32_t i = (game_cicle_counter >> 2) & 3;
    NewTile(x, y, 21 + i);
    NewTile(x + 1, y, 25);
    NewTile(x, y + 1, 26 + ((i >> 1) & 1));
    NewTile(x + 1, y + 1, 28 + i);

    if (obj->Counter != 0)
    {
        obj->Counter--;
    }

    //считаем кол-во пауков на экране
    int32_t c = 0;
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
            for (int32_t i = 0; i < 2; i++)
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

    int32_t dx = GetXDistance(obj);
    int32_t dy = std::abs(obj->Y - hero_object->Y);
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

    int32_t dx = std::abs(obj->X - obj->XTarget);
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

            int32_t n = obj->Status / 4;
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
                    int32_t x = -96;
                    if ((rnd->Next() & 1) == 0)
                    {
                        x = 80;
                    }
                    int32_t y = -32;
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

        int32_t d;
        int32_t x = obj->X - hero_object->X;
        if (std::abs(x) < 8)
        {
            x = 0;
        }
        int32_t y = obj->Y - (hero_object->Y + hero_object->Height + 8);
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

        int32_t a;
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
        int32_t dx = obj->X - hero_object->X;
        int32_t dy = obj->Y - hero_object->Y + 20;
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

void Program::Magnit(const std::shared_ptr<GameObject> &obj, int32_t x_dist, int32_t x_area, int32_t x_force)
{
    for (const auto &o : actual_objects)
    {
        if ((o->Name == idNova && !on_roof && !on_wall) || o->Name == idBubble)
        {
            int32_t dx = obj->X - o->X + 8;
            if (std::abs(dx) >= x_dist && std::abs(dx) < x_area)
            {
                bool t = o->Direction;
                uint8_t n = o->Name;
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

void Program::BubbleGenerator(const std::shared_ptr<GameObject> &obj, int32_t xoffset, int32_t yoffset)
{
    if (graphics_quality == 0)
    {
        return;
    }

    int32_t max = 3;
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

    int32_t i = obj->Type & 0x7f;
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
