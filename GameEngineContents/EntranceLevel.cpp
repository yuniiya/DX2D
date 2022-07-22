#include "PreCompile.h"
#include "EntranceLevel.h"
#include <GameEngineCore/GEngine.h>

EntranceLevel::EntranceLevel() 
{
}

EntranceLevel::~EntranceLevel() 
{
}

void EntranceLevel::Start()
{
	SetCamera();
	SetBackGround("Back_Entrance.png");
	SetStage("Stage_Entrance.png");
}

void EntranceLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Castle");
	}


}

void EntranceLevel::End()
{
}
