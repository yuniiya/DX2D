#include "PreCompile.h"
#include "Meso.h"

Meso::Meso() 
{
}

Meso::~Meso() 
{
}

void Meso::Start()
{
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::ITEM });
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
//	Renderer_->GetTransform().SetLocalScale({25.f, 24.f});		// MesoA
	Renderer_->GetTransform().SetLocalScale({ 33.f, 33.f });	// MesoB

	Renderer_->CreateFrameAnimationFolder("MesoA", FrameAnimation_DESC("MesoA", 0.1f));
	Renderer_->CreateFrameAnimationFolder("MesoB", FrameAnimation_DESC("MesoB", 0.16f));
	Renderer_->ChangeFrameAnimation("MesoB");
	Renderer_->Off();
}

void Meso::Update(float _DeltaTime)
{
	Renderer_->On();
}

