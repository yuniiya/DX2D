#include "PreCompile.h"
#include "TitleLogo.h"

TitleLogo::TitleLogo() 
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->CreateFrameAnimationFolder("Title", FrameAnimation_DESC("Title", 0.1f));
	Renderer_->ChangeFrameAnimation("Title");
	Renderer_->GetTransform().SetLocalScale({ 1280.f, 720.f });
}

void TitleLogo::Update(float _DeltaTime)
{
	Renderer_->AnimationBindEnd("Title", std::bind(&TitleLogo::BindLevelChange, this, std::placeholders::_1));
}

void TitleLogo::BindLevelChange(const FrameAnimation_DESC& _Info)
{
	GEngine::ChangeLevel("Login");
}

