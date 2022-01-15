#include "NextDay.h"


void NextDay::Initialize() {

	auto rc = Resource::GetInstance();

	base.SetResource(rc->Image("MoneyBase.png"));
	base.SetAll(Vector2(960, 540), Vector2(2, 5));
	
	morningBase.SetResource(rc->Image("MoneyBase.png"));
	morningBase.SetAll(Vector2(960, 540), Vector2(2, 8));

	Vector2 dist(160, 100);
	Vector2 buttonScale(0.7, 1);

	yes.SetResource(rc->Image("MoneyBase.png"));
	yes.SetAll(Vector2(960-dist.X, 540+dist.Y), buttonScale);

	no.SetResource(rc->Image("MoneyBase.png"));
	no.SetAll(Vector2(960 + dist.X, 540 + dist.Y), buttonScale);


}
void NextDay::Update() {
	auto mouse = MouseInput::GetInstance();
	auto eventManager = EventManager::GetInstance();
	auto planterSystem = PlanterSystem::GetInstance();

	//�m�F�p�̏���
	if (enable) {
		if (fade < 1) {
			fade += fadeSpeed;
		}
		if (mouse->left == 1) {
			if (yes.Hit(mouse->x, mouse->y)) {
				night = true;
				SetEnable(false);
			}
			if (no.Hit(mouse->x, mouse->y)) {
				SetEnable(false);
				processEnable = false;
			}
		}
	}
	else {
		if (fade > 0) {
			fade -= fadeSpeed;
		}
	}
	//���̓��ɍs���t�F�[�h		�����t�F�[�h
	if (night) {
		if (nightAlpha < 1) {
			nightAlpha += fadeSpeed;
		}
		else {
			night = false;
			morning = true;
			
			eventManager->AddDays();

			//���z�̑����������s��
			//�A�C�e���̏�����s��
			//��z������̐������s��
			planterSystem->SeedGrow();

		}
	}
	else {
		if (nightAlpha > 0) {
			nightAlpha -= fadeSpeed;
		}
	}
	//���̓��̏��߂̏���
	if (morning) {
		if (mouse->left == 1) {
			morning = false;
			eventManager->EndDays();

			//�v�����^�[�̒��g���k�ɂ���
			planterSystem->Reset();
			processEnable = false;//���ׂĂ̏������I��
		}
		if (morningAlpha < 1) {
			morningAlpha += fadeSpeed;
		}
	}
	else {
		if (morningAlpha > 0) {
			morningAlpha -= fadeSpeed;
		}
	}

	base.SetAlpha(fade);
	yes.SetAlpha(fade);
	no.SetAlpha(fade);

}

void NextDay::Draw() {
	DrawCheck();
	DrawMorning();
}
void NextDay::DrawCheck() {
	if (fade <= 0) {
		return;
	}

	auto akazukin = Fonts::GetInstance()->GetFont((int)FontList::AKAZUKIN);
	auto meirio = Fonts::GetInstance()->GetFont((int)FontList::MEIRIO);

	base.Draw();
	yes.Draw();
	no.Draw();
	Vector2 manualStrPos = base.GetPosLerp(Vector2(0.4, 0.2));
	akazukin->DrawString(str, manualStrPos, 2, Color(63, 41, 20, fade), true);

	akazukin->DrawString("�͂�", Vector2(yes.GetPos().X-15, yes.GetPos().Y-10), 2.5, Color(63, 41, 20, fade), true);
	akazukin->DrawString("������", Vector2(no.GetPos().X - 15, no.GetPos().Y-10), 2.5, Color(63, 41, 20, fade), true);
	
}
void NextDay::DrawMorning() {
	if (morningAlpha <= 0) {
		return;
	}
	auto item = Item::GetInstance();
	auto planterSystem = PlanterSystem::GetInstance();
	auto akazukin = Fonts::GetInstance()->GetFont((int)FontList::AKAZUKIN);
	auto meirio = Fonts::GetInstance()->GetFont((int)FontList::MEIRIO);

	Color strColor = Color(63, 41, 20, morningAlpha);
	//�x�[�X�̕`��i�C���[�W
	morningBase.SetAlpha(morningAlpha);
	morningBase.Draw();

	//�{���̐���(������
	Vector2 manualStrPos = morningBase.GetPosLerp(Vector2(0.5, 0.2));
	akazukin->DrawString("�{���̐��ʁI", manualStrPos, 3, Color(63, 41, 20, morningAlpha), true);
	//��{����
	Vector2 standardMoneyStrPos = morningBase.GetPosLerp(Vector2(0.4, 0.25));
	meirio->DrawString("��{����:100���E",standardMoneyStrPos, 1.7, strColor,true);
	//
	Vector2 matiTitlePos = morningBase.GetPosLerp(Vector2(0.4, 0.6));
	meirio->DrawString("�Ԃ���Ƃꂽ��", matiTitlePos, 1.7, strColor, true);
	//�琬�ہi������
	for (int i = 0; i < item->GetItemNum("�}�W�b�N�v�����^�["); i++) {
		int setItem = planterSystem->GetSetItem(i);
		if (setItem == -1) {
			continue;
		}
		bool seedGrow = planterSystem->GetGrouSeedEnable(setItem);
		string matingSeedStr = "";
		if (planterSystem->GetMatingSeed(i) != -1) {
			matingSeedStr = item->GetItemName(planterSystem->GetMatingSeed(i));
		}


		Vector2 seedNamePos = morningBase.GetPosLerp(Vector2(0.1,  0.4+(i*0.05)));
		Vector2 seedGrowPos = morningBase.GetPosLerp(Vector2(0.4,  0.4+(i*0.05)));
		Vector2 seedMoneyPos = morningBase.GetPosLerp(Vector2(0.65, 0.4+(i*0.05)));

		float strScale = 1.5f;
		//������///////////////////////
		//�琬������
		string setSeedStr = item->GetItemName(setItem);
		meirio->DrawString(setSeedStr, seedNamePos, strScale, strColor);
		//����or���s
		string growStr = "�琬���s";
		if (seedGrow) {
			growStr = "�琬�����I";
		}
		meirio->DrawString(growStr,seedGrowPos, strScale, strColor);
		//�킲�Ƃ̎���
		char moneyStr[50] = "0���E";
		if (seedGrow) {
			sprintf_s(moneyStr,"%d���E", item->GetSell(setItem));
		}
		meirio->DrawString(moneyStr, seedMoneyPos, strScale, strColor);
		/////////////////////////////////
		
		//��z�ŃQ�b�g������
		//������///////////////
		
		Vector2 matiSeedPos = morningBase.GetPosLerp(Vector2(0.4, 0.7+i*0.05));
		meirio->DrawString(matingSeedStr, matiSeedPos, strScale, strColor);
		///////////////////////
	}
	
	
	

}