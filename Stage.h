#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "Engine/Particle.h"
#include "Engine/CsvReader.h"

class Stage : public GameObject
{
    //定数
    static const int STAGE_SIZE_X = 180;
    static const int STAGE_SIZE_Z = 39;

    enum StageModelNum
    {
        empty = 0,
        log,
        coin,
        enemy,
        player,
        star,
        bridge,
        itembox,
        STAGE_MODEL_MAX
    };

    struct
    {
        int type;
        int height;
    } stage_[STAGE_SIZE_X][STAGE_SIZE_Z]; //ステージ

    int hModel_[20];
    XMFLOAT3 player_pos_;
    int PlayerPosX_;
    int PlayerPosZ_;
    int time_;
    int count_ = 1;

    std::list<XMFLOAT3> stagePosList_;

    Text* pText = new Text;
    CsvReader csv;
    Particle* pParticle_;
    EmitterData data;

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
};