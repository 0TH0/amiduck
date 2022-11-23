#include "Stage.h"
#include "Player.h"
#include "PlayScene.h"
#include "Enemy.h"
#include "Player.h"

#include "Engine/SceneManager.h"
#include "Engine/Model.h"
#include "Engine/CsvReader.h"
#include "Engine/Input.h"
#include "Engine/SphereCollider.h"
#include "Engine/BoxCollider.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")
{

}

//デストラクタ
Stage::~Stage()
{
}

void Stage::StageLoad()
{
    //空箱
    hModel_[0] = Model::Load("Empty.fbx");
    assert(hModel_[0] >= 0);

    //ブロック
    hModel_[1] = Model::Load("log.fbx");
    assert(hModel_[1] >= 0);

    //旗先端
    hModel_[2] = Model::Load("wood2.fbx");
    assert(hModel_[2] >= 0);
}

//初期化
void Stage::Initialize()
{
    StageLoad();

    //Csv読み込み
    CsvReader csv;
    csv.Load("map.csv");

    for (int x = 0; x < 180; x++)
    {
            for (int z = 0; z < 39; z++)
            {
                map_[x][0][z] = csv.GetValue(x, -z + 38);

                ////ブロック登場
                //if (map_[x][y] == 2)
                //{
                //    Block* pBlock = Instantiate<Block>(GetParent());
                //    pBlock->SetPosition(x, y, 0);
                //}

                ////土管根本登場
                //if (map_[x][y] == 3)
                //{
                //    Pipe_base* pPipe_base = Instantiate<Pipe_base>(GetParent());
                //    pPipe_base->SetPosition(x + 0.5f, y, 0);
                //}

                ////土管先端登場
                //if (map_[x][y] == 4)
                //{
                //    Pipe* pPipe= Instantiate<Pipe>(GetParent());
                //    pPipe->SetPosition(x + 0.5f, y, 0);
                //}

                ////旗登場
                //if (map_[x][y] == 5)
                //{
                //    Flag* pFlag = Instantiate<Flag>(GetParent());
                //    pFlag->SetPosition(x + 0.5f, y, 0);
                //}

                ////コイン登場
                //if (map_[x][y] == 7)
                //{
                //    Coin* pCoin = Instantiate<Coin>(GetParent());
                //    pCoin->SetPosition(x + 0.5, y + 0.75f, 0);
                //}

                ////ボス登場
                //if (map_[x][y] == 8)
                //{
                //    Boss* pBoss = Instantiate<Boss>(GetParent());
                //    pBoss->SetPosition(x, y, 0);
                //}

                ////エネミー登場
                //if (map_[x][y] == 9)
                //{
                //    Enemy* pEnemy = Instantiate<Enemy>(GetParent());
                //    pEnemy->SetPosition(x, y, 0);
                //}
                ////ボス2登場
                //if (map_[x][y] == 10)
                //{
                //    Boss2* pBoss2 = Instantiate<Boss2>(GetParent());
                //    pBoss2->SetPosition(x, y, 0);
                //}
            }
        }

    pText->Initialize();
}

//更新
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

//描画
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
                ////旗の位置
                if (map_[x][0][z] == 2)
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

//開放
void Stage::Release()
{
}

////そこは壁か
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