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
}