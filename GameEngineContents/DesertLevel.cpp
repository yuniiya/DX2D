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

}

void DesertLevel::End()
{
}
