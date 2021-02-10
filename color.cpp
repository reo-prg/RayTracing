#include "color.h"
#include <algorithm>

Color Color::operator+(const Color& c)
{
	Color ret;
	ret.r += c.r;
	ret.g += c.g;
	ret.b += c.b;
	return ret;
}

Color Color::operator*(float val)
{
	Color ret;
	ret.r = std::clamp(static_cast<int>(r * val), 0, 0xff);
	ret.g = std::clamp(static_cast<int>(g * val), 0, 0xff);
	ret.b = std::clamp(static_cast<int>(b * val), 0, 0xff);
	return ret;
}

Color Color::operator*(const Color& c1)
{
	return Color{
	static_cast<unsigned char>(std::clamp(static_cast<int>(static_cast<float>(r) * (static_cast<float>(c1.r) / 255.0f)), 0, 0xff)),
	static_cast<unsigned char>(std::clamp(static_cast<int>(static_cast<float>(g) * (static_cast<float>(c1.g) / 255.0f)), 0, 0xff)),
	static_cast<unsigned char>(std::clamp(static_cast<int>(static_cast<float>(b) * (static_cast<float>(c1.b) / 255.0f)), 0, 0xff))
	};
}

Color Color::Add_s(const Color& c1) const
{
	Color c;
	c.r = std::clamp(r + c1.r, 0, 0xff);
	c.g = std::clamp(g + c1.g, 0, 0xff);
	c.b = std::clamp(b + c1.b, 0, 0xff);

	return c;
}

unsigned int Color::Get()
{
	return (r << 16) + (g << 8) + b;
}
