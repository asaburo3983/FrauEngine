#pragma once
#include "Application.h"
#include "Objects.h"
#include "Item.h"
#include "EventManager.h"

using namespace frauEngine;

class NormalUI {
public:
	static NormalUI* GetInstance() {
		static NormalUI n;
		return &n;
	}
	void Initialize();
	void Update();
	void Draw();
private:

	ImageObject dayBase;
	
	ImageObject itemBase;
	ImageObject itemLine[7];
	ImageObject manualBase;
	ImageObject selectFrame;
	ImageObject rightArrow;
	ImageObject leftArrow;

	ImageObject moneyBase;

	ImageObject items[19];


	//インベントリ描画で必要
	bool inventory = false;
	float inventoryAlpha = 0.0f;
	const float inventoryAlphaSpeed = 0.05f;
	int selectItemNum = 0;
	int page = 1;
};