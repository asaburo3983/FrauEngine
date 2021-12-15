#include "Fade.h"

using namespace frauEngine;

void Fade::Reset() {
	fadeCount = -1;
}
bool Fade::DrawFadeIn(int countMax, float imageSize) {

	if (fadeCount == -1) {
		fadeCount = countMax;
	}

	image->Draw(960, 540, imageSize, imageSize, 0, (float)countMax / fadeCount - 1);

	if (fadeCount > 2) {
		fadeCount--;
	}
	else {
		return false;
	}
	return true;
}
bool Fade::DrawFadeOut(int countMax,float imageSize) {
	if (fadeCount == -1) {
		fadeCount = 0;
	}

	image->Draw(960, 540, imageSize, imageSize, 0, (float)countMax / fadeCount - 1);

	if (fadeCount < countMax) {
		fadeCount++;
	}
	else {
		return false;
	}
	return true;
	
}

