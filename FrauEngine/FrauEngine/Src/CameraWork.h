#pragma once

#include "CameraObject.h"
using namespace frauEngine;

class CameraWork {
private:
	CameraObject* resource;

	Vector3 pos;
	
public:
	void Setup(CameraObject* _resource);
	void Move(Vector3 _stopPos, Vector3 _speed);
	void Updata();

};