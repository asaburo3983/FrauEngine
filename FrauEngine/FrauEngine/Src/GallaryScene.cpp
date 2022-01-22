
#include "GallaryScene.h"
//#include "CustomMaterial.h"


//ロード前のデータロード　マルチスレッドで使うデータなどの初期化
void GallaryScene::LoadFrontLoad() {
	Loading::GetInstance()->Reset();
}
void GallaryScene::LoadInUpdate() {
	Loading::GetInstance()->Updata();
}
void GallaryScene::LoadInDraw() {
	Loading::GetInstance()->Draw();
}

void GallaryScene::StaticLoad() {
	GallaryPlayer* player = GallaryPlayer::GetInstance();

	auto vertexShader = resource->Shader("VertexShader.hlsl");
	auto vertexShaderShadow = resource->Shader("VertexShader_Shadow.hlsl");

	auto vertexShaderAnim = resource->Shader("VertexShader_Anim.hlsl");
	auto vertexShaderAnimShadow = resource->Shader("VertexShader_AnimShadow.hlsl");

	auto pixelShader = resource->Shader("PixelShader.hlsl");
	auto pixelShaderShadow = resource->Shader("PixelShader_Shadow.hlsl");
	auto pixelShaderToon = resource->Shader("PixelShader_Toon.hlsl");


	auto playerModel = resource->Model("Frau.fbx");
	playerExModel.Initialize(playerModel, vertexShaderAnim, pixelShader, nullptr, nullptr, nullptr, D3D12_CULL_MODE::D3D12_CULL_MODE_FRONT);
	playerExModel.InitializeSub(ModelType::SHADOW, vertexShaderAnimShadow, pixelShaderShadow);
	//playerExModel.InitializeSub(ModelType::SUB1, vertexShaderAnim, pixelShaderToon, nullptr, nullptr, nullptr, D3D12_CULL_MODE::D3D12_CULL_MODE_FRONT);	
	//トゥーンマテリアルの設定
	//auto playerSub1 =playerExModel.GetModelObject(ModelType::SUB1);
	//LoadMaterialLinker("Data/Model/Frau/MatLink/Frau.matlink", "Data/Model/Frau/MatLink/Material/", "Data/Model/Frau/Tex/", playerSub1);
	//プレイヤーオブジェクトの設定
	player->Setup(&playerExModel);

	auto flowerShopModel = resource->Model("FlowerShop.fbx");
	flowerShopExModel.Initialize(flowerShopModel, vertexShader, pixelShader, nullptr, nullptr, nullptr, D3D12_CULL_MODE::D3D12_CULL_MODE_BACK);
	flowerShopExModel.InitializeSub(ModelType::SHADOW, vertexShaderShadow, pixelShaderShadow);
	//flowerShopExModel.InitializeSub(ModelType::SUB1, vertexShader, pixelShaderToon, nullptr, nullptr, nullptr, D3D12_CULL_MODE::D3D12_CULL_MODE_BACK);
	//トゥーンマテリアルの設定
	//auto flowerShopSub1 = flowerShopExModel.GetModelObject(ModelType::SUB1);
	//LoadMaterialLinker("Data/Model/FlowerShop/MatLink/FlowerShop.matlink", "Data/Model/FlowerShop/MatLink/Material/", "Data/Model/FlowerShop/Tex/", flowerShopSub1);


	//UI
	auto wideButton = resource->LoadIm("Data/Image/Gallary/WideButon.png");
	for (int i = 0; i < (int)Button::MAX; i++) {
		wideButtonImage[i].SetResource(wideButton);
	}

	cameraStrImage.SetResource(resource->LoadIm("Data/Image/Gallary/Str/CameraStr.png"));
	enableUIStrImage.SetResource(resource->LoadIm("Data/Image/Gallary/Str/EnableUIStr.png"));

	shaderStrImages[0].SetResource(resource->LoadIm("Data/Image/Gallary/Str/PBRShaderStr.png"));
	shaderStrImages[1].SetResource(resource->LoadIm("Data/Image/Gallary/Str/ToonShaderStr.png"));

	postEffectStrImages[0].SetResource(resource->LoadIm("Data/Image/Gallary/Str/NoneEffectStr.png"));
	postEffectStrImages[1].SetResource(resource->LoadIm("Data/Image/Gallary/Str/DepthOfFieldStr.png"));
	postEffectStrImages[2].SetResource(resource->LoadIm("Data/Image/Gallary/Str/BlurStr.png"));
	postEffectStrImages[3].SetResource(resource->LoadIm("Data/Image/Gallary/Str/SharpStr.png"));
	postEffectStrImages[4].SetResource(resource->LoadIm("Data/Image/Gallary/Str/RetoroStr.png"));
	postEffectStrImages[5].SetResource(resource->LoadIm("Data/Image/Gallary/Str/NegativeStr.png"));
	postEffectStrImages[6].SetResource(resource->LoadIm("Data/Image/Gallary/Str/OutlineStr.png"));
	postEffectStrImages[7].SetResource(resource->LoadIm("Data/Image/Gallary/Str/OutlineDoFStr.png"));

	cameraTutorialStrImage.SetResource(resource->LoadIm("Data/Image/Gallary/Str/CameraTutorialStr.png"));
	DoFTutorialStrImage.SetResource(resource->LoadIm("Data/Image/Gallary/Str/DoFTutorialStr.png"));

	//背景画像

	skyImage.SetResource(resource->Image("Sky.png"));

	////ぶつかり判定用のコライダー
	SimpleBoxCollider2D _boxCollider[8];
	_boxCollider[0].Setup(Vector2(7, 0), Vector2(1, 32));
	_boxCollider[1].Setup(Vector2(0, 4.8), Vector2(32, 1));
	_boxCollider[2].Setup(Vector2(-7, 0), Vector2(1, 32));
	_boxCollider[3].Setup(Vector2(0, -4.75), Vector2(32, 1));
	_boxCollider[4].Setup(Vector2(-2.75, 0.9), Vector2(5.5, 3.6));
	_boxCollider[5].Setup(Vector2(5.6, 3.5), Vector2(7.6, 3));
	_boxCollider[6].Setup(Vector2(4.4, -4.8), Vector2(4.4, 4.8));
	_boxCollider[7].Setup(Vector2(7.5, -4.5), Vector2(4, 10.3));
	for (int i = 0; i < 8; i++) {
		boxCollider.push_back(_boxCollider[i]);
	}
	SimpleCircleCollider2D _circleCollider(Vector2(5.5, -2.5), 0.5);
	circleCollider.push_back(_circleCollider);
	////イベント用のぶつかり判定のないコライダー
	SimpleBoxCollider2D _boxColliderEvent[3];
	_boxColliderEvent[0].Setup(Vector2(-2.4, -4.6), Vector2(4.8, 4.6));//出口	
	for (int i = 0; i < 1; i++) {
		boxColliderEvent.push_back(_boxColliderEvent[i]);
	}

	SetObjectList(&playerExModel, "Player");
	SetObjectList(&camera, "Camera");
	SetObjectList(&light, "Lights");
}
void GallaryScene::Load() {

	camera.SetPos(Vector3(0, 5, -13));
	camera.SetTarget(Vector3(0, 0, 0));
	camera.SetUp(Vector3(0, 1, 0));
	camera.SetFov(45);

	directionalLightParam.pos = Vector3(12 / 2, 25.0f / 3.0f, -21 / 2);
	directionalLightParam.target = Vector3(0, 0, 0);
	directionalLightParam.up = Vector3(0, 1, 0);
	directionalLightParam.fov = 45;
	directionalLightParam.vector = Vector3(1, 1, 1);
	directionalLightParam.color = Vector3(1, 1, 1);

	light.SetDirectionalLight(directionalLightParam);
	light.SetAmbientLight(0.75);


	camera.Update();
	light.Update();

	flowerShopExModel.SetAllAnimeState(false, 1, 0.2);
	flowerShopExModel.SetAll(Vector3(-8, 2, 1.8), Vector3(0, 90, 0), Vector3(2, 0.9, 1.5));

	//UIの位置設定
	Vector2 cameraButtonPos =  Vector2(335, 845);
	Vector2 enableButtonPos =  Vector2(125, 845);

	Vector2 smallButtonUIScale = Vector2(0.45, 1);
	Vector2 smallButtonStrUIScale = Vector2(0.75, 0.75);

	wideButtonImage[(int)Button::CAMERA].SetAll(cameraButtonPos, smallButtonUIScale);
	cameraStrImage.SetAll(cameraButtonPos, smallButtonStrUIScale);

	wideButtonImage[(int)Button::ENABLE].SetAll(enableButtonPos, smallButtonUIScale);
	enableUIStrImage.SetAll(enableButtonPos, smallButtonStrUIScale);

	Vector2 shaderButtonPos = Vector2(230, 930);
	wideButtonImage[(int)Button::SHADER].SetAll(shaderButtonPos);
	for (int i = 0; i < (int)PreviewShader::MAX; i++) {
		shaderStrImages[i].SetAll(shaderButtonPos);
	}

	Vector2 postEffectButtonPos = Vector2(230, 1030);
	wideButtonImage[(int)Button::POSTEFFECT].SetAll(postEffectButtonPos);
	for (int i = 0; i < (int)AddPostEffect::MAX; i++) {
		postEffectStrImages[i].SetAll(postEffectButtonPos);
	}

	cameraTutorialStrImage.SetAll(Vector2(270, 770));
	DoFTutorialStrImage.SetAll(Vector2(270, 720));
	skyImage.SetAll(Vector2(960, 540));

}


void GallaryScene::UnLoad() {
}


void GallaryScene::Update() {
	GallaryPlayer* player = GallaryPlayer::GetInstance();
	auto app = Application::GetInstance();
	//フォトモード切替

	if (mouse->right == 1) {
		LoadScene("Title");
	}

	//UIの表示
	if (wideButtonImage[(int)Button::ENABLE].Hit(mouse->x, mouse->y) && mouse->left == 1) {
		enableUI = !enableUI;
		//UIの透過
		if (enableUI == false) {
			float enableButtonMinAlpha = 0.5f;
			wideButtonImage[(int)Button::ENABLE].SetAlpha(enableButtonMinAlpha);
			enableUIStrImage.SetAlpha(enableButtonMinAlpha);
		}
		//UIの非透過
		else {
			wideButtonImage[(int)Button::ENABLE].SetAlpha(1);
			enableUIStrImage.SetAlpha(1);
		}
	}
	//カメラ切り替え
	if (wideButtonImage[(int)Button::CAMERA].Hit(mouse->x, mouse->y) && mouse->left == 1) {
		photoMode = !photoMode;

		if (photoMode) {
			Vector3 targetPos = player->GetPos();
			targetPos.Y += 3.5f;
			Vector3 cameraPos = player->GetPos();
			cameraPos.Y += 3.5f;
			cameraPos.Z -= 5;
			camera.SetPos(cameraPos);
			camera.SetTarget(targetPos);
		}
		else {
			camera.SetPos(Vector3(0, 5, -13));
			camera.SetTarget(Vector3(0, 0, 0));
			camera.SetUp(Vector3(0, 1, 0));
			camera.SetFov(45);
		}
	}
	if (photoMode) {
		float cameraSpeed = 0.05f;
		Vector2 cameraMaxDist = { 3.0f ,3.0f };

		if (key->key[DIK_UP] >= 1) {
			Vector3 cameraPos = camera.GetPos();

			if (cameraPos.Y < camera.GetTarget().Y + cameraMaxDist.Y) {
				cameraPos.Y += cameraSpeed;
			}
			camera.SetPos(cameraPos);

		}
		if (key->key[DIK_DOWN] >= 1) {
			Vector3 cameraPos = camera.GetPos();
			if (cameraPos.Y > camera.GetTarget().Y - cameraMaxDist.Y) {
				cameraPos.Y -= cameraSpeed;
			}
			camera.SetPos(cameraPos);
		}
		if (key->key[DIK_RIGHT] >= 1) {
			Vector3 cameraPos = camera.GetPos();
			if (cameraPos.X < camera.GetTarget().X + cameraMaxDist.X) {
				cameraPos.X += cameraSpeed;
			}
			camera.SetPos(cameraPos);

		}
		if (key->key[DIK_LEFT] >= 1) {
			Vector3 cameraPos = camera.GetPos();
			if (cameraPos.X > camera.GetTarget().X - cameraMaxDist.X) {
				cameraPos.X -= cameraSpeed;
			}
			camera.SetPos(cameraPos);
		}


	}


	player->Move(0.04f, 9.0f);

	player->AnimationControl();

	player->Collision(boxCollider, circleCollider, boxColliderEvent);



	Application::GetInstance()->SetDepthOfField(true, mouse->x, mouse->y);

	//シェーダー切り替え
	if (wideButtonImage[(int)Button::SHADER].Hit(mouse->x, mouse->y) && mouse->left == 1) {
		shaderNum = (shaderNum + 1) % 2;

	}
	//ポストエフェクト切り替え
	if (wideButtonImage[(int)Button::POSTEFFECT].Hit(mouse->x, mouse->y) && mouse->left == 1) {
		postEffectNum = (postEffectNum + 1) % (int)AddPostEffect::MAX;
		app->SetBlurPower(1);
	}
	Application::GetInstance()->SetAddEffect(postEffectNum);
}

void GallaryScene::Draw() {

	

	auto lowApp = LowApplication::GetInstance();
	auto lights = Lights::GetInstance();
	GallaryPlayer* player = GallaryPlayer::GetInstance();

	//影の描画
	lowApp->DrawOnDepth(Lights::GetInstance()->depthHeap, Lights::GetInstance()->shadowTexSize);

	flowerShopExModel.Draw(ModelType::SHADOW);
	player->Draw(ModelType::SHADOW);

	//通常の描画
	lowApp->DrawOnRenderTarget(Application::GetInstance()->GetPostEffectRenderTarget());

	//空の描画
	skyImage.Draw();

	switch (shaderNum) {
	case 0:
		flowerShopExModel.ModelObject::Draw();
		player->Draw(ModelType::MAIN);
		break;
	}

	camera.Update();
	light.Update();

}

void GallaryScene::DrawNonePostEffect() {

	wideButtonImage[(int)Button::ENABLE].Draw();
	enableUIStrImage.Draw();

	if (enableUI) {
		for (int i = 0; i < (int)Button::MAX; i++) {
			if (i == (int)Button::ENABLE) {
				continue;
			}
			wideButtonImage[i].Draw();
		}

		cameraStrImage.Draw();

		shaderStrImages[shaderNum].Draw();
		postEffectStrImages[postEffectNum].Draw();

		if (photoMode) {
			cameraTutorialStrImage.Draw();
		}
		if (postEffectNum == (int)AddPostEffect::DEPTHOFFIELD ||
			postEffectNum == (int)AddPostEffect::OUTLINE_DEPTHOFFIELD) {
			DoFTutorialStrImage.Draw();
		}
	}
}
