#include "HitAudio.h"
#include "../Engine/Audio.h"
#include "ClickAudio.h"

namespace HitAudio
{
	int hAudio_;

	void Initialize()
	{
		hAudio_ = Audio::Load("Audio/hit.wav");
	}
	void HitAudio()
	{
		hAudio_ = Audio::Load("Audio/hit.wav");
		Audio::Play(hAudio_);
	}
}