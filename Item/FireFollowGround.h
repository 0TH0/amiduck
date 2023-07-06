#pragma once
#include "../Engine/GameObject.h"
#include "../Stage.h"
#include "../Engine/VFX.h"
#include "../Engine/PolyLine.h"

//◆◆◆を管理するクラス
class FireFollowGround : public GameObject
{
    PolyLine* pLine_;
    int hModel_;
public:
    //コンストラクタ
    FireFollowGround(GameObject* parent);

    //デストラクタ
    ~FireFollowGround();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void OnCollision(GameObject* pTarget) override;
};