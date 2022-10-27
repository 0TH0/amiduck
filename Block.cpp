#include "Block.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

//�R���X�g���N�^
Block::Block(GameObject* parent)
    :GameObject(parent, "Block"), hModel_(-1)
{
}

//�f�X�g���N�^
Block::~Block()
{
}

//������
void Block::Initialize()
{
    /////////////���f���f�[�^�̃��[�h////////////////////
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0.5f, 0.5f, 0), XMFLOAT3(1, 1, 0));
    AddCollider(collision);

    hModel_ = Model::Load("log.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void Block::Update()
{
}

//�`��
void Block::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Block::Release()
{
}