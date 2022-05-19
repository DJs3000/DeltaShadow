    std::int32_t scene_num = 0;
    std::shared_ptr<Program::ScreensProject> scene_scr;
    std::int32_t scene_cntr = 0;
    std::int32_t scene_status = 0;
    std::int32_t scene_music_timer = 0;

    void InitScene(std::int32_t num);

    void UpdateScene();

    std::vector<std::int32_t> final_explode = {1, 0, 1, 0, 1, 2, 3, 4, 2, 3, 4, 1, 0, 1, 0}; //15 элементов