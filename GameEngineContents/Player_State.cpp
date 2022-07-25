#include "PreCompile.h"
#include "Player.h"

void Player::IdleStart()
{
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
	if (true == IsMoveKey())
	{
		ChangeState(PLAYERSTATE::MOVE);
		return;
	}
}

void Player::MoveUpdate()
{
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
