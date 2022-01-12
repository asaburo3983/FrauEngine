#pragma once
#include "Application.h"
#include "Objects.h"
#include "Item.h"
#include "EventManager.h"

using namespace frauEngine;

class PlanterSystem {
public:
	static PlanterSystem* GetInstance() {
		static PlanterSystem n;
		return &n;
	}
	void Reset();
	void SetEnable(bool _enable);
	void Initialize();
	void Update();
	void Draw();
	int GetSetItem(int _num) {
		return planterSetItem[_num];
	}
private:

	bool enable = false;
	float alpha = 0.0f;
	const float alphaSpeed = 0.05f;
	int selectItemNum = 0;
	int page = 1;

	ImageObject itemBase;
	ImageObject itemBaseLine[7];
	ImageObject selectFrame;
	ImageObject rightArrow;
	ImageObject leftArrow;

	ImageObject manualBase[3];
	ImageObject items[3][12];

	int planterSetItem[3] = { -1,-1,-1 };

	int bug[3] = { 0,0,0 };//���ۂ̈琬���s��
	int bugFixSum = 0;//�琬���s���h�~�i���v�j
	int bugFix[3] = { 0,0,0 };//�琬���s���h�~�i�ʁj
	int bugSurface[3] = { 0,0,0 };//�琬���s���i�`��p�j

}; 