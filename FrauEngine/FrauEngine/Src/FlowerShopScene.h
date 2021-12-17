#pragma once
#include "Application.h"

#include "Objects.h"

#include "Loading.h"
#include "Fade.h"
#include "Player.h"

using namespace frauEngine;

class FlowerShopScene : public Scene {
private:
	Loading loading;
	Fade fade;


	CameraObject camera;
	
	LightsObject light;
	DirectionalLightParam directionalLightParam;

	ModelExtendObject playerExModel;
	ModelExtendObject flowerShopExModel;

	std::vector<SimpleBoxCollider2D> boxCollider;
	std::vector<SimpleCircleCollider2D> circleCollider;
	std::vector <SimpleBoxCollider2D> boxColliderEvent;

	bool photoMode = false;
public:

	void LoadFrontLoad();
	void LoadInUpdata();
	void LoadInDraw();

	void StaticLoad();
	void Load();
	void Updata();
	void Draw();
	void DrawNonePostEffect();
	void UnLoad();

};
