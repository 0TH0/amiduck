#include "Stage.h"
#include "Player.h"
#include "PlayScene.h"
#include "Enemy.h"
#include "Block.h"
#include "Coin.h"
#include "Boss.h"
#include "Boss2.h"
#include "Pipe.h"
#include "Pipe_base.h"
#include "Flag.h"
#include "Player.h"

#include "Engine/SceneManager.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "Engine/Input.h"
#include "Engine/SphereCollider.h"
#include "Engine/BoxCollider.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{

}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    //��
    hModel_[0] = Model::Load("Empty.fbx");
    assert(hModel_[0] >= 0);

    //�u���b�N
    hModel_[1] = Model::Load("log.fbx");
    assert(hModel_[1] >= 0);

    //����[
    hModel_[2] = Model::Load("wood.fbx");
    assert(hModel_[2] >= 0);

    //Csv�ǂݍ���
    CsvReader csv;
    csv.Load("map.csv");

    for (int x = 0; x < 180; x++)
    {
            for (int z = 0; z < 40; z++)
            {
                map_[x][0][z] = csv.GetValue(x, z);

                ////�u���b�N�o��
                //if (map_[x][y] == 2)
                //{
                //    Block* pBlock = Instantiate<Block>(GetParent());
                //    pBlock->SetPosition(x, y, 0);
                //}

                ////�y�Ǎ��{�o��
                //if (map_[x][y] == 3)
                //{
                //    Pipe_base* pPipe_base = Instantiate<Pipe_base>(GetParent());
                //    pPipe_base->SetPosition(x + 0.5f, y, 0);
                //}

                ////�y�ǐ�[�o��
                //if (map_[x][y] == 4)
                //{
                //    Pipe* pPipe= Instantiate<Pipe>(GetParent());
                //    pPipe->SetPosition(x + 0.5f, y, 0);
                //}

                ////���o��
                //if (map_[x][y] == 5)
                //{
                //    Flag* pFlag = Instantiate<Flag>(GetParent());
                //    pFlag->SetPosition(x + 0.5f, y, 0);
                //}

                ////�R�C���o��
                //if (map_[x][y] == 7)
                //{
                //    Coin* pCoin = Instantiate<Coin>(GetParent());
                //    pCoin->SetPosition(x + 0.5, y + 0.75f, 0);
                //}

                ////�{�X�o��
                //if (map_[x][y] == 8)
                //{
                //    Boss* pBoss = Instantiate<Boss>(GetParent());
                //    pBoss->SetPosition(x, y, 0);
                //}

                ////�G�l�~�[�o��
                //if (map_[x][y] == 9)
                //{
                //    Enemy* pEnemy = Instantiate<Enemy>(GetParent());
                //    pEnemy->SetPosition(x, y, 0);
                //}
                ////�{�X2�o��
                //if (map_[x][y] == 10)
                //{
                //    Boss2* pBoss2 = Instantiate<Boss2>(GetParent());
                //    pBoss2->SetPosition(x, y, 0);
                //}
            }
        }
}

//�X�V
void Stage::Update()
{
}

//�`��
void Stage::Draw()
{
    for (int x = 0; x < 180; x++)
    {
        for (int y = 0; y < 1; y++)
        {
            for (int z = 0; z < 40; z++)
            {
                int type = map_[x][0][z];
                transform_.position_.x = x;
                //transform_.position_.y = y;
                transform_.position_.z = -z;
                transform_.rotate_.y = 0;
                transform_.scale_ = XMFLOAT3(1, 1, 1);
                if (map_[x][y][z] == 1)
                {
                    transform_.rotate_.y = 90;
                }
                ////���̈ʒu
                if (map_[x][y][z] == 2)
                {
                    transform_.scale_ = XMFLOAT3(3, 1, 2.5);
                    //transform_.rotate_.y = 45;
                }


                Model::SetTransform(hModel_[type], transform_);
                Model::Draw(hModel_[type]);
            }
        }
    }
}

//�J��
void Stage::Release()
{
}

////�����͕ǂ�
bool Stage::IsWall(int x, int y, int z)
{
    return (map_[x][y][z] == 1);
}

bool Stage::IsWallX(int x, int y, int z)
{
    return (map_[x][y][z] == 2);
}

//bool Stage::IsWallM(int x, int y)
//{
//    return (map_[x][y] == 10);
//}
//
//bool Stage::IsPipe(int x, int y)
//{
//    return (map_[x][y] == 3);
//}