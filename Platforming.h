    std::int32_t location_status = 0; //текущий статус локации
    std::int32_t location_counter = 0; //счётчик для всяких действий в локации
    std::int32_t start_life = 0, start_energy = 0, start_weapon = 0; //значения на страте локации

    //инициализация режима платформинга
    void InitPlatforming(bool boss);

    //инициализация статусбара платформинга
    void InitPlatformingStatusbar();

    std::int32_t fall_down_effect[16][10];

    //инициализация локации
    std::int32_t start_slot = 0;
    std::int32_t room_cntr = 0; //уменьшающийся счётчик пройденных комнат, после инициализации равен 2.
    std::int32_t battery_cntr = 0; //сч-к уменьшения батарейки костюма
    std::int32_t level_music = 0; //трек уровня
    bool reverse_way = false; //прохождение уровня из конца в начало
    void InitLocation(bool boss);

    //инициализация DLC стелса
    void InitDLCStatusbar();


    //проверка конами-кода
    std::int32_t TestKonamiCode_pos = 0;
    std::int32_t TestKonamiCode_cnt = 0;
    std::vector<std::uint8_t> TestKonamiCode_txt = {Key_Up, Key_Down, Key_Up, Key_Down, Key_Left, Key_Left, Key_Right, Key_Right, Key_Fire, Key_Jump, 0xff};
    void TestKonamiCode();

    //обновление  платформенного уровня
    std::int32_t last_boss_fase = 0;
    void UpdatePlatforming();

    //уровень пройден
    void LevelComlete();

    //инициализация режима иконки статус-бара
    void InitIcon(std::int32_t command);

    //обновление иконки статус-бара
    void UpdateIcon();

    //инициализация финального босса
    std::int32_t final_scens_show = 0;
    void InitFinalBoss(std::int32_t fase);