#pragma once
#include "Engine/GameObject.h"
#include "Stage/Stage.h"

//�V�[�����Ǘ�����N���X
class Controller : public GameObject
{
	XMFLOAT3 mousePos_;
	const float Move_;		//�ړ����x
	const char Rotate_;		//��]���x
	float PrevPosX_;
	float PrevPosY_;
public:

	void CrickRight();

	enum class cameraState
	{
		camera1 = 0,
		camera2
	}cameraState_;

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

	void PlayerCamera();

	void EnemyCamera();
};