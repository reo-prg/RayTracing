#include "ObjectManager.h"
#include "Object.h"
#include "../color.h"
#include <cmath>

namespace
{
	Color Lerp(const Color& col1, const Color& col2, float t)
	{
		return Color{ static_cast<unsigned char>(static_cast<float>(col1.r) + static_cast<float>((short)col2.r - (short)col1.r) * t),
		static_cast<unsigned char>(static_cast<float>(col1.g) + static_cast<float>((short)col2.g - (short)col1.g) * t),
		static_cast<unsigned char>(static_cast<float>(col1.b) + static_cast<float>((short)col2.b - (short)col1.b) * t), };
	}
}

ObjectManager::ObjectManager()
{
	std::random_device dev;
	mt_ = std::mt19937(dev());
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Register(Object* object)
{
	objects_.emplace_back(object);
}

void ObjectManager::SetLight(const Vector3& light)
{
	light_ = light;
}

Color ObjectManager::StartRayTrace(const Position3& eye, const Vector3& ray, unsigned char count)
{
	try_ = count;
	return 	RayTracing(eye, ray, nullptr, try_);
}

void ObjectManager::SwitchAO(void)
{
	aoActive_ = (!aoActive_);
}

Color ObjectManager::RayTracing(const Position3& eye, const Vector3& ray, Object* except, unsigned char count)
{
	Color col;
	float distance = NAN, shadowDist = NAN;
	Object* target = nullptr;

	for (int i = 0; i < objects_.size(); i++)
	{
		if (objects_[i] == except) { continue; }
		float d = objects_[i]->isHit(eye, ray);
		if (std::isnan(d)) { continue; }
		if (std::isnan(distance))
		{
			target = objects_[i];
			distance = d;
		}
		else
		{
			if (distance > d && d >= 0.0f) 
			{ 
				target = objects_[i];
				distance = d; 
			}
		}
	}

	if (target == nullptr)
	{
		return sky_;
	}
	col = target->GetColor(eye + ray * distance, ray, light_, ambient_);

	// ‰e---------------------------------------------------------------------
	for (int i = 0; i < objects_.size(); i++)
	{
		if (objects_[i] == target) { continue; }
		float d = objects_[i]->isHit(eye + ray * distance, light_ * -1.0f);
		if (std::isnan(d)) { continue; }
		shadowDist = d;
		break;
	}
	Vector3 p = eye + ray * distance;
	if (count != 0)
	{
		Color ref = RayTracing(p, target->GetNormal(p), target, count - 1);
		col = Lerp(col, ref, target->material_.reflect_);
	}
	if (!std::isnan(shadowDist))
	{
		col = col * shadowBright_;
	}
	if (aoActive_)
	{
		// AO
		Vector3 rd;
		Vector3 normal = target->GetNormal(p);
		float ao = 0.0f, dv = 0.0f, str, rad = 30.0f;
		std::uniform_real_distribution<float> rnd(-1.0f, 1.0f);

#pragma omp parallel for reduction(+:ao) reduction(+:dv)
		for (int i = 0; i < 64; i++)
		{
			rd.x = rnd(mt_);
			rd.y = rnd(mt_);
			rd.z = rnd(mt_);
			rd.Normalize();
			str = Dot(normal, rd);
			if (str < 0.0f) { rd *= -1.0f; }
			str = abs(str);
			dv += str;
			float aod = rad;
			for (int i = 0; i < objects_.size(); i++)
			{
				if (objects_[i] == target) { continue; }
				float d = objects_[i]->isHit(p, rd);
				if (std::isnan(d)) { continue; }
				if (d < aod)
				{
					aod = d;
				}
				break;
			}

			if (aod < rad)
			{
				ao += str;
			}
		}
		ao = ao / dv;
		ao = 1.0f - ao;

		col = col * ao;
	}
	return col;
}
