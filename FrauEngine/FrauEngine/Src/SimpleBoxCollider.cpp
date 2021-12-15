#include "SimpleBoxCollider.h"

SimpleBoxCollider2D::SimpleBoxCollider2D() {

}
SimpleBoxCollider2D::SimpleBoxCollider2D(Vector2 _pos, Vector2 _scale) {
	Setup( _pos, _scale);
}
void SimpleBoxCollider2D::Setup(Vector2 _pos, Vector2 _scale) {
	pos = _pos;
	scale = _scale;

	point[0].X = _pos.X - 0.5 * scale.X;
	point[1].X = _pos.X + 0.5 * scale.X;
	
	point[0].Y = _pos.Y - 0.5 * scale.Y;
	point[1].Y = _pos.Y + 0.5 * scale.Y;
	
	
}

bool SimpleBoxCollider2D::HitX(float _posX) {
	if (point[0].X <= _posX && _posX <= point[1].X) {
		return true;
	}
	return false;
}
bool SimpleBoxCollider2D::HitY(float _posY) {
	if (point[0].Y <= _posY && _posY <= point[1].Y) {
		return true;
	}
	return false;
}

bool SimpleBoxCollider2D::Hit(Vector2 _pos) {
	if (!HitX(_pos.X)) {
		return false;
	}
	if (!HitY(_pos.Y)) {
		return false;
	}
	return true;
}

