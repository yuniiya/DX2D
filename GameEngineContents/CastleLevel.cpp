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

	SetStage("Castle.png");
}

void CastleLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Aqua");
	}
}

void CastleLevel::End()
{
}
