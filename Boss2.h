#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Player.h"

class Boss2 : public GameObject
{
    //�ϐ�
    int hModel_;
    Stage* pStage;
    Player* pPlayer;
    XMFLOAT3 move_;
    float time;        //����
    float RotateSpeed; //��]���x
    float SPEED;       //����
    float GRAVITY;     //�d��
    bool IsJump;       //�W�����v�t���O
    float jump_v0;     //�����x

public:
    Boss2(GameObject* parent);

    ~Boss2();

    void Initialize() override;

    void Update() override;

    void Draw() override;

    void Release() override;

    void OnCollision(GameObject* pTarget) override;
};