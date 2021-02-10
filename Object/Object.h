#pragma once
#include "../Mymath/Geometry.h"
#include "../color.h"

enum class MaterialType
{
	simpleColor,
	texture
};

struct Material
{
	float reflect_;
	Color color_;
	int texture_;
	MaterialType type_;
}; 

class Object
{
public:
	Object();
	virtual ~Object();

	void SetMaterial(const Color& col, float reflect);
	void SetMaterial(const wchar_t* texpath, float reflect);
	virtual float isHit(const Vector3& eye, const Vector3& ray) = 0;

	virtual Color GetColor(const Vector3& pos, const Vector3& ray, const Vector3& light, const Color& ambient) = 0;
	virtual Vector3 GetNormal(const Vector3& pos) = 0;
	Material material_;
};
