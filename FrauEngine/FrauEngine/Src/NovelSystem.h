#pragma once
#include "Application.h"
#include "Objects.h"
#include "Player.h"
#include "CameraWork.h"

using namespace frauEngine;

enum class ScenarioDataName {
	CHARA_NAME,
	SCENARIO_1,
	SCENARIO_2,
	SCENARIO_3,
	ECPRESSION_LEFT,
	ECPRESSION_RIGHT,
	EFFETC,
	MAX
};

class NovelSystem {
public:
	static NovelSystem* GetInstance() {
		static NovelSystem novelSystem;
		return &novelSystem;
	}

	void Initialize();
	void SetEnable(bool _enable=true, int _scenarioNum = NULL);
	void Update();
	void Draw();

	bool GetEnable() { return enable; }
	float GetAlphaUI() { return alphaUI; };

	void EndNovel();
private:
	void InitializeScenario();

	
	void TurnPage();
	void LoadPage();

	void DrawChara();
	void DrawUI();
	void DrawScenarioText();
private:
	Resource* resource;

	bool enable = false;

	
	//シナリオテキスト関連
	struct ScenarioData {

		std::unordered_map<std::string, int> ecpression;

		const string FRAU_NORMAL =		"フラウ＿ふつう";
		const string FRAU_SMILE =		"フラウ＿えがお";
		const string FRAU_SURPRISE =	"フラウ＿びっくり";
		const string FRAU_TROUBLE =		"フラウ＿こまる";

		const string CHRISTA_NORMAL =	"クリスタ＿ふつう";
		const string CHRISTA_SMILE =	"クリスタ＿えがお";
		const string CHRISTA_SURPRISE = "クリスタ＿びっくり";
		const string CHRISTA_TROUBLE =	"クリスタ＿こまる";

		const string HANDY_NORMAL =		"ハンディ＿ふつう";
		const string HANDY_SMILE =		"ハンディ＿えがお";
		const string HANDY_SURPRISE =	"ハンディ＿びっくり";
		const string HANDY_TROUBLE =	"ハンディ＿こまる";


		vector<CSV> csv;
		int num = 0;
		int page = 1;

		int leftCharaNumOld = -1;
		int rightCharaNumOld = -1;
		int leftCharaNum  = -1;
		int rightCharaNum = -1;
		string str[(int)ScenarioDataName::MAX];

	};

	ScenarioData scenario;

	//立ち絵関連
	const float charaAlphaSpeed = 0.05f;
	float charaAlpha[2] = {0,0};
	const float charaPosDistX = 100;
	const float charaScale = 0.5f;
	const Vector2 charaPos[2] = { Vector2(960 - 600,800),Vector2(960 + 600,800) };
	ImageObject chara[12];

	//ノベル共通UI関連
	int count = 0;			//ノベルが始まってからのカウント
	const int countMax = 30;
	float alphaUI = 0.0f;	//ノベルUIのA値
	ImageObject textBase;
	ImageObject frame[2];

	
};