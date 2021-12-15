#pragma once
#include "Player.h"

#include "ImageObject.h"
using namespace frauEngine;

class EventUI {
private:
	ImageObject* base;
	ImageObject* openShopStr;
	ImageObject* planterStr;
	ImageObject* exitShopStr;
public:
	void Setup(ImageObject* _base, ImageObject* _openShopStr, ImageObject* _planterStr, ImageObject* _exitShopStr);
	void SetDrawPos();
	int Click();
	void Draw();
};