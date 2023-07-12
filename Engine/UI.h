#pragma once
#include "GameObject.h"

class UI : public GameObject
{
	int hPict_;
	std::string fileName_;
	bool shouldUseHitCursor_;
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	UI(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	virtual void Load(std::string fileName);

	int GetHandle() { return hPict_; };

	void SetShouldUseHitCursor(bool flag) { shouldUseHitCursor_ = flag; };
	bool GetShouldUseHitCursor() {return shouldUseHitCursor_;};
};