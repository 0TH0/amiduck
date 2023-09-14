#pragma once
#include "../Engine/GameObject.h"
#include "../Stage/Stage.h"
#include "../Engine/VFX.h"

//�V�[�����Ǘ�����N���X
class Bomb : public GameObject
{
public:
	int hModel_;
	XMFLOAT3 playerPos_;
	XMFLOAT3 mousePos_;

	int starDelay_;
	Stage* pStage;
	float speed_;        //�ړ����x

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


};