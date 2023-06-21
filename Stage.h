#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "Engine/VFX.h"
#include "Engine/CsvReader.h"

class Player;

class Stage : public GameObject
{
    //定数
    static const int STAGE_SIZE_X = 100;
    static const int STAGE_SIZE_Z = 37;

    enum StageModelNum
    {
        EMPTY,
        BRIDGE_FADE,
        BRIDGE,
        LOG,
        ENEMY,
        PLAYER,
        STAR,
        ITEMBOX,
        FIRE,
        FIRE_RIGHT,
        ENEMY_RED,
        ENEMY_BLUE,
        ENEMY_GREEN,
        CORNER,
        STAGE_MAX
    };

    struct stageInfo
    {
        int type;
        int height;
    } stage_[STAGE_SIZE_X][STAGE_SIZE_Z]; //ステージ

    int hModel_[STAGE_MAX];
    XMFLOAT3 player_pos_;
    XMFLOAT3 enemyPos_;
    XMFLOAT3 stagePos_;
    int time_;
    int count_ = 1;
    int bridgeCount_;
    int hAudio_;
    int woodCoolTime_;
    bool ShouldPoPRandStage_;
    XMFLOAT3 GuidePopBridgePos;

    Text* pText = new Text;
    CsvReader* csv;
    XMFLOAT3 effectPos_;
    EmitterData data;
    Player* pPlayer_;

public: 

    Stage(GameObject* parent);

    ~Stage();

    void Initialize() override;

    void Update() override;

    void Draw() override;

    void Release() override;

    //そこは橋なのか
    bool IsBridge(int x,  int z);

    bool IsCorner(int x,  int z);

    int getModelHandle(int handle) { return hModel_[handle]; };

    void StageLoad();

    //セッターゲッター
    static const int GetStageSizeX() { return STAGE_SIZE_X; };
    static const int GetStageSizeZ() { return STAGE_SIZE_Z; };
    int GetWoodCoolTime() { return woodCoolTime_; };
    void SetShouldPoPRandStage(bool ShouldPoPRandStage) { ShouldPoPRandStage_ = ShouldPoPRandStage; };
    bool GetShouldPoPRandStage() { return ShouldPoPRandStage_; };

    //左クリックで橋を出現させる
    void PopBridge();
    void RandStage();

    int GetStageType(int x, int z) { return stage_[x][z].type; };
};