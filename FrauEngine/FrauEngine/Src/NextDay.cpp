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

	//確認用の処理
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
	//次の日に行くフェード		黒いフェード
	if (night) {
		if (nightAlpha < 1) {
			nightAlpha += fadeSpeed;
		}
		else {
			night = false;
			morning = true;
			
			eventManager->AddDays();

			//金額の増加処理を行う
			//アイテムの消費を行う
			//交配した種の生成を行う
			planterSystem->SeedGrow();

		}
	}
	else {
		if (nightAlpha > 0) {
			nightAlpha -= fadeSpeed;
		}
	}
	//次の日の初めの処理
	if (morning) {
		if (mouse->left == 1) {
			morning = false;
			eventManager->EndDays();

			//プランターの中身を殻にする
			planterSystem->Reset();
			processEnable = false;//すべての処理が終了
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

	akazukin->DrawString("はい", Vector2(yes.GetPos().X-15, yes.GetPos().Y-10), 2.5, Color(63, 41, 20, fade), true);
	akazukin->DrawString("いいえ", Vector2(no.GetPos().X - 15, no.GetPos().Y-10), 2.5, Color(63, 41, 20, fade), true);
	
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
	//ベースの描画（イメージ
	morningBase.SetAlpha(morningAlpha);
	morningBase.Draw();

	//本日の成果(文字列
	Vector2 manualStrPos = morningBase.GetPosLerp(Vector2(0.5, 0.2));
	akazukin->DrawString("本日の成果！", manualStrPos, 3, Color(63, 41, 20, morningAlpha), true);
	//基本収入
	Vector2 standardMoneyStrPos = morningBase.GetPosLerp(Vector2(0.4, 0.25));
	meirio->DrawString("基本収入:100ラウ",standardMoneyStrPos, 1.7, strColor,true);
	//
	Vector2 matiTitlePos = morningBase.GetPosLerp(Vector2(0.4, 0.6));
	meirio->DrawString("花からとれた種", matiTitlePos, 1.7, strColor, true);
	//育成可否（文字列
	for (int i = 0; i < item->GetItemNum("マジックプランター"); i++) {
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
		//同じ列///////////////////////
		//育成した種
		string setSeedStr = item->GetItemName(setItem);
		meirio->DrawString(setSeedStr, seedNamePos, strScale, strColor);
		//成功or失敗
		string growStr = "育成失敗";
		if (seedGrow) {
			growStr = "育成成功！";
		}
		meirio->DrawString(growStr,seedGrowPos, strScale, strColor);
		//種ごとの収入
		char moneyStr[50] = "0ラウ";
		if (seedGrow) {
			sprintf_s(moneyStr,"%dラウ", item->GetSell(setItem));
		}
		meirio->DrawString(moneyStr, seedMoneyPos, strScale, strColor);
		/////////////////////////////////
		
		//交配でゲットした種
		//同じ列///////////////
		
		Vector2 matiSeedPos = morningBase.GetPosLerp(Vector2(0.4, 0.7+i*0.05));
		meirio->DrawString(matingSeedStr, matiSeedPos, strScale, strColor);
		///////////////////////
	}
	
	
	

}