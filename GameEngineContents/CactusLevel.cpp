#include "PreCompile.h"
#include "CactusLevel.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
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
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

	BackGround_ = CreateActor<MapBackGround>();
	BackGround_->GetRenderer()->SetTexture("Back_Cactus.png");
	BackGround_->GetRenderer()->GetTransform().SetLocalScale({2060, 1030});
}

void CactusLevel::Update(float _DeltaTime)
{
}

void CactusLevel::End()
{
}
