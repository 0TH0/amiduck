#pragma once

/// <summary>
/// 様々な音を管理する
/// </summary>
namespace AudioManager
{
	//初期化
	void Initialize();

	//シーン遷移の時の初期化
	void SceneTransitionInitialize();

	//クリック音
	void ClickAudio();
	
	//ヒット音
	void HitAudio();

	//プレイBGM
	void PlayBGM();

	//タイトルBGM
	void TitleBGM();

	//勝った音
	void WinAudio();

	//負けた音
	void LoseAudio();

	//ジャンプ音
	void JumpAudio();

	//煙の音
	void SmokeAudio();

	//星の音
	void StarAudio();

	//プレイBGMストップ
	void StopPlayBGM();

	//タイトルBGM
	void StopTitleBGM();
}