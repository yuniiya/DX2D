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
#include "GameEngineCore/GEngine.h"


Player* Player::MainPlayer_ = nullptr;

Player::Player() 
	: Speed_(200.0f)
	, JumpPower_(200.f)
	, DownPower_(0.0f)
	, CurState_(PLAYERSTATE::IDLE)
	, PlayerCollision_(nullptr)
	, PlayerRenderer_(nullptr)
	, Position_(0.0f)
	, IsDebug(false)
	, CurDir_(ACTORDIR::RIGHT)
	, IsGround(true)
	, CanMove(true)
	, ColMapRenderer_(nullptr)
	, MapTexture_(nullptr)
	, Time_(0.0f)
{
}

Player::~Player() 
{
}


GameEngineTexture* Player::GetCurMapTexture()
{
	MapTexture_ = GetLevel<GlobalLevel>()->GetCollisionMap()->GetCurTexture();

	if (nullptr == MapTexture_)
	{
		MsgBoxAssert("�浹���� �������� �ʾҽ��ϴ�");
	}

	return MapTexture_;
}

void Player::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("Down", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Jump", 'X');		
		GameEngineInput::GetInst()->CreateKey("Pick", 'Z');
		GameEngineInput::GetInst()->CreateKey("Attack", VK_LCONTROL);

		GameEngineInput::GetInst()->CreateKey("MoveDown", VK_NUMPAD0);

		GameEngineInput::GetInst()->CreateKey("Inventory", 'I');
		GameEngineInput::GetInst()->CreateKey("Ability", 'H');

		// ���� �ι� => �ʻ��
		// ���Ǽ� �� Q
		// ����ǳ õ W
		// ������ �� E
		// ���� R
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
	PlayerRenderer_->CreateFrameAnimationFolder("Jump", FrameAnimation_DESC("Jump", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("Fall", FrameAnimation_DESC("Fall", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("Prone", FrameAnimation_DESC("Prone", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("ProneStab", FrameAnimation_DESC("ProneStab", 0.37f));
	PlayerRenderer_->CreateFrameAnimationFolder("Ladder", FrameAnimation_DESC("Ladder", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("Rope", FrameAnimation_DESC("Rope", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("DefaultAtt", FrameAnimation_DESC("Player_Attack1", 0.25f));
	PlayerRenderer_->CreateFrameAnimationFolder("SkillAtt", FrameAnimation_DESC("Player_Attack2", 0.25f));
	PlayerRenderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("Alert", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("Die", FrameAnimation_DESC("Player_Die", 0.2f));

	PlayerRenderer_->ChangeFrameAnimation("Idle");


	StateManager.CreateStateMember("Idle", this, &Player::IdleUpdate, &Player::IdleStart);
	StateManager.CreateStateMember("Move", this, &Player::MoveUpdate, &Player::MoveStart);
	StateManager.CreateStateMember("Jump", this, &Player::JumpUpdate, &Player::JumpStart);
	StateManager.CreateStateMember("Fall", this, &Player::FallUpdate, &Player::FallStart);
	StateManager.CreateStateMember("Prone", this, &Player::ProneUpdate, &Player::ProneStart);
	StateManager.CreateStateMember("ProneStab", this, &Player::ProneStabUpdate, &Player::ProneStabStart);
	StateManager.CreateStateMember("Ladder", this, &Player::LadderUpdate, &Player::LadderStart);
	StateManager.CreateStateMember("Rope", this, &Player::RopeUpdate, &Player::RopeStart);
	StateManager.CreateStateMember("DefaultAtt", this, &Player::DefaultAttackUpdate, &Player::DefaultAttackStart);
	StateManager.CreateStateMember("SkillAtt", this, &Player::SkillAttackUpdate, &Player::SkillAttackStart);
	StateManager.CreateStateMember("Damaged", this, &Player::DamagedUpdate, &Player::DamagedStart);
	StateManager.CreateStateMember("Die", this, &Player::DieUpdate, &Player::DieStart);

	StateManager.ChangeState("Idle");



}

void Player::Update(float _DeltaTime)
{
	//PlayerStateUpdate();
	StateManager.Update(_DeltaTime);

	PlayerMove(_DeltaTime);

	DebugModeOnOff();
	StagePixelCheck();
}

void Player::DebugModeOnOff()
{
	if (GetCurLevelName() == "BOSS")
	{
		return;
	}

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
	float4 Pos = 0.0f;
	GetCurMapTexture();

	BottomColor = MapTexture_->GetPixel((float)GetTransform().GetWorldPosition().ix(), (float)(-GetTransform().GetWorldPosition().iy()) + 43.f);	// �� �� �ȼ��� ���� ���´�
	float4 BottomUpColor = MapTexture_->GetPixel((float)GetTransform().GetWorldPosition().ix(), (float)(-GetTransform().GetWorldPosition().iy()) + 41.f);	// �ߺ��� ������
	float4 TopColor = MapTexture_->GetPixel((float)GetTransform().GetWorldPosition().ix(), (float)(-GetTransform().GetWorldPosition().iy()) - 25.f);
	float4 LeftColor = MapTexture_->GetPixel((float)GetTransform().GetWorldPosition().ix() - 30.f, (float)(-GetTransform().GetWorldPosition().iy()) + 10.f);
	float4 RightColor = MapTexture_->GetPixel((float)GetTransform().GetWorldPosition().ix() + 30.f, (float)(-GetTransform().GetWorldPosition().iy()) + 10.f);


	// ��
	if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		// ========= ���� : ������ �ƴҶ���?
		if (true == BottomUpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))													// 1-1) �� ���� ���� ���̸� 1�ȼ� �ø���
		{
			//Position_ = GetPosition() + float4{ 0.f, 2.f, 0.f };
			//GetTransform().SetLocalPosition(Position_);

			Pos = float4{ 0.f, 2.f, 0.f };
			GetTransform().SetWorldMove(Pos);
		}
	}

	//if (false == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	//{
	//	Position_ = GetPosition() + float4{ 0.f, -150.f, 0.f } *GameEngineTime::GetDeltaTime();
	//	GetTransform().SetLocalPosition(Position_);
	//}

	// ���
	if (true == BottomColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })		// ���
		|| true == BottomColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })	// ����
		|| true == BottomColor.CompareInt4D(float4{ 1.f, 0.f, 1.f, 1.f })	// ����Ÿ
		|| true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 1.f, 1.f }))	// ����
	{
		// ī�޶� �ٱ��� �̵� ���� - ��
		if (true == TopColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f })
			|| true == TopColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
		{
			DownPower_ = float4{ 0.f, -9.f, 0.f };
			GetTransform().SetWorldMove(DownPower_);
		}
		else
		{
			DownPower_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 15.f;
			GetTransform().SetWorldMove(DownPower_);
			/*Position_ = GetPosition() + float4{ 0.f, -150.f, 0.f } *GameEngineTime::GetDeltaTime();
			GetTransform().SetLocalPosition(Position_);*/
		}
	}
	else
	{
		DownPower_ = 0.0f;
	}

	//// �Ӹ��� ������ ��Ҵ�
	//if (true == TopColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })
	//	|| true == TopColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }))
	//{
	//	Position_ = GetPosition() + float4{ 0.f, -6.f, 0.f }*GameEngineTime::GetDeltaTime();
	//	GetTransform().SetLocalPosition(Position_);
	//}

	// ���
	//if (true == BottomColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })
	//	/*	|| true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f })*/)												// 1) �� ���� ����̴�
	//{
	//	DownPower += float4::DOWN;
	//	Position_ = GetPosition() + float4{ 0.f, -1.f, 0.f } + DownPower/**GameEngineTime::GetDeltaTime()*/;
	//	GetTransform().SetLocalPosition(Position_);

	//	//if (false == BottomUpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	//	//{
	//	//	Position_ = GetPosition() + float4{ 0.f, -2.f, 0.f }/**GameEngineTime::GetDeltaTime()*/;
	//	//	GetTransform().SetWorldMove(Position_);
	//	//}
	//}



	//else if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))												// 2) �� ���� ���̴�
	//{ 
	//	
	//	Position_ = GetPosition() + float4{ 0.f, 2.f, 0.f } *GameEngineTime::GetDeltaTime();
	//	GetTransform().SetLocalPosition(Position_);

	//	//if (true == LeftBottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })													// 2-2) ���� �߳��� ���̰ų�, ������ �߳��� ���̸� �ø���
	//	//	|| true == RightBottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	//	//{
	//	//	
	//	//}
	//}


	//// 0 0 0 1 => ����
	//if (false == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })) // �� ���� ������ �ƴϴ�
	//{
	//	// �����ٰ� ���� ��Ҵ�
	//	if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	//	{
	//		IsGround = true;

	//		//Position_ = GetPosition() + float4{ 0.f, 200.f, 0.f } *GameEngineTime::GetDeltaTime();

	//		//GetTransform().SetLocalPosition(Position_);
	//	}


		

	//	// 0 1 0 1 => �ʷϻ�
	//	if (true == BottomColor.CompareInt4D(float4{ 0.f, 1.f, 0.f, 1.f }))
	//	{
	//		Position_ = GetPosition() + float4{0.f, 200.f, 0.f} * GameEngineTime::GetDeltaTime();
	//		GetTransform().SetLocalPosition(Position_);
	//		// Down Ű ������ => Ladder
	//	}
	//	else if (false == BottomColor.CompareInt4D(float4{ 0.f, 1.f, 0.f, 1.f }))
	//	{
	//		Position_ = GetPosition() + float4{ 0.f, -200.f, 0.f } *GameEngineTime::GetDeltaTime();	// ������
	//		GetTransform().SetLocalPosition(Position_);
	//	}
	//	// 1 0 0 1 => �Ķ���
	//	if (true == BottomColor.CompareInt4D(float4{ 1.f, 0.f, 0.f, 1.f }))
	//	{
	//		Position_ = GetPosition() + float4{ 0.f, 200.f, 0.f } *GameEngineTime::GetDeltaTime();
	//		GetTransform().SetLocalPosition(Position_);
	//		// Down Ű ������ => Rope
	//	}
	//	else if(false == BottomColor.CompareInt4D(float4{ 1.f, 0.f, 0.f, 1.f }))
	//	{
	//		Position_ = GetPosition() + float4{ 0.f, -200.f, 0.f } *GameEngineTime::GetDeltaTime();	// ������
	//		GetTransform().SetLocalPosition(Position_);
	//	}

	//}



	// ī�޶� �ٱ��� �̵� ���� - ����
	if (CurDir_ == ACTORDIR::LEFT)
	{
		if (true == LeftColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }))
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

	// ī�޶� �ٱ��� �̵� ���� - ������
	if (CurDir_ == ACTORDIR::RIGHT)
	{
		if (true == RightColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }))
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



	// ��Ż, ����, ���� 
	ObjectPixelCheck();

	return true;
}

void Player::ObjectPixelCheck()
{
	float4 Color = MapTexture_->GetPixel((float)GetTransform().GetWorldPosition().ix(), (float)(-GetTransform().GetWorldPosition().iy()));

	if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{
		// ���� ����
		if (true == Color.CompareInt4D(float4{ 1.0f, 0.0f, 1.0f, 1.0f }))
		{
			if ("ARIANT" == CurLevelName_)
			{
				GEngine::ChangeLevel("Cactus");
			}
			else if ("ENTRANCE" == CurLevelName_)
			{
				GEngine::ChangeLevel("Castle");
			}
			else if ("CACTUS" == CurLevelName_)
			{
				GEngine::ChangeLevel("Desert");
			}
			else if ("DESERT" == CurLevelName_)
			{
				GEngine::ChangeLevel("Aqua");
			}
			else if ("AQUA" == CurLevelName_)
			{
				GEngine::ChangeLevel("Boss");
			}

		}	// ���� ����
		else if (true == Color.CompareInt4D(float4{ 0.0f, 0.0f, 1.0f, 1.0f }))
		{
			if ("ARIANT" == CurLevelName_)
			{
				GEngine::ChangeLevel("Entrance");
			}
			else if ("ENTRANCE" == CurLevelName_)
			{
				GEngine::ChangeLevel("Ariant");
			}
			else if ("CASTLE" == CurLevelName_)
			{
				GEngine::ChangeLevel("Entrance");
			}
			else if ("CACTUS" == CurLevelName_)
			{
				GEngine::ChangeLevel("Ariant");
			}
			else if ("DESERT" == CurLevelName_)
			{
				GEngine::ChangeLevel("Cactus");
			}
			else if ("AQUA" == CurLevelName_)
			{
				GEngine::ChangeLevel("Desert");
			}
		}
	}

	// ����, ����
	if (true == GameEngineInput::GetInst()->IsDown("Down"))
	{
		// ����
		if (true == BottomColor.CompareInt4D(float4{ 0.0f, 1.0f, 0.0f, 1.0f }))
		{
			StateManager.ChangeState("Ladder");
			return;
		}
	}
}

void Player::ChangeState(PLAYERSTATE _State)
{
	/*if (CurState_ != _State)
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

	CurState_ = _State;*/
}

void Player::PlayerStateUpdate()
{
	//switch (CurState_)
	//{
	//case PLAYERSTATE::IDLE:
	//	IdleUpdate();
	//	break;
	//case PLAYERSTATE::MOVE:
	//	MoveUpdate();
	//	break;
	//case PLAYERSTATE::JUMP:
	//	JumpUpdate();
	//	break;
	//case PLAYERSTATE::PRONE:
	//	ProneUpdate();
	//	break;
	//case PLAYERSTATE::PRONESTAB:
	//	ProneStabUpdate();
	//	break;
	//case PLAYERSTATE::LADDER:
	//	LadderUpdate();
	//	break;
	//case PLAYERSTATE::ROPE:
	//	RopeUpdate();
	//	break;
	//case PLAYERSTATE::ATTACK:
	//	AttackUpdate();
	//	break;
	//case PLAYERSTATE::DAMAGED:
	//	DamagedUpdate();
	//	break;
	//case PLAYERSTATE::DIE:
	//	DieUpdate();
	//	break;
	//}
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

			//if (CurState_ != PLAYERSTATE::PRONE
			//	&& CurState_ != PLAYERSTATE::PRONESTAB)		// ========= ���� �ʿ�
			{
				/*float4 Pos = MainPlayer_->GetTransform().GetLocalPosition();
				float4 Pos2 = MainPlayer_->GetTransform().GetWorldPosition();*/
				GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * _DeltaTime);
			}
		}
		if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
		{
			CurDir_ = ACTORDIR::RIGHT;

			//if (CurState_ != PLAYERSTATE::PRONE
			//	&& CurState_ != PLAYERSTATE::PRONESTAB)		// ========= ���� �ʿ�
			{
				GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * _DeltaTime);
			}
		}
	}

	DirCheck(PlayerRenderer_, CurDir_);

	/////////////////////////////////////////////////////////////////////////
	// 0 255 0 (����) �� �浹���� ���� 
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * 500.f * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown")
		&& false == IsGround)
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed_ * _DeltaTime);
	}
}

void Player::ReturnIdle(const FrameAnimation_DESC& _Info)
{
	StateManager.ChangeState("Idle");
}

