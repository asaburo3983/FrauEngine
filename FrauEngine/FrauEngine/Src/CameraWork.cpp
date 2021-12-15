#include "CameraWork.h"

void CameraWork::Setup(CameraObject* _resource) {
	resource = _resource;
	pos = resource->GetPos();
}
void CameraWork::Move(Vector3 _stopPos, Vector3 _speed) {
	bool plus[3] = { true,true,true };
	if (_speed.X < 0) {
		plus[0] = false;
	}
	if (_speed.Y < 0) {
		plus[1] = false;
	}
	if (_speed.Z < 0) {
		plus[2] = false;
	}
	if (plus[0]&&_stopPos.X > pos.X) {
		pos.X += _speed.X;
	}
	if (plus[1]&&_stopPos.Y > pos.Y) {
		pos.Y += _speed.Y;
	}
	if (plus[2]&&_stopPos.Z > pos.Z) {
		pos.Z += _speed.Z;
	}
	// stop -3 start-13 speed -1
	if (!plus[0]&&_stopPos.X < pos.X) {
		pos.X += _speed.X;
	}
	if (!plus[1]&&_stopPos.Y < pos.Y) {
		pos.Y += _speed.Y;
	}
	if (!plus[2]&&_stopPos.Z < pos.Z) {
		pos.Z += _speed.Z;
	}
}
void CameraWork::Updata() {
	resource->SetPos(pos);
	resource->Updata();
}

