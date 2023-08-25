#include "TutorialScece.h"
#include "../Engine/Image.h"
#include "../Engine/UI.h"
#include "../Engine/SceneManager.h"
#include "../Engine/Input.h"

namespace
{
	static UI* pPlayBt;
	XMFLOAT3 PosPlayBt;
	SceneManager* pSceneManager;
	static const int MAX_TIME = 120;
}

//コンストラクタ
TutorialScece::TutorialScece(GameObject* parent)
	: GameObject(parent, "TutorialScece"), hPict_(-1)
{
}

//初期化
void TutorialScece::Initialize()
{
	hPict_ = Image::Load("Image\\tutorial.jpg");
	assert(hPict_ >= 0);

	pPlayBt = Instantiate<UI>(this);
	pPlayBt->Load("Image\\playBt.png");
	PosPlayBt.y = -0.6f;
	assert(pPlayBt->GetHandle() >= 0);
}

//更新
void TutorialScece::Update()
{
	time_++;

	//２秒経ったら
	if (time_ >= MAX_TIME)
	{
		pPlayBt->SetShouldUseHitCursor(true);

		//カーソル画像の位置で左クリックしたら
		if (Image::IsHitCursor(pPlayBt->GetHandle()) && Input::IsMouseButtonDown(Input::LEFT))
		{
			pSceneManager = (SceneManager*)FindObject("SceneManager");
			pSceneManager->ChangeScene(SCENE_ID_PLAY);
		}
	}
}

//描画
void TutorialScece::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	pPlayBt->SetUIPosition(PosPlayBt);
	Image::Draw(pPlayBt->GetHandle());
}

//開放
void TutorialScece::Release()
{
}
