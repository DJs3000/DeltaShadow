    //обработчик событий объекта
private:
    class GameObject; // NOTE: forward declaration

    void DoEvent(const std::shared_ptr<GameObject> &obj, const std::string &e);

    //возвращение героя в safe point
    void Event_safepoint(const std::shared_ptr<GameObject> &obj);

    //создание осколков взрыва
    void Event_fraction(const std::shared_ptr<GameObject> &obj);

    //двери открылись
    void Event_door_open(const std::shared_ptr<GameObject> &obj);

    //двери закрылись
    void Event_door_close(const std::shared_ptr<GameObject> &obj);

    //создание пули танкетки
    void Event_tankshoot(const std::shared_ptr<GameObject> &obj);

    //создание снаряда пушки
    void Event_gunshoot(const std::shared_ptr<GameObject> &obj);

    //создание горизонтальной пули дрона
    void Event_dronshoot0(const std::shared_ptr<GameObject> &obj);

    //создание диагональной пули дрона
    void Event_dronshoot1(const std::shared_ptr<GameObject> &obj);

    void Event_show_hero(const std::shared_ptr<GameObject> &obj);

    //Жаклин входит в дверь
    void Event_jdoor(const std::shared_ptr<GameObject> &obj);

    //вход Жаклин в дверь после хака
    void Event_in_door(const std::shared_ptr<GameObject> &obj);

    //выстрел Жаклин
    void Event_jshoot(const std::shared_ptr<GameObject> &obj);

    //атака полицейского
    void Event_police_attack(const std::shared_ptr<GameObject> &obj);

    //выстрел полицейского
    void Event_police_shoot(const std::shared_ptr<GameObject> &obj);

    //полицейский оглядывается назад
    void Event_police_seeback(const std::shared_ptr<GameObject> &obj);

    //звук прибывшего лифта
    void Event_sfx_elevator();

    //звук взлома двери
    void Event_sfx_doors();

    //звук работы с терминалом
    void Event_sfx_terminal();

    //запуск ракеты
    void Event_lounchrocket(const std::shared_ptr<GameObject> &obj);

    //прыжок
    void Event_jump(const std::shared_ptr<GameObject> &obj, std::int32_t accel);

    //выстрел медузы
    void Event_jelly_shoot(const std::shared_ptr<GameObject> &obj);

    //выстрел краба клешнёй
    void Event_crab_shoot(const std::shared_ptr<GameObject> &obj);
    void Event_crab_upshoot(const std::shared_ptr<GameObject> &obj);

    //атака лучём
    void Event_ray_shot(const std::shared_ptr<GameObject> &obj, std::int32_t x_distance, std::int32_t y_distance);

    //атака финального босса второй фазы
    void Event_slider_attack(const std::shared_ptr<GameObject> &obj);

    //вкл/выкл магнита финального босса второй фазы
    void Event_slider_magnit_on();
    void Event_slider_magnit_off();

    void Event_dragonfire(const std::shared_ptr<GameObject> &obj);
