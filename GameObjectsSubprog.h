    //гравитация объекта,возвращает true если объект в воздухе
    std::int32_t ga = 0, gb = 0;
    bool Gravity(const std::shared_ptr<Program::GameObject> &obj);

    void ChangeDirection(const std::shared_ptr<Program::GameObject> &obj);

    //движение объекта вперёд
    bool MoveObjectForward(const std::shared_ptr<Program::GameObject> &obj, std::int32_t speed);

    bool SimpleMoveObjectForward(const std::shared_ptr<GameObject> &obj, std::int32_t speed);

    //создать пулю
    void CreateBullet(const std::shared_ptr<GameObject> &obj, const std::string &animations, const std::string &anim_name, std::int32_t xoffset, std::int32_t yoffset, std::int32_t xdelta, std::int32_t ydelta, bool damageble);

    //проверка, попадёт-ли объект в героя в заданном направлении, 0 - прямо, 1 - вниз, 2 - диагональ вверх, 3 - диагональ вниз
    bool TestShoot(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset, std::int32_t yoffset, std::int32_t direct);

    //подсчёт кол-ва активных объектов определенного вида
    std::int32_t ObjectsCount(std::int32_t name);

    //создать взрыв на основе родительского объекта
    void CreateExplosion(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset, std::int32_t yoffset);

    //развернуть объект по направлению к герою
    void TurnObject(const std::shared_ptr<GameObject> &obj);

    //расчёт дистанции до героя
    std::uint8_t GetXDistance(const std::shared_ptr<GameObject> &obj);
    std::uint8_t GetYDistance(const std::shared_ptr<GameObject> &obj);

    //повёрнут-ли объект к другом объекту лицом
    bool SeeOnObject(const std::shared_ptr<GameObject> &obj1, const std::shared_ptr<GameObject> &obj2);

    //повёрнут-ли объект к герою
    bool SeeOnHero(const std::shared_ptr<GameObject> &obj);

    //объект находится в текущей комнате
    bool InCurrentRoom(const std::shared_ptr<GameObject> &obj);

    //взять свойство тайла относительно игрового объекта с учётом Direction
    std::int32_t GetProperty(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset, std::int32_t yoffset);

    //взять целое свойство тайла относительно игрового объекта
    std::int32_t GetFullProperty(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset, std::int32_t yoffset);

    //взять свойство тайла по координатам
    std::int32_t GetXYProperty(std::int32_t x, std::int32_t y);

    //поиск рельсы для подвижной платформы по направлению, 0 - вверх, 1 - вправо, 2 - вниз, 3 - влево
    bool GetRailsTile(const std::shared_ptr<GameObject> &obj);

    //создать осколки
    void CreateFractions(const std::shared_ptr<GameObject> &obj, std::int32_t num);

    //создать мини-бонус
    bool mini_bonus_ready = false;
    void CreateMiniBonus(const std::shared_ptr<GameObject> &obj);

    //тест на шипы и воду для врагов
    bool EnemyWaterSpikeTest(const std::shared_ptr<GameObject> &obj);

    //инициализация попадения героя на шипы
    void InitHeroSpike();

    //получение урона
    bool HeroDamage(const std::shared_ptr<GameObject> &obj, std::int32_t yoffset);

    //уменьшение жизни героя
    void DecreaseHeroLife();

    std::shared_ptr<Program::GameObject> EnemyDamage(const std::shared_ptr<Program::GameObject> &obj, std::int32_t xdist);

    //покачивание летающего объекта в воздухе
    void ObjWiggle(const std::shared_ptr<GameObject> &obj);

    bool FlyUp(const std::shared_ptr<GameObject> &obj);

    bool FlyDown(const std::shared_ptr<GameObject> &obj);

    void HeroOnRoof();

    bool InRange(std::int32_t a, std::int32_t b, std::int32_t value);

    //центровка по объекту
    bool ObjCentrum(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset);

    //обработчик смерти драконов и боссов
    bool BossDie(const std::shared_ptr<GameObject> &obj);
