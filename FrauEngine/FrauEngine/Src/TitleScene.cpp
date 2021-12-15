
#include "TitleScene.h"


#include <cmath>
//ロード前のデータロード　マルチスレッドで使うデータなどの初期化
void TitleScene::LoadFrontLoad() {
	//loading.Reset();
}
//ロード中の処理
void TitleScene::LoadInUpdata() {
	//loading.Updata();
}
void TitleScene::LoadInDraw() {
	//loading.Draw();
}

void TitleScene::StaticLoad() {
	////シェーダーロード　プログラマブルにシーンに飛ぶ時用にここに記述
	//LoadShader("vs", shader::VS, "../x64/Debug/VertexShader.cso");
	//LoadShader("vsAnime", shader::VS, "../x64/Debug/VertexShader_Anime.cso");
	//LoadShader("gs", shader::GS, "../x64/Debug/GeometryShader.cso");
	//LoadShader("ps", shader::PS, "../x64/Debug/PixelShader.cso");


	titleFront.SetResource(resource->LoadIm("Data/Image/Title/TitleFront.png"));
	titleFront.SetAll(Vector2(960, 540), Vector2(1, 1), 0, 1);

	titleBack.SetResource(resource->LoadIm("Data/Image/Title/TitleBack.png"));
	titleBack.SetAll(Vector2(960, 540), Vector2(1, 1), 0, 1);

	titleCursor.SetResource(resource->LoadIm("Data/Image/Title/TitleCursor.png"));

	titleStr[0].SetResource(resource->LoadIm("Data/Image/Title/StartStr.png"));
	titleStr[1].SetResource(resource->LoadIm("Data/Image/Title/GallaryStr.png"));
	titleStr[2].SetResource(resource->LoadIm("Data/Image/Title/OptionStr.png"));
	titleStr[3].SetResource(resource->LoadIm("Data/Image/Title/ExitStr.png"));

	fade.SetResource(resource->LoadIm("Data/Image/Global/WhiteTex.png"));
}
void TitleScene::Load() {

	fade.Reset();

	fadeOn = false;
	sceneMove = false;

}
void TitleScene::UnLoad() {
}

void TitleScene::Updata() {


	//選択肢文字画像の位置設定
	float hitSelect = false;
	if (fadeOn == false) {
		for (int i = 0; i < (int)TitleStr::MAX; i++) {

			Vector2 pos = Vector2(std::lerp((float)strImageMoveStartX, (float)strImageMoveEndX, strImageLerp[i]), strImageStartY + strImageDistY * i);
			titleStr[i].SetAll(pos);

			//マウスによる選択
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
		fadeOn = true;
	}
	if (sceneMove) {
		switch (cursorNum) {
		case (int)TitleStr::START:
			LoadScene("FlowerShop");
			break;
		case (int)TitleStr::GALLARY:

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

	titleBack.Draw();
	
	titleFront.Draw();

	titleCursor.Draw();

	for (int i = 0; i < (int)TitleStr::MAX; i++) {
		titleStr[i].Draw();
	}

}
void TitleScene::DrawNonePostEffect() {
	if (fadeOn) {
		sceneMove = fade.DrawFadeIn(60, 10);
	}
}

