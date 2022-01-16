
#include "TitleScene.h"

//ロード前のデータロード　マルチスレッドで使うデータなどの初期化
void TitleScene::LoadFrontLoad() {
	Loading::GetInstance()->Reset();
}
//ロード中の処理
void TitleScene::LoadInUpdate() {
	Loading::GetInstance()->Updata();
}
void TitleScene::LoadInDraw() {
	Loading::GetInstance()->Draw();
}

void TitleScene::StaticLoad() {

	CommonDataLoad();

	auto WhiteTex = resource->Image("WhiteTex.png");
	fade.SetResource(WhiteTex);
}


void TitleScene::Load() {


	//メモリ不足が起こったのでシーン内のメモリは４GBまでに抑えるため、毎回ロード、アンロードする
	auto TitleFront = resource->LoadIm("Data/Image/Title/TitleFront.png");
	auto TitleBack = resource->LoadIm("Data/Image/Title/TitleBack.png");
	auto TitleCursor = resource->LoadIm("Data/Image/Title/TitleCursor.png");
	auto StartStr = resource->LoadIm("Data/Image/Title/StartStr.png");
	auto GallaryStr = resource->LoadIm("Data/Image/Title/GallaryStr.png");
	auto OptionStr = resource->LoadIm("Data/Image/Title/OptionStr.png");
	auto ExitStr = resource->LoadIm("Data/Image/Title/ExitStr.png");

	titleFront.SetResource(TitleFront);
	titleFront.SetAll(Vector2(960, 540), Vector2(1, 1), 0, 1);

	titleBack.SetResource(TitleBack);
	titleBack.SetAll(Vector2(960, 540), Vector2(1, 1), 0, 1);

	titleCursor.SetResource(TitleCursor);
	titleStr[0].SetResource(StartStr);
	titleStr[1].SetResource(GallaryStr);
	titleStr[2].SetResource(OptionStr);
	titleStr[3].SetResource(ExitStr);

	fade.Reset();

	fadeOn = false;
	sceneMove = false;

}
void TitleScene::UnLoad() {
	resource->UnLoadIm("TitleFront.png");
	resource->UnLoadIm("TitleBack.png");
	resource->UnLoadIm("TitleCursor.png");
	resource->UnLoadIm("StartStr.png");
	resource->UnLoadIm("GallaryStr.png");
	resource->UnLoadIm("OptionStr.png");
	resource->UnLoadIm("ExitStr.png");
}

void TitleScene::Update() {
	auto sound = SoundManager::GetInstance();
	sound->GetBGM(SoundList_BGM::TITLE)->Play();

	//選択肢文字画像の位置設定
	float hitSelect = false;
	if (fadeOn == false) {
		//マウスによる選択
		for (int i = 0; i < (int)TitleStr::MAX; i++) {

			Vector2 pos = Vector2(std::lerp((float)strImageMoveStartX, (float)strImageMoveEndX, strImageLerp[i]), strImageStartY + strImageDistY * i);
			titleStr[i].SetAll(pos);
			
			if (titleStr[i].Hit(mouse->x, mouse->y)) {
				cursorNum = i;
				hitSelect = true;
			}
		}
		//選択した文字画像の移動
		for (int i = 0; i < (int)TitleStr::MAX; i++) {
			if (i == cursorNum && strImageLerp[i] < 1.0f) {
				strImageLerp[i] += strImageLerpSpeed;
			}
			else if (i != cursorNum && strImageLerp[i] > 0.0f) {
				strImageLerp[i] -= strImageLerpSpeed;
			}
		}
	}
	//カーソルの位置設定
	Vector2 cursorPos = Vector2(cursorX, strImageStartY + strImageDistY * cursorNum);
	titleCursor.SetAll(cursorPos);

	if (mouse->left && hitSelect) {
		sound->GetSE(SoundList_SE::ENTER)->Play();
		fadeOn = true;

	}
	//scene移動
	if (sceneMove) {
		sound->GetBGM(SoundList_BGM::TITLE)->Stop();
		switch (cursorNum) {
		case (int)TitleStr::START:
			LoadScene("FlowerShop");
			break;
		case (int)TitleStr::GALLARY:
			LoadScene("Gallary");
			break;
		case (int)TitleStr::OPTION:
			break;
		case (int)TitleStr::EXIT:
			gameEnd = true;
			break;
		}
	}

}
 
void TitleScene::Draw() {
	auto app = Application::GetInstance();
	

	

	titleBack.Draw();
	
	titleFront.Draw();

	titleCursor.Draw();

	for (int i = 0; i < (int)TitleStr::MAX; i++) {
		titleStr[i].Draw();
	}

	app->SetColorMulti();

	
}
void TitleScene::DrawNonePostEffect() {
	if (fadeOn) {
		sceneMove = fade.DrawFadeIn(60, 10);
	}
}

