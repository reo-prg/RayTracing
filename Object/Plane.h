#pragma once
#include "Object.h"

class Plane :
    public Object
{
public:
    Plane();
    Plane(const Vector3& normal = { 0.0f, 1.0f, 0.0f }, float offset = 0.0f);
    Plane(float normal_x = 0.0f, float normal_y = 1.0f, float normal_z = 0.0f, float offset = 0.0f);
    ~Plane();

    float isHit(const Vector3& eye, const Vector3& ray)override;
    Color GetColor(const Vector3& pos, const Vector3& ray, const Vector3& light, const Color& ambient)override;
    Vector3 GetNormal(const Vector3& pos);
private:
    Vector3 normal_;
    float offset_;
};

