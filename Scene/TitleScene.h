#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Text.h"

//�e�X�g�V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
public:

	enum class UIName
	{
		PLAY = 0,
		TUTORIAL,
		TITLE,
		CHAR,
		UI_MAX
	} UIName_;

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