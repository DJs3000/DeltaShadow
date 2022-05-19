    std::shared_ptr<Music> GameSoundTheme;
    std::shared_ptr<Sound> MenuSoundTheme;

    std::vector<std::shared_ptr<Sound>> SFX_Bank; //банк звуковых эффектов

    std::array<std::int32_t, 32> SFX_Priority; //приоритет звука

    enum SFX_Codes
    {
        sfx_beetle = 0
      , sfx_bumerang = 1
      , sfx_damage = 2
      , sfx_dogscream = 3
      , sfx_dooropen = 4
      , sfx_doors = 5
      , sfx_droid = 6
      , sfx_elevator = 7
      , sfx_explosion = 8
      , sfx_gotonthewall = 9
      , sfx_lowpower = 10
      , sfx_missshoot = 11
      , sfx_powerup = 12
      , sfx_race_block_hit = 13
      , sfx_race_down = 14
      , sfx_race_jump = 15
      , sfx_race_wall_hit = 16
      , sfx_rocket = 17
      , sfx_shocker = 18
      , sfx_slide = 19
      , sfx_slime = 20
      , sfx_start = 21
      , sfx_stealth = 22
      , sfx_steam = 23
      , sfx_stungun = 24
      , sfx_switch = 25
      , sfx_tanketteborn = 26
      , sfx_tanketteshoot = 27
      , sfx_terminal = 28
      , sfx_type = 29
      , sfx_wave = 30
      , sfx_star = 31
    };

    //загрузка банка звуковых эффектов
    void InitSFXBank();

    void LoadSFX(const std::string &filePath, std::int32_t num, std::int32_t priority);

    //воспроизведение звукового эффекта

    std::int32_t sfx_busy = 0;
    std::int32_t current_sfx_priority = 0;
    void InitSFX(std::int32_t num);

    void InitGameMusic(std::int32_t num, bool looped);

    void MuteGameMusic();

    void PauseGameMusic();

    void ResumeGameMusic();

    void InitMenuMusic(std::int32_t num, bool looped);

    void MuteMenuMusic();

    void MuteAllMusic();