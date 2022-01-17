#pragma once

#include <memory>

namespace DeltaShadow
{
	class AnimTile : public std::enable_shared_from_this<AnimTile>
	{
	public:
		std::int32_t num = 0;
		std::int32_t x = 0;
		std::int32_t y = 0;
	};
}
