#pragma once
#include "Application.h"

#include "Objects.h"

#include "Loading.h"
#include "Fade.h"

#include "MaterialLinkerData.h"

#include "GallaryPlayer.h"

using namespace frauEngine;
enum class Button {
	CAMERA,ENABLE,SHADER,POSTEFFECT,MAX
};
enum class PreviewShader {
	PBR,TOON,MAX
};
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

	ImageObject wideButtonImage[4];
	ImageObject cameraStrImage;
	ImageObject enableUIStrImage;

	ImageObject shaderStrImages[2];
	ImageObject postEffectStrImages[(int)AddPostEffect::MAX];

	ImageObject cameraTutorialStrImage;
	ImageObject DoFTutorialStrImage;
	ImageObject skyImage;

	bool enableUI = true;

	bool photoMode = false;

	int shaderNum = 0;
	int postEffectNum = 0;
public:

	void LoadFrontLoad();
	void LoadInUpdate();
	void LoadInDraw();

	void StaticLoad();
	void Load();
	void Update();
	void Draw();
	void DrawNonePostEffect();
	void UnLoad();

};
