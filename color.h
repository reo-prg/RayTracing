#pragma once

struct Color
{
	Color() = default;
	~Color() = default;
	unsigned char r;
	unsigned char g;
	unsigned char b;

	Color operator+(const Color& c);

	Color operator*(float val);

	Color operator*(const Color& c1);

	/// <summary>オーバーフローしない加算</summary>
	/// <param name="c1">加算する色</param>
	/// <returns>加算後の色</returns>
	Color Add_s(const Color& c1)const;

	/// <summary>unsigned int型で色を取得</summary>
	unsigned int Get();
};
