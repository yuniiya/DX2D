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


}

void AquaLevel::End()
{
}
