    //обработка игровых объектов
    void ProcessingGameObject(const std::shared_ptr<GameObject> &obj);

    //Нова
    bool immortal_mode = false;
    bool on_ladder = false;
    bool on_wall = false;
    bool on_roof = false;
    bool is_jump = false;
    bool is_fly = false;
    bool hero_die = false;
    bool boss_mode = false;
    std::int32_t attack_cntr = 0;
    std::int32_t slide_cntr = 0;
    std::int32_t hero_weapon_max = 0;
    bool disable_control = false;
    bool extern_move = false;
    bool in_water = false;

    void Nova(const std::shared_ptr<GameObject> &obj);


    //для Жаклин из DLC
    bool gun_on = false;
    bool double_jump_on = false;
    bool is_double_jump = false;
    void DLCJacqueline(const std::shared_ptr<GameObject> &obj);

    //поверапы
    void PowerUp(const std::shared_ptr<GameObject> &obj);

    //убить объект, когда закончится анимация
    void KillWhileStopAnimation(const std::shared_ptr<GameObject> &obj);

    void MultiExplosions(const std::shared_ptr<GameObject> &obj);

    //вентилятор
    void Blower(const std::shared_ptr<GameObject> &obj);

    //пузыри
    void Bubble(const std::shared_ptr<GameObject> &obj);

    //бумеранг
    void Bumerang(const std::shared_ptr<GameObject> &obj);

    //энергетическая волна
    void Wave(const std::shared_ptr<GameObject> &obj);

    //платформа
    void Platform(const std::shared_ptr<GameObject> &obj);

    //пар
    void Steam(const std::shared_ptr<GameObject> &obj);

    //осколки
    void Fraction(const std::shared_ptr<GameObject> &obj);

    //дверь
    void Door(const std::shared_ptr<GameObject> &obj);

    //танкетка
    void Tankette(const std::shared_ptr<GameObject> &obj);

    //дрон
    void Dron(const std::shared_ptr<GameObject> &obj);

    //пуля
    void Bullet(const std::shared_ptr<GameObject> &obj);

    //паук
    void Spider(const std::shared_ptr<GameObject> &obj);

    //пиранья
    void Piranha(const std::shared_ptr<GameObject> &obj);

    //медуза
    void Jelly(const std::shared_ptr<GameObject> &obj);

    //паучье гнездо
    void SpiderNest(const std::shared_ptr<GameObject> &obj);

    //жук
    void Bug(const std::shared_ptr<GameObject> &obj);

    //пушка
    void Gun(const std::shared_ptr<GameObject> &obj);

    //летающие враги (ракетчик и бомбер)
    void FlyEnemy(const std::shared_ptr<GameObject> &obj);

    //подземный коготь
    void AlienClaw(const std::shared_ptr<GameObject> &obj);

    //червяк
    void AlienWorm(const std::shared_ptr<GameObject> &obj);

    //слизь
    void Slime(const std::shared_ptr<GameObject> &obj);

    //звуковой враг
    void SonusVenator(const std::shared_ptr<GameObject> &obj);


    //босс большой паук
    void BigSpider(const std::shared_ptr<GameObject> &obj);

    //кракен
    void Craken(const std::shared_ptr<GameObject> &obj);

    //мотылёк
    void Moth(const std::shared_ptr<GameObject> &obj);

    //босс Рокетмэн
    void Rocketman(const std::shared_ptr<GameObject> &obj);

    //босс краб
    void CrabBoss(const std::shared_ptr<GameObject> &obj);

    //летающий босс
    void FlyBoss(const std::shared_ptr<GameObject> &obj);

    //первая фаза финального босса
    void AlienPet(const std::shared_ptr<GameObject> &obj);

    //вторая фаза финального босса
    bool boss_magnit_on = false;
    void AlienSliderman(const std::shared_ptr<GameObject> &obj);

    //третья фаза финального босса
    void Megabrain(const std::shared_ptr<GameObject> &obj);


    //самонаводящаяся ракета
    void Rocket(const std::shared_ptr<GameObject> &obj);

    //мини-мозг
    void MiniBrain(const std::shared_ptr<GameObject> &obj);

    //бомба
    void Bomb(const std::shared_ptr<GameObject> &obj);

    //летающая бомба
    void FlyBomb(const std::shared_ptr<GameObject> &obj);

    //магнит к объекту
    void Magnit(const std::shared_ptr<GameObject> &obj, std::int32_t x_dist, std::int32_t x_area, std::int32_t x_force);

    //генератор пузырей
    void BubbleGenerator(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset, std::int32_t yoffset);



    //пуля Жаклин
    void DLCBullet(const std::shared_ptr<GameObject> &obj);

    //защита Жаклин
    void DLCBubble(const std::shared_ptr<GameObject> &obj);

    //DLC поверапы
    void DLCPowerUp(const std::shared_ptr<GameObject> &obj);

    //DLC дракон
    void Dragon(const std::shared_ptr<GameObject> &obj);