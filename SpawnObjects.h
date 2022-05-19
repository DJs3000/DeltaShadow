    //объект является врагом
    bool isEnemy(const std::shared_ptr<GameObject> &obj);

    //спавн объектов комнаты
    std::int32_t cntr_enter_in_room = 0; // счётчик, равен 2 после того как герой вошёл в комнату
    void SpawnObjects(const std::shared_ptr<GameObject> &obj);