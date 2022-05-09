#pragma once

#include "Program.h"

#include "AnimTile.h"
#include "RoomLayers.h"

#include "SdlDotNetCompat/Audio/Sound.h"
#include "SdlDotNetCompat/Audio/Music.h"
#include "SdlDotNetCompat/Audio/MusicPlayer.h"

#include "SdlDotNetCompat/Core/Events.h"

#include "SdlDotNetCompat/Graphics/Video.h"

#include "SdlDotNetCompat/Input/Joystick.h"
#include "SdlDotNetCompat/Input/Joysticks.h"
#include "SdlDotNetCompat/Input/Keyboard.h"
#include "SdlDotNetCompat/Input/KeyboardEventArgs.h"
#include "SdlDotNetCompat/Input/Mouse.h"

#include "SdlDotNetCompat/Drawing/Point.h"
#include "SdlDotNetCompat/Drawing/Size.h"
#include "SdlDotNetCompat/Drawing/Rectangle.h"
#include "SdlDotNetCompat/Drawing/Color.h"

#include "Util/Random.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#define NOT_PORTED_YET

using namespace SdlDotNetCompat::Core;
using namespace SdlDotNetCompat::Graphics;
using namespace SdlDotNetCompat::Audio;
using namespace SdlDotNetCompat::Input;

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace DeltaShadow { class GameObject; }
namespace DeltaShadow { class ObjectAnimation; }
namespace SdlDotNetCompat { namespace Graphics { class Surface; } }
namespace SdlDotNetCompat { namespace Input { class Joystick; } }
namespace SdlDotNetCompat { namespace Core { class QuitEventArgs; } }
namespace SdlDotNetCompat { namespace Core { class TickEventArgs; } }
namespace SdlDotNetCompat { namespace Input { class MouseMotionEventArgs; } }
namespace SdlDotNetCompat { namespace Input { class KeyboardEventArgs; } }
namespace SdlDotNetCompat { namespace Graphics { class VideoResizeEventArgs; } }
namespace SdlDotNetCompat { namespace Audio { class Music; } }
namespace SdlDotNetCompat { namespace Audio { class Sound; } }

namespace DeltaShadow
{
class Program : public std::enable_shared_from_this<Program>
{
    //обработчик событий объекта
private:
    class GameObject; // NOTE: forward declaration

    void DoEvent(const std::shared_ptr<GameObject> &obj, const std::string &e);

    //возвращение героя в safe point
    void Event_safepoint(const std::shared_ptr<GameObject> &obj);

    //создание осколков взрыва
    void Event_fraction(const std::shared_ptr<GameObject> &obj);

    //двери открылись
    void Event_door_open(const std::shared_ptr<GameObject> &obj);

    //двери закрылись
    void Event_door_close(const std::shared_ptr<GameObject> &obj);

    //создание пули танкетки
    void Event_tankshoot(const std::shared_ptr<GameObject> &obj);

    //создание снаряда пушки
    void Event_gunshoot(const std::shared_ptr<GameObject> &obj);

    //создание горизонтальной пули дрона
    void Event_dronshoot0(const std::shared_ptr<GameObject> &obj);

    //создание диагональной пули дрона
    void Event_dronshoot1(const std::shared_ptr<GameObject> &obj);

    void Event_show_hero(const std::shared_ptr<GameObject> &obj);

    //Жаклин входит в дверь
    void Event_jdoor(const std::shared_ptr<GameObject> &obj);

    //вход Жаклин в дверь после хака
    void Event_in_door(const std::shared_ptr<GameObject> &obj);

    //выстрел Жаклин
    void Event_jshoot(const std::shared_ptr<GameObject> &obj);

    //атака полицейского
    void Event_police_attack(const std::shared_ptr<GameObject> &obj);

    //выстрел полицейского
    void Event_police_shoot(const std::shared_ptr<GameObject> &obj);

    //полицейский оглядывается назад
    void Event_police_seeback(const std::shared_ptr<GameObject> &obj);

    //звук прибывшего лифта
    void Event_sfx_elevator();

    //звук взлома двери
    void Event_sfx_doors();

    //звук работы с терминалом
    void Event_sfx_terminal();

    //запуск ракеты
    void Event_lounchrocket(const std::shared_ptr<GameObject> &obj);

    //прыжок
    void Event_jump(const std::shared_ptr<GameObject> &obj, std::int32_t accel);

    //выстрел медузы
    void Event_jelly_shoot(const std::shared_ptr<GameObject> &obj);

    //выстрел краба клешнёй
    void Event_crab_shoot(const std::shared_ptr<GameObject> &obj);
    void Event_crab_upshoot(const std::shared_ptr<GameObject> &obj);

    //атака лучём
    void Event_ray_shot(const std::shared_ptr<GameObject> &obj, std::int32_t x_distance, std::int32_t y_distance);

    //атака финального босса второй фазы
    void Event_slider_attack(const std::shared_ptr<GameObject> &obj);

    //вкл/выкл магнита финального босса второй фазы
    void Event_slider_magnit_on();
    void Event_slider_magnit_off();

    void Event_dragonfire(const std::shared_ptr<GameObject> &obj);

    //id объектов
    enum
    {
          idNova = 1
        , idDust = 2
        , idExplosion = 3
        , idRocketSmoke = 4
        , idMultiExplosions = 5
        , idBlower = 6
        , idBubble = 7
        , idBumerang = 8
        , idWave = 9
        , idBattery = 10
        , idHeart = 11
        , idPowerup = 12
        , idMiniBattery = 13
        , idMiniHeart = 14
        , idMiniPowerup = 15
        , idSuit = 16
        , idStar = 17
        , idPlatform = 18
        , idSteam = 19
        , idFraction = 20
        , idDoor = 21
        , idTankette = 22
        , idDron = 23
        , idBullet = 24
        , idSpider = 25
        , idPiranha = 26
        , idBigPiranha = 27
        , idJelly = 28
        , idSpiderNest = 29
        , idBug = 30
        , idGun = 31
        , idDragonfly = 32
        , idFighterBomber = 33
        , idDronBomber = 34
        , idAlienClawBottom = 35
        , idAlienClawTop = 36
        , idAlienWorm = 37
        , idSlime = 38
        , idSonusVenator = 39
        , idBigSpider = 40
        , idCraken = 41
        , idMoth = 42
        , idRocketman = 43
        , idCrabBoss = 44
        , idFlyBoss = 45
        , idAlienPet = 46
        , idAlienSliderman = 47
        , idMegabrain = 48
        , idRocket = 49
        , idMiniBrain = 50
        , idBomb = 51
        , idFlyBomb = 52
        , idWaterFun = 53
        , idBubbleGenerator = 54
        , idJacqueline = 55
        , idJLift = 56
        , idJDoor = 57
        , idJTerminal = 58
        , idJPolice1 = 59
        , idJPolice2 = 60
        , idJPolice3 = 61
        , idJOffice1 = 62
        , idJOffice2 = 63
        , idJOffice3 = 64
        , idNovaBike = 65
        , idDLCBullet = 66
        , idJDJump = 67
        , idJGun = 68
        , idJShield = 69
        , idJBubble = 70
        , idDragon = 71
    };

    //описатель игрового объекта
private:
    class ObjectAnimation;
    class GameObject : public std::enable_shared_from_this<GameObject>
    {
    public:
        bool NoActivated = false; //объект не активирован
        std::int32_t X1Trigger = 0, X2Trigger = 0, Y1Trigger = 0, Y2Trigger = 0; //координаты триггера спавна
        std::uint8_t XYRoom = 0; //координаты комнаты с точкой спавна
        std::uint8_t Name = 0; //имя игрового объекта
        std::int32_t Life = 0; //жизненная энергия объекта
        std::uint8_t Status = 0; //статус объекта
        std::uint8_t Priority = 0; //приоритет прорисовки, 0 - самый дальний план, 2 - самый ближний
        std::int32_t X = 0, Y = 0; //координаты на экране
        std::int32_t Width = 0, Height = 0; //текущая ширина и высота объекта (из данных коллайдера)
        std::int32_t XTarget = 0, YTarget = 0; //координаты цели
        std::int32_t XTile = 0, YTile = 0; //координаты объекта в тайлах
        std::int32_t XAccel = 0; //ускорение по X
        std::int32_t YAccel = 0; //ускорение по Y
        bool Direction = false; //направление спрайта, false - вправо, true - влево
        bool Left = false, Down = false, Up = false, Right = false; //направление входа в комнату для активации объекта
        bool Fixed = false; //объект имеет фиксированные координаты
        std::uint8_t Type = 0; //тип объекта, 0 - спрайт, 1-127 - тайл, 128-255 - [символ - 128]
        bool haveGravity = false; //у объекта есть гравитация
        bool isDamageable = false; //объект можно уничтожить
        bool NoInterruptAnim = false; //непрерываемая анимация, автоматически сбрасывается по окончании анимации
        bool NoVisible = false; //объект невидимый
        std::int32_t Counter = 0; //счётчик общего назначения
        std::uint8_t UndeadCounter = 0; //счётчик бессмертия
        std::shared_ptr<GameObject> PlatformObject; //объект платформы, на которой находится объект

        std::vector<std::shared_ptr<ObjectAnimation>> Animations; //анимации игрового объекта
        bool AnimationPlayed = false; //проигрывается анимация
        std::int32_t Frame = 0; //номер кадра текущей анимации
        std::int32_t CurrentAnimation = 0; //номер текущей анимации
        std::int32_t AnimCounter = 0; //счётчик для проигрываемого кадра
    };

    //создать игровой объект
private:
    std::shared_ptr<Program::GameObject> CreateObject(std::uint8_t name, std::int32_t x, std::int32_t y, bool direction, bool actual_object);

    //удалить объект
    void RemoveObject(const std::shared_ptr<GameObject> &obj);

    //удалить все объекты
    void ClearAllObjects();

    //очистить список актуальных объектов
    void ClearActualObjectsList();

    //добавить игровой объект в список актуальных
    void AddActualObject(const std::shared_ptr<GameObject> &obj);

    //удалить игровой объект из списка актуальных
    void RemoveActualObject(const std::shared_ptr<GameObject> &obj);

    //создать дочерний игровой объект со смещениями, с учётом direction
    std::shared_ptr<Program::GameObject> CreateChild(const std::shared_ptr<Program::GameObject> &obj, std::uint8_t name, std::int32_t xoffset, std::int32_t yoffset);




    //гравитация объекта,возвращает true если объект в воздухе

    std::int32_t ga = 0, gb = 0;
    bool Gravity(const std::shared_ptr<Program::GameObject> &obj);

    void ChangeDirection(const std::shared_ptr<Program::GameObject> &obj);

    //движение объекта вперёд
    bool MoveObjectForward(const std::shared_ptr<Program::GameObject> &obj, std::int32_t speed);

    bool SimpleMoveObjectForward(const std::shared_ptr<GameObject> &obj, std::int32_t speed);

    //создать пулю
    void CreateBullet(const std::shared_ptr<GameObject> &obj, const std::string &animations, const std::string &anim_name, std::int32_t xoffset, std::int32_t yoffset, std::int32_t xdelta, std::int32_t ydelta, bool damageble);

    //проверка, попадёт-ли объект в героя в заданном направлении, 0 - прямо, 1 - вниз, 2 - диагональ вверх, 3 - диагональ вниз
    bool TestShoot(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset, std::int32_t yoffset, std::int32_t direct);

    //подсчёт кол-ва активных объектов определенного вида
    std::int32_t ObjectsCount(std::int32_t name);

    //создать взрыв на основе родительского объекта
    void CreateExplosion(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset, std::int32_t yoffset);

    //развернуть объект по направлению к герою
    void TurnObject(const std::shared_ptr<GameObject> &obj);

    //расчёт дистанции до героя
    std::uint8_t GetXDistance(const std::shared_ptr<GameObject> &obj);
    std::uint8_t GetYDistance(const std::shared_ptr<GameObject> &obj);

    //повёрнут-ли объект к другом объекту лицом
    bool SeeOnObject(const std::shared_ptr<GameObject> &obj1, const std::shared_ptr<GameObject> &obj2);

    //повёрнут-ли объект к герою
    bool SeeOnHero(const std::shared_ptr<GameObject> &obj);

    //объект находится в текущей комнате
    bool InCurrentRoom(const std::shared_ptr<GameObject> &obj);

    //взять свойство тайла относительно игрового объекта с учётом Direction
    std::int32_t GetProperty(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset, std::int32_t yoffset);

    //взять целое свойство тайла относительно игрового объекта
    std::int32_t GetFullProperty(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset, std::int32_t yoffset);

    //взять свойство тайла по координатам
    std::int32_t GetXYProperty(std::int32_t x, std::int32_t y);

    //поиск рельсы для подвижной платформы по направлению, 0 - вверх, 1 - вправо, 2 - вниз, 3 - влево
    bool GetRailsTile(const std::shared_ptr<GameObject> &obj);

    //создать осколки
    void CreateFractions(const std::shared_ptr<GameObject> &obj, std::int32_t num);

    //создать мини-бонус
    bool mini_bonus_ready = false;
    void CreateMiniBonus(const std::shared_ptr<GameObject> &obj);

    //тест на шипы и воду для врагов
    bool EnemyWaterSpikeTest(const std::shared_ptr<GameObject> &obj);

    //инициализация попадения героя на шипы
    void InitHeroSpike();

    //получение урона
    bool HeroDamage(const std::shared_ptr<GameObject> &obj, std::int32_t yoffset);

    //уменьшение жизни героя
    void DecreaseHeroLife();

    std::shared_ptr<Program::GameObject> EnemyDamage(const std::shared_ptr<Program::GameObject> &obj, std::int32_t xdist);

    //покачивание летающего объекта в воздухе
    void ObjWiggle(const std::shared_ptr<GameObject> &obj);

    bool FlyUp(const std::shared_ptr<GameObject> &obj);

    bool FlyDown(const std::shared_ptr<GameObject> &obj);

    void HeroOnRoof();

    bool InRange(std::int32_t a, std::int32_t b, std::int32_t value);

    //центровка по объекту
    bool ObjCentrum(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset);

    //обработчик смерти драконов и боссов
    bool BossDie(const std::shared_ptr<GameObject> &obj);

    SdlDotNetCompat::Drawing::Color next_palette[256];

    SdlDotNetCompat::Drawing::Color attr_palette[2][16]; //классическая палитра

    std::shared_ptr<Util::Random> rnd = std::make_shared<Util::Random>(); //генератор случайных чисел

public:
    std::shared_ptr<SdlDotNetCompat::Graphics::Surface> screen;
private:
    std::shared_ptr<SdlDotNetCompat::Graphics::Surface> screen_copy; //копия экрана
    std::shared_ptr<SdlDotNetCompat::Graphics::Surface> scroll_screen; //экран для скроллинга комнаты
public:

    SdlDotNetCompat::Drawing::Color attr_layer[2][256][192]; //атрибутный слой экрана для вывода монохромных спрайтов

private:
    std::int32_t scroll_direction = 0; //направление скроллинга, 1 - вверх, 2 - вправо, 3 - вниз, 4 - влево
    std::int32_t scroll_cntr = 0; //счётчик скроллинга

    //инициализация графического движка
    void InitGEngine();

    //функция возвращает цвет, соответствующий цвету ZX Spectrum [0..15]
public:
    SdlDotNetCompat::Drawing::Color GetColor(std::int32_t zxcolor);

    //очистка экрана
private:
    void ClearScreen();

    //заливка атрибутного прямоугольника и очистка пискелей
    void FillAttrRect(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height, std::uint8_t attr);

    void InitRoomTiles();

    //инициализация комнаты локации
    void InitRoom(bool new_hero_cord);

    //добавить тайл в локацию (кроме анимированных тайлов) координаты в тайлах
    void NewTile(std::int32_t x, std::int32_t y, std::int32_t num);

    //задание полной перерисовки комнаты
    void FullRoomRedraw();

    //прорисовка тайлов комнаты
    void DrawRoom();

    //прорисовка тайлового объекта
    void DrawTileObject(const std::shared_ptr<GameObject> &obj);

    //прорисовка объекта символа
    void DrawSymbolObject(const std::shared_ptr<GameObject> &obj);

    //прорисовка игровых объектов
    std::int32_t sprite_bottom = 160;
    void DrawGameObject(const std::shared_ptr<GameObject> &obj);
    void DrawGameObjects();

    //скролл комнаты
    void ScrollRoom();

    //установить значение шкалы
    void SetScale(std::int32_t x, std::int32_t y, std::int32_t value);

    //нарисовать столбик для шкалы
    void SetScaleCol(std::int32_t x, std::int32_t y);

    //стреть столбик для шкалы
    void ResScaleCol(std::int32_t x, std::int32_t y);

    //загрузка проекта локации и тайлсетов
    std::uint8_t current_tilesets[2][256][37];

    void LoadLocationProject(std::int32_t num);

    //прорисовка классического тайлсета
    void DrawClassicTileset();

    //проверка на необходимость скроллинга комнаты
    void NeedScrollRoom();

    //увеличить game_cicle_counter
    void IncGameCicleCounter();

    void SetBorder(const SdlDotNetCompat::Drawing::Color &c);


    bool external_resource = false; //разрешение использования внешних ресурсов
    bool demo_version = false;

    bool cheats_enabled = false;

    bool debug_mode = true;
public:
    static std::string language;
private:
    enum ReleaseType
    {
        classic_version = 0
      , next_version = 1
    };
    std::int32_t release_type = next_version;

    enum GameMode
    {
        debug_menu_mode = 0
      , platforming_mode = 1
      , race_mode = 2
      , game_over_mode = 3
      , stealth_mode = 4
      , clip_mode = 5
      , suit_mode = 6
      , select_level_mode = 7
      , main_menu_mode = 8
      , new_game_mode = 9
      , select_diff_mode = 10
      , cancel_mission_mode = 11
      , select_message_mode = 12
      , read_message_mode = 13
      , load_screen_mode = 14
      , settings_mode = 15
      , control_settings_mode = 16
      , redefine_mode = 17
      , graphic_settings_mode = 18
      , sound_settings_mode = 19
      , system_settings_mode = 20
      , areyousure_mode = 21
      , reset_mode = 22
      , player_mode = 23
    }
    game_mode = debug_menu_mode; //режим игры;

public:
    static std::int32_t sprite_mode; //режим спрайтов
    static std::int32_t tiles_mode; //режим тайлов
private:
    enum ZXMode
    {
        zx_classic_mode = 0
      , zx_next_mode = 1
    };

    enum SoundMode
    {
        one_ay_mode = 0
      , ts_mode = 1
    };

    std::int32_t sound_mode = one_ay_mode; //режим музыки

    std::array<std::shared_ptr<GameObject>, 128> game_objects;   //список всех объектов локации
    std::array<std::shared_ptr<GameObject>, 128> actual_objects; //ссылки на актуальные объекты
    std::shared_ptr<GameObject> hero_object; //объект героя
    bool hero_start_direction = false;

    enum Priority
    {
        low_priority = 0
      , normal_priority = 1
      , high_priority = 2
    };

    std::int32_t difficulty = 0; //режим сложности игры
    std::int32_t max_difficulty = 1; //максимальный уровень сложности

    bool music_on = true;
    bool sound_on = true;

    bool scroll_on = true;

    std::uint64_t collected_stars = 0x01; // битовый массив собранных звёзд, 48 бит, 6 байт, одна звезда сразу открыта
    std::uint64_t noreaded_stars = 0x01; //битовый массив непросмотренных звёзд, 48 бит
    std::int32_t stars_num = 1; //кол-во собранных звёзд

    std::int32_t graphics_quality = 2; //настройки качества графики

    bool in_boss_room = false; //герой в комнате босса
    std::int32_t **Loc; //массив с локацией
    std::int32_t LocWidth = 0;
    std::int32_t LocHeight = 0;

    std::shared_ptr<SdlDotNetCompat::Graphics::Surface> Tileset[2][256];

    SdlDotNetCompat::Drawing::Color TilesetAttr[2][256][16][16];  //атрибуты тайлсета для атрибутного слоя

    std::int32_t TilesetProperty[256];  //свойства тайлов в тайлсете

    std::vector<std::shared_ptr<AnimTile>> RoomAnimTiles = std::vector<std::shared_ptr<AnimTile>>(); //список анимированных тайлов в комнате

    std::vector<std::vector<std::shared_ptr<RoomLayers>>> RoomsLayers; //массив слоёв в комнатах локации

    bool secret_boss_enabled = false; //включен секретный босс

    std::int32_t current_suit = 0; //режим костюма, 0 - без костюма

    bool have_suit[4];  //костюмы в наличии (0 - без костюма)

    bool no_suit_run = false;

    //свойства тайлов
    enum TileProperties
    {
        isEmpty = 0
      , isFloor = 1
      , isLadder = 2
      , isWater = 3
      , isSpike = 4
      , isPlatform = 5
      , isRails = 6
      , isShift = 7
    };

    std::int32_t particle_cntr = 0; //счётчик частиц

    std::int32_t current_level = 1; //номер текущего уровня
    std::int32_t current_location = 1; //номер текущей локации
    std::int32_t x_home = 0, y_home = 0; //координаты верхнего левого угла комнаты в пикселях
    std::int32_t x_home_tile = 0, y_home_tile = 0; //координаты верхнего левого угла комнаты в тайлах
    std::uint8_t current_xy_room = 0; //текущая координата комнаты

    std::int32_t Room[16][10];

    bool screen_refresh_tab[16][10];

    //сохранение для безопасного возвращения
    std::uint8_t last_safe_xy_room = 0; //координата безопасной комнаты
    std::int32_t last_safe_x = 0, last_safe_y = 0; //координаты героя в безопасной комнате
    bool last_safe_direction = false; //направление героя в безопасной комнате

    bool bw_color_mode = false; //черно-белый режим

    bool kempston_on = false;

    class ScreensProject; // NOTE: forward declaration

    std::shared_ptr<ScreensProject> statusbar;
    std::shared_ptr<ScreensProject> select_menu;

    std::unordered_map<std::string, std::uint8_t> objects_names = std::unordered_map<std::string, std::uint8_t>();
    std::unordered_map<std::int32_t, std::string> levels_names = std::unordered_map<std::int32_t, std::string>();
    std::unordered_map<std::int32_t, std::string> music_names = std::unordered_map<std::int32_t, std::string>();

    //------------------------------------- основной блок -------------------------------------

    //инициализация главной формы
public:
    void MainInit();

    //сохранение прогресса игры
    static std::string current_save_version;
private:
    void SaveProgress();

    //загрузка прогресса игры
    bool loaded_progress = false;
    void LoadProgress();

    /////старт игры
    ///void StartTimer_Tick(const std::shared_ptr<void> &sender, const std::shared_ptr<SdlDotNetCompat::EventArgs> &e);

    //главный цикл
    std::int32_t pause_cnt = 0; //только для прототипа
    void MainCicle();


    //инициализация отладочного меню
    void InitDebugMenu();

    std::vector<std::string> level_names = {"Race", "Jacqueline", "Level 1-1", "Level 1-2", "Level 1-3", "Dragon 1", "Boss 1", "Level 2-1", "Level 2-2", "Level 2-3", "Dragon 2", "Boss 2", "Level 3-1", "Level 3-2", "Level 3-3", "Dragon 3", "Boss 3", "Level 4-1", "Level 4-2", "Level 4-3", "Level 4-4", "Level 4-5", "Level 4-6", "Level 4-7", "FinalBoss", "Extra 1-4", "Extra 2-4", "Extra 3-4", "Extra 4-8", "Jacqueline DLC"};

    //прорисовка отладочного меню
    void DrawDebugMenu();

    //обновление отладочного меню

    std::int32_t menu_pos = 29;
    void UpdateDebugMenu();

    //инициализация game over
    void InitGameOver();

    //обновление game over
    void UpdateGameOver();

    //инициализация выбора уровня
    std::int32_t select_level_status = 0;
    std::int32_t select_level_fase = 0;
    std::uint8_t levels_complete = 0;
    bool last_tower = false;
    std::uint8_t menu_keys = 0;
    std::shared_ptr<ScreensProject> select_level_screens;
    void InitSelectLevel();

    //обновление выбора уровня
    void UpdateSelectLevel();

    std::int32_t pictogramm_y = 0;
    std::int32_t pictogramm_pos = 0;
    std::shared_ptr<ScreensProject> pictogramm_screens;

    void InitSay(std::int32_t text_num, std::int32_t pictogramm);

    bool UpdateNovaSay();

    bool UpdateJacquelineSay();

    //обновление режима загрузочного экрана

    std::int32_t lspp = 255;
    void UpdateLoadScreen();

    //инициализация главного меню
    std::shared_ptr<ScreensProject> main_menu_scr;
    std::int32_t main_menu_pos = 0;
    std::int32_t prev_game_mode = 0; //из какого режима вошли в main_menu
    std::int32_t current_music = 0; //текущий трек уроня
    void InitMainMenu(bool hard_init);

    //обновление главного меню
    void UpdateMainMenu();

    std::int32_t new_game_pos = 0;
    void UpdateNewGame();

    std::int32_t cancel_mission_pos = 0;
    void UpdateCancelMission();

    void InitSelectDiff();

    void UpdateSelectDiff();

    void InitSelectMessage();

    std::int32_t select_message_home = 0;
    std::int32_t select_message_pos = 0;
    void UpdateSelectMessage();

    std::int32_t read_message_num = 0;
    std::int32_t read_message_home = 0;
    bool read_message_scroll = false;
    bool read_message_down = false;
    void UpdateReadMessage();

    void InitSettings();

    std::int32_t settings_pos = 0;
    void UpdateSettings();

    std::int32_t control_pos = 0;
    void UpdateControlsSettings();

    std::int32_t redefine_pos = 0;
    std::int32_t redefine_pause = 0;
    SdlDotNetCompat::Input::Key KeysMapNew[8];
    std::vector<std::int32_t> redefine_tab = {2, 3, 0, 1, 5, 6, 4, 7};
    void UpdateRedefine();

    std::int32_t graphic_pos = 0;
    void UpdateGraphicSettings();

    std::int32_t sound_pos = 0;
    void UpdateSoundSettings();

    std::int32_t system_pos = 0;
    void UpdateSystemSettings();

    void UpdateAreYouSure();

    std::int32_t reset_pos = 0;
    void UpdateReset();

    std::int32_t player_home = 0;
    std::int32_t player_pos = 0;
    void UpdatePlayer();

    void InitNewGame();

    //навигатор по меню
    std::int32_t MenuNavigation(std::int32_t current_pos, std::int32_t min, std::int32_t max);

    void PrintDemoVersion();


private:
    class ObjectAnimation : public std::enable_shared_from_this<ObjectAnimation>
    {
    public:
        std::string Name; //имя анимации

        //класс спрайта
    public:
        class Sprite : public std::enable_shared_from_this<Sprite>
        {
        public:
            std::string  Name; //имя спрайта
            std::int32_t Type = 0; //тип спрайта
            std::int32_t Width = 0; //ширина спрайта
            std::int32_t Height = 0; //высота спрайта
            std::int32_t **ClassicLayer; //слой для классического режима
            SdlDotNetCompat::Drawing::Color **NextLayer; //слой для режима Next
        };
    public:
        std::vector<std::shared_ptr<Sprite>> Sprites = std::vector<std::shared_ptr<Sprite>>(); //список спрайтов

        //класс элемента композиции
    public:
        class CompositionElement : public std::enable_shared_from_this<CompositionElement>
        {
        public:
            std::shared_ptr<Sprite> ElemSprite; //спрайт элемента композиции
            std::int32_t XOffset = 0; //смещение спрайта по X
            std::int32_t YOffset = 0; //смещение спрайта по Y
        };

        //класс кадра
    public:
        class Frame : public std::enable_shared_from_this<Frame>
        {
        public:
            std::vector<std::shared_ptr<CompositionElement>> Composition; //список элементов в композиции
            std::int32_t Time = 0; //время проигрывания кадра во фреймах
            std::int32_t DX1 = 0, DY1 = 0, DX2 = 0, DY2 = 0; //коллайдер повреждения
            std::int32_t HX1 = 0, HY1 = 0, HX2 = 0, HY2 = 0; //коллайдер удара
            std::string  Event; //название события
        };

        //класс анимации
    public:
        class Animation : public std::enable_shared_from_this<Animation>
        {
        public:
            std::string Name; //имя анимации
            std::vector<std::shared_ptr<Frame>> Frames; //список кадров
            bool Loop = false; //анимация зациклена
        };

    public:
        std::vector<std::shared_ptr<Animation>> Animations = std::vector<std::shared_ptr<Animation>>(); //список анимаций
    };

private:
    std::vector<std::shared_ptr<ObjectAnimation>> ObjectAnimations = std::vector<std::shared_ptr<ObjectAnimation>>(); //наборы анимаций объектов

    //загрузка анимаций по имени
    void LoadAnimations(const std::string &name);

    //загрузка проекта анимаций
    void LoadAnimationsProject(const std::string &name);

    //поиск спрайта по имени
    std::shared_ptr<ObjectAnimation::Sprite> FindSprite(const std::string &name, const std::shared_ptr<ObjectAnimation> &anim);

    //инициализация анимации по имени
    void InitAnimation(const std::shared_ptr<GameObject> &obj, const std::string &name, bool hard_enable);

    void InitAnimation(const std::shared_ptr<GameObject> &obj, std::uint8_t id_anim, bool hard_enable);

    //проигрывание анимации (вызывается каждый игровой цикл)
    void PlayAnimation(const std::shared_ptr<GameObject> &obj);

    //высота и ширина объекта
    void GetObjSize(const std::shared_ptr<Program::GameObject> &obj);

    //поиск набора анимаций по имени
    std::vector<std::shared_ptr<Program::ObjectAnimation>> FindObjectAnimation(const std::string &name);


    std::int32_t location_status = 0; //текущий статус локации
    std::int32_t location_counter = 0; //счётчик для всяких действий в локации
    std::int32_t start_life = 0, start_energy = 0, start_weapon = 0; //значения на страте локации

    //инициализация режима платформинга
    void InitPlatforming(bool boss);

    //инициализация статусбара платформинга
    void InitPlatformingStatusbar();

    std::int32_t fall_down_effect[16][10];

    //инициализация локации
    std::int32_t start_slot = 0;
    std::int32_t room_cntr = 0; //уменьшающийся счётчик пройденных комнат, после инициализации равен 2.
    std::int32_t battery_cntr = 0; //сч-к уменьшения батарейки костюма
    std::int32_t level_music = 0; //трек уровня
    bool reverse_way = false; //прохождение уровня из конца в начало
    void InitLocation(bool boss);

    //инициализация DLC стелса
    void InitDLCStatusbar();


    //проверка конами-кода
    std::int32_t TestKonamiCode_pos = 0;
    std::int32_t TestKonamiCode_cnt = 0;
    std::vector<std::uint8_t> TestKonamiCode_txt = {Key_Up, Key_Down, Key_Up, Key_Down, Key_Left, Key_Left, Key_Right, Key_Right, Key_Fire, Key_Jump, 0xff};
    void TestKonamiCode();

    //обновление  платформенного уровня
    std::int32_t last_boss_fase = 0;
    void UpdatePlatforming();

    //уровень пройден
    void LevelComlete();

    //инициализация режима иконки статус-бара
    void InitIcon(std::int32_t command);

    //обновление иконки статус-бара
    void UpdateIcon();

    //инициализация финального босса
    std::int32_t final_scens_show = 0;
    void InitFinalBoss(std::int32_t fase);


    //обработка игровых объектов
    void ProcessingGameObject(const std::shared_ptr<GameObject> &obj);

    //Нова
    bool immortal_mode = false;
    bool on_ladder = false;
    bool on_wall = false;
    bool on_roof = false;
    bool is_jump = false;
    bool is_fly = false;
    bool hero_die = false;
    bool boss_mode = false;
    std::int32_t attack_cntr = 0;
    std::int32_t slide_cntr = 0;
    std::int32_t hero_weapon_max = 0;
    bool disable_control = false;
    bool extern_move = false;
    bool in_water = false;

    void Nova(const std::shared_ptr<GameObject> &obj);


    //для Жаклин из DLC
    bool gun_on = false;
    bool double_jump_on = false;
    bool is_double_jump = false;
    void DLCJacqueline(const std::shared_ptr<GameObject> &obj);

    //поверапы
    void PowerUp(const std::shared_ptr<GameObject> &obj);

    //убить объект, когда закончится анимация
    void KillWhileStopAnimation(const std::shared_ptr<GameObject> &obj);

    void MultiExplosions(const std::shared_ptr<GameObject> &obj);

    //вентилятор
    void Blower(const std::shared_ptr<GameObject> &obj);

    //пузыри
    void Bubble(const std::shared_ptr<GameObject> &obj);

    //бумеранг
    void Bumerang(const std::shared_ptr<GameObject> &obj);

    //энергетическая волна
    void Wave(const std::shared_ptr<GameObject> &obj);

    //платформа
    void Platform(const std::shared_ptr<GameObject> &obj);

    //пар
    void Steam(const std::shared_ptr<GameObject> &obj);

    //осколки
    void Fraction(const std::shared_ptr<GameObject> &obj);

    //дверь
    void Door(const std::shared_ptr<GameObject> &obj);

    //танкетка
    void Tankette(const std::shared_ptr<GameObject> &obj);

    //дрон
    void Dron(const std::shared_ptr<GameObject> &obj);

    //пуля
    void Bullet(const std::shared_ptr<GameObject> &obj);

    //паук
    void Spider(const std::shared_ptr<GameObject> &obj);

    //пиранья
    void Piranha(const std::shared_ptr<GameObject> &obj);

    //медуза
    void Jelly(const std::shared_ptr<GameObject> &obj);

    //паучье гнездо
    void SpiderNest(const std::shared_ptr<GameObject> &obj);

    //жук
    void Bug(const std::shared_ptr<GameObject> &obj);

    //пушка
    void Gun(const std::shared_ptr<GameObject> &obj);

    //летающие враги (ракетчик и бомбер)
    void FlyEnemy(const std::shared_ptr<GameObject> &obj);

    //подземный коготь
    void AlienClaw(const std::shared_ptr<GameObject> &obj);

    //червяк
    void AlienWorm(const std::shared_ptr<GameObject> &obj);

    //слизь
    void Slime(const std::shared_ptr<GameObject> &obj);

    //звуковой враг
    void SonusVenator(const std::shared_ptr<GameObject> &obj);


    //босс большой паук
    void BigSpider(const std::shared_ptr<GameObject> &obj);

    //кракен
    void Craken(const std::shared_ptr<GameObject> &obj);

    //мотылёк
    void Moth(const std::shared_ptr<GameObject> &obj);

    //босс Рокетмэн
    void Rocketman(const std::shared_ptr<GameObject> &obj);

    //босс краб
    void CrabBoss(const std::shared_ptr<GameObject> &obj);

    //летающий босс
    void FlyBoss(const std::shared_ptr<GameObject> &obj);

    //первая фаза финального босса
    void AlienPet(const std::shared_ptr<GameObject> &obj);

    //вторая фаза финального босса
    bool boss_magnit_on = false;
    void AlienSliderman(const std::shared_ptr<GameObject> &obj);

    //третья фаза финального босса
    void Megabrain(const std::shared_ptr<GameObject> &obj);


    //самонаводящаяся ракета
    void Rocket(const std::shared_ptr<GameObject> &obj);

    //мини-мозг
    void MiniBrain(const std::shared_ptr<GameObject> &obj);

    //бомба
    void Bomb(const std::shared_ptr<GameObject> &obj);

    //летающая бомба
    void FlyBomb(const std::shared_ptr<GameObject> &obj);

    //магнит к объекту
    void Magnit(const std::shared_ptr<GameObject> &obj, std::int32_t x_dist, std::int32_t x_area, std::int32_t x_force);

    //генератор пузырей
    void BubbleGenerator(const std::shared_ptr<GameObject> &obj, std::int32_t xoffset, std::int32_t yoffset);



    //пуля Жаклин
    void DLCBullet(const std::shared_ptr<GameObject> &obj);

    //защита Жаклин
    void DLCBubble(const std::shared_ptr<GameObject> &obj);

    //DLC поверапы
    void DLCPowerUp(const std::shared_ptr<GameObject> &obj);

    //DLC дракон
    void Dragon(const std::shared_ptr<GameObject> &obj);


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


private:
    std::shared_ptr<ScreensProject> race_imgs;

    std::array<std::int32_t, 32> race_objects;
    std::int32_t bike_y_pos = 0; //позиция по Y
    std::int32_t bike_y_accel = 0; //ускорение по Y
    std::int32_t bike_y_offset = 0; //смещение по Y
    std::int32_t bike_down_counter = 0; //счётчик отката вниз
    std::int32_t bike_undead = 0; //счётчик бессмертия

    bool race_win = false;
    bool race_lose = false;
    std::int32_t race_exit_timer = 0; //таймер выхода из гонки
    std::int32_t race_turn_counter = 0; //счётчик для поворота
    bool turn_direction = false; //направление поворота, false - влево, true - вправо
    std::int32_t top_x = 0;
    std::int32_t race_pos = 0; //максимальное значение 2500, массив препятствий 825 элементов
    std::int32_t top_fase = 0;
    std::int32_t trace_pos = 0; //индекс в trace
    std::int32_t trace_pause = 0; //пауза в чтении trace

    bool race_pause = false; //гонка на паузе

    std::string top_name;

    //инициализация гонки
    void InitRace();

    //прорисовка верха
    void DrawRaceTop();

    //обновление гонки
    void UpdateRace();

    //уменьшение энергии Новы
    void DecLife(const std::shared_ptr<GameObject> &obj, std::int32_t value);

    enum
    {
        t_pause = 0x80
      , t_right = 0x01
      , t_center = 0x02
      , t_left = 0x04
      , t_tramplin = 0x08
      , t_turn_left = 0x10
      , t_turn_right = 0x20
    };

    std::vector<std::int32_t> trace;
    std::vector<std::int32_t> trace_1 = {t_pause + 20, t_turn_right, t_turn_left, t_pause + 5, t_turn_right, t_turn_left, t_left + t_right, t_left + t_right, t_left + t_right, t_left + t_right, t_center, t_pause + 15, t_turn_right, t_tramplin + t_center, t_center, t_left + t_center, t_right, t_tramplin + t_center, t_center, t_left + t_center, t_center, t_right, t_tramplin + t_left, t_left + t_right, t_center, t_tramplin + t_right, t_left + t_right, t_left + t_center, t_pause + 5, t_tramplin + t_center, t_center, t_left, t_left, t_left + t_center, t_left + t_center, t_left + t_center, t_pause + 15, t_turn_left, t_pause + 5, t_tramplin + t_left, t_left, t_tramplin + t_center, t_center, t_left, t_tramplin + t_right, t_right, t_center, t_center, t_pause + 10, t_turn_right, t_turn_left, t_right, t_tramplin + t_center, t_center, t_right, t_tramplin + t_center, t_center, t_right, t_center, t_center + t_right, t_center + t_right, t_pause + 15, t_turn_left, t_turn_right, t_turn_left, t_pause + 5, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_tramplin + t_left, t_left + t_right, t_pause + 15, t_tramplin + t_center, t_center, t_pause + 25, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_turn_right, t_turn_left, t_turn_right, t_tramplin + t_left, t_left + t_right, t_center, t_tramplin + t_left + t_right, t_left + t_right, t_tramplin + t_center, t_center, t_pause + 5, t_tramplin + t_right, t_left + t_right, t_left + t_right, t_left + t_right, 0};

    std::vector<std::int32_t> trace_2 = {t_pause + 20, t_turn_right, t_left + t_right, t_pause + 15, t_turn_left, t_pause + 5, t_turn_right, t_turn_left, t_pause + 5, t_left + t_right, t_left + t_right, t_left + t_right, t_center, t_pause + 5, t_tramplin + t_center, t_center, t_left, t_left, t_left + t_center, t_left + t_center, t_left + t_center, t_pause + 5, t_tramplin + t_right, t_left + t_right, t_left + t_right, t_left + t_right, t_pause + 15, t_turn_left, t_turn_right, t_turn_left, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_turn_right, t_tramplin + t_left, t_left, t_tramplin + t_center, t_center, t_left, t_tramplin + t_right, t_right, t_center, t_center, t_pause + 15, t_turn_right, t_tramplin + t_center, t_center, t_left + t_center, t_right, t_tramplin + t_center, t_center, t_left + t_center, t_center, t_right, t_tramplin + t_left, t_left + t_right, t_center, t_tramplin + t_right, t_left + t_right, t_left + t_center, t_pause + 10, t_turn_left, t_turn_left, t_right, t_tramplin + t_center, t_center, t_right, t_tramplin + t_center, t_center, t_right, t_center, t_center + t_right, t_center + t_right, t_pause + 5, t_tramplin + t_left, t_left + t_right, t_pause + 15, t_tramplin + t_center, t_center, t_pause + 25, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_turn_right, t_turn_left, t_turn_right, t_tramplin + t_left, t_left + t_right, t_center, t_tramplin + t_left + t_right, t_left + t_right, t_tramplin + t_center, t_center, 0};

    std::vector<std::int32_t> trace_3 = {t_pause + 20, t_turn_left, t_left + t_right, t_pause + 15, t_turn_right, t_turn_left, t_turn_right, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_turn_left, t_tramplin + t_left, t_left, t_tramplin + t_center, t_center, t_right, t_tramplin + t_left, t_left, t_center, t_pause + 5, t_tramplin + t_center, t_center, t_left, t_left, t_left + t_center, t_left + t_center, t_left + t_center, t_pause + 10, t_turn_right, t_turn_left, t_right, t_tramplin + t_center, t_center, t_right, t_tramplin + t_center, t_center, t_right, t_center, t_center + t_right, t_center + t_right, t_pause + 5, t_tramplin + t_left, t_left + t_right, t_pause + 15, t_turn_right, t_pause + 5, t_turn_left, t_turn_right, t_pause + 5, t_left + t_right, t_left + t_right, t_left + t_right, t_center, t_center, t_pause + 15, t_tramplin + t_center, t_center, t_pause + 15, t_turn_right, t_tramplin + t_center, t_center, t_left + t_center, t_right, t_tramplin + t_center, t_center, t_left + t_center, t_center, t_right, t_tramplin + t_left, t_left, t_center, t_tramplin + t_right, t_left + t_right, t_left + t_center, t_pause + 5, t_tramplin + t_right, t_left + t_right, t_left + t_right, t_left + t_right, t_pause + 25, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_turn_left, t_turn_left, t_turn_right, t_tramplin + t_left, t_left, t_center + t_right, t_tramplin + t_left + t_right, t_left + t_right, t_tramplin + t_center, t_center, 0};

    std::vector<std::int32_t> trace_4 = {t_pause + 20, t_turn_left, t_turn_right, t_pause + 5, t_turn_right, t_turn_left, t_tramplin + t_center, t_center, t_tramplin + t_center, t_center, t_left + t_right, t_left + t_right, t_left + t_right, t_left + t_right, t_center, t_pause + 10, t_turn_right, t_turn_left, t_right, t_right, t_right, t_center, t_center + t_right, t_center + t_right, t_pause + 5, t_left, t_left, t_left, t_left + t_center, t_left + t_center, t_left + t_center, t_pause + 5, t_left + t_right, t_left + t_right, t_left + t_right, t_pause + 15, t_turn_left, t_left, t_center, t_pause + 5, t_tramplin + t_left, t_left + t_right, t_tramplin + t_center, t_center, t_left, t_tramplin + t_right, t_right, t_center, t_pause + 15, t_turn_right, t_tramplin + t_center, t_center, t_left + t_center, t_right, t_tramplin + t_center, t_center, t_left + t_center, t_center, t_right, t_tramplin + t_left, t_left, t_center, t_tramplin + t_right, t_left + t_right, t_left + t_center, t_pause + 15, t_turn_right, t_turn_left, t_turn_right, t_left + t_right, t_center, t_tramplin + t_left + t_right, t_left + t_right, t_center + t_right, t_pause + 15, t_turn_left, t_turn_right, t_turn_left, t_tramplin + t_right, t_pause + 5, t_tramplin + t_right, t_left + t_center + t_right, t_tramplin + t_left, t_pause + 15, t_tramplin + t_left, t_left + t_center + t_right, t_tramplin + t_center, t_pause + 15, t_tramplin + t_center, t_left + t_center + t_right, t_pause + 25, t_tramplin + t_right, t_left + t_center + t_right, 0};

    std::vector<std::int32_t> turn_faze = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 9, 10, 11, 9, 10, 11, 9, 10, 11, 6, 7, 8, 3, 4, 5, 0, 1, 2};

    std::int32_t scene_num = 0;
    std::shared_ptr<Program::ScreensProject> scene_scr;
    std::int32_t scene_cntr = 0;
    std::int32_t scene_status = 0;
    std::int32_t scene_music_timer = 0;

    void InitScene(std::int32_t num);

    void UpdateScene();

    std::vector<std::int32_t> final_explode = {1, 0, 1, 0, 1, 2, 3, 4, 2, 3, 4, 1, 0, 1, 0}; //15 элементов


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


    std::int32_t prev_suit = 0;
    void InitSuit();


    void UpdateSuit();

    void ShowSelectMenu();

    void SelectTest(std::int32_t delta);

    //переключение костюма Новы
    void SwitchSuite(bool hard_enable);


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


    //объект является врагом
    bool isEnemy(const std::shared_ptr<GameObject> &obj);

    //спавн объектов комнаты
    std::int32_t cntr_enter_in_room = 0; // счётчик, равен 2 после того как герой вошёл в комнату
    void SpawnObjects(const std::shared_ptr<GameObject> &obj);


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


    bool alarm_on = false;
    bool init_alarm = false;
    std::int32_t alarm_cntr = 0;
    std::array<bool, 16> stealth_flags;
    std::int32_t start_stealth_music = 0;

    bool stealth_pause = false; //стелс на паузе

    //инициализация стелс уровня
    void InitStealth();

    //получить состояние stealth_flags
    bool GetStealth(std::int32_t num);

    //установить состояние stealth_flags
    void SetStealth(std::int32_t num);


    //инициализация статусбара стелса
    void InitStelthStatusbar();

    //обновление стелс уровня
    void UpdateStealth();

    //Жаклин
    bool hero_invisible = false;
    bool j_game_over = false;
    bool j_win = false;
    bool hero_moved = false;
    bool j_skip_cicle = false;
    void Jacqueline(const std::shared_ptr<GameObject> &obj);

    //полицейский
    void JPolice(const std::shared_ptr<GameObject> &obj);

    //офисные работники
    void JOffice(const std::shared_ptr<GameObject> &obj);

    //пуля
    void JBullet(const std::shared_ptr<GameObject> &obj);

    //лифт
    std::int32_t lift_moves = 0;
    std::int32_t next_lift_num = 1;
    std::int32_t lift_pause = 0;
    std::shared_ptr<GameObject> lift_object;
    void JLift(const std::shared_ptr<GameObject> &obj);

    //дверь
    std::uint8_t return_room = 0;
    void JDoor(const std::shared_ptr<GameObject> &obj);

    //поиск объекта двери в активных объектах
    std::shared_ptr<Program::GameObject> FindDoor();

    //терминал
    std::int32_t terminal_num = 0;
    std::shared_ptr<GameObject> current_door;
    void JTerminal(const std::shared_ptr<GameObject> &obj);

    //инициализация анимаций с учётом невидимости Жаклин
    void InitJAnimation(const std::shared_ptr<GameObject> &obj, const std::string &anim, bool hard);

    //спавн объектов для стелса
    void StealthSpawn(const std::shared_ptr<GameObject> &obj);

    //урон для объекта
    bool JDamage(const std::shared_ptr<GameObject> &obj);

    //включение паники у офисных работников
    void JOfficePanic();

    //проверяем что между объектом и Жаклин нет офисного работника
    bool JCover(const std::shared_ptr<GameObject> &obj);

    //инициализация режима иконки статус-бара
    void InitJIcon(std::int32_t command);

    //обновление иконки статус-бара
    void UpdateJIcon();



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

public:

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
};
}
