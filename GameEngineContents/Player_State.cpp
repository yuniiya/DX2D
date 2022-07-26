#include "PreCompile.h"
#include "Player.h"

void Player::IdleStart()
{
	PlayerRenderer_->GetTransform().SetLocalScale({ 80.f, 96.f, 1.f });

	AnimationName_ = "Idle";
	PlayerRenderer_->ChangeFrameAnimation("Idle");
}

void Player::MoveStart()
{
	AnimationName_ = "Move";
	PlayerRenderer_->ChangeFrameAnimation("Move");
}

void Player::JumpStart()
{
}

void Player::ProneStart()
{
	PlayerRenderer_->GetTransform().SetLocalScale({ 90.f, 130.f, 1.f });

	AnimationName_ = "Prone";
	PlayerRenderer_->ChangeFrameAnimation("Prone");
}

void Player::ProneStabStart()
{
}

void Player::LadderStart()
{
}

void Player::RopeStart()
{
}

void Player::AttackStart()
{
}

void Player::DamagedStart()
{
}

void Player::DieStart()
{
}

void Player::IdleUpdate()
{
	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		ChangeState(PLAYERSTATE::PRONE);
		return;
	}

	if (true == IsMoveKey())
	{
		ChangeState(PLAYERSTATE::MOVE);
		return;
	}
}

void Player::MoveUpdate()
{
	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		ChangeState(PLAYERSTATE::PRONE);
		return;
	}

	if (false == IsMoveKey())
	{
		ChangeState(PLAYERSTATE::IDLE);
		return;
	}
}

void Player::JumpUpdate()
{
}

void Player::ProneUpdate()
{
	if (true == GameEngineInput::GetInst()->IsUp("Down"))
	{
		ChangeState(PLAYERSTATE::IDLE);
		return;
	}
}

void Player::ProneStabUpdate()
{
}

void Player::LadderUpdate()
{
}

void Player::RopeUpdate()
{
}

void Player::AttackUpdate()
{
}

void Player::DamagedUpdate()
{
}

void Player::DieUpdate()
{
}
