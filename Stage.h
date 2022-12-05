#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class Stage : public GameObject
{
    enum Number
    {
        empty = 0,
        log,
        coin,
        enemy
    };

    int hModel_[20];
    int map_[180][1][39];
    int PlayerPosX_;
    int PlayerPosZ_;
    int time_;
    int count_ = 1;
    Text* pText = new Text;

public: 

    Stage(GameObject* parent);

    ~Stage();

    void Initialize() override;

    void Update() override;

    void Draw() override;

    void Release() override;

    //‚»‚±‚Í•Ç‚È‚Ì‚©
    bool IsWall(int x, int y, int z);

    bool IsWallX(int x, int y, int z);

    bool IsWallM(int x, int y, int z);

    bool IsPipe(int x, int y, int z);

    bool IsEmpty(int x, int y, int z);

    int getModelHandle(int handle) { return hModel_[handle]; };

    void StageLoad();
};