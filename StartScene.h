#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Engine/Text.h"

//�����V�[�����Ǘ�����N���X
class StartScene : public GameObject
{
	int hPict_[3];
	float time;
	int stock;
	Text* pText;
	//SceneManager* pSceneManager;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	StartScene(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	void minStock() { stock--; };
};