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
}

void AriantLevel::End()
{
}
