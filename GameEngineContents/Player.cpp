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

		GameEngineInput::GetInst()->CreateKey("Inventory", 'I');
		GameEngineInput::GetInst()->CreateKey("Ability", 'H');

		// Á¡ÇÁ µÎ¹ø => ÃÊ»óºñ
		// ¿©ÀÇ¼± ÀÎ Q
		// ÆÄÃÊÇ³ Ãµ W
		// ÁöÁø¼â Áö E
		// ±«·Â R
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
		MsgBoxAssert("Ãæµ¹¸ÊÀÌ ¼³Á¤µÇÁö ¾Ê¾Ò½À´Ï´Ù");
	}

	float4 BottomColor = MapTexture_->GetPixel(GetTransform().GetWorldPosition().ix(), (- GetTransform().GetWorldPosition().iy()) + 45.f);	// ¹ß ¹Ø ÇÈ¼¿ÀÇ °ªÀ» ¾ò¾î¿Â´Ù
	float4 LeftColor = MapTexture_->GetPixel(GetTransform().GetWorldPosition().ix() - 30.f, (-GetTransform().GetWorldPosition().iy()));
	float4 RightColor = MapTexture_->GetPixel(GetTransform().GetWorldPosition().ix() + 30.f, (-GetTransform().GetWorldPosition().iy()));

	
	if (true == BottomColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }))	// ¹ß ¹ØÀÌ ¶¥ÀÌ ¾Æ´Ï´Ù -> ¶¥¿¡ ´êÀ» ¶§±îÁö ³»·ÁÁØ´Ù
	{
		Position_ = GetPosition() + float4{ 0.f, -3.f, 0.f };		
		GetTransform().SetLocalPosition(Position_);
	}

	//if (false == LeftColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }))	// ¿Ü°û¿¡ ´ê¾Ò´Ù
	//{
	//	Position_ = GetPosition() + float4{ 3.f, 0.f, 0.f };
	//	GetTransform().SetLocalPosition(Position_);
	//}
	//else if (false == RightColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }))
	//{
	//	Position_ = GetPosition() + float4{ -3.f, 0.f, 0.f };
	//	GetTransform().SetLocalPosition(Position_);
	//}
	// ¿Ü°ûÀÌ ¾Æ´Ò¶§¸¸ °¥ ¼ö ÀÖ´Ù
	if (false == LeftColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }))	
	{
		CanMove = false;
	}
	else if (false == RightColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }))
	{
		CanMove = false;
	}
	else
	{
		CanMove = true;
	}

	//if (false == Color.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f }))	// ÇÈ¼¿ÀÌ °ËÁ¤ÀÌ´Ù = ¹ß ¹ØÀÌ ¶¥¿¡ ´ê¾Ò´Ù
	//{
	//	Position_ = GetPosition() + float4{ 0.f, 1.f, 0.f };
	//	GetTransform().SetLocalPosition(Position_);
	//}

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
		|| true == GameEngineInput::GetInst()->IsPress("MoveRight")
		|| true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		return true;
	}

	return false;
}

void Player::PlayerMove(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsUp("MoveLeft")
		|| true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		CanMove = true;
	}

	if (false == CanMove)
	{
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		CurDir_ = ACTORDIR::LEFT;
		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		CurDir_ = ACTORDIR::RIGHT;
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed_ * _DeltaTime);
	}

	DirCheck(PlayerRenderer_, CurDir_);

	//if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	//{
	//	GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * _DeltaTime);
	//}
}

