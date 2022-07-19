#include "PreCompile.h"
#include "CactusLevel.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "MapBackGround.h"
#include "Enums.h"

CactusLevel::CactusLevel() 
{
}

CactusLevel::~CactusLevel() 
{
}

void CactusLevel::Start()
{
	SetCamera();

	BackGround_ = CreateActor<MapBackGround>();
	BackGroundRenderer_ = BackGround_->GetRenderer();
	BackGroundRenderer_->SetTexture("Back_Cactus.png");
	BackGroundRenderer_->GetTransform().SetLocalScale({1280 ,720});
}

void CactusLevel::Update(float _DeltaTime)
{
}

void CactusLevel::End()
{
}
