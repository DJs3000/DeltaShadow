public:
    class Tile : public std::enable_shared_from_this<Tile>
    {
    public:
        std::vector<std::uint8_t> data; //данные спрайта
        std::shared_ptr<SdlDotNetCompat::Graphics::Surface> img; //изображение спрайта
    };

public:
    class Sprite : public std::enable_shared_from_this<Sprite>
    {
    public:
        std::string name; //имя спрайта
        std::int32_t height = 0; //ширина спрайта в символах
        std::int32_t width = 0; //высота спрайта в символах

        std::shared_ptr<Tile> **tiles; // массив тайлов
    };

public:
    class ScreenSprite : public std::enable_shared_from_this<ScreenSprite>
    {
    public:
        std::shared_ptr<Sprite> sprite; //спрайт
        std::int32_t x_cord = 0; //координата X
        std::int32_t y_cord = 0; //координата Y
    };

public:
    class Screen : public std::enable_shared_from_this<Screen>
    {
    public:
        std::string name; //имя экрана
        bool visible = false; //показыать экран
        std::vector<std::shared_ptr<ScreenSprite>> sprites;
    };

private:
    class ScreensProject : public std::enable_shared_from_this<ScreensProject>
    {
    public:
        std::vector<std::shared_ptr<Tile>>   Tileset;
        std::vector<std::shared_ptr<Sprite>> Sprites;
        std::vector<std::shared_ptr<Screen>> Screens;
    };

    //инициализцация проекта экранов
private:
    std::shared_ptr<Program::ScreensProject> InitScreensProject(const std::string &name);

    //добавить тайл в тайлсет
    std::shared_ptr<Program::Tile> AddTile(const std::shared_ptr<Program::ScreensProject> &obj, std::vector<std::uint8_t> &data);

public:
    SdlDotNetCompat::Drawing::Color GetAttrColor(std::uint8_t attr, bool enable);

    //поиск спрайта по имени в списке Sprites
private:
    std::shared_ptr<Program::Sprite> FindSprite(const std::shared_ptr<Program::ScreensProject> &proj, const std::string &name);

    //поиск экрана по имени в списке Screens
    std::shared_ptr<Program::Screen> FindScreen(const std::shared_ptr<Program::ScreensProject> &proj, const std::string &name);

    //вывод экрана

    void DrawScreen(const std::shared_ptr<ScreensProject> &proj, std::int32_t num);

    //вывод экранного спрайта по заданным координатам и обрезанного по окну
    void DrawScreenSprite(const std::shared_ptr<ScreensProject> &proj, const std::string &name, std::int32_t xcord, std::int32_t ycord, std::int32_t xwin, std::int32_t ywin, std::int32_t width, std::int32_t height);