#pragma once
#include "Application.h"

#include "Objects.h"


#include "Player.h"
#include "NovelSystem.h"
#include "TutorialSystem.h"

#include "CameraWork.h"
#include "Stage.h"
#include "HandyShop.h"
#include "MagicShop.h"
#include "Item.h"
#include "PlanterSystem.h"

class EventManager {
public:
	static EventManager* GetInstance() {
		static EventManager ev;
		return &ev;
	}
	EventManager() {
		days = 1;

		fade = false;
		fadeSpeed = 0.05f;
		fadeCount = 0.0f;
	}
	void SetScene(Scene* _scene) { scene = _scene; }
	void Initialize();

	void Update();

	int GetDays() { return days; }

	void StartDays();
	void EndDays();

	float GetFadeCount() { return fadeCount; }
private:
	void FieldEvent();
	
private:
	Scene* scene;

	bool isStartDays = true;
	int days = 1;

	bool fade = false;
	float fadeSpeed = 0.05f;
	float fadeCount = 0.0f;
};