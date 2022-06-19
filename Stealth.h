    bool alarm_on = false;
    bool init_alarm = false;
    std::int32_t alarm_cntr = 0;
    std::array<bool, 16> stealth_flags;
    std::int32_t start_stealth_music = 0;

    bool stealth_pause = false; //стелс на паузе

    //инициализация стелс уровня
    void InitStealth();

    //получить состояние stealth_flags
    bool GetStealth(std::int32_t num);

    //установить состояние stealth_flags
    void SetStealth(std::int32_t num);


    //инициализация статусбара стелса
    void InitStelthStatusbar();

    //обновление стелс уровня
    void UpdateStealth();

    //Жаклин
    bool hero_invisible = false;
    bool j_game_over = false;
    bool j_win = false;
    bool hero_moved = false;
    bool j_skip_cicle = false;
    void Jacqueline(const std::shared_ptr<GameObject> &obj);

    //полицейский
    void JPolice(const std::shared_ptr<GameObject> &obj);

    //офисные работники
    void JOffice(const std::shared_ptr<GameObject> &obj);

    //пуля
    void JBullet(const std::shared_ptr<GameObject> &obj);

    //лифт
    std::int32_t lift_moves = 0;
    std::int32_t next_lift_num = 1;
    std::int32_t lift_pause = 0;
    std::shared_ptr<GameObject> lift_object;
    void JLift(const std::shared_ptr<GameObject> &obj);

    //дверь
    std::uint8_t return_room = 0;
    void JDoor(const std::shared_ptr<GameObject> &obj);

    //поиск объекта двери в активных объектах
    std::shared_ptr<Program::GameObject> FindDoor();

    //терминал
    std::int32_t terminal_num = 0;
    std::shared_ptr<GameObject> current_door;
    void JTerminal(const std::shared_ptr<GameObject> &obj);

    //инициализация анимаций с учётом невидимости Жаклин
    void InitJAnimation(const std::shared_ptr<GameObject> &obj, const std::string &anim, bool hard);

    //спавн объектов для стелса
    void StealthSpawn(const std::shared_ptr<GameObject> &obj);

    //урон для объекта
    bool JDamage(const std::shared_ptr<GameObject> &obj);

    //включение паники у офисных работников
    void JOfficePanic();

    //проверяем что между объектом и Жаклин нет офисного работника
    bool JCover(const std::shared_ptr<GameObject> &obj);

    //инициализация режима иконки статус-бара
    void InitJIcon(std::int32_t command);

    //обновление иконки статус-бара
    void UpdateJIcon();