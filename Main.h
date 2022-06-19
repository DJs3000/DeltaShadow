    bool external_resource = false; //разрешение использования внешних ресурсов
    bool demo_version = false;

    bool cheats_enabled = false;

    bool debug_mode = true;
public:
    static std::string language;
private:
    enum ReleaseType
    {
        classic_version = 0
      , next_version = 1
    };
    std::int32_t release_type = next_version;

    enum GameMode
    {
        debug_menu_mode = 0
      , platforming_mode = 1
      , race_mode = 2
      , game_over_mode = 3
      , stealth_mode = 4
      , clip_mode = 5
      , suit_mode = 6
      , select_level_mode = 7
      , main_menu_mode = 8
      , new_game_mode = 9
      , select_diff_mode = 10
      , cancel_mission_mode = 11
      , select_message_mode = 12
      , read_message_mode = 13
      , load_screen_mode = 14
      , settings_mode = 15
      , control_settings_mode = 16
      , redefine_mode = 17
      , graphic_settings_mode = 18
      , sound_settings_mode = 19
      , system_settings_mode = 20
      , areyousure_mode = 21
      , reset_mode = 22
      , player_mode = 23
    }
    game_mode = debug_menu_mode; //режим игры;

public:
    static std::int32_t sprite_mode; //режим спрайтов
    static std::int32_t tiles_mode; //режим тайлов
private:
    enum ZXMode
    {
        zx_classic_mode = 0
      , zx_next_mode = 1
    };

    enum SoundMode
    {
        one_ay_mode = 0
      , ts_mode = 1
    };

    std::int32_t sound_mode = one_ay_mode; //режим музыки

    std::array<std::shared_ptr<GameObject>, 128> game_objects;   //список всех объектов локации
    std::array<std::shared_ptr<GameObject>, 128> actual_objects; //ссылки на актуальные объекты
    std::shared_ptr<GameObject> hero_object; //объект героя
    bool hero_start_direction = false;

    enum Priority
    {
        low_priority = 0
      , normal_priority = 1
      , high_priority = 2
    };

    std::int32_t difficulty = 0; //режим сложности игры
    std::int32_t max_difficulty = 1; //максимальный уровень сложности

    bool music_on = true;
    bool sound_on = true;

    bool scroll_on = true;

    std::uint64_t collected_stars = 0x01; // битовый массив собранных звёзд, 48 бит, 6 байт, одна звезда сразу открыта
    std::uint64_t noreaded_stars = 0x01; //битовый массив непросмотренных звёзд, 48 бит
    std::int32_t stars_num = 1; //кол-во собранных звёзд

    std::int32_t graphics_quality = 2; //настройки качества графики

    bool in_boss_room = false; //герой в комнате босса
    std::int32_t **Loc; //массив с локацией
    std::int32_t LocWidth = 0;
    std::int32_t LocHeight = 0;

    std::shared_ptr<SdlDotNetCompat::Graphics::Surface> Tileset[2][256];

    SdlDotNetCompat::Drawing::Color TilesetAttr[2][256][16][16];  //атрибуты тайлсета для атрибутного слоя

    std::int32_t TilesetProperty[256];  //свойства тайлов в тайлсете

    std::vector<std::shared_ptr<AnimTile>> RoomAnimTiles = std::vector<std::shared_ptr<AnimTile>>(); //список анимированных тайлов в комнате

    std::vector<std::vector<std::shared_ptr<RoomLayers>>> RoomsLayers; //массив слоёв в комнатах локации

    bool secret_boss_enabled = false; //включен секретный босс

    std::int32_t current_suit = 0; //режим костюма, 0 - без костюма

    bool have_suit[4];  //костюмы в наличии (0 - без костюма)

    bool no_suit_run = false;

    //свойства тайлов
    enum TileProperties
    {
        isEmpty = 0
      , isFloor = 1
      , isLadder = 2
      , isWater = 3
      , isSpike = 4
      , isPlatform = 5
      , isRails = 6
      , isShift = 7
    };

    std::int32_t particle_cntr = 0; //счётчик частиц

    std::int32_t current_level = 1; //номер текущего уровня
    std::int32_t current_location = 1; //номер текущей локации
    std::int32_t x_home = 0, y_home = 0; //координаты верхнего левого угла комнаты в пикселях
    std::int32_t x_home_tile = 0, y_home_tile = 0; //координаты верхнего левого угла комнаты в тайлах
    std::uint8_t current_xy_room = 0; //текущая координата комнаты

    std::int32_t Room[16][10];

    bool screen_refresh_tab[16][10];

    //сохранение для безопасного возвращения
    std::uint8_t last_safe_xy_room = 0; //координата безопасной комнаты
    std::int32_t last_safe_x = 0, last_safe_y = 0; //координаты героя в безопасной комнате
    bool last_safe_direction = false; //направление героя в безопасной комнате

    bool bw_color_mode = false; //черно-белый режим

    bool kempston_on = false;

    class ScreensProject; // NOTE: forward declaration

    std::shared_ptr<ScreensProject> statusbar;
    std::shared_ptr<ScreensProject> select_menu;

    std::unordered_map<std::string, std::uint8_t> objects_names = std::unordered_map<std::string, std::uint8_t>();
    std::unordered_map<std::int32_t, std::string> levels_names = std::unordered_map<std::int32_t, std::string>();
    std::unordered_map<std::int32_t, std::string> music_names = std::unordered_map<std::int32_t, std::string>();

    //------------------------------------- основной блок -------------------------------------

    //инициализация главной формы
public:
    void MainInit();

    //сохранение прогресса игры
    static std::string current_save_version;
private:
    void SaveProgress();

    //загрузка прогресса игры
    bool loaded_progress = false;
    void LoadProgress();

    /////старт игры
    ///void StartTimer_Tick(const std::shared_ptr<void> &sender, const std::shared_ptr<SdlDotNetCompat::EventArgs> &e);

    //главный цикл
    std::int32_t pause_cnt = 0; //только для прототипа
    void MainCicle();
