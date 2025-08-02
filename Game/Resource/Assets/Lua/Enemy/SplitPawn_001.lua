function	InitParam( in_Handle )
	Debug_PrintDebugMessage( "EnemySplit: InitParam\n" )

	--�p�����[�^�ݒ�
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

--�G���G�̋�������
function	Init( in_Handle )
	--�p�����[�^�ݒ�
	Debug_PrintDebugMessage( "EnemySplit: Init\n" )
	--	�����p�����[�^�ݒ�֐����Ăяo��
	InitParam( in_Handle )
end

--	�G���G�̒ʏ�ړ��̏I��
function	EndNormalAct( in_Handle )
	--	���̕Έڐ�����߂�
	Debug_PrintDebugMessage( "EnemySplit: EndNormalAct\n" );

	--�p�����[�^�ݒ�
	local	param	=
	{
		Handle			= in_Handle,
		Type			= "Pawn",
	}

	--	����J�n(���Ɏ��S����)
	Actor_TriggerEvent( "RequestEnemySplitDieAct", param );
end