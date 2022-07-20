#include "PreCompile.h"
#include "CactusLevel.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineBase/GameEngineInput.h>

CactusLevel::CactusLevel() 
{
}

CactusLevel::~CactusLevel() 
{
}

void CactusLevel::Start()
{
	SetCamera();

	SetBackGround("Back_Cactus.png");
	SetStage("Stage_Cactus.png");
}

void CactusLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Desert");
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

void CactusLevel::End()
{
}
