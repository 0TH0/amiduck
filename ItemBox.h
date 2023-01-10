#pragma once
#include "Engine/GameObject.h"
#include "Engine/Particle.h"

//�V�[�����Ǘ�����N���X
class ItemBox : public GameObject
{
	int coin_count_;
	int time_;
	bool IsHit_;
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

	int GetCoinCount() { return coin_count_; };

	void PlusCoinCount(int count) { coin_count_ += count; };

	void MinCoinCount(int count) { coin_count_ -= count; };
};