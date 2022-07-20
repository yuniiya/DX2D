#include "PreCompile.h"
#include "AriantLevel.h"
#include <GameEngineCore/GEngine.h>

AriantLevel::AriantLevel() 
{
}

AriantLevel::~AriantLevel() 
{
}

void AriantLevel::Start()
{
	SetCamera();
	SetBackGround("Back_Ariant.png");
	SetStage("Stage_Ariant.png");
}

void AriantLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Cactus");
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

void AriantLevel::End()
{
}
