#include "ConstantBuffer_PostEffect.hlsli"

float4 main(PeraType input) : SV_TARGET{
	float offsetU = 1.0f / 1920.0f;
	float offsetV = 1.0f / 1080.0f;


	float4 tex_color = tex.Sample(smp, input.uv);

	float4 tex_blur = texBlur.Sample(smp, input.uv);
	
	float tex_depth = texDepth.Sample(smp, input.uv);
	float forcus_depth = texDepth.Sample(smp, float2(forcusU, forcusV));

	float lerpValue = abs(tex_depth - forcus_depth) * 100;
	if (lerpValue >1.0f ) {
		lerpValue = 1;
	}
	if (lerpValue <0.0f ) {
		lerpValue = 0;
	}

	float4 anser = lerp(tex_color, tex_blur, lerpValue);

	switch (effectNum) {
	case BLUR:
		anser = lerp(tex_color, tex_blur, 1);
		break;
	case SHARP:
		float power = 5.0f;
		float vicinity = (power - 1.0f) / 4.0f * -1;
		anser = 0;
		float offsetPower = 4.0f;
		anser += tex.Sample(smp, input.uv + float2(-offsetPower * offsetU, -offsetPower * offsetV)) * 0;//LU
		anser += tex.Sample(smp, input.uv + float2(0, -offsetPower * offsetV)) * vicinity;//U
		anser += tex.Sample(smp, input.uv + float2(offsetPower * offsetU, -offsetPower * offsetV)) * 0;//RU

		anser += tex.Sample(smp, input.uv + float2(-offsetPower * offsetU, 0.0f)) * vicinity;//L
		anser += tex.Sample(smp, input.uv) * power;
		anser += tex.Sample(smp, input.uv + float2(offsetPower * offsetU, 0.0f)) * vicinity;//R

		anser += tex.Sample(smp, input.uv + float2(-offsetPower * offsetU, offsetPower * offsetV)) * 0;//LD
		anser += tex.Sample(smp, input.uv + float2(0, -offsetPower * offsetV)) * vicinity;//D
		anser += tex.Sample(smp, input.uv + float2(offsetPower * offsetU, offsetPower * offsetV)) * 0;//RD

		break;
	case RETORO:
		anser= float4(anser.rgb - fmod(anser, 1.0f / 4.0f), 1);
		break;
	case NEGA:
		anser = float4(float3(1.0, 1.0, 1.0) - anser.rgb, 1);
		break;
	}
	return anser;

}