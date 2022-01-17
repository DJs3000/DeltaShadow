#pragma once

#include <string>
#include <memory>

namespace DeltaShadow
{
	//класс инициализаторов объектов
	class ObjectData : public std::enable_shared_from_this<ObjectData>
	{
	public:
		std::wstring Name; //имя объекта
		std::uint8_t X1 = 0; //X1 триггера
		std::uint8_t Y1 = 0; //Y1 триггера
		std::uint8_t X2 = 0; //X2 триггера
		std::uint8_t Y2 = 0; //Y2 триггера
		std::uint8_t XCord = 0, YCord = 0; //координаты объекта
		bool Direction = false; //направление объекта
		std::uint8_t Pause = 0; //пауза перед инициализацией
		std::uint8_t Value = 0; //имеет разные функции для разных объектов

		ObjectData(const std::wstring &name, std::uint8_t x1, std::uint8_t y1, std::uint8_t x2, std::uint8_t y2, std::uint8_t xcord, std::uint8_t ycord, bool direction, std::uint8_t pause, std::uint8_t value);
	};
}
