#pragma once
#include "Engine/MiniEngine.h"
#include "Engine/Module/Module.h"
// モジュールのヘッダーファイルは全てインクルードする
namespace RHI
{
    /// <summary>
    /// RHIアクター用の追加モジュール
    /// </summary>
    class RHIModule final : public Module::ModuleBase
    {
        HE_MODULE_GENRATE_DECLARATION(RHIModule);
    public:
        RHIModule() : ModuleBase(ModuleName()) {}
    protected:
        /// <summary>
        /// モジュール初期化
        /// </summary>
        HE::Bool _VStart() override final;
        /// <summary>
        /// インスタンス破棄時に呼ばれる
        /// </summary>
        HE::Bool _VRelease() override final;
    };
}  // namespace RHI
