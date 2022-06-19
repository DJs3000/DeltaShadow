namespace DeltaShadow
{

	ObjectData::ObjectData(const std::wstring &name, std::uint8_t x1, std::uint8_t y1, std::uint8_t x2, std::uint8_t y2, std::uint8_t xcord, std::uint8_t ycord, bool direction, std::uint8_t pause, std::uint8_t value)
	{
		Name = name;
		X1 = x1;
		Y1 = y1;
		X2 = x2;
		Y2 = y2;
		XCord = xcord;
		YCord = ycord;
		Direction = direction;
		Pause = pause;
		Value = value;
	}
}
