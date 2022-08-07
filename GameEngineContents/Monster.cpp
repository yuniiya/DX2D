#include "PreCompile.h"
#include "Monster.h"
#include <GameEngineCore/GameEngineDefaultRenderer.h>

Monster::Monster()
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, CurState_(MONSTERSTATE::IDLE)
	, HP_(0)
	, Atk_(0.0f)
	, BottomPos_(0.0f)
	, LeftRightPos_(0.0f)
	, DownPower_(0.0f)
	, Time_(0.0f)
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
}

void Monster::Update(float _DeltaTime)
{
	MonsterStateUpdate();
	PixelCollisionMapUpdate(this, LeftRightPos_, BottomPos_);

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
		break;
	case MONSTERNAME::Sand:
		break;
	case MONSTERNAME::Freezer:
		break;
	case MONSTERNAME::Sparker:
		break;
	case MONSTERNAME::Boss:
		break;
	case MONSTERNAME::MAX:
		break;
	default:
		break;
	}

	ReSetAccTime();
	AddAccTime(Time_);

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
		break;
	case MONSTERNAME::Sand:
		break;
	case MONSTERNAME::Freezer:
		break;
	case MONSTERNAME::Sparker:
		break;
	case MONSTERNAME::Boss:
		break;
	case MONSTERNAME::MAX:
		break;
	default:
		break;
	}

	ReSetAccTime();
	AddAccTime(Time_);

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
		break;
	case MONSTERNAME::Sand:
		break;
	case MONSTERNAME::Freezer:
		break;
	case MONSTERNAME::Sparker:
		break;
	case MONSTERNAME::Boss:
		break;
	case MONSTERNAME::MAX:
		break;
	default:
		break;
	}
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
		break;
	case MONSTERNAME::Sand:
		break;
	case MONSTERNAME::Freezer:
		break;
	case MONSTERNAME::Sparker:
		break;
	case MONSTERNAME::Boss:
		break;
	case MONSTERNAME::MAX:
		break;
	default:
		break;
	}
}

void Monster::IdleUpdate()
{
	if (5.f < GetAccTime())
	{
		ChangeState(MONSTERSTATE::MOVE);
		return;
	}
}

void Monster::MoveUpdate()
{
	if (20.f < GetAccTime())
	{
		ChangeState(MONSTERSTATE::IDLE);
		return;
	}

	DirChange();

}

void Monster::DamagedUpdate()
{
}

void Monster::AttackUpdate()
{
}

void Monster::DieUpdate()
{
}
