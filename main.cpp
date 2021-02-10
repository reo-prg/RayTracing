#include <dxlib.h>
#include "Mymath/Geometry.h"
#include "Mymath/mathUtility.h"
#include <type_traits>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <string>
#include "color.h"

#include "Object/ObjectManager.h"
#include "Object/Plane.h"
#include "Object/Sphere.h"

int floorImage;
bool check = false;
bool space = false;
float reflectivity = 1.0f;

using namespace math_util;

namespace
{
	const int screen_width = 640;
	const int screen_height = 480;

	Position3 sunLight;
	Color ambient_def = { 0x20, 0x20, 0x20 };
	Color sphere_color = { 0xff, 0xff, 0xaa };
	Color sky_color = { 0x22, 0x22, 0xff };

	Color result[screen_height][screen_width];
}

void RayTracing2(ObjectManager& mng, const Position3& eye)
{
#pragma omp parallel for
	for (int y = 0; y < screen_height; y++)
	{
#pragma omp parallel for
		for (int x = 0; x < screen_width; x++)
		{
			Position3 tmp, screen, ray;
			screen = { static_cast<float>(x) - screen_width / 2.0f, static_cast<float>(y) - screen_height / 2.0f, 0.0f };
			ray = screen - eye;

			result[y][x] = mng.StartRayTrace(eye, ray, 5);
		}
	}

	for (int y = 0; y < screen_height; y++)
	{
		for (int x = 0; x < screen_width; x++)
		{
			DrawPixel(x, y, result[y][x].Get());
		}
	}
}

int WINAPI WinMain(HINSTANCE , HINSTANCE,LPSTR,int ) {
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(true);
	SetGraphMode(screen_width, screen_height, 32);
	SetMainWindowText(_T("1916037_パリィ勇行メサイアス"));
	DxLib_Init();

	floorImage = LoadSoftImage(L"Resource/tex.png");

	bool keyo = false;

	sunLight = { 1.0f, 1.0f, -1.0f};
	sunLight.Normalize();
	ObjectManager objManager_;

	objManager_.SetLight(sunLight);

	Sphere* sp1 = new Sphere(100.0f, 0.0f, 0.0f, -200.0f);
	sp1->SetMaterial(Color{ 0xff, 0xff, 0x00 }, 0.25f);
	Sphere* sp2 = new Sphere(150.0f, 300.0f, 30.0f, -300.0f);
	sp2->SetMaterial(Color{ 0xff, 0x00, 0xff }, 0.3f);
	Sphere* sp3 = new Sphere(200.0f, -280.0f, 0.0f, -250.0f);
	sp3->SetMaterial(Color{ 0x00, 0xff, 0xff }, 0.8f);
	Sphere* sp4 = new Sphere(300.0f, -480.0f, -350.0f, -750.0f);
	sp4->SetMaterial(Color{ 0xa3, 0x2d, 0x33 }, 0.2f);
	Sphere* sp5 = new Sphere(150.0f, 480.0f, -250.0f, -450.0f);
	sp5->SetMaterial(Color{ 0x30, 0xff, 0x00 }, 0.6f);
	Sphere* sp6 = new Sphere(50.0f, 50.0f, 50.0f, -100.0f);
	sp6->SetMaterial(Color{ 0xff, 0x00, 0x00 }, 0.4f);
	Sphere* sp7 = new Sphere(300.0f, 200.0f, -380.0f, -850.0f);
	sp7->SetMaterial(Color{ 0x00, 0xff, 0xff }, 0.3f);

	Plane* pl1 = new Plane(0.0f, 1.0f, 0.0f, 150.0f);
	pl1->SetMaterial(Color{ 0x40, 0xff, 0x40 }, 0.0f);

	objManager_.Register(sp1);
	objManager_.Register(sp2);
	objManager_.Register(sp3);
	objManager_.Register(sp4);
	objManager_.Register(sp5);
	objManager_.Register(sp6);
	objManager_.Register(sp7);
	objManager_.Register(pl1);

	while (!CheckHitKey(KEY_INPUT_ESCAPE) && DxLib::ProcessMessage() == 0)
	{
		ClsDrawScreen();
		RayTracing2(objManager_, Vector3(0, -100, 300));
		//DrawString(10, 50, (L"fps : " + std::to_wstring(GetFPS())).c_str(), 0xff0000);
		DrawString(10, 10, L"WASDキーでXZ移動", 0xff0000);
		DrawString(10, 30, L"SPACEで上昇、左SHIFTで下降", 0xff0000);
		DrawString(10, 70, L"Oキー(英語の)でAO ※めっちゃ重くなります", 0xff0000);
		DrawString(10, 90, L"下の表記が変わるまで長押ししてください", 0xff0000);
		if (objManager_.aoActive_)
		{
			DrawString(9, 109, L"AO : ACTIVE", 0x000000);
			DrawString(10, 110, L"AO : ACTIVE", 0x00ff00);
		}
		else
		{
			DrawString(10, 110, L"AO : NOT ACTIVE", 0xff0000);
		}

		if (CheckHitKey(KEY_INPUT_W))
		{
			sp1->coord_.z -= 5.0f;
		}
		if (CheckHitKey(KEY_INPUT_S))
		{
			sp1->coord_.z += 5.0f;
		}
		if (CheckHitKey(KEY_INPUT_A))
		{
			sp1->coord_.x -= 5.0f;
		}
		if (CheckHitKey(KEY_INPUT_D))
		{
			sp1->coord_.x += 5.0f;
		}
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			sp1->coord_.y -= 5.0f;
		}
		if (CheckHitKey(KEY_INPUT_LSHIFT))
		{
			sp1->coord_.y += 5.0f;
		}
		if (CheckHitKey(KEY_INPUT_O) && !keyo)
		{
			objManager_.SwitchAO();
		}
		keyo = CheckHitKey(KEY_INPUT_O);

		ScreenFlip();
	}
	DxLib_End();
}