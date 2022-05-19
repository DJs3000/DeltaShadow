#include "SEngine.h"

void Program::InitSFXBank()
{
    SFX_Bank.resize(32);

    LoadSFX("./res/SFX/sfx_beetle.wav"   , sfx_beetle, high_priority);
    LoadSFX("./res/SFX/sfx_bumerang.wav" , sfx_bumerang, high_priority);
    LoadSFX("./res/SFX/sfx_damage.wav"   , sfx_damage, normal_priority);
    LoadSFX("./res/SFX/sfx_dogscream.wav", sfx_dogscream, high_priority);
    LoadSFX("./res/SFX/sfx_dooropen.wav" , sfx_dooropen, high_priority);
    LoadSFX("./res/SFX/sfx_doors.wav"    , sfx_doors, normal_priority);
    LoadSFX("./res/SFX/sfx_droid.wav"    , sfx_droid, normal_priority);
    LoadSFX("./res/SFX/sfx_elevator.wav" , sfx_elevator, high_priority);
    LoadSFX("./res/SFX/sfx_explosion.wav", sfx_explosion, high_priority);
    LoadSFX("./res/SFX/sfx_gotonthewall.wav", sfx_gotonthewall, high_priority);
    LoadSFX("./res/SFX/sfx_lowpower.wav"    , sfx_lowpower, high_priority);
    LoadSFX("./res/SFX/sfx_missshoot.wav"   , sfx_missshoot, high_priority);
    LoadSFX("./res/SFX/sfx_powerup.wav", sfx_powerup, high_priority);
    LoadSFX("./res/SFX/sfx_race_block_hit.wav", sfx_race_block_hit, high_priority);
    LoadSFX("./res/SFX/sfx_race_down.wav", sfx_race_down, high_priority);
    LoadSFX("./res/SFX/sfx_race_jump.wav", sfx_race_jump, high_priority);
    LoadSFX("./res/SFX/sfx_race_wall_hit.wav", sfx_race_wall_hit, high_priority);
    LoadSFX("./res/SFX/sfx_rocket.wav", sfx_rocket, high_priority);
    LoadSFX("./res/SFX/sfx_shocker.wav", sfx_shocker, high_priority);
    LoadSFX("./res/SFX/sfx_slide.wav", sfx_slide, high_priority);
    LoadSFX("./res/SFX/sfx_slime.wav", sfx_slime, high_priority);
    LoadSFX("./res/SFX/sfx_start.wav", sfx_start, high_priority);
    LoadSFX("./res/SFX/sfx_stealth.wav", sfx_stealth, normal_priority);
    LoadSFX("./res/SFX/sfx_steam.wav", sfx_steam, normal_priority);
    LoadSFX("./res/SFX/sfx_stungun.wav", sfx_stungun, high_priority);
    LoadSFX("./res/SFX/sfx_switch.wav", sfx_switch, high_priority);
    LoadSFX("./res/SFX/sfx_tanketteborn.wav", sfx_tanketteborn, normal_priority);
    LoadSFX("./res/SFX/sfx_tanketteshoot.wav", sfx_tanketteshoot, normal_priority);
    LoadSFX("./res/SFX/sfx_terminal.wav", sfx_terminal, normal_priority);
    LoadSFX("./res/SFX/sfx_type.wav", sfx_type, low_priority);
    LoadSFX("./res/SFX/sfx_wave.wav", sfx_wave, high_priority);
    LoadSFX("./res/SFX/sfx_star.wav", sfx_star, high_priority);
}

void Program::LoadSFX(const std::string &filePath, int32_t num, int32_t priority)
{
    SFX_Priority[num] = priority;
    SFX_Bank[num] = std::make_shared<SdlDotNetCompat::Audio::Sound>(filePath);
}

void Program::InitSFX(int32_t num)
{
    if (!sound_on)
    {
        return;
    }

    const int32_t requestedSfxPriority = SFX_Priority[num];
    if (sfx_busy == 0 || requestedSfxPriority >= current_sfx_priority)
    {
        current_sfx_priority = requestedSfxPriority;
        sfx_busy = 20;

        SFX_Bank[num]->Play();
    }
}

void Program::InitGameMusic(int32_t num, bool looped)
{
    if (num == 255 || !music_on)
    {
        MuteGameMusic();
        return;
    }

    std::string name = music_names[num];
    if (sound_mode == ts_mode)
    {
        name += "_ts";
    }

    std::string path = "./res/music/" + name + ".ogg";

    GameSoundTheme = std::make_shared<SdlDotNetCompat::Audio::Music>(path);

    MusicPlayer::SetCurrentMusic(*GameSoundTheme);

    MusicPlayer::Play(looped);
}

void Program::MuteGameMusic()
{
    if (MusicPlayer::CurrentMusic())
    {
        MusicPlayer::Stop();
    }
}

void Program::PauseGameMusic()
{
    if (MusicPlayer::CurrentMusic())
    {
        MusicPlayer::Pause();
    }
}

void Program::ResumeGameMusic()
{
    if (MusicPlayer::CurrentMusic())
    {
        MusicPlayer::Resume();
    }
}

void Program::InitMenuMusic(int32_t num, bool looped)
{
    if (num == 255 || !music_on)
    {
        MuteMenuMusic();
        return;
    }

    std::string name = music_names[num];
    if (sound_mode == ts_mode)
    {
        name += "_ts";
    }
    std::string path = "./res/music/" + name + ".ogg";

    MenuSoundTheme = std::make_shared<Sound>(path);
    MenuSoundTheme->Play(looped);
}

void Program::MuteMenuMusic()
{
    if (MenuSoundTheme != nullptr)
    {
        MenuSoundTheme->Dispose();
    }
    MenuSoundTheme = nullptr;
}

void Program::MuteAllMusic()
{
    MuteGameMusic();
    MuteMenuMusic();
}