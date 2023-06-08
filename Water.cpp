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
    hModel_ = Model::Load("Water\\water.fbx");
    assert(hModel_ >= 0);
    transform_.position_ = { 10,0,10 };
    transform_.scale_ = XMFLOAT3(500, 0.1, 500);
    Model::SetSahder(hModel_);
}

static float scroll;

//�X�V
void Water::Update()
{
    transform_.rotate_.y += 0.05f;
    scroll += 0.002f;

    Model::SetUvScroll(hModel_, scroll);

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