#include "PreCompile.h"
#include "BossLevel.h"
#include <GameEngineCore/GEngine.h>
#include "MapStage.h"
#include "MapBackGround.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "Player.h"

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
	{
		SetBackGround("Back_Boss2.png");
		SetCollisionMap("ColMap_Boss.png");

		{
			StageActor_ = CreateActor<MapStage>((int)GAMEOBJGROUP::STAGE);
			StageRenderer_ = StageActor_->CreateComponent<GameEngineTextureRenderer>();
			StageRenderer_->GetTransform().SetLocalScale({ 1978.f, 730.f });
			StageRenderer_->CreateFrameAnimationFolder("Stage_Boss", FrameAnimation_DESC("Stage_Boss", 0.15f));
			StageRenderer_->ChangeFrameAnimation("Stage_Boss");
			StageRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
		}
	}


	// UI
	ContentsUI* MainUI = CreateActor<ContentsUI>(GAMEOBJGROUP::UI);


	Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player_->GetTransform().SetLocalPosition({ 200.f, -200.0f, 0.0f });

}

void BossLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("DebugModeOnOff"))
	{
		StageRenderer_->IsDebugModeSwitch();
	}

	float4 PlayerPos = Player_->GetTransform().GetLocalPosition();
	float4 CameraPos = GetMainCameraActor()->GetTransform().GetLocalPosition();

	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->GetTransform().SetLocalPosition({ PlayerPos.x, CameraPos.y + 100.f });
	}

	CameraFix({1978.f, 720.f});
}

void BossLevel::End()
{
}
