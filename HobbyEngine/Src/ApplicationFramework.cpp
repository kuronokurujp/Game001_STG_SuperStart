#include "Engine/ApplicationFramework.h"

#include "Engine/Engine.h"
#include "Engine/Time/FPS.h"

HE::Bool ApplicationEngineFramework::Init(const HE::Bool in_bDebug)
{
    // エンジン起動
    HE_CREATE_ENGINE;

    // TODO: エンジン用の設定ファイルが必要

    const HE::Bool bPreInitRet = HE_ENGINE.Init();
    HE_ASSERT_RETURN_VALUE(FALSE, bPreInitRet && "事前初期化に失敗");

    // モジュール登録
    if (this->_VRegistEngineModule() == FALSE) return FALSE;

    const HE::Bool bInitRet = HE_ENGINE.Start();
    HE_ASSERT_RETURN_VALUE(FALSE, bInitRet && "初期化に失敗");

    // TODO: FPSタイマーを作成
    // ゲームを固定フレームレートにするため

    this->_spFPS = this->_VCreateFPSTimer();
    HE_ASSERT_RETURN_VALUE(FALSE, this->_spFPS && "FPSタイマーの作成に失敗");

    // TODO: FPSは固定にして60にいったんしている
    this->_spFPS->EnableFixedMode(60);

    return TRUE;
}

void ApplicationEngineFramework::Release()
{
    this->_VUnRegistEngineModule();

    // エンジン終了
    HE_DELETE_ENGINE;
}

void ApplicationEngineFramework::Running()
{
    this->_VLoad();

    // TODO: 非同期処理にしたい
    this->_VStart();

    // ゲームループ
    HE::Float32 fDelta = 0.0f;
    while (HE_ENGINE.IsQuit() == FALSE)
    {
        // 前処理
        fDelta = HE_ENGINE.GetDeltaTimeSec();
        HE_ENGINE.BeforeUpdateLoop(fDelta);
        if (HE_ENGINE.IsQuit()) break;

        HE::Uint64 ulBeginMSec = this->_spFPS->GetLastTimeMSec();

        // 固定フレームモード
        if (this->_spFPS->IsFixedMode())
        {
            // 指定したFPSまで待機
            do
            {
                if (this->_spFPS->IsWaitFrameFixedMode())
                {
                    // TODO: 待機中は何か処理をした方がいい?
                    this->_VSleep(1);
                }
                else
                {
                    this->_spFPS->UpdateTime();
                    break;
                }
            } while (HE_ENGINE.IsQuit() == FALSE);
        }
        else
        {
            this->_spFPS->UpdateTime();
        }

        HE::Uint64 ulEndMSec = this->_spFPS->GetLastTimeMSec();

        if (HE_ENGINE.IsQuit()) break;

        HE_ENGINE.MainUpdateLoop(fDelta);
        if (HE_ENGINE.IsQuit()) break;

        HE_ENGINE.LateUpdateLoop(fDelta);
    }

    this->_VEnd();
}
