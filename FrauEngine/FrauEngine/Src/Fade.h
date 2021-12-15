#pragma once

#include "ImageObject.h"

using namespace frauEngine;

class Fade {
private:
	int fadeCount = -1;
	Image2D* image;
public:
	void Reset();
	void SetResource(Image2D* _image) { image = _image; }
	bool DrawFadeIn(int countMax, float imageSize);
	bool DrawFadeOut(int countMax, float imageSize);

};