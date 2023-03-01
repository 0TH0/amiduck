#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//�e�X�g�V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
	int hPict_;
	int hPictCh_;
	int hPictTuto_;
	int hPictStart_;
	int hPictPlay_;
	int alpha_ = 256;
	bool Is_;
	Text* pText;

	enum class BtState
	{
		NONE = 0,
		PLAY,
		Tutorial
	} btState_;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};