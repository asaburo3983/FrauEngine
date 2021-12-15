#include "ConstantBuffer.hlsli"


VS_OUT main(VS_IN input) {

	VS_OUT output;



	float4 pos;
	float4 normal;
	pos = input.pos;
	normal = input.normal;


	//�{�[���A�j���[�V��������
	float4x4 comb = (float4x4)0;
	for (int i = 0; i < 4; i++)
	{
		if (input.boneWeight[i] > 0.0 && input.boneIndex[i] != 512)
			comb += mBoneMatrix[input.boneIndex[i]] * input.boneWeight[i];
	}
	input.pos.w = 1.0;
	float4 combX;
	combX[0] = -comb[0][0] * input.pos.x;
	combX[1] = -comb[1][0] * input.pos.x;
	combX[2] = -comb[2][0] * input.pos.x;
	combX[3] = -comb[3][0] * input.pos.x;
	float4 combY;
	combY[0] = comb[0][1] * input.pos.y;
	combY[1] = comb[1][1] * input.pos.y;
	combY[2] = comb[2][1] * input.pos.y;
	combY[3] = comb[3][1] * input.pos.y;
	float4 combZ;
	combZ[0] = comb[0][2] * input.pos.z;
	combZ[1] = comb[1][2] * input.pos.z;
	combZ[2] = comb[2][2] * input.pos.z;
	combZ[3] = comb[3][2] * input.pos.z;
	float4 combW;
	combW[0] = comb[0][3] * input.pos.w;
	combW[1] = comb[1][3] * input.pos.w;
	combW[2] = comb[2][3] * input.pos.w;
	combW[3] = comb[3][3] * input.pos.w;
	pos.x = combX[0] + combY[0] + combZ[0] + combW[0];
	pos.y = combX[1] + combY[1] + combZ[1] + combW[1];
	pos.z = combX[2] + combY[2] + combZ[2] + combW[2];
	pos.w = combX[3] + combY[3] + combZ[3] + combW[3];
	pos.x /= pos.w;
	pos.y /= pos.w;
	pos.z /= pos.w;
	pos.w /= pos.w;
	normal.x = combX[0] + combY[0] + combZ[0] + combW[0];
	normal.y = combX[1] + combY[1] + combZ[1] + combW[1];
	normal.z = combX[2] + combY[2] + combZ[2] + combW[2];
	normal.w = combX[3] + combY[3] + combZ[3] + combW[3];
	normal.x /= normal.w;
	normal.y /= normal.w;
	normal.z /= normal.w;
	normal.w /= normal.w;
	//�{�[���A�j���I��

	//���_�̍��W�Ԋ�
	output.pos = mul(World, pos);
	output.worldPos = output.pos;

	output.posDLight = output.pos;
	output.normalDLight = mul(World, normal);

	output.pos = mul(CameraView, output.pos);
	output.pos = mul(CameraProjection, output.pos);

	output.normal = normalize(mul(World, normal));//�@���ɂ����[���h�ϊ����s��

	output.uv = input.texture_pos;

	
	
	

	//�f�B���N�V���i�����C�g���猩�����_
	float4 pos4;
	pos4 = output.worldPos;
	pos4 = mul(DLightView, pos4);
	pos4 = mul(DLightProjection, pos4);
	//�V���h�E�}�b�v�p�̐[�x�𐳋K��
	pos4.xyz = pos4.xyz / pos4.w;
	output.posSM.x = (pos4.x + 1.0) / 2.0;
	output.posSM.y = (-pos4.y + 1.0) / 2.0;
	output.posSM.z = pos4.z;


	return output;
}
