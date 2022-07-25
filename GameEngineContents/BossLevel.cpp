#include "PreCompile.h"
#include "BossLevel.h"
#include <GameEngineCore/GEngine.h>
#include "MapStage.h"
#include "MapBackGround.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "Enums.h"

BossLevel::BossLevel()
	: StageActor_(nullptr)
	, StageRenderer_(nullptr)
{
}

BossLevel::~BossLevel() 
{
}

void BossLevel::Start()
{
	MapSizeReturn(1978.f, 379.f);
	SetCamera();

	//SetBackGround("Back_Boss.png");
	{
		MapBackGround* BackGroundActor = CreateActor<MapBackGround>(GAMEOBJGROUP::BACKGROUND);
		GameEngineTextureRenderer* BackGroundRenderer = BackGroundActor->GetRenderer();

		BackGroundRenderer->SetTexture("Back_Boss.png");
		BackGroundRenderer->GetTransform().SetLocalScale({ 1978.f * 1.2f, 379.f * 1.2f });
	}

	{
		StageActor_ = CreateActor<MapStage>((int)GAMEOBJGROUP::STAGE);
		StageRenderer_ = StageActor_->CreateComponent<GameEngineTextureRenderer>();
		StageRenderer_->GetTransform().SetLocalScale({ 1978.f * 1.2f, 379.f * 1.2f });
		StageRenderer_->CreateFrameAnimationFolder("Stage_Boss", FrameAnimation_DESC("Stage_Boss", 0.2f));
		StageRenderer_->ChangeFrameAnimation("Stage_Boss");
	}

}

void BossLevel::Update(float _DeltaTime)
{
	
}

void BossLevel::End()
{
}
