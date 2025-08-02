--������
function	InitParam( in_Handle )
	Debug_PrintDebugMessage( "BossStage1: InitParam\n" )

	--�p�����[�^�ݒ�
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

--�{�X�P�̋�������
function	Init( in_Handle )
	--�p�����[�^�ݒ�
	Debug_PrintDebugMessage( "BossStage1: Init\n" )

	print( "handle ", in_Handle )
	--	�����p�����[�^�ݒ�֐����Ăяo��
	InitParam( in_Handle )
end

--�{�X�P�̒ʏ�ړ��̏I��
function	EndNormalAct( in_Handle, in_Param )
	--	���̕Έڐ�����߂�
	Debug_PrintDebugMessage( "BossStage1: EndNormalAct\n" );

	--�p�����[�^�ݒ�
	local	initParam	=
	{
		Handle			= in_Handle,
		State			= "Attack",
		Angle			= -1,
	}

	Actor_TriggerEvent( "RequestBossStage1AtkAct", initParam )
end

--�{�X�P�̍U���I��
function	EndAttackAct( in_Handle, in_Param )
	Debug_PrintDebugMessage( "BossStage1: EndAttackAct\n" );

	--�p�����[�^�ݒ�
	local	initParam	=
	{
		Handle			= in_Handle,
		State			= "Normal",
		Angle			= -1,
		NextStateCnt	= 100,
	}

	Actor_TriggerEvent( "RequestBossStage1NormalAct", initParam )
end