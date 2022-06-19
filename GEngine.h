    SdlDotNetCompat::Drawing::Color next_palette[256];

    SdlDotNetCompat::Drawing::Color attr_palette[2][16]; //классическая палитра

    std::shared_ptr<Util::Random> rnd = std::make_shared<Util::Random>(); //генератор случайных чисел

public:
    std::shared_ptr<SdlDotNetCompat::Graphics::Surface> screen;
private:
    std::shared_ptr<SdlDotNetCompat::Graphics::Surface> screen_copy; //копия экрана
    std::shared_ptr<SdlDotNetCompat::Graphics::Surface> scroll_screen; //экран для скроллинга комнаты
public:

    SdlDotNetCompat::Drawing::Color attr_layer[2][256][192]; //атрибутный слой экрана для вывода монохромных спрайтов

private:
    std::int32_t scroll_direction = 0; //направление скроллинга, 1 - вверх, 2 - вправо, 3 - вниз, 4 - влево
    std::int32_t scroll_cntr = 0; //счётчик скроллинга

    //инициализация графического движка
    void InitGEngine();

    //функция возвращает цвет, соответствующий цвету ZX Spectrum [0..15]
public:
    SdlDotNetCompat::Drawing::Color GetColor(std::int32_t zxcolor);

    //очистка экрана
private:
    void ClearScreen();

    //заливка атрибутного прямоугольника и очистка пискелей
    void FillAttrRect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, std::uint8_t attr);

    void InitRoomTiles();

    //инициализация комнаты локации
    void InitRoom(bool new_hero_cord);

    //добавить тайл в локацию (кроме анимированных тайлов) координаты в тайлах
    void NewTile(std::int32_t x, std::int32_t y, std::int32_t num);

    //задание полной перерисовки комнаты
    void FullRoomRedraw();

    //прорисовка тайлов комнаты
    void DrawRoom();

    //прорисовка тайлового объекта
    void DrawTileObject(const std::shared_ptr<GameObject> &obj);

    //прорисовка объекта символа
    void DrawSymbolObject(const std::shared_ptr<GameObject> &obj);

    //прорисовка игровых объектов
    std::int32_t sprite_bottom = 160;
    void DrawGameObject(const std::shared_ptr<GameObject> &obj);
    void DrawGameObjects();

    //скролл комнаты
    void ScrollRoom();

    //установить значение шкалы
    void SetScale(std::int32_t x, std::int32_t y, std::int32_t value);

    //нарисовать столбик для шкалы
    void SetScaleCol(std::int32_t x, std::int32_t y);

    //стреть столбик для шкалы
    void ResScaleCol(std::int32_t x, std::int32_t y);

    //загрузка проекта локации и тайлсетов
    std::uint8_t current_tilesets[2][256][37];

    void LoadLocationProject(std::int32_t num);

    //прорисовка классического тайлсета
    void DrawClassicTileset();

    //проверка на необходимость скроллинга комнаты
    void NeedScrollRoom();

    //увеличить game_cicle_counter
    void IncGameCicleCounter();

    void SetBorder(const SdlDotNetCompat::Drawing::Color &c);
