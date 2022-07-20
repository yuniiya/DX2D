#include "PreCompile.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <iostream>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineContents/GlobalContentsValue.h>
#include "ScoreTestComponent.h"
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>
#include <GameEngineCore/GameEngineDevice.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>


Player* Player::MainPlayer_ = nullptr;

Player::Player() 
	: Speed_(80.0f)
	, CurState_(PLAYERSTATE::MAX)
	, PlayerCollision_(nullptr)
	, PlayerRenderer_(nullptr)
{
}

Player::~Player() 
{
}


void Player::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("MoveDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Jump", VK_LMENU);
		GameEngineInput::GetInst()->CreateKey("Pick", VK_LCONTROL);

		GameEngineInput::GetInst()->CreateKey("Inventory", 'I');
		GameEngineInput::GetInst()->CreateKey("Ability", 'H');

		// 점프 두번 => 초상비
		// 여의선 인 Q
		// 파초풍 천 W
		// 지진쇄 지 E
		// 괴력 R
		GameEngineInput::GetInst()->CreateKey("Skill_Q", 'Q');
		GameEngineInput::GetInst()->CreateKey("Skill_W", 'W');
		GameEngineInput::GetInst()->CreateKey("SKill_E", 'E');
		GameEngineInput::GetInst()->CreateKey("Skill_R", 'R');

	}

	PlayerRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	PlayerRenderer_->GetTransform().SetLocalScale({80.f, 96.f, 1.f});

	//PlayerRenderer_->SetTexture("Idle", 0);
	PlayerRenderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Idle", 0.5f));
	PlayerRenderer_->ChangeFrameAnimation("Idle");

	//PlayerRenderer_->ScaleToTexture();


}

void Player::Update(float _DeltaTime)
{
	PlayerRenderer_->ChangeFrameAnimation("Idle");

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * _DeltaTime);
	}
}

void Player::ChangeState(PLAYERSTATE _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case PLAYERSTATE::IDLE:
			IdleStart();
			break;
		case PLAYERSTATE::MOVE:
			MoveStart();
			break;
		case PLAYERSTATE::JUMP:
			JumpStart();
			break;
		case PLAYERSTATE::PRONE:
			ProneStart();
			break;
		case PLAYERSTATE::PRONESTAB:
			ProneStabStart();
			break;
		case PLAYERSTATE::LADDER:
			LadderStart();
			break;
		case PLAYERSTATE::ROPE:
			RopeStart();
			break;
		case PLAYERSTATE::ATTACK:
			AttackStart();
			break;
		case PLAYERSTATE::DAMAGED:
			DamagedStart();
			break;
		case PLAYERSTATE::DIE:
			DieStart();
			break;
		}
	}

	CurState_ = _State;
}

void Player::PlayerStateUpdate()
{
	switch (CurState_)
	{
	case PLAYERSTATE::IDLE:
		IdleUpdate();
		break;
	case PLAYERSTATE::MOVE:
		MoveUpdate();
		break;
	case PLAYERSTATE::JUMP:
		JumpUpdate();
		break;
	case PLAYERSTATE::PRONE:
		ProneUpdate();
		break;
	case PLAYERSTATE::PRONESTAB:
		ProneStabUpdate();
		break;
	case PLAYERSTATE::LADDER:
		LadderUpdate();
		break;
	case PLAYERSTATE::ROPE:
		RopeUpdate();
		break;
	case PLAYERSTATE::ATTACK:
		AttackUpdate();
		break;
	case PLAYERSTATE::DAMAGED:
		DamagedUpdate();
		break;
	case PLAYERSTATE::DIE:
		DieUpdate();
		break;
	}
}

