#include "DeltaShadow.Program.h"

private:

    bool font32[256][8][8];
    std::vector<uint8_t> texts;
    bool invert_print = false;
    std::shared_ptr<SdlDotNetCompat::Graphics::Surface> next_mini_powerups;

    //инициализация шрифтов
public:
    void InitFonts();

    //вывод символа шрифтом font32
private:
    void DrawSymbol32(std::int32_t x, std::int32_t y, std::uint8_t symbol, std::uint8_t attr);

    //печать строки шрифтом font32
    void PrintString32(std::int32_t x, std::int32_t y, const std::string &text);

    //загрузка игровых текстов
public:
    void LoadTexts();

    //найти текст по номеру
private:
    std::int32_t FindText(std::int32_t num);

    std::int32_t NextString(std::int32_t pos);

    std::int32_t PrintString(std::int32_t pos, std::int32_t x, std::int32_t y);

    //инициализация вывода текста в окне
    std::int32_t text_pos = 0, text_x = 0, text_y = 0, text_counter = 0;
    std::int32_t x_win = 0, y_win = 0, width_win = 0, height_win = 0;
    void InitText(std::int32_t text_num, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, std::uint8_t attr);

    //печать символа
    bool type_with_sound = false;
    bool PrintSymbol();

    //печать текста в окне
    void PrintText(std::int32_t num, std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, std::uint8_t attr);

    //скроллировать окно на 8 пикселей вверх
    void ScrollWindow(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height);

    //вывод линии символа, только для прототипа
    void DrawSymbolLine(std::int32_t x, std::int32_t y, std::uint8_t symbol, std::int32_t line);

    //печать линии текста, только для прототипа
    std::int32_t PrintStringLine();

    //скроллировать титры на 1 пиксель
    std::int32_t titles_x = 0, titles_y = 0, titles_width = 0, titles_height = 0;
    void ScrollCredits();