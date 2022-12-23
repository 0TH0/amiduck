#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "Engine/Particle.h"
#include "Engine/CsvReader.h"

#define STAGE_SIZE_X 180
#define STAGE_SIZE_Z 39

class Stage : public GameObject
{
    enum Number
    {
        empty = 0,
        log,
        coin,
        enemy,
        player
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

    void SetCloudPos(float x, float y, float z);
};