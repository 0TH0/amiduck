#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "Engine/Particle.h"
#include "Engine/CsvReader.h"

class Player;

class Stage : public GameObject
{
    //定数
    static const int STAGE_SIZE_X = 180;
    static const int STAGE_SIZE_Z = 37;

    enum StageModelNum
    {
        empty,
        log,
        coin,
        enemy,
        player,
        star,
        bridge,
        itembox,
        fire,
        fire_right,
        STAGE_MODEL_MAX
    };

    struct
    {
        int type;
        int height;
    } stage_[STAGE_SIZE_X][STAGE_SIZE_Z]; //ステージ

    int hModel_[20];
    XMFLOAT3 player_pos_;
    XMFLOAT3 enemyPos_;
    XMFLOAT3 stagePos_;
    int time_;
    int count_ = 1;
    int bridgeCount_;
    int hAudio_;
    int woodCoolTime_;
    XMFLOAT3 GuidePopBridgePos;

    Text* pText = new Text;
    CsvReader csv;
    Particle* pParticle_;
    EmitterData data;
    Player* pPlayer_;

public: 

    Stage(GameObject* parent);

    ~Stage();

    void Initialize() override;

    void Update() override;

    void Draw() override;

    void Release() override;

    //そこは壁なのか
    bool IsWall(int x,  int z);

    bool IsBridge(int x,  int z);

    bool IsEmpty(int x,  int z);

    int getModelHandle(int handle) { return hModel_[handle]; };

    void StageLoad();

    void Cloud();

    static const int GetStageSizeX() { return STAGE_SIZE_X; };
    static const int GetStageSizeZ() { return STAGE_SIZE_Z; };

    int GetWoodCoolTime() { return woodCoolTime_; };

    //左クリックで橋を出現させる
    void PopBridge();
};