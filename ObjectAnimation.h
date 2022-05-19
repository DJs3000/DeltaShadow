private:
    class ObjectAnimation : public std::enable_shared_from_this<ObjectAnimation>
    {
    public:
        std::string Name; //имя анимации

        //класс спрайта
    public:
        class Sprite : public std::enable_shared_from_this<Sprite>
        {
        public:
            std::string  Name; //имя спрайта
            std::int32_t Type = 0; //тип спрайта
            std::int32_t Width = 0; //ширина спрайта
            std::int32_t Height = 0; //высота спрайта
            std::int32_t **ClassicLayer; //слой для классического режима
            SdlDotNetCompat::Drawing::Color **NextLayer; //слой для режима Next
        };
    public:
        std::vector<std::shared_ptr<Sprite>> Sprites = std::vector<std::shared_ptr<Sprite>>(); //список спрайтов

        //класс элемента композиции
    public:
        class CompositionElement : public std::enable_shared_from_this<CompositionElement>
        {
        public:
            std::shared_ptr<Sprite> ElemSprite; //спрайт элемента композиции
            std::int32_t XOffset = 0; //смещение спрайта по X
            std::int32_t YOffset = 0; //смещение спрайта по Y
        };

        //класс кадра
    public:
        class Frame : public std::enable_shared_from_this<Frame>
        {
        public:
            std::vector<std::shared_ptr<CompositionElement>> Composition; //список элементов в композиции
            std::int32_t Time = 0; //время проигрывания кадра во фреймах
            std::int32_t DX1 = 0, DY1 = 0, DX2 = 0, DY2 = 0; //коллайдер повреждения
            std::int32_t HX1 = 0, HY1 = 0, HX2 = 0, HY2 = 0; //коллайдер удара
            std::string  Event; //название события
        };

        //класс анимации
    public:
        class Animation : public std::enable_shared_from_this<Animation>
        {
        public:
            std::string Name; //имя анимации
            std::vector<std::shared_ptr<Frame>> Frames; //список кадров
            bool Loop = false; //анимация зациклена
        };

    public:
        std::vector<std::shared_ptr<Animation>> Animations = std::vector<std::shared_ptr<Animation>>(); //список анимаций
    };

private:
    std::vector<std::shared_ptr<ObjectAnimation>> ObjectAnimations = std::vector<std::shared_ptr<ObjectAnimation>>(); //наборы анимаций объектов

    //загрузка анимаций по имени
    void LoadAnimations(const std::string &name);

    //загрузка проекта анимаций
    void LoadAnimationsProject(const std::string &name);

    //поиск спрайта по имени
    std::shared_ptr<ObjectAnimation::Sprite> FindSprite(const std::string &name, const std::shared_ptr<ObjectAnimation> &anim);

    //инициализация анимации по имени
    void InitAnimation(const std::shared_ptr<GameObject> &obj, const std::string &name, bool hard_enable);

    void InitAnimation(const std::shared_ptr<GameObject> &obj, std::uint8_t id_anim, bool hard_enable);

    //проигрывание анимации (вызывается каждый игровой цикл)
    void PlayAnimation(const std::shared_ptr<GameObject> &obj);

    //высота и ширина объекта
    void GetObjSize(const std::shared_ptr<Program::GameObject> &obj);

    //поиск набора анимаций по имени
    std::vector<std::shared_ptr<Program::ObjectAnimation>> FindObjectAnimation(const std::string &name);
