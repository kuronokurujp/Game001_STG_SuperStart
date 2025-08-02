--初期化
function	InitParam( in_Handle )
	Debug_PrintDebugMessage( "BossStage1: InitParam\n" )

	--パラメータ設定
	local	initParam	=
	{
		Handle			= in_Handle,
		Type			= "Pawn",
		State			= "Normal",
		NextStateCnt	= 300,
		Hp				= 20,
		Speed			= 1.0,
		X				= 800,
		Y				= 200,
		Angle			= 180,
		Point			= 100,
		PartsHp			= 10,
		PartsPoint		= 200,
	}
	Actor_TriggerEvent( "RequestBossStage1InitParam", initParam )
end

--ボス１の挙動制御
function	Init( in_Handle )
	--パラメータ設定
	Debug_PrintDebugMessage( "BossStage1: Init\n" )

	print( "handle ", in_Handle )
	--	初期パラメータ設定関数を呼び出す
	InitParam( in_Handle )
end

--ボス１の通常移動の終了
function	EndNormalAct( in_Handle, in_Param )
	--	次の偏移先を決める
	Debug_PrintDebugMessage( "BossStage1: EndNormalAct\n" );

	--パラメータ設定
	local	initParam	=
	{
		Handle			= in_Handle,
		State			= "Attack",
		Angle			= -1,
	}

	Actor_TriggerEvent( "RequestBossStage1AtkAct", initParam )
end

--ボス１の攻撃終了
function	EndAttackAct( in_Handle, in_Param )
	Debug_PrintDebugMessage( "BossStage1: EndAttackAct\n" );

	--パラメータ設定
	local	initParam	=
	{
		Handle			= in_Handle,
		State			= "Normal",
		Angle			= -1,
		NextStateCnt	= 100,
	}

	Actor_TriggerEvent( "RequestBossStage1NormalAct", initParam )
end