#pragma once

#include "SimpleBoxCollider.h"
#include "SimpleCircleCollider.h"
#include "SlopeCollider.h"

#include "Player.h"
#include "LightsObject.h"
#include "Item.h"
using namespace frauEngine;

enum class NPCNum {
	HANDY,
	CHRISTA,
	MAX
};
enum class StageNum {
	FLOWER_SHOP,
	HANDY_SHOP,
	MAGIC_SHOP,
	MAP,
	MAX,
};
enum class EventNum {
	EXIT,
	PLANTER,
	OPEN_SHOP,
	BUY_HANDYSHOP,
	BUY_MAGICSHOP,
	JOIN_FLOWERSHOP,
	JOIN_HANDYSHOP,
	JOIN_MAGICSHOP,

	MAX
};
class Stage {
public:
	static Stage* GetInstance() {
		static Stage collisions;
		return &collisions;
	}

	std::vector<SimpleBoxCollider2D> boxCollider;
	std::vector<SimpleCircleCollider2D> circleCollider;
	std::vector<SimpleBoxCollider2D> boxColliderEvent;
	std::vector<SlopeCollider> slopeCollider;

	
private:
	ModelExtendObject	  model;

	ModelExtendObject	  npc;

	ModelObject skyModel;
	ModelObject waterModel;
	
	ModelObject planterModel[3];

	LightsObject		  light;
	DirectionalLightParam directionalLightParam ;
	PointLightParam		  pointLightParam[POINT_LIGHT];
	SpotLightParam		  spotLightParam[SPOT_LIGHT];

	int stageNumOld = 0;
	int stageNum;
public:
	void Initialize();
	void Load(StageNum _stageNum);
	void MoveStage(int _stageNum);
	int GetStageNum() { return stageNum; }
	int GetStageNumOld() { return stageNumOld; }
	void Update();
	void Draw();
	void DrawShadow();

	LightsObject* GetLight() { return &light; }
	ModelObject* GetStageModel() { return &model; }
private:
	int boxColliderMax = 0;
	int circleColliderMax = 0;
	int boxEventColliderMax = 0;
	int slopeColliderMax = 0;

	void SetCollisionSize(int _box, int _circle, int _event,int _slope);
	void SetStageCollisions();
	void SetLights();
	void ResetCollision();
};