#include "PreCompile.h"
#include "Player.h"

void Player::IdleStart(const StateInfo& _Info)
{
	JumpPower_ = 0.0f;
	ReSetAccTime();
	PlayerRenderer_->GetTransform().SetLocalScale({ 80.f, 96.f, 1.f});
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
	PlayerRenderer_->ChangeFrameAnimation("LadderA");

	PlayerRenderer_->GetTransform().SetLocalScale({ 85.f, 97.f, 1.f });
}

void Player::RopeStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("RopeA");
}

void Player::DefaultAttackStart(const StateInfo& _Info)
{
	PlayerRenderer_->GetTransform().SetLocalScale({ 107.f, 101.f, 1.f });
	PlayerRenderer_->ChangeFrameAnimation("DefaultAtt");
}

void Player::SkillAttackStart(const StateInfo& _Info)
{
	PlayerRenderer_->GetTransform().SetLocalScale({ 92.f, 102.f, 1.f });
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
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		if (true == BottomColor.CompareInt4D(float4{ 0.0f, 1.0f, 0.0f, 1.0f }))
		{
			StateManager.ChangeState("Ladder");
			return;
		}
		else if (true == BottomColor.CompareInt4D(float4{ 1.0f, 0.0f, 0.0f, 1.0f }))
		{
			StateManager.ChangeState("Rope");
			return;
		}
		else
		{
			StateManager.ChangeState("Prone");
			return;
		}
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
	}

	UseSkill();

	// ¶¥ÀÌ ¾Æ´Ï´Ù
	if (true == BottomDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })
		|| true == BottomDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })	// Åõ¸í
		|| true == BottomDownColor.CompareInt4D(float4{ 1.f, 0.f, 1.f, 1.f })	// ¸¶Á¨Å¸
		|| true == BottomDownColor.CompareInt4D(float4{ 0.f, 0.f, 1.f, 1.f }))	// ·¹µå
	{
		StateManager.ChangeState("Fall");
		return;
	}
}

void Player::MoveUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		if (true == BottomColor.CompareInt4D(float4{ 0.0f, 1.0f, 0.0f, 1.0f }))
		{
			StateManager.ChangeState("Ladder");
			return;
		}
		else if (true == BottomColor.CompareInt4D(float4{ 1.0f, 0.0f, 0.0f, 1.0f }))
		{
			StateManager.ChangeState("Rope");
			return;
		}
		else
		{
			StateManager.ChangeState("Prone");
			return;
		}
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

	UseSkill();

	// ¶¥ÀÌ ¾Æ´Ï´Ù
	if (true == BottomDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })
		|| true == BottomDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })	// Åõ¸í
		|| true == BottomDownColor.CompareInt4D(float4{ 1.f, 0.f, 1.f, 1.f })	// ¸¶Á¨Å¸
		|| true == BottomDownColor.CompareInt4D(float4{ 0.f, 0.f, 1.f, 1.f }))	// ·¹µå
	{
		StateManager.ChangeState("Fall");
		return;
	}
}

void Player::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	GetTransform().SetWorldMove(GetTransform().GetUpVector() * JumpPower_ * GameEngineTime::GetDeltaTime());

	float4 Color = MapTexture_->GetPixelToFloat4(static_cast<float>(GetTransform().GetWorldPosition().ix()), static_cast<float>(-GetTransform().GetWorldPosition().iy()) + 45.f);
	if (true == Color.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		StateManager.ChangeState("Idle");
		return;
	}

	UseSkill();

	if (true == TopColor.CompareInt4D(float4{ 0.f, 1.f, 0.f, 1.f })				
		|| true == MiddleColor.CompareInt4D(float4{ 0.f, 1.f, 0.f, 1.f }))
	{
		if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
		{
			StateManager.ChangeState("Ladder");
			return;
		}
		else
		{
			return;
		}

	}

	if (true == TopColor.CompareInt4D(float4{ 1.f, 0.f, 0.f, 1.f })
		|| true == MiddleColor.CompareInt4D(float4{ 1.f, 0.f, 0.f, 1.f }))
	{
		if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
		{
			StateManager.ChangeState("Rope");
			return;
		}
		else
		{
			return;
		}
	}
}

void Player::FallUpdate(float _DeltaTime, const StateInfo& _Info)
{
	UseSkill();

	if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		StateManager.ChangeState("Idle");
		return;
	}
}

void Player::ProneUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsUp("MoveDown"))
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

	if (true == GameEngineInput::GetInst()->IsUp("MoveDown"))
	{
		StateManager.ChangeState("Idle");
		return;
	}
}

void Player::LadderUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsUpDownMoveKey())
	{
		PlayerRenderer_->ChangeFrameAnimation("Ladder");

	}
	else
	{
		PlayerRenderer_->ChangeFrameAnimation("LadderA");
	}

	if (true == GameEngineInput::GetInst()->IsPress("Jump")
		&& true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		GameEngineSound::SoundPlayOneShot("Jump.mp3");
		StateManager.ChangeState("Fall");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Jump")
		&& true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		GameEngineSound::SoundPlayOneShot("Jump.mp3");
		StateManager.ChangeState("Fall");
		return;
	}

	if (true == MiddleColor.CompareInt4D(float4{ 0.0f, 1.0f, 0.0f, 1.0f })
		|| true == BottomColor.CompareInt4D(float4{ 0.0f, 1.0f, 0.0f, 1.0f }))
	{
		if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
		{
			GetTransform().SetWorldMove(GetTransform().GetUpVector() * 100.f * _DeltaTime);
		}

		if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
		{
			GetTransform().SetWorldMove(GetTransform().GetDownVector() * 100.f * _DeltaTime);
		}
	}

	if (true == BottomUpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })			// ¶¥
		|| true == BottomUpColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })			// Èò»ö
		|| true == BottomUpColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }))		// Åõ¸í
	{
		StateManager.ChangeState("Idle");
		return;
	}
}

void Player::RopeUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsUpDownMoveKey())
	{
		PlayerRenderer_->ChangeFrameAnimation("Rope");

	}
	else
	{
		PlayerRenderer_->ChangeFrameAnimation("RopeA");
	}

	if (true == GameEngineInput::GetInst()->IsPress("Jump")
		&& true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		GameEngineSound::SoundPlayOneShot("Jump.mp3");
		StateManager.ChangeState("Jump");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("Jump")
		&& true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		GameEngineSound::SoundPlayOneShot("Jump.mp3");
		StateManager.ChangeState("Jump");
		return;
	}

	if (true == MiddleColor.CompareInt4D(float4{ 1.0f, 0.0f, 0.0f, 1.0f })
		|| true == BottomColor.CompareInt4D(float4{ 1.0f, 0.0f, 0.0f, 1.0f }))
	{
		if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
		{
			GetTransform().SetWorldMove(GetTransform().GetUpVector() * 100.f * _DeltaTime);
		}

		if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
		{
			GetTransform().SetWorldMove(GetTransform().GetDownVector() * 100.f * _DeltaTime);
		}
	}

	if (true == BottomUpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })			// ¶¥
		|| true == BottomUpColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })			// Èò»ö
		|| true == BottomUpColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }))		// Åõ¸í
	{
		StateManager.ChangeState("Idle");
		return;
	}


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
	SkillPositionUpdate(CurSkill_);

	InA_Renderer_->AnimationBindEnd("In_A", std::bind(&Player::SkillEnd, this, std::placeholders::_1));
	//InB_Renderer_->AnimationBindEnd("In_B", std::bind(&Player::SkillEnd, this, std::placeholders::_1));

	//StateManager.ChangeState("Idle");
	//return;


	if (true == GameEngineInput::GetInst()->IsFree("Skill_Q"))
	{
		
	}
}

void Player::DamagedUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Player::DieUpdate(float _DeltaTime, const StateInfo& _Info)
{
}
