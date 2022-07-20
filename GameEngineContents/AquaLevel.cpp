#include "PreCompile.h"
#include "AquaLevel.h"
#include <GameEngineCore/GEngine.h>

AquaLevel::AquaLevel() 
{
}

AquaLevel::~AquaLevel() 
{
}

void AquaLevel::Start()
{
	SetCamera();

	SetBackGround("Back_Aqua.png");
	SetStage("Stage_Aqua.png");
}

void AquaLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Boss");
	}

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

void AquaLevel::End()
{
}
