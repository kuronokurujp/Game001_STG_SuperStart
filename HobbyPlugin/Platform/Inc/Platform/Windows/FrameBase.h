#pragma once

#include "Engine/Common/CustomMap.h"
#include "Engine/MiniEngine.h"
#include "Platform/Graphic/FrameConfig.h"

namespace Platform
{
    /// <summary>
    /// グラフィックの基本フレーム
    /// </summary>
    class FrameBase
    {
    public:
        FrameBase(const FrameConfig&, Core::Memory::UniquePtr<EventFrameInterface>);

        virtual void VSetPos(const HE::Uint32 in_uX, const HE::Uint32 in_uY) = 0;

        virtual void VActive() = 0;
        virtual void VShow()   = 0;
        virtual void VHide()   = 0;

        virtual void VBegin()                         = 0;
        virtual void VEnd()                           = 0;
        virtual void VUpdate(const HE::Float32 in_dt) = 0;

        virtual void VBeginFrame() = 0;
        virtual void VEndFrame() = 0;

        inline const FrameConfig& GetConfig() const { return this->_config; }

    protected:
        Core::Memory::UniquePtr<Platform::EventFrameInterface> _upEvent;

    private:
        Platform::FrameConfig _config;
    };
}  // namespace Platform
