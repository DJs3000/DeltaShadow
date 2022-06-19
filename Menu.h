    //инициализация отладочного меню
    void InitDebugMenu();

    std::vector<std::string> level_names = {"Race", "Jacqueline", "Level 1-1", "Level 1-2", "Level 1-3", "Dragon 1", "Boss 1", "Level 2-1", "Level 2-2", "Level 2-3", "Dragon 2", "Boss 2", "Level 3-1", "Level 3-2", "Level 3-3", "Dragon 3", "Boss 3", "Level 4-1", "Level 4-2", "Level 4-3", "Level 4-4", "Level 4-5", "Level 4-6", "Level 4-7", "FinalBoss", "Extra 1-4", "Extra 2-4", "Extra 3-4", "Extra 4-8", "Jacqueline DLC"};

    //прорисовка отладочного меню
    void DrawDebugMenu();

    //обновление отладочного меню

    std::int32_t menu_pos = 29;
    void UpdateDebugMenu();

    //инициализация game over
    void InitGameOver();

    //обновление game over
    void UpdateGameOver();

    //инициализация выбора уровня
    std::int32_t select_level_status = 0;
    std::int32_t select_level_fase = 0;
    std::uint8_t levels_complete = 0;
    bool last_tower = false;
    std::uint8_t menu_keys = 0;
    std::shared_ptr<ScreensProject> select_level_screens;
    void InitSelectLevel();

    //обновление выбора уровня
    void UpdateSelectLevel();

    std::int32_t pictogramm_y = 0;
    std::int32_t pictogramm_pos = 0;
    std::shared_ptr<ScreensProject> pictogramm_screens;

    void InitSay(std::int32_t text_num, std::int32_t pictogramm);

    bool UpdateNovaSay();

    bool UpdateJacquelineSay();

    //обновление режима загрузочного экрана

    std::int32_t lspp = 255;
    void UpdateLoadScreen();

    //инициализация главного меню
    std::shared_ptr<ScreensProject> main_menu_scr;
    std::int32_t main_menu_pos = 0;
    std::int32_t prev_game_mode = 0; //из какого режима вошли в main_menu
    std::int32_t current_music = 0; //текущий трек уроня
    void InitMainMenu(bool hard_init);

    //обновление главного меню
    void UpdateMainMenu();

    std::int32_t new_game_pos = 0;
    void UpdateNewGame();

    std::int32_t cancel_mission_pos = 0;
    void UpdateCancelMission();

    void InitSelectDiff();

    void UpdateSelectDiff();

    void InitSelectMessage();

    std::int32_t select_message_home = 0;
    std::int32_t select_message_pos = 0;
    void UpdateSelectMessage();

    std::int32_t read_message_num = 0;
    std::int32_t read_message_home = 0;
    bool read_message_scroll = false;
    bool read_message_down = false;
    void UpdateReadMessage();

    void InitSettings();

    std::int32_t settings_pos = 0;
    void UpdateSettings();

    std::int32_t control_pos = 0;
    void UpdateControlsSettings();

    std::int32_t redefine_pos = 0;
    std::int32_t redefine_pause = 0;
    SdlDotNetCompat::Input::Key KeysMapNew[8];
    std::vector<std::int32_t> redefine_tab = {2, 3, 0, 1, 5, 6, 4, 7};
    void UpdateRedefine();

    std::int32_t graphic_pos = 0;
    void UpdateGraphicSettings();

    std::int32_t sound_pos = 0;
    void UpdateSoundSettings();

    std::int32_t system_pos = 0;
    void UpdateSystemSettings();

    void UpdateAreYouSure();

    std::int32_t reset_pos = 0;
    void UpdateReset();

    std::int32_t player_home = 0;
    std::int32_t player_pos = 0;
    void UpdatePlayer();

    void InitNewGame();

    //навигатор по меню
    std::int32_t MenuNavigation(std::int32_t current_pos, std::int32_t min, std::int32_t max);

    void PrintDemoVersion();
