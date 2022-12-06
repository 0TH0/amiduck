#include "Player.h"
#include "Engine/Model.h"
//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1),pLine(nullptr)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("box.fbx");
    assert(hModel_ >= 0);

    transform_.scale_ = XMFLOAT3(0.3, 0.3, 0.3);


    //�|�����C��������
    pLine = new PoryLine;
    pLine->Load("tex.png");
}

//�X�V
void Player::Update()
{
    //�����͂����Ⴎ����L���[�u�𓮂����Ă邾��
    {
        XMVECTOR v = { 5.0f,0,0,0 };
        XMMATRIX rotY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
        XMMATRIX rotZ = XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));

        v = XMVector3TransformCoord(v, rotY * rotZ);

        XMStoreFloat3(&transform_.position_, v);

        transform_.rotate_.y += 5.0f;
        transform_.rotate_.z += 3.0f;
    }


    //�|�����C���Ɍ��݂̈ʒu��`����
    pLine->AddPosition(transform_.position_);

}

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);


    //�|�����C����`��
    pLine->Draw();
}

//�J��
void Player::Release()
{
    //�|�����C�����
    pLine->Release();
}