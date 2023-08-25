#include "ClickAudio.h"
#include "../Engine/Audio.h"

namespace ClickAudio
{
	int hAudio_;

	void Initialize()
	{
		hAudio_ = Audio::Load("Audio/click.wav");
	}
	void ClickAudio()
	{
		Audio::Play(hAudio_);
	}
}