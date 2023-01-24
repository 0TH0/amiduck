#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Engine/Text.h"

//�����V�[�����Ǘ�����N���X
class ItemUI: public GameObject
{
	int hPict_[3];
	int alpha_;
	Text* pText;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ItemUI(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;
};