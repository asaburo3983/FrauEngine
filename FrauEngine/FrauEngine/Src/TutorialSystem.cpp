#include "TutorialSystem.h"


void TutorialSystem::Initialize() {
	auto resource = Resource::GetInstance();
	csv[0].LoadCSV("Data/Tutorial/Tutorial_BasicOperation.csv");
	
	frame.SetResource(resource->Image("TutorialFrame.png"));

	return;
	//TODO チュートリアルの挿絵を用意

}
void TutorialSystem::SetEnable(bool _enable, int _num) {
	enable = _enable;
	num = _num;
	page = 1;
	LoadPage(text);
	used[num] = true;
}
void TutorialSystem::LoadPage(string* strs) {
	for (int i = 0; i < ROW_MAX; i++) {
		strs[i] = csv[num].GetString(page, i);
	}
}
void TutorialSystem::TurnPage() {
	MouseInput* mouse = MouseInput::GetInstance();
	//ページめくり処理
	if (mouse->left == 1) {
		//Page変数が加算されない
		LoadPage(textOld);
		page++;

		if (csv[num].GetRowMax() <= page) {
			
			SetEnable(false);
		}
		else {
			LoadPage(text);
		}
	}
	if (mouse->right == 1 && page > 1) {
		page--;
		LoadPage(text);
	}
}
void TutorialSystem::Update() {
	
	
	if (enable) {
		if (alpha < 1.0f) {
			alpha += alphaSpeed;
		}
		TurnPage();

	}
	else{
		if (alpha > 0.0f) {
			alpha -= alphaSpeed;
		}
	}

}
void TutorialSystem::Draw() {
	Font* meirio = nullptr;
	meirio = Fonts::GetInstance()->GetFont((int)FontList::MEIRIO);
	Font* akazukin = nullptr;
	akazukin = Fonts::GetInstance()->GetFont((int)FontList::AKAZUKIN);

	//画像の用意がまだなので後で
	//illust[num][page - 1].SetAll(framePos, Vector2(1, 1), 0, alpha);
	frame.SetAll(framePos, Vector2(1, 1), 0, alpha);
	frame.Draw();

	//テキスト描画
	Vector2 strPos[3];
	strPos[0].X = 530;
	for (int i = 0; i < ROW_MAX; i++) {
		float strPosDistY = 50;
		strPos[i].X = 630;
		strPos[i].Y = 730 + strPosDistY * i;
	}
	float strSize = 1.5f;
	Color strColor(63.0f / 256.0f, 41.0f / 256.0f, 20.0f / 256.0f, alpha);
	
	if (enable) {
		for (int i = 0; i < ROW_MAX; i++) {
			meirio->DrawString(text[i], strPos[i], strSize, strColor);
		}
	}
	else {
		for (int i = 0; i < ROW_MAX; i++) {
			meirio->DrawString(textOld[i], strPos[i], strSize, strColor);
		}
	}

}