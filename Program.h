#ifndef PROGRAM_H
#define PROGRAM_H

#include <memory>

namespace DeltaShadow
{
	class joy_button : public std::enable_shared_from_this<joy_button>
	{
	public:
		bool isAxis = false;
		int32_t AxisNum = 0;
		float AxisDirection = 0;
		bool isButton = false;
		int32_t ButtonNum = 0;
	};

}

#endif
