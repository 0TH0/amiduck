#include "Player.h"
#include "Stage.h"
#include "PlayScene.h"
#include "StartScene.h"
#include "Fire.h"
#include "Controller.h"
#include "Enemy.h"

#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"),

    //変数
    hModel_(-1),
    jump_v0(0), GRAVITY(0), angle(0),BossHp(3), hModelBlock_(-1),
    
    //フラグ
    IsJump(false), IsGround(false),

    //定数
    SPEED(0.3f), DUSHSPEED(0.05f),
    CAMERA_POS_Y(-15.0f), CAMERA_TAR_Y(-5.0f)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    hModel_ = Model::Load("Enemy\\raccoon10.fbx");
    assert(hModel_ >= 0);

    //アニメーションの設定
    Model::SetAnimFrame(hModel_, 0, 200, 1.0f);

    //位置
    transform_.position_ = XMFLOAT3(0, 0.5, 38);
    transform_.rotate_ = XMFLOAT3(0, 180, 0);
    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35); 

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    AddCollider(collision);

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    Instantiate<Controller>(this);

    pText->Initialize();

    pParticle_ = Instantiate<Particle>(this);

    //data.textureFileName = "Particle\\Cloud.png";
    //data.positionErr = XMFLOAT3(0.1, 0, 0.1);
    //data.delay = 5;
    //data.number = 1;
    //data.lifeTime = 30;
    //data.dir = XMFLOAT3(0, 1, 0);
    //data.dirErr = XMFLOAT3(0, 0, 0);
    //data.speed = 0.2f;
    //data.accel = 0.98;
    //data.speedErr = 0.0;
    //data.size = XMFLOAT2(2, 2);
    //data.sizeErr = XMFLOAT2(0.4, 0.4);
    //data.scale = XMFLOAT2(1.01, 1.01);
    //data.color = XMFLOAT4(1, 1, 1, 0.2);
    //data.deltaColor = XMFLOAT4(0, 0, 0, -0.002);

    //data.delay = 0;
    //data.number = 80;
    //data.lifeTime = 100;
    //data.positionErr = XMFLOAT3(0.5, 0, 0.5);
    //data.dir = XMFLOAT3(0, 1, 0);
    //data.dirErr = XMFLOAT3(90, 90, 90);
    //data.speed = 0.25f;
    //data.speedErr = 1;
    //data.accel = 0.93;
    //data.size = XMFLOAT2(0.1, 0.1);
    //data.sizeErr = XMFLOAT2(0.4, 0.4);
    //data.scale = XMFLOAT2(0.99, 0.99);
    //data.color = XMFLOAT4(1, 0.5, 0.1, 1);
    //data.deltaColor = XMFLOAT4(0, 0, 0, 0);
    //data.gravity = 0.003f;

    //炎
    {
    }
}

void Player::Update()
{
    if (Input::IsKeyDown(DIK_SPACE))
    {
        //EmitterData data;
        //data.textureFileName = "Particle\\Cloud.png";
        //data.position = transform_.position_;
        //data.positionErr = XMFLOAT3(0.1, 0, 0.1);
        //data.delay = 0;
        //data.number = 5;
        //data.lifeTime = 60;
        //data.dir = XMFLOAT3(0, 1, 0);
        //data.dirErr = XMFLOAT3(0, 0, 0);
        //data.speed = 0.01f;
        //data.speedErr = 0.0;
        //data.size = XMFLOAT2(2, 2);
        //data.sizeErr = XMFLOAT2(0.4, 0.4);
        //data.scale = XMFLOAT2(1.03, 1.02);
        //data.color = XMFLOAT4(0.7, 0.7, 0.7, 0.1);
        //pParticle_->Start(data);

        ////神々しいやつ
        //EmitterData data;

        //data.textureFileName = "Particle\\Cloud.png";
        //data.position = transform_.position_;
        //data.positionErr = XMFLOAT3(0.1, 2, 0.1);
        //data.delay = 0;
        //data.number = 1;
        //data.lifeTime = 150;
        //data.dir = XMFLOAT3(0, 1, 0);
        //data.dirErr = XMFLOAT3(0, 0, 0);
        //data.speed = 0.1f;
        //data.accel = 0.98;
        //data.speedErr = 0.5;
        //data.size = XMFLOAT2(2, 2);
        //data.sizeErr = XMFLOAT2(0.4, 0.4);
        //data.scale = XMFLOAT2(1.01, 1.5);
        //data.color = XMFLOAT4(1, 1, 1, 0.2);
        //data.deltaColor = XMFLOAT4(0, 0, 0, -0.002);
        //pParticle_->Start(data);

        //EmitterData data;
        //data.textureFileName = "Particle\\Cloud.png";
        //data.position = transform_.position_;
        //data.delay = 0;
        //data.number = 80;
        //data.lifeTime = 30;
        //data.dir = XMFLOAT3(1, 0, 0);
        //data.dirErr = XMFLOAT3(180, 90, 90);
        //data.speed = 0.4f;
        //data.speedErr = 1;
        //data.size = XMFLOAT2(1, 0.5);
        //data.sizeErr = XMFLOAT2(0.4, 0.4);
        //data.scale = XMFLOAT2(1.05, 1.05);
        //data.color = XMFLOAT4(0.2, 0.2, 1, 1);
        //data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
        //data.gravity = 0.003f;
        //pParticle_->Start(data);

        //data.color = XMFLOAT4(0.5, 0.5, 0, 1);
        //pParticle_->Start(data);

        //data.delay = 0;
        //data.number = 80;
        //data.lifeTime = 100;
        //data.positionErr = XMFLOAT3(0.5, 0, 0.5);
        //data.dir = XMFLOAT3(0, 1, 0);
        //data.dirErr = XMFLOAT3(180, 180, 180);
        //data.speed = 0.5f;
        //data.speedErr = 1;
        //data.accel = 0.93;
        //data.size = XMFLOAT2(0.1, 0.1);
        //data.sizeErr = XMFLOAT2(0.4, 0.4);
        //data.scale = XMFLOAT2(0.99, 0.99);
        //data.color = XMFLOAT4(1, 1, 0.1, 1);
        //data.deltaColor = XMFLOAT4(0, 0, 0, 0);
        //data.gravity = 0.003f;
        //pParticle_->Start(data);
    }


    //if (Input::IsKeyDown(DIK_SPACE))
    //{
    //    EmitterData data;
    //    data.textureFileName = "Cloud.png";
    //    data.position = XMFLOAT3(0, 0.05, 0);
    //    data.delay = 0;
    //    data.number = 80;
    //    data.lifeTime = 20;
    //    data.dir = XMFLOAT3(0, 1, 0);
    //    data.dirErr = XMFLOAT3(90, 90, 90);
    //    data.speed = 0.1f;
    //    data.speedErr = 0.8;
    //    data.size = XMFLOAT2(1, 1);
    //    data.sizeErr = XMFLOAT2(0.4, 0.4);
    //    data.scale = XMFLOAT2(1.05, 1.05);
    //    data.color = XMFLOAT4(1, 1, 0.1, 1);
    //    data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
    //    pParticle_->Start(data);





    //    data.delay = 0;
    //    data.number = 80;
    //    data.lifeTime = 100;
    //    data.positionErr = XMFLOAT3(0.5, 0, 0.5);
    //    data.dir = XMFLOAT3(0, 1, 0);
    //    data.dirErr = XMFLOAT3(90, 90, 90);
    //    data.speed = 0.25f;
    //    data.speedErr = 1;
    //    data.accel = 0.93;
    //    data.size = XMFLOAT2(0.1, 0.1);
    //    data.sizeErr = XMFLOAT2(0.4, 0.4);
    //    data.scale = XMFLOAT2(0.99, 0.99);
    //    data.color = XMFLOAT4(1, 1, 0.1, 1);
    //    data.deltaColor = XMFLOAT4(0, 0, 0, 0);
    //    data.gravity = 0.003f;
    //    pParticle_->Start(data);





    //}

    pStage = (Stage*)FindObject("Stage");
    Enemy* pEnemy = (Enemy*)FindObject("Enemy");


    //EnemyPos_ = pEnemy->GetPosition();
    //EnemyPos_.x = EnemyPos_.x - 5;

    //if (Input::IsKeyDown(DIK_L))
    //{
    //    transform_.position_ = EnemyPos_;
    //}

    // 1フレーム前の座標
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

    //停止する
    if(Input::IsKeyDown(DIK_F))
    {
        if (!IsStop)
        {
            SPEED = 0;
            IsStop = true;
        }
        else
        {
            SPEED = 0.3f;
            IsStop = false;
        }
    }

    /////////////////////////移動/////////////////////////

    ////左移動
    //if (Input::IsKey(DIK_W))
    //{
    //    transform_.position_.x += SPEED;
    //}

    ////左移動
    //if (Input::IsKey(DIK_S))
    //{
    //    transform_.position_.x -= SPEED;
    //}

    //if (Input::IsKey(DIK_A))
    //{
    //    transform_.position_.z += SPEED;
    //}

    //if (Input::IsKey(DIK_D))
    //{
    //    transform_.position_.z -= SPEED;
    //}

    ////右移動
    //if (Input::IsKey(DIK_D))
    //{
    //    transform_.position_.x += SPEED;
    //}

    //if (Input::IsKey(DIK_W))
    //{
    //    transform_.position_.z += SPEED;
    //}

    //if (Input::IsKey(DIK_S))
    //{
    //    transform_.position_.z -= SPEED;
    //}

    ////左ダッシュ
    //if ((Input::IsKey(DIK_A)) && (Input::IsKey(DIK_B)))
    //{
    //    transform_.position_.x -= DUSHSPEED;
    //}

    ////右ダッシュ
    //if ((Input::IsKey(DIK_D)) && (Input::IsKey(DIK_B)))
    //{
    //    transform_.position_.x += DUSHSPEED;
    //}

    ////カメラ
    //Camera::SetPosition(XMFLOAT3(transform_.position_.x, 7, CAMERA_POS_Y));
    //Camera::SetTarget(XMFLOAT3(transform_.position_.x, 7, CAMERA_TAR_Y));

    ////カメラ移動制限
    //if (transform_.position_.x < 8.0f)
    //{
    //    Camera::SetTarget(XMFLOAT3(8, 7, -5));
    //    Camera::SetPosition(XMFLOAT3(8, 7, -15));
    //}

    //////////ジャンプ///////
    //if (Input::IsKeyDown(DIK_SPACE)) //&& (IsJump == 0))
    //{
    //    ////初速度
    //    //jump_v0 = 0.2f;
    //    ////重力
    //    //GRAVITY = 0.008f;

    //    ////初速度を加える
    //    //move_.y = jump_v0;

    //    ////重力を加える
    //    //move_.y += GRAVITY;

    //    ////ジャンプフラグ
    //    //IsJump = 1;
    //    SPEED = 0;
    //}

    ////ジャンプ中の重力
    if (IsJump == 1)
    {
        //重力
        move_.y -= GRAVITY;
        transform_.position_.y += move_.y;
    }

    //ジャンプしてない時の重力
    if (IsJump == 0)
    {
        //重力
        GRAVITY = 0.1f;

        //重力を加える
        move_.y = -GRAVITY;
        transform_.position_.y += move_.y;
    }

    //if (a)
    //{
        //if (transform_.position_.y < 1.0)
        //{
        //    transform_.position_.y = 1.0;
        //    IsJump = false;
        //}
    //}
    
    ///////////// プレイヤーの向き /////////////

    ////現在の位置のベクトル
    //XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);

    ////今回位置のベクトル
    //XMVECTOR nowMove = nowPosition - prevPosition;

    ////移動べクトル
    //XMVECTOR Length = XMVector3Length(nowMove);

    ////0.1以上の時は実行しない
    //if (XMVectorGetX(Length) > 0.01)
    //{
    //    //角度を求めるのに長さを1にする（正規化）
    //    nowMove = XMVector3Normalize(nowMove);

    //    //基準となる向きのベクトル
    //    XMVECTOR front = { 0, 0, 1, 0 };

    //    //frontとmoveの外積を求める
    //    XMVECTOR vecDot = XMVector3Dot(front, nowMove);
    //    float dot = XMVectorGetX(vecDot);

    //    //向いてる角度を求める(ラジアン)
    //    angle = acos(dot);

    //    //frontとmoveの外積を求める
    //    XMVECTOR cross = XMVector3Cross(front, nowMove);

    //    //外積がマイナスだと下向き
    //    if (XMVectorGetY(cross) < 0)
    //    {
    //        angle *= -1;
    //    }

    //    //その角度回転させる
    //    transform_.rotate_.y = angle * 180.0f / 3.14f;
    //}

    //////////////////壁との衝突判定///////////////////////
    int objX = transform_.position_.x;
    int objY = transform_.position_.y;
    int objZ = transform_.position_.z;

    ////壁の判定(上)
    if (pStage->IsWall(objX, objY ,objZ))
    {
        transform_.position_.y = (int)(transform_.position_.y) + 0.8;
        IsJump = 0;
    }
    if (pStage->IsWallX(objX, objY, objZ))
    {
        transform_.position_.y = (int)(transform_.position_.y) + 0.8;
        IsJump = 0;
    }

    if (!a && !b && pStage->IsEmpty((float)objX + 5, objY, objZ))
    {
        IsReturn = true;
    }
    if (!a && !b && pStage->IsEmpty((float)objX - 2.5, objY, objZ))
    {
        IsReturn = false;
    }
    if (IsReturn)
    {
        transform_.position_.x -= SPEED;
    }
    else
    {
        transform_.position_.x += SPEED;
    }


    ///////////////////////// あみだくじの処理 ///////////////////////////////////////////

    if (!b && time2 > 4)
    {
        if (pStage->IsWallM(objX, objY, objZ - 3))
        {
            SPEED = 0;
            a = true;
            time2 = 0;
        }
    }

    //右に行く
    if (a)
    {
        IsStop = false;

        transform_.rotate_ = XMFLOAT3(0, -90, 0);
        if (g <= 0)
        {
            s = 0.2f;
            t += s;
            if (t >= 6)
            {
                trans[0].position_ = transform_.position_;
                time1 = 0;
                s = 0;
                t = 0;
                a = false;
                SPEED = 0.2;
                if (IsReturn)
                {
                    transform_.rotate_ = XMFLOAT3(0, 0, 0);
                }
                else
                {
                    transform_.rotate_ = XMFLOAT3(0, 180, 0);
                }
            }
            else
            {
                transform_.position_.z -= s;
            }
        }
    }
    //左に行く
    else
    {
        //止まっていなかったら
        if (!IsStop)
        {
            time2++;

            if (!b) time1++;
        }

        if (time1 > 4)
        {
            if (pStage->IsPipe(objX, objY, objZ + 2))
            {
                SPEED = 0;
                b = true;
            }
        }

        if (b)
        {
            IsStop = false;
            f = 0.2f;
            g += f;
            transform_.rotate_ = XMFLOAT3(0, 90, 0);
            if (g >= 6)
            {
                trans[1].position_ = transform_.position_;
                time2 = 0;
                g = 0;
                f = 0;
                b = false;
                SPEED = 0.2;
                time1 = 0;
                if (IsReturn)
                {
                    transform_.rotate_ = XMFLOAT3(0, 0, 0);
                }
                else
                {
                    transform_.rotate_ = XMFLOAT3(0, 180, 0);
                }
            }
            else
            {
                transform_.position_.z += f;
            }
        }
    }

    if (Input::IsKeyDown(DIK_Z))
    {
        IsVisibled();
    }
    if (Input::IsKeyDown(DIK_X))
    {
        Visible();
    }
    if (Input::IsKeyDown(DIK_C))
    {
        SPEED = -0.2f;
    }
    if (Input::IsKeyDown(DIK_V))
    {
        SPEED = 0.2f;
    }
    if (IsPress)
    {
    }

    //if (pStage->IsPipe(objX, objY, objZ + 2))
    //{
    //    transform_.position_.z += 12;
    //}

    //
    ////壁の判定(下)
    //if (pStage->IsWall((int)objX, (int)(objY + 0.2f)))
    //{
    //    transform_.position_.y = (float)(int)(transform_.position_.y + 0.5f) - 0.4f;
    //    move_.y = -GRAVITY;
    //}

    ////壁の判定(右)
    //if (pStage->IsWall((int)(objX + 0.4f), (int)objY))
    //{
    //    transform_.position_.x = (float)(int)(transform_.position_.x + 0.5f) - 0.4f;
    //}

    ////壁の判定(左)
    //if (pStage->IsWall((int)(objX - 0.4f), (int)objY))
    //{
    //    transform_.position_.x = (float)(int)(transform_.position_.x) + 0.4f;
    //}

    /////////////////////////　シーン切り替え ///////////////////////////

    ////落ちたらゲームオーバーに戻る
    //if (transform_.position_.y < 0)
    //{
    //    SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
    //    pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
    //}

    FollowGround();

    if (!IsBlend())
    {
        if (Input::IsKeyDown(DIK_L))
        {
            Blend();
            EmitterData data;
            data.textureFileName = "Particle\\Cloud.png";
            data.position = transform_.position_;
            data.positionErr = XMFLOAT3(0.1, 0, 0.1);
            data.delay = 0;
            data.number = 5;
            data.lifeTime = 60;
            data.dir = XMFLOAT3(0, 1, 0);
            data.dirErr = XMFLOAT3(0, 0, 0);
            data.speed = 0.01f;
            data.speedErr = 0.0;
            data.size = XMFLOAT2(2, 2);
            data.sizeErr = XMFLOAT2(0.4, 0.4);
            data.scale = XMFLOAT2(1.03, 1.02);
            data.color = XMFLOAT4(0.7, 0.7, 0.7, 0.1);
            pParticle_->Start(data);
        }
    }
    if (Input::IsKeyDown(DIK_K))
    {
        Default();
    }
}

void Player::Draw()
{
    //if (blade_)
    //{
    //    Direct3D::SetBlendMode(Direct3D::BLEND_ADD);
    //}
    //else
    //{
    //    Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);
    //}

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //pText->Draw(20, 20, "rotate.xyz");
    //pText->Draw(50, 50, transform_.rotate_.x);
    //pText->Draw(150, 50, transform_.rotate_.y);
    //pText->Draw(250, 50, transform_.rotate_.z);

    //pText->Draw(20, 100, "transform.xyz");
    //pText->Draw(50, 130, transform_.position_.x);
    //pText->Draw(150, 130, transform_.position_.y);
    //pText->Draw(250, 130, transform_.position_.z);

    //pText->Draw(100, 250, "coin");
    //pText->Draw(200, 250, coin_count_);
}

void Player::Release()
{
}

//何かに当たった
void Player::OnCollision(GameObject* pTarget)
{
    //XMVECTOR vPlayerPos = XMLoadFloat3(&transform_.position_);
    //XMVECTOR Down = { 0,-1,0,0 };

    //float objX = transform_.position_.x;
    //float objY = transform_.position_.y;

    ////ブロックに当たった
    //if (pTarget->GetObjectName() == "Block")
    //{
    //    if (pStage->IsWallX((int)objX, (int)(objY + 0.2f)))
    //    {
    //        pTarget->KillMe();
    //        IsJump = 0;
    //    }
    //}

    ////コインに当たった
    //if (pTarget->GetObjectName() == "Coin")
    //{
    //    pTarget->KillMe();
    //}

    //敵に当たった
    if (pTarget->GetObjectName() == "Enemy")
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
    }

    ////動くブロックに当たった
    //if (pTarget->GetObjectName() == "Block_move")
    //{
    //    //壁の判定(下)
    //    if (pStage->IsWallM((int)objX, (int)(objY + 0.2f)))
    //    {
    //        transform_.position_.y = (float)(int)(transform_.position_.y + 0.5f) - 0.2f;
    //        IsJump = 0;
    //    }
    //    //壁の判定（上）
    //    if (pStage->IsWallM((int)objX, (int)(objY - 0.2f)))
    //    {
    //        transform_.position_.y = (float)(int)(transform_.position_.y) + 0.2f;
    //        IsJump = 0;
    //    }
    //    //壁の判定(右)
    //    if (pStage->IsWallM((int)(objX + 0.4f), (int)objY))
    //    {
    //        transform_.position_.x = (float)(int)(transform_.position_.x + 0.5f) - 0.4f;
    //    }

    //    //壁の判定(左)
    //    if (pStage->IsWallM((int)(objX - 0.4f), (int)objY))
    //    {
    //        transform_.position_.x = (float)(int)(transform_.position_.x) + 0.4f;
    //    }
    //}

    ////土管に当たった
    //if (pTarget->GetObjectName() == "Pipe_base")
    //{
    //    //壁の判定(上)
    //    if (pStage->IsPipe((int)objX, (int)(objY - 0.2f)))
    //    {
    //        transform_.position_.y = (float)(int)(transform_.position_.y) + 0.2f;
    //        IsJump = 0;
    //    }

    //    //壁の判定(下)
    //    if (pStage->IsPipe((int)objX, (int)(objY + 0.2f)))
    //    {
    //        transform_.position_.y = (float)(int)(transform_.position_.y + 0.5f) - 0.4f;
    //        move_.y = -GRAVITY;
    //    }

    //    //壁の判定(右)
    //    if (pStage->IsPipe((int)(objX + 0.4f), (int)objY))
    //    {
    //        transform_.position_.x = (float)(int)(transform_.position_.x + 0.5f) - 0.4f;
    //    }

    //    //壁の判定(左)
    //    if (pStage->IsPipe((int)(objX - 0.4f), (int)objY))
    //    {
    //        transform_.position_.x = (float)(int)(transform_.position_.x) + 0.4f;
    //    }
    //}

    ////ボスに当たった
    //if (pTarget->GetObjectName() == "Boss")
    //{
    //    //敵の位置
    //    XMFLOAT3 BossPos = pTarget->GetPosition();
    //    XMVECTOR vBossPos = XMLoadFloat3(&BossPos);

    //    //プレイヤーの位置
    //    XMVECTOR PlayerPos = vBossPos - vPlayerPos;
    //    XMVector3Normalize(PlayerPos);

    //    //Downとプレイヤーの外積を求める
    //    XMVECTOR vDot = XMVector3Dot(Down, PlayerPos);
    //    float Dot = XMVectorGetY(vDot);

    //    //角度を求める
    //    angle = acos(Dot) * (180.0 / 3.14f);

    //    if (angle <= 90)
    //    {
    //        //初速度
    //        jump_v0 = 0.15f;
    //        //重力
    //        GRAVITY = 0.003f;

    //        //初速度を加える
    //        move_.y = jump_v0;
    //        transform_.position_.y += move_.y;

    //        //重力を加える
    //        move_.y += GRAVITY;
    //        transform_.position_.y += move_.y;

    //        pTarget->KillMe();
    //    }
    //    else
    //    {
    //        //横から当たったらプレイヤーを消す
    //        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
    //        pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
    //        KillMe();
    //    }
    //}

    ////ボス2に当たった
    //if (pTarget->GetObjectName() == "Boss2")
    //{
    //    //敵の位置
    //    XMFLOAT3 Boss2Pos = pTarget->GetPosition();
    //    XMVECTOR vBoss2Pos = XMLoadFloat3(&Boss2Pos);

    //    //プレイヤーの位置
    //    XMVECTOR PlayerPos = vBoss2Pos - vPlayerPos;
    //    XMVector3Normalize(PlayerPos);

    //    //Downとプレイヤーの外積を求める
    //    XMVECTOR vDot = XMVector3Dot(Down, PlayerPos);
    //    float Dot = XMVectorGetY(vDot);

    //    if (angle <= 90)
    //    {
    //        //初速度
    //        jump_v0 = 0.15f;
    //        //重力
    //        GRAVITY = 0.003f;

    //        //初速度を加える
    //        move_.y = jump_v0;
    //        transform_.position_.y += move_.y;

    //        //重力を加える
    //        move_.y += GRAVITY;
    //        transform_.position_.y += move_.y;

    //        //HPを減らす
    //        BossHp--;

    //        //HPが０になったら消す
    //        if (BossHp <= 0)
    //        {
    //            pTarget->KillMe();
    //        }
    //    }
    //    else
    //    {
    //        //横から当たったらプレイヤーを消す
    //        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
    //        pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
    //        KillMe();
    //    }
    //}
}

//地面に沿わせる
void Player::FollowGround()
{
    //まだ地面のモデル番号を知らない

    //モデル番号を調べる
    hModelBlock_ = ((Stage*)FindObject("Stage"))->getModelHandle(1);
    hModelWood_ = ((Stage*)FindObject("Stage"))->getModelHandle(2);

    //レイを撃つ準備
    RayCastData data;
    data.start = transform_.position_;
    data.start.y = transform_.position_.y + 1;
    data.dir = XMFLOAT3(0, -1, 0);

    RayCastData xdata;
    xdata.start = transform_.position_;
    xdata.start.y = transform_.position_.y + 1;
    xdata.dir = XMFLOAT3(0, -1, 0);
    xdata.normal;

    //地面に対してレイを撃つ
    Model::RayCast(hModelBlock_, &data);
    Model::RayCast(hModelWood_, &xdata);

    //レイが地面に当たったら
    if (data.hit)
    {
        if (transform_.position_.y - data.dist > 1)
        {
            transform_.position_.y = -data.dist;
        }
    }
    if (xdata.hit)
    {
        if (transform_.position_.y - xdata.dist > 1)
        {
            transform_.position_.y = -xdata.dist;
        }
    }

    /*if (xdata.hit) a = true;
    else a = false;*/
}