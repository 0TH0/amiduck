#include "Duck.h"
#include "Engine/Model.h"

//�R���X�g���N�^
Duck::Duck(GameObject* parent)
    :GameObject(parent, "Duck"), hModel_(-1)
{
}

//�f�X�g���N�^
Duck::~Duck()
{
}

//������
void Duck::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Model\\Player\\duck.fbx");
    assert(hModel_ >= 0);
    transform_.scale_ = XMFLOAT3(5, 5, 5);
    transform_.position_ = XMFLOAT3(300, 1, 50);
}

//�X�V
void Duck::Update()
{
    //transform_.rotate_.y += 1.0f;
}

//�`��
void Duck::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Duck::Release()
{
}