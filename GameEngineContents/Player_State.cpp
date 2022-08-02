#include "PreCompile.h"
#include "Player.h"

void Player::IdleStart(const StateInfo& _Info)
{
	JumpPower_ = 0.0f;

	ReSetAccTime();
	PlayerRenderer_->GetTransform().SetLocalScale({ 80.f, 96.f, 1.f });
	PlayerRenderer_->ChangeFrameAnimation("Idle");
}

void Player::MoveStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("Move");
}

void Player::JumpStart(const StateInfo& _Info)
{
	GameEngineSound::SoundPlayOneShot("Jump.mp3");

	AddAccTime(Time_);
	JumpPower_ = float4{ 0.f, 450.f, 0.f };
	PlayerRenderer_->ChangeFrameAnimation("Jump");
}

void Player::FallStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("Fall");
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

	if (true == GameEngineInput::GetInst()->IsPress("Attack"))
	{
		StateManager.ChangeState("DefaultAtt");
		return;
	}

	// 땅이 아니다
	if (true == BottomDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })
		|| true == BottomDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })	// 투명
		|| true == BottomDownColor.CompareInt4D(float4{ 1.f, 0.f, 1.f, 1.f })	// 마젠타
		|| true == BottomDownColor.CompareInt4D(float4{ 0.f, 0.f, 1.f, 1.f }))	// 레드
	{
		StateManager.ChangeState("Fall");
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


	// 땅이 아니다
	if (true == BottomDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })
		|| true == BottomDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })	// 투명
		|| true == BottomDownColor.CompareInt4D(float4{ 1.f, 0.f, 1.f, 1.f })	// 마젠타
		|| true == BottomDownColor.CompareInt4D(float4{ 0.f, 0.f, 1.f, 1.f }))	// 레드
	{
		StateManager.ChangeState("Fall");
		return;
	}
}

void Player::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	GetTransform().SetWorldMove(GetTransform().GetUpVector() * JumpPower_ * GameEngineTime::GetDeltaTime());

	float4 Color = MapTexture_->GetPixel(static_cast<float>(GetTransform().GetWorldPosition().ix()), static_cast<float>(-GetTransform().GetWorldPosition().iy()) + 45.f);
	if (true == Color.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		StateManager.ChangeState("Idle");
		return;
	}
	
	//if (true == GameEngineInput::GetInst()->IsUp("Jump"))
	//{
	//	StateManager.ChangeState("Idle");
	//	return;

	//}


	/*if (1.f < GetAccTime())
	{
		StateManager.ChangeState("Idle");
		return;
	}*/
}

void Player::FallUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		StateManager.ChangeState("Idle");
		return;
	}
}

void Player::ProneUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsUp("Down"))
	{
		StateManager.ChangeState("Idle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Attack"))
	{
		StateManager.ChangeState("ProneStab");
		return;
	}
}

void Player::ProneStabUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsUp("Attack"))
	{
		StateManager.ChangeState("Prone");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsUp("Down"))
	{
		StateManager.ChangeState("Idle");
		return;
	}
}

void Player::LadderUpdate(float _DeltaTime, const StateInfo& _Info)
{


	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector());
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector());
	}
}

void Player::RopeUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Player::DefaultAttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsUp("Attack"))
	{
		StateManager.ChangeState("Idle");
		return;
	}
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
