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

	
	//�V�i���I�e�L�X�g�֘A
	struct ScenarioData {

		std::unordered_map<std::string, int> ecpression;

		const string FRAU_NORMAL =		"�t���E�Q�ӂ�";
		const string FRAU_SMILE =		"�t���E�Q������";
		const string FRAU_SURPRISE =	"�t���E�Q�т�����";
		const string FRAU_TROUBLE =		"�t���E�Q���܂�";

		const string CHRISTA_NORMAL =	"�N���X�^�Q�ӂ�";
		const string CHRISTA_SMILE =	"�N���X�^�Q������";
		const string CHRISTA_SURPRISE = "�N���X�^�Q�т�����";
		const string CHRISTA_TROUBLE =	"�N���X�^�Q���܂�";

		const string HANDY_NORMAL =		"�n���f�B�Q�ӂ�";
		const string HANDY_SMILE =		"�n���f�B�Q������";
		const string HANDY_SURPRISE =	"�n���f�B�Q�т�����";
		const string HANDY_TROUBLE =	"�n���f�B�Q���܂�";


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

	//�����G�֘A
	const float charaAlphaSpeed = 0.05f;
	float charaAlpha[2] = {0,0};
	const float charaPosDistX = 100;
	const float charaScale = 0.5f;
	const Vector2 charaPos[2] = { Vector2(960 - 600,800),Vector2(960 + 600,800) };
	ImageObject chara[12];

	//�m�x������UI�֘A
	int count = 0;			//�m�x�����n�܂��Ă���̃J�E���g
	const int countMax = 30;
	float alphaUI = 0.0f;	//�m�x��UI��A�l
	ImageObject textBase;
	ImageObject frame[2];

	
};