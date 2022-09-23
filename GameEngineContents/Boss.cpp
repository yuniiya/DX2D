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
	Renderer_->GetTransform().SetLocalScale({ 201.f, 237.f });	// Idle
	Renderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Boss_Idle", 0.12f));
	Renderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Boss_Move", 0.18f));
	Renderer_->CreateFrameAnimationFolder("AttackA", FrameAnimation_DESC("Boss_Att1", 0.1f));
	Renderer_->CreateFrameAnimationFolder("AttackB", FrameAnimation_DESC("Boss_Att2", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Transform", FrameAnimation_DESC("Boss_Transform", 0.15f));
	Renderer_->CreateFrameAnimationFolder("Regen", FrameAnimation_DESC("Boss_Regen", 0.15f));
	Renderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("Boss_Damaged", 0.2f));
	Renderer_->CreateFrameAnimationFolder("Die", FrameAnimation_DESC("Boss_Die", 0.12f));

	// Blue
	Renderer_->CreateFrameAnimationFolder("Blue_Idle", FrameAnimation_DESC("BlueBoss_Idle", 0.12f));
	Renderer_->CreateFrameAnimationFolder("Blue_Attack", FrameAnimation_DESC("BlueBoss_Att", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Blue_Transform", FrameAnimation_DESC("BlueBoss_Transform", 0.15f));
	Renderer_->CreateFrameAnimationFolder("Blue_Regen", FrameAnimation_DESC("BlueBoss_Regen", 0.15f));
	Renderer_->CreateFrameAnimationFolder("Blue_Damaged", FrameAnimation_DESC("BlueBoss_Damaged", 0.2f));
	Renderer_->CreateFrameAnimationFolder("Blue_Die", FrameAnimation_DESC("BlueBoss_Die", 0.12f));

	// Red
	Renderer_->CreateFrameAnimationFolder("Red_Idle", FrameAnimation_DESC("RedBoss_Idle", 0.12f));
	Renderer_->CreateFrameAnimationFolder("Red_Move", FrameAnimation_DESC("RedBoss_Move", 0.18f));
	Renderer_->CreateFrameAnimationFolder("Red_AttackA", FrameAnimation_DESC("RedBoss_Att1", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Red_AttackB", FrameAnimation_DESC("RedBoss_Att2", 0.1f));
	Renderer_->CreateFrameAnimationFolder("Red_Transform", FrameAnimation_DESC("RedBoss_Transform", 0.15f));
	Renderer_->CreateFrameAnimationFolder("Red_Regen", FrameAnimation_DESC("RedBoss_Regen", 0.15f));
	Renderer_->CreateFrameAnimationFolder("Red_Tel", FrameAnimation_DESC("RedBoss_Tel", 0.15f));
	Renderer_->CreateFrameAnimationFolder("Red_TelRegen", FrameAnimation_DESC("RedBoss_TelRegen", 0.15f));
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
	Renderer_->AnimationBindEnd("AttackA", std::bind(&Boss::BindBossAttackEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("AttackB", std::bind(&Boss::BindBossAttackEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Blue_Attack", std::bind(&Boss::BindBossAttackEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Red_AttackA", std::bind(&Boss::BindBossAttackEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Red_AttackB", std::bind(&Boss::BindBossAttackEnd, this, std::placeholders::_1));

	Renderer_->AnimationBindEnd("Damaged", std::bind(&Boss::BindBossDamagedEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Blue_Damaged", std::bind(&Boss::BindBossDamagedEnd, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Red_Damaged", std::bind(&Boss::BindBossDamagedEnd, this, std::placeholders::_1));

	Renderer_->ChangeFrameAnimation("Move");
	ChangeState(BossState::Move);

	SetHP(1000.f);
	SetMaxHP(HP_);
	SetSpeed(90.f);
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

	if (true == IsAttack)
	{
		CanAttTime_ += _DeltaTime;
	}

	if (true == IsAttackEnd)
	{
		AttEndTime_ += _DeltaTime;
	}

	CreateHatTime_ += _DeltaTime;
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

	if (200.f >= abs(GetPosition().x - GetPlayerPosition().x))
	{
		int Random = GameEngineRandom::MainRandom.RandomInt(1, 1);
		if (BossType::NORMAL == CurType_)
		{
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
	PrevPos_ = GetPosition();
	Renderer_->GetTransform().SetWorldPosition({ GetPosition().x, PrevPos_.y, (int)ZOrder::MONSTER});

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

	Renderer_->ScaleToTexture();
}

void Boss::MoveStart()
{
	PrevPos_ = GetPosition();
	Renderer_->GetTransform().SetWorldPosition({ GetPosition().x, PrevPos_.y, (int)ZOrder::MONSTER });

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

	Renderer_->ScaleToTexture();
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
	Renderer_->ScaleToTexture();
	Renderer_->GetTransform().SetWorldPosition({ GetPosition().x,  GetPosition().y + 10.f, (int)ZOrder::MONSTER });

//	Renderer_->GetTransform().SetLocalScale({ 248.f, 255.f });
}

void Boss::DieStart()
{
	GameEngineSound::SoundPlayOneShot("BossDie.mp3");
	Renderer_->GetTransform().SetWorldPosition({ GetPosition().x,  GetPosition().y + 30.f, (int)ZOrder::MONSTER });

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
	Renderer_->ScaleToTexture();

	Collision_->Off();
}

void Boss::TransformStart()
{
	GameEngineSound::SoundPlayOneShot("BossTransForm.mp3");
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
	Renderer_->ScaleToTexture();
}

void Boss::RegenStart()
{
	GameEngineSound::SoundPlayOneShot("BossRegen.mp3");
//	Renderer_->GetTransform().SetLocalScale({ 413.f, 299.f });
	switch (CurType_)
	{
	case BossType::NORMAL:
	{
		Renderer_->ChangeFrameAnimation("Regen");
	}
	break;
	case BossType::BLUE:
	{
		Renderer_->ChangeFrameAnimation("Blue_Regen");
	}
	break;
	case BossType::RED:
	{
		Renderer_->ChangeFrameAnimation("Red_Regen");
	}
	break;

	default:
		break;
	}
	Renderer_->ScaleToTexture();
}


void Boss::AttackAStart()
{
	IsAttack = true;
	GameEngineSound::SoundPlayOneShot("BossAttack1.mp3");
	Renderer_->GetTransform().SetLocalScale({ 357.f, 360.f });

	CurDirCheck(GetPlayerPosition().x, GetPosition(), 90.f);
	SetBossSkill(BossAttackType::Att_A);

	if (CurDir_ == ACTORDIR::LEFT)
	{
		Renderer_->GetTransform().SetWorldPosition({ GetPosition().x - 60.f,  GetPosition().y - 33.f, (int)ZOrder::MONSTER });
		AttackACollision_->GetTransform().SetWorldPosition({ GetPosition().x - 200.f,  GetPosition().y - 30.f });
	}
	else if (CurDir_ == ACTORDIR::RIGHT)
	{
		Renderer_->GetTransform().SetWorldPosition({ GetPosition().x + 60.f,  GetPosition().y - 33.f, (int)ZOrder::MONSTER });
		AttackACollision_->GetTransform().SetWorldPosition({ GetPosition().x + 200.f,  GetPosition().y - 30.f });

	}
	Renderer_->ChangeFrameAnimation("AttackA");

}

void Boss::AttackBStart()
{
	IsAttack = true;
	//GameEngineSound::SoundPlayOneShot("BossAttack2.mp3");
	Renderer_->GetTransform().SetLocalScale({ 427.f, 276.f });

	CurDirCheck(GetPlayerPosition().x, GetPosition(), 90.f);
	SetBossSkill(BossAttackType::Att_B);

	if (CurDir_ == ACTORDIR::LEFT)
	{
		Renderer_->GetTransform().SetWorldPosition({ GetPosition().x - 90.f,  GetPosition().y - 13.f, (int)ZOrder::MONSTER });
		AttackBCollision_->GetTransform().SetWorldPosition({ GetPosition().x - 200.f,  GetPosition().y - 30.f });

	}
	else if (CurDir_ == ACTORDIR::RIGHT)
	{
		Renderer_->GetTransform().SetWorldPosition({ GetPosition().x + 90.f,  GetPosition().y - 13.f, (int)ZOrder::MONSTER });
		AttackBCollision_->GetTransform().SetWorldPosition({ GetPosition().x + 200.f,  GetPosition().y - 30.f });
	}

	Renderer_->ChangeFrameAnimation("AttackB");
}

void Boss::AttackCStart()
{
	IsAttack = true;
	Renderer_->GetTransform().SetLocalScale({ 427.f, 276.f });
	Renderer_->GetTransform().SetWorldPosition({ GetPosition().x,  GetPosition().y, (int)ZOrder::MONSTER });
}

void Boss::BlueAttackStart()
{
	IsAttack = true;
	Renderer_->ChangeFrameAnimation("Blue_Attack");
	Renderer_->ScaleToTexture();
	SetBossSkill(BossAttackType::BlueAtt_A);
	BlueAttackACollision_->On();
}

void Boss::RedAttackAStart()
{
	IsAttack = true;
	Renderer_->ChangeFrameAnimation("Red_AttackA");
	Renderer_->ScaleToTexture();
	SetBossSkill(BossAttackType::RedAtt_A);
}

void Boss::RedAttackBStart()
{
	IsAttack = true;
	Renderer_->ChangeFrameAnimation("Red_AttackB");
	Renderer_->ScaleToTexture();
	SetBossSkill(BossAttackType::RedAtt_B);
}

void Boss::RedTeleportStart()
{
	Renderer_->ChangeFrameAnimation("Red_Tel");
	Renderer_->ScaleToTexture();
}

void Boss::RedTeleportRegenStart()
{
	Renderer_->ChangeFrameAnimation("Red_TelRegen");
	Renderer_->ScaleToTexture();
}

void Boss::IdleUpdate()
{
	Attack();

	if (IdleTime_ < GetAccTime())
	{
		ReSetAccTime();
		ChangeState(BossState::Move);
		return;
	}

}

void Boss::MoveUpdate()
{
	Attack();

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
		BlueAttackACollision_->Off();
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

void Boss::BindBossDamagedEnd(const FrameAnimation_DESC& _Info)
{
	ChangeState(BossState::Move);
	return;
}
