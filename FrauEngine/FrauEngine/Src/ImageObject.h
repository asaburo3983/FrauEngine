#pragma once
#include "LowApplication.h"
#include "DXTK.h"
#include "Object.h"

namespace frauEngine {
	class ImageObject : public frauEngine::Object {

	protected:
		frauEngine::Image2D* resource;

		bool enable = true;
		Vector2 pos;
		Vector2 scale;
		float angle = 0.0f;
		float alpha = 1.0f;
		bool turnLR = false;
		bool turnUD = false;
		bool center = true;

	public:
		void SetResource(frauEngine::Image2D* _image);

		void SetPos(Vector2 _pos);
		void SetScale(Vector2 _scale);
		void SetAngle(float _angle);
		void SetAlpha(float _alpha);
		void SetTurn(bool _turnLR, bool _turnUD);
		void SetCenter(bool _center);

		bool GetEnable() { return enable; };
		Vector2 GetPos() { return pos; };
		Vector2 GetScale() { return scale; };
		float GetAngle() { return angle; };
		float GetAlpha() { return alpha; };
		bool GetTurnLR() { return turnLR; };
		bool GetTurnUD() { return turnUD; };
		bool GetCenter() { return center; }

		void SetAll(Vector2 _pos = Vector2(0, 0), Vector2 _scale = Vector2(1, 1), float _angle = 0.0f, float _alpha = 1.0f);

		void DrawImGUI();
		void Updata();
		void Draw();
		bool Hit(int _x, int _y);
	};

}