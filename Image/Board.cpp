#include "Board.h"
#include "../Engine/Image.h"

//�R���X�g���N�^
Board::Board(GameObject* parent)
	: GameObject(parent, "Board"),hPict_(-1)
{
}

//������
void Board::Initialize()
{
	hPict_ = Image::Load("Image\\board.jpg");
	assert(hPict_ >= 0);
}

//�X�V
void Board::Update()
{
}

//�`��
void Board::Draw()
{
	Image::SetTransform(hPict_, transform_);
}

//�J��
void Board::Release()
{
}

void Board::BoardDraw()
{
	Image::Draw(hPict_);
}
