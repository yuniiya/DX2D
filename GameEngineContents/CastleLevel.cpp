#include "PreCompile.h"
#include "CastleLevel.h"
#include <GameEngineCore/GEngine.h>
#include "MapBackGround.h"
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


}

void CastleLevel::End()
{
}
