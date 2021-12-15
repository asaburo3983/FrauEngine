#pragma once

#include "Application.h"
#include "Fade.h"
class Loading {
private:
	int animeNum = 0;
	int animeCount = 0;
	int posX = 0;
	int dist = 200;
	std::vector<int> grass;

	Fade fade;

	int frontAlpha = 0;
public:
	void Reset();
	void Updata();
	void Draw();
};