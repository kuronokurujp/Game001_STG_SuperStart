function	InitParam( in_Handle )
	Debug_PrintDebugMessage( "EnemySplit: InitParam\n" )

	--パラメータ設定
	local	initParam	=
	{
		Handle			= in_Handle,
		Type			= "Pawn",
		State			= "Normal",
		NextStateCnt	= 60,
		Hp				= 10,
		Speed			= 2.0,
		X				= 500,
		Y				= 40,
		Angle			= 180,
		ZakoNum			= 4,
		Point			= 350,
	}
	Actor_TriggerEvent( "RequestEnemySplitInitParam", initParam )
end

--雑魚敵の挙動制御
function	Init( in_Handle )
	--パラメータ設定
	Debug_PrintDebugMessage( "EnemySplit: Init\n" )
	--	初期パラメータ設定関数を呼び出す
	InitParam( in_Handle )
end

--	雑魚敵の通常移動の終了
function	EndNormalAct( in_Handle )
	--	次の偏移先を決める
	Debug_PrintDebugMessage( "EnemySplit: EndNormalAct\n" );

	--パラメータ設定
	local	param	=
	{
		Handle			= in_Handle,
		Type			= "Pawn",
	}

	--	分裂開始(俗に死亡する)
	Actor_TriggerEvent( "RequestEnemySplitDieAct", param );
end