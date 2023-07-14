#pragma once
#include "GameObject.h"
#include "CsvReader.h"

//定数
const unsigned int  STAGE_SIZE_X = 100;
const unsigned int  STAGE_SIZE_Z = 37;
const unsigned int  MAX_COSTS = 9999;
const unsigned int  MAX_DIRECTIONS = 4;

//どこのマスかを指す構造体
typedef struct tagCell {
    int x;
    int z;
}CELL;

//ノードの状態
enum NodeStatus
{
    NONE,
    OPEN,
    CLOSE,
    NODE_STATUS_MAX
};

//各ノードが持っている情報
struct Node
{
    CELL pos_;           //ポジション
    int status_;         //ノードの状態
    int actualCost_;     //実コスト
    int estimatedCost_;  //推定コスト
    int moveCost_;       //移動コスト
    Node* pParentNode_;  //親Nodeクラスのポインタ(経路を求めるときに必要)

    //コンストラクタ(初期化)
    Node() {};
    Node(CELL pos, int status, int actualCost, int estimatedCost, int moveCost, Node* ParentNode) :pos_(pos), status_(status), actualCost_(actualCost), estimatedCost_(estimatedCost), moveCost_(moveCost), pParentNode_(ParentNode) {}
};

class Astar
{
    //マップごとのモデル番号
    int map_[STAGE_SIZE_X][STAGE_SIZE_Z];

    //各マス分のノード
    Node mapNode[STAGE_SIZE_X][STAGE_SIZE_Z];

    //Openリスト
    std::list<Node> open;

    //Closeリスト
    std::list<Node> close;

    //各マスにどのくらいのコスト持っているか
    int costmap[STAGE_SIZE_X][STAGE_SIZE_Z];

    //どこの方向を見るか
    typedef struct tagDirection {
        int dirX;
        int dirZ;
    }DIRECTION;

    const DIRECTION DIRECTIONS[MAX_DIRECTIONS] = {
        {  0, -1 },		// L
        {  0, +1 },		// R
        { -1,  0 },		// U
        { +1,  0 }		// D
    };

    //スタートのマス
    CELL startCell_;

    //スタートのマス
    CELL goalCell_ ;

    //スタート地点からのトータルコストを入れる
    int totalCosts[STAGE_SIZE_X][STAGE_SIZE_Z];

    //ゴールからスタートまでのマスの移動を保存しておく
    std::list<CELL>StartToGoalCell;

    //マップ読み込み
    CsvReader* csv;

    //最小コスト
    Node* minNode;

public:
    //コンストラクタ
    Astar();

    //デストラクタ
    ~Astar();

    //csvファイルで読み込む
    void CsvLoad(std::string name);

    //マップのタイプをセット
    void SetMapType(int type, int x, int z);

    //スタート位置の設定
    //startCell ：startのCELL
    //goalCell  ：goalのCELL
    bool Search(CELL startCell, CELL goalCell);

    //周りをOpenする
    //引数：startのCELL
    void OpenNode(CELL cell);

    //ゴールまでのマス移動を計算する
    //引数：ゴールのCELL
    void MoveToGoal();

    //スタートからゴールまでのマスの数を教えてくれる
    //引数：ゴールのCELL
    int GetToGoalTotalCell() { return StartToGoalCell.size() - 1; }

    //スタートからゴールまでのマスを教えてくれる
    //引数：何番目のマス
    CELL GetToGoalCell(int num);

    //最短ノードが空か(なかったら目的地についてる)
    bool GetExistMinNode()
    {
        if (minNode == nullptr)
        {
            return false;
        }
        else
        {
            return true;
        }
    };
};