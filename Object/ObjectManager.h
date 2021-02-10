#pragma once
#include <memory>
#include <vector>
#include <random>
#include "../color.h"
#include "../Mymath/Geometry.h"

class Object;
class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();

	void Register(Object* object);
	void SetLight(const Vector3& light);
	Color StartRayTrace(const Position3& eye, const Vector3& ray, unsigned char count);

	void SwitchAO(void);
	bool aoActive_ = false;
private:
	Color RayTracing(const Position3& eye, const Vector3& ray, Object* except, unsigned char count = 5);
	std::vector<Object*> objects_;

	static constexpr Color sky_ = { 0xab, 0xe7, 0xff };
	static constexpr Color ambient_ = { 0x20, 0x20, 0x20 };
	static constexpr float shadowBright_ = 0.3f;
	Vector3 light_;
	unsigned char try_;

	std::mt19937 mt_;
};

