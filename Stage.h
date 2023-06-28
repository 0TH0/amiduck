#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"
#include "Engine/VFX.h"
#include "Engine/CsvReader.h"

class Player;

class Stage : public GameObject
{
    //�萔
    static const int STAGE_SIZE_X = 100;
    static const int STAGE_SIZE_Z = 37;

    //���f���ԍ�
    enum StageModelType
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

    struct stageData
    {
        int type;
        int height;
    } stage_[STAGE_SIZE_X][STAGE_SIZE_Z]; //�X�e�[�W

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

    //�����͋��Ȃ̂�
    bool IsBridge(int x,  int z);

    //�����͒[�Ȃ̂�
    bool IsCorner(int x,  int z);

    //�X�e�[�W�������[�h
    void StageLoad();

    //�Z�b�^�[�Q�b�^�[
    const int GetStageSizeX() { return STAGE_SIZE_X; };
    const int GetStageSizeZ() { return STAGE_SIZE_Z; };
    void SetWoodCoolTime(int woodCoolTime) { woodCoolTime_ = woodCoolTime; };
    int GetWoodCoolTime() { return woodCoolTime_; };
    void SetShouldPoPRandStage(bool ShouldPoPRandStage) { ShouldPoPRandStage_ = ShouldPoPRandStage; };
    bool GetShouldPoPRandStage() { return ShouldPoPRandStage_; };
    void SetStageType(int x, int z, StageModelType Type) { stage_[x][z].type = Type; };
    int GetStageType(int x, int z) { return stage_[x][z].type; };
    int GetModelHandle(int handle) { return hModel_[handle]; };

    //���N���b�N�ŋ����o��������
    void PopBridge();
    void PopBridgeEffect();
    void RandStage();
};