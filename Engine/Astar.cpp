#include "Astar.h"
#include "Model.h"

//コンストラクタ
Astar::Astar():
    costmap(),goalCell_(),map_(),minNode(),startCell_(),totalCosts(),csv()
{
}

//デストラクタ
Astar::~Astar()
{
}

void Astar::CsvLoad(std::string name)
{
    csv = new CsvReader();
    csv->Load(name);

    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            SetMapType(csv->GetValue(x, z), x, z);
        }
    }
}

void Astar::SetMapType(int type, int x, int z)
{
    map_[x][z] = type;
}

//最短経路を探索
bool Astar::Search(CELL startCell, CELL goalCell)
{
    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            //Node設定(posと推定コストの計算だけしておく)
            mapNode[x][z] = Node({ x,z }, NONE, 0, abs((goalCell.x - x) + (goalCell.z - z)), 0, nullptr);

            //コストの初期値
            if (map_[x][z] < 2)
            {
                costmap[x][z] = -1;
            }
            else
            {
                costmap[x][z] = 1;
            }
        }
    }

    //初期化
    startCell_ = startCell;
    goalCell_ = goalCell;

    //すべてのリストを空にしておく
    StartToGoalCell.clear();
    open.clear();
    close.clear();

    //Openリストに格納
    open.push_back(mapNode[startCell.x][startCell.z]);
    //開始
    OpenNode(startCell_);

    return true;
}

//スタート位置からの各マスのコスト計算
void Astar::OpenNode(CELL cell)
{
    //ノードをOpenにする
    mapNode[cell.x][cell.z].status_ = OPEN;

    //4方向調べる
    for (DIRECTION dir : DIRECTIONS)
    {
        //次のマスの位置を調べる
        int nextX = cell.x + dir.dirX;
        int nextZ = cell.z + dir.dirZ;

        //エラーの数値をはいていたらコンテニューする
        if ((nextX == cell.x && nextZ == cell.z) || mapNode[nextX][nextZ].status_ != NONE || costmap[nextX][nextZ] < 0 || nextX < 0 || nextX >= STAGE_SIZE_X || nextZ < 0 || nextZ >= STAGE_SIZE_Z)
        {
            continue;
        }

        //状態をOPENにする
        mapNode[nextX][nextZ].status_ = OPEN;

        //移動コストを引数で受け取ったノードの移動コストにプラス1した値を設定
        mapNode[nextX][nextZ].moveCost_ = sqrt(pow(nextX - startCell_.x, 2) + pow(nextZ - startCell_.z, 2));

        //実コストを推定コストと移動コストを足した値に設定
        mapNode[nextX][nextZ].actualCost_ = mapNode[nextX][nextZ].moveCost_ + mapNode[nextX][nextZ].estimatedCost_;

        //親ノードの設定
        mapNode[nextX][nextZ].pParentNode_ = &mapNode[cell.x][cell.z];

        //Openリストに格納
        open.push_back(mapNode[nextX][nextZ]);
    }

    //ノードをCloseにする
    mapNode[cell.x][cell.z].status_ = CLOSE;

    //openListがからじゃないのなら
    if (!open.empty())
    {
        //ノードを見つけてlistから削除(closeリストに格納)
        for (auto i = open.begin(); i != open.end();)
        {
            if ((*i).pos_.x == cell.x && (*i).pos_.z == cell.z)
            {
                close.push_back((*i));
                i = open.erase(i);
            }
            else
                i++;
        }

        //最小コストを入れる用の変数
        float min = 99999;

        //ノード保存用
        minNode = nullptr;

        //実コストが一番小さい要素を探す
        for (auto i = open.begin(); i != open.end(); i++)
        {
            //コストが最小コストより小さければ
            if (min > (*i).actualCost_ && ((*i).pos_.x != cell.x || (*i).pos_.z != cell.z))
            {
                min = (*i).actualCost_;
                minNode = &(*i);
            }
        }

        //ゴールしている
        if (minNode == nullptr)
        {
            return;
        }
        //もしゴールにたどり着いたのなら
        else if (minNode->pos_.x == goalCell_.x && minNode->pos_.z == goalCell_.z)
        {
            //ゴールまで移動
            MoveToGoal();
            return;
        }
        else
        {
            //ノードの周りオープンする
            OpenNode(minNode->pos_);
        }
    }

}

//スタートからゴールまでの移動
void Astar::MoveToGoal()
{
    //ゴールセルを入れておく
    CELL cell = goalCell_;

    //スタートと同じセルになるまで繰り返し
    while (!(startCell_.x == cell.x && startCell_.z == cell.z))
    {
        //ゴールからListに入れていく
        StartToGoalCell.push_back(cell);

        //次のマスのセルを代入
        cell = mapNode[cell.x][cell.z].pParentNode_->pos_;
    }
}

CELL Astar::GetToGoalCell(int num)
{
    //カウントするためのやつ
    int count = 0;

    //num番目の要素を探す
    for (auto i = StartToGoalCell.begin(); i != StartToGoalCell.end(); i++)
    {
        //同じなら返す
        if (count == num)
        {
            return (*i);
        }
        count++;
    }

    return CELL{ 0,0 };
}