#include "Object.h"
#include <DxLib.h>

Object::Object()
{
}

Object::~Object()
{
}

void Object::SetMaterial(const Color& col, float reflect)
{
	material_.type_ = MaterialType::simpleColor;
	material_.color_ = col;
	material_.reflect_ = reflect;
}

void Object::SetMaterial(const wchar_t* texpath, float reflect)
{
	material_.type_ = MaterialType::texture;
	material_.texture_ = LoadSoftImage(texpath);
	material_.reflect_ = reflect;
}
