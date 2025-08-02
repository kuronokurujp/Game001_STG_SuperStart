function	InitParam( in_Handle )
	Debug_PrintDebugMessage( "EnemySnake: InitParam\n" )

	--�p�����[�^�ݒ�
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

--�G���G�̋�������
function	Init( in_Handle )
	--�p�����[�^�ݒ�
	Debug_PrintDebugMessage( "EnemySnake: Init\n" )
	--	�����p�����[�^�ݒ�֐����Ăяo��
	InitParam( in_Handle )
end

--	�G���G�̒ʏ�ړ��̏I��
function	EndNormalAct( in_Handle )
	--	���̕Έڐ�����߂�
	Debug_PrintDebugMessage( "EnemySnake: EndNormalAct\n" );

	--�p�����[�^�ݒ�
	local	param	=
	{
		Handle			= in_Handle,
		Speed			= 2.0,
	}

	Actor_TriggerEvent( "RequestEnemySnakeEscapeAct", param )
end