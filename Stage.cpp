#include "Stage.h"
#include "Player.h"
#include "PlayScene.h"
#include "Enemy.h"
#include "Player.h"
#include "Coin.h"

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

void Stage::StageLoad()
{
    //��
    hModel_[empty] = Model::Load("Empty.fbx");
    assert(hModel_[0] >= 0);

    //�u���b�N
    hModel_[log] = Model::Load("log.fbx");
    assert(hModel_[log] >= 0);

    //����[
    hModel_[coin] = Model::Load("wood2.fbx");
    assert(hModel_[coin] >= 0);
}

//������
void Stage::Initialize()
{
    StageLoad();

    //Csv�ǂݍ���
    CsvReader csv;
    csv.Load("map.csv");

    for (int x = 0; x < 180; x++)
    {
        for (int z = 0; z < 39; z++)
        {
            map_[x][0][z] = csv.GetValue(x, -z + 38);

            ////�R�C���o��
            if (map_[x][0][z] == coin)
            {
                Coin* pCoin = Instantiate<Coin>(GetParent());
                pCoin->SetPosition(x + 0.25, 1, z + 1);
            }

            ////�{�X�o��
            //if (map_[x][y] == 8)
            //{
            //    Boss* pBoss = Instantiate<Boss>(GetParent());
            //    pBoss->SetPosition(x, y, 0);
            //}

            //�G�l�~�[�o��
            if (map_[x][0][z] == enemy)
            {
                Enemy* pEnemy = Instantiate<Enemy>(GetParent());
                pEnemy->SetPosition(x, 1, z + 1);
            }
        }
    }

    pText->Initialize();
}
//�X�V
void Stage::Update()
{
    Player* pPlayer = (Player*)FindObject("Player");

    if (!pPlayer->GetReturn()) PlayerPosX_ = (int)pPlayer->GetPosition().x + 1;
    else PlayerPosX_ = (int)pPlayer->GetPosition().x - 1;

    PlayerPosZ_ = (int)pPlayer->GetPosition().z;

    time_++;

    if (time_ >= 180 && time_ <= 180)
    {
        count_++;
        time_ = 0;
    }

    if (count_ >= 3)
    {
        count_ = 3;
    }

    if (count_ > 0)
    {
        if (Input::IsKeyDown(DIK_B))
        {
            map_[PlayerPosX_][0][PlayerPosZ_ + 2] = 2;
            map_[PlayerPosX_][0][PlayerPosZ_ + 3] = 2;
            map_[PlayerPosX_][0][PlayerPosZ_ + 4] = 2;
            time_ = 0;
            count_--;
        }

        if (PlayerPosZ_ >= 38)
        {
            if (Input::IsKeyDown(DIK_N))
            {
                map_[PlayerPosX_][0][PlayerPosZ_ - 3] = 2;
                map_[PlayerPosX_][0][PlayerPosZ_ - 4] = 2;
                map_[PlayerPosX_][0][PlayerPosZ_ - 5] = 2;
                time_ = 0;
                count_--;
            }
        }
        else
        {
            if (Input::IsKeyDown(DIK_N))
            {
                map_[PlayerPosX_][0][PlayerPosZ_ - 2] = 2;
                map_[PlayerPosX_][0][PlayerPosZ_ - 3] = 2;
                map_[PlayerPosX_][0][PlayerPosZ_ - 4] = 2;
                time_ = 0;
                count_--;
            }
        }
    }
}

//�`��
void Stage::Draw()
{
    for (int x = 0; x < 180; x++)
    {
        for (int y = 0; y < 1; y++)
        {
            for (int z = 0; z < 39; z++)
            {
                int type = map_[x][0][z];
                transform_.position_ = XMFLOAT3(x, 0, z + 1);
                transform_.rotate_ = XMFLOAT3(0, 0, 0);
                transform_.scale_ = XMFLOAT3(1, 1, 1);
                if (map_[x][0][z] == 1)
                {
                    transform_.rotate_.y = 90;
                }
                ////���̈ʒu
                if (map_[x][0][z] == 2 || map_[x][0][z] == enemy)
                {
                    transform_.position_ = XMFLOAT3(x + 0.25, 0.5, z + 1);
                    transform_.scale_ = XMFLOAT3(0.5, 1, 2);
                }

                Model::SetTransform(hModel_[type], transform_);
                Model::Draw(hModel_[type]);
            }
        }
    }

    pText->Draw(100, 200, "count");
    pText->Draw(200, 200, count_);
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

bool Stage::IsWallM(int x, int y, int z)
{
    return (map_[x][y][z] == 2);
}

//bool Stage::IsWallM(int x, int y)
//{
//    return (map_[x][y] == 10);
//}
//
bool Stage::IsPipe(int x, int y, int z)
{
    return (map_[x][y][z] == 2);
}

bool Stage::IsEmpty(int x, int y, int z)
{
    return (map_[x][y][z] == 0);
}