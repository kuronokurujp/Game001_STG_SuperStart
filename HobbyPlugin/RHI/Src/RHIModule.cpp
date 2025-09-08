#include "RHIModule.h"
namespace RHI
{
    /// <summary>
    /// モジュール初期化
    /// </summary>
    HE::Bool RHIModule::_VStart()
    {
        return TRUE;
    }
    /// <summary>
    /// インスタンス破棄時に呼ばれる
    /// </summary>
    HE::Bool RHIModule::_VRelease()
    {
        return TRUE;
    }
}  // namespace RHI
