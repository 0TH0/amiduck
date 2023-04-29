#include "Water.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Water::Water(GameObject* parent)
    :GameObject(parent, "Water"), hModel_(-1)
{
}

//�f�X�g���N�^
Water::~Water()
{
}

//������
void Water::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Water\\Water.fbx");
    assert(hModel_ >= 0);
    transform_.scale_ = XMFLOAT3(500, 0.1, 500);
    //transform_.position_ = XMFLOAT3(-500, -1, -500);
    //transform_.scale_ = XMFLOAT3(2, 2, 2);
    Model::SetSahder(hModel_, Direct3D::SHADER_3D);
}

//�X�V
void Water::Update()
{
    transform_.rotate_.y += 0.5f;
}

//�`��
void Water::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Water::Release()
{
}