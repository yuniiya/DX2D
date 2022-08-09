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
#include "Fade.h"
#include "FadeIn.h"


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
	, TopColor(0.0f)
	, MiddleColor(0.0f)
	, BottomUpColor(0.0f)
	, InA_Renderer_(nullptr)
	, InB_Renderer_(nullptr)
	, InHit_Renderer_(nullptr)
	, JiA_Renderer_(nullptr)
	, JiB_Renderer_(nullptr)
	, JiHit_Renderer_(nullptr)
	, PaA_Renderer_(nullptr)
	, PaHit_Renderer_(nullptr)
	, SinStart_Renderer_(nullptr)
	, SinA_Renderer_(nullptr)
	, SinAHit_Renderer_(nullptr)
	, SinB_Renderer_(nullptr)
	, SinBHit_Renderer_(nullptr)
	, SinC_Renderer_(nullptr)
	, SinCHit_Renderer_(nullptr)
	, SinD_Renderer_(nullptr)
	, SinDHit_Renderer_(nullptr)
	, InSkillCollision_(nullptr)
	, PaSkillCollision_(nullptr)
	, JiSkillCollision_(nullptr)
	, SinACollision_(nullptr)
	, SinBCollision_(nullptr)
	, SinCCollision_(nullptr)
	, SinDCollision_(nullptr)
	, CurSkill_(PLAYERSKILL::MAX)
	, ChoA_Renderer_(nullptr)
	, ChoB_Renderer_(nullptr)
	, HP_(8000)
	, MP_(6000)
	, Exp_(10000)
	, Atk_(5000)

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
		MsgBoxAssert("충돌맵이 설정되지 않았습니다");
	}

	return MapTexture_;
}

void Player::TakeDamage(int _Damage)
{
	if (HP_ <= 0)
	{
		StateManager.ChangeState("Die");
	}

	HP_ = HP_ - _Damage;
}

void Player::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("MoveDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Jump", 'X');		
		GameEngineInput::GetInst()->CreateKey("Pick", 'Z');
		GameEngineInput::GetInst()->CreateKey("Attack", VK_LCONTROL);

		GameEngineInput::GetInst()->CreateKey("Down", VK_NUMPAD0);

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

	PlayerCollision_ = CreateComponent<GameEngineCollision>();
	PlayerCollision_->GetTransform().SetLocalScale({75.f, 75.f});
	PlayerCollision_->ChangeOrder(GAMEOBJGROUP::PLAYER);

	PlayerRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	PlayerRenderer_->GetTransform().SetLocalScale({80.f, 96.f, 1.f});

	//PlayerRenderer_->SetTexture("Idle", 0);
	PlayerRenderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Player_Idle", 0.5f));
	PlayerRenderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Player_Move", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("Jump", FrameAnimation_DESC("Jump", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("Fall", FrameAnimation_DESC("Fall", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("Prone", FrameAnimation_DESC("Prone", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("ProneStab", FrameAnimation_DESC("ProneStab", 0.37f));
	PlayerRenderer_->CreateFrameAnimationFolder("Ladder", FrameAnimation_DESC("Ladder", 0.5f));
	PlayerRenderer_->CreateFrameAnimationFolder("Rope", FrameAnimation_DESC("Rope", 0.5f));
	PlayerRenderer_->CreateFrameAnimationFolder("LadderA", FrameAnimation_DESC("LadderA", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("RopeA", FrameAnimation_DESC("RopeA", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("DefaultAtt", FrameAnimation_DESC("Player_Attack1", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("SkillAtt", FrameAnimation_DESC("Player_Attack2", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("Alert", 0.2f));
	PlayerRenderer_->CreateFrameAnimationFolder("Die", FrameAnimation_DESC("Player_Die", 0.2f));

	PlayerRenderer_->ChangeFrameAnimation("Idle");


	StateManager.CreateStateMember("Idle"
		, std::bind(&Player::IdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(& Player::IdleStart, this, std::placeholders::_1)
		);
	StateManager.CreateStateMember("Move"
		, std::bind(&Player::MoveUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::MoveStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Jump"
		, std::bind(&Player::JumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::JumpStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Fall"
		, std::bind(&Player::FallUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::FallStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Prone"
		, std::bind(&Player::ProneUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::ProneStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("ProneStab"
		, std::bind(&Player::ProneStabUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::ProneStabStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Ladder"
		, std::bind(&Player::LadderUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::LadderStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Rope"
		, std::bind(&Player::RopeUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::RopeStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("DefaultAtt"
		, std::bind(&Player::DefaultAttackUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::DefaultAttackStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("SkillAtt"
		, std::bind(&Player::SkillAttackUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::SkillAttackStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Damaged"
		, std::bind(&Player::DamagedUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::DamagedStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Die"
		, std::bind(&Player::DieUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::DieStart, this, std::placeholders::_1)
	);
	/*StateManager.CreateStateMember("Move", this, &Player::MoveUpdate, &Player::MoveStart);
	StateManager.CreateStateMember("Jump", this, &Player::JumpUpdate, &Player::JumpStart);
	StateManager.CreateStateMember("Fall", this, &Player::FallUpdate, &Player::FallStart);
	StateManager.CreateStateMember("Prone", this, &Player::ProneUpdate, &Player::ProneStart);
	StateManager.CreateStateMember("ProneStab", this, &Player::ProneStabUpdate, &Player::ProneStabStart);
	StateManager.CreateStateMember("Ladder", this, &Player::LadderUpdate, &Player::LadderStart);
	StateManager.CreateStateMember("Rope", this, &Player::RopeUpdate, &Player::RopeStart);
	StateManager.CreateStateMember("DefaultAtt", this, &Player::DefaultAttackUpdate, &Player::DefaultAttackStart);
	StateManager.CreateStateMember("SkillAtt", this, &Player::SkillAttackUpdate, &Player::SkillAttackStart);
	StateManager.CreateStateMember("Damaged", this, &Player::DamagedUpdate, &Player::DamagedStart);
	StateManager.CreateStateMember("Die", this, &Player::DieUpdate, &Player::DieStart);*/

	StateManager.ChangeState("Idle");


	// 스킬
	{
		InSkillCollision_ = CreateComponent<GameEngineCollision>();
		InSkillCollision_->GetTransform().SetLocalScale({400.f, 300.f});
		InSkillCollision_->ChangeOrder(GAMEOBJGROUP::SKILL);
		InSkillCollision_->Off();

		InA_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		InA_Renderer_->GetTransform().SetLocalScale({ 343.f, 290.f });
		InA_Renderer_->CreateFrameAnimationFolder("In_A", FrameAnimation_DESC("In_A", 0.06f));
		InA_Renderer_->ChangeFrameAnimation("In_A");
		InA_Renderer_->Off();

		InB_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		InB_Renderer_->GetTransform().SetLocalScale({ 407.f, 246.f });
		InB_Renderer_->CreateFrameAnimationFolder("In_B", FrameAnimation_DESC("In_B", 0.075f));
		InB_Renderer_->ChangeFrameAnimation("In_B");
		InB_Renderer_->Off();

		InHit_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		InHit_Renderer_->GetTransform().SetLocalScale({ 132.f, 132.f });
		InHit_Renderer_->CreateFrameAnimationFolder("In_Hit", FrameAnimation_DESC("In_Hit", 0.06f));
		InHit_Renderer_->ChangeFrameAnimation("In_Hit");
		InHit_Renderer_->Off();

	}
}

void Player::Update(float _DeltaTime)
{
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
	float PlayerPosX = GetPosition().x;
	float PlayerPosY = GetPosition().y;

	if (true == IsDebug)
	{
		std::string PosX = "";
		std::string PosY = "";

		PosX = "PosX : " + std::to_string(PlayerPosX);
		PosY = "PosY : " + std::to_string(PlayerPosY);


		TextOut(GameEngineWindow::GetHDC(), GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().x + 40.f, GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().x - 30.f, PosX.c_str(), static_cast<int>(PosX.length()));
		TextOut(GameEngineWindow::GetHDC(), GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().x + 40.f, GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().y - 10.f, PosY.c_str(), static_cast<int>(PosY.length()));
	}
}


bool Player::StagePixelCheck()
{
	float4 Pos = 0.0f;
	GetCurMapTexture();

	//MiddleColor = MapTexture_->GetPixel(static_cast<float>(GetTransform().GetWorldPosition().ix()), static_cast<float>(-(GetTransform().GetWorldPosition().iy())));
	//BottomDownColor = MapTexture_->GetPixel(static_cast<float>(GetTransform().GetWorldPosition().ix()), static_cast<float>(((-GetTransform().GetWorldPosition().iy()) + 47.f)));
	//BottomColor = MapTexture_->GetPixel(static_cast<float>(GetTransform().GetWorldPosition().ix()), static_cast<float>((-GetTransform().GetWorldPosition().iy()) + 43.f));	// 발 밑 픽셀의 값을 얻어온다
	//BottomUpColor = MapTexture_->GetPixel(static_cast<float>(GetTransform().GetWorldPosition().ix()), static_cast<float>(-GetTransform().GetWorldPosition().iy()) + 41.f);	// 발보다 조금위
	//TopColor = MapTexture_->GetPixel(static_cast<float>(GetTransform().GetWorldPosition().ix()), static_cast<float>((-GetTransform().GetWorldPosition().iy()) - 25.f));
	//float4 LeftColor = MapTexture_->GetPixel(static_cast<float>(GetTransform().GetWorldPosition().ix() - 30.f), static_cast<float>(-GetTransform().GetWorldPosition().iy()) + 10.f);
	//float4 RightColor = MapTexture_->GetPixel(static_cast<float>(GetTransform().GetWorldPosition().ix() + 30.f), static_cast<float>((-GetTransform().GetWorldPosition().iy()) + 10.f));

	MiddleColor = MapTexture_->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));
	BottomDownColor = MapTexture_->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y) + 47.f);
	BottomColor = MapTexture_->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y) + 43.f);	// 발 밑 픽셀의 값을 얻어온다
	BottomUpColor = MapTexture_->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y) + 41.f);	// 발보다 조금위
	TopColor = MapTexture_->GetPixel(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y) - 25.f);
	float4 LeftColor = MapTexture_->GetPixel(static_cast<float>(GetTransform().GetWorldPosition().ix() - 30.f), static_cast<float>(-GetTransform().GetWorldPosition().iy()) + 10.f);
	float4 RightColor = MapTexture_->GetPixel(static_cast<float>(GetTransform().GetWorldPosition().ix() + 30.f), static_cast<float>((-GetTransform().GetWorldPosition().iy()) + 10.f));

	
	// 땅
	if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		if (true == BottomUpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))													// 1-1) 발 조금 위가 땅이면 1픽셀 올린다
		{
			Pos = float4{ 0.f, 2.f, 0.f };
			GetTransform().SetWorldMove(Pos);
		}
	}

	// 허공
	if (true == BottomColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })		// 흰색
		|| true == BottomColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 0.f })	// 투명
		|| true == BottomColor.CompareInt4D(float4{ 1.f, 0.f, 1.f, 1.f })	// 마젠타
		|| true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 1.f, 1.f }))	// 레드
	{
		// 카메라 바깥쪽 이동 막기 - 위
		if (true == TopColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f })
			|| true == TopColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
		{
			DownPower_ = float4{ 0.f, -9.f, 0.f };
			GetTransform().SetWorldMove(DownPower_);
		}
		else
		{
			DownPower_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 20.f;
			GetTransform().SetWorldMove(DownPower_);
			/*Position_ = GetPosition() + float4{ 0.f, -150.f, 0.f } *GameEngineTime::GetDeltaTime();
			GetTransform().SetLocalPosition(Position_);*/
		}
	}
	else if (true == BottomColor.CompareInt4D(float4{ 0.f, 1.f, 0.f, 1.f })
		|| true == BottomColor.CompareInt4D(float4{ 1.f, 0.f, 0.f, 1.f }))
	{
		if ("Jump" == StateManager.GetCurStateStateName())
		{
			DownPower_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 20.f;
			GetTransform().SetWorldMove(DownPower_);
		}

	}
	else
	{
		DownPower_ = 0.0f;
	}


	// 카메라 바깥쪽 이동 막기 - 왼쪽
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

	// 카메라 바깥쪽 이동 막기 - 오른쪽
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


	// 포탈, 레더, 로프 
	ObjectPixelCheck();

	return true;
}

void Player::ObjectPixelCheck()
{
	float4 Color = MapTexture_->GetPixel(static_cast<float>(GetTransform().GetWorldPosition().ix()), static_cast<float>(-GetTransform().GetWorldPosition().iy()));

	if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{
		// 다음 레벨
		if (true == Color.CompareInt4D(float4{ 1.0f, 0.0f, 1.0f, 1.0f }))
		{
			GameEngineSound::SoundPlayOneShot("Portal.mp3");

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

			//LevelChangeTime_ = 0.0f;

		}	// 이전 레벨
		else if (true == Color.CompareInt4D(float4{ 0.0f, 0.0f, 1.0f, 1.0f }))
		{
			GameEngineSound::SoundPlayOneShot("Portal.mp3");

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

	// 레더, 로프
	if (true == GameEngineInput::GetInst()->IsDown("Down"))
	{
		// 레더
		if (true == BottomColor.CompareInt4D(float4{ 0.0f, 1.0f, 0.0f, 1.0f }))
		{
			StateManager.ChangeState("Ladder");
			return;
		}
	}
}

void Player::ColiisionCheck()
{
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

bool Player::IsUpDownMoveKey()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp")
		|| true == GameEngineInput::GetInst()->IsPress("MoveDown"))
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

			
			if (StateManager.GetCurStateStateName() != "Prone"
				&& StateManager.GetCurStateStateName() != "ProneStab"
				&& StateManager.GetCurStateStateName() != "Ladder"
				&& StateManager.GetCurStateStateName() != "Rope"
				)
			{
				/*float4 Pos = MainPlayer_->GetTransform().GetLocalPosition();
				float4 Pos2 = MainPlayer_->GetTransform().GetWorldPosition();*/
				//std::string str = StateManager.GetCurStateStateName();
				GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * _DeltaTime);
			}
		}
		if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
		{
			CurDir_ = ACTORDIR::RIGHT;

			if (StateManager.GetCurStateStateName() != "Prone"
				&& StateManager.GetCurStateStateName() != "ProneStab"
				&& StateManager.GetCurStateStateName() != "Ladder"
				&& StateManager.GetCurStateStateName() != "Rope"
				)
			{
				GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed_ * _DeltaTime);
			}
		}
	}

	if ("Ladder" != StateManager.GetCurStateStateName()
		&& "Rope" != StateManager.GetCurStateStateName())
	{
		DirCheck(PlayerRenderer_, CurDir_);
	}

}

void Player::UseSkill()
{
	if (true == GameEngineInput::GetInst()->IsDown("Skill_Q"))
	{
		GameEngineSound::SoundPlayControl("InUse.mp3");

		InA_Renderer_->On();
		InB_Renderer_->On();
		InSkillCollision_->On();

		CurSkill_ = PLAYERSKILL::SKILL_IN;

		AddAccTime(Time_);
		StateManager.ChangeState("SkillAtt");
		return;
	}
	else if (true == GameEngineInput::GetInst()->IsPress("Skill_W"))
	{

	}
	else if (true == GameEngineInput::GetInst()->IsPress("Skill_E"))
	{

	}
	else if (true == GameEngineInput::GetInst()->IsPress("Skill_R"))
	{

	}
}

void Player::SkillEnd(const FrameAnimation_DESC& _Info)
{
	switch (CurSkill_)
	{
	case PLAYERSKILL::SKILL_IN:
	{

		InA_Renderer_->Off();
		InB_Renderer_->Off();
		InSkillCollision_->Off();

	}
	case PLAYERSKILL::SKILL_JI:
	{
	
	}
	break;
	default:
		break;
	}

	StateManager.ChangeState("Idle");
	return;
}

void Player::SkillPositionUpdate(PLAYERSKILL _CurSkill)
{
	if ("SkillAtt" != StateManager.GetCurStateStateName())
	{
		return;
	}

	switch (_CurSkill)
	{
	case PLAYERSKILL::SKILL_IN:
	{
		if (ACTORDIR::RIGHT == CurDir_)
		{
			InA_Renderer_->GetTransform().PixLocalNegativeX();
			InA_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x - 20.f, GetPosition().y });

			InB_Renderer_->GetTransform().PixLocalNegativeX();
			InB_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x + 130.f, GetPosition().y });
		}
		else
		{
			InA_Renderer_->GetTransform().PixLocalPositiveX();
			InA_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x + 20.f, GetPosition().y });

			InB_Renderer_->GetTransform().PixLocalPositiveX();
			InB_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x - 130.f, GetPosition().y });
		}
	}
		break;
	case PLAYERSKILL::SKILL_JI:
		break;
	case PLAYERSKILL::SKILL_PA:
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
}

