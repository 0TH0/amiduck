#pragma once

class Alpha
{
public:
	int time_;	//時間
	int alpha_;	//透明度
	int frameCount_;	//何フレーム毎に点滅させるか
	bool IsFlash_;	//フラッシュさせるか
	
	Alpha();
	~Alpha();

	void FlashModel(int frameMove_);

	void FlashImage(int frameMove_);

	void FlashImage2(int frameMove_);

	void SetIsFlash(bool IsFlash);

	void FadeOutImage(float frameMove_ = 0.05f);

	void FadeInImage(float frameMove_ = 0.05f);

	bool GetIsFlash() { return IsFlash_; };

	int GetAlpha() { return alpha_; };

	int GetTime() { return time_; };
};