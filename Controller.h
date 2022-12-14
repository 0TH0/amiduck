#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"

//�V�[�����Ǘ�����N���X
class Controller : public GameObject
{
public:
	int hModel_;
	float PlayerPosX_;
	float PlayerPosY_;
	float PlayerPosZ_;
	XMFLOAT3 PlayerPos_;
	float plus;
	bool Is;


	float a = false;
	bool c = false;
	bool b = false;
	int time1 = 0;
	int time2;
	int time3;
	Transform trans[2];
	bool IsPress;
	bool IsReturn;
	bool IsStop;
	float s;
	float t;
	float f;
	float g;

	int time;

	Stage* pStage;
	float speed_;        //�ړ����x
	XMFLOAT3 mousePos_;

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Controller(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void OnCollision(GameObject* pTarget) override;

};