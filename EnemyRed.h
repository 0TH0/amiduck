#include "EnemyBase.h"

class EnemyRed : public EnemyBase
{
public:
    //コンストラクタ
    EnemyRed(GameObject* parent);

    //デストラクタ
    ~EnemyRed();

    void Action() override;
    void InitBase() override;
    void ChangeColor() override;
    void ReleaseBase() override;
};