#pragma once
#include "Engine/GameObject.h"
#include "Engine/Particle.h"

//�e�X�g�V�[�����Ǘ�����N���X
class Mushroom : public GameObject
{
	int hModel_;
	Particle* pParticle_;
	Transform trans;
	bool first_;
	bool right_; //�E����ɂ��邩
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Mushroom(GameObject* parent);

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