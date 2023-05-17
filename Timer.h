#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

//�e�X�g�V�[�����Ǘ�����N���X
class Timer : public GameObject
{
	Text* pText_;
	unsigned int frame_;	//���t���[���o������
	unsigned int rimit_;	//�c�莞��
	std::string minStr_;	//�c�蕪
	std::string secStr_;	//�c��b
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Timer(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void SetRimit(int rimit) { rimit_ = rimit; };

	int GetRimit() { return rimit_; };
};