#include "DeltaShadow.Program.h"

    std::int32_t interrupt_counter = 0; //счётчик прерываний
    std::int32_t game_cicle_counter = 0; //счётчик игровых циклов

    std::int32_t TimerCounters[4];    //таймеры для анимации тайлов
    std::int32_t TimerTiles[4];       //номера тайлов для анимации
    std::int32_t RndTimerCounters[4]; //таймеры для случайной анимации тайлов
    std::int32_t RndTimerTiles[4];    //номера тайлов для случайной анимации

    Key KeysMap[8] = {Key::W, Key::S, Key::A, Key::D, Key::M, Key::B, Key::N, Key::P}; //карта кнопок
    const Key KeysMapStandart[8] = {Key::W, Key::S, Key::A, Key::D, Key::M, Key::B, Key::N, Key::P}; //карта кнопок
    std::uint8_t pressed_keys = 0; //состояние кнопок управления (побитовое)
    std::uint8_t last_keys = 0; //предыдущее состояние кнопок
    std::uint8_t single_keys = 0; //одиночно нажатые кнопки

    enum
    {
        Key_Up = 0x01
      , Key_Down = 0x02
      , Key_Left = 0x04
      , Key_Right = 0x08
      , Key_Select = 0x10
      , Key_Fire = 0x20
      , Key_Jump = 0x40
      , Key_Pause = 0x80
    };

    std::int32_t pressed_key_symbol = 0; //символ последней нажатой кнопки
    Key pressed_key = static_cast<Key>(0);

    std::int32_t keys_repeat_counter = 0;

    //имитация прерывания
    void Interrupt();

    //проверить, нажата-ли кнопка
    bool GetKey(std::uint8_t key);

    //проверить предыдущее состояние кнопок
    bool GetLastKey(std::uint8_t key);

    //проверить одиночное нажатие кнопки
    bool GetPressedKey(std::uint8_t key);

    void NextPressedKey();