#pragma once
#include "Resource.h"
#include "Object.h"

namespace frauEngine {
	class Scene {
	public:
		Resource* resource;
	protected:
		KeyInput* key;
		MouseInput* mouse;

		std::vector<Object*> objectList;

	public:

		void Init();
		void StartUpdata();//ÉVÅ[ÉìÇ≈ÇÃã§í èàóù
		void EndUpdata();

		void SetObjectList(Object* _object, const char* _name);
		void DrawObjectList();

		virtual void LoadFrontLoad() = 0;
		virtual void LoadInUpdata() = 0;
		virtual void LoadInDraw() = 0;

		virtual void Load() = 0;
		virtual void Updata() = 0;
		virtual void Draw() = 0;
		virtual void UnLoad() = 0;

	};
}