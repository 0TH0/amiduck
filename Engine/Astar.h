#pragma once
#include "GameObject.h"
#include "CsvReader.h"

//�萔
const unsigned int  STAGE_SIZE_X = 100;
const unsigned int  STAGE_SIZE_Z = 37;
const unsigned int  MAX_COSTS = 9999;
const unsigned int  MAX_DIRECTIONS = 4;

//�ǂ��̃}�X�����w���\����
typedef struct tagCell {
    int x;
    int z;
}CELL;

//�m�[�h�̏��
enum NodeStatus
{
    NONE,
    OPEN,
    CLOSE,
    NODE_STATUS_MAX
};

//�e�m�[�h�������Ă�����
struct Node
{
    CELL pos_;           //�|�W�V����
    int status_;         //�m�[�h�̏��
    int actualCost_;     //���R�X�g
    int estimatedCost_;  //����R�X�g
    int moveCost_;       //�ړ��R�X�g
    Node* pParentNode_;  //�eNode�N���X�̃|�C���^(�o�H�����߂�Ƃ��ɕK�v)

    //�R���X�g���N�^(������)
    Node() {};
    Node(CELL pos, int status, int actualCost, int estimatedCost, int moveCost, Node* ParentNode) :pos_(pos), status_(status), actualCost_(actualCost), estimatedCost_(estimatedCost), moveCost_(moveCost), pParentNode_(ParentNode) {}
};

class Astar
{
    //�}�b�v���Ƃ̃��f���ԍ�
    int map_[STAGE_SIZE_X][STAGE_SIZE_Z];

    //�e�}�X���̃m�[�h
    Node mapNode[STAGE_SIZE_X][STAGE_SIZE_Z];

    //Open���X�g
    std::list<Node> open;

    //Close���X�g
    std::list<Node> close;

    //�e�}�X�ɂǂ̂��炢�̃R�X�g�����Ă��邩
    int costmap[STAGE_SIZE_X][STAGE_SIZE_Z];

    //�ǂ��̕��������邩
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

    //�X�^�[�g�̃}�X
    CELL startCell_;

    //�X�^�[�g�̃}�X
    CELL goalCell_ ;

    //�X�^�[�g�n�_����̃g�[�^���R�X�g������
    int totalCosts[STAGE_SIZE_X][STAGE_SIZE_Z];

    //�S�[������X�^�[�g�܂ł̃}�X�̈ړ���ۑ����Ă���
    std::list<CELL>StartToGoalCell;

    //�}�b�v�ǂݍ���
    CsvReader* csv;

    //�ŏ��R�X�g
    Node* minNode;

public:
    //�R���X�g���N�^
    Astar();

    //�f�X�g���N�^
    ~Astar();

    //csv�t�@�C���œǂݍ���
    void CsvLoad(std::string name);

    //�}�b�v�̃^�C�v���Z�b�g
    void SetMapType(int type, int x, int z);

    //�X�^�[�g�ʒu�̐ݒ�
    //startCell �Fstart��CELL
    //goalCell  �Fgoal��CELL
    bool Search(CELL startCell, CELL goalCell);

    //�����Open����
    //�����Fstart��CELL
    void OpenNode(CELL cell);

    //�S�[���܂ł̃}�X�ړ����v�Z����
    //�����F�S�[����CELL
    void MoveToGoal();

    //�X�^�[�g����S�[���܂ł̃}�X�̐��������Ă����
    //�����F�S�[����CELL
    int GetToGoalTotalCell() { return StartToGoalCell.size() - 1; }

    //�X�^�[�g����S�[���܂ł̃}�X�������Ă����
    //�����F���Ԗڂ̃}�X
    CELL GetToGoalCell(int num);

    //�ŒZ�m�[�h����(�Ȃ�������ړI�n�ɂ��Ă�)
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