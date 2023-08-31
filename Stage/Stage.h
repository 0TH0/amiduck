#pragma once
#include "../Engine/GameObject.h"
#include "../Engine/Text.h"
#include "../Engine/CsvReader.h"
#include "../Engine/VFX.h"

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
        PLAYER,
        ITEMBOX,
        ENEMY_WHITE,
        ENEMY_YELLOW,
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
    XMFLOAT3 stagePos_;
    int frameCount_;
    int bridgeCount_;
    int hAudio_;
    int woodCoolTime_;
    int bufX, bufY, bufZ;                //�N���b�N�����ʒu
    const int bridgeRimit_;             //�[���牽�}�X����u���Ȃ����邩
    bool ShouldPopRandStage_;
    XMFLOAT3 GuidePopBridgePos;
    CsvReader* csv;
    XMFLOAT3 effectPos_;

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
    const int GetBridgeRimit() { return bridgeRimit_; };
    void SetWoodCoolTime(int woodCoolTime) { woodCoolTime_ = woodCoolTime; };
    int GetWoodCoolTime() { return woodCoolTime_; };
    void SetShouldPoPRandStage(bool ShouldPoPRandStage) { ShouldPopRandStage_ = ShouldPoPRandStage; };
    bool GetShouldPoPRandStage() { return ShouldPopRandStage_; };
    void SetStageType(int x, int z, StageModelType Type) { stage_[x][z].type = Type; };
    int GetStageType(int x, int z) { return stage_[x][z].type; };
    int GetModelHandle(int handle) { return hModel_[handle]; };
    XMINT3 GetMousePos() { return XMINT3(bufX, bufY, bufZ); };

    //���N���b�N�ŋ����o��������
    void PopBridge();
    void PopBridgeEffect();
    void RandStage();
};