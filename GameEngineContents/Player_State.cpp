#include "PreCompile.h"
#include "Player.h"
#include "Skill.h"
#include "DamageNumber.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "Boss.h"

void Player::IdleStart(const StateInfo& _Info)
{
	PlayerCollision_->On();

	MoveDir_ = 0.0f;
	JumpPower_ = 0.0f;
	Speed_ = 200.f;
	ReSetAccTime();
	PlayerRenderer_->ChangeFrameAnimation("Idle");
}

void Player::MoveStart(const StateInfo& _Info)
{
	if (true == IsStun_)
	{
		return;
	}
	MoveDir_ = 0.0f;
	JumpPower_ = 0.0f;
	PlayerRenderer_->ChangeFrameAnimation("Move");
}

void Player::JumpStart(const StateInfo& _Info)
{
	// ���� �ƴ϶�� ������ �� ����
	if (false == BottomDownColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		return;
	}

	GameEngineSound::SoundPlayOneShot("Jump.mp3");

	PrevPosition_ = GetPosition();
	PrevDir_ = CurDir_;

	AddAccTime(Time_);
	JumpPower_ = float4{ 0.f, 230.f, 0.f };

	PlayerRenderer_->ChangeFrameAnimation("Jump");
}

void Player::FallStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("Fall");
}

void Player::ProneStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("Prone");
}

void Player::ProneStabStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("ProneStab");
}

void Player::LadderStart(const StateInfo& _Info)
{
	PlayerRenderer_->GetPixelData().MulColor = { 1.f, 1.f, 1.f };
	PlayerRenderer_->ChangeFrameAnimation("LadderA");
}

void Player::RopeStart(const StateInfo& _Info)
{
	PlayerRenderer_->GetPixelData().MulColor = { 1.f, 1.f, 1.f };
	PlayerRenderer_->ChangeFrameAnimation("RopeA");
}

void Player::DefaultAttackStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("DefaultAtt");
}

void Player::SkillAttackStart(const StateInfo& _Info)
{
	PrevPosition_ = GetPosition();
	PrevDir_ = CurDir_;

	PlayerRenderer_->ChangeFrameAnimation("SkillAtt");
}

void Player::JumpSkillAttackStart(const StateInfo& _Info)
{
	// ���� �ƴ϶�� ������ �� ����
	if (false == BottomDownColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		return;
	}

	PrevPosition_ = GetPosition();
	PrevDir_ = CurDir_;

	AddAccTime(Time_);
	JumpPower_ = float4{ 0.f, 230.f, 0.f };

	PlayerRenderer_->ChangeFrameAnimation("Jump");
}

void Player::DoubleJumpStart(const StateInfo& _Info)
{
	JumpPower_ = float4{ 0.f, 400.f, 0.f };
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

	GameEngineSound::SoundPlayOneShot("Cho.mp3");
	PlayerRenderer_->ChangeFrameAnimation("Jump");
}

void Player::DamagedStart(const StateInfo& _Info)
{
	JumpPower_ = 0.0f; 
	MoveDir_.y = 130.f;

	DamageNumber* DamageNum_ = GetLevel()->CreateActor<DamageNumber>();
	DamageNum_->SetDamageType(DamageTextureType::Player);
	int Damage_ = GameEngineRandom::MainRandom.RandomInt(5, 99);
	DamageNum_->GetTransform().SetLocalMove({ 0.f, -20.f });
	DamageNum_->SetDamage(Damage_);

	PlayerRenderer_->ChangeFrameAnimation("Damaged");
}

void Player::KnockBackStart(const StateInfo& _Info)
{
	JumpPower_ = 0.0f;
	MoveDir_.y = 130.f;

	DamageNumber* DamageNum_ = GetLevel()->CreateActor<DamageNumber>();
	DamageNum_->SetDamageType(DamageTextureType::Player);
	int Damage_ = GameEngineRandom::MainRandom.RandomInt(5, 99);
	DamageNum_->GetTransform().SetLocalMove({ 0.f, -20.f });
	DamageNum_->SetDamage(Damage_);

	PlayerRenderer_->ChangeFrameAnimation("Damaged");
}

void Player::DieStart(const StateInfo& _Info)
{
	PlayerRenderer_->ChangeFrameAnimation("Die");
}

void Player::FlyingStart(const StateInfo& _Info)
{
	PlayerCollision_->On();

	GameEngineSound::SoundPlayOneShot("Jump.mp3");
	PlayerRenderer_->ChangeFrameAnimation("Flying");
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
		if (CurLevelName_ == "AQUA")
		{
			MoveDir_ = float4{ 0.f, 200.f, 0.f };
			StateManager.ChangeState("Flying");
			return;
		}
		else
		{
			StateManager.ChangeState("Jump");
			return;
		}
	}

	//if (true == GameEngineInput::GetInst()->IsPress("Attack"))
	//{
	//	StateManager.ChangeState("DefaultAtt");
	//}

	if (true == IsSkillKey())
	{
		UseSkill();
	}

	// ���� �ƴϴ�
	if (true == BottomDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })
		|| true == BottomDownColor.CompareInt4D(float4{ 1.f, 0.f, 1.f, 1.f })	// ����Ÿ
		|| true == BottomDownColor.CompareInt4D(float4{ 0.f, 0.f, 1.f, 1.f }))	// ����
	{
		StateManager.ChangeState("Fall");
		return;
	}


	if (CurSkill_ == PLAYERSKILL::SKILL_SIN)
	{
		SkillPositionUpdate(CurSkill_);
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
	// ī�޶� �ٱ��� �̵� ���� - ����
	if (CurDir_ == ACTORDIR::LEFT)
	{
		if (true == LeftColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }))
		{
			if (true == GameEngineInput::GetInst()->IsUp("MoveLeft"))
			{
				CurDir_ = ACTORDIR::NONE;
			}
			else
			{
				CanMove = false;
			}
		}
		else
		{
			CanMove = true;
		}
	}

	// ī�޶� �ٱ��� �̵� ���� - ������
	if (CurDir_ == ACTORDIR::RIGHT)
	{
		if (true == RightColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }))
		{
			if (true == GameEngineInput::GetInst()->IsUp("MoveRight"))
			{
				CurDir_ = ACTORDIR::NONE;
			}
			else
			{
				CanMove = false;
			}
		}
		else
		{
			CanMove = true;
		}
	}
	if (true == GameEngineInput::GetInst()->IsPress("Jump"))
	{
		if (CurLevelName_ == "AQUA")
		{
			MoveDir_ = float4{ 0.f, 200.f, 0.f };
			StateManager.ChangeState("Flying");
			return;
		}
		else
		{
			StateManager.ChangeState("Jump");
			return;
		}
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

	// ���� �ƴϴ�
	if (true == BottomDownColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })
		|| true == BottomDownColor.CompareInt4D(float4{ 1.f, 0.f, 1.f, 1.f })	// ����Ÿ
		|| true == BottomDownColor.CompareInt4D(float4{ 0.f, 0.f, 1.f, 1.f }))	// ����
	{
		StateManager.ChangeState("Fall");
		return;
	}

	if (PLAYERSKILL::SKILL_PA == CurSkill_)
	{
		SkillPositionUpdate(CurSkill_);
	}
}

void Player::JumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (0.3f < _Info.StateTime  && false == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		JumpPower_ -= float4{0.f, 3.f, 0.f} * GameEngineTime::GetDeltaTime() * 630.f;

	}
	else if (0.4f < _Info.StateTime)
	{
		if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })
/*			|| true == Color.CompareInt4D(float4{ 0.f, 1.f, 0.f, 1.f })
			|| true == Color.CompareInt4D(float4{ 1.f, 0.f, 0.f, 1.f })*/)
		{
			StateManager.ChangeState("Idle");
			return;
		}
	}

	GetTransform().SetWorldMove(JumpPower_ * _DeltaTime);

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
	}

}

void Player::FallUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (CurLevelName_ == "AQUA")
	{
		MoveDir_ = float4{ 0.f, -50.f, 0.f };
		StateManager.ChangeState("Flying");
		return;
	}

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

	//if (true == GameEngineInput::GetInst()->IsPress("Attack"))
	//{
	//	StateManager.ChangeState("ProneStab");
	//	return;
	//}
}

void Player::ProneStabUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsUp("MoveDown"))
	{
		StateManager.ChangeState("Idle");
		return;
	}

	//if (true == GameEngineInput::GetInst()->IsUp("Attack"))
	//{
	//	StateManager.ChangeState("Prone");
	//	return;
	//}
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

	if (true == BottomUpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })			// ��
		|| true == BottomUpColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })			// ���
/*		|| true == BottomUpColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })*/)		// ����
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

	if (true == BottomUpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })				// ��
		|| true == BottomUpColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f }))			// ���
	{
		StateManager.ChangeState("Idle");
		return;
	}

}

void Player::DefaultAttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//if (true == GameEngineInput::GetInst()->IsUp("Attack"))
	//{
	//	StateManager.ChangeState("Idle");
	//	return;
	//}
}

void Player::SkillAttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
	SkillPositionUpdate(CurSkill_);

	if (CurSkill_ == PLAYERSKILL::SKILL_JI)
	{
		if (true == Skill_->IsEnd_)
		{
			StateManager.ChangeState("Idle");
			return;
		}
	}
	//switch (CurSkill_)
	//{
	//case PLAYERSKILL::SKILL_IN:
	//{
	//}
	//break;
	//case PLAYERSKILL::SKILL_PA:
	//{
	//}
	//break;
	//case PLAYERSKILL::SKILL_JI:
	//{
	//	if (true == Skill_->IsEnd_)
	//	{
	//		StateManager.ChangeState("Idle");
	//		return;
	//	}
	//}
	//break;
	//}

}

void Player::JumpSkillAttackUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (0.3f < _Info.StateTime && false == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		JumpPower_ -= float4{ 0.f, 3.f, 0.f } *GameEngineTime::GetDeltaTime() * 630.f;

	}
	else if (0.4f < _Info.StateTime)
	{
		if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
		{
			StateManager.ChangeState("Idle");
			return;
		}
	}

	GetTransform().SetWorldMove(JumpPower_ * _DeltaTime);


	SkillPositionUpdate(CurSkill_);

	PaA_Renderer_->AnimationBindEnd("Pa_A", std::bind(&Player::SkillEnd, this, std::placeholders::_1));

}

void Player::DoubleJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{

	GetTransform().SetWorldMove(GetTransform().GetUpVector() * JumpPower_ * GameEngineTime::GetDeltaTime());

	if (GetAccTime() > 0.5f)	// �ѹ� �� �ڴ�
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
	if (GetCurLevelName() == "AQUA")
	{
		if (0.1f < _Info.StateTime)
		{
			MoveDir_ -= float4{ 0.f, 1.f, 0.f } *2.f;
		}
		if (0.3f < _Info.StateTime)
		{
			//MoveDir_ = float4{ 0.f, -90.f, 0.f };
			MoveDir_ = 0.f;
			StateManager.ChangeState("Flying");
			return;
		}
	}
	else
	{
		if (0.3f < _Info.StateTime)
		{
			MoveDir_ -= float4{ 0.f, 1.f, 0.f } *70.f;

			if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
			{
				MoveDir_ = 0.f;
				StateManager.ChangeState("Idle");
				return;
			}
		}
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

void Player::KnockBackUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (0.3f < _Info.StateTime)
	{
		MoveDir_ -= float4{ 0.f, 1.f, 0.f } *70.f;

		if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
		{
			MoveDir_ = 0.f;
			StateManager.ChangeState("Idle");
			return;
		}
	}

	if (nullptr == dynamic_cast<GlobalLevel*>(GetLevel())->GetBoss())
	{
		return;
	}
	Boss_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetBoss();
	if (abs(GetPosition().x - Boss_->GetPosition().x) < 90.f)
	{
		return;
	}
	if (GetPosition().x < Boss_->GetPosition().x)
	{
		MoveDir_.x = -1000.f;
	}	
	else if (GetPosition().x > Boss_->GetPosition().x)
	{
		MoveDir_.x = 1000.f;
	}

	GetTransform().SetWorldMove(MoveDir_ * _DeltaTime);
}

void Player::DieUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Player::FlyingUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (0.01f < _Info.StateTime && false == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		MoveDir_ -= float4{ 0.f, 1.f, 0.f } * 170.f * _DeltaTime;
	}
	else if (0.2f < _Info.StateTime)
	{
		if (true == BottomDownColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
		{
			StateManager.ChangeState("Idle");
			return;
		}
	}
	
	if (true == GameEngineInput::GetInst()->IsDown("Jump"))
	{
		if (true == TopColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }))
		{
			MoveDir_.y = 0.f;
		}
		else
		{
			MoveDir_.y = 180.f;

		}
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		if (true == TopColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }))
		{
			MoveDir_.y = 0.f;
		}
		else
		{
			MoveDir_.y = 120.f;
		}
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir_.y = -120.f;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		CurDir_ = ACTORDIR::LEFT;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		CurDir_ = ACTORDIR::RIGHT;
	}


	GetTransform().SetWorldMove(MoveDir_ * _DeltaTime);

	//if (true == IsSkillKey())
	//{
	//	UseSkill();
	//}

}
