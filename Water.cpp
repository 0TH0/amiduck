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
    hModel_ = Model::Load("Water\\water3.fbx");
    assert(hModel_ >= 0);
    transform_.position_ = { 5,-3 ,5 };
    transform_.scale_ = XMFLOAT3(24, 0.1, 24);
    Model::SetSahder(hModel_, Direct3D::SHADER_WATER);
}

//�X�V
void Water::Update()
{
    scroll_ += 0.0002f;

    Model::SetUvScroll(hModel_, scroll_);

}

//�`��
void Water::Draw()
{
    transform_.scale_ = XMFLOAT3(24, 0.1, 24);
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Water::Release()
{
}