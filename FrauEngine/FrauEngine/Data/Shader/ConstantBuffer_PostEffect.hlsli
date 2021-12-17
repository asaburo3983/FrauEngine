Texture2D<float4> tex : register(t1);
Texture2D<float> texDepth : register(t2);
Texture2D<float4> texBlur : register(t3);

SamplerState smp : register(s0);

static const int DEPTHOFFIELD = 0;
static const int BLUR = 1;
static const int SHARP = 2;
static const int RETORO = 3;
static const int NEGA = 4;

cbuffer PostEffectBuffer : register(b0) {
	float forcusU;
	float forcusV;
	int effectNum;
};

struct VS_IN {
	float4 pos:POSITION;
	float2 uv : TEXCOORD;

};

//ƒyƒ‰ƒ|ƒŠƒSƒ“•`‰æ—p
struct PeraType {
	float4 pos: SV_POSITION;
	float2 uv:TEXCOORD;
};