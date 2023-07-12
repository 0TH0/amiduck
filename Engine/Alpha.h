#pragma once

class Alpha
{
public:
	int time_;	//時間
	int alpha_;	//透明度
	int frame_;	//何フレーム毎に点滅させるか
	bool IsFlash_;	//フラッシュさせるか
	
	Alpha();
	~Alpha();

	void FlashModel(int frame);

	void FlashImage(int frame);

	void FlashImage2(int frame);

	void SetIsFlash(bool IsFlash);

	void FadeOutImage(float frame = 0.05f);

	void FadeInImage(float frame = 0.05f);

	bool GetIsFlash() { return IsFlash_; };

	int GetAlpha() { return alpha_; };

	int GetTime() { return time_; };
};