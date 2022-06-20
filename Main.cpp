// NOTE: preferences (tile mode - zx_classic_mode OR zx_next_mode)
std::string Program::language = "English";
int32_t Program::sprite_mode = zx_next_mode;
int32_t Program::tiles_mode = zx_next_mode;

void Program::MainInit()
{
    start_weapon = 20;
    start_life   = 77;
    start_energy = 77;

    for (int32_t i = 0; i < 16; i++)
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
    for (int32_t i = 0; i < 8; i++)
    {
        f.Write(static_cast<uint8_t>(KeysMap[i]));
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
    for (int32_t i = 0; i < 4; i++)
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
    for (int32_t i = 0; i < 8; i++)
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
    for (int32_t i = 0; i < 4; i++)
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
