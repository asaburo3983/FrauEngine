#pragma once
#include "Application.h"
#include "Object.h"

#include "Loading.h"
#include "Fade.h"

using namespace frauEngine;

class GallaryScene : public Scene {
private:
	Loading loading;
	Fade fade;

public:

	void LoadFrontLoad();
	void LoadInUpdata();
	void LoadInDraw();

	void StaticLoad();
	void Load();
	void Updata();
	void Draw();
	void DrawNonePostEffect();
	void UnLoad();

};
