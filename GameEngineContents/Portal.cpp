#include "PreCompile.h"
#include "Portal.h"

Portal::Portal() 
	: PortalActor_(nullptr)
	, PortalRenderer_(nullptr)
	, PortalCollision_(nullptr)
{
}

Portal::~Portal() 
{
}

void Portal::Start()
{
	PortalRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	PortalRenderer_->CreateFrameAnimationFolder("Portal", FrameAnimation_DESC("Portal", 0.2f));
	PortalRenderer_->ChangeFrameAnimation("Portal");
}

void Portal::Update(float _DeltaTime)
{
}

