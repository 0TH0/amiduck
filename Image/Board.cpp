#include "Board.h"
#include "../Engine/Image.h"

//コンストラクタ
Board::Board(GameObject* parent)
	: GameObject(parent, "Board"),hPict_(-1)
{
}

//初期化
void Board::Initialize()
{
	hPict_ = Image::Load("Image\\board.jpg");
	assert(hPict_ >= 0);
}

//更新
void Board::Update()
{
}

//描画
void Board::Draw()
{
	Image::SetTransform(hPict_, transform_);
}

//開放
void Board::Release()
{
}

void Board::BoardDraw()
{
	Image::Draw(hPict_);
}
