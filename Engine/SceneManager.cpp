#include "sceneManager.h"
#include "../Scene/PlayScene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/ResultScene.h"
#include "../Scene/TutorialScece.h"
#include "Model.h"
#include "Image.h"
#include "Audio.h"
#include "Input.h"
#include "VFX.h"
#include "../Manager/AudioManager.h"

//コンストラクタ
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager"),nextSceneID_(),currentSceneID_()
{
}

//初期化
void SceneManager::Initialize()
{
	//最初のシーンを準備
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

//更新
void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//ロードしたデータを全削除
		Audio::AllRelease();
		Model::AllRelease();
		Image::AllRelease();
		VFX::Release();

		//そのシーンのオブジェクトを全削除
		KillAllChildren();
		
		//オーディオ初期化
		AudioManager::Initialize();

		//次のシーンを作成
		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		case SCENE_ID_PLAY: Instantiate<PlayScene>(this); break;
		case SCENE_ID_RESULT: Instantiate<ResultScene>(this); break;
		case SCENE_ID_TUTORIAL: Instantiate<TutorialScece>(this); break;
		}
		currentSceneID_ = nextSceneID_;
	}
}

//描画
void SceneManager::Draw()
{
}

//開放
void SceneManager::Release()
{
}

//シーン切り替え（実際に切り替わるのはこの次のフレーム）
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}