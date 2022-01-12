#include "MainGameCommonProcess.h"

void LoadFont() {
	//フォント読み込み
	auto fonts = Fonts::GetInstance();
	fonts->GetFont((int)FontList::MEIRIO)->SetAllSize(0.5);
	fonts->GetFont((int)FontList::AKAZUKIN)->SetAllSize(0.5);

}
void LoadShader() {
	auto rc = Resource::GetInstance();
	rc->LoadShader(ShaderType::VS, "Data/Shader/VertexShader.hlsl");
	rc->LoadShader(ShaderType::VS, "Data/Shader/VertexShader_Shadow.hlsl");

	rc->LoadShader(ShaderType::VS, "Data/Shader/VertexShader_Anim.hlsl");
	rc->LoadShader(ShaderType::VS, "Data/Shader/VertexShader_AnimShadow.hlsl");

	rc->LoadShader(ShaderType::PS, "Data/Shader/PixelShader.hlsl");
	rc->LoadShader(ShaderType::PS, "Data/Shader/PixelShader_Shadow.hlsl");
	rc->LoadShader(ShaderType::PS, "Data/Shader/PixelShader_Toon.hlsl");

	rc->LoadShader(ShaderType::VS, "Data/Shader/VertexShader_BillBoard.hlsl");
	rc->LoadShader(ShaderType::PS, "Data/Shader/PixelShader_BillBoard.hlsl");

	rc->LoadShader(ShaderType::PS, "Data/Shader/PixelShader_Water.hlsl");
	rc->LoadShader(ShaderType::PS, "Data/Shader/PixelShader_Texture.hlsl");
}
void LoadModel() {
	auto rc = Resource::GetInstance();

	rc->LoadModel("Data/Model/Frau/Frau.fbx", "Data/Model/Frau/Tex/");

	rc->LoadModel("Data/Model/Idea_Billboard/Idea_Frame.fbx", "Data/Model/Idea_Billboard/Tex/");
	rc->LoadModel("Data/Model/Idea_Billboard/Idea_Buy.fbx", "Data/Model/Idea_Billboard/Tex/");
	rc->LoadModel("Data/Model/Idea_Billboard/Idea_Exit.fbx", "Data/Model/Idea_Billboard/Tex/");
	rc->LoadModel("Data/Model/Idea_Billboard/Idea_OpenShop.fbx", "Data/Model/Idea_Billboard/Tex/");
	rc->LoadModel("Data/Model/Idea_Billboard/Idea_Planter.fbx", "Data/Model/Idea_Billboard/Tex/");
	rc->LoadModel("Data/Model/Idea_Billboard/Idea_JoinShop.fbx", "Data/Model/Idea_Billboard/Tex/");

	rc->LoadModel("Data/Model/MagicShop/MagicShop.fbx", "Data/Model/MagicShop/Tex/");

	rc->LoadModel("Data/Model/FlowerShop/FlowerShop.fbx", "Data/Model/FlowerShop/Tex/");
	rc->LoadModel("Data/Model/Planter/MagicPlanter.fbx", "Data/Model/Planter/Tex/");

	rc->LoadModel("Data/Model/HandyShop/HandyShop.fbx", "Data/Model/HandyShop/Tex/");
	rc->LoadModel("Data/Model/Handy/Handy.fbx", "Data/Model/Handy/Tex/");

	rc->LoadModel("Data/Model/Map/Map.fbx", "Data/Model/Map/Tex/");

}
void LoadIm() {
	auto rc = Resource::GetInstance();
	rc->LoadIm("Data/Image/Global/Sky.png");
	rc->LoadIm("Data/Image/Global/Black.png");
	rc->LoadIm("Data/Image/Global/WhiteTex.png");

	//アイテム
	//タネ
	rc->LoadIm("Data/Image/Item/Beranda_Seed.png");
	rc->LoadIm("Data/Image/Item/Cosmo_Seed.png");
	rc->LoadIm("Data/Image/Item/Maso_Seed.png");
	rc->LoadIm("Data/Image/Item/Panda_Seed.png");
	rc->LoadIm("Data/Image/Item/Rose_Seed.png");
	rc->LoadIm("Data/Image/Item/Sugger_Seed.png");
	rc->LoadIm("Data/Image/Item/Tanepopo_Seed.png");	
	rc->LoadIm("Data/Image/Item/Masomaso_Seed.png");
	rc->LoadIm("Data/Image/Item/Ranpopo_Seed.png");
	rc->LoadIm("Data/Image/Item/Barabara_Seed.png");
	rc->LoadIm("Data/Image/Item/SuggerPan_Seed.png");
	rc->LoadIm("Data/Image/Item/Frau_Seed.png");


	//マジックアイテム
	rc->LoadIm("Data/Image/Item/MagicPlanter.png");
	rc->LoadIm("Data/Image/Item/BugFix.png");
	rc->LoadIm("Data/Image/Item/Book0.png");
	rc->LoadIm("Data/Image/Item/Book1.png");
	rc->LoadIm("Data/Image/Item/Book2.png");
	rc->LoadIm("Data/Image/Item/Book3.png");
	rc->LoadIm("Data/Image/Item/Book4.png");

	//立ち絵ロード　イベントの多さによって使用頻度は変わる
	rc->LoadIm("Data/Image/Chara/Frau/Frau_Normal.png");
	rc->LoadIm("Data/Image/Chara/Frau/Frau_Smile.png");
	rc->LoadIm("Data/Image/Chara/Frau/Frau_Surprise.png");
	rc->LoadIm("Data/Image/Chara/Frau/Frau_Trouble.png");

	rc->LoadIm("Data/Image/Chara/Christa/Christa_Normal.png");
	rc->LoadIm("Data/Image/Chara/Christa/Christa_Smile.png");
	rc->LoadIm("Data/Image/Chara/Christa/Christa_Surprise.png");
	rc->LoadIm("Data/Image/Chara/Christa/Christa_Trouble.png");

	rc->LoadIm("Data/Image/Chara/Handy/Handy_Normal.png");
	rc->LoadIm("Data/Image/Chara/Handy/Handy_Smile.png");
	rc->LoadIm("Data/Image/Chara/Handy/Handy_Surprise.png");
	rc->LoadIm("Data/Image/Chara/Handy/Handy_Trouble.png");

	//ノベル関連
	rc->LoadIm("Data/Image/Novel/Novel_TextBase.png");
	rc->LoadIm("Data/Image/Novel/Novel_Frame.png");

	//ショップ関連 
	rc->LoadIm("Data/Image/Shop/ManualBase.png");
	rc->LoadIm("Data/Image/Shop/RightArrow.png");
	rc->LoadIm("Data/Image/Shop/ShopBase.png");
	rc->LoadIm("Data/Image/Shop/ShopBaseLine.png");
	rc->LoadIm("Data/Image/Shop/BuyButton.png");
	rc->LoadIm("Data/Image/Shop/SelectFrame.png");

	//チュートリアル関連
	rc->LoadIm("Data/Image/Tutorial/TutorialFrame.png");

	//ノーマルUI関連
	rc->LoadIm("Data/Image/NormalUI/DayBase.png");
	
	rc->LoadIm("Data/Image/NormalUI/MoneyBase.png");

	rc->LoadIm("Data/Image/NormalUI/ItemBase.png");
	rc->LoadIm("Data/Image/NormalUI/ItemBaseLine.png");



}
void LoadSound() {
	auto rc = Resource::GetInstance();
}
void StaticClassSetting() {
	Player* player = Player::GetInstance();
	Stage* stage = Stage::GetInstance();
	CameraWork* camera = CameraWork::GetInstance();
	NovelSystem* novelSystem = NovelSystem::GetInstance();
	TutorialSystem* tutorialSystem = TutorialSystem::GetInstance();
	EventManager* eventManager = EventManager::GetInstance();
	HandyShop* handyShop = HandyShop::GetInstance();
	MagicShop* magicShop = MagicShop::GetInstance();
	auto normalUI = NormalUI::GetInstance();
	auto item = Item::GetInstance();
	auto planterSystem = PlanterSystem::GetInstance();

	eventManager->Initialize();
	stage->Initialize();
	player->Initialize(0.04 * 5, 9.0f);
	camera->Initialize();
	novelSystem->Initialize();
	tutorialSystem->Initialize();
	handyShop->Initialize("Data/ShopCSV/HandyItem.csv", "Data/ShopCSV/HandyReaction.csv");
	magicShop->Initialize("Data/ShopCSV/MagicItem.csv", "Data/ShopCSV/MagicReaction.csv");
	normalUI->Initialize();
	item->Initialize("Data/ItemCSV/ItemList.csv");
	planterSystem->Initialize();
}
void CommonDataLoad() {
	auto rc = Resource::GetInstance();

	LoadFont();
	LoadIm();
	LoadShader();
	LoadModel();

	StaticClassSetting();
}
void CommonUpdate() {
	auto player = Player::GetInstance();
	auto stage = Stage::GetInstance();
	auto camera = CameraWork::GetInstance();
	auto eventManager = EventManager::GetInstance();
	auto novelSystem = NovelSystem::GetInstance();
	auto tutorialSystem = TutorialSystem::GetInstance();
	auto item = Item::GetInstance();
	auto normalUI = NormalUI::GetInstance();
	auto planterSystem = PlanterSystem::GetInstance();

	player->Update();
	stage->Update();
	camera->Updata();
	novelSystem->Update();
	tutorialSystem->Update();
	eventManager->Update();
	item->Update();
	normalUI->Update();
	planterSystem->Update();
}

void CommonDraw() {
	auto novelSystem = NovelSystem::GetInstance();
	auto tutorialSystem = TutorialSystem::GetInstance();
	auto lowApp = LowApplication::GetInstance();
	auto app = Application::GetInstance();
	auto lights = Lights::GetInstance();
	auto player = Player::GetInstance();
	auto stage = Stage::GetInstance();
	auto planterSystem = PlanterSystem::GetInstance();

	//影の描画
	lowApp->DrawOnDepth(Lights::GetInstance()->depthHeap, Lights::GetInstance()->shadowTexSize);

	stage->DrawShadow();
	player->DrawShadow();

	//通常の描画
	lowApp->DrawOnRenderTarget(app->GetPostEffectRenderTarget());

	stage->Draw();

	player->Draw();
	player->DrawBillBoard();

	
	//ポストエフェクト用の処理
	app->SetDepthOfField(true);
	app->SetAddEffect((int)AddPostEffect::BLUR);
	app->SetBlurPower(novelSystem->GetAlphaUI() + tutorialSystem->GetAlpha());
}

void CommonDrawNonePostEffect() {

	auto player = Player::GetInstance();
	auto novelSystem = NovelSystem::GetInstance();
	auto tutorialSystem = TutorialSystem::GetInstance();
	auto eventManager = EventManager::GetInstance();
	auto app = Application::GetInstance();
	auto normalUI = NormalUI::GetInstance();
	auto planterSystem = PlanterSystem::GetInstance();

	normalUI->Draw();

	planterSystem->Draw();

	novelSystem->Draw();

	tutorialSystem->Draw();



	app->SetColorMulti(Color(1.0f - eventManager->GetFadeCount()));

	ImGui::Begin("FPS");                          //ウィンドウ名になる
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}