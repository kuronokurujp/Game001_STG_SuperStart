// SDL2プラットフォームの機能
#ifdef HE_USE_SDL2

#pragma once

#include "Platform/Interface/System.h"

namespace Platform::SDL2
{
    /// <summary>
    /// SDL2プラットフォームのシステム
    /// </summary>
    class System final : public Platform::SystemInterface
    {
    public:
        System();
        virtual ~System();

        HE::UTF8* GetVersion() { return HE_STR_U8_TEXT("#version 330 core"); }

        HE::Uint32 VGetRand(const HE::Uint32) override final;
        HE::Bool VSetSeedRand(const HE::Uint32) override final;

        // 小数点を含めた乱数
        HE::Float32 VGetRandByFloat(const HE::Float32 in_fMin,
                                    const HE::Float32 in_fMax) override final;
        HE::Bool VSetSeedRandByFloat() override final;
    };
}  // namespace Platform
#endif
