#pragma once
#include "../Engine/GameObject.h"
#include "../Stage/Stage.h"
#include "../Engine/VFX.h"

//�V�[�����Ǘ�����N���X
class BombGuide : public GameObject
{
public:
	int hModel_;
	Transform PlayerTrans_;
	float plus;
	EmitterData data;
	int time;
	int starDelay_;
	Stage* pStage;
	float speed_;        //�ړ����x
	bool IsReturn_;

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	BombGuide(GameObject* parent);

	~BombGuide() override;

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};