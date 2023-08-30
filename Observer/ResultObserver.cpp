#include "ResultObserver.h"
#include "../Engine/Audio.h"

namespace
{
    bool IsWin = false;
}

namespace ResultObserver
{
    void SetIsWin(bool result)
    {
        IsWin = result;
    }

    bool GetIsWin()
    {
        return IsWin;
    }
    void ResultAudio()
    {
        //èüÇ¡ÇΩÇ∆Ç´
        if (IsWin)
        {
            Audio::Play(Audio::Load("Audio/win.wav"));
        }
        else
        {
            Audio::Play(Audio::Load("Audio/lose.wav"));
        }
    }
}