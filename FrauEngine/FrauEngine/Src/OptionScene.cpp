
#include "OptionScene.h"

//ロード前のデータロード　マルチスレッドで使うデータなどの初期化
void OptionScene::LoadFrontLoad() {
	Loading::GetInstance()->Reset();
}
//ロード中の処理
void OptionScene::LoadInUpdate() {
	Loading::GetInstance()->Updata();
}
void OptionScene::LoadInDraw() {
	Loading::GetInstance()->Draw();
}

void OptionScene::StaticLoad() {

}


void OptionScene::Load() {
	//リソース取得
	auto backButtonI=resource->LoadIm("Data/Image/Option/OptionBackButton.png");
	auto barI=resource->LoadIm("Data/Image/Option/OptionBar.png");
	auto baseI =resource->LoadIm("Data/Image/Option/OptionBase.png");
	auto miniButtonI=resource->LoadIm("Data/Image/Option/OptionMiniButton.png");

	backButton.SetResource(backButtonI);
	base.SetResource(baseI);
	for (int i = 0; i < 3; i++) {
		bar[i].SetResource(barI);
		miniButton[i].SetResource(miniButtonI);
	}


	//画像情報設定
	backButton.SetAll(Vector2(350, 900));
	base.SetAll(Vector2(960, 540));


	
	for (int i = 0; i < 3; i++) {
		bar[i].SetAll(Vector2(1450, 730 + i * 90));
	}
	int barWidth = bar[0].GetWidth();
	barLeftX = bar[0].GetPos().X - bar[0].GetWidth() / 2.0f;
	barRightX = bar[0].GetPos().X + bar[0].GetWidth() / 2.0f;

	for (int i = 0; i < 3; i++) {
		
		miniButton[i].SetAll(Vector2(barLeftX +barWidth*volumes[i], 730 +  i  * 90));
	}

}
void OptionScene::UnLoad() {
	resource->UnLoadIm("OptionBackButton.png");
	resource->UnLoadIm("OptionBar.png");
	resource->UnLoadIm("OptionBase.png");
	resource->UnLoadIm("OptionMiniButton.png");
}

void OptionScene::Update() {
	auto sound = SoundManager::GetInstance();
	sound->GetBGM(SoundList_BGM::TITLE)->Play();

	if (mouse->left == 1) {
		sound->GetSE(SoundList_SE::ENTER)->Play();
	}




	for (int i = 0; i < 3; i++) {
		if ((bar[i].Hit(mouse->x, mouse->y)|| miniButton[i].Hit(mouse->x, mouse->y)) && mouse->left > 0) {

			miniButton[i].SetPos(Vector2(mouse->x, miniButton[i].GetPos().Y));

			//マウスの速度でバーを飛び出したときの修正
			if (miniButton[i].GetPos().X >= barRightX) {
				miniButton[i].SetPos(Vector2(barRightX, miniButton[i].GetPos().Y));
			}
			if (miniButton[i].GetPos().X <= barLeftX) {
				miniButton[i].SetPos(Vector2(barLeftX, miniButton[i].GetPos().Y));
			}

			//0の割り算を阻止しつつ画像の位置からボリュームを計算
			if (miniButton[i].GetPos().X - barLeftX <= 0) {
				volumes[i] = 0;
			}
			else {
				volumes[i] = (float)(miniButton[i].GetPos().X - barLeftX) / (float)(barRightX - barLeftX) ;
			}

		}
	}
	sound->SetVolumeBGM(volumes[0] * volumes[1]);
	sound->SetVolumeSE(volumes[0] * volumes[2]);

	if (backButton.Hit(mouse->x, mouse->y)&&mouse->left==1) {
		LoadScene("Title");
	}

}

void OptionScene::Draw() {
	auto app = Application::GetInstance();



}
void OptionScene::DrawNonePostEffect() {

	base.Draw();

	backButton.Draw();
	for (int i = 0; i < 3; i++) {
		bar[i].Draw();
		miniButton[i].Draw();
	}

	

}

