    //id объектов
    enum
    {
          idNova = 1
        , idDust = 2
        , idExplosion = 3
        , idRocketSmoke = 4
        , idMultiExplosions = 5
        , idBlower = 6
        , idBubble = 7
        , idBumerang = 8
        , idWave = 9
        , idBattery = 10
        , idHeart = 11
        , idPowerup = 12
        , idMiniBattery = 13
        , idMiniHeart = 14
        , idMiniPowerup = 15
        , idSuit = 16
        , idStar = 17
        , idPlatform = 18
        , idSteam = 19
        , idFraction = 20
        , idDoor = 21
        , idTankette = 22
        , idDron = 23
        , idBullet = 24
        , idSpider = 25
        , idPiranha = 26
        , idBigPiranha = 27
        , idJelly = 28
        , idSpiderNest = 29
        , idBug = 30
        , idGun = 31
        , idDragonfly = 32
        , idFighterBomber = 33
        , idDronBomber = 34
        , idAlienClawBottom = 35
        , idAlienClawTop = 36
        , idAlienWorm = 37
        , idSlime = 38
        , idSonusVenator = 39
        , idBigSpider = 40
        , idCraken = 41
        , idMoth = 42
        , idRocketman = 43
        , idCrabBoss = 44
        , idFlyBoss = 45
        , idAlienPet = 46
        , idAlienSliderman = 47
        , idMegabrain = 48
        , idRocket = 49
        , idMiniBrain = 50
        , idBomb = 51
        , idFlyBomb = 52
        , idWaterFun = 53
        , idBubbleGenerator = 54
        , idJacqueline = 55
        , idJLift = 56
        , idJDoor = 57
        , idJTerminal = 58
        , idJPolice1 = 59
        , idJPolice2 = 60
        , idJPolice3 = 61
        , idJOffice1 = 62
        , idJOffice2 = 63
        , idJOffice3 = 64
        , idNovaBike = 65
        , idDLCBullet = 66
        , idJDJump = 67
        , idJGun = 68
        , idJShield = 69
        , idJBubble = 70
        , idDragon = 71
    };

    //описатель игрового объекта
private:
    class ObjectAnimation;
    class GameObject : public std::enable_shared_from_this<GameObject>
    {
    public:
        bool NoActivated = false; //объект не активирован
        std::int32_t X1Trigger = 0, X2Trigger = 0, Y1Trigger = 0, Y2Trigger = 0; //координаты триггера спавна
        std::uint8_t XYRoom = 0; //координаты комнаты с точкой спавна
        std::uint8_t Name = 0; //имя игрового объекта
        std::int32_t Life = 0; //жизненная энергия объекта
        std::uint8_t Status = 0; //статус объекта
        std::uint8_t Priority = 0; //приоритет прорисовки, 0 - самый дальний план, 2 - самый ближний
        std::int32_t X = 0, Y = 0; //координаты на экране
        std::int32_t Width = 0, Height = 0; //текущая ширина и высота объекта (из данных коллайдера)
        std::int32_t XTarget = 0, YTarget = 0; //координаты цели
        std::int32_t XTile = 0, YTile = 0; //координаты объекта в тайлах
        std::int32_t XAccel = 0; //ускорение по X
        std::int32_t YAccel = 0; //ускорение по Y
        bool Direction = false; //направление спрайта, false - вправо, true - влево
        bool Left = false, Down = false, Up = false, Right = false; //направление входа в комнату для активации объекта
        bool Fixed = false; //объект имеет фиксированные координаты
        std::uint8_t Type = 0; //тип объекта, 0 - спрайт, 1-127 - тайл, 128-255 - [символ - 128]
        bool haveGravity = false; //у объекта есть гравитация
        bool isDamageable = false; //объект можно уничтожить
        bool NoInterruptAnim = false; //непрерываемая анимация, автоматически сбрасывается по окончании анимации
        bool NoVisible = false; //объект невидимый
        std::int32_t Counter = 0; //счётчик общего назначения
        std::uint8_t UndeadCounter = 0; //счётчик бессмертия
        std::shared_ptr<GameObject> PlatformObject; //объект платформы, на которой находится объект

        std::vector<std::shared_ptr<ObjectAnimation>> Animations; //анимации игрового объекта
        bool AnimationPlayed = false; //проигрывается анимация
        std::int32_t Frame = 0; //номер кадра текущей анимации
        std::int32_t CurrentAnimation = 0; //номер текущей анимации
        std::int32_t AnimCounter = 0; //счётчик для проигрываемого кадра
    };

    //создать игровой объект
private:
    std::shared_ptr<Program::GameObject> CreateObject(std::uint8_t name, std::int32_t x, std::int32_t y, bool direction, bool actual_object);

    //удалить объект
    void RemoveObject(const std::shared_ptr<GameObject> &obj);

    //удалить все объекты
    void ClearAllObjects();

    //очистить список актуальных объектов
    void ClearActualObjectsList();

    //добавить игровой объект в список актуальных
    void AddActualObject(const std::shared_ptr<GameObject> &obj);

    //удалить игровой объект из списка актуальных
    void RemoveActualObject(const std::shared_ptr<GameObject> &obj);

    //создать дочерний игровой объект со смещениями, с учётом direction
    std::shared_ptr<Program::GameObject> CreateChild(const std::shared_ptr<Program::GameObject> &obj, std::uint8_t name, std::int32_t xoffset, std::int32_t yoffset);
