#pragma once
#include "Engine/GameObject.h"
#include "Engine/Astar.h"
#include "Engine/VFX.h"

//◆◆◆を管理するクラス
class EnemyRed : public GameObject
{
    XMFLOAT3 playerPos_;
    int count_;
    Astar AI_;
    bool CanMove_;
    int totalCell;
    int hModel_;
public:
    //コンストラクタ
    EnemyRed(GameObject* parent);

    //デストラクタ
    ~EnemyRed();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void Action();
};