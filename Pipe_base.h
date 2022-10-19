#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Pipe_base : public GameObject
{
    int hModel_;   //モデル番号
public:
    //コンストラクタ
    Pipe_base(GameObject* parent);

    //デストラクタ
    ~Pipe_base();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};

