#include "ClickAudio.h"
#include "../Engine/Audio.h"

namespace ClickAudio
{
	int hClickAudio_;

	void Initialize()
	{
		hClickAudio_ = Audio::Load("Audio/click.wav");
	}
	void ClickAudio()
	{
		Audio::Play(hClickAudio_);
	}
}