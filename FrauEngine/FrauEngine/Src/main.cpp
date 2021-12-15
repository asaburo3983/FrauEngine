// strictStrings_off.cpp
#include "Application.h"
#include "TitleScene.h"
#include "FlowerShopScene.h"

using namespace DirectX;
using namespace std;
using namespace frauEngine;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	int wx = GetSystemMetrics(SM_CXSCREEN);
	int wy = GetSystemMetrics(SM_CYSCREEN);

	auto app = Application::GetInstance();
	app->Init("FrauBouquet", wx, wy, false);

	
	TitleScene titleScene;
	FlowerShopScene flowerShopScene;
	app->SetSceneList("Title", &titleScene);
	app->SetSceneList("FlowerShop", &flowerShopScene);

	app->Load(&titleScene);

	app->Loop();

	app->UnInit();

}

