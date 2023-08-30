#include "StageAudio.h"
#include "../Engine/Audio.h"

namespace StageAudio
{
	int hPopStageAudio_;
	
	void Initialize()
	{
		hPopStageAudio_ = Audio::Load("Audio/smoke.wav");
	}
	void PopStageAudio()
	{
		Audio::Play(hPopStageAudio_);
	}
}