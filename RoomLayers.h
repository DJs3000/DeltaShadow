#pragma once

#include <string>
#include <vector>
#include <memory>

namespace DeltaShadow
{
	class RoomLayers : public std::enable_shared_from_this<RoomLayers>
	{
		//класс тайла в слое
	public:
		class LayerTile : public std::enable_shared_from_this<LayerTile>
		{
		public:
			std::uint8_t X = 0, Y = 0; //координаты тайла
			std::uint8_t Tile = 0; //значение тайла
		};

	public:
      std::string Name;
		std::vector<std::shared_ptr<LayerTile>> LayerTiles = std::vector<std::shared_ptr<LayerTile>>();

	};
}
