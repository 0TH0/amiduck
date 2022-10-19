#include "Pipe_Base.h"
#include "Block.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

//�R���X�g���N�^
Pipe_base::Pipe_base(GameObject* parent)
    :GameObject(parent, "Pipe_base"), hModel_(-1)
{
}

//�f�X�g���N�^
Pipe_base::~Pipe_base()
{
}

//������
void Pipe_base::Initialize()
{
    /////////////���f���f�[�^�̃��[�h////////////////////
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0.0f, 0.5f, 0), XMFLOAT3(1, 1, 0));
    AddCollider(collision);

    hModel_ = Model::Load("Pipe_Base.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void Pipe_base::Update()
{
}

//�`��
void Pipe_base::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Pipe_base::Release()
{
}