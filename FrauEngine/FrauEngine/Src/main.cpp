// strictStrings_off.cpp
#include "Application.h"
#include "Loading.h"
#include "TitleScene.h"
#include "FlowerShopScene.h"
#include "GallaryScene.h"
#include "HandyShopScene.h"
#include "MagicShopScene.h"
#include "MapScene.h"

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
	app->Init("FrauBouquet", wx, wy, true);
	//LowApplication::GetInstance()->SetDebugMode(false);

	Loading::GetInstance()->Initialize();
	TitleScene titleScene;
	FlowerShopScene flowerShopScene;
	GallaryScene gallaryScene;
	MapScene mapScene;
	HandyShopScene handyShopScene;
	MagicShopScene magicShopScene;

	app->SetSceneList("Title", &titleScene);
	app->SetSceneList("FlowerShop", &flowerShopScene);
	app->SetSceneList("Gallary", &gallaryScene);
	app->SetSceneList("Map", &mapScene);
	app->SetSceneList("HandyShop", &handyShopScene);
	app->SetSceneList("MagicShop", &magicShopScene);

	app->Load(&titleScene);

	app->Loop();

	app->UnInit();

}

