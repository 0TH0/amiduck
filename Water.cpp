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
    //transform_.scale_ = XMFLOAT3(500, 0.1, 500);
    //transform_.position_ = XMFLOAT3(-500, -1, -500);
    transform_.scale_ = XMFLOAT3(2, 2, 2);
    Model::SetSahder(hModel_, Direct3D::SHADER_NORMALMAP);
}

//�X�V
void Water::Update()
{
    //transform_.rotate_.y += 0.5f;
}

//�`��
void Water::Draw()
{
    //for (int x = 0; x <= 200; x += 5)
    //{
    //    for (int z = 0; z <= 200; z += 5)
    //    {
    //        transform_.position_.x = -10 + x;
    //        transform_.position_.z = -10 + z;
    //        Model::SetSahder(hModel_, Direct3D::SHADER_3D);
    //        Model::SetTransform(hModel_, transform_);
    //        Model::Draw(hModel_);
    //    }
    //}

    for (int x = 0; x <= 50; x += 10)
    {
        for (int z = 0; z <= 50; z += 10)
        {
            transform_.position_.x = -10 + x;
            transform_.position_.z = -10 + z;

            Model::SetTransform(hModel_, transform_);
            Model::Draw(hModel_);
        }
    }
}

//�J��
void Water::Release()
{
}