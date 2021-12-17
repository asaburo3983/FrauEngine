#pragma once
#include "LowApplication.h"

#include "Object.h"

#include "Shader.h"

#include "Scene.h"

#include "ImGuiDX12.h"

#include "PostEffect.h"


namespace frauEngine {
	class Application {
	private:

		Scene* scene;
		Scene* sceneOld;
		std::unordered_map<std::string, Scene*> sceneList;

		int loadTime = 0;//ƒ[ƒh’†‚©‚Ç‚¤‚©
		bool loaded = false;
		int loadTimeMaxFrame = 15;

		PostEffect postEffect;
		PostEffect blurEffect;
		PostEffect depthOfFieldEffect;

		bool depthOfField = false;

	public:
		static Application* GetInstance()
		{
			static Application happ;
			return &happ;
		}
		void Init(const char* _windowName, int _windowSizeX, int _windowSizeY, bool _fullscreen);
		void UnInit();
		void SetSceneList(std::string _str, Scene* _scene);
		void Load(Scene* _scene);
		void Load(std::string _nextScene);
		void Loop();
		void LoadLoop();
		void LoadScene();

		void SetLoadTimeMaxFrame(int _maxFrame) { loadTimeMaxFrame = _maxFrame; }

		void SetDepthOfField(bool _on, int forcusX = 0, int forcusY = 0) {
			auto lowApp = frauEngine::LowApplication::GetInstance();
			depthOfField = _on;
			depthOfFieldEffect.constantBufferHeap.buffer->forcusU = 1.0f / lowApp->GetWindowSizeX() * forcusX;
			depthOfFieldEffect.constantBufferHeap.buffer->forcusV = 1.0f / lowApp->GetWindowSizeY() * forcusY;
		}
		//”íŽÊŠE[“x‚É’Ç‰Á‚Å“ü‚ê‚é‚±‚Æ‚É‚È‚é
		void SetAddEffect(int _effectNum) {
			depthOfFieldEffect.constantBufferHeap.buffer->effectNum = _effectNum;
		}
		ID3D12DescriptorHeap* GetPostEffectRenderTarget() {
			return postEffect.GetRenderTargetHeap().Get();
		}
	private:
		void InitExternalLibrary();
		void UnInitExternalLibrary();

	};
}