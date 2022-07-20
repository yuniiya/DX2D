#include "PreCompile.h"
#include "CastleLevel.h"
#include <GameEngineCore/GEngine.h>
#include "MapBackGround.h"
#include "Enums.h"
#include <GameEngineBase/GameEngineWindow.h>

CastleLevel::CastleLevel() 
{
}

CastleLevel::~CastleLevel() 
{
}

void CastleLevel::Start()
{
	SetCamera();

	SetBackGround("Back_Castle.png");
	SetStage("Stage_Castle2.png");
}

void CastleLevel::Update(float _DeltaTime)
{ 
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Aqua");
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

void CastleLevel::End()
{
}
