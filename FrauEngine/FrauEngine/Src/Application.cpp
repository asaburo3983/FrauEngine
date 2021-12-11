#include "Application.h"

//vector str;
using namespace frauEngine;




void frauEngine::Application::Init(const char* _windowName, int _windowSizeX, int _windowSizeY, bool _fullscreen) {

	frauEngine::LowApplication::GetInstance()->SetDebugMode(true);

	frauEngine::LowApplication::GetInstance()->Init(_windowName, _windowSizeX, _windowSizeY, _fullscreen);

	InitExternalLibrary();

	auto resource = Resource::GetInstance();
	resource->LoadShader(frauEngine::ShaderType::VS, "Data/Shader/VertexShader_PostEffect.hlsl");
	resource->LoadShader(frauEngine::ShaderType::PS, "Data/Shader/PixelShader_PostEffect.hlsl");

	resource->LoadShader(frauEngine::ShaderType::PS, "Data/Shader/PixelShader_Blur.hlsl");
	resource->LoadShader(frauEngine::ShaderType::PS, "Data/Shader/PixelShader_DepthOfField.hlsl");

	postEffect.Create(
		resource->Shader("Data/Shader/VertexShader_PostEffect.hlsl"),
		resource->Shader("Data/Shader/PixelShader_PostEffect.hlsl"));
	blurEffect.Create(
		resource->Shader("Data/Shader/VertexShader_PostEffect.hlsl"),
		resource->Shader("Data/Shader/PixelShader_Blur.hlsl"));

	depthOfFieldEffect.Create(
		resource->Shader("Data/Shader/VertexShader_PostEffect.hlsl"),
		resource->Shader("Data/Shader/PixelShader_DepthOfField.hlsl"));

	blurEffect.SetMainTexture(postEffect.GetResourceHeap());

	depthOfFieldEffect.SetMainTexture(postEffect.GetResourceHeap());
	depthOfFieldEffect.SetBlurTexture(blurEffect.GetResourceHeap());

}
void frauEngine::Application::InitExternalLibrary() {

	frauEngine::ManagerDXTK::GetInstance()->Init();

	frauEngine::ManagerImGui::GetInstance()->Init();
}
void frauEngine::Application::UnInitExternalLibrary() {

	frauEngine::ManagerDXTK::GetInstance()->UnInit();

	frauEngine::ManagerImGui::GetInstance()->UnInit();

	Resource::GetInstance()->AllDelete();

}
void frauEngine::Application::UnInit() {

	frauEngine::LowApplication::GetInstance()->UnInit();

}
void frauEngine::Application::Load(Scene* _scene) {

	load = true;
	sceneOld = scene;
	if (sceneOld != nullptr) {
		sceneOld->UnLoad();
	}
	scene = _scene;

	scene->Init();

	scene->LoadFrontLoad();

	std::thread loadLoopThread(&frauEngine::Application::LoadLoop,this);

	std::thread loadSceneThread(&frauEngine::Application::LoadScene,this);

	loadLoopThread.join();
	loadSceneThread.join();
}



void frauEngine::Application::Loop() {
	auto lowApp = LowApplication::GetInstance();
	
	MSG msg = {};
	while (true) {

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT) {
			break;
		}
		lowApp->DrawStart();

		lowApp->DrawOnRenderTarget(postEffect.GetRenderTargetHeap().Get());

		if(frauEngine::LowApplication::GetInstance()->GetDebugMode()) {
			frauEngine::ManagerImGui::GetInstance()->DrawStart();//ImGUIループ枚処理
		}
		UpdateInput();//入力処理更新	

		scene->StartUpdata();

		scene->Updata();

		scene->Draw();
		
		scene->EndUpdata();

		//被写界深度用ブラーテクスチャ
		if (depthOfField) {
			//ポストエフェクトにブラーをかけるRTVに変更
			lowApp->DrawOnRenderTargetNoDepth(blurEffect.GetRenderTargetHeap().Get());

			blurEffect.Draw();
		}
		lowApp->DrawOnScreen();

		//被写界深度対応描画
		if (depthOfField) {
			depthOfFieldEffect.Draw();
		}
		else {
			postEffect.Draw();
		}

		if (frauEngine::LowApplication::GetInstance()->GetDebugMode()) {
			scene->DrawObjectList();
			frauEngine::ManagerImGui::GetInstance()->DrawFinish();//ImGUIループ枚処理
		}
		lowApp->DrawFinish();
		frauEngine::ManagerDXTK::GetInstance()->DrawFinish();
	}
}

//スレッド用ループ
void frauEngine::Application::LoadLoop() {

	auto lowApp = LowApplication::GetInstance();
	MSG msg = {};
	while (true) {

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//もうアプリケーションが終わるって時にmessageがWM_QUITになる
		if (msg.message == WM_QUIT) {
			break;
		}
		lowApp->DrawStart();

		lowApp->DrawOnRenderTarget(postEffect.GetRenderTargetHeap().Get());

		UpdateInput();//入力処理更新	

		scene->StartUpdata();

		scene->LoadInUpdata();
		scene->LoadInDraw();

		scene->EndUpdata();

		if (depthOfField) {
			lowApp->DrawOnRenderTargetNoDepth(blurEffect.GetRenderTargetHeap().Get());

			blurEffect.Draw();
		}

		lowApp->DrawOnScreen();

		if (depthOfField) {
			depthOfFieldEffect.Draw();
		}
		else {
			postEffect.Draw();
		}

		lowApp->DrawFinish();

		frauEngine::ManagerDXTK::GetInstance()->DrawFinish();
	
		if (load == false) {
			break;
		}
	}
}
void frauEngine:: Application::LoadScene() {
	scene->Load();//継承したロード
	load = false;
}

