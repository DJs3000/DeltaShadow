#include "Resources.Designer.h"

namespace DeltaShadow
{
	namespace Properties
	{

std::shared_ptr<System::Resources::ResourceManager> Resources::resourceMan;
std::shared_ptr<System::Globalization::CultureInfo> Resources::resourceCulture;

		Resources::Resources()
		{
		}

		std::shared_ptr<System::Resources::ResourceManager> Resources::getResourceManager()
		{
			if (Object::ReferenceEquals(resourceMan, nullptr))
			{
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
				std::shared_ptr<System::Resources::ResourceManager> temp = std::make_shared<System::Resources::ResourceManager>(L"DeltaShadow.Properties.Resources", typeof(Resources)->Assembly);
				resourceMan = temp;
			}
			return resourceMan;
		}

		std::shared_ptr<System::Globalization::CultureInfo> Resources::getCulture()
		{
			return resourceCulture;
		}

		void Resources::setCulture(const std::shared_ptr<System::Globalization::CultureInfo> &value)
		{
			resourceCulture = value;
		}

		std::vector<std::uint8_t> Resources::get1_1()
		{
			auto obj = getResourceManager()->GetObject(L"_1_1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get1_1Ts()
		{
			auto obj = getResourceManager()->GetObject(L"_1_1_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get1_2()
		{
			auto obj = getResourceManager()->GetObject(L"_1_2", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get1_2Ts()
		{
			auto obj = getResourceManager()->GetObject(L"_1_2_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get1_3()
		{
			auto obj = getResourceManager()->GetObject(L"_1_3", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get1_3Ts()
		{
			auto obj = getResourceManager()->GetObject(L"_1_3_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get2_1()
		{
			auto obj = getResourceManager()->GetObject(L"_2_1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get2_1Ts()
		{
			auto obj = getResourceManager()->GetObject(L"_2_1_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get2_2()
		{
			auto obj = getResourceManager()->GetObject(L"_2_2", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get2_2Ts()
		{
			auto obj = getResourceManager()->GetObject(L"_2_2_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get2_3()
		{
			auto obj = getResourceManager()->GetObject(L"_2_3", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get2_3Ts()
		{
			auto obj = getResourceManager()->GetObject(L"_2_3_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get3_1()
		{
			auto obj = getResourceManager()->GetObject(L"_3_1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get3_1Ts()
		{
			auto obj = getResourceManager()->GetObject(L"_3_1_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get3_2()
		{
			auto obj = getResourceManager()->GetObject(L"_3_2", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get3_2Ts()
		{
			auto obj = getResourceManager()->GetObject(L"_3_2_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get3_3()
		{
			auto obj = getResourceManager()->GetObject(L"_3_3", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get3_3Ts()
		{
			auto obj = getResourceManager()->GetObject(L"_3_3_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get4_1()
		{
			auto obj = getResourceManager()->GetObject(L"_4_1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::get4_1Ts()
		{
			auto obj = getResourceManager()->GetObject(L"_4_1_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getAlienClawClassic()
		{
			auto obj = getResourceManager()->GetObject(L"AlienClawClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getAlienClawNext()
		{
			auto obj = getResourceManager()->GetObject(L"AlienClawNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getAlienPetClassic()
		{
			auto obj = getResourceManager()->GetObject(L"AlienPetClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getAlienPetNext()
		{
			auto obj = getResourceManager()->GetObject(L"AlienPetNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getAlienSlidermanClassic()
		{
			auto obj = getResourceManager()->GetObject(L"AlienSlidermanClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getAlienSlidermanNext()
		{
			auto obj = getResourceManager()->GetObject(L"AlienSlidermanNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getAlienWormClassic()
		{
			auto obj = getResourceManager()->GetObject(L"AlienWormClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getAlienWormNext()
		{
			auto obj = getResourceManager()->GetObject(L"AlienWormNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getBigSpiderClassic()
		{
			auto obj = getResourceManager()->GetObject(L"BigSpiderClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getBigSpiderNext()
		{
			auto obj = getResourceManager()->GetObject(L"BigSpiderNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getBoss()
		{
			auto obj = getResourceManager()->GetObject(L"boss", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getBoss_1()
		{
			auto obj = getResourceManager()->GetObject(L"boss_1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getBoss_2()
		{
			auto obj = getResourceManager()->GetObject(L"boss_2", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getBoss_3()
		{
			auto obj = getResourceManager()->GetObject(L"boss_3", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getBossTs()
		{
			auto obj = getResourceManager()->GetObject(L"boss_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getBugClassic()
		{
			auto obj = getResourceManager()->GetObject(L"BugClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getBugNext()
		{
			auto obj = getResourceManager()->GetObject(L"BugNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClassicBar()
		{
			auto obj = getResourceManager()->GetObject(L"classic_bar", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClassicEscape_1()
		{
			auto obj = getResourceManager()->GetObject(L"classic_escape_1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClassicEscape_2()
		{
			auto obj = getResourceManager()->GetObject(L"classic_escape_2", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClassicEscape_3()
		{
			auto obj = getResourceManager()->GetObject(L"classic_escape_3", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClassicFinalBoss()
		{
			auto obj = getResourceManager()->GetObject(L"classic_final_boss", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClassicFinalcut()
		{
			auto obj = getResourceManager()->GetObject(L"classic_finalcut", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClassicIntro()
		{
			auto obj = getResourceManager()->GetObject(L"classic_intro", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClassicJBar()
		{
			auto obj = getResourceManager()->GetObject(L"classic_j_bar", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClassicJEscape()
		{
			auto obj = getResourceManager()->GetObject(L"classic_j_escape", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClassicMainMenu()
		{
			auto obj = getResourceManager()->GetObject(L"classic_main_menu", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClassicRace()
		{
			auto obj = getResourceManager()->GetObject(L"classic_race", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClassicRaceRoad()
		{
			auto obj = getResourceManager()->GetObject(L"classic_race_road", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClassicRaceTop()
		{
			auto obj = getResourceManager()->GetObject(L"classic_race_top", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClassicSelectLevel()
		{
			auto obj = getResourceManager()->GetObject(L"classic_select_level", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClassicSelectSuit()
		{
			auto obj = getResourceManager()->GetObject(L"classic_select_suit", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClip()
		{
			auto obj = getResourceManager()->GetObject(L"clip", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getClipTs()
		{
			auto obj = getResourceManager()->GetObject(L"clip_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getCrabBossClassic()
		{
			auto obj = getResourceManager()->GetObject(L"CrabBossClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getCrabBossNext()
		{
			auto obj = getResourceManager()->GetObject(L"CrabBossNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getCrakenClassic()
		{
			auto obj = getResourceManager()->GetObject(L"CrakenClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getCrakenNext()
		{
			auto obj = getResourceManager()->GetObject(L"CrakenNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getDLC()
		{
			auto obj = getResourceManager()->GetObject(L"DLC", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getDLCBoss()
		{
			auto obj = getResourceManager()->GetObject(L"DLCBoss", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getDLCBossClassic()
		{
			auto obj = getResourceManager()->GetObject(L"DLCBossClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getDLCBossNext()
		{
			auto obj = getResourceManager()->GetObject(L"DLCBossNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getDLCJacquelineClassic()
		{
			auto obj = getResourceManager()->GetObject(L"DLCJacquelineClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getDLCJacquelineNext()
		{
			auto obj = getResourceManager()->GetObject(L"DLCJacquelineNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getDragon_1()
		{
			auto obj = getResourceManager()->GetObject(L"dragon_1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getDragon_2()
		{
			auto obj = getResourceManager()->GetObject(L"dragon_2", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getDragon_3()
		{
			auto obj = getResourceManager()->GetObject(L"dragon_3", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getDragonflyClassic()
		{
			auto obj = getResourceManager()->GetObject(L"DragonflyClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getDragonflyNext()
		{
			auto obj = getResourceManager()->GetObject(L"DragonflyNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getDronBomberClassic()
		{
			auto obj = getResourceManager()->GetObject(L"DronBomberClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getDronBomberNext()
		{
			auto obj = getResourceManager()->GetObject(L"DronBomberNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getDronClassic()
		{
			auto obj = getResourceManager()->GetObject(L"DronClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getDronNext()
		{
			auto obj = getResourceManager()->GetObject(L"DronNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getEnglish()
		{
			auto obj = getResourceManager()->GetObject(L"English", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFighterBomberClassic()
		{
			auto obj = getResourceManager()->GetObject(L"FighterBomberClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFighterBomberNext()
		{
			auto obj = getResourceManager()->GetObject(L"FighterBomberNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFinalboss()
		{
			auto obj = getResourceManager()->GetObject(L"finalboss", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFinalboss_0()
		{
			auto obj = getResourceManager()->GetObject(L"finalboss_0", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFinalboss_1()
		{
			auto obj = getResourceManager()->GetObject(L"finalboss_1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFinalboss_2()
		{
			auto obj = getResourceManager()->GetObject(L"finalboss_2", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFinalbossTs()
		{
			auto obj = getResourceManager()->GetObject(L"finalboss_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFinalcut()
		{
			auto obj = getResourceManager()->GetObject(L"finalcut", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFinalcutTs()
		{
			auto obj = getResourceManager()->GetObject(L"finalcut_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFlyBossClassic()
		{
			auto obj = getResourceManager()->GetObject(L"FlyBossClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFlyBossNext()
		{
			auto obj = getResourceManager()->GetObject(L"FlyBossNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFont()
		{
			auto obj = getResourceManager()->GetObject(L"font", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFontEnglish()
		{
			auto obj = getResourceManager()->GetObject(L"font_english", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFontPolish()
		{
			auto obj = getResourceManager()->GetObject(L"font_polish", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFontRussian()
		{
			auto obj = getResourceManager()->GetObject(L"font_russian", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getFontSpanish()
		{
			auto obj = getResourceManager()->GetObject(L"font_spanish", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getGameOver()
		{
			auto obj = getResourceManager()->GetObject(L"game_over", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getGameOverTs()
		{
			auto obj = getResourceManager()->GetObject(L"game_over_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getGunClassic()
		{
			auto obj = getResourceManager()->GetObject(L"GunClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getGunNext()
		{
			auto obj = getResourceManager()->GetObject(L"GunNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::shared_ptr<System::Drawing::Icon> Resources::getIco32()
		{
			auto obj = getResourceManager()->GetObject(L"ico32", resourceCulture);
			return (std::static_pointer_cast<System::Drawing::Icon>(obj));
		}

		std::shared_ptr<System::Drawing::Icon> Resources::getIco64()
		{
			auto obj = getResourceManager()->GetObject(L"ico64", resourceCulture);
			return (std::static_pointer_cast<System::Drawing::Icon>(obj));
		}

		std::vector<std::uint8_t> Resources::getIntro()
		{
			auto obj = getResourceManager()->GetObject(L"intro", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getIntroTs()
		{
			auto obj = getResourceManager()->GetObject(L"intro_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getItemsClassic()
		{
			auto obj = getResourceManager()->GetObject(L"ItemsClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getItemsNext()
		{
			auto obj = getResourceManager()->GetObject(L"ItemsNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getJacqueline()
		{
			auto obj = getResourceManager()->GetObject(L"Jacqueline", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getJacquelineClassic()
		{
			auto obj = getResourceManager()->GetObject(L"JacquelineClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getJacquelineNext()
		{
			auto obj = getResourceManager()->GetObject(L"JacquelineNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getJellyClassic()
		{
			auto obj = getResourceManager()->GetObject(L"JellyClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getJellyNext()
		{
			auto obj = getResourceManager()->GetObject(L"JellyNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_1_1()
		{
			auto obj = getResourceManager()->GetObject(L"level_1_1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_1_2()
		{
			auto obj = getResourceManager()->GetObject(L"level_1_2", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_1_3()
		{
			auto obj = getResourceManager()->GetObject(L"level_1_3", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_1_4()
		{
			auto obj = getResourceManager()->GetObject(L"level_1_4", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_2_1()
		{
			auto obj = getResourceManager()->GetObject(L"level_2_1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_2_2()
		{
			auto obj = getResourceManager()->GetObject(L"level_2_2", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_2_3()
		{
			auto obj = getResourceManager()->GetObject(L"level_2_3", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_2_4()
		{
			auto obj = getResourceManager()->GetObject(L"level_2_4", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_3_1()
		{
			auto obj = getResourceManager()->GetObject(L"level_3_1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_3_2()
		{
			auto obj = getResourceManager()->GetObject(L"level_3_2", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_3_3()
		{
			auto obj = getResourceManager()->GetObject(L"level_3_3", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_3_4()
		{
			auto obj = getResourceManager()->GetObject(L"level_3_4", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_4_1()
		{
			auto obj = getResourceManager()->GetObject(L"level_4_1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_4_2()
		{
			auto obj = getResourceManager()->GetObject(L"level_4_2", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_4_3()
		{
			auto obj = getResourceManager()->GetObject(L"level_4_3", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_4_4()
		{
			auto obj = getResourceManager()->GetObject(L"level_4_4", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_4_5()
		{
			auto obj = getResourceManager()->GetObject(L"level_4_5", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_4_6()
		{
			auto obj = getResourceManager()->GetObject(L"level_4_6", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_4_7()
		{
			auto obj = getResourceManager()->GetObject(L"level_4_7", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getLevel_4_8()
		{
			auto obj = getResourceManager()->GetObject(L"level_4_8", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getMegabrainClassic()
		{
			auto obj = getResourceManager()->GetObject(L"MegabrainClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getMegabrainNext()
		{
			auto obj = getResourceManager()->GetObject(L"MegabrainNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getMenu()
		{
			auto obj = getResourceManager()->GetObject(L"menu", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getMenuTs()
		{
			auto obj = getResourceManager()->GetObject(L"menu_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::shared_ptr<System::Drawing::Bitmap> Resources::getMetall()
		{
			auto obj = getResourceManager()->GetObject(L"metall", resourceCulture);
			return (std::static_pointer_cast<System::Drawing::Bitmap>(obj));
		}

		std::vector<std::uint8_t> Resources::getMothClassic()
		{
			auto obj = getResourceManager()->GetObject(L"MothClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getMothNext()
		{
			auto obj = getResourceManager()->GetObject(L"MothNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getMotorbike()
		{
			auto obj = getResourceManager()->GetObject(L"motorbike", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getMotorbikeTs()
		{
			auto obj = getResourceManager()->GetObject(L"motorbike_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextBar()
		{
			auto obj = getResourceManager()->GetObject(L"next_bar", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextEscape_1()
		{
			auto obj = getResourceManager()->GetObject(L"next_escape_1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextEscape_2()
		{
			auto obj = getResourceManager()->GetObject(L"next_escape_2", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextEscape_3()
		{
			auto obj = getResourceManager()->GetObject(L"next_escape_3", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextFinalBoss()
		{
			auto obj = getResourceManager()->GetObject(L"next_final_boss", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextFinalcut()
		{
			auto obj = getResourceManager()->GetObject(L"next_finalcut", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextIntro()
		{
			auto obj = getResourceManager()->GetObject(L"next_intro", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextJBar()
		{
			auto obj = getResourceManager()->GetObject(L"next_j_bar", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextJEscape()
		{
			auto obj = getResourceManager()->GetObject(L"next_j_escape", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextMainMenu()
		{
			auto obj = getResourceManager()->GetObject(L"next_main_menu", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextRace()
		{
			auto obj = getResourceManager()->GetObject(L"next_race", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextRaceRoad()
		{
			auto obj = getResourceManager()->GetObject(L"next_race_road", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextRaceTop()
		{
			auto obj = getResourceManager()->GetObject(L"next_race_top", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextSelectLevel()
		{
			auto obj = getResourceManager()->GetObject(L"next_select_level", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextSelectSuit()
		{
			auto obj = getResourceManager()->GetObject(L"next_select_suit", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNextPalette()
		{
			auto obj = getResourceManager()->GetObject(L"NextPalette", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNovaClassic()
		{
			auto obj = getResourceManager()->GetObject(L"NovaClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getNovaNext()
		{
			auto obj = getResourceManager()->GetObject(L"NovaNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getPiranhaClassic()
		{
			auto obj = getResourceManager()->GetObject(L"PiranhaClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getPiranhaNext()
		{
			auto obj = getResourceManager()->GetObject(L"PiranhaNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::shared_ptr<System::Drawing::Bitmap> Resources::getPlatformerModeFont()
		{
			auto obj = getResourceManager()->GetObject(L"platformer_mode_font", resourceCulture);
			return (std::static_pointer_cast<System::Drawing::Bitmap>(obj));
		}

		std::vector<std::uint8_t> Resources::getPlatformerModeFont1()
		{
			auto obj = getResourceManager()->GetObject(L"platformer_mode_font1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getPolish()
		{
			auto obj = getResourceManager()->GetObject(L"Polish", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getRace()
		{
			auto obj = getResourceManager()->GetObject(L"race", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getRaceTs()
		{
			auto obj = getResourceManager()->GetObject(L"race_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getRaceClassic()
		{
			auto obj = getResourceManager()->GetObject(L"RaceClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getRaceNext()
		{
			auto obj = getResourceManager()->GetObject(L"RaceNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getRocketmanClassic()
		{
			auto obj = getResourceManager()->GetObject(L"RocketmanClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getRocketmanNext()
		{
			auto obj = getResourceManager()->GetObject(L"RocketmanNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getRussian()
		{
			auto obj = getResourceManager()->GetObject(L"Russian", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSecretBoss()
		{
			auto obj = getResourceManager()->GetObject(L"Secret_boss", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSecretBossTs()
		{
			auto obj = getResourceManager()->GetObject(L"Secret_boss_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxBeetle()
		{
			return getResourceManager()->GetStream(L"sfx_beetle", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxBumerang()
		{
			return getResourceManager()->GetStream(L"sfx_bumerang", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxDamage()
		{
			return getResourceManager()->GetStream(L"sfx_damage", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxDogscream()
		{
			return getResourceManager()->GetStream(L"sfx_dogscream", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxDooropen()
		{
			return getResourceManager()->GetStream(L"sfx_dooropen", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxDoors()
		{
			return getResourceManager()->GetStream(L"sfx_doors", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxDroid()
		{
			return getResourceManager()->GetStream(L"sfx_droid", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxElevator()
		{
			return getResourceManager()->GetStream(L"sfx_elevator", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxExplosion()
		{
			return getResourceManager()->GetStream(L"sfx_explosion", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxGotonthewall()
		{
			return getResourceManager()->GetStream(L"sfx_gotonthewall", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxLowpower()
		{
			return getResourceManager()->GetStream(L"sfx_lowpower", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxMissshoot()
		{
			return getResourceManager()->GetStream(L"sfx_missshoot", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxPowerup()
		{
			return getResourceManager()->GetStream(L"sfx_powerup", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxRaceBlockHit()
		{
			return getResourceManager()->GetStream(L"sfx_race_block_hit", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxRaceDown()
		{
			return getResourceManager()->GetStream(L"sfx_race_down", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxRaceJump()
		{
			return getResourceManager()->GetStream(L"sfx_race_jump", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxRaceWallHit()
		{
			return getResourceManager()->GetStream(L"sfx_race_wall_hit", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxRocket()
		{
			return getResourceManager()->GetStream(L"sfx_rocket", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxShocker()
		{
			return getResourceManager()->GetStream(L"sfx_shocker", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxSlide()
		{
			return getResourceManager()->GetStream(L"sfx_slide", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxSlime()
		{
			return getResourceManager()->GetStream(L"sfx_slime", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxStar()
		{
			return getResourceManager()->GetStream(L"sfx_star", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxStart()
		{
			return getResourceManager()->GetStream(L"sfx_start", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxStealth()
		{
			return getResourceManager()->GetStream(L"sfx_stealth", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxSteam()
		{
			return getResourceManager()->GetStream(L"sfx_steam", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxStungun()
		{
			return getResourceManager()->GetStream(L"sfx_stungun", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxSwitch()
		{
			return getResourceManager()->GetStream(L"sfx_switch", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxTanketteborn()
		{
			return getResourceManager()->GetStream(L"sfx_tanketteborn", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxTanketteshoot()
		{
			return getResourceManager()->GetStream(L"sfx_tanketteshoot", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxTerminal()
		{
			return getResourceManager()->GetStream(L"sfx_terminal", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxType()
		{
			return getResourceManager()->GetStream(L"sfx_type", resourceCulture);
		}

		std::shared_ptr<System::IO::UnmanagedMemoryStream> Resources::getSfxWave()
		{
			return getResourceManager()->GetStream(L"sfx_wave", resourceCulture);
		}

		std::vector<std::uint8_t> Resources::getSlimeClassic()
		{
			auto obj = getResourceManager()->GetObject(L"SlimeClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSlimeNext()
		{
			auto obj = getResourceManager()->GetObject(L"SlimeNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSonusVenatorClassic()
		{
			auto obj = getResourceManager()->GetObject(L"SonusVenatorClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSonusVenatorNext()
		{
			auto obj = getResourceManager()->GetObject(L"SonusVenatorNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSpanish()
		{
			auto obj = getResourceManager()->GetObject(L"Spanish", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSpiderClassic()
		{
			auto obj = getResourceManager()->GetObject(L"SpiderClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSpiderNext()
		{
			auto obj = getResourceManager()->GetObject(L"SpiderNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getStealth_1()
		{
			auto obj = getResourceManager()->GetObject(L"stealth_1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getStealth_1Ts()
		{
			auto obj = getResourceManager()->GetObject(L"stealth_1_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getStealth_2()
		{
			auto obj = getResourceManager()->GetObject(L"stealth_2", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getStealth_2Ts()
		{
			auto obj = getResourceManager()->GetObject(L"stealth_2_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getStealth_3()
		{
			auto obj = getResourceManager()->GetObject(L"stealth_3", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getStealth_3Ts()
		{
			auto obj = getResourceManager()->GetObject(L"stealth_3_ts", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSubboss_1()
		{
			auto obj = getResourceManager()->GetObject(L"subboss_1", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSubboss_2()
		{
			auto obj = getResourceManager()->GetObject(L"subboss_2", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSubboss_3()
		{
			auto obj = getResourceManager()->GetObject(L"subboss_3", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSubboss_4()
		{
			auto obj = getResourceManager()->GetObject(L"subboss_4", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSubboss_5()
		{
			auto obj = getResourceManager()->GetObject(L"subboss_5", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSubboss_6()
		{
			auto obj = getResourceManager()->GetObject(L"subboss_6", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSuitClassic()
		{
			auto obj = getResourceManager()->GetObject(L"SuitClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSuitNext()
		{
			auto obj = getResourceManager()->GetObject(L"SuitNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getSystem()
		{
			auto obj = getResourceManager()->GetObject(L"system", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getTanketteClassic()
		{
			auto obj = getResourceManager()->GetObject(L"TanketteClassic", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}

		std::vector<std::uint8_t> Resources::getTanketteNext()
		{
			auto obj = getResourceManager()->GetObject(L"TanketteNext", resourceCulture);
			return (static_cast<std::vector<std::uint8_t>>(obj));
		}
	}
}
