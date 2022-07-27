#include "PreCompile.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <iostream>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineContents/GlobalContentsValue.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>
#include <GameEngineCore/GameEngineDevice.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "GlobalLevel.h"


Player* Player::MainPlayer_ = nullptr;

Player::Player() 
	: Speed_(200.0f)
	, CurState_(PLAYERSTATE::IDLE)
	, PlayerCollision_(nullptr)
	, PlayerRenderer_(nullptr)
	, Position_(0.f)
	, IsDebug(false)
	, CurDir_(ACTORDIR::RIGHT)
	, IsGround(true)
	, CanMove(true)
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
		GameEngineInput::GetInst()->CreateKey("Down", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Jump", VK_LMENU);
		GameEngineInput::GetInst()->CreateKey("Pick", VK_LCONTROL);

		GameEngineInput::GetInst()->CreateKey("MoveDown", VK_NUMPAD0);

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
	PlayerRenderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Player_Idle", 0.5f));
	PlayerRenderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Player_Move", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("Prone", FrameAnimation_DESC("Prone", 0.2f));
	PlayerRenderer_->ChangeFrameAnimation("Idle");

	//CameraActor_ = GetLevel()->CreateActor<GameEngineCameraActor>();
}

void Player::Update(float _DeltaTime)
{
	PlayerStateUpdate();

	PlayerMove(_DeltaTime);

	DebugModeOnOff();
	StagePixelCheck();
	//PixelCollisionMapUpdate(this);
}

void Player::DebugModeOnOff()
{
	if (true == GameEngineInput::GetInst()->IsDown("DebugModeOnOff") && true == IsDebug)
	{
		IsDebug = false;
		GetLevel<GlobalLevel>()->CollisionMapOnOff();
	}

	if (true == GameEngineInput::GetInst()->IsDown("DebugModeOnOff") && false == IsDebug)
	{
		IsDebug = true;
		GetLevel<GlobalLevel>()->CollisionMapOnOff();
	}

	

	DebugRender();
}

void Player::DebugRender()
{
	//float PlayerPosX = GetPosition().x;
	//float PlayerPosY = GetPosition().y;

	//if (true == IsDebug)
	//{
	//	std::string PosX = "";
	//	std::string PosY = "";

	//	PosX = "PosX : " + std::to_string(PlayerPosX);
	//	PosY = "PosY : " + std::to_string(PlayerPosY);


	//	TextOut(GameEngineWindow::GetHDC(), GetLevel()->GetMainCameraActor()->GetTransform().GetLocalPosition().x + 40, GetLevel()->GetMainCameraActor()->GetTransform().GetLocalPosition().x - 30, PosX.c_str(), static_cast<int>(PosX.length()));
	//	TextOut(GameEngineWindow::GetHDC(), GetLevel()->GetMainCameraActor()->GetTransform().GetLocalPosition().x + 40, GetLevel()->GetMainCameraActor()->GetTransform().GetLocalPosition().y - 10, PosY.c_str(), static_cast<int>(PosY.length()));
	//}
}

bool Player::StagePixelCheck()
{
	GameEngineTexture* MapTexture_ = GetLevel<GlobalLevel>()->GetCollisionMap()->GetCurTexture();

	if (nullptr == MapTexture_)
	{
		MsgBoxAssert("충돌맵이 설정되지 않았습니다");
	}

	float4 BottomColor = MapTexture_->GetPixel(GetTransform().GetWorldPosition().ix(), (- GetTransform().GetWorldPosition().iy()) + 45.f);	// 발 밑 픽셀의 값을 얻어온다
	float4 LeftColor = MapTexture_->GetPixel(GetTransform().GetWorldPosition().ix() - 30.f, (-GetTransform().GetWorldPosition().iy()));
	float4 RightColor = MapTexture_->GetPixel(GetTransform().GetWorldPosition().ix() + 30.f, (-GetTransform().GetWorldPosition().iy()));

	
	if (true == BottomColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }))	// 발 밑이 땅이(검정이) 아니다 -> 발 밑이 땅(검정)일 때 까지 내려준다
	{
		Position_ = GetPosition() + float4{ 0.f, -1.f, 0.f };		
		GetTransform().SetLocalPosition(Position_);

		// 내리다가 땅에 닿았다
		if (false == BottomColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }))
		{
			IsGround = true;
		}
	}


	// 카메라 바깥쪽 이동 막기 - 왼쪽
	if (CurDir_ == ACTORDIR::LEFT)
	{
		if (false == LeftColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }))
		{
			if (true == GameEngineInput::GetInst()->IsUp("MoveLeft"))
			{
				CurDir_ = ACTORDIR::NONE;
				return true;
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
	if (CurDir_ == ACTORDIR::RIGHT)
	{
		// 카메라 바깥쪽 이동 막기 - 오른쪽
		if (false == RightColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }))
		{
			if (true == GameEngineInput::GetInst()->IsUp("MoveRight"))
			{
				CurDir_ = ACTORDIR::NONE;
				return true;
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

	return true;
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

bool Player::IsMoveKey()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft")
		|| true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		return true;
	}

	return false;
}

void Player::PlayerMove(float _DeltaTime)
{
	if (CurDir_ == ACTORDIR::NONE)
	{
		CanMove = true;
	}

	if (true == CanMove)
	{
		if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
		{
			CurDir_ = ACTORDIR::LEFT;

			if (CurState_ != PLAYERSTATE::PRONE
				&& CurState_ != PLAYERSTATE::PRONESTAB)
			{
				GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * _DeltaTime);
			}
		}
		if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
		{
			CurDir_ = ACTORDIR::RIGHT;

			if (CurState_ != PLAYERSTATE::PRONE
				&& CurState_ != PLAYERSTATE::PRONESTAB)
			{
				GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * _DeltaTime);
			}
		}
	}

	DirCheck(PlayerRenderer_, CurDir_);

	/////////////////////////////////////////////////////////////////////////
	// 0 255 0 (로프) 에 충돌했을 때만 
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown")
		&& false == IsGround)
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * _DeltaTime);
	}
}

