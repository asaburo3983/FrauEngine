#include "EventManager.h"


void EventManager::Initialize() {
	days = 1;

	fade = false;
	fadeSpeed = 0.05f;
	fadeCount = 0.0f;
}
void EventManager::StartDays() {
	//���ɂ����ς�����������ɔ�������C�x���g
	Player* player = Player::GetInstance();
	NovelSystem* novelSystem = NovelSystem::GetInstance();
	CameraWork* camera = CameraWork::GetInstance();
	auto item = Item::GetInstance();

	switch (days) {
	case 1:
		player->SetPos(Vector3(4.5, -3.9, 5.0));
		novelSystem->SetEnable(true, 0);
		camera->SetMoveNum(1);
		item->AddItem("�}�W�b�N�v�����^�[", 1);//�ǉ�
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

	//�C�x���g���͏���
	if (mouse->left == 1 && eventNum != -1) {
		
		switch (eventNum) {
		//�ړ��C�x���g�p�̃t�F�[�h
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
	
	//�t�F�[�h����
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
	//�t�F�[�h���^���ÂȎ��̏���
	if (fadeCount >= 1.0f) {
		fade = false;
		player->IsMove(true);
		switch (eventNum) {
			//����̓V�[���ړ��̏����ɂ��Ă��܂�
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
			//�m�x�����I�����Ă��ĂO�Ԃ̃`���[�g���A�����P�x���s���Ă��Ȃ��Ƃ��O�Ԃ̃`���[�g���A�����s��
			if (novelSystem->GetEnable() == false && tutorialSystem->GetUsed(0) == false) {
				tutorialSystem->SetEnable(true, 0);
			}
			break;
		}
	}
	
	FieldEvent();

	//�}�b�v�̎��̂݃J�����͒Ǐ]������
	if (stage->GetStageNum() == (int)StageNum::MAP) {
		camera->SetPlayerTarget(true);
	}
	else {
		camera->SetPlayerTarget(false);
	}

}