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
}

void CactusLevel::End()
{
}
