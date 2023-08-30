#include "BGMManager.h"
#include "../Engine/Audio.h"

namespace BGMManager
{
	int hTitleBGM_;

	void Initialize()
	{
		hTitleBGM_ = Audio::Load("Audio/titleBGM.wav");
	}
	void TitleBGM()
	{
		Audio::PlayLoop(hTitleBGM_);
	}
	void Stop()
	{
		Audio::Stop(hTitleBGM_);
	}
}