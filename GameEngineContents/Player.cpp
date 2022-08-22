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
#include "ContentsUI.h"
#include "Monster.h"


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
	, JiC_Renderer_(nullptr)
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
	, CurHP_(100.f)
	, CurMP_(100.f)
	, CurExp_(60.f)
	, Atk_(5000)
	, PrevPosition_(Position_)
	, PrevDir_(CurDir_)
	, IsHit(false)
	, DamageTime_(0.0f)
	, IsUsePaSkill(false)
	, SinSkillAttCount_(2)
	, SinSkillFrameCount_(1)
	, IsUseSinSkill(false)
	, IsSinLoopStart(false)
	, SinLoopTime_(0.0f)
	, SinEndTime_(0.0f)
	, DoubleJumpTime_(0.0f)
	, MaxHP_(CurHP_)
	, MaxMP_(CurMP_)
	, MaxExp_(CurExp_)
	, IsSinLoopEnd(false)
	, SinAttackEnd(false)
	, MoveDir_(0.f)
	, CurLevel_(120.f)
	, IsLevelUp(false)
	, LevelUpEffRenderer_(nullptr)
{
}

Player::~Player() 
{
}


GameEngineTexture* Player::GetCurMapTexture()
{
	if (CurLevelName_ != "TITLE"
		&& CurLevelName_ != "LOGIN"
		&& CurLevelName_ != "SELECT")
	{
		MapTexture_ = GetLevel<GlobalLevel>()->GetCollisionMap()->GetCurTexture();
	}

	if (nullptr == MapTexture_)
	{
		MsgBoxAssert("충돌맵이 설정되지 않았습니다");
	}

	return MapTexture_;
}

void Player::TakeDamage(float _Damage)
{
	if (CurHP_ <= 0)
	{
		StateManager.ChangeState("Die");
		return;
	}

	CurHP_ = CurHP_ - _Damage;
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
		GameEngineInput::GetInst()->CreateKey("DoubleJump", VK_LSHIFT);

		GameEngineInput::GetInst()->CreateKey("Down", VK_NUMPAD0);

		GameEngineInput::GetInst()->CreateKey("Inventory", 'I');
		GameEngineInput::GetInst()->CreateKey("Ability", 'H');

		GameEngineInput::GetInst()->CreateKey("Test", 'T');

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

	GetTransform().SetLocalPosition({ 0, 0, (int)ZOrder::PLAYER});
	PlayerCollision_ = CreateComponent<GameEngineCollision>();
	PlayerCollision_->GetTransform().SetLocalScale({65.f, 60.f, (int)ZOrder::PLAYER});
	PlayerCollision_->ChangeOrder(GAMEOBJGROUP::PLAYER);

	PlayerRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	//PlayerRenderer_->GetTransform().SetLocalScale({80.f, 96.f});
	PlayerRenderer_->GetTransform().SetLocalScale({ 66.f, 69.f});

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
	PlayerRenderer_->CreateFrameAnimationFolder("DoubleJump", FrameAnimation_DESC("Jump", 0.2f));

	PlayerRenderer_->ChangeFrameAnimation("Idle");

	//PlayerRenderer_->GetPipeLine()->SetOutputMergerBlend("TransparentBlend");

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
	StateManager.CreateStateMember("DoubleJump"
		, std::bind(&Player::DoubleJumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::DoubleJumpStart, this, std::placeholders::_1)
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

	{
		JiSkillCollision_ = CreateComponent<GameEngineCollision>();
		JiSkillCollision_->GetTransform().SetLocalScale({ 900.f, 350.f });
		JiSkillCollision_->ChangeOrder(GAMEOBJGROUP::SKILL);
		JiSkillCollision_->Off();

		JiA_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		JiA_Renderer_->GetTransform().SetLocalScale({ 328.f, 297.f });
		JiA_Renderer_->CreateFrameAnimationFolder("Ji_A", FrameAnimation_DESC("Ji_A", 0.06f));
		JiA_Renderer_->ChangeFrameAnimation("Ji_A");
		JiA_Renderer_->Off();

		JiB_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		JiB_Renderer_->GetTransform().SetLocalScale({ 972.f, 398.f });
		JiB_Renderer_->CreateFrameAnimationFolder("Ji_B", FrameAnimation_DESC("Ji_B", 0.04f));
		JiB_Renderer_->ChangeFrameAnimation("Ji_B");
		JiB_Renderer_->Off();

		JiC_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		JiC_Renderer_->GetTransform().SetLocalScale({ 1197.f, 508.f });
		JiC_Renderer_->CreateFrameAnimationFolder("Ji_C", FrameAnimation_DESC("Ji_C", 0.05f));
		JiC_Renderer_->AnimationBindEnd("Ji_C", std::bind(&Player::JiCFrameEnd, this, std::placeholders::_1));
		JiC_Renderer_->ChangeFrameAnimation("Ji_C");
		JiC_Renderer_->Off();

		JiHit_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		JiHit_Renderer_->GetTransform().SetLocalScale({ 368.f, 275.f });
		JiHit_Renderer_->CreateFrameAnimationFolder("Ji_Hit", FrameAnimation_DESC("Ji_Hit", 0.06f));
		JiHit_Renderer_->ChangeFrameAnimation("Ji_Hit");
		JiHit_Renderer_->Off();
	}

	{
		PaSkillCollision_ = CreateComponent<GameEngineCollision>();
		PaSkillCollision_->GetTransform().SetLocalScale({ 680.f, 330.f });
		PaSkillCollision_->ChangeOrder(GAMEOBJGROUP::SKILL);
		PaSkillCollision_->Off();

		PaA_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		PaA_Renderer_->GetTransform().SetLocalScale({ 792.f, 434.f });
		PaA_Renderer_->CreateFrameAnimationFolder("Pa_A", FrameAnimation_DESC("Pa_A", 0.06f));
		PaA_Renderer_->ChangeFrameAnimation("Pa_A");
		PaA_Renderer_->Off();

		PaHit_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		PaHit_Renderer_->GetTransform().SetLocalScale({ 272.f, 228.f });
		PaHit_Renderer_->CreateFrameAnimationFolder("Pa_Hit", FrameAnimation_DESC("Pa_Hit", 0.06f));
		PaHit_Renderer_->ChangeFrameAnimation("Pa_Hit");
		PaHit_Renderer_->Off();
	}

	{
		SinStart_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		SinStart_Renderer_->GetTransform().SetLocalScale({ 717.f * 0.8f, 500.f * 0.8f });
		SinStart_Renderer_->CreateFrameAnimationFolder("Sin_Start", FrameAnimation_DESC("Sin_Start", 0.06f));
		SinStart_Renderer_->ChangeFrameAnimation("Sin_Start");
		SinStart_Renderer_->Off();
		
		SinA_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		SinA_Renderer_->GetTransform().SetLocalScale({ 982.f * 0.8f, 992.f * 0.8f });
		SinA_Renderer_->CreateFrameAnimationFolder("Sin_A", FrameAnimation_DESC("SinA", 0.08f));
		SinA_Renderer_->ChangeFrameAnimation("Sin_A");
		SinA_Renderer_->Off();

		SinAHit_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		SinAHit_Renderer_->GetTransform().SetLocalScale({ 324.f, 328.f });
		SinAHit_Renderer_->CreateFrameAnimationFolder("SinA_Hit", FrameAnimation_DESC("SinA_Hit", 0.06f));
		SinAHit_Renderer_->ChangeFrameAnimation("SinA_Hit");
		SinAHit_Renderer_->Off();

		SinACollision_ = CreateComponent<GameEngineCollision>();
		SinACollision_->GetTransform().SetLocalScale({ 970.f * 0.8f, 500.f * 0.8f });
		SinACollision_->ChangeOrder(GAMEOBJGROUP::SKILL);
		SinACollision_->Off();
	}

	{
		SinB_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		SinB_Renderer_->GetTransform().SetLocalScale({ 850.f * 0.8f, 1096.f * 0.8f });
		SinB_Renderer_->CreateFrameAnimationFolder("Sin_B", FrameAnimation_DESC("SinB", 0.08f));
		SinB_Renderer_->ChangeFrameAnimation("Sin_B");
		SinB_Renderer_->Off();

		SinBHit_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		SinBHit_Renderer_->GetTransform().SetLocalScale({ 324.f, 328.f });
		SinBHit_Renderer_->CreateFrameAnimationFolder("SinB_Hit", FrameAnimation_DESC("SinB_Hit", 0.06f));
		SinBHit_Renderer_->ChangeFrameAnimation("SinB_Hit");
		SinBHit_Renderer_->Off();

		SinBCollision_ = CreateComponent<GameEngineCollision>();
		SinBCollision_->GetTransform().SetLocalScale({ 500.f * 0.8f, 1000.f * 0.8f });
		SinBCollision_->ChangeOrder(GAMEOBJGROUP::SKILL);
		SinBCollision_->Off();
	}

	{
		SinC_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		SinC_Renderer_->GetTransform().SetLocalScale({ 1255.f * 0.8f, 969.f * 0.8f });
		SinC_Renderer_->CreateFrameAnimationFolder("Sin_C", FrameAnimation_DESC("SinC", 0.08f));
		SinC_Renderer_->ChangeFrameAnimation("Sin_C");
		SinC_Renderer_->Off();

		SinCHit_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		SinCHit_Renderer_->GetTransform().SetLocalScale({ 324.f, 328.f });
		SinCHit_Renderer_->CreateFrameAnimationFolder("SinC_Hit", FrameAnimation_DESC("SinC_Hit", 0.06f));
		SinCHit_Renderer_->ChangeFrameAnimation("SinC_Hit");
		SinCHit_Renderer_->Off();

		SinCCollision_ = CreateComponent<GameEngineCollision>();
		SinCCollision_->GetTransform().SetLocalScale({ 700.f * 0.8f, 960.f * 0.8f });
		SinCCollision_->ChangeOrder(GAMEOBJGROUP::SKILL);
		SinCCollision_->Off();
	}

	{
		SinD_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		SinD_Renderer_->GetTransform().SetLocalScale({ 1280.f, 720.f });
		SinD_Renderer_->CreateFrameAnimationFolder("Sin_D", FrameAnimation_DESC("SinD", 0.09f));
		SinD_Renderer_->ChangeFrameAnimation("Sin_D");
		SinD_Renderer_->Off();

		SinDHit_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		SinDHit_Renderer_->GetTransform().SetLocalScale({ 324.f, 328.f });
		SinDHit_Renderer_->CreateFrameAnimationFolder("SinD_Hit", FrameAnimation_DESC("SinD_Hit", 0.06f));
		SinDHit_Renderer_->ChangeFrameAnimation("SinD_Hit");
		SinDHit_Renderer_->Off();

		SinDCollision_ = CreateComponent<GameEngineCollision>();
		SinDCollision_->GetTransform().SetLocalScale({ 1280.f, 720.f });
		SinDCollision_->ChangeOrder(GAMEOBJGROUP::SKILL);
		SinDCollision_->Off();
	}

	{
		ChoA_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
		ChoA_Renderer_->GetTransform().SetLocalScale({ 440.f, 213.f });
		ChoA_Renderer_->CreateFrameAnimationFolder("DoubleJump", FrameAnimation_DESC("ChoA", 0.05f));
		ChoA_Renderer_->AnimationBindEnd("DoubleJump", std::bind(&Player::DoubleJumpEnd, this, std::placeholders::_1));
		ChoA_Renderer_->ChangeFrameAnimation("DoubleJump");
	//	ChoA_Renderer_->GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::SKILLBACK });
		ChoA_Renderer_->Off();
	}

	SinA_Renderer_->AnimationBindEnd("Sin_A", std::bind(&Player::SinSkillUpdate, this, std::placeholders::_1));
	SinB_Renderer_->AnimationBindEnd("Sin_B", std::bind(&Player::SinSkillUpdate, this, std::placeholders::_1));
	SinC_Renderer_->AnimationBindEnd("Sin_C", std::bind(&Player::SinSkillUpdate, this, std::placeholders::_1));
	SinD_Renderer_->AnimationBindEnd("Sin_D", std::bind(&Player::SinSkillUpdate, this, std::placeholders::_1));

	SinA_Renderer_->AnimationBindFrame("Sin_A", std::bind(&Player::SinSkillSoundUpdate, this, std::placeholders::_1));
	SinB_Renderer_->AnimationBindFrame("Sin_B", std::bind(&Player::SinSkillSoundUpdate, this, std::placeholders::_1));
	SinC_Renderer_->AnimationBindFrame("Sin_C", std::bind(&Player::SinSkillSoundUpdate, this, std::placeholders::_1));
	SinD_Renderer_->AnimationBindFrame("Sin_D", std::bind(&Player::SinSkillSoundUpdate, this, std::placeholders::_1));

	LevelUpEffRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	LevelUpEffRenderer_->GetTransform().SetLocalScale({ 904.f, 904.f });
	LevelUpEffRenderer_->CreateFrameAnimationFolder("LevelUp", FrameAnimation_DESC("LevelUp", 0.09f));
	LevelUpEffRenderer_->AnimationBindEnd("LevelUp", std::bind(&Player::LevelUpEffectEnd, this, std::placeholders::_1));
	LevelUpEffRenderer_->ChangeFrameAnimation("LevelUp");
	LevelUpEffRenderer_->Off();
}

void Player::Update(float _DeltaTime)
{
	StateManager.Update(_DeltaTime);

	PlayerMove(_DeltaTime);
	CollisionCheck();

	DebugModeOnOff();
	StagePixelCheck();

	SkillSinLoop();
	LevelUpUpdate();

	if (true == GameEngineInput::GetInst()->IsDown("Test"))
	{
		Player::MainPlayer_->AddExp(50.f);
		ContentsUI::MainUI->ExpBarUpdate(Player::MainPlayer_->GetExp(), 100.f);
	}
}

void Player::End()
{
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


	//	TextOut(GameEngineWindow::GetHDC(), GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().x + 40.f, GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().x - 30.f, PosX.c_str(), static_cast<int>(PosX.length()));
	//	TextOut(GameEngineWindow::GetHDC(), GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().x + 40.f, GetLevel()->GetMainCameraActor()->GetTransform().GetWorldPosition().y - 10.f, PosY.c_str(), static_cast<int>(PosY.length()));
	//}
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

	MiddleColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y));
	BottomDownColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y) + 36.f);	// 36, 32, 30, 17, 23, 23, 15, 15
	BottomColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y) + 32.f);	// 발 밑 픽셀의 값을 얻어온다
	BottomUpColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y) + 30.f);	// 발보다 조금위
	TopColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().x, -(GetTransform().GetWorldPosition().y) - 17.f);
	float4 LeftColor = MapTexture_->GetPixelToFloat4(static_cast<float>(GetTransform().GetWorldPosition().ix() - 23.f), static_cast<float>(-GetTransform().GetWorldPosition().iy()) + 15.f);
	float4 RightColor = MapTexture_->GetPixelToFloat4(static_cast<float>(GetTransform().GetWorldPosition().ix() + 23.f), static_cast<float>((-GetTransform().GetWorldPosition().iy()) + 15.f));

	
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
	float4 Color = MapTexture_->GetPixelToFloat4(static_cast<float>(GetTransform().GetWorldPosition().ix()), static_cast<float>(-GetTransform().GetWorldPosition().iy()));

	if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{
		// 다음 레벨
		if (true == Color.CompareInt4D(float4{ 1.0f, 0.0f, 1.0f, 1.0f }))
		{
			GameEngineSound::SoundPlayControl("Portal.mp3", 0);

			//GameEngineSound::SoundPlayOneShot("Portal.mp3");

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
			GameEngineSound::SoundPlayControl("Portal.mp3", 0);

			//GameEngineSound::SoundPlayOneShot("Portal.mp3");

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

void Player::CollisionCheck()
{
	if ("Ladder" == StateManager.GetCurStateStateName()
		|| "Rope" == StateManager.GetCurStateStateName())
	{
		return;
	}

	if (true == IsHit)
	{
		PlayerCollision_->Off();
		DamageTime_ += GameEngineTime::GetDeltaTime();	// 시간을 잰다

		// 깜빡이기
		PlayerRenderer_->GetColorData().MulColor = { 0.6f, 0.6f, 0.6f };

		if (0.08f < DamageTime_)
		{
			PlayerRenderer_->GetColorData().MulColor = { 1.f, 1.f, 1.f };
		}
		if (0.16f < DamageTime_)
		{
			PlayerRenderer_->GetColorData().MulColor = { 0.6f, 0.6f, 0.6f };
		}
		if (0.24f < DamageTime_)
		{
			PlayerRenderer_->GetColorData().MulColor = { 1.f, 1.f, 1.f };
		}
		if (0.32f < DamageTime_)
		{
			PlayerRenderer_->GetColorData().MulColor = { 0.6f, 0.6f, 0.6f };
		}
		if (0.40f < DamageTime_)
		{
			PlayerRenderer_->GetColorData().MulColor = { 1.f, 1.f, 1.f };
		}
		if (0.48f < DamageTime_)
		{
			PlayerRenderer_->GetColorData().MulColor = { 0.6f, 0.6f, 0.6f };
		}
		if (0.56f < DamageTime_)
		{
			PlayerRenderer_->GetColorData().MulColor = { 1.f, 1.f, 1.f };
		}
		if (0.64f < DamageTime_)
		{
			PlayerRenderer_->GetColorData().MulColor = { 0.6f, 0.6f, 0.6f };
		}
		if (0.72f < DamageTime_)
		{
			PlayerRenderer_->GetColorData().MulColor = { 1.f, 1.f, 1.f };
		}
		if (0.80f < DamageTime_)
		{
			PlayerRenderer_->GetColorData().MulColor = { 0.6f, 0.6f, 0.6f };
		}
		if (0.88f < DamageTime_)
		{
			PlayerRenderer_->GetColorData().MulColor = { 1.f, 1.f, 1.f };
		}

		if (1.5f < DamageTime_)							// 2초가 지났으면 다시 IsHit -> Off
		{
			IsHit = false;
			DamageTime_ = 0.0f;							// 시간 리셋

			StateManager.ChangeState("Idle");
			return;
		}
	}

	// 몬스터 
	if (true == PlayerCollision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MONSTER, CollisionType::CT_OBB2D))
	{
		IsHit = true;

		TakeDamage(3.f);
		ContentsUI::MainUI->HPBarUpdate(CurHP_, MaxHP_);
		
		StateManager.ChangeState("Damaged");
		return;
	}

	// 몬스터 스킬 
	if (true == PlayerCollision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MONSTERSKILL, CollisionType::CT_OBB2D))
	{
		IsHit = true;

		TakeDamage(2.f);
		ContentsUI::MainUI->HPBarUpdate(CurHP_, MaxHP_);

		StateManager.ChangeState("Damaged");
		return;
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

bool Player::IsUpDownMoveKey()
{
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp")
		|| true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		return true;
	}

	return false;
}

bool Player::IsSkillKey()
{
	if (CurMP_ == 0.f)
	{
		return false;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Skill_Q")
		|| true == GameEngineInput::GetInst()->IsDown("Skill_W")
		|| true == GameEngineInput::GetInst()->IsDown("Skill_E")
		|| true == GameEngineInput::GetInst()->IsDown("Skill_R"))
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
				&& StateManager.GetCurStateStateName() != "Damaged"
				&& StateManager.GetCurStateStateName() != "Die")
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
				&& StateManager.GetCurStateStateName() != "Damaged"
				&& StateManager.GetCurStateStateName() != "Die")
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
	if (true == IsUseSinSkill)
	{
		return;
	}

	UseMP(3.f);
	ContentsUI::MainUI->MPBarUpdate(CurMP_, MaxMP_);

	if (true == GameEngineInput::GetInst()->IsDown("Skill_Q"))
	{
		GameEngineSound::SoundPlayOneShot("InUse.mp3");

		InA_Renderer_->On();
		InB_Renderer_->On();
		InSkillCollision_->On();

		CurSkill_ = PLAYERSKILL::SKILL_IN;

		AddAccTime(Time_);
		StateManager.ChangeState("SkillAtt");
		return;
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Skill_W"))
	{
		//GameEngineSound::SoundPlayOneShot("PaUse.mp3");
		GameEngineSound::SoundPlayControl("PaUse.mp3", 0);

		PaA_Renderer_->On();
		PaSkillCollision_->On();

		CurSkill_ = PLAYERSKILL::SKILL_PA;
		IsUsePaSkill = true;

		StateManager.ChangeState("Jump");
		return;
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Skill_E"))
	{
		GameEngineSound::SoundPlayOneShot("JiUse.mp3");

		JiA_Renderer_->On();
		JiB_Renderer_->On();
		JiB_Renderer_->ChangeFrameAnimation("Ji_B");
		JiSkillCollision_->On();
		CurSkill_ = PLAYERSKILL::SKILL_JI;

		StateManager.ChangeState("SkillAtt");
		return;
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Skill_R"))
	{
		GameEngineSound::SoundPlayOneShot("SinUse.mp3");

		SinStart_Renderer_->On();
		CurSkill_ = PLAYERSKILL::SKILL_SIN;

		StateManager.ChangeState("Idle");
		return;
	}
}

void Player::SkillSinLoop()
{

	if (SinLoopTime_ > 1.5f)
	{
		IsSinLoopStart = false;
		SinLoopTime_ = 0.0f;	// 초기화
	}

	if (SinEndTime_ > 0.7f
		&& true == IsSinLoopEnd)	// 완전히 끝
	{
		IsSinLoopEnd = false;
		IsUseSinSkill = false;

		SinLoopTime_ = 0.0f;
		SinDCollision_->Off();
	}

	if (true == IsSinLoopStart)
	{
		SinLoopTime_ += GameEngineTime::GetDeltaTime();
	}

	if (true == IsSinLoopEnd)
	{
		SinEndTime_ += GameEngineTime::GetDeltaTime();
	}

	if (true == IsUseSinSkill)
	{
		SkillPositionUpdate(CurSkill_);

		if (false == IsSinLoopStart
			&& false == IsSinLoopEnd)
		{
			switch (CurSkill_)
			{
			case PLAYERSKILL::SKILL_SINA:
				break;
			case PLAYERSKILL::SKILL_SINB:
			{
				SinB_Renderer_->On();
			}
			break;
			case PLAYERSKILL::SKILL_SINC:
			{
				SinC_Renderer_->On();
			}
			break;
			case PLAYERSKILL::SKILL_SIND:
			{
				SinD_Renderer_->On();
			}
			break;
			}
		}
	}
}

void Player::LevelUpUpdate()
{
	if (100.f <= CurExp_)
	{
		CurLevel_ += 1;
		IsLevelUp = true;
		GameEngineSound::SoundPlayOneShot("LevelUp.mp3");

		LevelUpEffRenderer_->On();
		LevelUpEffRenderer_->GetTransform().SetWorldPosition({GetPosition().x, GetPosition().y + 160.f});

		CurExp_ = 0.f;
		ContentsUI::MainUI->ExpBarUpdate(Player::MainPlayer_->GetExp(), 100.f);
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
	break;
	case PLAYERSKILL::SKILL_PA:
	{
		IsUsePaSkill = false;

		PaA_Renderer_->Off();
		PaSkillCollision_->Off();
	}
	break;
	case PLAYERSKILL::SKILL_JI:
	{
		//AddAccTime(Time_);
		JiA_Renderer_->Off();
		JiB_Renderer_->Off();
		//JiB_Renderer_->ChangeFrameAnimation("Ji_C");
		
		JiC_Renderer_->On();

		//JiC_Renderer_->On();
		JiSkillCollision_->Off();
	}
	break;
	case PLAYERSKILL::SKILL_SIN:
	{
		IsUseSinSkill = true;

		SinStart_Renderer_->Off();
		
		SinA_Renderer_->On();
		SinSkillFrameCount_ = 1;
		CurSkill_ = PLAYERSKILL::SKILL_SINA;
	}
	break;
	case PLAYERSKILL::SKILL_SINA:
	{

	}
	break;
	}

	StateManager.ChangeState("Idle");
	return;
}

void Player::SkillPositionUpdate(PLAYERSKILL _CurSkill)
{
	float4 Pos = GetPosition();

	//if ("SkillAtt" != StateManager.GetCurStateStateName()
	//	&& "Jump" != StateManager.GetCurStateStateName())
	//{
	//	return;
	//}

	switch (_CurSkill)
	{
	case PLAYERSKILL::SKILL_IN:
	{
		if (ACTORDIR::RIGHT == PrevDir_)
		{
			InA_Renderer_->GetTransform().PixLocalNegativeX();
			InA_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x - 20.f, GetPosition().y, (int)ZOrder::SKILLFRONT});

			InB_Renderer_->GetTransform().PixLocalNegativeX();
			InB_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x + 130.f, GetPosition().y, (int)ZOrder::SKILLFRONT });
		}
		else
		{
			InA_Renderer_->GetTransform().PixLocalPositiveX();
			InA_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x + 20.f, GetPosition().y, (int)ZOrder::SKILLFRONT });

			InB_Renderer_->GetTransform().PixLocalPositiveX();
			InB_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x - 130.f, GetPosition().y, (int)ZOrder::SKILLFRONT });
		}
	}
		break;
	case PLAYERSKILL::SKILL_PA:
	{
		if (ACTORDIR::RIGHT == PrevDir_)
		{
			PaA_Renderer_->GetTransform().PixLocalNegativeX();
			PaA_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x + 150.f, PrevPosition_.y + 20.f, (int)ZOrder::SKILLBACK });
			PaSkillCollision_->GetTransform().SetWorldPosition({ GetPosition().x + 200.f, PrevPosition_.y + 20.f, (int)ZOrder::SKILLBACK });
		}
		else
		{
			PaA_Renderer_->GetTransform().PixLocalPositiveX();
			PaA_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x - 150.f, PrevPosition_.y + 20.f, (int)ZOrder::SKILLBACK });
			PaSkillCollision_->GetTransform().SetWorldPosition({ GetPosition().x - 200.f, PrevPosition_.y + 20.f, (int)ZOrder::SKILLBACK });
		}
	}
		break;
	case PLAYERSKILL::SKILL_JI:
	{
		JiA_Renderer_->GetTransform().SetWorldPosition({ PrevPosition_.x, PrevPosition_.y + 60.f, (int)ZOrder::SKILLBACK });
		JiB_Renderer_->GetTransform().SetWorldPosition({ PrevPosition_.x, PrevPosition_.y + 110.f, (int)ZOrder::SKILLBACK });
		JiC_Renderer_->GetTransform().SetWorldPosition({ PrevPosition_.x - 4.5f, PrevPosition_.y + 139.f, (int)ZOrder::SKILLBACK });
	}
		break;
	case PLAYERSKILL::SKILL_SIN:
	{
		SinStart_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x,  GetPosition().y + 100.f, (int)ZOrder::SKILLBACK });
	}
	break;
	case PLAYERSKILL::SKILL_SINA:
	{
		if (ACTORDIR::RIGHT == CurDir_)
		{
			SinA_Renderer_->GetTransform().PixLocalNegativeX();
			SinA_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x + 200.f, GetPosition().y + 40.f, (int)ZOrder::SKILLBACK });
			SinACollision_->GetTransform().SetWorldPosition({ GetPosition().x + 200.f, GetPosition().y + 20.f, (int)ZOrder::SKILLBACK });
		}
		else
		{
			SinA_Renderer_->GetTransform().PixLocalPositiveX();
			SinA_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x - 200.f, GetPosition().y + 40.f, (int)ZOrder::SKILLBACK });
			SinACollision_->GetTransform().SetWorldPosition({ GetPosition().x - 200.f, GetPosition().y + 20.f, (int)ZOrder::SKILLBACK });
		}
	}

		break;
	case PLAYERSKILL::SKILL_SINB:
	{
		if (ACTORDIR::RIGHT == CurDir_)
		{
			SinB_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x + 200.f, GetPosition().y + 200.f, (int)ZOrder::SKILLBACK });
			SinBCollision_->GetTransform().SetWorldPosition({ GetPosition().x - 200.f, GetPosition().y + 170.f, (int)ZOrder::SKILLBACK });
		}
		else
		{
			SinB_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x + 200.f, GetPosition().y + 200.f, (int)ZOrder::SKILLBACK });
			SinBCollision_->GetTransform().SetWorldPosition({ GetPosition().x - 200.f, GetPosition().y + 100.f, (int)ZOrder::SKILLBACK });
		}
		
	}
		break;
	case PLAYERSKILL::SKILL_SINC:
	{
		if (ACTORDIR::RIGHT == CurDir_)
		{
			SinC_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x + 200.f, GetPosition().y + 100.f, (int)ZOrder::SKILLBACK });
			SinCCollision_->GetTransform().SetWorldPosition({ GetPosition().x + 200.f, GetPosition().y + 100.f, (int)ZOrder::SKILLBACK });
		}
		else
		{
			SinC_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x - 200.f, GetPosition().y + 100.f, (int)ZOrder::SKILLBACK });
			SinCCollision_->GetTransform().SetWorldPosition({ GetPosition().x - 200.f, GetPosition().y + 100.f, (int)ZOrder::SKILLBACK });
		}

	}
		break;
	case PLAYERSKILL::SKILL_SIND:
	{
		float4 CamPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();
		SinD_Renderer_->GetTransform().SetWorldPosition({ CamPos.x, CamPos.y, (int)ZOrder::SKILLFRONT});
	}
		break;
	case PLAYERSKILL::MAX:
		break;
	default:
		break;
	}
}

void Player::JiCFrameEnd(const FrameAnimation_DESC& _Info)
{
	JiC_Renderer_->Off();
}

void Player::SinSkillUpdate(const FrameAnimation_DESC& _Info)
{
	switch (CurSkill_)
	{
	case PLAYERSKILL::SKILL_SINA:
	{
		SinA_Renderer_->Off();
		SinACollision_->Off();

		IsSinLoopStart = true;
		CurSkill_ = PLAYERSKILL::SKILL_SINB;
		SinSkillFrameCount_ = 1;
	}
	break;
	case PLAYERSKILL::SKILL_SINB:
	{
		SinB_Renderer_->Off();
		SinBCollision_->Off();

		IsSinLoopStart = true;
		CurSkill_ = PLAYERSKILL::SKILL_SINC;
		SinSkillFrameCount_ = 1;
	}
	break;
	case PLAYERSKILL::SKILL_SINC:
	{
		SinC_Renderer_->Off();
		SinCCollision_->Off();

		IsSinLoopStart = true;
	//	SinDCollision_->On();		// ** 수정 필요
		CurSkill_ = PLAYERSKILL::SKILL_SIND;
		SinSkillFrameCount_ = 1;
	}
		break;
	case PLAYERSKILL::SKILL_SIND:
	{
		IsSinLoopEnd = true;

		SinD_Renderer_->Off();
		SinDCollision_->On();		// ** 수정 필요
	}
		break;
	case PLAYERSKILL::MAX:
		break;
	default:
		break;	
	}
}

void Player::SinSkillSoundUpdate(const FrameAnimation_DESC& _Info)
{
	if (SinSkillFrameCount_ == 0)
	{
		switch (CurSkill_)
		{
		case PLAYERSKILL::SKILL_SINA:
		{
			SinACollision_->On();
			GameEngineSound::SoundPlayOneShot("SinAttack1.mp3");
		}
		break;
		case PLAYERSKILL::SKILL_SINB:
		{
			SinBCollision_->On();
			GameEngineSound::SoundPlayOneShot("SinAttack2.mp3");
		}
		break;
		case PLAYERSKILL::SKILL_SINC:
		{
			SinCCollision_->On();
			GameEngineSound::SoundPlayOneShot("SinAttack3.mp3");
		}
			break;
		case PLAYERSKILL::SKILL_SIND:
		{
			GameEngineSound::SoundPlayOneShot("SinAttack4.mp3");
		}
			break;
		default:
			break;
		}
	}

	if (SinSkillFrameCount_ < 0)
	{
		SinSkillFrameCount_ = 0;
	}

	SinSkillFrameCount_ -= 1;

}

void Player::DoubleJumpEnd(const FrameAnimation_DESC& _Info)
{
	ChoA_Renderer_->Off();
}

void Player::LevelUpEffectEnd(const FrameAnimation_DESC& _Info)
{
	LevelUpEffRenderer_->Off();
}

