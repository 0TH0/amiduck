#include "Fire.h"
#include "Engine/Model.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"
#include "Player.h"

//�R���X�g���N�^
Fire::Fire(GameObject* parent)
	: GameObject(parent, "Fire"), hModel_(-1), pLine(nullptr)
{
}

//������
void Fire::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hModel_ = Model::Load("fire.fbx");
	assert(hModel_ >= 0);

	//�����蔻��
	SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
	AddCollider(collision);

    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

    transform_.rotate_ = XMFLOAT3(0, 90, 0);

    //�|�����C��������
    pLine = new PoryLine;
    pLine->Load("tex_red.png");

    pLine2 = new PoryLine;
    pLine2->Load("tex_orange.png");

    Player* pPlayer = (Player*)FindObject("Player");
    PlayerPos_ = pPlayer->GetPosition();
    transform_.position_ = PlayerPos_;
}

//�X�V
void Fire::Update()
{
	Player* pPlayer = (Player*)FindObject("Player");
    transform_.position_ = PlayerPos_;

	plus = 1;
	time++;

	if (Input::IsKeyDown(DIK_SPACE))
	{
		if (!Is)
		{
            PlayerPos_ = pPlayer->GetPosition();
			Is = true;
		}
	}

	if (time >= 90)
	{
		KillMe();
	}
	else
	{
		PlayerPos_.x += plus;
	}

    //�|�����C���Ɍ��݂̈ʒu��`����
    pLine->AddPosition(PlayerPos_);
    pLine2->AddPosition(PlayerPos_);

    ///////////////////////// ���݂������̏��� //////////////////////////////////////////
   
    //////////////////�ǂƂ̏Փ˔���///////////////////////
    //int objX = transform_.position_.x;
    //int objY = transform_.position_.y;
    //int objZ = transform_.position_.z;
    //////�ǂ̔���(��)
    //if (pStage->IsWall(objX, objY, objZ))
    //{
    //    transform_.position_.y = (int)(transform_.position_.y) + 0.8;
    //}
    //if (pStage->IsWallX(objX, objY, objZ))
    //{
    //    transform_.position_.y = (int)(transform_.position_.y) + 0.8;
    //}
    //if (!a && !b && pStage->IsEmpty((float)objX + 4, objY, objZ))
    //{
    //    IsReturn = true;
    //}
    //if (!a && !b && pStage->IsEmpty((float)objX - 2.5, objY, objZ))
    //{
    //    IsReturn = false;
    //}
    //if (IsReturn)
    //{
    //    transform_.position_.x -= speed_;
    //}
    //else
    //{
    //    transform_.position_.x += speed_;
    //}
    //if (!b && time2 > 4)
    //{
    //    if (pStage->IsWallM(objX, objY, objZ - 3))
    //    {
    //        speed_ = 0;
    //        a = true;
    //        time2 = 0;
    //    }
    //}
    ////�E�ɍs��
    //if (a)
    //{
    //    IsStop = false;
    //    if (g <= 0)
    //    {
    //        s = 0.2f;
    //        t += s;
    //        if (t >= 6)
    //        {
    //            trans[0].position_ = transform_.position_;
    //            time1 = 0;
    //            s = 0;
    //            t = 0;
    //            a = false;
    //            speed_ = 0.2;
    //        }
    //        else
    //        {
    //            transform_.position_.z -= s;
    //        }
    //    }
    //}
    ////���ɍs��
    //else
    //{
    //    //�~�܂��Ă��Ȃ�������
    //    if (!IsStop)
    //    {
    //        time2++;
    //        if (!b) time1++;
    //    }
    //    if (time1 > 4)
    //    {
    //        if (pStage->IsPipe(objX, objY, objZ + 2))
    //        {
    //            speed_ = 0;
    //            b = true;
    //        }
    //    }
    //    if (b)
    //    {
    //        IsStop = false;
    //        f = 0.2f;
    //        g += f;
    //        if (g >= 6)
    //        {
    //            trans[1].position_ = transform_.position_;
    //            time2 = 0;
    //            g = 0;
    //            f = 0;
    //            b = false;
    //            speed_ = 0.2;
    //            time1 = 0;
    //        }
    //        else
    //        {
    //            transform_.position_.z += f;
    //        }
    //    }
    //}
}

//�`��
void Fire::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

    //�|�����C����`��
    pLine->Draw();
    pLine2->Draw();
}

//�J��
void Fire::Release()
{
    //�|�����C�����
    pLine->Release();
    pLine2->Release();
}

void Fire::OnCollision(GameObject* pTarget)
{
	//�G�ɓ�������
	if (pTarget->GetObjectName() == "Enemy")
	{
		pTarget->KillMe();
	}
}