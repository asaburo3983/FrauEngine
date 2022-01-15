#pragma once
#include "Application.h"
#include "Objects.h"
#include "EventManager.h"
#include "PlanterSystem.h"
using namespace frauEngine;

class NextDay {
private:
	

	const std::string str = "¡“ú‚Ì€”õ‚ğI‚¦‚ÄŸ‚Ì“ú‚Éi‚İ‚Ü‚·‚©H";

	ImageObject base;
	ImageObject yes;
	ImageObject no;
	ImageObject morningBase;

	bool processEnable = false;
	bool enable = false;
	float fade = 0.0f;
	const float fadeSpeed = 0.05f;

	bool night = false;
	float nightAlpha = 0.0f;

	bool morning = false;
	float morningAlpha = 0.0f;
public:
	static NextDay* GetInstance() {
		static NextDay ev;
		return &ev;
	}

	void SetEnable(bool _enable) { 
		enable = _enable; 
		if (enable)
			processEnable = true;
	}
	void SetMorning(bool _enable) { morning = _enable; }

	void Initialize();
	void Update();
	void Draw();
	void DrawCheck();
	void DrawMorning();
	float GetFade() { return nightAlpha; }
	bool GetProcessEnable() { return processEnable; }
};