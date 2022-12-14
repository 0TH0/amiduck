#include "FireFollowGround.h"
#include "Stage.h"
#include "PlayScene.h"
#include "StartScene.h"

#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"
#include "Engine/SceneManager.h"
#include "Engine/Text.h"

//コンストラクタ
FireFollowGround::FireFollowGround(GameObject* parent)
    :GameObject(parent, "FireFollowGround"),

    //変数
    hModel_(-1),
    jump_v0(0), gravity(0), angle(0), BossHp(3), hModelBlock_(-1),

    //フラグ
    IsJump(false), IsGround(false),

    //定数
    SPEED(0.5f), DUSHSPEED(0.05f),
    CAMERA_POS_Y(-15.0f), CAMERA_TAR_Y(-5.0f)
{
}

//デストラクタ
FireFollowGround::~FireFollowGround()
{
}

//初期化
void FireFollowGround::Initialize()
{
    hModel_ = Model::Load("fire_blue.fbx");
    assert(hModel_ >= 0);

    //位置
    transform_.rotate_ = XMFLOAT3(0, rotate_.y, 0);
    transform_.scale_ = XMFLOAT3(0.35, 0.35, 0.35);

    //当たり判定
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0.5f, 0), 0.5f);
    AddCollider(collision);

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    pText->Initialize();

    pLine = new PoryLine;
    pLine->Load("white_line.png.");

    Player* pPlayer = (Player*)FindObject("Player");
    PlayerPos_ = pPlayer->GetPosition();
    transform_.position_ = PlayerPos_;
}

void FireFollowGround::Update()
{
    time++;

    if (time >= 240)
    {
        KillMe();
    }

    pLine->AddPosition(transform_.position_);

    transform_.rotate_ = XMFLOAT3(0, rotate_.y, 0);

    pStage = (Stage*)FindObject("Stage");

    // 1フレーム前の座標
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

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
    //    //初速度
    //    jump_v0 = 0.2f;
    //    //重力
    //    gravity = 0.008f;

    //    //初速度を加える
    //    move_.y = jump_v0;

    //    //重力を加える
    //    move_.y += gravity;

    //    //ジャンプフラグ
    //    IsJump = 1;
    //}

    ////ジャンプ中の重力
    if (IsJump == 1)
    {
        //重力
        move_.y -= gravity;
        transform_.position_.y += move_.y;
    }

    //ジャンプしてない時の重力
    if (IsJump == 0)
    {
        //重力
        gravity = 0.1f;

        //重力を加える
        move_.y = -gravity;
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
    //    transform_.rotate_.y = angle * STAGE_SIZE_X.0f / 3.14f;
    //}

    //////////////////壁との衝突判定///////////////////////
    int objX = transform_.position_.x;
    int objY = transform_.position_.y;
    int objZ = transform_.position_.z;

    ////壁の判定(上)
    if (pStage->IsWall(objX, objZ))
    {
        transform_.position_.y = (int)(transform_.position_.y) + 0.8;
        IsJump = 0;
    }
    if (pStage->IsBridge(objX, objZ))
    {
        transform_.position_.y = (int)(transform_.position_.y) + 0.8;
        IsJump = 0;
    }

    if (!a && !b && pStage->IsEmpty((float)objX + 3, objZ))
    {
        IsReturn = true;
    }
    if (!a && !b && pStage->IsEmpty((float)objX - 2.5, objZ))
    {
        IsReturn = false;
    }

    if (IsReturn)
    {
        transform_.position_.x -= SPEED;
        rotate_.y = 0;
    }
    else
    {
        transform_.position_.x += SPEED;
        rotate_.y = Stage::GetStageSizeX();
    }

    ///////////////////////// あみだくじの処理 ///////////////////////////////////////////

    if (!b && time2 > 4)
    {
        if (pStage->IsBridge(objX, objZ - 3))
        {
            SPEED = 0;
            a = true;
            time2 = 0;
        }
    }

    //右に行く
    if (a)
    {
        rotate_.y = -90;
        if (g <= 0)
        {
            s = 0.5;
            t += s;
            if (t >= 6)
            {
                trans[0].position_ = transform_.position_;
                time1 = 0;
                s = 0;
                t = 0;
                a = false;
                SPEED = 0.5;
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
        time2++;

        if (!b) time1++;

        if (time1 > 4)
        {
            if (pStage->IsBridge(objX, objZ + 2))
            {
                SPEED = 0;
                b = true;
            }
        }

        if (b)
        {
            rotate_.y = 90;
            f = 0.5;
            g += f;
            if (g >= 6)
            {
                trans[1].position_ = transform_.position_;
                time2 = 0;
                g = 0;
                f = 0;
                b = false;
                SPEED = 0.5;
                time1 = 0;
            }
            else
            {
                transform_.position_.z += f;
            }
        }
    }

    //if (Input::IsKeyDown(DIK_Z))
    //{
    //    IsPress = true;
    //}
    //if (Input::IsKeyDown(DIK_X))
    //{
    //    IsPress = false;
    //}
    //if (Input::IsKeyDown(DIK_C))
    //{
    //    SPEED = -0.2f;
    //}
    //if (Input::IsKeyDown(DIK_V))
    //{
    //    SPEED = 0.2f;
    //}
    //if (IsPress)
    //{
    //}

    //if (pStage->IsBridge(objX, objY, objZ + 2))
    //{
    //    transform_.position_.z += 12;
    //}

    //
    ////壁の判定(下)
    //if (pStage->IsWall((int)objX, (int)(objY + 0.2f)))
    //{
    //    transform_.position_.y = (float)(int)(transform_.position_.y + 0.5f) - 0.4f;
    //    move_.y = -gravity;
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

    // //カメラ回転
    //if (Input::IsKey(DIK_LEFT))
    //{
    //    transform_.rotate_.y -= 1.0f;
    //}

    //if (Input::IsKey(DIK_RIGHT))
    //{
    //    transform_.rotate_.y += 1.0f;
    //}

    //if (Input::IsKey(DIK_UP))
    //{
    //    transform_.rotate_.x += 1.0f;
    //}

    //if (Input::IsKey(DIK_DOWN))
    //{
    //    transform_.rotate_.x -= 1.0f;
    //}

    ////回転行列
    //XMMATRIX mRotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    //XMMATRIX mRotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    //XMMATRIX mRotate = mRotateX * mRotateY;

    ////現在位置をベクトルにしておく
    //XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    ////移動ベクトル
    //XMFLOAT3 move = { 0, 0, 0.2f };
    //XMVECTOR vMove = XMLoadFloat3(&move);
    //vMove = XMVector3TransformCoord(vMove, mRotate);

    //XMFLOAT3 X = { 0.2f, 0, 0 };
    //XMVECTOR vX = XMLoadFloat3(&X);
    //vX = XMVector3TransformCoord(vX, mRotate);

    //////カメラ移動
    //if (Input::IsKey(DIK_W))
    //{
    //    vPos += vMove;
    //    XMStoreFloat3(&transform_.position_, vPos);
    //}

    //if (Input::IsKey(DIK_S))
    //{
    //    vPos -= vMove;
    //    XMStoreFloat3(&transform_.position_, vPos);
    //}

    //if (Input::IsKey(DIK_D))
    //{
    //    vPos += vX;
    //    XMStoreFloat3(&transform_.position_, vPos);
    //}

    //if (Input::IsKey(DIK_A))
    //{
    //    vPos -= vX;
    //    XMStoreFloat3(&transform_.position_, vPos);
    //}

    ////カメラ
    //XMVECTOR vCam = XMVectorSet(0, 10, -10, 0);
    //vCam = XMVector3TransformCoord(vCam, mRotate);
    //XMFLOAT3 camPos;
    //XMStoreFloat3(&camPos, vPos + vCam);
    //Camera::SetPosition(camPos);
    //Camera::SetTarget(transform_.position_);


    //XMFLOAT3 a = Input::GetMousePosition();

    //XMFLOAT3 b = Input::GetMouseMove();

    //float x = b.z - a.z;

    //float y = b.z - a.z;

    //transform_.rotate_.x += x * 0.025;

    //if (transform_.rotate_.x > 40)  transform_.rotate_.x = 40;
    //if (transform_.rotate_.x < -40) transform_.rotate_.x = -40;

    //FollowGround();
}

void FireFollowGround::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    pLine->SetColor(XMFLOAT4(1, 0.6, 1, 0.7));
    pLine->Draw();

    //pText->Draw(20, 20, "rotate.xyz");
    //pText->Draw(50, 50, transform_.rotate_.x);
    //pText->Draw(150, 50, transform_.rotate_.y);
    //pText->Draw(250, 50, transform_.rotate_.z);

    //pText->Draw(20, 100, "transform.xyz");
    //pText->Draw(50, 130, transform_.position_.x);
    //pText->Draw(150, 130, transform_.position_.y);
    //pText->Draw(250, 130, transform_.position_.z);
}

void FireFollowGround::Release()
{
    pLine->Release();
}

void FireFollowGround::OnCollision(GameObject* pTarget)
{
    //敵に当たった
    if (pTarget->GetObjectName() == "Enemy")
    {
        pTarget->Invisible();
        KillMe();
    }
}

////何かに当たった
//void FireFollowGround::OnCollision(GameObject* pTarget)
//{
//    XMVECTOR vFireFollowGroundPos = XMLoadFloat3(&transform_.position_);
//    XMVECTOR Down = { 0,-1,0,0 };
//
//    float objX = transform_.position_.x;
//    float objY = transform_.position_.y;
//
//    //ブロックに当たった
//    if (pTarget->GetObjectName() == "Block")
//    {
//        if (pStage->IsBridge((int)objX, (int)(objY + 0.2f)))
//        {
//            pTarget->KillMe();
//            IsJump = 0;
//        }
//    }
//
//    //コインに当たった
//    if (pTarget->GetObjectName() == "Coin")
//    {
//        pTarget->KillMe();
//    }
//
//    //敵に当たった
//    if (pTarget->GetObjectName() == "FireFollowGround")
//    {
//        //敵の位置
//        XMFLOAT3 FireFollowGroundPos = pTarget->GetPosition();
//        XMVECTOR vFireFollowGroundPos = XMLoadFloat3(&FireFollowGroundPos);
//
//        //プレイヤーの位置
//        XMVECTOR FireFollowGroundPos = vFireFollowGroundPos - vFireFollowGroundPos;
//        XMVector3Normalize(FireFollowGroundPos);
//
//        //Downとプレイヤーの外積を求める
//        XMVECTOR vDot = XMVector3Dot(Down, FireFollowGroundPos);
//        float Dot = XMVectorGetY(vDot);
//
//        //角度を求める
//        angle = acos(Dot) * (STAGE_SIZE_X.0 / 3.14f);
//
//        if (angle <= 90)
//        {
//            //初速度
//            jump_v0 = 0.15f;
//            //重力
//            gravity = 0.003f;
//
//            //初速度を加える
//            move_.y = jump_v0;
//            transform_.position_.y += move_.y;
//
//            //重力を加える
//            move_.y += gravity;
//            transform_.position_.y += move_.y;
//        }
//        else
//        {
//            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
//            pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
//            KillMe();
//        }
//    }
//
//    //動くブロックに当たった
//    if (pTarget->GetObjectName() == "Block_move")
//    {
//        //壁の判定(下)
//        if (pStage->IsBridge((int)objX, (int)(objY + 0.2f)))
//        {
//            transform_.position_.y = (float)(int)(transform_.position_.y + 0.5f) - 0.2f;
//            IsJump = 0;
//        }
//        //壁の判定（上）
//        if (pStage->IsBridge((int)objX, (int)(objY - 0.2f)))
//        {
//            transform_.position_.y = (float)(int)(transform_.position_.y) + 0.2f;
//            IsJump = 0;
//        }
//        //壁の判定(右)
//        if (pStage->IsBridge((int)(objX + 0.4f), (int)objY))
//        {
//            transform_.position_.x = (float)(int)(transform_.position_.x + 0.5f) - 0.4f;
//        }
//
//        //壁の判定(左)
//        if (pStage->IsBridge((int)(objX - 0.4f), (int)objY))
//        {
//            transform_.position_.x = (float)(int)(transform_.position_.x) + 0.4f;
//        }
//    }
//
//    //土管に当たった
//    if (pTarget->GetObjectName() == "Pipe_base")
//    {
//        //壁の判定(上)
//        if (pStage->IsBridge((int)objX, (int)(objY - 0.2f)))
//        {
//            transform_.position_.y = (float)(int)(transform_.position_.y) + 0.2f;
//            IsJump = 0;
//        }
//
//        //壁の判定(下)
//        if (pStage->IsBridge((int)objX, (int)(objY + 0.2f)))
//        {
//            transform_.position_.y = (float)(int)(transform_.position_.y + 0.5f) - 0.4f;
//            move_.y = -gravity;
//        }
//
//        //壁の判定(右)
//        if (pStage->IsBridge((int)(objX + 0.4f), (int)objY))
//        {
//            transform_.position_.x = (float)(int)(transform_.position_.x + 0.5f) - 0.4f;
//        }
//
//        //壁の判定(左)
//        if (pStage->IsBridge((int)(objX - 0.4f), (int)objY))
//        {
//            transform_.position_.x = (float)(int)(transform_.position_.x) + 0.4f;
//        }
//    }
//
//    //ボスに当たった
//    if (pTarget->GetObjectName() == "Boss")
//    {
//        //敵の位置
//        XMFLOAT3 BossPos = pTarget->GetPosition();
//        XMVECTOR vBossPos = XMLoadFloat3(&BossPos);
//
//        //プレイヤーの位置
//        XMVECTOR FireFollowGroundPos = vBossPos - vFireFollowGroundPos;
//        XMVector3Normalize(FireFollowGroundPos);
//
//        //Downとプレイヤーの外積を求める
//        XMVECTOR vDot = XMVector3Dot(Down, FireFollowGroundPos);
//        float Dot = XMVectorGetY(vDot);
//
//        //角度を求める
//        angle = acos(Dot) * (STAGE_SIZE_X.0 / 3.14f);
//
//        if (angle <= 90)
//        {
//            //初速度
//            jump_v0 = 0.15f;
//            //重力
//            gravity = 0.003f;
//
//            //初速度を加える
//            move_.y = jump_v0;
//            transform_.position_.y += move_.y;
//
//            //重力を加える
//            move_.y += gravity;
//            transform_.position_.y += move_.y;
//
//            pTarget->KillMe();
//        }
//        else
//        {
//            //横から当たったらプレイヤーを消す
//            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
//            pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
//            KillMe();
//        }
//    }
//
//    //ボス2に当たった
//    if (pTarget->GetObjectName() == "Boss2")
//    {
//        //敵の位置
//        XMFLOAT3 Boss2Pos = pTarget->GetPosition();
//        XMVECTOR vBoss2Pos = XMLoadFloat3(&Boss2Pos);
//
//        //プレイヤーの位置
//        XMVECTOR FireFollowGroundPos = vBoss2Pos - vFireFollowGroundPos;
//        XMVector3Normalize(FireFollowGroundPos);
//
//        //Downとプレイヤーの外積を求める
//        XMVECTOR vDot = XMVector3Dot(Down, FireFollowGroundPos);
//        float Dot = XMVectorGetY(vDot);
//
//        if (angle <= 90)
//        {
//            //初速度
//            jump_v0 = 0.15f;
//            //重力
//            gravity = 0.003f;
//
//            //初速度を加える
//            move_.y = jump_v0;
//            transform_.position_.y += move_.y;
//
//            //重力を加える
//            move_.y += gravity;
//            transform_.position_.y += move_.y;
//
//            //HPを減らす
//            BossHp--;
//
//            //HPが０になったら消す
//            if (BossHp <= 0)
//            {
//                pTarget->KillMe();
//            }
//        }
//        else
//        {
//            //横から当たったらプレイヤーを消す
//            SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
//            pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
//            KillMe();
//        }
//    }
//}

//地面に沿わせる
void FireFollowGround::FollowGround()
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