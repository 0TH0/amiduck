#include "Observer.h"

namespace
{
    bool IsWin = false;
}

namespace Observer
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