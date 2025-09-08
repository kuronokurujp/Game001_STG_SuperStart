#pragma once

#include "Engine/MiniEngine.h"
#include "Engine/Module/Module.h"
#include "Platform/Interface/File.h"
#include "Platform/Interface/Input.h"
#include "Platform/Interface/System.h"
#include "Platform/Interface/Time.h"

/// <summary>
/// SDL2やDirectXなどのプラットフォームに依存するモジュール
/// 最初エンジンにインターフェイスを実装したが、エンジンはあくまでOSでいうところのカーネルようなもので、
/// プラットフォーム関連は全てモジュールに実装することにした
/// </summary>
namespace Platform
{
    /// <summary>
    /// Platformアクター用の追加モジュール
    /// </summary>
    class PlatformModule final : public Module::ModuleBase
    {
        HE_MODULE_GENRATE_DECLARATION(PlatformModule);

    public:
        PlatformModule();

        /// <summary>
        /// 時間関連の処理
        /// </summary>
        Core::Memory::SharedPtr<Platform::TimeInterface> Time() { return this->_spTime; }

        /// <summary>
        /// 入力関連
        /// </summary>
        Core::Memory::SharedPtr<Platform::InputInterface> Input() { return this->_spInput; }

        /// <summary>
        /// ファイル関連
        /// </summary>
        Core::Memory::SharedPtr<Platform::FileInterface> File() { return this->_spFile; }

        /// <summary>
        /// システム関連
        /// </summary>
        Core::Memory::SharedPtr<Platform::SystemInterface> System() { return this->_spSysmte; }

        /// <summary>
        /// プラットフォームの終了状態か
        /// </summary>
        /// <returns></returns>
        HE::Bool VIsQuit();

    protected:
        /// <summary>
        /// モジュール初期化
        /// </summary>
        HE::Bool _VStart() override final;

        /// <summary>
        /// インスタンス破棄時に呼ばれる
        /// </summary>
        HE::Bool _VRelease() override final;

        /// <summary>
        /// 前更新
        /// </summary>
        void _VBeforeUpdate(const HE::Float32 in_fDeltaTime) override final;

    protected:
        Core::Memory::SharedPtr<Platform::TimeInterface> _spTime;
        Core::Memory::SharedPtr<Platform::InputInterface> _spInput;
        Core::Memory::SharedPtr<Platform::FileInterface> _spFile;
        Core::Memory::SharedPtr<Platform::SystemInterface> _spSysmte;

    private:
        HE::Bool _bMainWindowInitialized = TRUE;
    };
}  // namespace Platform
