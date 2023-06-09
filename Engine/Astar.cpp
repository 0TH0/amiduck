#include "Astar.h"
#include "Model.h"

//�R���X�g���N�^
Astar::Astar():
    costmap(),goalCell_(),map_(),minNode(),startCell_(),totalCosts(),csv()
{
}

//�f�X�g���N�^
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

//�ŒZ�o�H��T��
bool Astar::Search(CELL startCell, CELL goalCell)
{
    for (int x = 0; x < STAGE_SIZE_X; x++)
    {
        for (int z = 0; z < STAGE_SIZE_Z; z++)
        {
            //Node�ݒ�(pos�Ɛ���R�X�g�̌v�Z�������Ă���)
            mapNode[x][z] = Node({ x,z }, NONE, 0, abs((goalCell.x - x) + (goalCell.z - z)), 0, nullptr);

            //�R�X�g�̏����l
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

    //������
    startCell_ = startCell;
    goalCell_ = goalCell;

    //���ׂẴ��X�g����ɂ��Ă���
    StartToGoalCell.clear();
    open.clear();
    close.clear();

    //Open���X�g�Ɋi�[
    open.push_back(mapNode[startCell.x][startCell.z]);
    //�J�n
    OpenNode(startCell_);

    return true;
}

//�X�^�[�g�ʒu����̊e�}�X�̃R�X�g�v�Z
void Astar::OpenNode(CELL cell)
{
    //�m�[�h��Open�ɂ���
    mapNode[cell.x][cell.z].status_ = OPEN;

    //4�������ׂ�
    for (DIRECTION dir : DIRECTIONS)
    {
        //���̃}�X�̈ʒu�𒲂ׂ�
        int nextX = cell.x + dir.dirX;
        int nextZ = cell.z + dir.dirZ;

        //�G���[�̐��l���͂��Ă�����R���e�j���[����
        if ((nextX == cell.x && nextZ == cell.z) || mapNode[nextX][nextZ].status_ != NONE || costmap[nextX][nextZ] < 0 || nextX < 0 || nextX >= STAGE_SIZE_X || nextZ < 0 || nextZ >= STAGE_SIZE_Z)
        {
            continue;
        }

        //��Ԃ�OPEN�ɂ���
        mapNode[nextX][nextZ].status_ = OPEN;

        //�ړ��R�X�g�������Ŏ󂯎�����m�[�h�̈ړ��R�X�g�Ƀv���X1�����l��ݒ�
        mapNode[nextX][nextZ].moveCost_ = sqrt(pow(nextX - startCell_.x, 2) + pow(nextZ - startCell_.z, 2));

        //���R�X�g�𐄒�R�X�g�ƈړ��R�X�g�𑫂����l�ɐݒ�
        mapNode[nextX][nextZ].actualCost_ = mapNode[nextX][nextZ].moveCost_ + mapNode[nextX][nextZ].estimatedCost_;

        //�e�m�[�h�̐ݒ�
        mapNode[nextX][nextZ].pParentNode_ = &mapNode[cell.x][cell.z];

        //Open���X�g�Ɋi�[
        open.push_back(mapNode[nextX][nextZ]);
    }

    //�m�[�h��Close�ɂ���
    mapNode[cell.x][cell.z].status_ = CLOSE;

    //openList�����炶��Ȃ��̂Ȃ�
    if (!open.empty())
    {
        //�m�[�h��������list����폜(close���X�g�Ɋi�[)
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

        //�ŏ��R�X�g������p�̕ϐ�
        float min = 99999;

        //�m�[�h�ۑ��p
        minNode = nullptr;

        //���R�X�g����ԏ������v�f��T��
        for (auto i = open.begin(); i != open.end(); i++)
        {
            //�R�X�g���ŏ��R�X�g��菬�������
            if (min > (*i).actualCost_ && ((*i).pos_.x != cell.x || (*i).pos_.z != cell.z))
            {
                min = (*i).actualCost_;
                minNode = &(*i);
            }
        }

        //�S�[�����Ă���
        if (minNode == nullptr)
        {
            return;
        }
        //�����S�[���ɂ��ǂ蒅�����̂Ȃ�
        else if (minNode->pos_.x == goalCell_.x && minNode->pos_.z == goalCell_.z)
        {
            //�S�[���܂ňړ�
            MoveToGoal();
            return;
        }
        else
        {
            //�m�[�h�̎���I�[�v������
            OpenNode(minNode->pos_);
        }
    }

}

//�X�^�[�g����S�[���܂ł̈ړ�
void Astar::MoveToGoal()
{
    //�S�[���Z�������Ă���
    CELL cell = goalCell_;

    //�X�^�[�g�Ɠ����Z���ɂȂ�܂ŌJ��Ԃ�
    while (!(startCell_.x == cell.x && startCell_.z == cell.z))
    {
        //�S�[������List�ɓ���Ă���
        StartToGoalCell.push_back(cell);

        //���̃}�X�̃Z������
        cell = mapNode[cell.x][cell.z].pParentNode_->pos_;
    }
}

CELL Astar::GetToGoalCell(int num)
{
    //�J�E���g���邽�߂̂��
    int count = 0;

    //num�Ԗڂ̗v�f��T��
    for (auto i = StartToGoalCell.begin(); i != StartToGoalCell.end(); i++)
    {
        //�����Ȃ�Ԃ�
        if (count == num)
        {
            return (*i);
        }
        count++;
    }

    return CELL{ 0,0 };
}