#include "Enemy.h"
#include "Player.h"
#include "Pipe_base.h"

#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), hModel_(-1),
    SPEED(0.02)
{
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//������
void Enemy::Initialize()
{
    hModel_ = Model::Load("Enemy.fbx");
    assert(hModel_ >= 0);

    SphereCollider* collision = new SphereCollider(XMFLOAT3(0.0f, 0.3f, 0.0f), 0.3f);
    AddCollider(collision);

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);
}

void Enemy::Update()
{
   // // 1�t���[���O�̍��W
   // XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

   // //�ړ�
   // transform_.position_.x += SPEED;

   // //�d��
   // GRAVITY = 0.075f;
   // move_.y = -GRAVITY;
   // transform_.position_.y += move_.y;

   // //////////////////�ǂƂ̏Փ˔���///////////////////////
   // float objX = transform_.position_.x;
   // float objY = transform_.position_.y;

   // //�ǂ̔���(��)
   // if (pStage->IsWall((int)objX, (int)(objY - 0.2f)) || pStage->IsWallX((int)objX, (int)(objY - 0.2f)))
   // {
   //     transform_.position_.y = (float)(int)(transform_.position_.y) + 0.2f;
   // }

   // //�ǂ̔���(��)
   // if (pStage->IsWall((int)objX, (int)(objY + 0.2f)) || pStage->IsWallX((int)objX, (int)(objY + 0.2f)))
   // {
   //     transform_.position_.y = (float)(int)(transform_.position_.y + 0.5f) - 0.2f;
   // }

   // //�ǂ̔���(�E)
   // if (pStage->IsWall((int)(objX + 0.2f), (int)objY))
   // {
   //     transform_.position_.x = (float)(int)(transform_.position_.x + 0.5f) - 0.2f;
   //     SPEED *= -1;
   // }

   // //�ǂ̔���(��)
   // if (pStage->IsWall((int)(objX - 0.2f), (int)objY))
   // {
   //     transform_.position_.x = (float)(int)(transform_.position_.x) + 0.2f;
   //     SPEED *= -1;
   // }

   // //////////////////�y�ǂƂ̏Փ˔���///////////////////////
   // // 
   // //�y�ǂ̔���(��)
   // if (pStage->IsPipe((int)objX, (int)(objY - 0.2f)))
   // {
   //     transform_.position_.y = (float)(int)(transform_.position_.y) + 0.2f;
   // }

   // //�y�ǂ̔���(��)
   // if (pStage->IsPipe((int)objX, (int)(objY + 0.2f)))
   // {
   //     transform_.position_.y = (float)(int)(transform_.position_.y + 0.5f) - 0.4f;
   // }

   // //�y�ǂ̔���(�E)
   // if (pStage->IsPipe((int)(objX + 0.4f), (int)objY))
   // {
   //     transform_.position_.x = (float)(int)(transform_.position_.x + 0.5f) - 0.4f;
   //     SPEED *= -1;
   // }

   // //�y�ǂ̔���(��)
   // if (pStage->IsPipe((int)(objX - 0.4f), (int)objY))
   // {
   //     transform_.position_.x = (float)(int)(transform_.position_.x) + 0.4f;
   //     SPEED *= -1;
   // }

   // ///////////// �G�̌��� /////////////

   ////���݂̈ʒu�̃x�N�g��
   // XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);

   // //����ʒu�̃x�N�g��
   // XMVECTOR nowMove = nowPosition - prevPosition;

   // //�ړ��׃N�g��
   // XMVECTOR Length = XMVector3Length(nowMove);

   // //0.1�ȏ�̎��͎��s���Ȃ�
   // if (XMVectorGetX(Length) > 0.01)
   // {
   //     //�p�x�����߂�̂ɒ�����1�ɂ���i���K���j
   //     nowMove = XMVector3Normalize(nowMove);

   //     //��ƂȂ�����̃x�N�g��
   //     XMVECTOR front = { 0, 0, 1, 0 };

   //     //front��move�̊O�ς����߂�
   //     XMVECTOR vecDot = XMVector3Dot(front, nowMove);
   //     float dot = XMVectorGetX(vecDot);

   //     //�����Ă�p�x�����߂�(���W�A��)
   //     float angle = acos(dot);

   //     //front��move�̊O�ς����߂�
   //     XMVECTOR cross = XMVector3Cross(front, nowMove);

   //     //�O�ς��}�C�i�X���Ɖ�����
   //     if (XMVectorGetY(cross) < 0)
   //     {
   //         angle *= -1;
   //     }

   //     //���̊p�x��]������
   //     transform_.rotate_.y = angle * 180.0f / 3.14f;
   // }
}

void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
    if (pTarget->GetObjectName() == "Player")
    {
        KillMe();
    }
}