#include "PreCompile.h"
#include "Monster.h"
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "Player.h"

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
	, SparkerAtt_(nullptr)
	, FreezerAtt_(nullptr)
	, SoundPlay_(false)
	, ChaseTime_(0.0f)
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

void Monster::Start()
{

	IdleTime_ = GameEngineRandom::MainRandom.RandomInt(3, 6);
	MoveTime_ = GameEngineRandom::MainRandom.RandomInt(35, 50);

}

void Monster::Update(float _DeltaTime)
{
	SetChangeTime(IdleTime_, MoveTime_);

	MonsterStateUpdate();
	PixelCollisionMapUpdate(this, LeftRightPos_, BottomPos_);

	CollisonCheck();
	DirChange();
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

	if (CurState_ != MONSTERSTATE::CHASE)
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
	}
		break;
	case MONSTERNAME::Sparker:
	{
		Renderer_->GetTransform().SetLocalScale({ 77.f, 79.f });
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
	}
		break;
	case MONSTERNAME::Sparker:
	{
		Renderer_->GetTransform().SetLocalScale({ 80.f, 81.f });
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
		Renderer_->GetTransform().SetLocalScale({ 133.f, 143.f });
		GameEngineSound::SoundPlayOneShot("FrAttack1.mp3");
	}
	break;
	case MONSTERNAME::Sparker:
	{
		Renderer_->GetTransform().SetLocalScale({ 159.f, 147.f });
		GameEngineSound::SoundPlayOneShot("SpAttack1.mp3");
	}
	break;
	case MONSTERNAME::Boss:
	{

	}
	break;
	}

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

	Renderer_->ChangeFrameAnimation("Die");
}

void Monster::IdleUpdate()
{
	if (IdleTime_ < GetAccTime())
	{
		ReSetAccTime();
		ChangeState(MONSTERSTATE::MOVE);
		return;
	}
}

void Monster::MoveUpdate()
{
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
		MoveDir_.x = GetPosition().x + 0.7f;
	}
	else if (PlayerPos_.x > MonsterPos_.x)
	{
		// 몬스터 오른쪽에 있다
		MoveDir_.x = GetPosition().x - 0.7f;
	}

	GetTransform().SetLocalPosition({ MoveDir_.x, GetPosition().y});

	Hit();
}

void Monster::AttackUpdate()
{
}

void Monster::DieUpdate()
{
	Renderer_->AnimationBindEnd("Die", std::bind(&Monster::BindMonsterUpdate, this, std::placeholders::_1));

}

void Monster::BindMonsterUpdate(const FrameAnimation_DESC& _Info)
{
	
	Death();
}