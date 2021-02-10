#include "Sphere.h"
#include <cmath>
#include <algorithm>
#include "../Mymath/mathUtility.h"

using namespace math_util;

Sphere::Sphere():radius_(1.0f), coord_(0.0f, 0.0f, 0.0f)
{

}

Sphere::Sphere(float radius, const Vector3& coordinate)
	:radius_(radius), coord_(coordinate)
{

}

Sphere::Sphere(float radius, float coord_x, float coord_y, float coord_z)
	: radius_(radius), coord_(coord_x, coord_y, coord_z)
{

}

Sphere::~Sphere()
{

}

float Sphere::isHit(const Vector3& eye, const Vector3& ray)
{
	float a, b, c, d;
	a = Double(ray.x) + Double(ray.y) + Double(ray.z);
	b = (eye.x - coord_.x) * ray.x + (eye.y - coord_.y) * ray.y + (eye.z - coord_.z) * ray.z;
	c = Double(eye.x - coord_.x) + Double(eye.y - coord_.y) + Double(eye.z - coord_.z) - Double(radius_);

	d = b * b - a * c;
	if (d < 0)
	{
		return NAN;
	}
	float t;

	t = (-1.0f * b - std::sqrt(d)) / a;

	if (t < 0.0f || t >= 20000)
	{
		return NAN;
	}
	return t;
}

Color Sphere::GetColor(const Vector3& pos, const Vector3& ray, const Vector3& light, const Color& ambient)
{
	Color dif, spec;
	dif = Diffuse(pos, light);
	spec = Speculer(pos, ray.Normalized(), light);
	return dif.Add_s(spec.Add_s(ambient));
}

Vector3 Sphere::GetNormal(const Vector3& pos)
{
	return (pos - coord_).Normalized();
}

Color Sphere::Diffuse(const Vector3& pos, const Vector3& light)
{
	Vector3 norm = pos - coord_;
	norm.Normalize();
	float bright = Dot(norm, light * -1.0f);
	bright = std::clamp(bright, 0.0f, 1.0f);

	return material_.color_ * bright;
}

Color Sphere::Speculer(const Vector3& pos, const Vector3& ray, const Vector3& light)
{
	Vector3 norm = pos - coord_;
	norm.Normalize();
	Vector3 Reflect = (norm * 2.0f) * Dot(norm, light * -1.0f) + light;
	Reflect.Normalize();

	unsigned char bright = std::clamp(static_cast<unsigned short>(std::powf(std::clamp(Dot(ray * -1.0f, Reflect), 
		0.0f, 1.0f), sharpness_) * 255.0f * strength_), (unsigned short)0, (unsigned short)0xff);

	return Color{ bright, bright, bright };
}
