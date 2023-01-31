#pragma once
#include "Engine/GameObject.h"
#include "Engine/Particle.h"

//�V�[�����Ǘ�����N���X
class Star : public GameObject
{
	int coin_count_;
	int time_;
	bool IsHit_;
	Particle* pParticle_;
public:

	int hModel_;
	int hPict_;    //�摜�ԍ�

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Star(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void OnCollision(GameObject* pTarget) override;

	void StarEffect();
};