#include "PlatformModule.h"

// SDL2プラットフォーム
#ifdef HE_USE_SDL2

#include "Platform/Core/SDL2/File.h"
#include "Platform/Core/SDL2/Input.h"
#include "Platform/Core/SDL2/System.h"
#include "Platform/Core/SDL2/Time.h"

#endif

namespace Platform
{
    PlatformModule::PlatformModule() : PlatformModule()
    {
    }

    HE::Bool PlatformModule::VIsQuit()
    {
        if (this->_bMainWindowInitialized == FALSE)
        {
            // メインウィンドウの処理が終わっている場合は終了状態
            return FALSE;
        }

        return TRUE;
    }

    /// <summary>
    /// モジュール初期化
    /// </summary>
    HE::Bool PlatformModule::_VStart()
    {
#ifdef HE_USE_SDL2
        this->_spSysmte = HE_MAKE_CUSTOM_SHARED_PTR((::Platform::SDL2::System));
        // プラットフォームの各機能を生成
        {
            this->_spTime  = HE_MAKE_CUSTOM_SHARED_PTR((::Platform::SDL2::Time));
            this->_spInput = HE_MAKE_CUSTOM_SHARED_PTR((::Platform::SDL2::Input));
            this->_spFile  = HE_MAKE_CUSTOM_SHARED_PTR((::Platform::SDL2::File));
        }
#else
        // TODO: DX12
#endif
        return TRUE;
    }

    /// <summary>
    /// インスタンス破棄時に呼ばれる
    /// </summary>
    HE::Bool PlatformModule::_VRelease()
    {
        this->_spFile.reset();
        this->_spInput.reset();
        this->_spTime.reset();
        this->_spSysmte.reset();

        return TRUE;
    }

    void PlatformModule::_VBeforeUpdate(const HE::Float32 in_fDeltaTime)
    {
        this->_spInput->VUpdate(in_fDeltaTime);
    }

}  // namespace Platform
