#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Text.h"

//�e�X�g�V�[�����Ǘ�����N���X
class ResultScene : public GameObject
{
public:
	enum class UIName
	{
		FINISH = 0,
		RETRY,
		BACK_TITLE,
		RESULT,
		UI_MAX
	} UIName_;

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ResultScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};