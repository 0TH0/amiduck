#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Engine/Text.h"
#include "ItemBox.h"

//�����V�[�����Ǘ�����N���X
class ItemUI: public GameObject
{
	int hItemPict_[4];
	int hPict_;
	int hPictWood_;

	int alpha_;
	ItemBox* pItemBox_;
	bool IsItem_;

public:
	//���̃A�C�e���������Ă��邩
	enum class Item
	{
		BOMB,
		BALL,
		WING,
		ITEM_MAX
	} item_;

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ItemUI(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	void DrawWoodUI(Transform tra);

	void DrawItem(Transform tra);

	void SetItem(Item item) { item_ = item; };
	Item GetItem() { return item_; };

	void SetIsItem(bool IsItem) { IsItem_ = IsItem; };
	bool IsItem() { return IsItem_; };
};