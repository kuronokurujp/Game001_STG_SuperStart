function	InitParam( in_Handle )
	Debug_PrintDebugMessage( "EnemyZako2: InitParam\n" )

	--パラメータ設定
	local	initParam	=
	{
		Handle			= in_Handle,
		Type			= "Knight",
		State			= "Normal",
		NextStateCnt	= 30,
		Hp				= 3,
		Speed			= 2.0,
		X				= 500,
		Y				= 30,
		Angle			= 180,
		Point			= 300,
	}
	Actor_TriggerEvent( "RequestEnemyZakoInitParam", initParam )
end

--雑魚敵の挙動制御
function	Init( in_Handle )
	--パラメータ設定
	Debug_PrintDebugMessage( "EnemyZako2: Init\n" )
	--初期パラメータ設定関数を呼び出す
	InitParam( in_Handle )
end

--	雑魚敵の通常処理の終了
function	EndNormalAct( in_Handle, in_Param )
	--	次の偏移先を決める
	Debug_PrintDebugMessage( "EnemyZako: EndNormalAct\n" );

	--パラメータ設定
	local	param	=
	{
		Handle			= in_Handle,
		Type			= "Knight",
		Speed			= 3.0,
		Angle			= in_Param.Angle + 20,
	}

	Actor_TriggerEvent( "RequestEnemyZakoEscapeAct", param )
end