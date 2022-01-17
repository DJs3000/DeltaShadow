#pragma once

#include "AnimTile.h"
#include "RoomLayers.h"
#include "Program.h"
#include "DeltaShadow.SetupForm.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <memory>
#include "rectangularvectors.h"
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace DeltaShadow { class GameObject; }
namespace DeltaShadow { class ObjectAnimation; }
namespace SdlDotNet { namespace Graphics { class Surface; } }
namespace DeltaShadow { class ScreensProject; }
namespace SdlDotNet { namespace Graphics { namespace Sprites { class Sprite; } } }
namespace DeltaShadow { class Sprite; }
namespace SdlDotNet { namespace Input { class Joystick; } }
namespace SharpDX { namespace XInput { class Controller; } }
namespace SdlDotNet { namespace Core { class QuitEventArgs; } }
namespace SdlDotNet { namespace Core { class TickEventArgs; } }
namespace SdlDotNet { namespace Input { class MouseMotionEventArgs; } }
namespace SdlDotNet { namespace Input { class KeyboardEventArgs; } }
namespace SdlDotNet { namespace Graphics { class VideoResizeEventArgs; } }
namespace SdlDotNet { namespace Audio { class Music; } }
namespace SdlDotNet { namespace Audio { class Sound; } }

using namespace SdlDotNet::Core;
using namespace SdlDotNet::Graphics;
using namespace SdlDotNet::Graphics::Sprites;
using namespace SdlDotNet::Audio;
using namespace SdlDotNet::Input;

using namespace Tao::Sdl;
using namespace SharpDX::XInput;

using namespace DeltaShadow::Properties;
using namespace WMPLib;


namespace DeltaShadow
{
	class Program : public std::enable_shared_from_this<Program>
	{
		//обработчик событий объекта
	private:
		void DoEvent(const std::shared_ptr<GameObject> &obj, const std::wstring &e);

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
		static constexpr std::uint8_t idNova = 1;
		static constexpr std::uint8_t idDust = 2;
		static constexpr std::uint8_t idExplosion = 3;
		static constexpr std::uint8_t idRocketSmoke = 4;
		static constexpr std::uint8_t idMultiExplosions = 5;
		static constexpr std::uint8_t idBlower = 6;
		static constexpr std::uint8_t idBubble = 7;
		static constexpr std::uint8_t idBumerang = 8;
		static constexpr std::uint8_t idWave = 9;
		static constexpr std::uint8_t idBattery = 10;
		static constexpr std::uint8_t idHeart = 11;
		static constexpr std::uint8_t idPowerup = 12;
		static constexpr std::uint8_t idMiniBattery = 13;
		static constexpr std::uint8_t idMiniHeart = 14;
		static constexpr std::uint8_t idMiniPowerup = 15;
		static constexpr std::uint8_t idSuit = 16;
		static constexpr std::uint8_t idStar = 17;
		static constexpr std::uint8_t idPlatform = 18;
		static constexpr std::uint8_t idSteam = 19;
		static constexpr std::uint8_t idFraction = 20;
		static constexpr std::uint8_t idDoor = 21;
		static constexpr std::uint8_t idTankette = 22;
		static constexpr std::uint8_t idDron = 23;
		static constexpr std::uint8_t idBullet = 24;
		static constexpr std::uint8_t idSpider = 25;
		static constexpr std::uint8_t idPiranha = 26;
		static constexpr std::uint8_t idBigPiranha = 27;
		static constexpr std::uint8_t idJelly = 28;
		static constexpr std::uint8_t idSpiderNest = 29;
		static constexpr std::uint8_t idBug = 30;
		static constexpr std::uint8_t idGun = 31;
		static constexpr std::uint8_t idDragonfly = 32;
		static constexpr std::uint8_t idFighterBomber = 33;
		static constexpr std::uint8_t idDronBomber = 34;
		static constexpr std::uint8_t idAlienClawBottom = 35;
		static constexpr std::uint8_t idAlienClawTop = 36;
		static constexpr std::uint8_t idAlienWorm = 37;
		static constexpr std::uint8_t idSlime = 38;
		static constexpr std::uint8_t idSonusVenator = 39;
		static constexpr std::uint8_t idBigSpider = 40;
		static constexpr std::uint8_t idCraken = 41;
		static constexpr std::uint8_t idMoth = 42;
		static constexpr std::uint8_t idRocketman = 43;
		static constexpr std::uint8_t idCrabBoss = 44;
		static constexpr std::uint8_t idFlyBoss = 45;
		static constexpr std::uint8_t idAlienPet = 46;
		static constexpr std::uint8_t idAlienSliderman = 47;
		static constexpr std::uint8_t idMegabrain = 48;
		static constexpr std::uint8_t idRocket = 49;
		static constexpr std::uint8_t idMiniBrain = 50;
		static constexpr std::uint8_t idBomb = 51;
		static constexpr std::uint8_t idFlyBomb = 52;
		static constexpr std::uint8_t idWaterFun = 53;
		static constexpr std::uint8_t idBubbleGenerator = 54;
		static constexpr std::uint8_t idJacqueline = 55;
		static constexpr std::uint8_t idJLift = 56;
		static constexpr std::uint8_t idJDoor = 57;
		static constexpr std::uint8_t idJTerminal = 58;
		static constexpr std::uint8_t idJPolice1 = 59;
		static constexpr std::uint8_t idJPolice2 = 60;
		static constexpr std::uint8_t idJPolice3 = 61;
		static constexpr std::uint8_t idJOffice1 = 62;
		static constexpr std::uint8_t idJOffice2 = 63;
		static constexpr std::uint8_t idJOffice3 = 64;
		static constexpr std::uint8_t idNovaBike = 65;
		static constexpr std::uint8_t idDLCBullet = 66;
		static constexpr std::uint8_t idJDJump = 67;
		static constexpr std::uint8_t idJGun = 68;
		static constexpr std::uint8_t idJShield = 69;
		static constexpr std::uint8_t idJBubble = 70;
		static constexpr std::uint8_t idDragon = 71;

		//описатель игрового объекта
	private:
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
		std::shared_ptr<GameObject> CreateObject(std::uint8_t name, std::int32_t x, std::int32_t y, bool direction, bool actual_object);

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
		std::shared_ptr<GameObject> CreateChild(const std::shared_ptr<GameObject> &obj, std::uint8_t name, std::int32_t xoffset, std::int32_t yoffset);




		//гравитация объекта,возвращает true если объект в воздухе

		std::int32_t ga = 0, gb = 0;
		bool Gravity(const std::shared_ptr<GameObject> &obj);

		void ChangeDirection(const std::shared_ptr<GameObject> &obj);

		//движение объекта вперёд
		bool MoveObjectForward(const std::shared_ptr<GameObject> &obj, std::int32_t speed);

		bool SimpleMoveObjectForward(const std::shared_ptr<GameObject> &obj, std::int32_t speed);

		//создать пулю
		void CreateBullet(const std::shared_ptr<GameObject> &obj, const std::wstring &animations, const std::wstring &anim_name, std::int32_t xoffset, std::int32_t yoffset, std::int32_t xdelta, std::int32_t ydelta, bool damageble);

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

		std::shared_ptr<GameObject> EnemyDamage(const std::shared_ptr<GameObject> &obj, std::int32_t xdist);

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


		std::vector<Color> next_palette = std::vector<Color>(256);
//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
//ORIGINAL LINE: Color[,] attr_palette = new Color[2, 16];
		std::vector<std::vector<Color>> attr_palette = RectangularVectors::RectangularColorVector(2, 16); //классическая палитра
		std::shared_ptr<Random> rnd = std::make_shared<Random>(); //генератор случайных чисел

	public:
		std::shared_ptr<Surface> screen;
	private:
		std::shared_ptr<Surface> screen_copy; //копия экрана
		std::shared_ptr<Surface> scroll_screen; //экран для скроллинга комнаты
	public:
//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
//ORIGINAL LINE: public static Color[,,] attr_layer = new Color[2, 256, 192];
		static std::vector<std::vector<std::vector<Color>>> attr_layer; //атрибутный слой экрана для вывода монохромных спрайтов

	private:
		std::int32_t scroll_direction = 0; //направление скроллинга, 1 - вверх, 2 - вправо, 3 - вниз, 4 - влево
		std::int32_t scroll_cntr = 0; //счётчик скроллинга

		//инициализация графического движка
		void InitGEngine();

		//функция возвращает цвет, соответствующий цвету ZX Spectrum [0..15]
	public:
		System::Drawing::Color GetColor(std::int32_t zxcolor);

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
		std::vector<std::vector<std::vector<std::uint8_t>>> current_tilesets;
		void LoadLocationProject(std::int32_t num);

		//прорисовка классического тайлсета
		void DrawClassicTileset();

		//проверка на необходимость скроллинга комнаты
		void NeedScrollRoom();

		//увеличить game_cicle_counter
		void IncGameCicleCounter();

		void SetBorder(Color c);


		bool external_resource = false; //разрешение использования внешних ресурсов
		bool demo_version = false;

		bool cheats_enabled = false;

		bool debug_mode = false;
	public:
		static std::wstring language;
	private:
		static constexpr std::int32_t classic_version = 0;
		static constexpr std::int32_t next_version = 1;
		std::int32_t release_type = next_version;

		std::int32_t game_mode = 0; //режим игры
		static constexpr std::int32_t debug_menu_mode = 0;
		static constexpr std::int32_t platforming_mode = 1;
		static constexpr std::int32_t race_mode = 2;
		static constexpr std::int32_t game_over_mode = 3;
		static constexpr std::int32_t stealth_mode = 4;
		static constexpr std::int32_t clip_mode = 5;
		static constexpr std::int32_t suit_mode = 6;
		static constexpr std::int32_t select_level_mode = 7;
		static constexpr std::int32_t main_menu_mode = 8;
		static constexpr std::int32_t new_game_mode = 9;
		static constexpr std::int32_t select_diff_mode = 10;
		static constexpr std::int32_t cancel_mission_mode = 11;
		static constexpr std::int32_t select_message_mode = 12;
		static constexpr std::int32_t read_message_mode = 13;
		static constexpr std::int32_t load_screen_mode = 14;
		static constexpr std::int32_t settings_mode = 15;
		static constexpr std::int32_t control_settings_mode = 16;
		static constexpr std::int32_t redefine_mode = 17;
		static constexpr std::int32_t graphic_settings_mode = 18;
		static constexpr std::int32_t sound_settings_mode = 19;
		static constexpr std::int32_t system_settings_mode = 20;
		static constexpr std::int32_t areyousure_mode = 21;
		static constexpr std::int32_t reset_mode = 22;
		static constexpr std::int32_t player_mode = 23;

	public:
		static std::int32_t sprite_mode; //режим спрайтов
		static std::int32_t tiles_mode; //режим тайлов
	private:
		static constexpr std::int32_t zx_classic_mode = 0;
		static constexpr std::int32_t zx_next_mode = 1;

		std::int32_t sound_mode = one_ay_mode; //режим музыки
		static constexpr std::int32_t one_ay_mode = 0;
		static constexpr std::int32_t ts_mode = 1;

		std::vector<std::shared_ptr<GameObject>> game_objects = std::vector<std::shared_ptr<GameObject>>(128); //список всех объектов локации
		std::vector<std::shared_ptr<GameObject>> actual_objects = std::vector<std::shared_ptr<GameObject>>(128); //ссылки на актуальные объекты
		std::shared_ptr<GameObject> hero_object; //объект героя
		bool hero_start_direction = false;

		static constexpr std::int32_t low_priority = 0;
		static constexpr std::int32_t normal_priority = 1;
		static constexpr std::int32_t high_priority = 2;

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
		std::vector<std::vector<std::int32_t>> Loc; //массив с локацией
		std::int32_t LocWidth = 0;
		std::int32_t LocHeight = 0;

//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
//ORIGINAL LINE: Surface[,] Tileset = new Surface[2, 256];
		std::vector<std::vector<std::shared_ptr<Surface>>> Tileset = RectangularVectors::RectangularSurfaceVector(2, 256); //изображения тайлов
//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
//ORIGINAL LINE: Color[,,,] TilesetAttr = new Color[2, 256, 16, 16];
		std::vector<std::vector<std::vector<std::vector<Color>>>> TilesetAttr = RectangularVectors::RectangularColorVector(2, 256, 16, 16); //атрибуты тайлсета для атрибутного слоя
		std::vector<std::int32_t> TilesetProperty = std::vector<std::int32_t>(256); //свойства тайлов в тайлсете

		std::vector<std::shared_ptr<AnimTile>> RoomAnimTiles = std::vector<std::shared_ptr<AnimTile>>(); //список анимированных тайлов в комнате

		std::vector<std::vector<std::shared_ptr<RoomLayers>>> RoomsLayers; //массив слоёв в комнатах локации

		bool secret_boss_enabled = false; //включен секретный босс

		std::int32_t current_suit = 0; //режим костюма, 0 - без костюма
		std::vector<bool> have_suit = std::vector<bool>(4); //костюмы в наличии (0 - без костюма)
		bool no_suit_run = false;

		//свойства тайлов
		static constexpr std::int32_t isEmpty = 0;
		static constexpr std::int32_t isFloor = 1;
		static constexpr std::int32_t isLadder = 2;
		static constexpr std::int32_t isWater = 3;
		static constexpr std::int32_t isSpike = 4;
		static constexpr std::int32_t isPlatform = 5;
		static constexpr std::int32_t isRails = 6;
		static constexpr std::int32_t isShift = 7;

		std::int32_t particle_cntr = 0; //счётчик частиц

		std::int32_t current_level = 1; //номер текущего уровня
		std::int32_t current_location = 1; //номер текущей локации
		std::int32_t x_home = 0, y_home = 0; //координаты верхнего левого угла комнаты в пикселях
		std::int32_t x_home_tile = 0, y_home_tile = 0; //координаты верхнего левого угла комнаты в тайлах
		std::uint8_t current_xy_room = 0; //текущая координата комнаты
//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
//ORIGINAL LINE: int[,] Room = new int[16, 10];
		std::vector<std::vector<std::int32_t>> Room = RectangularVectors::RectangularStd::int32_tVector(16, 10); //массив с номерами тайлов комнаты
//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
//ORIGINAL LINE: bool[,] screen_refresh_tab = new bool[16, 10];
		std::vector<std::vector<bool>> screen_refresh_tab = RectangularVectors::RectangularBoolVector(16, 10); //таблица обновления экрана

		//сохранение для безопасного возвращения
		std::uint8_t last_safe_xy_room = 0; //координата безопасной комнаты
		std::int32_t last_safe_x = 0, last_safe_y = 0; //координаты героя в безопасной комнате
		bool last_safe_direction = false; //направление героя в безопасной комнате

		bool bw_color_mode = false; //черно-белый режим

		bool kempston_on = false;

		std::shared_ptr<ScreensProject> statusbar;
		std::shared_ptr<ScreensProject> select_menu;

		std::unordered_map<std::wstring, std::uint8_t> objects_names = std::unordered_map<std::wstring, std::uint8_t>();
		std::unordered_map<std::int32_t, std::wstring> levels_names = std::unordered_map<std::int32_t, std::wstring>();
		std::unordered_map<std::int32_t, std::wstring> music_names = std::unordered_map<std::int32_t, std::wstring>();

		//------------------------------------- основной блок -------------------------------------

		//инициализация главной формы
	public:
		void MainInit();

		//сохранение прогресса игры
		static std::wstring current_save_version;
	private:
		void SaveProgress();

		//загрузка прогресса игры
		bool loaded_progress = false;
		void LoadProgress();

		//старт игры
		void StartTimer_Tick(const std::shared_ptr<void> &sender, const std::shared_ptr<EventArgs> &e);

		//главный цикл
		std::int32_t pause_cnt = 0; //только для прототипа
		void MainCicle();


		//инициализация отладочного меню
		void InitDebugMenu();

		std::vector<std::wstring> level_names = {L"Race", L"Jacqueline", L"Level 1-1", L"Level 1-2", L"Level 1-3", L"Dragon 1", L"Boss 1", L"Level 2-1", L"Level 2-2", L"Level 2-3", L"Dragon 2", L"Boss 2", L"Level 3-1", L"Level 3-2", L"Level 3-3", L"Dragon 3", L"Boss 3", L"Level 4-1", L"Level 4-2", L"Level 4-3", L"Level 4-4", L"Level 4-5", L"Level 4-6", L"Level 4-7", L"FinalBoss", L"Extra 1-4", L"Extra 2-4", L"Extra 3-4", L"Extra 4-8", L"Jacqueline DLC"};

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
		std::vector<Key> KeysMapNew;
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
			std::wstring Name; //имя анимации

			//класс спрайта
		public:
			class Sprite : public std::enable_shared_from_this<Sprite>
			{
			public:
				std::wstring Name; //имя спрайта
				std::int32_t Type = 0; //тип спрайта
				std::int32_t Width = 0; //ширина спрайта
				std::int32_t Height = 0; //высота спрайта
				std::vector<std::vector<std::int32_t>> ClassicLayer; //слой для классического режима
				std::vector<std::vector<Color>> NextLayer; //слой для режима Next
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
				std::wstring Event; //название события
			};

			//класс анимации
		public:
			class Animation : public std::enable_shared_from_this<Animation>
			{
			public:
				std::wstring Name; //имя анимации
				std::vector<std::shared_ptr<Frame>> Frames; //список кадров
				bool Loop = false; //анимация зациклена
			};

		public:
			std::vector<std::shared_ptr<Animation>> Animations = std::vector<std::shared_ptr<Animation>>(); //список анимаций
		};

	private:
		std::vector<std::shared_ptr<ObjectAnimation>> ObjectAnimations = std::vector<std::shared_ptr<ObjectAnimation>>(); //наборы анимаций объектов

		//загрузка анимаций по имени
		void LoadAnimations(const std::wstring &name);

		//загрузка проекта анимаций
		void LoadAnimationsProject(const std::wstring &name);

		//поиск спрайта по имени
		std::shared_ptr<ObjectAnimation::Sprite> FindSprite(const std::wstring &name, const std::shared_ptr<ObjectAnimation> &anim);

		//инициализация анимации по имени
		void InitAnimation(const std::shared_ptr<GameObject> &obj, const std::wstring &name, bool hard_enable);

		void InitAnimation(const std::shared_ptr<GameObject> &obj, std::uint8_t id_anim, bool hard_enable);

		//проигрывание анимации (вызывается каждый игровой цикл)
		void PlayAnimation(const std::shared_ptr<GameObject> &obj);

		//высота и ширина объекта
		void GetObjSize(const std::shared_ptr<GameObject> &obj);

		//поиск набора анимаций по имени
		std::vector<std::shared_ptr<ObjectAnimation>> FindObjectAnimation(const std::wstring &name);


		std::int32_t location_status = 0; //текущий статус локации
		std::int32_t location_counter = 0; //счётчик для всяких действий в локации
		std::int32_t start_life = 0, start_energy = 0, start_weapon = 0; //значения на страте локации

		//инициализация режима платформинга
		void InitPlatforming(bool boss);

		//инициализация статусбара платформинга
		void InitPlatformingStatusbar();

//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
//ORIGINAL LINE: int[,] fall_down_effect = new int[16, 10];
		std::vector<std::vector<std::int32_t>> fall_down_effect = RectangularVectors::RectangularStd::int32_tVector(16, 10);

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
		static std::shared_ptr<Joystick> kempston;
		static std::vector<std::shared_ptr<joy_button>> kempston_buttons;
		static float kempston_ax_v;
		static float kempston_ax_h;
		static std::vector<ButtonKeyState> kempston_btns;
	private:
		std::shared_ptr<SetupForm> setup_form = nullptr;

		static std::shared_ptr<Controller> x_input_controller;
		static Gamepad x_input_gamepad;

		//[STAThread]
	public:
		static void Main();

		Program();

		void Run();

		void Quit(const std::shared_ptr<void> &sender, const std::shared_ptr<QuitEventArgs> &e);

		static std::int32_t x_screen_home;
		static std::int32_t y_screen_home;
		void Update(const std::shared_ptr<void> &sender, const std::shared_ptr<TickEventArgs> &e);

	private:
		std::int32_t hide_cursor_timer = 0;
		std::int32_t show_cursor_timer = 0;
	public:
		void MouseMotion(const std::shared_ptr<void> &sender, const std::shared_ptr<MouseMotionEventArgs> &e);

	private:
		std::uint8_t PressedKeysStatus = 0;
	public:
		void KeyboardDown(const std::shared_ptr<void> &sender, const std::shared_ptr<KeyboardEventArgs> &e);

		void KeyboardUp(const std::shared_ptr<void> &sender, const std::shared_ptr<KeyboardEventArgs> &e);

		static void InitVideo();

		void VideoResize(const std::shared_ptr<void> &sender, const std::shared_ptr<VideoResizeEventArgs> &e);

		static void SaveSettings();

		static void LoadSettings();

		static void StartKempston();

		//[System.Runtime.InteropServices.DllImport("user32.dll", CharSet = System.Runtime.InteropServices.CharSet.Auto, ExactSpelling = true)]
		//public static extern short GetAsyncKeyState(int vkey);


	private:
		std::shared_ptr<ScreensProject> race_imgs;

		std::vector<std::int32_t> race_objects;
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

		std::wstring top_name;

		//инициализация гонки
		void InitRace();

		//прорисовка верха
		void DrawRaceTop();

		//обновление гонки
		void UpdateRace();

		//уменьшение энергии Новы
		void DecLife(const std::shared_ptr<GameObject> &obj, std::int32_t value);

		static constexpr std::int32_t t_pause = 0x80;
		static constexpr std::int32_t t_right = 0x01;
		static constexpr std::int32_t t_center = 0x02;
		static constexpr std::int32_t t_left = 0x04;
		static constexpr std::int32_t t_tramplin = 0x08;
		static constexpr std::int32_t t_turn_left = 0x10;
		static constexpr std::int32_t t_turn_right = 0x20;

		std::vector<std::int32_t> trace;
		std::vector<std::int32_t> trace_1 = {t_pause + 20, t_turn_right, t_turn_left, t_pause + 5, t_turn_right, t_turn_left, t_left + t_right, t_left + t_right, t_left + t_right, t_left + t_right, t_center, t_pause + 15, t_turn_right, t_tramplin + t_center, t_center, t_left + t_center, t_right, t_tramplin + t_center, t_center, t_left + t_center, t_center, t_right, t_tramplin + t_left, t_left + t_right, t_center, t_tramplin + t_right, t_left + t_right, t_left + t_center, t_pause + 5, t_tramplin + t_center, t_center, t_left, t_left, t_left + t_center, t_left + t_center, t_left + t_center, t_pause + 15, t_turn_left, t_pause + 5, t_tramplin + t_left, t_left, t_tramplin + t_center, t_center, t_left, t_tramplin + t_right, t_right, t_center, t_center, t_pause + 10, t_turn_right, t_turn_left, t_right, t_tramplin + t_center, t_center, t_right, t_tramplin + t_center, t_center, t_right, t_center, t_center + t_right, t_center + t_right, t_pause + 15, t_turn_left, t_turn_right, t_turn_left, t_pause + 5, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_tramplin + t_left, t_left + t_right, t_pause + 15, t_tramplin + t_center, t_center, t_pause + 25, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_turn_right, t_turn_left, t_turn_right, t_tramplin + t_left, t_left + t_right, t_center, t_tramplin + t_left + t_right, t_left + t_right, t_tramplin + t_center, t_center, t_pause + 5, t_tramplin + t_right, t_left + t_right, t_left + t_right, t_left + t_right, 0};

		std::vector<std::int32_t> trace_2 = {t_pause + 20, t_turn_right, t_left + t_right, t_pause + 15, t_turn_left, t_pause + 5, t_turn_right, t_turn_left, t_pause + 5, t_left + t_right, t_left + t_right, t_left + t_right, t_center, t_pause + 5, t_tramplin + t_center, t_center, t_left, t_left, t_left + t_center, t_left + t_center, t_left + t_center, t_pause + 5, t_tramplin + t_right, t_left + t_right, t_left + t_right, t_left + t_right, t_pause + 15, t_turn_left, t_turn_right, t_turn_left, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_turn_right, t_tramplin + t_left, t_left, t_tramplin + t_center, t_center, t_left, t_tramplin + t_right, t_right, t_center, t_center, t_pause + 15, t_turn_right, t_tramplin + t_center, t_center, t_left + t_center, t_right, t_tramplin + t_center, t_center, t_left + t_center, t_center, t_right, t_tramplin + t_left, t_left + t_right, t_center, t_tramplin + t_right, t_left + t_right, t_left + t_center, t_pause + 10, t_turn_left, t_turn_left, t_right, t_tramplin + t_center, t_center, t_right, t_tramplin + t_center, t_center, t_right, t_center, t_center + t_right, t_center + t_right, t_pause + 5, t_tramplin + t_left, t_left + t_right, t_pause + 15, t_tramplin + t_center, t_center, t_pause + 25, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_turn_right, t_turn_left, t_turn_right, t_tramplin + t_left, t_left + t_right, t_center, t_tramplin + t_left + t_right, t_left + t_right, t_tramplin + t_center, t_center, 0};

		std::vector<std::int32_t> trace_3 = {t_pause + 20, t_turn_left, t_left + t_right, t_pause + 15, t_turn_right, t_turn_left, t_turn_right, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_turn_left, t_tramplin + t_left, t_left, t_tramplin + t_center, t_center, t_right, t_tramplin + t_left, t_left, t_center, t_pause + 5, t_tramplin + t_center, t_center, t_left, t_left, t_left + t_center, t_left + t_center, t_left + t_center, t_pause + 10, t_turn_right, t_turn_left, t_right, t_tramplin + t_center, t_center, t_right, t_tramplin + t_center, t_center, t_right, t_center, t_center + t_right, t_center + t_right, t_pause + 5, t_tramplin + t_left, t_left + t_right, t_pause + 15, t_turn_right, t_pause + 5, t_turn_left, t_turn_right, t_pause + 5, t_left + t_right, t_left + t_right, t_left + t_right, t_center, t_center, t_pause + 15, t_tramplin + t_center, t_center, t_pause + 15, t_turn_right, t_tramplin + t_center, t_center, t_left + t_center, t_right, t_tramplin + t_center, t_center, t_left + t_center, t_center, t_right, t_tramplin + t_left, t_left, t_center, t_tramplin + t_right, t_left + t_right, t_left + t_center, t_pause + 5, t_tramplin + t_right, t_left + t_right, t_left + t_right, t_left + t_right, t_pause + 25, t_tramplin + t_right, t_left + t_right, t_pause + 15, t_turn_left, t_turn_left, t_turn_right, t_tramplin + t_left, t_left, t_center + t_right, t_tramplin + t_left + t_right, t_left + t_right, t_tramplin + t_center, t_center, 0};

		std::vector<std::int32_t> trace_4 = {t_pause + 20, t_turn_left, t_turn_right, t_pause + 5, t_turn_right, t_turn_left, t_tramplin + t_center, t_center, t_tramplin + t_center, t_center, t_left + t_right, t_left + t_right, t_left + t_right, t_left + t_right, t_center, t_pause + 10, t_turn_right, t_turn_left, t_right, t_right, t_right, t_center, t_center + t_right, t_center + t_right, t_pause + 5, t_left, t_left, t_left, t_left + t_center, t_left + t_center, t_left + t_center, t_pause + 5, t_left + t_right, t_left + t_right, t_left + t_right, t_pause + 15, t_turn_left, t_left, t_center, t_pause + 5, t_tramplin + t_left, t_left + t_right, t_tramplin + t_center, t_center, t_left, t_tramplin + t_right, t_right, t_center, t_pause + 15, t_turn_right, t_tramplin + t_center, t_center, t_left + t_center, t_right, t_tramplin + t_center, t_center, t_left + t_center, t_center, t_right, t_tramplin + t_left, t_left, t_center, t_tramplin + t_right, t_left + t_right, t_left + t_center, t_pause + 15, t_turn_right, t_turn_left, t_turn_right, t_left + t_right, t_center, t_tramplin + t_left + t_right, t_left + t_right, t_center + t_right, t_pause + 15, t_turn_left, t_turn_right, t_turn_left, t_tramplin + t_right, t_pause + 5, t_tramplin + t_right, t_left + t_center + t_right, t_tramplin + t_left, t_pause + 15, t_tramplin + t_left, t_left + t_center + t_right, t_tramplin + t_center, t_pause + 15, t_tramplin + t_center, t_left + t_center + t_right, t_pause + 25, t_tramplin + t_right, t_left + t_center + t_right, 0};

		std::vector<std::int32_t> turn_faze = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 9, 10, 11, 9, 10, 11, 9, 10, 11, 6, 7, 8, 3, 4, 5, 0, 1, 2};


		std::int32_t scene_num = 0;
		std::shared_ptr<ScreensProject> scene_scr;
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
			std::shared_ptr<Surface> img; //изображение спрайта
		};

	public:
		class Sprite : public std::enable_shared_from_this<Sprite>
		{
		public:
			std::wstring name; //имя спрайта
			std::int32_t height = 0; //ширина спрайта в символах
			std::int32_t width = 0; //высота спрайта в символах
			std::vector<std::vector<std::shared_ptr<Tile>>> tiles; // массив тайлов

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
			std::wstring name; //имя экрана
			bool visible = false; //показыать экран
			std::vector<std::shared_ptr<ScreenSprite>> sprites = std::vector<std::shared_ptr<ScreenSprite>>();
		};

	private:
		class ScreensProject : public std::enable_shared_from_this<ScreensProject>
		{
		public:
			std::vector<std::shared_ptr<Tile>> Tileset = std::vector<std::shared_ptr<Tile>>();
			std::vector<std::shared_ptr<Sprite>> Sprites = std::vector<std::shared_ptr<Sprite>>();
			std::vector<std::shared_ptr<Screen>> Screens = std::vector<std::shared_ptr<Screen>>();
		};

		//инициализцация проекта экранов
	private:
		std::shared_ptr<ScreensProject> InitScreensProject(const std::wstring &name);

		//добавить тайл в тайлсет
		std::shared_ptr<Tile> AddTile(const std::shared_ptr<ScreensProject> &obj, std::vector<std::uint8_t> &data);

	public:
		Color GetAttrColor(std::uint8_t attr, bool enable);

		//поиск спрайта по имени в списке Sprites
	private:
		std::shared_ptr<Sprite> FindSprite(const std::shared_ptr<ScreensProject> &proj, const std::wstring &name);

		//поиск экрана по имени в списке Screens
		std::shared_ptr<Screen> FindScreen(const std::shared_ptr<ScreensProject> &proj, const std::wstring &name);

		//вывод экрана

		void DrawScreen(const std::shared_ptr<ScreensProject> &proj, std::int32_t num);

		//вывод экранного спрайта по заданным координатам и обрезанного по окну
		void DrawScreenSprite(const std::shared_ptr<ScreensProject> &proj, const std::wstring &name, std::int32_t xcord, std::int32_t ycord, std::int32_t xwin, std::int32_t ywin, std::int32_t width, std::int32_t height);


		std::int32_t prev_suit = 0;
		void InitSuit();


		void UpdateSuit();

		void ShowSelectMenu();

		void SelectTest(std::int32_t delta);

		//переключение костюма Новы
		void SwitchSuite(bool hard_enable);


		std::shared_ptr<Music> GameSoundTheme;
		std::shared_ptr<Sound> MenuSoundTheme;

		std::vector<std::shared_ptr<Stream>> SFX_Bank; //банк звуковых эффектов
		std::vector<std::int32_t> SFX_Priority; //приоритет звука
		std::shared_ptr<SoundPlayer> SFX_Player = std::make_shared<SoundPlayer>(); //проигрыватель звуковых эффектов

		static constexpr std::int32_t sfx_beetle = 0;
		static constexpr std::int32_t sfx_bumerang = 1;
		static constexpr std::int32_t sfx_damage = 2;
		static constexpr std::int32_t sfx_dogscream = 3;
		static constexpr std::int32_t sfx_dooropen = 4;
		static constexpr std::int32_t sfx_doors = 5;
		static constexpr std::int32_t sfx_droid = 6;
		static constexpr std::int32_t sfx_elevator = 7;
		static constexpr std::int32_t sfx_explosion = 8;
		static constexpr std::int32_t sfx_gotonthewall = 9;
		static constexpr std::int32_t sfx_lowpower = 10;
		static constexpr std::int32_t sfx_missshoot = 11;
		static constexpr std::int32_t sfx_powerup = 12;
		static constexpr std::int32_t sfx_race_block_hit = 13;
		static constexpr std::int32_t sfx_race_down = 14;
		static constexpr std::int32_t sfx_race_jump = 15;
		static constexpr std::int32_t sfx_race_wall_hit = 16;
		static constexpr std::int32_t sfx_rocket = 17;
		static constexpr std::int32_t sfx_shocker = 18;
		static constexpr std::int32_t sfx_slide = 19;
		static constexpr std::int32_t sfx_slime = 20;
		static constexpr std::int32_t sfx_start = 21;
		static constexpr std::int32_t sfx_stealth = 22;
		static constexpr std::int32_t sfx_steam = 23;
		static constexpr std::int32_t sfx_stungun = 24;
		static constexpr std::int32_t sfx_switch = 25;
		static constexpr std::int32_t sfx_tanketteborn = 26;
		static constexpr std::int32_t sfx_tanketteshoot = 27;
		static constexpr std::int32_t sfx_terminal = 28;
		static constexpr std::int32_t sfx_type = 29;
		static constexpr std::int32_t sfx_wave = 30;
		static constexpr std::int32_t sfx_star = 31;


		//загрузка банка звуковых эффектов
		void InitSFXBank();

		void LoadSFX(const std::wstring &name, std::int32_t num, std::int32_t priority);

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

		static constexpr std::int32_t im_none = 0;
		static constexpr std::int32_t im_damage = 1;
		static constexpr std::int32_t im_noise = 2;
		std::int32_t icon_mode = 0;
		std::int32_t icon_cntr = 0;
		std::int32_t icon_timer = 0;

		//изменение шкалы
		std::int32_t UpdateBar(std::int32_t current, std::int32_t value, std::int32_t x, std::int32_t y);


		bool alarm_on = false;
		bool init_alarm = false;
		std::int32_t alarm_cntr = 0;
		std::vector<bool> stealth_flags = std::vector<bool>(16);
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
		std::shared_ptr<GameObject> FindDoor();

		//терминал
		std::int32_t terminal_num = 0;
		std::shared_ptr<GameObject> current_door;
		void JTerminal(const std::shared_ptr<GameObject> &obj);

		//инициализация анимаций с учётом невидимости Жаклин
		void InitJAnimation(const std::shared_ptr<GameObject> &obj, const std::wstring &anim, bool hard);

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

		std::vector<std::int32_t> TimerCounters = std::vector<std::int32_t>(4); //таймеры для анимации тайлов
		std::vector<std::int32_t> TimerTiles = std::vector<std::int32_t>(4); //номера тайлов для анимации
		std::vector<std::int32_t> RndTimerCounters = std::vector<std::int32_t>(4); //таймеры для случайной анимации тайлов
		std::vector<std::int32_t> RndTimerTiles = std::vector<std::int32_t>(4); //номера тайлов для случайной анимации

		std::vector<Key> KeysMap = {Key::W, Key::S, Key::A, Key::D, Key::M, Key::B, Key::N, Key::P}; //карта кнопок
		std::vector<Key> KeysMapStandart = {Key::W, Key::S, Key::A, Key::D, Key::M, Key::B, Key::N, Key::P}; //карта кнопок
		std::uint8_t pressed_keys = 0; //состояние кнопок управления (побитовое)
		std::uint8_t last_keys = 0; //предыдущее состояние кнопок
		std::uint8_t single_keys = 0; //одиночно нажатые кнопки
		static constexpr std::uint8_t Key_Up = 0x01;
		static constexpr std::uint8_t Key_Down = 0x02;
		static constexpr std::uint8_t Key_Left = 0x04;
		static constexpr std::uint8_t Key_Right = 0x08;
		static constexpr std::uint8_t Key_Select = 0x10;
		static constexpr std::uint8_t Key_Fire = 0x20;
		static constexpr std::uint8_t Key_Jump = 0x40;
		static constexpr std::uint8_t Key_Pause = 0x80;

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
		enum class KeyCode
		{
			A = 0x41,
			Add = 0x6b,
			Alt = 0x40000,
			Apps = 0x5d,
			Attn = 0xf6,
			B = 0x42,
			Back = 8,
			BrowserBack = 0xa6,
			BrowserFavorites = 0xab,
			BrowserForward = 0xa7,
			BrowserHome = 0xac,
			BrowserRefresh = 0xa8,
			BrowserSearch = 170,
			BrowserStop = 0xa9,
			C = 0x43,
			Cancel = 3,
			Capital = 20,
			CapsLock = 20,
			Clear = 12,
			Control = 0x20000,
			ControlKey = 0x11,
			Crsel = 0xf7,
			D = 0x44,
			D0 = 0x30,
			D1 = 0x31,
			D2 = 50,
			D3 = 0x33,
			D4 = 0x34,
			D5 = 0x35,
			D6 = 0x36,
			D7 = 0x37,
			D8 = 0x38,
			D9 = 0x39,
			Decimal = 110,
			Delete = 0x2e,
			Divide = 0x6f,
			Down = 40,
			E = 0x45,
			End = 0x23,
			Enter = 13,
			EraseEof = 0xf9,
			Escape = 0x1b,
			Execute = 0x2b,
			Exsel = 0xf8,
			F = 70,
			F1 = 0x70,
			F10 = 0x79,
			F11 = 0x7a,
			F12 = 0x7b,
			F13 = 0x7c,
			F14 = 0x7d,
			F15 = 0x7e,
			F16 = 0x7f,
			F17 = 0x80,
			F18 = 0x81,
			F19 = 130,
			F2 = 0x71,
			F20 = 0x83,
			F21 = 0x84,
			F22 = 0x85,
			F23 = 0x86,
			F24 = 0x87,
			F3 = 0x72,
			F4 = 0x73,
			F5 = 0x74,
			F6 = 0x75,
			F7 = 0x76,
			F8 = 0x77,
			F9 = 120,
			FinalMode = 0x18,
			G = 0x47,
			H = 0x48,
			HanguelMode = 0x15,
			HangulMode = 0x15,
			HanjaMode = 0x19,
			Help = 0x2f,
			Home = 0x24,
			I = 0x49,
			IMEAccept = 30,
			IMEAceept = 30,
			IMEConvert = 0x1c,
			IMEModeChange = 0x1f,
			IMENonconvert = 0x1d,
			Insert = 0x2d,
			J = 0x4a,
			JunjaMode = 0x17,
			K = 0x4b,
			KanaMode = 0x15,
			KanjiMode = 0x19,
			KeyCode = 0xffff,
			L = 0x4c,
			LaunchApplication1 = 0xb6,
			LaunchApplication2 = 0xb7,
			LaunchMail = 180,
			LButton = 1,
			LControlKey = 0xa2,
			Left = 0x25,
			LineFeed = 10,
			LMenu = 0xa4,
			LShiftKey = 160,
			LWin = 0x5b,
			M = 0x4d,
			MButton = 4,
			MediaNextTrack = 0xb0,
			MediaPlayPause = 0xb3,
			MediaPreviousTrack = 0xb1,
			MediaStop = 0xb2,
			Menu = 0x12,
			Modifiers = -65536,
			Multiply = 0x6a,
			N = 0x4e,
			Next = 0x22,
			NoName = 0xfc,
			None = 0,
			NumLock = 0x90,
			NumPad0 = 0x60,
			NumPad1 = 0x61,
			NumPad2 = 0x62,
			NumPad3 = 0x63,
			NumPad4 = 100,
			NumPad5 = 0x65,
			NumPad6 = 0x66,
			NumPad7 = 0x67,
			NumPad8 = 0x68,
			NumPad9 = 0x69,
			O = 0x4f,
			Oem1 = 0xba,
			Oem102 = 0xe2,
			Oem2 = 0xbf,
			Oem3 = 0xc0,
			Oem4 = 0xdb,
			Oem5 = 220,
			Oem6 = 0xdd,
			Oem7 = 0xde,
			Oem8 = 0xdf,
			OemBackslash = 0xe2,
			OemClear = 0xfe,
			OemCloseBrackets = 0xdd,
			Oemcomma = 0xbc,
			OemMinus = 0xbd,
			OemOpenBrackets = 0xdb,
			OemPeriod = 190,
			OemPipe = 220,
			Oemplus = 0xbb,
			OemQuestion = 0xbf,
			OemQuotes = 0xde,
			OemSemicolon = 0xba,
			Oemtilde = 0xc0,
			P = 80,
			Pa1 = 0xfd,
			Packet = 0xe7,
			PageDown = 0x22,
			PageUp = 0x21,
			Pause = 0x13,
			Play = 250,
			Print = 0x2a,
			PrintScreen = 0x2c,
			Prior = 0x21,
			ProcessKey = 0xe5,
			Q = 0x51,
			R = 0x52,
			RButton = 2,
			RControlKey = 0xa3,
			Return = 13,
			Right = 0x27,
			RMenu = 0xa5,
			RShiftKey = 0xa1,
			RWin = 0x5c,
			S = 0x53,
			Scroll = 0x91,
			Select = 0x29,
			SelectMedia = 0xb5,
			Separator = 0x6c,
			Shift = 0x10000,
			ShiftKey = 0x10,
			Sleep = 0x5f,
			Snapshot = 0x2c,
			Space = 0x20,
			Subtract = 0x6d,
			T = 0x54,
			Tab = 9,
			U = 0x55,
			Up = 0x26,
			V = 0x56,
			VolumeDown = 0xae,
			VolumeMute = 0xad,
			VolumeUp = 0xaf,
			W = 0x57,
			X = 0x58,
			XButton1 = 5,
			XButton2 = 6,
			Y = 0x59,
			Z = 90,
			Zoom = 0xfb
		};


	private:
//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
//ORIGINAL LINE: bool[][,] font32 = new bool[256][,];
		std::vector<std::vector<std::vector<bool>>> font32 = RectangularVectors::RectangularBoolVector(256, ,);
		std::vector<std::uint8_t> texts;
		bool invert_print = false;
		std::shared_ptr<Surface> next_mini_powerups;

		//инициализация шрифтов
	public:
		void InitFonts();

		//вывод символа шрифтом font32
	private:
		void DrawSymbol32(std::int32_t x, std::int32_t y, std::uint8_t symbol, std::uint8_t attr);

		//печать строки шрифтом font32
		void PrintString32(std::int32_t x, std::int32_t y, const std::wstring &text);

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
