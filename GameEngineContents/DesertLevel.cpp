#include "PreCompile.h"
#include "DesertLevel.h"
#include <GameEngineCore/GEngine.h>

DesertLevel::DesertLevel() 
{
}

DesertLevel::~DesertLevel() 
{
}

void DesertLevel::Start()
{
	SetCamera();

	SetBackGround("Back_Desert.png");
	SetStage("Stage_Desert.png");
}

void DesertLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Entrance");
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

void DesertLevel::End()
{
}
