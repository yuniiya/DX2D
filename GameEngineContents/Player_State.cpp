#include "PreCompile.h"
#include "Player.h"

void Player::IdleStart(const StateInfo& _Info)
{
	JumpPower_ = 0.0f;

	PlayerRenderer_->GetTransform().SetLocalScale({ 80.f, 96.f, 1.f });
	PlayerRenderer_->ChangeFrameAnimation("Idle");
}

void Player::MoveStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("Move");
}

void Player::JumpStart(const StateInfo& _Info)
{
	JumpPower_ = float4{ 0.f, 380.f, 0.f };
	PlayerRenderer_->ChangeFrameAnimation("Jump");
}

void Player::FallStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("Jump");
}

void Player::ProneStart(const StateInfo& _Info)
{
	PlayerRenderer_->GetTransform().SetLocalScale({ 90.f, 130.f, 1.f });

	PlayerRenderer_->ChangeFrameAnimation("Prone");
}

void Player::ProneStabStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("ProneStab");
}

void Player::LadderStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("Ladder");
}

void Player::RopeStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("Rope");
}

void Player::DefaultAttackStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("DefaultAtt");
}

void Player::SkillAttackStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("SkillAtt");
}

void Player::DamagedStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("SkillAtt");

}

void Player::DieStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("Die");
}

void Player::IdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		StateManager.ChangeState("Prone");
		return;
	}

	if (true == IsMoveKey())
	{
		StateManager.ChangeState("Move");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Jump"))
	{
		StateManager.ChangeState("Jump");
		return;
	}
}

void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("Down"))
	{
		StateManager.ChangeState("Prone");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Jump"))
	{
		StateManager.ChangeState("Jump");
		return;
	}

	if (false == IsMoveKey())
	{
		StateManager.ChangeState("Idle");
		return;
	}
}

void Player::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	GetTransform().SetWorldMove(GetTransform().GetUpVector() * JumpPower_ * GameEngineTime::GetDeltaTime());


	//if (_Info.StateTime >= 20.f);
	//{
	//	StateManager.ChangeState("Idle");
	//	return;
	//}

	if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		StateManager.ChangeState("Idle");
		return;
	}
}

void Player::FallUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Player::ProneUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsUp("Down"))
	{
		StateManager.ChangeState("Idle");
		return;
	}
}

void Player::ProneStabUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Player::LadderUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Player::RopeUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Player::DefaultAttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Player::SkillAttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Player::DamagedUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Player::DieUpdate(float _DeltaTime, const StateInfo& _Info)
{
}
