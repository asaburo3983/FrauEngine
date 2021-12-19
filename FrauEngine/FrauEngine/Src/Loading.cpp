#include "Loading.h"

using namespace frauEngine;

void Loading::Reset() {
	animeNum = 0;
	animeCount = 0;
	dist = 200;
	posX = -dist;
	
	while (grass.size() > 0) {
		grass.pop_back();
	}

	fade.Reset();
}

void Loading::Updata() {
	const int speed = 5;
	const int posXMax = 1920+dist;

	//キャラの位置を移動
	posX += speed;
	if (posX > posXMax) {
		posX = -dist;
	}

	//アニメーションの変異
	int animChangeF = 7;
	
	if (animeCount % animChangeF == 0) {
		if (animeCount >= animChangeF * 8) {
			animeCount = 0;
		}
		if (animeCount >= animChangeF * 4) {
			animeNum--;
		}
		else {
			animeNum++;
		}
	}
	animeCount++;

	//草を発生させる
	int grassPushF = 45;
	if (animeCount % grassPushF == 0) {
		grass.push_back(posX);
	}

}


void Loading::Draw() {
	Resource* rc = Resource::GetInstance();
	frontAlpha++;

	if (frontAlpha > 100) {
		frontAlpha = 0;
	}
	//背景
	rc->Image("LoadBack")->Draw(960, 540);
	rc->Image("LoadFront")->Draw(960, 540, 1, 1, 0, (float)frontAlpha / 100.0f);


	//草
	for (int i = 0; i < grass.size(); i++) {
		rc->Image("LoadGrass")->Draw(grass[i], 670);
	}

	//アニメ
	ostringstream animeStr;
	animeStr << "LoadAnime"  << animeNum ;
	string str = animeStr.str();
	rc->Image(str)->Draw(posX, 570, 0.6, 0.6, 0, 1, true);


	//fade.DrawFadeOut(120, 10);

}