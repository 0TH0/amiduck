#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Particle.h"

//�V�[�����Ǘ�����N���X
class Bomb : public GameObject
{
public:
	int hModel_; 
	Transform PlayerTrans_;
	float plus;
	Particle* pParticle_;
	EmitterData data;

	int starTime_;
	Stage* pStage;
	float speed_;        //�ړ����x
	bool IsStart_;

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Bomb(GameObject* parent);

	~Bomb() override;

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void Start() { IsStart_ = true; };

	void Stop() { IsStart_ = false; };

	void OnCollision(GameObject* pTarget) override;
};