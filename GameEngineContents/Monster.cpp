#include "PreCompile.h"
#include "Monster.h"
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "Player.h"
#include "ContentsUI.h"
#include "Item.h"
#include "Meso.h"

Monster::Monster()
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, CurState_(MONSTERSTATE::IDLE)
	, PrevState_(CurState_)
	, HP_(0)
	, Atk_(0.0f)
	, Speed_(0.0f)
	, BottomPos_(0.0f)
	, LeftRightPos_(0.0f)
	, DownPower_(0.0f)
	, Time_(0.0f)
	, MonsterDir_(ACTORDIR::MAX)
	, MonsterName_(MONSTERNAME::MAX)
	, MonsterType_(MONSTERTYPE::MAX)
	, IdleTime_(0)
	, MoveTime_(0)
	, IsHit(false)
	, DamageTime_(0.0f)
	, DirChangeTime_(0.0f)
	, MoveDir_(float4::ZERO)
	, MonsterPos_(0.0f)
	, PlayerPos_(0.0f)
	, SparkerAttEffect_(nullptr)
	, FreezerAttEffect_(nullptr)
	, SoundPlay_(false)
	, ChaseTime_(0.0f)
	, PrevPos_(0.0f)
	, IsAttack(false)
	, CanAttTime_(0.0f)
	, AttEndTime_(0.0f)
	, IsAttackEnd(false)
	, SparkerAttCol_(nullptr)
	, FreezerAttCol_(nullptr)
{
}

Monster::~Monster()
{
}

void Monster::TakeDamage(int _Damage)
{
	//if (DamageTime_ > 2.f)	// 다시 맞은지 2초 지났다
	//{
	//	SetHP(GetHP() - _Damage);

	//	DamageTime_ = 0.0f;

	//	ChangeState(MONSTERSTATE::MOVE);
	//	return;
	//}
		
	if (false == IsHit)				// IsHIt가 아니었으면 Hp깎아준다
	{
		IsHit = true;				// 충돌 On. 시간을 잰다

		HP_ = HP_ - _Damage;
	}
	else // IsHit가 true이다
	{
		return;
	}

}

void Monster::CollisionPositionUpdate()
{
	MonsterPos_ = GetPosition();

	switch (MonsterName_)
	{
	case MONSTERNAME::Freezer:
	{
		if (nullptr == FreezerAttCol_)
		{
			return;
		}

		if (CurDir_ == ACTORDIR::LEFT)
		{
			FreezerAttCol_->GetTransform().SetWorldPosition({ MonsterPos_.x - 50.f, MonsterPos_.y});
		}
		else if (CurDir_ == ACTORDIR::RIGHT)
		{
			FreezerAttCol_->GetTransform().SetWorldPosition({ MonsterPos_.x + 50.f, MonsterPos_.y});
		}

	}
	break;
	case MONSTERNAME::Sparker:
	{
		if (nullptr == SparkerAttCol_)
		{
			return;
		}

		if (CurDir_ == ACTORDIR::LEFT)
		{
			SparkerAttCol_->GetTransform().SetWorldPosition({ MonsterPos_.x - 50.f, MonsterPos_.y});
		}
		else if (CurDir_ == ACTORDIR::RIGHT)
		{
			SparkerAttCol_->GetTransform().SetWorldPosition({ MonsterPos_.x + 50.f, MonsterPos_.y});
		}
	}
	break;
	}
}

void Monster::EffectPositionUpdate()
{
	PlayerPos_ = Player::MainPlayer_->GetPosition();

	switch (MonsterName_)
	{
	case MONSTERNAME::Freezer:
	{
		if (nullptr == FreezerAttEffect_)
		{
			return;
		}

		if (CurDir_ == ACTORDIR::LEFT)
		{
			FreezerAttEffect_->GetTransform().SetWorldPosition({ PlayerPos_.x + 30.f, PlayerPos_.y });
		}
		else if (CurDir_ == ACTORDIR::RIGHT)
		{
			FreezerAttEffect_->GetTransform().SetWorldPosition({ PlayerPos_.x, PlayerPos_.y });
		}

	}
	break;
	case MONSTERNAME::Sparker:
	{
		if (nullptr == SparkerAttEffect_)
		{
			return;
		}

		if (CurDir_ == ACTORDIR::LEFT)
		{
			SparkerAttEffect_->GetTransform().SetWorldPosition({ PlayerPos_.x, PlayerPos_.y });
		}
		else if (CurDir_ == ACTORDIR::RIGHT)
		{
			SparkerAttEffect_->GetTransform().SetWorldPosition({ PlayerPos_.x, PlayerPos_.y});
		}
	}
	break;
	}
}

void Monster::Start()
{

	IdleTime_ = GameEngineRandom::MainRandom.RandomInt(3, 6);
	MoveTime_ = GameEngineRandom::MainRandom.RandomInt(35, 50);

	GetTransform().SetLocalPosition({ 0, 0, (int)ZOrder::MONSTER });
}

void Monster::Update(float _DeltaTime)
{
	SetChangeTime(IdleTime_, MoveTime_);

	MonsterStateUpdate();
	PixelCollisionMapUpdate(this, LeftRightPos_, BottomPos_);

	CollisonCheck();
	DirChange();

	if (CanAttTime_ > 3.f)
	{
		CanAttTime_ = 0.0f;
		IsAttack = false;
	}

	if (AttEndTime_ > 0.04f)
	{
		AttEndTime_ = 0.0f;
		IsAttackEnd = false;

		ChangeState(MONSTERSTATE::IDLE);
		return;
	}

	if (true == IsAttack)
	{
		CanAttTime_ += GameEngineTime::GetDeltaTime();
	}

	if (true == IsAttackEnd)
	{
		AttEndTime_ += GameEngineTime::GetDeltaTime();
	}
}

void Monster::ChangeState(MONSTERSTATE _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case MONSTERSTATE::IDLE:
			IdleStart();
			break;
		case MONSTERSTATE::MOVE:
			MoveStart();
			break;
		case MONSTERSTATE::CHASE:
			ChaseStart();
			break;
		case MONSTERSTATE::DAMAGED:
			DamagedStart();
			break;
		case MONSTERSTATE::ATTACK:
			AttackStart();
			break;
		case MONSTERSTATE::DIE:
			DieStart();
			break;
		}
	}

	CurState_ = _State;
}

void Monster::MonsterStateUpdate()
{
	switch (CurState_)
	{
	case MONSTERSTATE::IDLE:
		IdleUpdate();
		break;
	case MONSTERSTATE::MOVE:
		MoveUpdate();
		break;
	case MONSTERSTATE::CHASE:
		ChaseUpdate();
		break;
	case MONSTERSTATE::ATTACK:
		AttackUpdate();
		break;
	case MONSTERSTATE::DAMAGED:
		DamagedUpdate();
		break;
	case MONSTERSTATE::DIE:
		DieUpdate();
		break;
	}
}

void Monster::Hit()
{
	TakeDamage(50);

}

void Monster::DirChange()
{
	DirCheck(Renderer_, CurDir_);

	if (CurState_ != MONSTERSTATE::CHASE
		&& CurState_ != MONSTERSTATE::ATTACK)
	{
		if (50.f < GetAccTime())
		{
			if (CurDir_ == ACTORDIR::LEFT)
			{
				CurDir_ = ACTORDIR::RIGHT;
			}
			else if (CurDir_ == ACTORDIR::RIGHT)
			{
				CurDir_ = ACTORDIR::LEFT;
			}

			ReSetAccTime();
		}
	}

	if (CurState_ == MONSTERSTATE::MOVE
		|| CurState_ == MONSTERSTATE::CHASE)
	{
		AddAccTime(DirChangeTime_);

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

void Monster::Attack()
{
	if (true == IsAttack)
	{
		return;
	}

	if (MonsterType_ == MONSTERTYPE::ATTACK)
	{
		PlayerPos_ = Player::MainPlayer_->GetPosition();
		MonsterPos_ = GetPosition();

		if (100.f >= abs(MonsterPos_.x - PlayerPos_.x))
		{
			ChangeState(MONSTERSTATE::ATTACK);
			return;
		}
	}
}

bool Monster::MonsterCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

void Monster::CollisonCheck()
{
	if (true == IsDie())
	{
		ChangeState(MONSTERSTATE::DIE);
		return;
	}

	if (true == IsHit)									// 충돌 true이면 IsHIt -> On
	{
		Collision_->Off();
		DamageTime_ += GameEngineTime::GetDeltaTime();	// 시간을 잰다

		if (1.8f < DamageTime_)							// 2초가 지났으면 다시 IsHit -> Off
		{
			IsHit = false;
			DamageTime_ = 0.0f;							// 시간 리셋
						
			ChangeState(MONSTERSTATE::CHASE);			// 상태 체인지
			return;
		}
	}

	if (true == Collision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::SKILL, CollisionType::CT_OBB2D,
		std::bind(&Monster::MonsterCollisionCheck, this, std::placeholders::_1, std::placeholders::_2)
	))
	{
		ChangeState(MONSTERSTATE::DAMAGED);
		return;
	}


	// 몬스터 스킬 - 스파커, 프리저
	if (MONSTERSTATE::ATTACK == CurState_
		&& MONSTERTYPE::ATTACK == MonsterType_)
	{
		CollisionPositionUpdate();
		EffectPositionUpdate();

		if (MONSTERNAME::Freezer == MonsterName_)
		{
			if (true == FreezerAttCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::PLAYER, CollisionType::CT_OBB2D,
				std::bind(&Monster::MonsterCollisionCheck, this, std::placeholders::_1, std::placeholders::_2)
			))
			{
				FreezerAttEffect_->On();
			}

		}
		if (MONSTERNAME::Sparker == MonsterName_)
		{

			if (true == SparkerAttCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::PLAYER, CollisionType::CT_OBB2D,
				std::bind(&Monster::MonsterCollisionCheck, this, std::placeholders::_1, std::placeholders::_2)
			))
			{
				SparkerAttEffect_->On();
			}
		}
	}
	
}

bool Monster::IsDie()
{
	if (GetHP() <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Monster::IdleStart()
{
	PrevPos_ = GetPosition();

	switch (MonsterName_)
	{
	case MONSTERNAME::WhiteRabbit:
	{
		Renderer_->GetTransform().SetLocalScale({ 60.f, 58.f });
	}
		break;
	case MONSTERNAME::BrownRabbit:
	{
		Renderer_->GetTransform().SetLocalScale({ 60.f, 58.f });
	}
		break;
	case MONSTERNAME::BabyCactus:
	{
		Renderer_->GetTransform().SetLocalScale({ 54.f, 63.f });
	}
		break;
	case MONSTERNAME::Sand:
	{
		Renderer_->GetTransform().SetLocalScale({ 107.f, 81.f });
	}
		break;
	case MONSTERNAME::Scorpion:
	{
		Renderer_->GetTransform().SetLocalScale({ 75.f, 59.f });
	}
	break;
	case MONSTERNAME::Freezer:
	{
		Renderer_->GetTransform().SetLocalScale({ 77.f, 82.f });
		Renderer_->GetTransform().SetWorldPosition({ GetPosition().x, PrevPos_.y });
	}
		break;
	case MONSTERNAME::Sparker:
	{
		Renderer_->GetTransform().SetLocalScale({ 77.f, 79.f });
		Renderer_->GetTransform().SetWorldPosition({ GetPosition().x, PrevPos_.y });
	}
		break;
	case MONSTERNAME::Boss:
		break;
	default:
		break;
	}

	Renderer_->ChangeFrameAnimation("Idle");
}

void Monster::MoveStart()
{
	PrevPos_ = GetPosition();

	switch (MonsterName_)
	{
	case MONSTERNAME::WhiteRabbit:
	{
		Renderer_->GetTransform().SetLocalScale({ 67.f, 68.f });
	}
		break;
	case MONSTERNAME::BrownRabbit:
	{
		Renderer_->GetTransform().SetLocalScale({ 67.f, 68.f });
	}
	break;
	case MONSTERNAME::BabyCactus:
	{
		Renderer_->GetTransform().SetLocalScale({ 54.f, 67.f });
	}
		break;
	case MONSTERNAME::Sand:
	{
		Renderer_->GetTransform().SetLocalScale({ 108.f, 48.f });
	}
		break;
	case MONSTERNAME::Scorpion:
	{
		Renderer_->GetTransform().SetLocalScale({ 79.f, 61.f });
	}
	break;
	case MONSTERNAME::Freezer:
	{
		Renderer_->GetTransform().SetLocalScale({ 80.f, 82.f });
		Renderer_->GetTransform().SetWorldPosition({ GetPosition().x, PrevPos_.y});
	}
		break;
	case MONSTERNAME::Sparker:
	{
		Renderer_->GetTransform().SetLocalScale({ 80.f, 81.f });
		Renderer_->GetTransform().SetWorldPosition({ GetPosition().x, PrevPos_.y});
	}
		break;
	case MONSTERNAME::Boss:
		break;
	default:
		break;
	}

	Collision_->On();

	Renderer_->ChangeFrameAnimation("Move");
}

void Monster::ChaseStart()
{
	MoveStart();
}

void Monster::DamagedStart()
{
	switch (MonsterName_)
	{
	case MONSTERNAME::WhiteRabbit:
	{
		Renderer_->GetTransform().SetLocalScale({ 65.f, 59.f });
		GameEngineSound::SoundPlayOneShot("R1Damage.mp3");
	}
		break;
	case MONSTERNAME::BrownRabbit:
	{
		Renderer_->GetTransform().SetLocalScale({ 65.f, 59.f });
		GameEngineSound::SoundPlayOneShot("R2Damage.mp3");
	}
	break;
	case MONSTERNAME::BabyCactus:
	{
		Renderer_->GetTransform().SetLocalScale({ 83.f, 69.f });
		GameEngineSound::SoundPlayOneShot("CaDamage.mp3");
	}
		break;
	case MONSTERNAME::Sand:
	{
		Renderer_->GetTransform().SetLocalScale({ 86.f, 86.f });
		GameEngineSound::SoundPlayOneShot("SaDamage.mp3");
	}
		break;
	case MONSTERNAME::Scorpion:
	{
		Renderer_->GetTransform().SetLocalScale({ 101.f, 57.f });
		GameEngineSound::SoundPlayOneShot("SaDamage.mp3");
	}
	break;
	case MONSTERNAME::Freezer:
	{
		Renderer_->GetTransform().SetLocalScale({ 73.f, 92.f });
		GameEngineSound::SoundPlayOneShot("FrDamage.mp3");
	}
		break;
	case MONSTERNAME::Sparker:
	{
		Renderer_->GetTransform().SetLocalScale({ 77.f, 73.f });
		GameEngineSound::SoundPlayOneShot("SpDamage.mp3");
	}
		break;
	case MONSTERNAME::Boss:
		break;
	default:
		break;
	}

	MoveDir_ = GetPosition();
	PlayerPos_ = Player::MainPlayer_->GetPosition();
	MonsterPos_ = GetPosition();

	Renderer_->ChangeFrameAnimation("Damaged");

}

void Monster::AttackStart()
{
	switch (MonsterName_)
	{
	case MONSTERNAME::Freezer:
	{
		Renderer_->GetTransform().SetLocalScale({ 133.f, 143.f});
		Renderer_->GetTransform().SetWorldPosition({ GetPosition().x, GetPosition().y + 27.f});
		GameEngineSound::SoundPlayOneShot("FrAttack1.mp3");

		FreezerAttCol_->On();
	}
	break;
	case MONSTERNAME::Sparker:
	{
		Renderer_->GetTransform().SetLocalScale({ 159.f, 147.f });
		Renderer_->GetTransform().SetWorldPosition({ GetPosition().x, GetPosition().y + 20.f});
		GameEngineSound::SoundPlayOneShot("SpAttack1.mp3");

		SparkerAttCol_->On();
	}
	break;
	case MONSTERNAME::Boss:
	{

	}
	break;
	}

	Renderer_->AnimationBindStart("Attack", std::bind(&Monster::BindAttackStartCheck, this, std::placeholders::_1));
	Renderer_->AnimationBindEnd("Attack", std::bind(&Monster::BindAttackEndCheck, this, std::placeholders::_1));



	Renderer_->ChangeFrameAnimation("Attack");
}

void Monster::DieStart()
{
	switch (MonsterName_)
	{
	case MONSTERNAME::WhiteRabbit:
	{
		Renderer_->GetTransform().SetLocalScale({ 72.f, 66.f });
		GameEngineSound::SoundPlayOneShot("R1Die.mp3");
	}
	break;
	case MONSTERNAME::BrownRabbit:
	{
		Renderer_->GetTransform().SetLocalScale({ 72.f, 66.f });
		GameEngineSound::SoundPlayOneShot("R2Die.mp3");
	}
	break;
	case MONSTERNAME::BabyCactus:
	{
		Renderer_->GetTransform().SetLocalScale({ 87.f, 73.f });
		GameEngineSound::SoundPlayOneShot("CaDie.mp3");
	}
		break;
	case MONSTERNAME::Sand:
	{
		Renderer_->GetTransform().SetLocalScale({ 97.f, 99.f });
		Renderer_->GetTransform().SetWorldPosition({ GetPosition().x, GetPosition().y + 10.f });
		GameEngineSound::SoundPlayOneShot("SaDie.mp3");
	}
		break;
	case MONSTERNAME::Scorpion:
	{
		Renderer_->GetTransform().SetLocalScale({ 109.f, 59.f });
		GameEngineSound::SoundPlayOneShot("ScDie.mp3");
	}
	break;
	case MONSTERNAME::Freezer:
	{
		Renderer_->GetTransform().SetLocalScale({ 116.f, 107.f });
		GameEngineSound::SoundPlayOneShot("FrDie.mp3");
	}
		break;
	case MONSTERNAME::Sparker:
	{
		Renderer_->GetTransform().SetLocalScale({ 139.f, 132.f });
		GameEngineSound::SoundPlayOneShot("SpDie.mp3");

	}
		break;
	case MONSTERNAME::Boss:
		break;
	default:
		break;
	}

	AddAccTime(Time_);

	Collision_->Off();

	Player::MainPlayer_->AddExp(1.f);
	ContentsUI::MainUI->ExpBarUpdate(Player::MainPlayer_->GetExp(), 100.f);

	Renderer_->ChangeFrameAnimation("Die");
}

void Monster::IdleUpdate()
{
	Attack();

	if (IdleTime_ < GetAccTime())
	{
		ReSetAccTime();
		ChangeState(MONSTERSTATE::MOVE);
		return;
	}
}

void Monster::MoveUpdate()
{
	Attack();

	if (MoveTime_ < GetAccTime())
	{
		ReSetAccTime();
		ChangeState(MONSTERSTATE::IDLE);
		return;
	}  

	DirChange();
}

void Monster::ChaseUpdate()
{
	ChaseTime_ += GameEngineTime::GetDeltaTime();

	PlayerPos_ = Player::MainPlayer_->GetPosition();
	MonsterPos_ = GetPosition();

	if (PlayerPos_.x < MonsterPos_.x)	// 플레이어가 왼쪽에 있다
	{
		CurDir_ = ACTORDIR::LEFT;
	}
	else if (PlayerPos_.x > MonsterPos_.x)
	{
		CurDir_ = ACTORDIR::RIGHT;
	}

	if (7.f < ChaseTime_)
	{
		ChaseTime_ = 0.0f;
		ChangeState(MONSTERSTATE::MOVE);
		return;
	}
}

void Monster::DamagedUpdate()
{
	// 플레이어가 몬스터 왼쪽에 있다
	if (PlayerPos_.x < MonsterPos_.x)
	{
		MoveDir_.x = GetPosition().x + 0.5f;
	}
	else if (PlayerPos_.x > MonsterPos_.x)
	{
		// 몬스터 오른쪽에 있다
		MoveDir_.x = GetPosition().x - 0.5f;
	}

	GetTransform().SetLocalPosition({ MoveDir_.x, GetPosition().y });

	Hit();
}

void Monster::AttackUpdate()
{
	PlayerPos_ = Player::MainPlayer_->GetPosition();
	MonsterPos_ = GetPosition();

	if (200.f < abs(MonsterPos_.x - PlayerPos_.x))
	{
		ChangeState(MONSTERSTATE::IDLE);
		return;
	}

	if (PlayerPos_.x < MonsterPos_.x)	// 플레이어가 왼쪽에 있다
	{
		CurDir_ = ACTORDIR::LEFT;
	}
	else if (PlayerPos_.x > MonsterPos_.x)
	{
		CurDir_ = ACTORDIR::RIGHT;
	}

	IsAttack = true;
}

void Monster::DieUpdate()
{
	Renderer_->AnimationBindEnd("Die", std::bind(&Monster::BindMonsterDeathCheck, this, std::placeholders::_1));
}

void Monster::BindMonsterDeathCheck(const FrameAnimation_DESC& _Info)
{
	Item* ItemActor = GetLevel()->CreateActor<Item>(GAMEOBJGROUP::OBJ);
	ItemActor->MonsterName_ = GetMonsterName();
	ItemActor->GetTransform().SetLocalPosition({ GetPosition().x - 12.f, GetPosition().y - 14.f});

	Meso* MesoActor = GetLevel()->CreateActor<Meso>(GAMEOBJGROUP::OBJ);
	MesoActor->GetTransform().SetLocalPosition({ GetPosition().x + 12.f, GetPosition().y - 14.f });

	Death();
}

void Monster::BindAttackStartCheck(const FrameAnimation_DESC& _Info)
{
	switch (MonsterName_)
	{
	case MONSTERNAME::Freezer:
	{
		FreezerAttCol_->Off();
	}
	break;
	case MONSTERNAME::Sparker:
	{
		SparkerAttCol_->Off();
	}
	break;
	}
}

void Monster::BindAttackEndCheck(const FrameAnimation_DESC& _Info)
{
	IsAttackEnd = true;
}

