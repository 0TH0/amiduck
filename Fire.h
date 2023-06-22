#pragma once
#include "Engine/GameObject.h"
#include "Engine/VFX.h"
#include "Engine/Astar.h"

//�e�X�g�V�[�����Ǘ�����N���X
class Fire : public GameObject
{
	int hModel_;
	Transform trans;
	bool first_;
	bool right_; //�E����ɂ��邩
	XMFLOAT3 playerPos_;
	int count_;
	Astar AI_;
	bool CanMove_;
	int totalCell;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Fire(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetRight(bool right) { right_ = right; };
};