#include "Plane.h"
#include <cmath>
#include <DxLib.h>

Plane::Plane():normal_(0.0f, 1.0f, 0.0f), offset_(0.0f)
{

}

Plane::Plane(const Vector3& normal, float offset)
	:normal_(normal.Normalized()), offset_(offset)
{

}

Plane::Plane(float normal_x, float normal_y, float normal_z, float offset)
	:normal_(normal_x, normal_y, normal_z), offset_(offset)
{
	normal_.Normalize();
}

Plane::~Plane()
{

}

float Plane::isHit(const Vector3& eye, const Vector3& ray)
{
	float t;
	t = (offset_ - Dot(eye, normal_)) / Dot(ray, normal_);
	if (t <= 0.0f || t >= 3000.0f)
	{
		t = NAN;
	}
	return t;
}

Color Plane::GetColor(const Vector3& pos, const Vector3& ray, const Vector3& light, const Color& ambient)
{
	switch (material_.type_)
	{
	case MaterialType::simpleColor:
		if ((static_cast<int>(std::sqrtf(pos.x * pos.x + pos.z * pos.z)) / 20) % 2 == 0)
		{
			return material_.color_;
		}
		else
		{
			return Color{ 0xff, 0xff, 0xff };
		}
		break;
	case MaterialType::texture:
		Vector2 base, plane_xy, plane_zy;
		base = Vector2(0.0f, 1.0f).Normalized();
		plane_xy = Vector2(normal_.x, normal_.y).Normalized();
		plane_zy = Vector2(normal_.z, normal_.y).Normalized();

		float angle_x = Dot(base, plane_xy);
		float angle_z = Dot(base, plane_zy);
		Vector3 p;

		p.x = pos.x * angle_x;
		p.z = pos.z * angle_z;

		Color col = {};
		int r, g, b, a;
		int size_x, size_y;
		GetSoftImageSize(material_.texture_, &size_x, &size_y);
		GetPixelSoftImage(material_.texture_, pos.x < 0 ? (size_x - 1) - (static_cast<int>(abs(pos.x)) % size_x) : static_cast<int>(pos.x) % size_x,
			pos.z < 0 ? (size_y - 1) - (static_cast<int>(abs(pos.z)) % size_y) : static_cast<int>(pos.z) % size_y,
			&r, &g, &b, &a);
		col.r = r;
		col.g = g;
		col.b = b;
		return col;
		break;
	}
}

Vector3 Plane::GetNormal(const Vector3& pos)
{
	return normal_;
}
