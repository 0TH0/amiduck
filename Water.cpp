#include "Water.h"
#include "Engine/Model.h"

namespace
{
    static const int SCROOL = 0.0001f; //1�t���[���œ�������
}

//�R���X�g���N�^
Water::Water(GameObject* parent)
    :GameObject(parent, "Water"), hModel_(-1),scroll_(0.f)
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
    hModel_ = Model::Load("Water\\water5.fbx");
    assert(hModel_ >= 0);
    transform_.position_.y = -3;
    //transform_.scale_ = XMFLOAT3(0.5 ,0.1, 0.5);
    Model::SetSahder(hModel_, Direct3D::SHADER_WATER);
}

//�X�V
void Water::Update()
{
    scroll_ += SCROOL;
    Model::SetUvScroll(hModel_, scroll_);
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