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

	/// <summary>�I�[�o�[�t���[���Ȃ����Z</summary>
	/// <param name="c1">���Z����F</param>
	/// <returns>���Z��̐F</returns>
	Color Add_s(const Color& c1)const;

	/// <summary>unsigned int�^�ŐF���擾</summary>
	unsigned int Get();
};
