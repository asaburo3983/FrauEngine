#include "EventManager.h"


void EventManager::Initialize() {
	days = 1;

	fade = false;
	fadeSpeed = 0.05f;
	fadeCount = 0.0f;
}
void EventManager::StartDays() {
	//日にちが変わった時だけに発生するイベント
	Player* player = Player::GetInstance();
	NovelSystem* novelSystem = NovelSystem::GetInstance();
	CameraWork* camera = CameraWork::GetInstance();
	auto item = Item::GetInstance();

	switch (days) {
	case 1:
		player->SetPos(Vector3(4.5, -3.9, 5.0));
		novelSystem->SetEnable(true, 0);
		camera->SetMoveNum(1);
		item->AddItem("マジックプランター", 1);//追加
		break;
	case 2:
		novelSystem->EndNovel();
		break;
	}
	
	isStartDays = false;
}
void EventManager::EndDays() {
	days++;
}
void EventManager::FieldEvent() {
	Player* player = Player::GetInstance();
	Stage* stage = Stage::GetInstance();
	auto mouse = MouseInput::GetInstance();
	auto handyShop = HandyShop::GetInstance();
	auto magicShop = MagicShop::GetInstance();
	auto palnterSystem = PlanterSystem::GetInstance();

	int eventNum = player->GetEventNum();

	//イベント入力処理
	if (mouse->left == 1 && eventNum != -1) {
		
		switch (eventNum) {
		//移動イベント用のフェード
		case (int)EventNum::EXIT:
		case (int)EventNum::JOIN_FLOWERSHOP:
		case (int)EventNum::JOIN_HANDYSHOP:
		case (int)EventNum::JOIN_MAGICSHOP:
			fade = true;
			break;
		case (int)EventNum::PLANTER:
			palnterSystem->SetEnable(true);
			break;
		case (int)EventNum::OPEN_SHOP:
			break;
		case (int)EventNum::BUY_HANDYSHOP:
			if (handyShop->GetEnable() == false) {
				handyShop->SetEnable(true);
			}
			break;
		case (int)EventNum::BUY_MAGICSHOP:
			if (magicShop->GetEnable() == false) {
				magicShop->SetEnable(true);
			}
			break;
		}
	}
	
	//フェード処理
	if (fade) {
		if (fadeCount <1.0f) {
			fadeCount += fadeSpeed;
		}
		player->IsMove(false);
	}
	else {
		if (fadeCount > 0) {
			fadeCount -= fadeSpeed; 
		}
	}
	//フェードが真っ暗な時の処理
	if (fadeCount >= 1.0f) {
		fade = false;
		player->IsMove(true);
		switch (eventNum) {
			//これはシーン移動の処理にしてしまう
		case (int)EventNum::EXIT:
			
			scene->LoadScene("Map");
			stage->MoveStage((int)StageNum::MAP);
			break;
		case (int)EventNum::JOIN_FLOWERSHOP:
			
			scene->LoadScene("FlowerShop");
			stage->MoveStage((int)StageNum::FLOWER_SHOP);
			break;
		case (int)EventNum::JOIN_HANDYSHOP:
			scene->LoadScene("HandyShop");
			stage->MoveStage((int)StageNum::HANDY_SHOP);
			break;
		case (int)EventNum::JOIN_MAGICSHOP:
			scene->LoadScene("MagicShop");
			stage->MoveStage((int)StageNum::MAGIC_SHOP);
			break;
		}
	}

}

void EventManager::Update() {
	CameraWork* camera = CameraWork::GetInstance();
	NovelSystem* novelSystem = NovelSystem::GetInstance();
	TutorialSystem* tutorialSystem = TutorialSystem::GetInstance();
	Stage* stage = Stage::GetInstance();

	bool events = true;
	if (events) {
		if (isStartDays) {
			StartDays();
		}
		switch (days) {
		case 1:
			//ノベルが終了していて０番のチュートリアルが１度も行われていないとき０番のチュートリアルを行う
			if (novelSystem->GetEnable() == false && tutorialSystem->GetUsed(0) == false) {
				tutorialSystem->SetEnable(true, 0);
			}
			break;
		}
	}
	
	FieldEvent();

	//マップの時のみカメラは追従させる
	if (stage->GetStageNum() == (int)StageNum::MAP) {
		camera->SetPlayerTarget(true);
	}
	else {
		camera->SetPlayerTarget(false);
	}

}