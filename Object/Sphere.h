#pragma once
#include "Object.h"

class Sphere :
    public Object
{
public:
    Sphere();
    Sphere(float radius = 1.0f, const Vector3& coordinate = { 0.0f, 0.0f, 0.0f });
    Sphere(float radius = 1.0f, float coord_x = 0.0f, float coord_y = 0.0f, float coord_z = 0.0f);
    ~Sphere();

    float isHit(const Vector3& eye, const Vector3& ray)override;
    Color GetColor(const Vector3& pos, const Vector3& ray, const Vector3& light, const Color& ambient)override;
    Vector3 GetNormal(const Vector3& pos);
    Vector3 coord_;
    float radius_;
private:
    Color Diffuse(const Vector3& pos, const Vector3& light);
    Color Speculer(const Vector3& pos, const Vector3& ray, const Vector3& light);

    static constexpr float strength_ = 0.8f;
    static constexpr float sharpness_ = 20.0f;
};

