#include "Fire.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Player.h"

//�R���X�g���N�^
Fire::Fire(GameObject* parent)
	: GameObject(parent, "Fire"), hModel_(-1), pLine(nullptr)
{
}

//������
void Fire::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hModel_ = Model::Load("Enemy\\raccoon10.fbx");
	assert(hModel_ >= 0);

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.0f);
	AddCollider(collision);

    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

    transform_.rotate_ = XMFLOAT3(0, 0, 0);

    //�|�����C��������
    pLine = new PoryLine;
    pLine->Load("tex_red.png");

    pLine2 = new PoryLine;
    pLine2->Load("tex_orange.png");

    //�����ʒu�̓v���C���[�̈ʒu�̂��{�P
    Player* pPlayer = (Player*)FindObject("Player");
    PlayerTrans_.position_ = pPlayer->GetPosition();
    transform_.position_ = PlayerTrans_.position_;
    transform_.position_.y = PlayerTrans_.position_.y + 1;
}

//�X�V
void Fire::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
    transform_.rotate_.x += 5;

	time++;

	if (time >= 90)
	{
		KillMe();
	}
	else
	{
        transform_.position_.x++;
	}

    //�|�����C���Ɍ��݂̈ʒu��`����
    pLine->AddPosition(transform_.position_);
    pLine2->AddPosition(transform_.position_);
}

//�`��
void Fire::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

    //�|�����C����`��
    //pLine->Draw();
    //pLine2->Draw();
}

//�J��
void Fire::Release()
{
    //�|�����C�����
    pLine->Release();
    pLine2->Release();
}

void Fire::OnCollision(GameObject* pTarget)
{
	//�G�ɓ�������
	if (pTarget->GetObjectName() == "Enemy")
	{
		pTarget->KillMe();
	}
}