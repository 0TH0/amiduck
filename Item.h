#pragma once
#include "Engine/GameObject.h"
#include "Player.h"
#include "Engine/Text.h"
#include "ItemBox.h"

class Itembox;

//�����V�[�����Ǘ�����N���X
class Item: public GameObject
{
	int hItemPict_[4];
	int hPict_;
	int hPictWood_;
	int alpha_;
	ItemBox* pItemBox_;
	bool IsItem_;
	int woodCoolTime_;
	int woodCount_;
public:
	//���̃A�C�e���������Ă��邩
	enum class ItemNum
	{
		BOMB,
		BALL,
		WING,
		ITEM_MAX
	} item_;

	enum class WoodCount
	{
		NONE,
		ONE,
		TWO,
		THREE
	};

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Item(GameObject* parent);

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	void DrawWoodUI(Transform tra);

	void DrawItem();

	void SetItem(ItemNum item) { item_ = item; };
	ItemNum GetItem() { return item_; };

	void SetIsItem(bool IsItem) { IsItem_ = IsItem; };
	bool GetIsItem() { return IsItem_; };

	void MinWoodCount() { woodCount_ -= 1;};
	void PluswoodCount() { woodCount_ += 1; };
	int GetwoodCount() { return woodCount_; };
};