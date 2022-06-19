public:
    static std::int32_t screen_width;
    static std::int32_t screen_height;
    static double screen_scale;
    static bool full_screen_mode;
    static bool prev_full_screen_mode;

    static std::shared_ptr<SdlDotNetCompat::Input::Joystick> kempston;
    static std::array<std::shared_ptr<DeltaShadow::joy_button>, 8> kempston_buttons;
    static float kempston_ax_v;
    static float kempston_ax_h;
    static std::vector<SdlDotNetCompat::Input::ButtonKeyState> kempston_btns;

private:

#ifndef NOT_PORTED_YET
    class SetupDialog *m_setup_form = nullptr;

    // https://ourmachinery.com/post/gamepad-implementation-on-linux/
    static std::shared_ptr<Controller> x_input_controller;
    static Gamepad x_input_gamepad;
#endif

    //[STAThread]
public:
    static void Main();

    Program();

    void Run();

    void Quit(void *sender, QuitEventArgs *e);

    static std::int32_t x_screen_home;
    static std::int32_t y_screen_home;
    void Update(void *sender, TickEventArgs *e);

private:
    std::int32_t hide_cursor_timer = 0;
    std::int32_t show_cursor_timer = 0;
public:
    void MouseMotion(void *sender, MouseMotionEventArgs *e);

private:
    std::uint8_t PressedKeysStatus = 0;
public:
    void KeyboardDown(void *sender, KeyboardEventArgs *e);

    void KeyboardUp(void *sender, KeyboardEventArgs *e);

    static void InitVideo();

    void VideoResize(void *sender, VideoResizeEventArgs *e);

    static void SaveSettings();

    static void LoadSettings();

    static void StartKempston();

    //[System.Runtime.InteropServices.DllImport("user32.dl", CharSet = System.Runtime.InteropServices.CharSet.Auto, ExactSpelling = true)]
    //public static extern short GetAsyncKeyState(int vkey);