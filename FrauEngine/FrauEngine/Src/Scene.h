#pragma once
#include "Resource.h"
#include "Object.h"

namespace frauEngine {
	class Scene {
	public:
		Resource* resource;

		bool gameEnd = false;

		bool loadScene = false;

		std::string nextScene;
	protected:
		KeyInput* key;
		MouseInput* mouse;

		std::vector<Object*> objectList;
	private:
		bool staticLoad = true;

	public:
		bool GetStaticLoad() { return staticLoad; };
		void SetStaticLoadOFF();

		void Init();
		void StartUpdata();//ÉVÅ[ÉìÇ≈ÇÃã§í èàóù
		void EndUpdata();

		void SetObjectList(Object* _object, const char* _name);
		void DrawObjectList();

		void LoadScene(std::string _str);

		virtual void LoadFrontLoad() = 0;
		virtual void LoadInUpdata() = 0;
		virtual void LoadInDraw() = 0;

		virtual void StaticLoad() = 0;
		virtual void Load() = 0;
		virtual void Updata() = 0;
		virtual void Draw() = 0;
		virtual void DrawNonePostEffect() = 0;
		virtual void UnLoad() = 0;




	};
}