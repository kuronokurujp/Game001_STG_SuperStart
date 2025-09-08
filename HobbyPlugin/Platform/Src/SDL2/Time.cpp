// SDL2プラットフォームの機能
#ifdef HE_USE_SDL2

#include "Platform/Core/SDL2/Time.h"

// SDL2のヘッダーファイル
#include "SDL2/SDL.h"

namespace Platform::SDL2
{
    /// <summary>
    /// 現在の経過時間を取得(ミリセコンド)
    /// </summary>
    HE::Uint64 Time::VNowMSec()
    {
        return ::SDL_GetTicks();
    }

    /// <summary>
    /// 指定した時間停止(ミリセコンド)
    /// </summary>
    void Time::VSleepMSec(const HE::Uint64 in_uMs)
    {
        ::SDL_Delay(in_uMs);
    }
}  // namespace Platform
#endif
