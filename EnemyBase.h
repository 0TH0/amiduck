#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/PolyLine.h"
#include "Engine/Astar.h"
#include "Manager/EnemyEffect.h"
#include "Player.h"


//EnemyBase���Ǘ�����N���X
class EnemyBase : public GameObject
{
protected:
    Player* pPlayer_;
    int hModel_;
    int count_;
    Astar AI_;
    bool CanMove_;
    int totalCell;
    int frame; //���t���[�����ɐi�ނ�

    virtual void Action() = 0;
    virtual void InitBase() = 0;
    virtual void ChangeColor() = 0;
    virtual void ReleaseBase() = 0;

public:
    //�p���p�R���X�g���N�^
    EnemyBase(GameObject* parent, std::string name);

    //�f�X�g���N�^
    ~EnemyBase();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};