
#include "FlowerShopScene.h"
//#include "CustomMaterial.h"


//ロード前のデータロード　マルチスレッドで使うデータなどの初期化
void FlowerShopScene::LoadFrontLoad() {
	//loading.Reset();
}
void FlowerShopScene::LoadInUpdata() {
	//loading.Updata();
}
void FlowerShopScene::LoadInDraw() {
	//loading.Draw();
}

void FlowerShopScene::StaticLoad() {
	Player* player = Player::GetInstance();

	auto vertexShader = resource->Shader("VertexShader.hlsl");
	auto vertexShaderShadow = resource->Shader("VertexShader_Shadow.hlsl");

	auto vertexShaderAnim = resource->Shader("VertexShader_Anim.hlsl");
	auto vertexShaderAnimShadow = resource->Shader("VertexShader_AnimShadow.hlsl");

	auto pixelShader = resource->Shader("PixelShader.hlsl");
	auto pixelShaderShadow = resource->Shader("PixelShader_Shadow.hlsl");
	auto pixelShaderToon = resource->Shader("PixelShader_Toon.hlsl");
		
	auto playerModel = resource->Model("Frau.fbx");
	
	playerExModel.Initialize(playerModel, vertexShaderAnim, pixelShaderToon, nullptr, nullptr, nullptr, D3D12_CULL_MODE::D3D12_CULL_MODE_FRONT);
	playerExModel.InitializeSub(ModelType::SHADOW, vertexShaderAnimShadow, pixelShaderShadow);
	player->Setup(&playerExModel);
	LoadMaterialLinker("Data/Model/Frau/MatLink/Frau.matlink", "Data/Model/Frau/MatLink/Material/", "Data/Model/Frau/Tex/", &playerExModel);

	auto flowerShopModel = resource->Model("FlowerShop.fbx");
	flowerShopExModel.Initialize(flowerShopModel, vertexShader, pixelShaderToon, nullptr, nullptr, nullptr, D3D12_CULL_MODE::D3D12_CULL_MODE_BACK);
	flowerShopExModel.InitializeSub(ModelType::SHADOW, vertexShaderShadow, pixelShaderShadow);

	LoadMaterialLinker("Data/Model/FlowerShop/MatLink/FlowerShop.matlink", "Data/Model/FlowerShop/MatLink/Material/", "Data/Model/FlowerShop/Tex/", &flowerShopExModel);

	
	//マテリアルロード
	//LoadLinker(
	//	"Data/Material/MaterialLinker/MainBack.matlink",
	//	"Data/Material/Material/",
	//	"Data/Model/MainBack/Tex/",
	//	&modelObjM["MainBack"]);
	//LoadLinker(
	//	"Data/Material/MaterialLinker/Frau.matlink",
	//	"Data/Material/Material/",
	//	"Data/Model/Frau/Tex/",
	//	&modelObjM["Frau"]);

	////画像ロード　
	//LoadIm("Back", "Data/Image/MainGame/Back.png");
	//imageObjM["Back"].SetResource(Image("Back"));
	//imageObjM["Back"].SetAll(Vector2(960, 540), Vector2(4, 4), 0, 1);

	////UI
	//LoadIm("EventBase", "Data/Image/MainGame/UI/EventBase.png");
	//LoadIm("OpenShopStr", "Data/Image/MainGame/UI/OpenShopStr.png");
	//LoadIm("PlanterStr", "Data/Image/MainGame/UI/PlanterStr.png");
	//LoadIm("ExitShopStr", "Data/Image/MainGame/UI/ExitShopStr.png");
	//LoadIm("ShopingStr", "Data/Image/MainGame/UI/ShopingStr.png");

	//imageObjM["EventBase"].SetResource(Image("EventBase"));
	//imageObjM["OpenShopStr"].SetResource(Image("OpenShopStr"));
	//imageObjM["PlanterStr"].SetResource(Image("PlanterStr"));
	//imageObjM["ExitShopStr"].SetResource(Image("ExitShopStr"));
	//imageObjM["ShopingStr"].SetResource(Image("ShopingStr"));

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
	_boxColliderEvent[1].Setup(Vector2(-11, 1), Vector2(11, 2));//花壇	
	_boxColliderEvent[2].Setup(Vector2(4.95, 1.75), Vector2(3, 0.5));//開店
	for (int i = 0; i < 3; i++) {
		boxColliderEvent.push_back(_boxColliderEvent[i]);
	}


	////オブジェクトの設定
	//player->Setup(&modelObjM["Frau"], &modelObjM["FrauS"]);

	//myShopEventUI.Setup(&imageObjM["EventBase"], &imageObjM["OpenShopStr"], &imageObjM["PlanterStr"], &imageObjM["ExitShopStr"]);

	SetObjectList(&playerExModel, "Player");
	SetObjectList(&camera, "Camera");
	SetObjectList(&light, "Lights");
}
void FlowerShopScene::Load() {

	camera.SetPos(Vector3(0, 5, -13));
	camera.SetTarget(Vector3(0, 0, 0));
	camera.SetUp(Vector3(0, 1, 0));
	camera.SetFov(45);
	
	directionalLightParam.pos = Vector3(12, 25, -21);
	directionalLightParam.target = Vector3(0, 0, 0);
	directionalLightParam.up = Vector3(0, 1, 0);
	directionalLightParam.fov = 45;
	directionalLightParam.vector = Vector3(1, 1, 1);
	directionalLightParam.color = Vector3(1, 1, 1);

	light.SetDirectionalLight(directionalLightParam);
	light.SetAmbientLight(0.5);



	camera.Updata();
	light.Updata();
	
	//fade.Reset();

	flowerShopExModel.SetAllAnimeState(false, 1, 0.2);
	flowerShopExModel.SetAll(Vector3(-8, 2, 1.8), Vector3(0, 90, 0), Vector3(2, 0.9, 1.5));
}


void FlowerShopScene::UnLoad() {
}


void FlowerShopScene::Updata() {
	Player* player = Player::GetInstance();

	//フォトモード切替
	if (key->key[DIK_F] == 1) {
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

			if (cameraPos.Y < camera.GetTarget().Y+ cameraMaxDist.Y) {
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
			if (cameraPos.X < camera.GetTarget().X+ cameraMaxDist.X) {
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

		//auto dLight = light::DirectionalLight::GetInstance();

		//Player* player = Player::GetInstance();
		player->Move(0.04f, 9.0f);

		player->AnimationControl();

		player->Collision(boxCollider, circleCollider, boxColliderEvent);

		//myShopEventUI.SetDrawPos();

		//int eventClickNum = myShopEventUI.Click();

		//switch (eventClickNum) {
		//case 1://出口	
		//	LoadScene("Handyman");
		//	break;
		//case 2://プランター

		//	break;
		//case 3://開店

		//	break;
		//}

		//if (KEY->key[DIK_ESCAPE]) {
		//	gameEnd = true;
		//}
}

int postEffectNum = 0;
void FlowerShopScene::Draw() {



	auto lowApp = LowApplication::GetInstance();
	auto lights = Lights::GetInstance();
	Player* player = Player::GetInstance();

	//影の描画
	lowApp->DrawOnDepth(Lights::GetInstance()->depthHeap, Lights::GetInstance()->shadowTexSize);

	flowerShopExModel.Draw(ModelType::SHADOW);
	player->DrawShadow();

	//通常の描画
	lowApp->DrawOnRenderTarget(Application::GetInstance()->GetPostEffectRenderTarget());

	flowerShopExModel.ModelObject::Draw();
	player->Draw();
	
	ImGui::End();



	ImGui::Begin("FPS");                          //ウィンドウ名になる
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	camera.Updata();
	light.Updata();

	//被写界深度
	if (photoMode) {
		Application::GetInstance()->SetDepthOfField(true, mouse->x, mouse->y);

		if (key->key[DIK_1] == 1) {
			postEffectNum = (postEffectNum + 1) % (int)AddPostEffect::MAX;

		}
		Application::GetInstance()->SetAddEffect(postEffectNum);
	}
	else {
		Application::GetInstance()->SetDepthOfField(false);
	}
}

void FlowerShopScene::DrawNonePostEffect() {
	//myShopEventUI.Draw();


}
