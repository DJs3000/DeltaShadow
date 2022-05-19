#include "System.h"

void Program::Interrupt()
{
    single_keys |= static_cast<uint8_t>(pressed_keys & (~last_keys));
    last_keys = pressed_keys;

    pressed_keys = PressedKeysStatus;

#ifndef NOT_PORTED_YET
    //if (kempston != nullptr && (setup_form == nullptr || setup_form->getActiveControl() == nullptr))
    if (kempston != nullptr && m_setup_form == nullptr)
    {

        for (int32_t i = 0; i < 8; i++)
        {
            bool is_press = false;
            if (kempston_buttons[i]->isAxis)
            {
                float val = 0.5f;
                if (kempston_buttons[i]->AxisNum == 0)
                {
                    val = kempston->GetAxisPosition(JoystickAxis::Horizontal);
                }
                else if (kempston_buttons[i]->AxisNum == 1)
                {
                    val = kempston->GetAxisPosition(JoystickAxis::Vertical);
                }
                if (val == kempston_buttons[i]->AxisDirection)
                {
                    is_press = true;
                }
            }
            else if (kempston_buttons[i]->isButton && kempston->GetButtonState(kempston_buttons[i]->ButtonNum) == ButtonKeyState::Pressed)
            {
                is_press = true;
            }
            if (is_press)
            {
                int32_t nn = i;
                if (i == 4)
                {
                    nn = 5;
                }
                else if (i == 5)
                {
                    nn = 6;
                }
                else if (i == 6)
                {
                    nn = 4;
                }
                pressed_keys |= static_cast<uint8_t>(1 << nn);
            }
        }
    }
#endif

#ifndef NOT_PORTED_YET
    if (x_input_controller->IsConnected)
    {
        x_input_gamepad = x_input_controller->GetState().Gamepad;

        if (x_input_gamepad.LeftThumbY > 15000 || x_input_gamepad.Buttons == GamepadButtonFlags::DPadUp)
        {
            pressed_keys |= 1;
        }

        if (x_input_gamepad.LeftThumbY < -15000 || x_input_gamepad.Buttons == GamepadButtonFlags::DPadDown)
        {
            pressed_keys |= 2;
        }

        if (x_input_gamepad.LeftThumbX < -15000 || x_input_gamepad.Buttons == GamepadButtonFlags::DPadLeft)
        {
            pressed_keys |= 4;
        }

        if (x_input_gamepad.LeftThumbX > 15000 || x_input_gamepad.Buttons == GamepadButtonFlags::DPadRight)
        {
            pressed_keys |= 8;
        }

        if (x_input_gamepad.Buttons == GamepadButtonFlags::X)
        {
            pressed_keys |= 32;
            pressed_key_symbol = 1;
        }

        if (x_input_gamepad.Buttons == GamepadButtonFlags::A)
        {
            pressed_keys |= 64;
            pressed_key_symbol = 1;
        }

        if (x_input_gamepad.Buttons == GamepadButtonFlags::B)
        {
            pressed_keys |= 16;
            pressed_key_symbol = 1;
        }

        if (x_input_gamepad.Buttons == GamepadButtonFlags::Back)
        {
            pressed_keys |= 128;
            pressed_key_symbol = 1;
        }

    }
#endif

    if (pressed_keys != 0)
    {
        keys_repeat_counter++;
        if (keys_repeat_counter == 40)
        {
            keys_repeat_counter = 35;
            single_keys = pressed_keys;
        }
    }
    else
    {
        keys_repeat_counter = 0;
    }

    interrupt_counter++;
    if (interrupt_counter == 256)
    {
        interrupt_counter = 0;
    }

    if ((interrupt_counter & 1) == 0)
    {
        //инициализация для случайной анимации
        if ((rnd->Next() & 31) == 0)
        {
            for (int32_t i = 0; i < 4; i++)
            {
                if (RndTimerTiles[i] == 8)
                {
                    RndTimerTiles[i] = 0;
                }
            }
        }

        //счётчики анимации
        for (int32_t i = 0; i < 4; i++)
        {
            TimerCounters[i]++;
            if (TimerCounters[i] == i + 1)
            {
                TimerCounters[i] = 0;
                TimerTiles[i]++;
                if (TimerTiles[i] == 8)
                {
                    TimerTiles[i] = 0;
                }
            }
        }

        //счётчики случайной анимации
        for (int32_t i = 0; i < 4; i++)
        {
            RndTimerCounters[i]++;
            if (RndTimerCounters[i] == i + 1)
            {
                RndTimerCounters[i] = 0;
                if (RndTimerTiles[i] != 8)
                {
                    RndTimerTiles[i]++;
                }
            }
        }
    }

    //приоритеты воспроизведения звуковых эффектов
    if (sfx_busy != 0)
    {
        sfx_busy--;
        if (sfx_busy == 0)
        {
            current_sfx_priority = 0;
        }
    }
}

bool Program::GetKey(uint8_t key)
{
    int32_t mask = disable_control ? 0 : 255;
    mask |= 0x80;
    return (pressed_keys & key & mask) != 0;
}

bool Program::GetLastKey(uint8_t key)
{
    return (last_keys & key) != 0;
}

bool Program::GetPressedKey(uint8_t key)
{
    return (single_keys & key) != 0;
}

void Program::NextPressedKey()
{
    single_keys = 0;
}