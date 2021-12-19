
#include "GallaryPlayer.h"


GallaryPlayer::GallaryPlayer() {
	KEY = KeyInput::GetInstance();
}
void GallaryPlayer::Setup(ModelExtendObject* _resource) {
	resource = _resource;

	resource->SetScale(Vector3(0.03f, 0.03f, 0.03f));
	resource->SetAngle(Vector3(0, 180, 0));
	resource->SetPos(Vector3(1, -3.9f, -2));
}

void GallaryPlayer::AnimationControl() {
	if (KEY->key[DIK_A] > 0 ||
		KEY->key[DIK_D] > 0 ||
		KEY->key[DIK_W] > 0 ||
		KEY->key[DIK_S] > 0) {
		resource->SetAnimeNum(2);
		resource->SetAnimeSpeed(0.4f);
	}
	else {
		resource->SetAnimeNum(1);
		resource->SetAnimeSpeed(0.3f);
	}
}
void GallaryPlayer::Move(float _moveSpeed, float _rotaSpeed) {
	posOld = resource->GetPos();
	Vector3 pos;
	Vector3 angle;

	pos = resource->GetPos();
	angle = resource->GetAngle();

	float target = -1, targetX = -1, targetY = -1;
	if (KEY->key[DIK_A] > 0) {
		pos.X -= _moveSpeed;
		targetY = 270;
	}
	else if (KEY->key[DIK_D] > 0) {
		pos.X += _moveSpeed;
		targetY = 90;
	}

	if (KEY->key[DIK_W] > 0) {
		pos.Z += _moveSpeed;
		targetX = 0;
		if (angle.Y > 180) {
			targetX = 360;
		}
	}
	else if (KEY->key[DIK_S] > 0.0f) {
		pos.Z -= _moveSpeed;
		targetX = 180;
	}
	//向きの計算
	if (targetX != -1 && targetY != -1) {
		if (targetX == 360 || targetX == 0) {
			if (targetY > 180) {
				targetX = 360;
			}
			else {
				targetX = 0;
			}
		}
		target = (targetX + targetY) / 2;
	}
	else {
		if (targetX >= 0) {
			target = targetX;
		}
		else {
			target = targetY;
		}
	}
	//回転処理
	if (target != -1) {
		if (target > angle.Y) {
			float tmp = target - angle.Y;
			if (tmp <= 180) {
				angle.Y += _rotaSpeed;
			}
			else {
				angle.Y -= _rotaSpeed;
			}
		}
		else if (target < angle.Y) {
			int tmp = angle.Y - target;
			if (tmp < 180) {
				angle.Y -= _rotaSpeed;
			}
			else {
				angle.Y += _rotaSpeed;
			}
		}
		if (angle.Y < 0) {
			angle.Y = 360;
		}
		if (angle.Y > 360) {
			angle.Y = 0;
		}
	}
	resource->SetPos(pos);
	resource->SetAngle(angle);

}

void GallaryPlayer::Collision(vector<SimpleBoxCollider2D> _boxCollider, vector<SimpleCircleCollider2D> _circleCollider, vector<SimpleBoxCollider2D> _boxColliderEvent) {
	//当たり判定処理
	for (int i = 0; i < _boxCollider.size(); i++) {
		Vector3 tmp;
		bool moveBack[2] = { false,false };

		if (_boxCollider[i].HitX(GetPos().X) &&
			_boxCollider[i].HitY(GetPosOld().Z)) {
			moveBack[0] = true;
		}
		if (_boxCollider[i].HitX(GetPosOld().X) &&
			_boxCollider[i].HitY(GetPos().Z)) {
			moveBack[1] = true;
		}
		if (moveBack[0] == true) {
			MoveBackX();
		}
		if (moveBack[1] == true) {
			MoveBackZ();
		}
	}
	for (int i = 0; i < _circleCollider.size(); i++) {
		Vector3 tmp;
		bool moveBack[2] = { false,false };
		if (_circleCollider[i].Hit(Vector2(GetPos().X, GetPosOld().Z), 1)) {
			moveBack[0] = true;
		}
		if (_circleCollider[i].Hit(Vector2(GetPosOld().X, GetPos().Z), 1)) {
			moveBack[1] = true;
		}
		if (moveBack[0] == true) {
			MoveBackX();
		}
		if (moveBack[1] == true) {
			MoveBackZ();
		}
	}

	//当たり判定処理　イベント
	for (int i = 0; i < _boxColliderEvent.size(); i++) {
		if (_boxColliderEvent[i].Hit(Vector2(GetPos().X, GetPos().Z))) {
			eventNum = i + 1;
			break;
		}
		eventNum = 0;
	}

}

void GallaryPlayer::Draw(ModelType _modelType) {
	resource->SetAllAnimeState(true, resource->GetAnimeNum(), resource->GetAnimeSpeed());
	resource->SetAll(resource->GetPos(), resource->GetAngle(), resource->GetScale());

	if (_modelType == ModelType::MAIN) {
		resource->ModelObject::Draw();
	}
	else {
		resource->Draw(_modelType);
	}
}

Vector3 GallaryPlayer::GetPos() {
	return resource->GetPos();
}
Vector3 GallaryPlayer::GetPosOld() {
	return posOld;
}

int GallaryPlayer::GetEventNum() {
	return eventNum;
}
void GallaryPlayer::MoveBackX() {
	Vector3 posOldX = resource->GetPos();
	posOldX.X = posOld.X;
	resource->SetPos(posOldX);
}
void GallaryPlayer::MoveBackZ() {
	Vector3 posOldZ = resource->GetPos();
	posOldZ.Z = posOld.Z;
	resource->SetPos(posOldZ);
}