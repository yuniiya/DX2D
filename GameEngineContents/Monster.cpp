#include "PreCompile.h"
#include "Monster.h"
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>

Monster::Monster()
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, CurState_(MONSTERSTATE::IDLE)
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
{
}

Monster::~Monster()
{
}

void Monster::TakeDamage(int _Damage)
{
	if (HP_ <= 0)
	{
		ChangeState(MONSTERSTATE::DIE);
		return;
	}
	else
	{
		AddAccTime(GameEngineTime::GetDeltaTime());

		HP_ = HP_ - _Damage;

		if (1.5f < GetAccTime())
		{
			ChangeState(MONSTERSTATE::MOVE);
			return;
		}
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
		case MONSTERSTATE::DAMAGED:
			DamagedStart();
			break;
		case MONSTERSTATE::ATTACK:
			AttackStart();
			break;
		case MONSTERSTATE::DIE:
			DamagedStart();
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

	if (CurState_ == MONSTERSTATE::MOVE)
	{
		AddAccTime(GameEngineTime::GetDeltaTime());

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
	if (true == Collision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::SKILL, CollisionType::CT_OBB2D,
		std::bind(&Monster::MonsterCollisionCheck, this, std::placeholders::_1, std::placeholders::_2)
	))
	{
		ChangeState(MONSTERSTATE::DAMAGED);
		return;
	}
}

void Monster::IdleStart()
{
	switch (MonsterName_)
	{
	case MONSTERNAME::Rabbit:
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
	case MONSTERNAME::Freezer:
		break;
	case MONSTERNAME::Sparker:
		break;
	case MONSTERNAME::Boss:
		break;
	default:
		break;
	}

	//ReSetAccTime();
	//AddAccTime(Time_);

	Renderer_->ChangeFrameAnimation("Idle");
}

void Monster::MoveStart()
{
	switch (MonsterName_)
	{
	case MONSTERNAME::Rabbit:
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
	case MONSTERNAME::Freezer:
		break;
	case MONSTERNAME::Sparker:
		break;
	case MONSTERNAME::Boss:
		break;
	default:
		break;
	}

	//ReSetAccTime();
	//AddAccTime(Time_);

	Renderer_->ChangeFrameAnimation("Move");
}

void Monster::DamagedStart()
{
	switch (MonsterName_)
	{
	case MONSTERNAME::Rabbit:
	{
		Renderer_->GetTransform().SetLocalScale({ 65.f, 59.f });
	}
	break;
	case MONSTERNAME::BabyCactus:
	{
		Renderer_->GetTransform().SetLocalScale({ 83.f, 69.f });
	}
		break;
	case MONSTERNAME::Sand:
	{
		Renderer_->GetTransform().SetLocalScale({ 86.f, 86.f });
	}
		break;
	case MONSTERNAME::Freezer:
		break;
	case MONSTERNAME::Sparker:
		break;
	case MONSTERNAME::Boss:
		break;
	default:
		break;
	}

	Renderer_->ChangeFrameAnimation("Damaged");
}

void Monster::AttackStart()
{

}

void Monster::DieStart()
{
	switch (MonsterName_)
	{
	case MONSTERNAME::Rabbit:
	{
		Renderer_->GetTransform().SetLocalScale({ 72.f, 66.f });
	}
	break;
	case MONSTERNAME::BabyCactus:
	{
		Renderer_->GetTransform().SetLocalScale({ 87.f, 73.f });
	}
		break;
	case MONSTERNAME::Sand:
	{
		Renderer_->GetTransform().SetLocalScale({ 97.f, 99.f });
	}
		break;
	case MONSTERNAME::Freezer:
		break;
	case MONSTERNAME::Sparker:
		break;
	case MONSTERNAME::Boss:
		break;
	default:
		break;
	}

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

void Monster::DamagedUpdate()
{
	Hit();
}

void Monster::AttackUpdate()
{
}

void Monster::DieUpdate()
{
	Death();
}
