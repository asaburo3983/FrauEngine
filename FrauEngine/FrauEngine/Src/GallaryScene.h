#pragma once
#include "Application.h"

#include "Objects.h"

#include "Loading.h"
#include "Fade.h"

#include "MaterialLinkerData.h"

#include "GallaryPlayer.h"

using namespace frauEngine;

class GallaryScene : public Scene {
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

	int shaderNum = 0;
	int postEffectNum = 0;
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
