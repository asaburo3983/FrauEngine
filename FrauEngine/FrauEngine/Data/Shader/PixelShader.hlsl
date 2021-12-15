#include "ConstantBuffer.hlsli"


float Beckmann(float m, float t)
{
    float t2 = t * t;
    float t4 = t * t * t * t;
    float m2 = m * m;
    float D = 1.0f / (4.0f * m2 * t4);
    D *= exp((-1.0f / m2) * (1.0f - t2) / t2);
    return D;
}

float SpcFresnel(float f0, float u)
{
    // from Schlick
    return f0 + (1 - f0) * pow(1 - u, 5);
}

float CalcDiffuseFromFresnel(float3 N, float3 L, float3 V, float roughness)
{
    // step-1 �f�B�Y�j�[�x�[�X�̃t���l�����˂ɂ��g�U���˂�^�ʖڂɎ�������B
    // �����Ɍ������x�N�g���Ǝ����Ɍ������x�N�g���̃n�[�t�x�N�g�������߂�
    float3 H = normalize(L + V);

    // �e����0.5�ŌŒ�B
    float energyBias = lerp(0.0f, 0.5f, roughness);
    float energyFactor = lerp(1.0, 1.0 / 1.51, roughness);

    // �����Ɍ������x�N�g���ƃn�[�t�x�N�g�����ǂꂾ�����Ă��邩����ςŋ��߂�
    float dotLH = saturate(dot(L, H));

    // �����Ɍ������x�N�g���ƃn�[�t�x�N�g���A
    // �������s�ɓ��˂����Ƃ��̊g�U���˗ʂ����߂Ă���
    float Fd90 = energyBias + 2.0 * dotLH * dotLH * roughness;

    // �@���ƌ����Ɍ������x�N�g��w�𗘗p���Ċg�U���˗������߂�
    float dotNL = saturate(dot(N, L));
    float FL = (1 + (Fd90 - 1) * pow(1 - dotNL, 5));

    // �@���Ǝ��_�Ɍ������x�N�g���𗘗p���Ċg�U���˗������߂�
    float dotNV = saturate(dot(N, V));
    float FV = (1 + (Fd90 - 1) * pow(1 - dotNV, 5));

    // �@���ƌ����ւ̕����Ɉˑ�����g�U���˗��ƁA�@���Ǝ��_�x�N�g���Ɉˑ�����g�U���˗���
    // ��Z���čŏI�I�Ȋg�U���˗������߂Ă���BPI�ŏ��Z���Ă���̂͐��K�����s������
    return (FL * FV * energyFactor);
}

float CookTorranceSpecular(float3 L, float3 V, float3 N, float _metallic)
{
    float microfacet = 0.76f;

    // �����x�𐂒����˂̎��̃t���l�����˗��Ƃ��Ĉ���
    // �����x�������قǃt���l�����˂͑傫���Ȃ�
    float f0 = _metallic;

    // ���C�g�Ɍ������x�N�g���Ǝ����Ɍ������x�N�g���̃n�[�t�x�N�g�������߂�
    float3 H = normalize(L + V);

    // �e��x�N�g�����ǂꂭ�炢���Ă��邩����ς𗘗p���ċ��߂�
    float NdotH = saturate(dot(N, H));
    float VdotH = saturate(dot(V, H));
    float NdotL = saturate(dot(N, L));
    float NdotV = saturate(dot(N, V));

    // D�����x�b�N�}�����z��p���Čv�Z����
    float D = Beckmann(microfacet, NdotH);

    // F����Schlick�ߎ���p���Čv�Z����
    float F = SpcFresnel(f0, VdotH);

    // G�������߂�
    float G = min(1.0f, min(2 * NdotH * NdotV / VdotH, 2 * NdotH * NdotL / VdotH));

    // m�������߂�
    float m = PI * NdotV * NdotH;

    // �����܂ŋ��߂��A�l�𗘗p���āACook-Torrance���f���̋��ʔ��˂����߂�
    return max(F * D * G / m, 0.0);
}

float3 PointLight(float3 modelWorldPos, float3 lightPos,float lightRange,float3 lightColor) {

    float distance = length(modelWorldPos - lightPos);//���_�Ƃ̋������v�Z
    distance /= lightRange;//�͈͓��ł̏�����

    float anser = 1.0f - distance;

    if (anser < 0) {
        anser = 0;
    }
    anser = pow(anser, 2.0f);
    return lightColor * anser;
}
float3 SpotLight(float3 modelWorldPos, float3 lightPos, float lightRange, float3 lightColor,float lightAnglurRange,float3 lightVector) {
    //�X�|�b�g���C�g�̌v�Z
    lightVector = normalize(lightVector);

    float3 objectVector = normalize(modelWorldPos - lightPos);//�I�u�W�F�N�g�̃��C�g�ւ̃x�N�g��

    float scalar = dot(objectVector, lightVector);//���C�g�ƃI�u�W�F�N�g�̓��ς����߂�

    float angle = (1.0 - scalar) * 180.0f;//�x�����o�܂�

    float anser = 1.0f - 1.0f / lightAnglurRange * angle;//�p�x����

    float length2 = length(modelWorldPos - lightPos);//�����i�����n�j
    length2 /= lightRange;
    anser *= length2;//��������
    if (anser < 0) {
        anser = 0;
    }
    anser = pow(anser, 2.0f);

    return lightColor * anser;
}
float4 main(VS_OUT input) : SV_TARGET{

    float offsetX = 1.5f / 1920.0f;
    float offsetY = 1.5f / 1080.0f;

     //�e�N�X�`���J���[
     float4 tex_color = tex.Sample(smp, input.uv);
     if (tex_color.a <= 0.0)discard;//a�O�l��\������

     if (anotherTexture0 == 1) {
         return(texAnother0.Sample(smp, input.uv));
     }

    float3 normal = input.normalDLight;
    //normal = mul(CameraView, normal);
    //normal = mul(CameraProjection, normal);

    //�\�t�g�V���h�E�@����
    float sm0 = texDepth.Sample(smpSM, input.posSM.xy);
    float sm1 = texDepth.Sample(smpSM, input.posSM.xy + float2(offsetX, 0.0f));
    float sm2 = texDepth.Sample(smpSM, input.posSM.xy + float2(offsetX, offsetY));
    float sm3 = texDepth.Sample(smpSM, input.posSM.xy + float2(0.0f, offsetY));

    float shadowRate = 0.0f;

    float zShadoBuffar = input.posSM.z;
    if (zShadoBuffar < sm0) {
        shadowRate += 1.0f;
    }
    if (zShadoBuffar < sm1) {
        shadowRate += 1.0f;
    }
    if (zShadoBuffar < sm2) {
        shadowRate += 1.0f;
    }
    if (zShadoBuffar < sm3) {
        shadowRate += 1.0f;
    }
    shadowRate /= 4.0f;

    if (shadowRate == 0.0f) {
        shadowRate += 0.25f;//�Œ�̍���
    }
    //�ȒP�ȃV���h�E
    //shadowRate = 1;
    //if (zShadoBuffar > sm0) {
    //    shadowRate = 0.5f;
    //}

    //�A�E�g���C������(�V�F�[�_�[���ł̎�����,2�p�X�����̂ق������x���悢�̂ōl����)
    float outlineCos = dot(normalize(CameraPos.xyz), normalize(normal));
    
    float outlineAngle= lerp(45.0f, 50.0f, outline);
    if (outlineCos <cos(outlineAngle)) {
        //return float4(outlineColorR,outlineColorG,outlineColorB, 1);
    }

    //PBR����
    float4 albedoColor = tex_color;
    float3 specColor = albedoColor;

    float smooth = roufhness;
    float _metallic = 1.0f - metallic;//���]���Ă�
    // �����Ɍ������ĐL�т�x�N�g�����v�Z����
    float3 toEye = normalize(CameraPos - input.posDLight);

    float diffuseFromFresnel = CalcDiffuseFromFresnel(normal, -DLightVector, toEye, smooth);

    float NdotL = saturate(dot(normal, -DLightVector));
    float3 lambertDiffuse = DLightColor * NdotL / PI;

    float3 diffuse =  diffuseFromFresnel * lambertDiffuse;

    float spec = CookTorranceSpecular(-DLightVector, toEye, normal, _metallic) * DLightColor;

    spec *= lerp(float3(1.0f, 1.0f, 1.0f), specColor, _metallic);

    float3 lig = 0;
    // ���炩�����g���āA�g�U���ˌ��Ƌ��ʔ��ˌ�����������
    // ���炩����������΁A�g�U���˂͎キ�Ȃ�
    lig +=  diffuse * (1.0f - smooth) + spec;
   
    
    float3 pointLight = 0;
    for (int i = 0; i < POINT_LIGHT; i++) {
        if (pointLightRange[i].x > 0)
        pointLight += PointLight(input.worldPos.xyz, pointLightPos[i], pointLightRange[i].x, pointLightColor[i]);
    }
    float3 spotLight = 0;
    for (int i = 0; i < SPOT_LIGHT; i++) {
        if (spotLightRange[i].x > 0)
             spotLight += SpotLight(input.worldPos.xyz, spotLightPos[i], spotLightRange[i].x, spotLightColor[i], spotLightAngularRange[i].x, spotLightTarget[i]);
    }


    // �����ɂ���グ�@
    lig += ambientLight.x;
    lig *= albedoColor;

    //�\�t�g�V���h�E�ǉ�
    lig *= shadowRate;

    lig += lig * pointLight;// �|�C���g���C�g�����Z //���PBR�̗���������������ق�������
    lig += lig * spotLight;//�X�|�b�g���C�g�����Z

    //�e���[������ 0.5~1.0�̐��l�łR����
    //if (1) {
    //    if (lig.x < 0.7) {
    //        lig = 0.7;
    //    }
    //    if (lig.x < 0.6f) {
    //        lig = 0.5;
    //    }
    //    if (lig.x > 0.7) {
    //        lig = 0.9;
    //    }
    //}



    float4 finalColor = 1.0f;
    finalColor.xyz = lig;

    finalColor.a = tex_color.a;

    return finalColor;

}