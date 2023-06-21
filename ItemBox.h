#pragma once
#include "Engine/GameObject.h"
#include "Engine/VFX.h"

//�V�[�����Ǘ�����N���X
class ItemBox : public GameObject
{
	int alpha_;
	int time_;
	bool IsHit_;
	
	EmitterData data;

public:

	int hModel_;
	int hPict_;    //�摜�ԍ�

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ItemBox(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void OnCollision(GameObject* pTarget) override;

	void QuestionEffect();

	bool GetIsHit() { return IsHit_; };
};