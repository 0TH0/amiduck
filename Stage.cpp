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

    hModel_[enemy] = Model::Load("log.fbx");
    assert(hModel_[enemy] >= 0);

    hModel_[player] = Model::Load("log.fbx");
    assert(hModel_[player] >= 0);
}

void Stage::Cloud()
{
    data.textureFileName = "Particle\\Cloud.png";
    data.positionErr = XMFLOAT3(0.1, 0, 0.1);
    data.delay = 0;
    data.number = 5;
    data.lifeTime = 60;
    data.dir = XMFLOAT3(0, 1, 0);
    data.dirErr = XMFLOAT3(0, 0, 0);
    data.speed = 0.01f;
    data.speedErr = 0.5;
    data.size = XMFLOAT2(2, 2);
    data.sizeErr = XMFLOAT2(0.4, 0.4);
    data.scale = XMFLOAT2(1.03, 1.02);
    float color = 0.5;
    data.color = XMFLOAT4(color, color, color, 0.1);
    pParticle_->Start(data);
}

void Stage::SetCloudPos(float x, float y, float z)
{
    data.position.x = x;
    data.position.y = y;
    data.position.z = z;
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

            //�R�C���o��
            if (map_[x][0][z] == coin)
            {
                Coin* pCoin = Instantiate<Coin>(GetParent());
                pCoin->SetPosition(x + 0.25, 1, z + 1);
            }

            //�G�l�~�[�o��
            if (map_[x][0][z] == enemy)
            {
                Enemy* pEnemy = Instantiate<Enemy>(GetParent());
                pEnemy->SetPosition(x, 1, z + 1);
            }

            //�v���C���[�o��
            if (map_[x][0][z] == player)
            {
                Player* pPlayer = Instantiate<Player>(GetParent());
                pPlayer->SetPosition(x, 1, z + 1);
            }
        }
    }

    pText->Initialize();
    pParticle_ = Instantiate<Particle>(this);
}
//�X�V
void Stage::Update()
{
    Player* pPlayer = (Player*)FindObject("Player");

    if (!pPlayer->GetReturn()) player_pos_.x = (int)pPlayer->GetPosition().x + 1;
    else player_pos_.x = (int)pPlayer->GetPosition().x - 1;

    player_pos_.z = (int)pPlayer->GetPosition().z;

    time_++;

    if (time_ == 180)
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
        if (Input::IsKeyDown(DIK_A))
        {
            map_[(int)player_pos_.x][0][(int)player_pos_.z + 2] = 2;
            map_[(int)player_pos_.x][0][(int)player_pos_.z + 3] = 2;
            map_[(int)player_pos_.x][0][(int)player_pos_.z + 4] = 2;
            time_ = 0;
            count_--;
            SetCloudPos(player_pos_.x, player_pos_.y + 1, player_pos_.z + 4);
            Cloud();
        }

        if (Input::IsKeyDown(DIK_D))
        {
            if ((int)player_pos_.z >= 38)
            {
                map_[(int)player_pos_.x][0][(int)player_pos_.z - 3] = 2;
                map_[(int)player_pos_.x][0][(int)player_pos_.z - 4] = 2;
                map_[(int)player_pos_.x][0][(int)player_pos_.z - 5] = 2;
                time_ = 0;
                count_--;
                SetCloudPos(player_pos_.x, player_pos_.y + 1, player_pos_.z - 3);
                Cloud();
            }
            else
            {
                if (Input::IsKeyDown(DIK_D))
                {
                    map_[(int)player_pos_.x][0][(int)player_pos_.z - 2] = 2;
                    map_[(int)player_pos_.x][0][(int)player_pos_.z - 3] = 2;
                    map_[(int)player_pos_.x][0][(int)player_pos_.z - 4] = 2;
                    time_ = 0;
                    count_--;
                    SetCloudPos(player_pos_.x, player_pos_.y + 1, player_pos_.z - 2);
                    Cloud();
                }
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
                if (map_[x][0][z] == coin)
                {
                    transform_.position_ = XMFLOAT3(x + 0.25, 0.5, z + 1);
                    transform_.scale_ = XMFLOAT3(0.5, 1, 2);
                }
                if (map_[x][0][z] == enemy || map_[x][0][z] == player)
                {
                    transform_.rotate_.y = 90;
                }

                //Direct3D::SetShader(Direct3D::SHADER_NORMALMAP);
                //Direct3D::SetShader(Direct3D::SHADER_3D);
                Model::SetTransform(hModel_[type], transform_);
                Model::Draw(hModel_[type]);
            }
        }
    }

    //pText->Draw(100, 200, "count");
    //pText->Draw(200, 200, count_);
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