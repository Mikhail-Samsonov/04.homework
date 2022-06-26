#ifndef EDITOR_COLOR_H
#define EDITOR_COLOR_H

enum class Color
{
	red, green, blue, yellow, black, white
};

std::ostream& operator<<(std::ostream& os, Color color)
{
	switch (color)
	{
	case Color::red:
		os << "red";
		break;
	case Color::green:
		os << "green";
		break;
	case Color::blue:
		os << "blue";
		break;
	case Color::yellow:
		os << "yellow";
		break;
	case Color::black:
		os << "black";
		break;
	case Color::white:
		os << "white";
		break;
	default:
		os << "Unknown";
		break;
	}
	return os;
}


#endif //EDITOR_COLOR_H
