#pragma once
#include "Engine/GameObject.h"
#include "Engine/VFX.h"

//�V�[�����Ǘ�����N���X
class ItemBox : public GameObject
{
	int alpha_;
	bool IsHit_;
	int hModel_;
	int hPict_;    //�摜�ԍ�
public:



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

	bool GetIsHit() { return IsHit_; };
};