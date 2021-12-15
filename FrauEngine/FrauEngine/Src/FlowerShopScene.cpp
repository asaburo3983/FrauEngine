
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

	auto vertexShader=resource->LoadShader(ShaderType::VS, "Data/Shader/VertexShader.hlsl");	
	auto vertexShaderShadow = resource->LoadShader(ShaderType::VS, "Data/Shader/VertexShader_Shadow.hlsl");

	auto vertexShaderAnim = resource->LoadShader(ShaderType::VS, "Data/Shader/VertexShader_Anim.hlsl");
	auto vertexShaderAnimShadow = resource->LoadShader(ShaderType::VS, "Data/Shader/VertexShader_AnimShadow.hlsl");

	auto pixelShader = resource->LoadShader(ShaderType::PS, "Data/Shader/PixelShader.hlsl");
	//auto pixelShaderAnim = resource->LoadShader(ShaderType::PS, "Data/Shader/PixelShader_Anim.hlsl");
	auto pixelShaderShadow = resource->LoadShader(ShaderType::PS, "Data/Shader/PixelShader_Shadow.hlsl");


	auto playerModel = resource->LoadModel("Data/Model/Frau/Frau.fbx", "Data/Model/Frau/Tex/");
	playerExModel.Initialize(playerModel, vertexShaderAnim, pixelShader);
	playerExModel.InitializeSub(ModelType::SHADOW, vertexShaderAnimShadow, pixelShaderShadow);
	player->Setup(&playerExModel);

	auto flowerShopModel = resource->LoadModel("Data/Model/FlowerShop/FlowerShop.fbx", "Data/Model/FlowerShop/Tex/");
	flowerShopExModel.Initialize(flowerShopModel, vertexShader, pixelShader);
	flowerShopExModel.InitializeSub(ModelType::SHADOW, vertexShaderShadow, pixelShaderShadow);

	//モデルロード
	//LoadModel("MainBack", "Data/Model/MainBack/MainBack.fbx", "Data/Model/MainBack/Tex/");
	//modelObjM["MainBack"].Initialize(Model("MainBack"), Shader("vs"), Shader("ps"), Shader("gs"));
	//modelObjM["MainBackS"].Initialize(Model("MainBack"), Shader("vs"), Shader("ps"), Shader("gs"));

	//LoadModel("Frau", "Data/Model/Frau/Frau.fbx", "Data/Model/Frau/Tex/");
	//modelObjM["Frau"].Initialize(Model("Frau"), Shader("vsAnime"), Shader("ps"), Shader("gs"));
	//modelObjM["FrauS"].Initialize(Model("Frau"), Shader("vsAnime"), Shader("ps"), Shader("gs"));

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
	//SimpleBoxCollider2D boxCollider[8];
	//boxCollider[0].Setup(Vector2(7, 0), Vector2(1, 32));
	//boxCollider[1].Setup(Vector2(0, 4.8), Vector2(32, 1));
	//boxCollider[2].Setup(Vector2(-7, 0), Vector2(1, 32));
	//boxCollider[3].Setup(Vector2(0, -4.75), Vector2(32, 1));
	//boxCollider[4].Setup(Vector2(-2.75, 0.9), Vector2(5.5, 3.6));
	//boxCollider[5].Setup(Vector2(5.6, 3.5), Vector2(7.6, 3));
	//boxCollider[6].Setup(Vector2(4.4, -4.8), Vector2(4.4, 4.8));
	//boxCollider[7].Setup(Vector2(7.5, -4.5), Vector2(4, 10.3));
	//for (int i = 0; i < 8; i++) {
	//	myShopBoxCollider.push_back(boxCollider[i]);
	//}
	//SimpleCircleCollider2D circleCollider(Vector2(5.5, -2.5), 0.5);
	//myShopCircleCollider.push_back(circleCollider);
	////イベント用のぶつかり判定のないコライダー
	//SimpleBoxCollider2D boxColliderEvent[3];
	//boxColliderEvent[0].Setup(Vector2(-2.4, -4.6), Vector2(4.8, 4.6));//出口	
	//boxColliderEvent[1].Setup(Vector2(-11, 1), Vector2(11, 2));//花壇	
	//boxColliderEvent[2].Setup(Vector2(4.95, 1.75), Vector2(3, 0.5));//開店
	//for (int i = 0; i < 3; i++) {
	//	myShopBoxColliderEvent.push_back(boxColliderEvent[i]);
	//}


	////オブジェクトの設定
	//player->Setup(&modelObjM["Frau"], &modelObjM["FrauS"]);

	//myShopEventUI.Setup(&imageObjM["EventBase"], &imageObjM["OpenShopStr"], &imageObjM["PlanterStr"], &imageObjM["ExitShopStr"]);

	////デバッグ用リストに追加
	//SetObjectList(&modelObjM["MainBack"], "MainBack");
	//SetObjectList(&modelObjM["Frau"], "Frau");
	//SetObjectList(&cameraObjM["camera1"], "camera1");
	//SetObjectList(&dLightObjM["dLightTest"], "Sun");
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


	SetObjectList(&camera, "Camera");
	SetObjectList(&light, "Lights");
	

	camera.Updata();
	light.Updata();
	//dLightObjM["dLightTest"].SetCameraRelative(cameraObjM["camera1"], Vector3(-12, 20, -7.5), Vector3(0, 1, 0), 45, Vector3(1, 1, 1));

	//fade.Reset();

	flowerShopExModel.SetAllAnimeState(false, 1, 0.2);
	flowerShopExModel.SetAll(Vector3(-8, 2, 1.8), Vector3(0, 90, 0), Vector3(2, 0.9, 1.5));
}


void FlowerShopScene::UnLoad() {
}


void FlowerShopScene::Updata() {
	Player* player = Player::GetInstance();


	//auto dLight = light::DirectionalLight::GetInstance();

	//Player* player = Player::GetInstance();
	player->Move(0.04f, 9.0f);

	player->AnimationControl();

	//player->Collision(myShopBoxCollider, myShopCircleCollider, myShopBoxColliderEvent);

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

void FlowerShopScene::Draw() {



	auto lowApp = LowApplication::GetInstance();
	auto lights = Lights::GetInstance();
	Player* player = Player::GetInstance();


	lowApp->DrawOnDepth(Lights::GetInstance()->depthHeap, Lights::GetInstance()->shadowTexSize);

	
	flowerShopExModel.Draw(ModelType::SHADOW);
	player->DrawShadow();

	lowApp->DrawOnRenderTarget(Application::GetInstance()->GetPostEffectRenderTarget());
	flowerShopExModel.ModelObject::Draw();
	player->Draw();
	

	//	lowApp->DrawDepth(dLight->depthHeap);//ライトからの視点で深度を描画

	//	modelObjM["MainBackS"].SetShadow(true);
	//	modelObjM["MainBackS"].SetAllAnimeState(false, 1, 0.2);
	//	modelObjM["MainBackS"].SetAll(modelObjM["MainBack"].GetPos(), modelObjM["MainBack"].GetAngle(), modelObjM["MainBack"].GetScale());
	//	modelObjM["MainBackS"].Draw();

	
	//}
	//{
	//	lowApp->DrawModel();//普通の頂点描画

	//	imageObjM["Back"].Draw();


	//	modelObjM["MainBack"].SetShadow(false);
	//	modelObjM["MainBack"].SetAllAnimeState(false, 1, 0.2);
	//	modelObjM["MainBack"].SetAll(Vector3(-8, 2, 1.8), Vector3(0, 90, 0), Vector3(2, 0.9, 1.5));
	//	modelObjM["MainBack"].Draw();

		



	ImGui::Begin("FPS");                          //ウィンドウ名になる
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	camera.Updata();
	light.Updata();
}

void FlowerShopScene::DrawNonePostEffect() {
	//myShopEventUI.Draw();


}
