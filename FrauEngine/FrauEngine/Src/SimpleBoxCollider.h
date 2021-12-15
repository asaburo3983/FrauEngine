#pragma once
#include "Object.h"

class SimpleBoxCollider2D {
 private:
	 Vector2 pos;
	 Vector2 scale;

	 Vector2 point[2];
public:
	SimpleBoxCollider2D();
	SimpleBoxCollider2D(Vector2 _pos, Vector2 _scale);
	void Setup(Vector2 _pos, Vector2 _scale);
	bool HitX(float _posX);
	bool HitY(float _posY);
	bool Hit(Vector2 _pos);

};