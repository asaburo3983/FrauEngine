#pragma once
#include "Application.h"
#include "Objects.h"
#include "NovelSystem.h"

using namespace frauEngine;

enum {
	TUTORIAL_MAX = 4,
	ROW_MAX = 2,//1ページの段落の最大数
};
class TutorialSystem {
public:
	static TutorialSystem* GetInstance() {
		static TutorialSystem ts;
		return &ts;
	}
	void Initialize();
	void SetEnable(bool _enable=true, int _num=NULL);
	void Update();
	void Draw();

	float GetAlpha() { return alpha; }
	bool GetEnd(int _num) { return end[_num]; }
private:
	void LoadPage(std::string* strs);
	void TurnPage();
private:

	int num = 0;
	int page = 1;

	bool enable = false;
	bool used[TUTORIAL_MAX];
	bool end[TUTORIAL_MAX];
	CSV csv[TUTORIAL_MAX];



	float alpha = 0.0f;
	const float alphaSpeed = 0.05f;
	string title;
	string textOld[ROW_MAX];
	string text[ROW_MAX];

	const Vector2 framePos = Vector2(960, 540);
	const Vector2 illustPos = Vector2(960, 540);

	ImageObject frame;
	std::vector<ImageObject> illust[TUTORIAL_MAX];

};