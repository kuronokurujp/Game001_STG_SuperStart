function	InitParam( in_Handle )
	Debug_PrintDebugMessage( "EnemyZako2: InitParam\n" )

	--�p�����[�^�ݒ�
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

--�G���G�̋�������
function	Init( in_Handle )
	--�p�����[�^�ݒ�
	Debug_PrintDebugMessage( "EnemyZako2: Init\n" )
	--�����p�����[�^�ݒ�֐����Ăяo��
	InitParam( in_Handle )
end

--	�G���G�̒ʏ폈���̏I��
function	EndNormalAct( in_Handle, in_Param )
	--	���̕Έڐ�����߂�
	Debug_PrintDebugMessage( "EnemyZako: EndNormalAct\n" );

	--�p�����[�^�ݒ�
	local	param	=
	{
		Handle			= in_Handle,
		Type			= "Knight",
		Speed			= 3.0,
		Angle			= in_Param.Angle + 20,
	}

	Actor_TriggerEvent( "RequestEnemyZakoEscapeAct", param )
end