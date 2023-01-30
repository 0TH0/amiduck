﻿#pragma once

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

	void SetIsFlash(bool IsFlash);

	bool GetIsFlash() { return IsFlash_; };

	int GetAlpha() { return alpha_; };
};