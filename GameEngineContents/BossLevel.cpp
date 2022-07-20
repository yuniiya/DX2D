#include "PreCompile.h"
#include "BossLevel.h"
#include <GameEngineCore/GEngine.h>

BossLevel::BossLevel() 
{
}

BossLevel::~BossLevel() 
{
}

void BossLevel::Start()
{
	SetCamera();

	SetBackGround("Back_Boss.png");
	SetStage("Stage_Boss.png");
}

void BossLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsPress("CameraLeft"))
	{
		GetMainCameraActorTransform().SetLocalMove(-GetMainCameraActorTransform().GetRightVector() * 500 * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("CameraRight"))
	{
		GetMainCameraActorTransform().SetLocalMove(GetMainCameraActorTransform().GetRightVector() * 500 * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("CameraUp"))
	{
		GetMainCameraActorTransform().SetLocalMove(GetMainCameraActorTransform().GetUpVector() * 500 * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("CameraDown"))
	{
		GetMainCameraActorTransform().SetLocalMove(-GetMainCameraActorTransform().GetUpVector() * 500 * _DeltaTime);
	}
}

void BossLevel::End()
{
}
