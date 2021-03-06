#pragma once
#include "LowApplication.h"
#include "Shader.h"

namespace frauEngine {

	enum ConstantBufferHeapSlot {
		HEAP_SLOT_MODEL = 7
	};
	enum LightSlot {
		POINT_LIGHT=4,
		SPOT_LIGHT=4,

	};
	//定数バッファの中身を定義//////////////////
	struct WorldBuffer {
		DirectX::XMMATRIX world;
	};

	struct BoneBuffer {
		DirectX::XMMATRIX boneMatrix[512];
	};
	struct MaterialBuffer {
		DirectX::XMFLOAT4  ambient;
		DirectX::XMFLOAT4  diffuse;
		DirectX::XMFLOAT4  specular;
	};
	struct CameraBuffer {
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
		DirectX::XMFLOAT4 pos;
	};
	struct LightBuffer {
		DirectX::XMFLOAT4 ambientLight;////パッキングの影響でfloat4のxだけ使用

		DirectX::XMMATRIX directionalLightView;
		DirectX::XMMATRIX directionalLightProjection;
		DirectX::XMFLOAT4 directionalLightPos;
		DirectX::XMFLOAT4 directionalLightVector;
		DirectX::XMFLOAT4 directionalLightColor;

		DirectX::XMFLOAT4 pointLightPos[POINT_LIGHT];
		DirectX::XMFLOAT4 pointLightRange[POINT_LIGHT];////パッキングの影響でfloat4のxだけ使用
		DirectX::XMFLOAT4 pointLightColor[POINT_LIGHT];

		DirectX::XMFLOAT4 spotLightPos[SPOT_LIGHT];
		DirectX::XMFLOAT4 spotLightRange[SPOT_LIGHT];
		DirectX::XMFLOAT4 spotLightTarget[SPOT_LIGHT];
		DirectX::XMFLOAT4 spotLightAngularRange[SPOT_LIGHT];
		DirectX::XMFLOAT4 spotLightColor[SPOT_LIGHT];

	};

	struct UtilityBuffer {
		int meshNum = -1;
	};
	struct PBRBuffer {

		float subsurface;

		float metallic;

		float specular;

		float specularTint;

		float roufhness;

		float anistropics;

		float sheen;

		float sheenTint;

		float clearColor;

		float clearcoatGloss;

		float outline;
		float outlineColorR;
		float outlineColorG;
		float outlineColorB;

		float workSpace;

		int anotherTexture[(int)frauEngine::ShaderTextureSlot::MODEL_ANOTHER];
	};
	/////////////////////////////////////////////
		//ポストエフェクト用のバッファ
	struct PostEffectBuffer {
		float forcusU;
		float forcusV;
	};
	//デスクリプタヒープを補完している/////////////////////////
	class ConstantBufferHeap {
	public:
		ID3D12DescriptorHeap* descripterHeap = nullptr;
	protected:
		void CreateConstantBufferHeap(int dataSize, void** data);
	};

	class WorldBufferHeap : public ConstantBufferHeap {
	public:
		WorldBuffer* buffer;
		void Create();
	};
	class BoneBufferHeap : public ConstantBufferHeap {
	public:
		BoneBuffer* buffer;
		void Create();
	};	
	class MaterialBufferHeap : public ConstantBufferHeap {
	public:
		MaterialBuffer buffer;
		void Create();
	};	
	class CameraBufferHeap : public ConstantBufferHeap {
	public:
		CameraBuffer* buffer;
		void Create();
	};	
	class LightBufferHeap : public ConstantBufferHeap {
	public:
		LightBuffer* buffer;
		void Create();
	};	
	class UtilityBufferHeap : public ConstantBufferHeap {
	public:
		UtilityBuffer* buffer;
		void Create();
	};
	class PBRBufferHeap : public ConstantBufferHeap {
	public:
		PBRBuffer* buffer;
		void Create();
	};
	class PostEffectBufferHeap : public ConstantBufferHeap {
	public:
		PostEffectBuffer* buffer;
		void Create();
	};
	//////////////////////////////////////////////////////
}