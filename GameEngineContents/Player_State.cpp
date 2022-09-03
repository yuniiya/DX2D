#include "PreCompile.h"
#include "Player.h"

void Player::IdleStart(const StateInfo& _Info)
{
	PlayerCollision_->On();

	MoveDir_ = 0.0f;
	JumpPower_ = 0.0f;
	Speed_ = 200.f;
	ReSetAccTime();
	//PlayerRenderer_->GetTransform().SetLocalScale({ 80.f, 96.f});
	PlayerRenderer_->GetTransform().SetLocalScale({ 66.f, 69.f});
	PlayerRenderer_->ChangeFrameAnimation("Idle");
}

void Player::MoveStart(const StateInfo& _Info)
{
	PlayerRenderer_->GetTransform().SetLocalScale({ 66.f, 70.f});
	PlayerRenderer_->ChangeFrameAnimation("Move");
}

void Player::JumpStart(const StateInfo& _Info)
{
	if (false == IsUsePaSkill)
	{
		GameEngineSound::SoundPlayOneShot("Jump.mp3");
	}

	PrevPosition_ = GetPosition();
	PrevDir_ = CurDir_;

	AddAccTime(Time_);
	JumpPower_ = float4{ 0.f, 230.f, 0.f };

	PlayerRenderer_->GetTransform().SetLocalScale({ 66.f, 69.f });
	PlayerRenderer_->ChangeFrameAnimation("Jump");
}

void Player::FallStart(const StateInfo& _Info)
{
	PlayerRenderer_->GetTransform().SetLocalScale({ 66.f, 69.f });
	PlayerRenderer_->ChangeFrameAnimation("Fall");
}

void Player::ProneStart(const StateInfo& _Info)
{
	//PlayerRenderer_->GetTransform().SetLocalScale({ 90.f, 130.f});
	PlayerRenderer_->GetTransform().SetLocalScale({ 87.f, 130.f});
	PlayerRenderer_->ChangeFrameAnimation("Prone");
}

void Player::ProneStabStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("ProneStab");
}

void Player::LadderStart(const StateInfo& _Info)
{
	//PlayerRenderer_->GetTransform().SetLocalScale({ 85.f, 97.f});
	PlayerRenderer_->GetTransform().SetLocalScale({ 69.f, 74.f });
	PlayerRenderer_->ChangeFrameAnimation("LadderA");
}

void Player::RopeStart(const StateInfo& _Info)
{
	PlayerRenderer_->GetTransform().SetLocalScale({ 66.f, 78.f});
	PlayerRenderer_->ChangeFrameAnimation("RopeA");
}

void Player::DefaultAttackStart(const StateInfo& _Info)
{
	//PlayerRenderer_->GetTransform().SetLocalScale({ 107.f, 101.f });
	PlayerRenderer_->GetTransform().SetLocalScale({ 94.f, 75.f });
	PlayerRenderer_->ChangeFrameAnimation("DefaultAtt");
}

void Player::SkillAttackStart(const StateInfo& _Info)
{
	PrevPosition_ = GetPosition();
	PrevDir_ = CurDir_;

	//PlayerRenderer_->GetTransform().SetLocalScale({ 92.f, 102.f });
	PlayerRenderer_->GetTransform().SetLocalScale({ 79.f, 76.f });
	PlayerRenderer_->ChangeFrameAnimation("SkillAtt");
}

void Player::DoubleJumpStart(const StateInfo& _Info)
{
	JumpPower_ = float4{ 0.f, 500.f, 0.f };
	Speed_ = 350.f;

	AddAccTime(DoubleJumpTime_);
	ChoA_Renderer_->On();

	if (CurDir_ == ACTORDIR::RIGHT)
	{
		ChoA_Renderer_->GetTransform().PixLocalNegativeX();
		ChoA_Renderer_->GetTransform().SetWorldPosition({GetPosition().x - 160.f, GetPosition().y - 60.f, (int)ZOrder::SKILLBACK });
	}
	else
	{
		ChoA_Renderer_->GetTransform().PixLocalPositiveX();
		ChoA_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x + 160.f, GetPosition().y - 60.f, (int)ZOrder::SKILLBACK });
	}

	PlayerRenderer_->GetTransform().SetLocalScale({ 66.f, 69.f });
	GameEngineSound::SoundPlayOneShot("Cho.mp3");
	PlayerRenderer_->ChangeFrameAnimation("Jump");
}

void Player::DamagedStart(const StateInfo& _Info)
{
	MoveDir_ = float4{ 0.f, 170.f, 0.f };

	PlayerRenderer_->GetTransform().SetLocalScale({ 66.f, 71.f });
	PlayerRenderer_->ChangeFrameAnimation("Damaged");
}

void Player::DieStart(const StateInfo& _Info)
{
	PlayerRenderer_->GetTransform().SetLocalScale({ 66.f, 69.f});
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

	if (true == IsSkillKey())
	{
		UseSkill();
	}

	/*if (true == GameEngineInput::GetInst()->IsPress("DoubleJump"))
	{
		StateManager.ChangeState("DoubleJump");
	}*/

	// ¶¥ÀÌ ¾Æ´Ï´Ù
	if (true == BottomDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })
		|| true == BottomDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })	// Åõ¸í
		|| true == BottomDownColor.CompareInt4D(float4{ 1.f, 0.f, 1.f, 1.f })	// ¸¶Á¨Å¸
		|| true == BottomDownColor.CompareInt4D(float4{ 0.f, 0.f, 1.f, 1.f }))	// ·¹µå
	{
		StateManager.ChangeState("Fall");
		return;
	}


	if (CurSkill_ == PLAYERSKILL::SKILL_SIN)
	{
		SkillPositionUpdate(CurSkill_);

		SinStart_Renderer_->AnimationBindEnd("Sin_Start", std::bind(&Player::SkillEnd, this, std::placeholders::_1));
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

	if (true == IsSkillKey())
	{
		UseSkill();
	}

	/*if (true == GameEngineInput::GetInst()->IsPress("DoubleJump"))
	{
		StateManager.ChangeState("DoubleJump");
	}*/

	// ¶¥ÀÌ ¾Æ´Ï´Ù
	if (true == BottomDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })
		|| true == BottomDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })	// Åõ¸í
		|| true == BottomDownColor.CompareInt4D(float4{ 1.f, 0.f, 1.f, 1.f })	// ¸¶Á¨Å¸
		|| true == BottomDownColor.CompareInt4D(float4{ 0.f, 0.f, 1.f, 1.f }))	// ·¹µå
	{
		StateManager.ChangeState("Fall");
		return;
	}

	if (PLAYERSKILL::SKILL_PA == CurSkill_)
	{
		SkillPositionUpdate(CurSkill_);

		PaA_Renderer_->AnimationBindEnd("Pa_A", std::bind(&Player::SkillEnd, this, std::placeholders::_1));
	}
}

void Player::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (0.3f < _Info.StateTime)
	{
		JumpPower_ -= float4{0.f, 3.f, 0.f} * GameEngineTime::GetDeltaTime() * 630.f;

		float4 Color = MapTexture_->GetPixelToFloat4((GetTransform().GetWorldPosition().ix()), (-GetTransform().GetWorldPosition().iy()) + 34);	// 34
		if (true == Color.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })
			|| true == Color.CompareInt4D(float4{ 0.f, 1.f, 0.f, 1.f })
			|| true == Color.CompareInt4D(float4{ 1.f, 0.f, 0.f, 1.f }))
		{
			StateManager.ChangeState("Idle");
			return;
		}
	}

	GetTransform().SetWorldMove(GetTransform().GetUpVector() * JumpPower_ * _DeltaTime);

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

	

	if (true == IsSkillKey())
	{
		UseSkill();
	}



	if (PLAYERSKILL::SKILL_PA == CurSkill_)
	{
		SkillPositionUpdate(CurSkill_);

		PaA_Renderer_->AnimationBindEnd("Pa_A", std::bind(&Player::SkillEnd, this, std::placeholders::_1));
	}

}

void Player::FallUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == IsSkillKey())
	{
		UseSkill();
	}

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
	if (true == GameEngineInput::GetInst()->IsUp("MoveDown"))
	{
		StateManager.ChangeState("Idle");
		return;
	}

	if (true == GameEngineInput::GetInst()->IsUp("Attack"))
	{
		StateManager.ChangeState("Prone");
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

	
	switch (CurSkill_)
	{
	case PLAYERSKILL::SKILL_IN:
	{
		InA_Renderer_->AnimationBindEnd("In_A", std::bind(&Player::SkillEnd, this, std::placeholders::_1));
	}
		break;
	case PLAYERSKILL::SKILL_PA:
	{
		PaA_Renderer_->AnimationBindEnd("Pa_A", std::bind(&Player::SkillEnd, this, std::placeholders::_1));
	}
		break;
	case PLAYERSKILL::SKILL_JI:
	{
		JiB_Renderer_->AnimationBindEnd("Ji_B", std::bind(&Player::SkillEnd, this, std::placeholders::_1));	
		//JiB_Renderer_->AnimationBindFrame("Ji_B", std::bind(&Player::SkillEnd, this, std::placeholders::_1));
	}
		break;
	case PLAYERSKILL::SKILL_SIN:
	{
		SinStart_Renderer_->AnimationBindEnd("Sin_Start", std::bind(&Player::SkillEnd, this, std::placeholders::_1));
	}
		break;
	case PLAYERSKILL::SKILL_SINA:
		break;
	case PLAYERSKILL::SKILL_SINB:
		break;
	case PLAYERSKILL::SKILL_SINC:
		break;
	case PLAYERSKILL::SKILL_SIND:
		break;
	case PLAYERSKILL::MAX:
		break;
	default:
		break;
	}
	//InB_Renderer_->AnimationBindEnd("In_B", std::bind(&Player::SkillEnd, this, std::placeholders::_1));

	//StateManager.ChangeState("Idle");
	//return;
}

void Player::DoubleJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	
	GetTransform().SetWorldMove(GetTransform().GetUpVector() * JumpPower_ * GameEngineTime::GetDeltaTime());

	if (GetAccTime() > 0.5f)	// ÇÑ¹ø ´õ ¶Ú´Ù
	{
		Speed_ = 500.f;
		JumpPower_ = { 0.f, 400.f, 0.f };
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * JumpPower_ * GameEngineTime::GetDeltaTime());
	}

	float4 Color = MapTexture_->GetPixelToFloat4((GetTransform().GetWorldPosition().ix()), (-GetTransform().GetWorldPosition().iy()) + 34);	// 34
	if (true == Color.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		StateManager.ChangeState("Idle");
		return;
	}

}

void Player::DamagedUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (0.2f < _Info.StateTime)
	{
		StateManager.ChangeState("Idle");
		return;
	}

	if (CurDir_ == ACTORDIR::LEFT)
	{
		MoveDir_.x = 110.f;
	}
	else if (CurDir_ == ACTORDIR::RIGHT)
	{
		MoveDir_.x = -110.f;
	}

	GetTransform().SetWorldMove(MoveDir_ * _DeltaTime);
}

void Player::DieUpdate(float _DeltaTime, const StateInfo& _Info)
{
}
