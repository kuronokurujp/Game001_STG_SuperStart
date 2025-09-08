// SDL2プラットフォームの機能
#ifdef HE_USE_SDL2

#pragma once

#include "Platform/Interface/Time.h"

namespace Platform::SDL2
{
    /// <summary>
    /// プラットフォームの時間インターフェイス
    /// </summary>
    class Time final : public Platform::TimeInterface
    {
    public:
        HE::Uint64 VNowMSec() override final;
        void VSleepMSec(const HE::Uint64 in_uMs) override final;
    };
}  // namespace Platform
#endif
