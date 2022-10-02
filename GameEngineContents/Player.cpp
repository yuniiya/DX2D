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
#include "Skill.h"


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
	, BottomDownColor(0.0f)
	, BottomColor(0.0f)
	, LeftColor(0.0f)
	, RightColor(0.0f)
	, InA_Renderer_(nullptr)
	, InB_Renderer_(nullptr)
	, InHit_Renderer_(nullptr)
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
	, MaxHP_(100.f)
	, MaxMP_(100.f)
	, MaxExp_(100.f)
	, IsSinLoopEnd(false)
	, SinAttackEnd(false)
	, MoveDir_(0.f)
	, CurLevel_(120.f)
	, IsLevelUp(false)
	, LevelUpEffRenderer_(nullptr)
	, LevelUpCollision_(nullptr)
	, CurMeso_(10000)
	, IsEntranceQuestClear_(false)
	, IsCactusQuestOngoing_(false)
	, IsCactusQuestClear_(false)
	, IsCastleQuestClear_(false)
	, IsCactusQuestEnd_(false)
	, Skill_(nullptr)
	, IsMoveKeyChange_(false)
	, IsStun_(false)
	, IsInvincible_(false)
	, IsSkillLock_(false)
	, MoveKeyChaneTime_(0.f)
	, StunTime_(0.f)
	, SkillLockTime_(0.f)
	, HatChaseRenderer_(nullptr)
	, StunRenderer_(nullptr)
	, SkillLockRenderer_(nullptr)
	, IsChase_(false)
	, MissRenderer_(nullptr)
	, Boss_(nullptr)
	, RedHatRenderer_(nullptr)
	, BlueHatRenderer_(nullptr)
	, IsBlueHat_(false)
	, IsRedHat_(false)
	, IsAriantLevel_(false)
	, IsPrevLevel_(false)
	, NormalPlayerRenderer_(nullptr)
	, RedHatPlayerRenderer_(nullptr)
	, BlueHatPlayerRenderer_(nullptr)
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
		GameEngineInput::GetInst()->CreateKey("Down", VK_NUMPAD0);
		GameEngineInput::GetInst()->CreateKey("Inventory", 'I');

		GameEngineInput::GetInst()->CreateKey("Test", 'T');
		GameEngineInput::GetInst()->CreateKey("Invincible", 'O');

		// 점프 두번 => 초상비
		// 여의선 인 Q
		// 파초풍 천 W
		// 지진쇄 지 E
		// 괴력 R
		GameEngineInput::GetInst()->CreateKey("Skill_Q", 'Q');
		GameEngineInput::GetInst()->CreateKey("Skill_W", 'W');
		GameEngineInput::GetInst()->CreateKey("SKill_E", 'E');
		GameEngineInput::GetInst()->CreateKey("Skill_R", 'R');

		GameEngineInput::GetInst()->CreateKey("1", '1');
		GameEngineInput::GetInst()->CreateKey("2", '2');
		GameEngineInput::GetInst()->CreateKey("SpaceBar", VK_SPACE);

	}

	GetTransform().SetLocalPosition(float4{ 0, 0, (int)ZOrder::PLAYER });
	PlayerCollision_ = CreateComponent<GameEngineCollision>();
	PlayerCollision_->GetTransform().SetLocalScale({ 65.f, 60.f, (int)ZOrder::PLAYER });
	PlayerCollision_->ChangeOrder(GAMEOBJGROUP::PLAYER);

	LevelUpCollision_ = CreateComponent<GameEngineCollision>();
	LevelUpCollision_->GetTransform().SetLocalScale(GameEngineWindow::GetScale());
	LevelUpCollision_->GetTransform().SetLocalPosition({0.f, 100.f});
	LevelUpCollision_->ChangeOrder(GAMEOBJGROUP::LEVELUP);
	LevelUpCollision_->Off();

	PlayerRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	NormalPlayerRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	//NormalPlayerRenderer_->GetTransform().SetLocalScale({ 66.f, 69.f});
	NormalPlayerRenderer_->GetTransform().SetLocalScale({ 200.f, 200.f });
	NormalPlayerRenderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Player_Idle", 0.5f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Player_Move", 0.2f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("Jump", FrameAnimation_DESC("Jump", 0.2f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("JumpAttack", FrameAnimation_DESC("JumpAttack", 0.2f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("Fall", FrameAnimation_DESC("Fall", 0.2f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("Prone", FrameAnimation_DESC("Prone", 0.2f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("ProneStab", FrameAnimation_DESC("ProneStab", 0.37f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("Ladder", FrameAnimation_DESC("Ladder", 0.5f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("Rope", FrameAnimation_DESC("Rope", 0.5f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("LadderA", FrameAnimation_DESC("LadderA", 0.2f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("RopeA", FrameAnimation_DESC("RopeA", 0.2f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("DefaultAtt", FrameAnimation_DESC("Player_Attack1", 0.2f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("SkillAtt", FrameAnimation_DESC("Player_Attack2", 0.2f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("Alert", 0.2f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("KnockBack", FrameAnimation_DESC("Alert", 0.2f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("Die", FrameAnimation_DESC("Player_Die", 0.2f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("DoubleJump", FrameAnimation_DESC("Jump", 0.2f));
	NormalPlayerRenderer_->CreateFrameAnimationFolder("Flying", FrameAnimation_DESC("Flying", 0.3f));
	NormalPlayerRenderer_->ChangeFrameAnimation("Idle");
	PlayerRenderer_ = NormalPlayerRenderer_;

	BlueHatPlayerRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	BlueHatPlayerRenderer_->GetTransform().SetLocalScale({ 200.f, 200.f });
	BlueHatPlayerRenderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("BlueHat_Idle", 0.5f));
	BlueHatPlayerRenderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("BlueHat_Move", 0.2f));
	BlueHatPlayerRenderer_->CreateFrameAnimationFolder("Jump", FrameAnimation_DESC("BlueHat_Jump", 0.2f));
	BlueHatPlayerRenderer_->CreateFrameAnimationFolder("JumpAttack", FrameAnimation_DESC("BlueHat_JumpAttack", 0.2f));
	BlueHatPlayerRenderer_->CreateFrameAnimationFolder("Fall", FrameAnimation_DESC("BlueHat_Fall", 0.2f));
	BlueHatPlayerRenderer_->CreateFrameAnimationFolder("Prone", FrameAnimation_DESC("BlueHat_Prone", 0.2f));
	BlueHatPlayerRenderer_->CreateFrameAnimationFolder("ProneStab", FrameAnimation_DESC("BlueHat_ProneStab", 0.37f));
	BlueHatPlayerRenderer_->CreateFrameAnimationFolder("DefaultAtt", FrameAnimation_DESC("BlueHat_Attack1", 0.2f));
	BlueHatPlayerRenderer_->CreateFrameAnimationFolder("SkillAtt", FrameAnimation_DESC("BlueHat_Attack2", 0.2f));
	BlueHatPlayerRenderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("BlueHat_Alert", 0.2f));
	BlueHatPlayerRenderer_->CreateFrameAnimationFolder("KnockBack", FrameAnimation_DESC("BlueHat_Alert", 0.2f));
	BlueHatPlayerRenderer_->ChangeFrameAnimation("Idle");
	BlueHatPlayerRenderer_->Off();

	RedHatPlayerRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	RedHatPlayerRenderer_->GetTransform().SetLocalScale({ 200.f, 200.f });
	RedHatPlayerRenderer_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("RedHat_Idle", 0.5f));
	RedHatPlayerRenderer_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("RedHat_Move", 0.2f));
	RedHatPlayerRenderer_->CreateFrameAnimationFolder("Jump", FrameAnimation_DESC("RedHat_Jump", 0.2f));
	RedHatPlayerRenderer_->CreateFrameAnimationFolder("Fall", FrameAnimation_DESC("RedHat_Fall", 0.2f));
	RedHatPlayerRenderer_->CreateFrameAnimationFolder("JumpAttack", FrameAnimation_DESC("RedHat_JumpAttack", 0.2f));
	RedHatPlayerRenderer_->CreateFrameAnimationFolder("Prone", FrameAnimation_DESC("RedHat_Prone", 0.2f));
	RedHatPlayerRenderer_->CreateFrameAnimationFolder("ProneStab", FrameAnimation_DESC("RedHat_ProneStab", 0.37f));
	RedHatPlayerRenderer_->CreateFrameAnimationFolder("DefaultAtt", FrameAnimation_DESC("RedHat_Attack1", 0.2f));
	RedHatPlayerRenderer_->CreateFrameAnimationFolder("SkillAtt", FrameAnimation_DESC("RedHat_Attack2", 0.2f));
	RedHatPlayerRenderer_->CreateFrameAnimationFolder("Damaged", FrameAnimation_DESC("RedHat_Alert", 0.2f));
	RedHatPlayerRenderer_->CreateFrameAnimationFolder("KnockBack", FrameAnimation_DESC("RedHat_Alert", 0.2f));
	RedHatPlayerRenderer_->ChangeFrameAnimation("Idle");
	RedHatPlayerRenderer_->Off();


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
	StateManager.CreateStateMember("JumpAttack"
		, std::bind(&Player::JumpSkillAttackUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::JumpSkillAttackStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("DoubleJump"
		, std::bind(&Player::DoubleJumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::DoubleJumpStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Damaged"
		, std::bind(&Player::DamagedUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::DamagedStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("KnockBack"
		, std::bind(&Player::KnockBackUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::KnockBackStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Die"
		, std::bind(&Player::DieUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::DieStart, this, std::placeholders::_1)
	);
	StateManager.CreateStateMember("Flying"
		, std::bind(&Player::FlyingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Player::FlyingStart, this, std::placeholders::_1)
	);

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
	LevelUpEffRenderer_->AnimationBindFrame("LevelUp", std::bind(&Player::LevelUpCollisionStart, this, std::placeholders::_1));
	LevelUpEffRenderer_->ChangeFrameAnimation("LevelUp");
	LevelUpEffRenderer_->Off();

	// 플레이어 머리 위 상태 이상 렌더러
	{
		RedHatRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		RedHatRenderer_->GetTransform().SetLocalScale({ 91.f, 61.f });
		RedHatRenderer_->SetTexture("RedBoss_Hat.png");
		RedHatRenderer_->Off();

		BlueHatRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		BlueHatRenderer_->GetTransform().SetLocalScale({ 91.f, 61.f });
		BlueHatRenderer_->SetTexture("BlueBoss_Hat.png");
		BlueHatRenderer_->Off();

		StunRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		StunRenderer_->GetTransform().SetLocalScale({ 66.f, 18.f });
		StunRenderer_->CreateFrameAnimationFolder("Stun", FrameAnimation_DESC("Stun", 0.09f));
		StunRenderer_->ChangeFrameAnimation("Stun");
		StunRenderer_->GetTransform().SetLocalPosition({ 0.f, 40.f });
		StunRenderer_->Off();

		HatChaseRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		HatChaseRenderer_->GetTransform().SetLocalScale({ 81.f, 92.f });
		HatChaseRenderer_->CreateFrameAnimationFolder("Hat_Chase", FrameAnimation_DESC("Hat_Chase", 0.1f));
		HatChaseRenderer_->ChangeFrameAnimation("Hat_Chase");
		HatChaseRenderer_->GetTransform().SetLocalPosition({ 0.f, 70.f });
		HatChaseRenderer_->Off();

		SkillLockRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		SkillLockRenderer_->GetTransform().SetLocalScale({ 59.f, 42.f });
		SkillLockRenderer_->CreateFrameAnimationFolder("SkillLock", FrameAnimation_DESC("SkillLock", 0.1f));
		SkillLockRenderer_->ChangeFrameAnimation("SkillLock");
		SkillLockRenderer_->GetTransform().SetLocalPosition({ 0.f, 35.f });
		SkillLockRenderer_->Off();

		MissRenderer_ = CreateComponent<GameEngineTextureRenderer>();
		MissRenderer_->GetTransform().SetLocalScale({ 98.f * 0.8f, 38.f * 0.8f });
		MissRenderer_->SetTexture("NoViolet0.Miss.png");
		MissRenderer_->GetTransform().SetLocalPosition({ 0.f, 50.f });
		MissRenderer_->Off();
	}


	//TakeDamage(50.f);
	//UseMP(50.f);

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

	if (MoveKeyChaneTime_ > 1.5f)
	{
		IsMoveKeyChange_ = false;
		MoveKeyChaneTime_ = 0.f;
	}
	if (StunTime_ > 3.f)
	{
		Speed_ = 200.f;
		IsStun_ = false;
		StunTime_ = 0.f;
		StunRenderer_->Off();
	}
	if (SkillLockTime_ > 5.f)
	{
		SkillLockTime_ = 0.f;
		IsSkillLock_ = false;
		SkillLockRenderer_->Off();
	}
	if (true == IsMoveKeyChange_)
	{
		MoveKeyChaneTime_ += _DeltaTime;
	}
	if (true == IsStun_)
	{
		StunTime_ += _DeltaTime;
	}
	if (true == IsSkillLock_)
	{
		SkillLockTime_ += _DeltaTime;
	}
	if (true == IsChase_)
	{
		HatChaseRenderer_->On();
	}
	else
	{
		HatChaseRenderer_->Off();
	}
	if (true == GameEngineInput::GetInst()->IsDown("Test"))
	{
		Player::MainPlayer_->AddExp(30.f);
	}

	// 무적
	if (true == GameEngineInput::GetInst()->IsDown("Invincible"))
	{
		if (true == IsInvincible_)
		{
			IsInvincible_ = false;
			MissRenderer_->Off();
		}
		else
		{
			IsInvincible_ = true;
			MissRenderer_->On();
		}
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

	MiddleColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix(), -(GetTransform().GetWorldPosition().iy()));
	BottomDownColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy() + 36);	// 36, 32, 30, 17, 23, 23, 15, 15
	BottomColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy() + 32);	// 발 밑 픽셀의 값을 얻어온다
	BottomUpColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy() + 30);	// 발보다 조금위
	TopColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy() - 17);
	LeftColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix() - 23, -GetTransform().GetWorldPosition().iy() + 15);
	RightColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix() + 23, (-GetTransform().GetWorldPosition().iy() + 15));
	LeftLeftColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix() - 40, -GetTransform().GetWorldPosition().iy() + 15);
	RightRightColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix() + 40, (-GetTransform().GetWorldPosition().iy() + 15));
	
	// 땅
	if (true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))
	{
		if (true == BottomUpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }))													// 1-1) 발 조금 위가 땅이면 1픽셀 올린다
		{
			//Pos = float4{ 0.f, 1.f, 0.f };x
			GetTransform().SetWorldMove(float4::UP);
		}
	}
	// 허공
	if (true == BottomColor.CompareInt4D(float4{ 1.f, 1.f, 1.f, 1.f })		// 흰색
		|| true == BottomColor.CompareInt4D(float4{ 1.f, 0.f, 1.f, 1.f })	// 마젠타
		|| true == BottomColor.CompareInt4D(float4{ 0.f, 0.f, 1.f, 1.f }))	// 레드
	{
		// 카메라 바깥쪽 이동 막기 - 위
		if (true == TopColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f })
/*			|| true == TopColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f }*/)
		{
			Pos = float4{ 0.f, -1.f, 0.f };
			GetTransform().SetWorldMove(Pos);
	/*		if ("Flying" != StateManager.GetCurStateStateName())
			{
				
			}*/
		}
		else // 허공 -> 땅에 닿을 때까지 내려준다
		{
			if ("Jump" != StateManager.GetCurStateStateName()
				&& "Damaged" != StateManager.GetCurStateStateName()
				&& "JumpAttack" != StateManager.GetCurStateStateName()
				&& "Flying" != StateManager.GetCurStateStateName())
			{
				DownPower_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 5.f;
				GetTransform().SetWorldMove(DownPower_);
			}
			//else if ()
			//{
			//	DownPower_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 2.f;
			//	GetTransform().SetWorldMove(DownPower_);
			//}
			else
			{
				DownPower_ = 0.0f;
			}
		}
	}
	else if (true == BottomColor.CompareInt4D(float4{ 0.f, 1.f, 0.f, 1.f })
			|| true == MiddleColor.CompareInt4D(float4{ 0.f, 1.f, 0.f, 1.f }))	// 레더 쪽으로 점프
	{
		if ("Jump" == StateManager.GetCurStateStateName())
		{
			DownPower_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 5.f;
			GetTransform().SetWorldMove(DownPower_);
		}
	}	
	else if(true == BottomColor.CompareInt4D(float4{ 1.f, 0.f, 0.f, 1.f })
			|| true == MiddleColor.CompareInt4D(float4{ 1.f, 0.f, 0.f, 1.f }))	// 로프 쪽으로 점프
	{
		if ("Jump" == StateManager.GetCurStateStateName())
		{
			DownPower_ += float4::DOWN * GameEngineTime::GetDeltaTime() * 5.f;
			GetTransform().SetWorldMove(DownPower_);
		}
	}	
	else
	{
		DownPower_ = 0.0f;
	}

	if(StateManager.GetCurStateStateName() != "Move")
	{
		if (true == LeftColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }))
		{
			// 왼쪽이 검정이 아닐때까지 오른쪽으로 
			while (true == LeftColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }))
			{
				LeftColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix() - 23, -GetTransform().GetWorldPosition().iy() + 15);
				float4 Pos = float4::RIGHT;
				GetTransform().SetWorldMove(Pos);
			}
		}
		else if (true == RightColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }))
		{
			// 오른쪽이 검정이 아닐때까지
			while (true == RightColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 0.f }))
			{
				RightColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix() + 23, (-GetTransform().GetWorldPosition().iy() + 15));
				float4 Pos = float4::LEFT;
				GetTransform().SetWorldMove(Pos);
			}
		}
	}

	// 포탈, 레더, 로프 
	ObjectPixelCheck();

	return true;
}

void Player::ObjectPixelCheck()
{
	float4 Color = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy());

	if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{
		// 다음 레벨
		if (true == Color.CompareInt4D(float4{ 1.0f, 0.0f, 1.0f, 1.0f }))
		{
			IsPrevLevel_ = false;
			if ("ARIANT" == CurLevelName_)
			{
				GEngine::ChangeLevel("Cactus");
			}
			else if ("ENTRANCE" == CurLevelName_)
			{
				// Entrance 퀘스트 미완료 시 레벨 이동 불가
				if (false == IsEntranceQuestClear_)
				{
					return;
				}
				IsAriantLevel_ = true;
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

			GameEngineSound::SoundPlayOneShot("Portal.mp3");

		}	// 이전 레벨
		else if (true == Color.CompareInt4D(float4{ 0.0f, 0.0f, 1.0f, 1.0f }))
		{
			IsPrevLevel_ = true;
			if ("ARIANT" == CurLevelName_)
			{
				IsAriantLevel_ = true;
				GEngine::ChangeLevel("Entrance");
			}
			else if ("ENTRANCE" == CurLevelName_)
			{
				IsAriantLevel_ = true;
				GEngine::ChangeLevel("Ariant");
			}
			else if ("CASTLE" == CurLevelName_)
			{
				IsAriantLevel_ = true;
				GEngine::ChangeLevel("Entrance");
			}
			else if ("CACTUS" == CurLevelName_)
			{
				IsAriantLevel_ = false;
				GEngine::ChangeLevel("Ariant");
			}
			else if ("DESERT" == CurLevelName_)
			{
				//Player::MainPlayer_->GetTransform().SetLocalPosition({ 1864.f, -776.f, (int)ZOrder::PLAYER });
				GEngine::ChangeLevel("Cactus");
			}
			else if ("AQUA" == CurLevelName_)
			{
				//Player::MainPlayer_->GetTransform().SetLocalPosition({ 1489.f, -542.f, (int)ZOrder::PLAYER });
				GEngine::ChangeLevel("Desert");
			}

			GameEngineSound::SoundPlayOneShot("Portal.mp3");
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
	if (true == IsInvincible_)
	{
		return;
	}
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
		PlayerRenderer_->GetPixelData().MulColor = { 0.6f, 0.6f, 0.6f };

		if (0.08f < DamageTime_)
		{
			PlayerRenderer_->GetPixelData().MulColor = { 1.f, 1.f, 1.f };
		}
		if (0.16f < DamageTime_)
		{
			PlayerRenderer_->GetPixelData().MulColor = { 0.6f, 0.6f, 0.6f };
		}
		if (0.24f < DamageTime_)
		{
			PlayerRenderer_->GetPixelData().MulColor = { 1.f, 1.f, 1.f };
		}
		if (0.32f < DamageTime_)
		{
			PlayerRenderer_->GetPixelData().MulColor = { 0.6f, 0.6f, 0.6f };
		}
		if (0.40f < DamageTime_)
		{
			PlayerRenderer_->GetPixelData().MulColor = { 1.f, 1.f, 1.f };
		}
		if (0.48f < DamageTime_)
		{
			PlayerRenderer_->GetPixelData().MulColor = { 0.6f, 0.6f, 0.6f };
		}
		if (0.56f < DamageTime_)
		{
			PlayerRenderer_->GetPixelData().MulColor = { 1.f, 1.f, 1.f };
		}
		if (0.64f < DamageTime_)
		{
			PlayerRenderer_->GetPixelData().MulColor = { 0.6f, 0.6f, 0.6f };
		}
		if (0.72f < DamageTime_)
		{
			PlayerRenderer_->GetPixelData().MulColor = { 1.f, 1.f, 1.f };
		}
		if (0.80f < DamageTime_)
		{
			PlayerRenderer_->GetPixelData().MulColor = { 0.6f, 0.6f, 0.6f };
		}
		if (0.88f < DamageTime_)
		{
			PlayerRenderer_->GetPixelData().MulColor = { 1.f, 1.f, 1.f };
		}
		
		if (1.3f < DamageTime_)							// 2초가 지났으면 다시 IsHit -> Off
		{
			IsHit = false;
			DamageTime_ = 0.0f;							// 시간 리셋

			//StateManager.ChangeState("Idle");
			//return;
		}
	}

	// 몬스터 
	if (true == PlayerCollision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MONSTER, CollisionType::CT_OBB2D))
	{
		// 블루 A : 스킬 봉인 
		if (true == PlayerCollision_->IsCollision(CollisionType::CT_OBB2D, BossAttackType::BlueAtt_A, CollisionType::CT_OBB2D))
		{
			IsSkillLock_ = true;
			SkillLockRenderer_->On();
		}
		IsHit = true;

		TakeDamage(3.f);
		StateManager.ChangeState("Damaged");
		return;
	}

	// 몬스터 스킬 
	if (true == PlayerCollision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MONSTERSKILL, CollisionType::CT_OBB2D))
	{
		IsHit = true;

		TakeDamage(2.f);
		StateManager.ChangeState("Damaged");
		return;
	}

	////////////// Boss
	// 모자
	if (true == PlayerCollision_->IsCollision(CollisionType::CT_OBB2D, BossAttackType::Hat, CollisionType::CT_OBB2D))
	{
		IsStun_ = true;
		IsHit = true;
		StunRenderer_->On();

		//TakeDamage(2.f);
		StateManager.ChangeState("Damaged");
		return;
	}
	// 노멀 A : 2초간 상하좌우 조작 바뀜
	if (true == PlayerCollision_->IsCollision(CollisionType::CT_OBB2D, BossAttackType::Att_A, CollisionType::CT_OBB2D))
	{
	//	IsMoveKeyChange_ = true;
		IsHit = true;

		TakeDamage(2.f);
		StateManager.ChangeState("Damaged");
		return;
	}
	// 노멀 B : 넉백, 3초 스턴
	else if (true == PlayerCollision_->IsCollision(CollisionType::CT_OBB2D, BossAttackType::Att_B, CollisionType::CT_OBB2D))
	{
		IsStun_ = true;
		IsHit = true;
		StunRenderer_->On();

		TakeDamage(2.f);
		StateManager.ChangeState("KnockBack");
		return;
	}
	// 레드 B : 세 번 공격
	else if (true == PlayerCollision_->IsCollision(CollisionType::CT_OBB2D, BossAttackType::RedAtt_B, CollisionType::CT_OBB2D))
	{
		IsHit = true;

		TakeDamage(2.f);
		StateManager.ChangeState("Damaged");
		return;
	}
	// 레드 A : 한 번 내려치기, 슬로우
	else if (true == PlayerCollision_->IsCollision(CollisionType::CT_OBB2D, BossAttackType::RedAtt_A, CollisionType::CT_OBB2D))
	{
		IsHit = true;

		TakeDamage(2.f);
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
	if (true == IsStun_)
	{
		Speed_ = 0.f;
	}
	if (CurDir_ == ACTORDIR::NONE)
	{
		CanMove = true;
	}

	if (true == CanMove)
	{
		// 좌우 조작 바뀜
		if (true == IsMoveKeyChange_)
		{
			if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
			{
				CurDir_ = ACTORDIR::LEFT;

				if (StateManager.GetCurStateStateName() != "Prone"
					&& StateManager.GetCurStateStateName() != "ProneStab"
					&& StateManager.GetCurStateStateName() != "Ladder"
					&& StateManager.GetCurStateStateName() != "Rope"
					&& StateManager.GetCurStateStateName() != "Damaged"
					&& StateManager.GetCurStateStateName() != "Die")
				{
					GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed_ * _DeltaTime);
				}
			}
			if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
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
		else
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
	}

	if ("Ladder" != StateManager.GetCurStateStateName()
		&& "Rope" != StateManager.GetCurStateStateName())
	{
		PlayerRendererChange();
		DirCheck(PlayerRenderer_, CurDir_);
	}

	// 보스 레벨 모자

	//if (true == IsRedHat_)
	//{
	//	if (true == BlueHatRenderer_->IsUpdate())
	//	{
	//		
	//		BlueHatRenderer_->Off();
	//	}
	//	RedHatRenderer_->On();
	//	if (ACTORDIR::LEFT == CurDir_)
	//	{
	//		RedHatRenderer_->GetTransform().PixLocalPositiveX();
	//		RedHatRenderer_->GetTransform().SetLocalPosition({ 0.f, 34.f});
	//	}
	//	else if (ACTORDIR::RIGHT == CurDir_)
	//	{
	//		RedHatRenderer_->GetTransform().PixLocalNegativeX();
	//		RedHatRenderer_->GetTransform().SetLocalPosition({ 0.f, 34.f });
	//	}
	//}
	//else if (true == IsBlueHat_)
	//{
	//	if (true == RedHatRenderer_->IsUpdate())
	//	{
	//		RedHatRenderer_->Off();
	//	}
	//	BlueHatRenderer_->On();
	//	if (ACTORDIR::LEFT == CurDir_)
	//	{
	//		BlueHatRenderer_->GetTransform().PixLocalPositiveX();
	//		BlueHatRenderer_->GetTransform().SetLocalPosition({ 0.f, 34.f });
	//	}
	//	else if (ACTORDIR::RIGHT == CurDir_)
	//	{
	//		BlueHatRenderer_->GetTransform().PixLocalNegativeX();
	//		BlueHatRenderer_->GetTransform().SetLocalPosition({ 0.f, 34.f });
	//	}
	//}
}

void Player::PlayerRendererChange()
{
	if (true == IsRedHat_)
	{
		if (true == BlueHatPlayerRenderer_->IsUpdate())
		{
			BlueHatPlayerRenderer_->Off();
		}
		if (true == PlayerRenderer_->IsUpdate())
		{
			PlayerRenderer_->Off();
		}
		RedHatPlayerRenderer_->On();
		PlayerRenderer_ = RedHatPlayerRenderer_;
	}
	else if (true == IsBlueHat_)
	{
		if (true == RedHatPlayerRenderer_->IsUpdate())
		{
			RedHatPlayerRenderer_->Off();
		}
		if (true == PlayerRenderer_->IsUpdate())
		{
			PlayerRenderer_->Off();
		}
		BlueHatPlayerRenderer_->On();
		PlayerRenderer_ = BlueHatPlayerRenderer_;
	}
	else
	{
		if (true == BlueHatPlayerRenderer_->IsUpdate())
		{
			BlueHatPlayerRenderer_->Off();
		}
		if (true == RedHatPlayerRenderer_->IsUpdate())
		{
			RedHatPlayerRenderer_->Off();
		}
		NormalPlayerRenderer_->On();
		PlayerRenderer_ = NormalPlayerRenderer_;
	}
	PlayerRenderer_->ChangeFrameAnimation(StateManager.GetCurStateStateName());
	PlayerRenderer_->GetPixelData().MulColor = { 1.f, 1.f, 1.f };
}

void Player::UseSkill()
{
	if (CurMP_ <= 0.f || true == IsSkillLock_)
	{
		return;
	}

	if (true == IsUseSinSkill)
	{
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Skill_Q"))
	{
		GameEngineSound::SoundPlayOneShot("InUse.mp3");

		InA_Renderer_->On();
		InB_Renderer_->On();
		InSkillCollision_->On();

		CurSkill_ = PLAYERSKILL::SKILL_IN;

		UseMP(3.f);
		AddAccTime(Time_);
		StateManager.ChangeState("SkillAtt");
		return;
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Skill_W"))
	{
		if (StateManager.GetCurStateStateName() == "Jump")
		{
			return;
		}
		GameEngineSound::SoundPlayOneShot("PaUse.mp3");

		PaA_Renderer_->On();
		PaSkillCollision_->On();
		
		CurSkill_ = PLAYERSKILL::SKILL_PA;
		IsUsePaSkill = true;
		UseMP(3.f);
		StateManager.ChangeState("JumpAttack");
		return;
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Skill_E"))
	{
		GameEngineSound::SoundPlayOneShot("JiUse.mp3");

		Skill_ = GetLevel()->CreateActor<Skill>();
		Skill_->GetJiARenderer()->On();
		Skill_->GetJiARenderer()->GetTransform().SetLocalPosition({ GetPosition().x, GetPosition().y + 70.f});
		Skill_->GetJiBRenderer()->On();
		Skill_->GetJiBRenderer()->ChangeFrameAnimation("Ji_B");
		Skill_->GetJiBRenderer()->GetTransform().SetLocalPosition({ GetPosition().x, GetPosition().y + 130.f});
		Skill_->GetCollision()->GetTransform().SetLocalPosition({ GetPosition().x, GetPosition().y + 100.f });
		Skill_->GetCollision()->On();
		CurSkill_ = PLAYERSKILL::SKILL_JI;
		UseMP(3.f);
		StateManager.ChangeState("SkillAtt");
		return;
	}
	else if (true == GameEngineInput::GetInst()->IsDown("Skill_R"))
	{
		GameEngineSound::SoundPlayOneShot("SinUse.mp3");

		SinStart_Renderer_->On();
		CurSkill_ = PLAYERSKILL::SKILL_SIN;
		UseMP(3.f);
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
	// 
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
			PaSkillCollision_->GetTransform().SetWorldPosition({ GetPosition().x + 210.f, PrevPosition_.y + 20.f, (int)ZOrder::SKILLBACK });
		}
		else
		{
			PaA_Renderer_->GetTransform().PixLocalPositiveX();
			PaA_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x - 150.f, PrevPosition_.y + 20.f, (int)ZOrder::SKILLBACK });
			PaSkillCollision_->GetTransform().SetWorldPosition({ GetPosition().x - 210.f, PrevPosition_.y + 20.f, (int)ZOrder::SKILLBACK });
		}
	}
		break;
	case PLAYERSKILL::SKILL_JI:
	{
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
			SinBCollision_->GetTransform().SetWorldPosition({ GetPosition().x + 200.f, GetPosition().y + 170.f, (int)ZOrder::SKILLBACK });
		}
		else
		{
			SinB_Renderer_->GetTransform().SetWorldPosition({ GetPosition().x - 200.f, GetPosition().y + 200.f, (int)ZOrder::SKILLBACK });
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
		
		SinD_Renderer_->GetTransform().SetWorldPosition({ CamPos.x, CamPos.y, 1.f});
	}
		break;
	case PLAYERSKILL::MAX:
		break;
	default:
		break;
	}
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
		CurSkill_ = PLAYERSKILL::SKILL_SIND;
		SinSkillFrameCount_ = 1;
	}
		break;
	case PLAYERSKILL::SKILL_SIND:
	{
		IsSinLoopEnd = true;

		SinD_Renderer_->Off();
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

	if (42 == _Info.CurFrame)
	{
		SinDCollision_->On();
	}
	else if (43 == _Info.CurFrame)
	{
		SinDCollision_->Off();
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

void Player::LevelUpCollisionStart(const FrameAnimation_DESC& _Info)
{
	if (12 == _Info.CurFrame)
	{
		LevelUpCollision_->On();
	}
	else if (13 == _Info.CurFrame)
	{
		LevelUpCollision_->Off();
	}
}

