
#include "TitleScene.h"


#include <cmath>
//���[�h�O�̃f�[�^���[�h�@�}���`�X���b�h�Ŏg���f�[�^�Ȃǂ̏�����
void TitleScene::LoadFrontLoad() {
	//loading.Reset();
}
//���[�h���̏���
void TitleScene::LoadInUpdata() {
	//loading.Updata();
}
void TitleScene::LoadInDraw() {
	//loading.Draw();
}

void TitleScene::StaticLoad() {
	////�V�F�[�_�[���[�h�@�v���O���}�u���ɃV�[���ɔ�Ԏ��p�ɂ����ɋL�q
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


	//�I���������摜�̈ʒu�ݒ�
	float hitSelect = false;
	if (fadeOn == false) {
		for (int i = 0; i < (int)TitleStr::MAX; i++) {

			Vector2 pos = Vector2(std::lerp((float)strImageMoveStartX, (float)strImageMoveEndX, strImageLerp[i]), strImageStartY + strImageDistY * i);
			titleStr[i].SetAll(pos);

			//�}�E�X�ɂ��I��
			if (titleStr[i].Hit(mouse->x, mouse->y)) {
				cursorNum = i;
				hitSelect = true;
			}
		}
		//�I�����������摜�̈ړ�
		for (int i = 0; i < (int)TitleStr::MAX; i++) {
			if (i == cursorNum && strImageLerp[i] < 1.0f) {
				strImageLerp[i] += strImageLerpSpeed;
			}
			else if (i != cursorNum && strImageLerp[i] > 0.0f) {
				strImageLerp[i] -= strImageLerpSpeed;
			}
		}
	}
	//�J�[�\���̈ʒu�ݒ�
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

