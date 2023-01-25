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
    transform_.scale_ = XMFLOAT3(1000, 0.1, 1000);
    transform_.position_ = XMFLOAT3(20, -1, 30);
}

//�X�V
void Water::Update()
{
    //transform_.rotate_.y += 1.0f;
}

//�`��
void Water::Draw()
{
    Model::SetSahder(hModel_, Direct3D::SHADER_WATER);
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Water::Release()
{
}