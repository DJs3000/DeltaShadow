    //длинна шкалы 77 пикселей
    std::int32_t hero_life = 0, hero_life_current = 0;
    std::int32_t hero_energy = 0, hero_energy_current = 0;
    std::int32_t hero_weapon = 0, hero_weapon_current = 0;
    std::int32_t hero_path = 0, hero_path_current = 0;

    enum
    {
        im_none = 0
      , im_damage = 1
      , im_noise = 2
    };

    std::int32_t icon_mode = 0;
    std::int32_t icon_cntr = 0;
    std::int32_t icon_timer = 0;

    //изменение шкалы
    std::int32_t UpdateBar(std::int32_t current, std::int32_t value, std::int32_t x, std::int32_t y);