#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Instructions.h"
#include "Engine/Text.h"

//�����V�[�����Ǘ�����N���X
class PlayScene : public GameObject
{
public:
	Player* pPlayer;
	Text* pText;
	Transform playerTrans;

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};