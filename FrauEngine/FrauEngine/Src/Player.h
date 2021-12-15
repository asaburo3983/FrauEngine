#pragma once
#include "ModelExtendObject.h"
#include "SimpleBoxCollider.h"
#include "SimpleCircleCollider.h"

using namespace frauEngine;

class Player {

private:
	KeyInput* KEY;
	ModelExtendObject* resource;
	Vector3 posOld;

	int eventNum = 0;
public:
	static Player* GetInstance() {
		static Player player;
		return &player;
	}
	Player();
	void Setup(ModelExtendObject* _resource);
	void AnimationControl();
	void Move(float _moveSpeed, float _rotaSpeed);
	void Collision(vector<SimpleBoxCollider2D> _boxCollider, vector<SimpleCircleCollider2D> _circleCollider, vector<SimpleBoxCollider2D> _boxColliderEvent);
	void DrawShadow();
	void Draw();

	
	Vector3 GetPos();
	Vector3 GetPosOld();
	int GetEventNum();

private:
	void MoveBackX();
	void MoveBackZ();

};
