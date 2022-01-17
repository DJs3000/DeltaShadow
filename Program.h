#pragma once

#include <memory>

using namespace SdlDotNet::Core;
using namespace SdlDotNet::Graphics;
using namespace SdlDotNet::Graphics::Sprites;
using namespace SdlDotNet::Audio;
using namespace SdlDotNet::Input;
using namespace Tao::Sdl;
using namespace SharpDX::XInput;

namespace DeltaShadow
{
	class joy_button : public std::enable_shared_from_this<joy_button>
	{
	public:
		bool isAxis = false;
		std::int32_t AxisNum = 0;
		float AxisDirection = 0;
		bool isButton = false;
		std::int32_t ButtonNum = 0;
	};

}
