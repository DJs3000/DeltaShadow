private:
    std::shared_ptr<ScreensProject> race_imgs;

    std::array<std::int32_t, 32> race_objects;
    std::int32_t bike_y_pos = 0; //позиция по Y
    std::int32_t bike_y_accel = 0; //ускорение по Y
    std::int32_t bike_y_offset = 0; //смещение по Y
    std::int32_t bike_down_counter = 0; //счётчик отката вниз
    std::int32_t bike_undead = 0; //счётчик бессмертия

    bool race_win = false;
    bool race_lose = false;
    std::int32_t race_exit_timer = 0; //таймер выхода из гонки
    std::int32_t race_turn_counter = 0; //счётчик для поворота
    bool turn_direction = false; //направление поворота, false - влево, true - вправо
    std::int32_t top_x = 0;
    std::int32_t race_pos = 0; //максимальное значение 2500, массив препятствий 825 элементов
    std::int32_t top_fase = 0;
    std::int32_t trace_pos = 0; //индекс в trace
    std::int32_t trace_pause = 0; //пауза в чтении trace

    bool race_pause = false; //гонка на паузе

    std::string top_name;

    //инициализация гонки
    void InitRace();

    //прорисовка верха
    void DrawRaceTop();

    //обновление гонки
    void UpdateRace();

    //уменьшение энергии Новы
    void DecLife(const std::shared_ptr<GameObject> &obj, std::int32_t value);

    enum
    {
        t_pause = 0x80
      , t_right = 0x01
      , t_center = 0x02
      , t_left = 0x04
      , t_tramplin = 0x08
      , t_turn_left = 0x10
      , t_turn_right = 0x20
    };

    std::vector<std::int32_t> trace;
    std::vector<std::int32_t> trace_1 = {t_pause + 20, t_turn_right, t_turn_left, t_pause + 5, t_turn_right, t_turn_left, t_left + t_right, t_left + t_right, t_left + t_right, t_left + t_right, t_center, t_pause + 15, t_turn_right, t_tramplin + t_center, t_center, t_left + t_center, t_right, t_tramplin + t_center, t_center, t_left + t_center, t_center, t_right, t_tramplin + t_left, t_left + t_right, t_center, t_tramplin + t_right, t_left + t_right, t_left + t_center, t_pause + 5, t_tramplin + t_center, t_center, t_left, t_left, t_left + t_center, t_left + t_center, t_left + t_center, t_pause + 15, t_turn_left, t_pause + 5, t_tramplin + t_left, t_left, t_tramplin + t_center, t_center, t_left, t_tramplin + t_right, t_right, t_center, t_center, t_pause + 10, t_turn_right, t_turn_left, t_right, t_tramplin + t_center, t_center, t_right, t_tramplin + t_center, t_center, t_right, t_center, t_center + t_right, t_center + t_right, t_pause + 15, t_turn_left, t_turn_right, t_turn_left, t_pause + 5, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_tramplin + t_left, t_left + t_right, t_pause + 15, t_tramplin + t_center, t_center, t_pause + 25, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_turn_right, t_turn_left, t_turn_right, t_tramplin + t_left, t_left + t_right, t_center, t_tramplin + t_left + t_right, t_left + t_right, t_tramplin + t_center, t_center, t_pause + 5, t_tramplin + t_right, t_left + t_right, t_left + t_right, t_left + t_right, 0};

    std::vector<std::int32_t> trace_2 = {t_pause + 20, t_turn_right, t_left + t_right, t_pause + 15, t_turn_left, t_pause + 5, t_turn_right, t_turn_left, t_pause + 5, t_left + t_right, t_left + t_right, t_left + t_right, t_center, t_pause + 5, t_tramplin + t_center, t_center, t_left, t_left, t_left + t_center, t_left + t_center, t_left + t_center, t_pause + 5, t_tramplin + t_right, t_left + t_right, t_left + t_right, t_left + t_right, t_pause + 15, t_turn_left, t_turn_right, t_turn_left, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_turn_right, t_tramplin + t_left, t_left, t_tramplin + t_center, t_center, t_left, t_tramplin + t_right, t_right, t_center, t_center, t_pause + 15, t_turn_right, t_tramplin + t_center, t_center, t_left + t_center, t_right, t_tramplin + t_center, t_center, t_left + t_center, t_center, t_right, t_tramplin + t_left, t_left + t_right, t_center, t_tramplin + t_right, t_left + t_right, t_left + t_center, t_pause + 10, t_turn_left, t_turn_left, t_right, t_tramplin + t_center, t_center, t_right, t_tramplin + t_center, t_center, t_right, t_center, t_center + t_right, t_center + t_right, t_pause + 5, t_tramplin + t_left, t_left + t_right, t_pause + 15, t_tramplin + t_center, t_center, t_pause + 25, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_turn_right, t_turn_left, t_turn_right, t_tramplin + t_left, t_left + t_right, t_center, t_tramplin + t_left + t_right, t_left + t_right, t_tramplin + t_center, t_center, 0};

    std::vector<std::int32_t> trace_3 = {t_pause + 20, t_turn_left, t_left + t_right, t_pause + 15, t_turn_right, t_turn_left, t_turn_right, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_turn_left, t_tramplin + t_left, t_left, t_tramplin + t_center, t_center, t_right, t_tramplin + t_left, t_left, t_center, t_pause + 5, t_tramplin + t_center, t_center, t_left, t_left, t_left + t_center, t_left + t_center, t_left + t_center, t_pause + 10, t_turn_right, t_turn_left, t_right, t_tramplin + t_center, t_center, t_right, t_tramplin + t_center, t_center, t_right, t_center, t_center + t_right, t_center + t_right, t_pause + 5, t_tramplin + t_left, t_left + t_right, t_pause + 15, t_turn_right, t_pause + 5, t_turn_left, t_turn_right, t_pause + 5, t_left + t_right, t_left + t_right, t_left + t_right, t_center, t_center, t_pause + 15, t_tramplin + t_center, t_center, t_pause + 15, t_turn_right, t_tramplin + t_center, t_center, t_left + t_center, t_right, t_tramplin + t_center, t_center, t_left + t_center, t_center, t_right, t_tramplin + t_left, t_left, t_center, t_tramplin + t_right, t_left + t_right, t_left + t_center, t_pause + 5, t_tramplin + t_right, t_left + t_right, t_left + t_right, t_left + t_right, t_pause + 25, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_turn_left, t_turn_left, t_turn_right, t_tramplin + t_left, t_left, t_center + t_right, t_tramplin + t_left + t_right, t_left + t_right, t_tramplin + t_center, t_center, 0};

    std::vector<std::int32_t> trace_4 = {t_pause + 20, t_turn_left, t_turn_right, t_pause + 5, t_turn_right, t_turn_left, t_tramplin + t_center, t_center, t_tramplin + t_center, t_center, t_left + t_right, t_left + t_right, t_left + t_right, t_left + t_right, t_center, t_pause + 10, t_turn_right, t_turn_left, t_right, t_right, t_right, t_center, t_center + t_right, t_center + t_right, t_pause + 5, t_left, t_left, t_left, t_left + t_center, t_left + t_center, t_left + t_center, t_pause + 5, t_left + t_right, t_left + t_right, t_left + t_right, t_pause + 15, t_turn_left, t_left, t_center, t_pause + 5, t_tramplin + t_left, t_left + t_right, t_tramplin + t_center, t_center, t_left, t_tramplin + t_right, t_right, t_center, t_pause + 15, t_turn_right, t_tramplin + t_center, t_center, t_left + t_center, t_right, t_tramplin + t_center, t_center, t_left + t_center, t_center, t_right, t_tramplin + t_left, t_left, t_center, t_tramplin + t_right, t_left + t_right, t_left + t_center, t_pause + 15, t_turn_right, t_turn_left, t_turn_right, t_left + t_right, t_center, t_tramplin + t_left + t_right, t_left + t_right, t_center + t_right, t_pause + 15, t_turn_left, t_turn_right, t_turn_left, t_tramplin + t_right, t_pause + 5, t_tramplin + t_right, t_left + t_center + t_right, t_tramplin + t_left, t_pause + 15, t_tramplin + t_left, t_left + t_center + t_right, t_tramplin + t_center, t_pause + 15, t_tramplin + t_center, t_left + t_center + t_right, t_pause + 25, t_tramplin + t_right, t_left + t_center + t_right, 0};

    std::vector<std::int32_t> turn_faze = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 9, 10, 11, 9, 10, 11, 9, 10, 11, 6, 7, 8, 3, 4, 5, 0, 1, 2};