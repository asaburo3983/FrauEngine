#include "CameraWork.h"


void CameraWork::Initialize() {

	Vector3 posOld;
	Vector3 targetOld;


	camera.SetPos(Vector3(0, 5, -13));
	camera.SetTarget(Vector3(0, 0, 0));
	camera.SetUp(Vector3(0, 1, 0));
	camera.SetFov(45);

	pos.resize(10);
	target.resize(10);

	//通常カメラ
	pos[0] = Vector3(0, 5, -13);
	target[0] = Vector3(0, 0, 0);
	//導入のカメラワーク
	pos[1] = Vector3(2, 1, -2);
	target[1] = Vector3(7, 0, 10);


}
void CameraWork::Move() {
	if (lerpCount < 1.0f) {
		lerpCount += lerpSpeed;
	}
	Vector3 tmp = Vector3(
		lerp(pos[moveNumOld].X, pos[moveNum].X, lerpCount),
		lerp(pos[moveNumOld].Y, pos[moveNum].Y, lerpCount),
		lerp(pos[moveNumOld].Z, pos[moveNum].Z, lerpCount));
	camera.SetPos(tmp);

	tmp = Vector3(
		lerp(target[moveNumOld].X, target[moveNum].X, lerpCount),
		lerp(target[moveNumOld].Y, target[moveNum].Y, lerpCount),
		lerp(target[moveNumOld].Z, target[moveNum].Z, lerpCount));

	camera.SetTarget(tmp);
}
void CameraWork::PlayerTarget() {
	auto player=Player::GetInstance();

	auto pos = player->GetPos();
	pos.Y += 8.0f;
	pos.Z -= 10.0f;
	auto target = player->GetPos();
	target.Y += 4.0f;

	camera.SetPos(pos);
	camera.SetTarget(target);
}
void CameraWork::Updata() {

	if (playerTarget) {
		PlayerTarget();
	}
	else {
		Move();
	}
	camera.Update();
}

void CameraWork::SetMoveNum(int _moveNum) {
	moveNumOld = moveNum;
	moveNum = _moveNum; 
	lerpCount = 0;
}