#include "PreCompile.h"
#include "BossLevel.h"
#include <GameEngineCore/GEngine.h>

BossLevel::BossLevel() 
{
}

BossLevel::~BossLevel() 
{
}

void BossLevel::Start()
{
	SetCamera();

	SetBackGround("Back_Boss.png");
	SetStage("Stage_Boss.png");
}

void BossLevel::Update(float _DeltaTime)
{
}

void BossLevel::End()
{
}
