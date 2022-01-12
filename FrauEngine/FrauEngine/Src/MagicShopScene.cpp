
#include "MagicShopScene.h"

//���[�h�O�̃f�[�^���[�h�@�}���`�X���b�h�Ŏg���f�[�^�Ȃǂ̏�����
void MagicShopScene::LoadFrontLoad() {
	Loading::GetInstance()->Reset();
}
void MagicShopScene::LoadInUpdate() {
	Loading::GetInstance()->Updata();
}
void MagicShopScene::LoadInDraw() {
	Loading::GetInstance()->Draw();
}

void MagicShopScene::StaticLoad() {
	Player* player = Player::GetInstance();
	Stage* stage = Stage::GetInstance();
	CameraWork* camera = CameraWork::GetInstance();
	NovelSystem* novelSystem = NovelSystem::GetInstance();
	TutorialSystem* tutorialSystem = TutorialSystem::GetInstance();
	EventManager* eventManager = EventManager::GetInstance();

	SetObjectList(player->GetModel(), "Player");
	SetObjectList(camera->GetCamera(), "Camera");
	SetObjectList(stage->GetLight(), "Lights");
	SetObjectList(stage->GetStageModel(),"MazigSgp");
}






void MagicShopScene::Load() {
	Stage* stage = Stage::GetInstance();
	EventManager* eventManager = EventManager::GetInstance();

	eventManager->SetScene(this);


	//�X�e�[�W�̃��f���f�[�^�̓����[�h���Ă���
	stage->Load(StageNum::MAGIC_SHOP);
}


void MagicShopScene::UnLoad() {
}

void MagicShopScene::Update() {
	CommonUpdate();
	auto MagicShop = MagicShop::GetInstance();
	MagicShop->Update();

}
void MagicShopScene::Draw() {
	CommonDraw();
}

void MagicShopScene::DrawNonePostEffect() {
	CommonDrawNonePostEffect();
	auto MagicShop = MagicShop::GetInstance();
	MagicShop->Draw();

}
