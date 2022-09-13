#include "PreCompile.h"
#include "Skill.h"

Skill::Skill() 
	: JiA_Renderer_(nullptr)
	, JiB_Renderer_(nullptr)
	, JiC_Renderer_(nullptr)
	, JiSkillCollision_(nullptr)
	, IsEnd_(false)
{
}

Skill::~Skill() 
{
}

void Skill::Start()
{
	GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::SKILLBACK});

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
	//JiB_Renderer_->GetTransform().SetLocalScale({ 972.f, 398.f });
	JiB_Renderer_->CreateFrameAnimationFolder("Ji_B", FrameAnimation_DESC("Ji_B", 0.04f));
	JiB_Renderer_->CreateFrameAnimationFolder("Ji_C", FrameAnimation_DESC("Ji_C", 0.05f));
	JiB_Renderer_->AnimationBindEnd("Ji_B", std::bind(&Skill::SkillEnd, this, std::placeholders::_1));
	JiB_Renderer_->AnimationBindEnd("Ji_C", std::bind(&Skill::JiCFrameEnd, this, std::placeholders::_1));
	JiB_Renderer_->ChangeFrameAnimation("Ji_B");
	JiB_Renderer_->Off();

	//JiC_Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	//JiC_Renderer_->GetTransform().SetLocalScale({ 1197.f, 508.f });
	//JiC_Renderer_->CreateFrameAnimationFolder("Ji_C", FrameAnimation_DESC("Ji_C", 0.05f));
	//JiC_Renderer_->AnimationBindEnd("Ji_C", std::bind(&Skill::JiCFrameEnd, this, std::placeholders::_1));
	//JiC_Renderer_->ChangeFrameAnimation("Ji_C");
	//JiC_Renderer_->Off();
}

void Skill::Update(float _DeltaTime)
{
}

void Skill::SkillEnd(const FrameAnimation_DESC& _Info)
{
	JiA_Renderer_->Off();
	//JiB_Renderer_->Off();
	JiB_Renderer_->GetTransform().SetLocalScale({ 1197.f, 508.f });
	JiB_Renderer_->GetTransform().SetLocalPosition({ JiB_Renderer_->GetTransform().GetLocalPosition().x - 5.f
		, JiB_Renderer_->GetTransform().GetLocalPosition().y + 30.f });
	JiB_Renderer_->ChangeFrameAnimation("Ji_C");
	JiSkillCollision_->Off();

	IsEnd_ = true;
}

void Skill::JiCFrameEnd(const FrameAnimation_DESC& _Info)
{
	JiB_Renderer_->Off();

	IsEnd_ = false;
}



