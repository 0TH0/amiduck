#include "Water.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"

namespace
{
    static const float SCROOL = 0.0001f; //1�t���[���œ�������
    static const float posY = -3;
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
    transform_.position_.y = posY;
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