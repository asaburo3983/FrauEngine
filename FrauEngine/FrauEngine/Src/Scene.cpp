#include "Scene.h"

using namespace frauEngine;


void Scene::Init() {
	key = KeyInput::GetInstance();
	mouse = MouseInput::GetInstance();
	resource = Resource::GetInstance();
}
void Scene::StartUpdata() {

}
void Scene::EndUpdata() {

}

void Scene::SetObjectList(Object* _object, const char* _name) {
	_object->SetName(_name);
	objectList.push_back(_object);
}
void Scene::DrawObjectList() {
	//TODO マジックナンバーは修正する
	ImGui::SetNextWindowPos(ImVec2(280, 720 - 150), 1);
	ImGui::SetNextWindowSize(ImVec2(280, 150), 1);

	ImGui::Begin("ObjectList");

	ImGui::Text("Enable ImGui");
	for (int i = 0; i < objectList.size(); i++) {
		ImGui::Checkbox(objectList[i]->GetName(), objectList[i]->GetImGuiEnable());//ブールを切り替えれる
	}

	ImGui::End();
}
void Scene::SetStaticLoadOFF() {
	staticLoad = false;
}

void Scene::LoadScene(std::string _str) {
	loadScene = true;
	nextScene = _str;
}