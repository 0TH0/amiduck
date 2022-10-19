#include "Pipe.h"
#include "Block.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"

//�R���X�g���N�^
Pipe::Pipe(GameObject* parent)
    :GameObject(parent, "Pipe"), hModel_(-1)
{
}

//�f�X�g���N�^
Pipe::~Pipe()
{
}

//������
void Pipe::Initialize()
{
    /////////////���f���f�[�^�̃��[�h////////////////////
    hModel_ = Model::Load("Pipe_Edge.fbx");
    assert(hModel_ >= 0);
}

//�X�V
void Pipe::Update()
{
}

//�`��
void Pipe::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Pipe::Release()
{
}