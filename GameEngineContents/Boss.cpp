#include "PreCompile.h"
#include "Boss.h"
#include "DamageNumber.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "BossUI.h"
#include "BossHat.h"

Boss::Boss() 
	: CurState_(BossState::MAX)
	, CurType_(BossType::NORMAL)
	, Position_(0.f)
	, PlayerPos_(0.f)
	, AttackACollision_(nullptr)
	, AttackBCollision_(nullptr)
	, BlueAttackACollision_(nullptr)
	, RedAttackACollision_(nullptr)
	, RedAttackBCollision_(nullptr)
	, CreateHatTime_(0.f)
	, RandomTime_(0)
	, CurBossSkill_(BossAttackType::MAX)
	, TypeChangeTime_(0.f)
	, BossTypeChange_(false)
	, Random_(0)
	, TransformTime_(0.f)
	, TeleportTime_(0.f)
	, IsTeleport_(false)
	, Speed_(100.f)
	, BlueSpeed_(140.f)
{
}

Boss::~Boss() 
{
}

void Boss::Start()
{
	GetTransform().SetLocalPosition({ 0, 0, (int)ZOrder::MONSTER });
	IdleTime_ = GameEngineRandom::MainRandom.RandomInt(1, 3);
	MoveTime_ = GameEngineRandom::MainRandom.RandomInt(20, 30);

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ 170.f, 180.f });
	Collision_->ChangeOrder(GAMEOBJGROUP::MONSTER);

	AttackACollision_ = CreateComponent<GameEngineCollision>();
	AttackACollision_->GetTransform().SetLocalScale({ 150.f, 150.f });
	AttackACollision_->ChangeOrder(BossAttackType::Att_A);
	AttackACollision_->Off();

	AttackBCollision_ = CreateComponent<GameEngineCollision>();
	AttackBCollision_->GetTransform().SetLocalScale({ 150.f, 150.f });
	AttackBCollision_->ChangeOrder(BossAttackType::Att_B);
	AttackBCollision_->Off();

	BlueAttackACollision_ = CreateComponent<GameEngineCollision>();
	BlueAttackACollision_->GetTransform().SetLocalScale({ 150.f, 150.f });
	BlueAttackACollision_->ChangeOrder(BossAttackType::BlueAtt_A);
	BlueAttackACollision_->Off();

	RedAttackACollision_ = CreateComponent<GameEngineCollision>();
	RedAttackACollision_->GetTransform().SetLocalScale({ 150.f, 150.f });
	RedAttackACollision_->ChangeOrder(BossAttackType::RedAtt_A);
	RedAttackACollision_->Off();

	RedAttackBCollision_ = CreateComponent<GameEngineCollision>();
	RedAttackBCollision_->GetTransform().SetLocalScale({ 150.f, 150.f });
	RedAttackBCollision_->ChangeOrder(BossAttackType::RedAtt_B);
	RedAttackBCollision_->Off();


	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalScale({ 800.f, 800.f });	// Idle
	Renderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Boss_Idle", 0.12f));
	Renderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Boss_Move", 0.14f));
	Renderer_->CreateFrameAnimationFolder("AttackA", FrameAnimation_DESC("Boss_Att1", 0.1f));
	Renderer_->CreateFrameAnimationFolder("AttackB", FrameAnimation_DESC("Boss_Att2", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Transform", FrameAnimation_DESC("Boss_Transform", 0.11f));
	Renderer_->CreateFrameAnimationFolder("Regen", FrameAnimation_DESC("Boss_Regen", 0.11f));
	Renderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("Boss_Damaged", 0.2f));
	Renderer_->CreateFrameAnimationFolder("Die", FrameAnimation_DESC("Boss_Die", 0.12f));

	// Blue
	Renderer_->CreateFrameAnimationFolder("Blue_Idle", FrameAnimation_DESC("BlueBoss_Idle", 0.12f));
	Renderer_->CreateFrameAnimationFolder("Blue_Attack", FrameAnimation_DESC("BlueBoss_Att", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Blue_Transform", FrameAnimation_DESC("BlueBoss_Transform", 0.11f));
	Renderer_->CreateFrameAnimationFolder("Blue_Regen", FrameAnimation_DESC("BlueBoss_Regen", 0.11f));
	Renderer_->CreateFrameAnimationFolder("Blue_Damaged", FrameAnimation_DESC("BlueBoss_Damaged", 0.2f));
	Renderer_->CreateFrameAnimationFolder("Blue_Die", FrameAnimation_DESC("BlueBoss_Die", 0.12f));

	// Red
	Renderer_->CreateFrameAnimationFolder("Red_Idle", FrameAnimation_DESC("RedBoss_Idle", 0.12f));
	Renderer_->CreateFrameAnimationFolder("Red_Move", FrameAnimation_DESC("RedBoss_Move", 0.14f));
	Renderer_->CreateFrameAnimationFolder("Red_AttackA", FrameAnimation_DESC("RedBoss_Att1", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Red_AttackB", FrameAnimation_DESC("RedBoss_Att2", 0.08f));
	Renderer_->CreateFrameAnimationFolder("Red_Transform", FrameAnimation_DESC("RedBoss_Transform", 0.11f));
	Renderer_->CreateFrameAnimationFolder("Red_Regen", FrameAnimation_DESC("RedBoss_Regen", 0.11f));
	Renderer_->CreateFrameAnimationFolder("Red_Tel", FrameAnimation_DESC("RedBoss_Tel", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Red_TelRegen", FrameAnimation_DESC("RedBoss_TelRegen", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Red_Damaged", FrameAnimation_DESC("RedBoss_Damaged", 0.2f));
	Renderer_->CreateFrameAnimationFolder("Red_Die", FrameAnimation_DESC("RedBoss_Die", 0.12f));

	Renderer_->AnimationBindEnd("Die", std::bind(&Boss::BindBossDieEnd, this, std::placeholders::_1));
	
	Renderer_->AnimationBindStart("AttackA", std::bind(&Boss::BindBossAttackStart, this, std::placeholders::_1));
	Renderer_->AnimationBindStart("AttackB", std::bind(&Boss::BindBossAttackStart, this, std::placeholders::_1));
	Renderer_->AnimationBindStart("Blue_Attack", std::bind(&Boss::BindBossAttackStart, this, std::placeholders::_1));
	Renderer_->AnimationBindStart("Red_AttackA", std::bind(&Boss::BindBossAttackStart, this, std::placeholders::_1));
	Renderer_->AnimationBindStart("Red_AttackB", std::bind(&Boss::BindBossAttackStart, this, std::placeholders::_1));
	Renderer_->AnimationBindStart("AttackA", std::bind(&Boss::BindBossAttackStart, this, std::placeholders::_1));
	Renderer_->AnimationBindStart("AttackB", std::bind(&Boss::BindBossAttackStart, this, std::placeholders::_1));
	Renderer_->AnimationBindStart("Blue_Attack", std::bind(&Boss::BindBossAttackStart, this, std::placeholders::_1));
	Renderer_->AnimationBindStart("Red_AttackA", std::bind(&Boss::BindBossAttackStart, this, std::placeholders::_1));
	Renderer_->AnimationBindStart("Red_AttackB", std::bind(&Boss::BindBossAttackStart, this, std::placeholders::_1));

	Renderer_->AnimationBindFrame("AttackA", std::bind(&Boss::BindBossAttackFrame, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame("AttackB", std::bind(&Boss::BindBossAttackFrame, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame("Blue_Attack", std::bind(&Boss::BindBossAttackFrame, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame("Red_AttackA", std::bind(&Boss::BindBossAttackFrame, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame("Red_AttackB", std::bind(&Boss::BindBossAttackFrame, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame("AttackA", std::bind(&Boss::BindBossAttackFrame, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame("AttackB", std::bind(&Boss::BindBossAttackFrame, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame("Blue_Attack", std::bind(&Boss::BindBossAttackFrame, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame("Red_AttackA", std::bind(&Boss::BindBossAttackFrame, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame("Red_AttackB", std::bind(&Boss::BindBossAttackFrame, this, std::placeholders::_1));
	
	Renderer_->AnimationBindEnd("AttackA", std::bind(&Boss::BindBossAttackEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("AttackB", std::bind(&Boss::BindBossAttackEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Blue_Attack", std::bind(&Boss::BindBossAttackEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Red_AttackA", std::bind(&Boss::BindBossAttackEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Red_AttackB", std::bind(&Boss::BindBossAttackEnd, this, std::placeholders::_1));

	Renderer_->AnimationBindEnd("Damaged", std::bind(&Boss::BindBossDamagedEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Blue_Damaged", std::bind(&Boss::BindBossDamagedEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Red_Damaged", std::bind(&Boss::BindBossDamagedEnd, this, std::placeholders::_1));

	Renderer_->AnimationBindFrame("Transform", std::bind(&Boss::BindBossTransformFrame, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame("Blue_Transform", std::bind(&Boss::BindBossTransformFrame, this, std::placeholders::_1));
	Renderer_->AnimationBindFrame("Red_Transform", std::bind(&Boss::BindBossTransformFrame, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Transform", std::bind(&Boss::BindBossTransformEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Blue_Transform", std::bind(&Boss::BindBossTransformEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Red_Transform", std::bind(&Boss::BindBossTransformEnd, this, std::placeholders::_1));

	Renderer_->AnimationBindEnd("Regen", std::bind(&Boss::BindBossRegenEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Blue_Regen", std::bind(&Boss::BindBossRegenEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Red_Regen", std::bind(&Boss::BindBossRegenEnd, this, std::placeholders::_1));

	Renderer_->AnimationBindEnd("Red_Tel", std::bind(&Boss::BindRedBossTelEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Red_TelRegen", std::bind(&Boss::BindRedBossTelRegenEnd, this, std::placeholders::_1));
//	Renderer_->AnimationBindEnd("Red_AttackB", std::bind(&Boss::BindRedBossAttackBEnd, this, std::placeholders::_1));

	Renderer_->ChangeFrameAnimation("Move");
	ChangeState(BossState::Move);

	SetHP(1000.f);
	SetMaxHP(HP_);
	SetSpeed(Speed_);
	SetPixelCheckPos(44, -113);
	SetMonsterName(MONSTERNAME::Boss);
	SetMonsterType(MONSTERTYPE::ATTACK);
	SetMonsterDir(ACTORDIR::NONE);
	SetBossType(BossType::NORMAL);

	BossUI* BossUI_ = GetLevel()->CreateActor<BossUI>(GAMEOBJGROUP::UI);
	BossUI_->SetBoss(this);
}

void Boss::Update(float _DeltaTime)
{
	SetChangeTime(IdleTime_, MoveTime_);;
	MonsterStateUpdate();
	PixelCollisionMapUpdate(this, LeftRightPos_, BottomPos_);

	CollisonCheck();
	DirChange();

	if (CanAttTime_ > 4.f)
	{
		CanAttTime_ = 0.0f;
		IsAttack = false;
	}

	if (AttEndTime_ > 0.04f)
	{
		AttEndTime_ = 0.0f;
		IsAttackEnd = false;

		ChangeState(BossState::Idle);
		return;
	}

	if (TeleportTime_ > 3.f)
	{
		TeleportTime_ = 0.f;
		IsTeleport_ = false;
		ChangeState(BossState::RED_TelRegen);
		return;
	}

	if (true == IsTeleport_)
	{
		TeleportTime_ += _DeltaTime;
	}

	if (true == IsAttack)
	{
		CanAttTime_ += _DeltaTime;
	}

	if (true == IsAttackEnd)
	{
		AttEndTime_ += _DeltaTime;
	}

	CreateHatTime_ += _DeltaTime;

	// 20초마다 상태 체인지
	//if (CurState_ == BossState::Attack_A
	//	|| CurState_ == BossState::Attack_B
	//	|| CurState_ == BossState::RED_Tel
	//	|| CurState_ == BossState::RED_TelRegen)
	//{
	//	return;
	//}
	if (CurType_ == BossType::BLUE || CurType_ == BossType::RED)
	{
		if (TypeChangeTime_ > 10.f)
		{
			TypeChangeTime_ = 0.f;
			ChangeState(BossState::Transform);
			return;
		}
	}
	else if (CurType_ == BossType::NORMAL)
	{
		if (TypeChangeTime_ > 5.f)
		{
			TypeChangeTime_ = 0.f;
			ChangeState(BossState::Transform);
			return;
		}
	}


	//RandomTime_ = GameEngineRandom::MainRandom.RandomInt(5, 13);
	//if (CreateHatTime_ > 2.f)
	//{
	//	BossHat* Hat = GetLevel()->CreateActor<BossHat>();
	//	Hat->GetTransform().SetLocalPosition({ GetPlayerPosition() });
	//	//for (int i = 0; i < 5; ++i)
	//	//{
	//	//	BossHat* Hat = GetLevel()->CreateActor<BossHat>();
	//	//	Hat->GetTransform().SetLocalPosition({GetPlayerPosition()});
	//	//}

	//	CreateHatTime_ = 0.f;
	//}

}

void Boss::ChangeState(BossState _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case BossState::Idle:
			IdleStart();
			break;
		case BossState::Move:
			MoveStart();
			break;
		case BossState::Transform:
			TransformStart();
			break;
		case BossState::Regen:
			RegenStart();
			break;
		case BossState::Damaged:
			DamagedStart();
			break;
		case BossState::Die:
			DieStart();
			break;
		case BossState::Attack_A:
			AttackAStart();
			break;
		case BossState::Attack_B:
			AttackBStart();
			break;
		case BossState::Attack_C:
			AttackCStart();
			break;
		case BossState::BLUE_Attack:
			BlueAttackStart();
			break;
		case BossState::RED_AttackA:
			RedAttackAStart();
			break;
		case BossState::RED_AttackB:
			RedAttackBStart();
			break;
		case BossState::RED_Tel:
			RedTeleportStart();
			break;
		case BossState::RED_TelRegen:
			RedTeleportRegenStart();
			break;
		}
	}

	CurState_ = _State;
}

void Boss::MonsterStateUpdate()
{
	switch (CurState_)
	{
	case BossState::Idle:
		IdleUpdate();
		break;
	case BossState::Move:
		MoveUpdate();
		break;
	case BossState::Transform:
		TransformUpdate();
		break;
	case BossState::Regen:
		RegenUpdate();
		break;
	case BossState::Damaged:
		DamagedUpdate();
		break;
	case BossState::Die:
		DieUpdate();
		break;
	case BossState::Attack_A:
		AttackAUpdate();
		break;
	case BossState::Attack_B:
		AttackBUpdate();
		break;
	case BossState::Attack_C:
		AttackCUpdate();
		break;
	case BossState::BLUE_Attack:
		BlueAttackUpdate();
		break;
	case BossState::RED_AttackA:
		RedAttackAUpdate();
		break;
	case BossState::RED_AttackB:
		RedAttackBUpdate();
		break;
	case BossState::RED_Tel:
		RedTeleportUpdate();
		break;
	case BossState::RED_TelRegen:
		RedTeleportRegenUpdate();
		break;
	}
}

void Boss::Hit()
{
	TakeDamage(50);
}

void Boss::DirChange()
{
	// Blue는 Move X
	if (CurType_ == BossType::BLUE)
	{
		return;
	}
	DirCheck(Renderer_, CurDir_);

	if (CurState_ == BossState::Move)
	{
		if (CurDir_ == ACTORDIR::LEFT)
		{
			GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * GameEngineTime::GetDeltaTime());

		}
		else if (CurDir_ == ACTORDIR::RIGHT)
		{
			GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * GameEngineTime::GetDeltaTime());
		}
	}
}

void Boss::Attack()
{
	if (true == IsAttack)
	{
		return;
	}

	switch (CurType_)
	{
	case BossType::NORMAL:
	{
		if (200.f >= abs(GetPosition().x - GetPlayerPosition().x))
		{
			int Random = GameEngineRandom::MainRandom.RandomInt(0, 1);
			switch (Random)
			{
			case 0:
				ChangeState(BossState::Attack_A);
				return;
				break;
			case 1:
				ChangeState(BossState::Attack_B);
				return;
				break;
			default:
				break;
			}
		}	
	}
	break;
	case BossType::BLUE:
	{
		return;
	}
	break;
	case BossType::RED:
	{
		if (200.f > abs(GetPosition().x - GetPlayerPosition().x))
		{
			ChangeState(BossState::RED_AttackA);
			return;
		}
		else if (300.f < abs(GetPosition().x - GetPlayerPosition().x))
		{
			ChangeState(BossState::RED_Tel);
			return;
		}
	}
	break;
	default:
		break;
	}

}

void Boss::CollisonCheck()
{
	if (true == IsDie())
	{
		ChangeState(BossState::Die);
		return;
	}

	if (true == IsHit)									// 충돌 true이면 IsHIt -> On
	{
		Collision_->Off();
		DamageTime_ += GameEngineTime::GetDeltaTime();	// 시간을 잰다

		if (0.8f < DamageTime_)
		{
			ChangeState(BossState::Move);				// 상태 체인지
		}
		if (1.8f < DamageTime_)							// 2초가 지났으면 다시 IsHit -> Off
		{
			IsHit = false;
			DamageTime_ = 0.0f;							// 시간 리셋
			
			Collision_->On();
			return;
		}
	}

	if (true == Collision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::SKILL, CollisionType::CT_OBB2D))
	{
		ChangeState(BossState::Damaged);
		return;
	}
}

void Boss::IdleStart()
{
	switch (CurType_)
	{
	case BossType::NORMAL: 
	{
		Renderer_->ChangeFrameAnimation("Idle");
	}
		break;
	case BossType::BLUE:
	{
		Renderer_->ChangeFrameAnimation("Blue_Idle");
	}
		break;
	case BossType::RED:
	{
		Renderer_->ChangeFrameAnimation("Red_Idle");
	}
		break;

	default:
		break;
	}

}

void Boss::MoveStart()
{
	switch (CurType_)
	{
	case BossType::NORMAL:
	{
		Renderer_->ChangeFrameAnimation("Move");
	}
	break;
	case BossType::BLUE:
	{
	}
	break;
	case BossType::RED:
	{
		Renderer_->ChangeFrameAnimation("Red_Move");
	}
	break;

	default:
		break;
	}

}

void Boss::DamagedStart()
{
	GameEngineSound::SoundPlayOneShot("BossDamage.mp3");

	MoveDir_ = GetPosition();
	PlayerPos_ = GetPlayerPosition();
	MonsterPos_ = GetPosition();

	DamageNumber* DamageNum_ = GetLevel()->CreateActor<DamageNumber>();
	DamageNum_->SetMonster(this);
	DamageNum_->SetDamageType(DamageType::Monster);
	Damage_ = GameEngineRandom::MainRandom.RandomInt(1000, 9999);
	DamageNum_->GetTransform().SetLocalMove({0.f, 45.f});
	DamageNum_->SetDamage(Damage_);

	switch (CurType_)
	{
	case BossType::NORMAL:
	{
		Renderer_->ChangeFrameAnimation("Damaged");
	}
	break;
	case BossType::BLUE:
	{
		Renderer_->ChangeFrameAnimation("Blue_Damaged");
	}
	break;
	case BossType::RED:
	{
		Renderer_->ChangeFrameAnimation("Red_Damaged");
	}
	break;

	default:
		break;
	}
}

void Boss::DieStart()
{
	GameEngineSound::SoundPlayOneShot("BossDie.mp3");
	AddAccTime(Time_);

	switch (CurType_)
	{
	case BossType::NORMAL:
	{
		Renderer_->ChangeFrameAnimation("Die");
	}
	break;
	case BossType::BLUE:
	{
		Renderer_->ChangeFrameAnimation("Blue_Die");
	}
	break;
	case BossType::RED:
	{
		Renderer_->ChangeFrameAnimation("Red_Die");
	}
	break;

	default:
		break;
	}


	Collision_->Off();
}

void Boss::TransformStart()
{
	switch (CurType_)
	{
	case BossType::NORMAL:
	{
		Renderer_->ChangeFrameAnimation("Transform");
	}
	break;
	case BossType::BLUE:
	{
		Renderer_->ChangeFrameAnimation("Blue_Transform");
	}
	break;
	case BossType::RED:
	{
		Renderer_->ChangeFrameAnimation("Red_Transform");
	}
	break;

	default:
		break;
	}

}

void Boss::RegenStart()
{
	switch (CurType_)
	{
	case BossType::NORMAL:
	{
		Random_ = GameEngineRandom::MainRandom.RandomInt(0, 0);
		switch (Random_)
		{
		case 0:
		{
			SetBossType(BossType::BLUE);
			Renderer_->ChangeFrameAnimation("Blue_Regen");
		}
		break;
		case 1:
		{
			SetBossType(BossType::RED);
			Renderer_->ChangeFrameAnimation("Red_Regen");
		}
		break;
		}
	}
	break;
	case BossType::BLUE:
	{
		SetBossType(BossType::NORMAL);
		BlueAttackACollision_->Off();
		Renderer_->ChangeFrameAnimation("Regen");
	}
	break;
	case BossType::RED:
	{
		SetBossType(BossType::NORMAL);
		RedAttackACollision_->Off();
		RedAttackBCollision_->Off();
		Renderer_->ChangeFrameAnimation("Regen");
	}
	break;
	default:
		break;
	}

}


void Boss::AttackAStart()
{
	IsAttack = true;
	GameEngineSound::SoundPlayOneShot("BossAttack1.mp3");

	CurDirCheck(GetPlayerPosition().x, GetPosition(), 90.f);
	SetBossSkill(BossAttackType::Att_A);

	if (CurDir_ == ACTORDIR::LEFT)
	{
		AttackACollision_->GetTransform().SetWorldPosition({ GetPosition().x - 200.f,  GetPosition().y - 30.f });
	}
	else if (CurDir_ == ACTORDIR::RIGHT)
	{
		AttackACollision_->GetTransform().SetWorldPosition({ GetPosition().x + 200.f,  GetPosition().y - 30.f });

	}

	Renderer_->ChangeFrameAnimation("AttackA");
}

void Boss::AttackBStart()
{
	IsAttack = true;
	GameEngineSound::SoundPlayOneShot("BossAttack2.mp3");

	CurDirCheck(GetPlayerPosition().x, GetPosition(), 90.f);
	SetBossSkill(BossAttackType::Att_B);

	if (CurDir_ == ACTORDIR::LEFT)
	{
		AttackBCollision_->GetTransform().SetWorldPosition({ GetPosition().x - 200.f,  GetPosition().y - 30.f });

	}
	else if (CurDir_ == ACTORDIR::RIGHT)
	{
		AttackBCollision_->GetTransform().SetWorldPosition({ GetPosition().x + 200.f,  GetPosition().y - 30.f });
	}

	Renderer_->ChangeFrameAnimation("AttackB");
}

void Boss::AttackCStart()
{
	IsAttack = true;
}

void Boss::BlueAttackStart()
{
	Player::MainPlayer_->IsChase_ = true;
	IsChase_ = true;
	IsAttack = true;
	Renderer_->ChangeFrameAnimation("Blue_Attack");

	SetBossSkill(BossAttackType::BlueAtt_A);
	BlueAttackACollision_->On();
}

void Boss::RedAttackAStart()
{
	GameEngineSound::SoundPlayOneShot("RedAttack1.mp3");
	IsAttack = true;
	SetBossSkill(BossAttackType::RedAtt_A);
	RedAttackACollision_->On();
	if (CurDir_ == ACTORDIR::LEFT)
	{
		RedAttackACollision_->GetTransform().SetWorldPosition({ GetPosition().x - 200.f,  GetPosition().y - 30.f });

	}
	else if (CurDir_ == ACTORDIR::RIGHT)
	{
		RedAttackACollision_->GetTransform().SetWorldPosition({ GetPosition().x + 200.f,  GetPosition().y - 30.f });
	}

	Renderer_->ChangeFrameAnimation("Red_AttackA");
}

void Boss::RedAttackBStart()
{
	GameEngineSound::SoundPlayOneShot("RedAttack2.mp3");
	IsAttack = true;
	SetBossSkill(BossAttackType::RedAtt_B);
	RedAttackBCollision_->On();
	if (CurDir_ == ACTORDIR::LEFT)
	{
		RedAttackBCollision_->GetTransform().SetWorldPosition({ GetPosition().x - 200.f,  GetPosition().y - 30.f });

	}
	else if (CurDir_ == ACTORDIR::RIGHT)
	{
		RedAttackBCollision_->GetTransform().SetWorldPosition({ GetPosition().x + 200.f,  GetPosition().y - 30.f });
	}
	Renderer_->ChangeFrameAnimation("Red_AttackB");
}

void Boss::RedTeleportStart()
{
	GameEngineSound::SoundPlayOneShot("RedSkill1.mp3");
	Renderer_->ChangeFrameAnimation("Red_Tel");
}

void Boss::RedTeleportRegenStart()
{
	Renderer_->On();
	Collision_->On();
	GetTransform().SetLocalPosition(GetPlayerPosition());
	Renderer_->ChangeFrameAnimation("Red_TelRegen");
}

void Boss::IdleUpdate()
{
	if (CurType_ == BossType::BLUE)
	{
		if (GetAccTime() > 1.f)
		{
			ChangeState(BossState::BLUE_Attack);
			return;
		}
	}
	else
	{
		Attack();

		if (IdleTime_ < GetAccTime())
		{
			ReSetAccTime();
			ChangeState(BossState::Move);
			return;
		}
	}
}

void Boss::MoveUpdate()
{
	Attack();
	TypeChangeTime_ += GameEngineTime::GetDeltaTime();
	if (MoveTime_ < GetAccTime())
	{
		ReSetAccTime();
		ChangeState(BossState::Idle);
		return;
	}

	CurDirCheck(GetPlayerPosition().x, GetPosition(), 90.f);
}

void Boss::DamagedUpdate()
{
	// 플레이어가 몬스터 왼쪽에 있다
	if (PlayerPos_.x < MonsterPos_.x)
	{
		MoveDir_ = { 18.f, 0.f };
	}
	else if (PlayerPos_.x > MonsterPos_.x)
	{
		// 몬스터 오른쪽에 있다
		MoveDir_ = { -18.f, 0.f };
	}

	GetTransform().SetLocalMove({ MoveDir_ * GameEngineTime::GetDeltaTime() });

	Hit();
}

void Boss::DieUpdate()
{
}

void Boss::TransformUpdate()
{

}

void Boss::RegenUpdate()
{
}

void Boss::AttackAUpdate()
{
}

void Boss::AttackBUpdate()
{
}

void Boss::AttackCUpdate()
{
}


void Boss::BlueAttackUpdate()
{
	if (ChaseTime_ > 7.f)
	{
		IsAttack = false;
		Player::MainPlayer_->IsChase_ = false;

		SetBossSkill(BossAttackType::MAX);
		ChangeState(BossState::Idle);
		return;
	}
	ChaseTime_ += GameEngineTime::GetDeltaTime();

	if (GetPlayerPosition().x < GetPosition().x)
	{
		CurDir_ = ACTORDIR::LEFT;
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * BlueSpeed_ * GameEngineTime::GetDeltaTime());
	}	//오른쪽에 있다 -> 오른쪽
	else if (GetPlayerPosition().x > GetPosition().x)
	{
		CurDir_ = ACTORDIR::RIGHT;
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * BlueSpeed_ * GameEngineTime::GetDeltaTime());
	}
}

void Boss::RedAttackAUpdate()
{
}

void Boss::RedAttackBUpdate()
{
}

void Boss::RedTeleportUpdate()
{
}

void Boss::RedTeleportRegenUpdate()
{

}

void Boss::BindBossDieEnd(const FrameAnimation_DESC& _Info)
{
	Death();
}

void Boss::BindBossAttackStart(const FrameAnimation_DESC& _Info)
{
	
}

void Boss::BindBossAttackFrame(const FrameAnimation_DESC& _Info)
{
	switch (CurBossSkill_)
	{
	case BossAttackType::Att_A:
	{
		if (5 == _Info.CurFrame)
		{
			AttackACollision_->On();
		}
	}
	break;
	case BossAttackType::Att_B:
	{
		if (7 == _Info.CurFrame)
		{
			AttackBCollision_->On();
		}
	}
	break;
	case BossAttackType::BlueAtt_A:
	{
		BlueAttackACollision_->On();
	}
	break;
	case BossAttackType::RedAtt_A:
	{
		if (3 == _Info.CurFrame)
		{
			RedAttackACollision_->On();
		}
	}
	break;
	case BossAttackType::RedAtt_B:
	{
		if (1 == _Info.CurFrame)
		{
			RedAttackBCollision_->On();
		}
	}
	break;
	case BossAttackType::Hat:
		break;
	default:
		break;
	}
}

void Boss::BindBossAttackEnd(const FrameAnimation_DESC& _Info)
{
	IsAttackEnd = true;

	switch (CurBossSkill_)
	{
	case BossAttackType::Att_A: 
	{
		AttackACollision_->Off();
	}
		break;
	case BossAttackType::Att_B:
	{
		AttackBCollision_->Off();
	}
		break;
	case BossAttackType::BlueAtt_A:
	{
		//BlueAttackACollision_->Off();
	}
		break;
	case BossAttackType::RedAtt_A:
	{
		RedAttackACollision_->Off();
	}
		break;
	case BossAttackType::RedAtt_B:
	{
		RedAttackBCollision_->Off();
	}
		break;
	case BossAttackType::Hat:
		break;
	default:
		break;
	}

	SetBossSkill(BossAttackType::MAX);
	ChangeState(BossState::Move);
	return;
}

void Boss::BindRedBossAttackBEnd(const FrameAnimation_DESC& _Info)
{
	//RedAttackBCollision_->Off();
	//ChangeState(BossState::Idle);
	//return;
}

void Boss::BindBossDamagedEnd(const FrameAnimation_DESC& _Info)
{
	ChangeState(BossState::Move);
	return;
}

void Boss::BindBossTransformFrame(const FrameAnimation_DESC& _Info)
{
	if (1 == _Info.CurFrame)
	{
		//GameEngineSound::SoundPlayOneShot("BossTransForm.mp3");
	}
}

void Boss::BindBossTransformEnd(const FrameAnimation_DESC& _Info)
{
	ChangeState(BossState::Regen);
	return;
}

void Boss::BindBossRegenEnd(const FrameAnimation_DESC& _Info)
{
//	GameEngineSound::SoundPlayOneShot("BossRegen.mp3");
	ChangeState(BossState::Idle);
	return;
}

void Boss::BindRedBossTelEnd(const FrameAnimation_DESC& _Info)
{
	// 텔레포트 끝나면 렌더러 off
	Renderer_->Off();
	Collision_->Off();
	IsTeleport_ = true;
}

void Boss::BindRedBossTelRegenEnd(const FrameAnimation_DESC& _Info)
{
	GameEngineSound::SoundPlayOneShot("RedSkillAfter1.mp3");
	ChangeState(BossState::RED_AttackB);
	return;
}
