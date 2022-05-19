#include "Program.h"

int32_t Program::screen_width = 0;
int32_t Program::screen_height = 0;
double Program::screen_scale = 3;
bool Program::full_screen_mode = false;
bool Program::prev_full_screen_mode = true;

std::shared_ptr<Joystick> Program::kempston = nullptr;
std::array<std::shared_ptr<DeltaShadow::joy_button>, 8> Program::kempston_buttons;
float Program::kempston_ax_v = 0;
float Program::kempston_ax_h = 0;
std::vector<SdlDotNetCompat::Input::ButtonKeyState> Program::kempston_btns;

#ifndef NOT_PORTED_YET
std::shared_ptr<Controller> Program::x_input_controller;
Gamepad Program::x_input_gamepad;
#endif

void Program::Main()
{
    LoadSettings();

    std::shared_ptr<Program> Game = std::make_shared<Program>();

    Game->Run();
}

Program::Program()
{
    InitVideo();

#ifndef NOT_PORTED_YET
    Video::WindowIcon(std::make_shared<Surface>(std::make_shared<Bitmap>(Properties->Resources::getIco32()->ToBitmap())));
#endif

    Video::SetWindowCaption("Delta's Shadow");

    MainInit();

#ifndef NOT_PORTED_YET
    x_input_controller = std::make_shared<Controller>(UserIndex::One);
#endif
}

void Program::Run()
{
    using namespace std::placeholders;

    StartKempston();

    Events::Quit         += std::bind(&Program::Quit        , this, _1, _2);
    Events::Tick         += std::bind(&Program::Update      , this, _1, _2);
    Events::SetTargetFps(50);
    Events::KeyboardDown += std::bind(&Program::KeyboardDown, this, _1, _2);
    Events::KeyboardUp   += std::bind(&Program::KeyboardUp  , this, _1, _2);
    Events::MouseMotion  += std::bind(&Program::MouseMotion , this, _1, _2);
    Events::VideoResize  += std::bind(&Program::VideoResize , this, _1, _2);

    Events::Run();
}

void Program::Quit(void *, QuitEventArgs *)
{
    //if (setup_form != nullptr && setup_form->getActiveControl() != nullptr)
#ifndef NOT_PORTED_YET
    if (m_setup_form != nullptr)
    {
        full_screen_mode = prev_full_screen_mode;
    }
#endif
    SaveSettings();

    Mouse::ShowCursor = true;

    Events::QuitApplication();
}

int32_t Program::x_screen_home = 16;
int32_t Program::y_screen_home = 16;

void Program::Update(void *, TickEventArgs *)
{
    if (show_cursor_timer != 0)
    {
        show_cursor_timer--;
    }

    if (hide_cursor_timer != 0)
    {
        hide_cursor_timer--;
        if (hide_cursor_timer == 0)
        {
            Mouse::ShowCursor = false;
            show_cursor_timer = 1;
        }
    }

    MainCicle();

    //чтение джойстика
#ifndef NOT_PORTED_YET
    if (kempston != nullptr)
    {
        kempston_ax_v = kempston->GetAxisPosition(JoystickAxis::Vertical);
        kempston_ax_h = kempston->GetAxisPosition(JoystickAxis::Horizontal);
        for (int32_t i = 0; i < kempston->NumberOfButtons(); i++)
        {
            kempston_btns[i] = kempston->GetButtonState(i);
        }
    }
#endif

    double s = screen_scale;

    if (full_screen_mode)
    {
        Size win;
        Environment::PrimaryScreen::Size(win.Width, win.Height);
        int32_t sx = win.Width / 256;
        int32_t sy = win.Height / 192;
        s = static_cast<double>(std::min(sx, sy));
    }

    Surface sur = screen->CreateScaledSurface(s);
    Video::Screen().Blit(sur, Point(static_cast<int32_t>(x_screen_home * s), static_cast<int32_t>(y_screen_home * s)));
    Video::Screen().Update();
    sur.Dispose();
}

void Program::MouseMotion(void*, MouseMotionEventArgs*)
{
    if (show_cursor_timer != 0)
    {
        return;
    }
    Mouse::ShowCursor = true;
    hide_cursor_timer = 150;
}

void Program::KeyboardDown(void *, KeyboardEventArgs *e)
{
    SdlDotNetCompat::Input::Key key = e->Key();

    if (key == Key::UpArrow)
    {
        key = KeysMap[0];
    }
    if (key == Key::DownArrow)
    {
        key = KeysMap[1];
    }
    if (key == Key::LeftArrow)
    {
        key = KeysMap[2];
    }
    if (key == Key::RightArrow)
    {
        key = KeysMap[3];
    }
    if (key == Key::Escape)
    {
        key = KeysMap[7];
    }

    if (key == KeysMap[0])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus | Key_Up);
    }
    if (key == KeysMap[1])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus | Key_Down);
    }
    if (key == KeysMap[2])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus | Key_Left);
    }
    if (key == KeysMap[3])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus | Key_Right);
    }
    if (key == KeysMap[4])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus | Key_Select);
    }
    if (key == KeysMap[5])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus | Key_Fire);
    }
    if (key == KeysMap[6])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus | Key_Jump);
    }
    if (key == KeysMap[7])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus | Key_Pause);
    }

    pressed_key_symbol = static_cast<int32_t>(key);
    pressed_key = key;

    if (pressed_key_symbol > static_cast<int32_t>('9'))
    {        
        if (key >= Key::A && key <= Key::Z)
        {
            pressed_key_symbol = (pressed_key_symbol - (Key::A - 'A')); // SDL key code to ASCII code conversion
        }
    }

    if ((key >= Key::Zero && key <= Key::Nine)
            || (key >= Key::A && key <= Key::Z)
            ||  key == Key::Return
            ||  key == Key::KeypadEnter
            ||  key == Key::LeftShift
            ||  key == Key::LeftControl
            ||  key == Key::RightShift
            ||  key == Key::RightControl
            ||  key == Key::Space
            ||  key == Key::Escape )
    {
        switch (key)
        {
        case Key::Return:
        case Key::KeypadEnter:
            pressed_key_symbol = 0xf4;
            break;
        case Key::RightShift:
        case Key::LeftShift:
            pressed_key_symbol = 0xf5;
            break;
        case Key::RightControl:
        case Key::LeftControl:
            pressed_key_symbol = 0xf6;
            break;
        case Key::Escape:
            pressed_key_symbol = 0;
            break;
        case Key::Space:
            pressed_key_symbol = 0xf7;
            break;

        default:
            break;
        }
    }
    else
    {
        pressed_key_symbol = 0;
    }

    //настройки
    if (e->Key() == Key::F1)
    {
        prev_full_screen_mode = full_screen_mode;

        if (full_screen_mode)
        {
            full_screen_mode = false;
            InitVideo();
        }

#ifndef NOT_PORTED_YET
        if (m_setup_form == nullptr)
            //if (setup_form == nullptr || setup_form->getActiveControl() == nullptr)
        {
            StartKempston();

            //setup_form = std::make_shared<SetupForm>();
            m_setup_form = new SetupDialog();
            m_setup_form->open();
            //setup_form->Show();
        }
        else
        {
            m_setup_form->close();
            //setup_form->Close();
        }
#endif
    }

    if (e->Key() == Key::LeftWindows || e->Key() == Key::RightWindows)
    {
        if (full_screen_mode)
        {
            full_screen_mode = false;
            InitVideo();
        }
    }

    //пропуск локации
    if (cheats_enabled && e->Key() == Key::F2)
    {
        if (game_mode == platforming_mode)
        {
            if (!boss_mode)
            {
                std::shared_ptr<GameObject> t = std::make_shared<GameObject>();
                t->Status = 1;
                Event_door_close(t);
            }
            else if (last_boss_fase == 0)
            {
                in_boss_room = true;
                boss_mode = false;
                hero_path = 0;
                hero_path_current = 0;
                location_status = 1;
            }
            else
            {
                for (const auto &obj : actual_objects)
                {
                    if (obj->Name != idNova)
                    {
                        obj->isDamageable = false;
                        obj->Status = 3;
                        obj->Life = 0;
                        if (obj->Name == idMegabrain && !secret_boss_enabled)
                        {
                            std::shared_ptr<GameObject> o = CreateChild(obj, idMultiExplosions, 0, 0);
                            o->Counter = 127;
                            o->NoVisible = true;
                        }
                    }
                }
            }
        }
        if (game_mode == stealth_mode)
        {
            j_win = true;
            game_cicle_counter = 64;
        }

        if (game_mode == race_mode)
        {
            MuteAllMusic();
            race_win = true;
            race_exit_timer = 1;
        }

        if (game_mode == select_level_mode && current_level < 4)
        {
            uint8_t a = static_cast<uint8_t>(1 << (current_level - 1));
            levels_complete |= a;
            if (levels_complete == 7)
            {
                levels_complete = 15;
            }
            InitSelectLevel();
        }
    }

    if (cheats_enabled && e->Key() == Key::F3)
    {
        if (game_mode == platforming_mode || game_mode == stealth_mode)
        {
            InitSFX(sfx_powerup);
            hero_life_current = hero_life;
            hero_life = 77;
            hero_energy = 77;
        }
        else if (game_mode == race_mode)
        {
            hero_life_current = hero_object->Life;
            hero_object->Life = 77;
        }
    }

    if (( (e->Mod() & ModifierKeys::LeftAlt) | (e->Mod() & ModifierKeys::RightAlt) ) != 0 && e->Key() == Key::Return)
    {
        full_screen_mode = !full_screen_mode;
        InitVideo();
    }

    if (( (e->Mod() & ModifierKeys::LeftAlt) | (e->Mod() & ModifierKeys::RightAlt) ) != 0 && e->Key() == Key::F4)
    {
        Quit(this, new QuitEventArgs());
    }
}

void Program::KeyboardUp(void *, KeyboardEventArgs *e)
{
    if (e->Key() == KeysMap[0])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus & (~Key_Up));
    }
    if (e->Key() == KeysMap[1])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus & (~Key_Down));
    }
    if (e->Key() == KeysMap[2])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus & (~Key_Left));
    }
    if (e->Key() == KeysMap[3])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus & (~Key_Right));
    }
    if (e->Key() == KeysMap[4])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus & (~Key_Select));
    }
    if (e->Key() == KeysMap[5])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus & (~Key_Fire));
    }
    if (e->Key() == KeysMap[6])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus & (~Key_Jump));
    }
    if (e->Key() == KeysMap[7])
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus & (~Key_Pause));
    }
    if (e->Key() == Key::UpArrow)
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus & (~Key_Up));
    }
    if (e->Key() == Key::DownArrow)
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus & (~Key_Down));
    }
    if (e->Key() == Key::LeftArrow)
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus & (~Key_Left));
    }
    if (e->Key() == Key::RightArrow)
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus & (~Key_Right));
    }
    if (e->Key() == Key::Escape)
    {
        PressedKeysStatus = static_cast<uint8_t>(PressedKeysStatus & (~Key_Pause));
    }
}

void Program::InitVideo()
{
    double s = screen_scale;
    if (full_screen_mode)
    {
        Size win;
        Environment::PrimaryScreen::Size(win.Width, win.Height);

        int32_t sx = win.Width / 256;
        int32_t sy = win.Height / 192;
        s = static_cast<double>(std::min(sx, sy));
        screen_width = win.Width;
        screen_height = win.Height;
        x_screen_home = static_cast<int32_t>((screen_width - 256 * s) / 2 / s);
        y_screen_home = static_cast<int32_t>((screen_height - 192 * s) / 2 / s);
    }
    else
    {
        screen_width = static_cast<int32_t>(288 * s);
        screen_height = static_cast<int32_t>(224 * s);
        x_screen_home = 16;
        y_screen_home = 16;
    }
    Video::Initialize();
    int32_t bpp = Video::BestBitsPerPixel(screen_width, screen_height, full_screen_mode);
    Video::SetVideoMode(screen_width, screen_height, bpp, true, false, full_screen_mode, true);
}

void Program::VideoResize(void *, VideoResizeEventArgs *e)
{
    Size win;
    Environment::PrimaryScreen::Size(win.Width, win.Height);
    if (e->Width() >= win.Width || e->Height() >= win.Height)
    {
        full_screen_mode = true;
    }
    else
    {
        double x = e->Width();
        double y = e->Height();
        x = std::max(x, 288.0);
        y = std::max(y, 224.0);

        int32_t dx = std::abs(screen_width  - e->Width());
        int32_t dy = std::abs(screen_height - e->Height());

        if (dx > dy)
        {
            screen_scale = x / 288;
        }
        else
        {
            screen_scale = y / 224;
        }
    }
    InitVideo();
}

void Program::SaveSettings()
{
    try
    {
        const std::string settingsPath = Environment::SpecialFolder::ApplicationData() + "/blade_project.settings";

        BinaryStreamWriter f(settingsPath.c_str());

        f.Write(current_save_version);

        for (int32_t i = 0; i < 8; i++)
        {
            std::shared_ptr<joy_button> k = kempston_buttons[i];
            f.Write(k->isAxis);
            f.Write(k->isButton);
            f.Write(k->AxisNum);
            f.Write(k->AxisDirection);
            f.Write(k->ButtonNum);
        }
        f.Write(full_screen_mode);
        f.Write(language);
    }
    catch (...)
    {
    }
}

void Program::LoadSettings()
{
    for (int32_t i = 0; i < 8; i++)
    {
        kempston_buttons[i] = std::make_shared<joy_button>();
    }
    try
    {
        const std::string settingsPath = Environment::SpecialFolder::ApplicationData() + "/blade_project.settings";

        BinaryStreamReader f(settingsPath.c_str());

        std::string ver = f.ReadString();
        if (ver != current_save_version)
        {        
            return;
        }

        for (int32_t i = 0; i < 8; i++)
        {
            std::shared_ptr<joy_button> k = std::make_shared<joy_button>();
            k->isAxis        = f.ReadBoolean();
            k->isButton      = f.ReadBoolean();
            k->AxisNum       = f.ReadInt32();
            k->AxisDirection = f.ReadSingle();
            k->ButtonNum     = f.ReadInt32();
            kempston_buttons[i] = k;
        }
        full_screen_mode = f.ReadBoolean();
        language = f.ReadString();
    }
    catch (...)
    {
    }
}

void Program::StartKempston()
{
#ifndef NOT_PORTED_YET
    Joysticks::Close();
    if (kempston != nullptr)
    {
        kempston->Close();
        kempston = nullptr;
    }

    Joysticks::Initialize();
    if (Joysticks::NumberOfJoysticks != 0)
    {
        Joysticks::OpenJoystick(0);
        kempston = std::make_shared<Joystick>(0);
        kempston_btns = std::vector<ButtonKeyState>(kempston->NumberOfButtons());
    }
    else
    {
        kempston = nullptr;
    }
#endif
}
