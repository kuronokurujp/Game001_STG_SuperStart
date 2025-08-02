function	InitParam( in_Handle )
	Debug_PrintDebugMessage( "EnemySnake: InitParam\n" )

	--パラメータ設定
	local	initParam	=
	{
		Handle			= in_Handle,
		State			= "Normal",
		NextStateCnt	= 60,
		Hp				= 1,
		Speed			= 2,
		X				= 300,
		Y				= 300,
		LinkPosNum		= 8,
		Point			= 400,
	}
	Actor_TriggerEvent( "RequestEnemySnakeInitParam", initParam )
end

--雑魚敵の挙動制御
function	Init( in_Handle )
	--パラメータ設定
	Debug_PrintDebugMessage( "EnemySnake: Init\n" )
	--	初期パラメータ設定関数を呼び出す
	InitParam( in_Handle )
end

--	雑魚敵の通常移動の終了
function	EndNormalAct( in_Handle )
	--	次の偏移先を決める
	Debug_PrintDebugMessage( "EnemySnake: EndNormalAct\n" );

	--パラメータ設定
	local	param	=
	{
		Handle			= in_Handle,
		Speed			= 2.0,
	}

	Actor_TriggerEvent( "RequestEnemySnakeEscapeAct", param )
end