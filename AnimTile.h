#pragma once

#include <memory>

namespace DeltaShadow
{
	class AnimTile : public std::enable_shared_from_this<AnimTile>
	{
	public:
		int32_t num = 0;
		int32_t x = 0;
		int32_t y = 0;
      int32_t property = 0;
	};
}
