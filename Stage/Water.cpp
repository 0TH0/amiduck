#include "Water.h"
#include "../Engine/Model.h"

namespace
{
    static const float SCROOL = 0.0001f; //1�t���[���œ�������
    static const XMFLOAT3 pos = { 0,-3,0 };
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
    hModel_ = Model::Load("Water\\water.fbx");
    assert(hModel_ >= 0);
    transform_.position_.y = pos.y;
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