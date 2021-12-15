#include "Resource.h"

using namespace frauEngine;
Image2D* Resource::LoadIm(const char* _filepath) {
	if (image[_filepath] != nullptr) {
		MessageBox(NULL, TEXT("�摜�f�[�^���d�����Ă��܂�"), TEXT("ResourceError"), MB_OK | MB_ICONERROR);
		return nullptr;
	}
	image[_filepath] = new frauEngine::Image2D();
	image[_filepath]->Load(_filepath);

	return image[_filepath];
}
Sound_MP3* Resource::LoadSound(const char* _filepath) {
	if (sound[_filepath] != nullptr) {
		MessageBox(NULL, TEXT("�T�E���h�f�[�^���d�����Ă��܂�"), TEXT("ResourceError"), MB_OK | MB_ICONERROR);
		return nullptr;
	}
	sound[_filepath] = new frauEngine::Sound_MP3();
	sound[_filepath]->Load(_filepath);

	return sound[_filepath];
}
FBX* Resource::LoadModel(std::string _filepath, std::string _texpath) {
	if (model[_filepath] != nullptr) {
		MessageBox(NULL, TEXT("���f���f�[�^���d�����Ă��܂�"), TEXT("ResourceError"), MB_OK | MB_ICONERROR);
		return nullptr;
	}
	model[_filepath] = new frauEngine::FBX();
	model[_filepath]->Load(_filepath, _texpath);

	return model[_filepath];
}
Effect* Resource::LoadEffect(const char* _filepath) {
	char16_t ustr[256];
	mbstate_t* ps=nullptr;
	mbrtoc16(ustr, _filepath, 256, ps);

	if (effect[_filepath] != nullptr) {
		MessageBox(NULL, TEXT("�G�t�F�N�g�f�[�^���d�����Ă��܂�"), TEXT("ResourceError"), MB_OK | MB_ICONERROR);
		return nullptr;
	}
	effect[_filepath] = new frauEngine::Effect();
	effect[_filepath]->Load(ustr);

	return effect[_filepath];
}
Shader* Resource::LoadShader(frauEngine::ShaderType _shaderType, const char* _filepath) {
	if (shader[_filepath] != nullptr) {
		MessageBox(NULL, TEXT("�V�F�[�_�[�f�[�^���d�����Ă��܂�"), TEXT("ResourceError"), MB_OK | MB_ICONERROR);
		return nullptr;
	}
	shader[_filepath] = new frauEngine::Shader();
	shader[_filepath]->Load(_shaderType, _filepath);

	return shader[_filepath];
}
void Resource::UnLoadIm(std::string _filepath) {
	auto itr = image.find(_filepath);
	if (itr != image.end())         // �L�[�̗v�f�����݂��Ă���ꍇ
		image.erase(itr);
}
void Resource::UnLoadSound(std::string _filepath) {
	auto itr = sound.find(_filepath);
	if (itr != sound.end())         // �L�[�̗v�f�����݂��Ă���ꍇ
		sound.erase(itr);
}
void Resource::UnLoadModel(std::string _filepath) {
	auto itr = model.find(_filepath);
	if (itr != model.end())         // �L�[�̗v�f�����݂��Ă���ꍇ
		model.erase(itr);
}
void Resource::UnLoadEffect(std::string _filepath) {
	auto itr = effect.find(_filepath);
	if (itr != effect.end())         // �L�[�̗v�f�����݂��Ă���ꍇ
		effect.erase(itr);
}
void Resource::UnLoadShader(std::string _filepath) {
	auto itr = shader.find(_filepath);
	if (itr != shader.end())         // �L�[�̗v�f�����݂��Ă���ꍇ
		shader.erase(itr);
}
void Resource::AllDelete() {

	while (image.size() > 0) {
		auto itr = image.begin();
		image.erase(itr);
	}
	while (sound.size() > 0) {
		auto itr = sound.begin();
		sound.erase(itr);
	}
	while (model.size() > 0) {
		auto itr = model.begin();
		model.erase(itr);
	}
	while (effect.size() > 0) {
		auto itr = effect.begin();
		effect.erase(itr);
	}

}
Image2D* Resource::Image(std::string _filepath) {
	return image[_filepath];
}
Sound_MP3* Resource::Sound(std::string _filepath) {
	return sound[_filepath];
}
FBX* Resource::Model(std::string _filepath) {
	return model[_filepath];
}
Effect* Resource::Effect(std::string _filepath) {
	return effect[_filepath];
}
Shader* Resource::Shader(std::string _filepath) {
	return shader[_filepath];
}