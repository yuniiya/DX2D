#include "PreCompile.h"
#include "GlobalLevel.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include "MapBackGround.h"

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
	MapBackGround* BackGround_ = CreateActor<MapBackGround>();
	GameEngineTextureRenderer* BackGroundRenderer_ = BackGround_->GetRenderer();

	BackGroundRenderer_->SetTexture(_Name);
	//BackGroundRenderer_->GetTransform().SetLocalScale({ 1280 ,720 });
}

