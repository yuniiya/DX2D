#include "PreCompile.h"
#include "GlobalLevel.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "MapBackGround.h"
#include "MapStage.h"
#include "Enums.h"

GlobalLevel::GlobalLevel() 
{
}

GlobalLevel::~GlobalLevel() 
{
}

void GlobalLevel::SetCamera()
{
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetTransform().SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

}

void GlobalLevel::SetBackGround(const std::string& _Name)
{
	MapBackGround* BackGroundActor = CreateActor<MapBackGround>(GAMEOBJGROUP::BACKGROUND);
	GameEngineTextureRenderer* BackGroundRenderer = BackGroundActor->GetRenderer();

	BackGroundRenderer->SetTexture(_Name);
	BackGroundRenderer->ScaleToTexture();
}

void GlobalLevel::SetStage(const std::string& _Name)
{
	MapStage* StageActor = CreateActor<MapStage>(GAMEOBJGROUP::STAGE);
	GameEngineTextureRenderer* StageRenderer_ = StageActor->GetRenderer();

	StageRenderer_->SetTexture(_Name);
	StageRenderer_->ScaleToTexture();
}

