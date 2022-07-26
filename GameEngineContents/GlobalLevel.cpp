#include "PreCompile.h"
#include "GlobalLevel.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "MapBackGround.h"
#include "MapStage.h"
#include "Player.h"
#include "Enums.h"

GlobalLevel::GlobalLevel() 
	: MapSizeX_(0.f)
	, MapSizeY_(0.f)
	, CameraPosX_(0.f)
	, CameraPosY_(0.f)
	, StageRenderer_(nullptr)
	, ColMapRenderer_(nullptr)
{
}

GlobalLevel::~GlobalLevel() 
{
}

void GlobalLevel::Update(float _DeltaTime)
{
}

void GlobalLevel::SetCamera()
{
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetTransform().SetLocalPosition({ 0.f, 0.f, -500.0f });
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);

}

void GlobalLevel::SetBackGround(const std::string& _Name)
{
	MapBackGround* BackGroundActor = CreateActor<MapBackGround>(GAMEOBJGROUP::BACKGROUND);
	GameEngineTextureRenderer* BackGroundRenderer = BackGroundActor->GetRenderer();

	BackGroundRenderer->SetTexture(_Name);
	BackGroundRenderer->ScaleToTexture();
	BackGroundRenderer->SetPivot(PIVOTMODE::LEFTTOP);
}

void GlobalLevel::SetStage(const std::string& _Name)
{
	MapStage* StageActor = CreateActor<MapStage>(GAMEOBJGROUP::STAGE);
	StageRenderer_ = StageActor->GetRenderer();

	StageRenderer_->SetTexture(_Name);
	StageRenderer_->ScaleToTexture();
	StageRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
}

void GlobalLevel::SetCollisionMap(const std::string& _Name)
{
	MapStage* ColMapActor = CreateActor<MapStage>(GAMEOBJGROUP::STAGE);
	ColMapRenderer_ = ColMapActor->GetRenderer();

	ColMapRenderer_->SetTexture(_Name);
	ColMapRenderer_->ScaleToTexture();
	ColMapRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
}


void GlobalLevel::LimitCamera(float4 _MapSize)
{
	//if (nullptr != GetMainCameraActor())
	//{
	//	CameraPos_ = GetMainCameraActor()->GetTransform().GetLocalPosition();
	//	float4 CurCameraPos = GetMainCameraActor()->GetTransform().GetLocalPosition();

	//	float CameraRectX = 1280;
	//	float CameraRectY = 720;

	//	// 왼쪽 X
	//	if (CameraPos_.x <= CameraRectX / 2.f)
	//	{
	//		CurCameraPos.x = (CameraRectX / 2.f) + 5.f;
	//		GetMainCameraActor()->GetTransform().SetLocalPosition(CurCameraPos);
	//	}
	//	// 오른쪽 X
	//	if (_MapSize.x - (CameraRectX / 2.f) <= CameraPos_.x)
	//	{
	//		CurCameraPos.x = _MapSize.x - (CameraRectX / 2.f) - 5.f;
	//		GetMainCameraActor()->GetTransform().SetLocalPosition(CurCameraPos);
	//	}
	//	// 위 Y
	//	if (-(CameraRectY / 2.f) <= CameraPos_.y)
	//	{
	//		CurCameraPos.y = -(CameraRectY / 2.f) - 5.f;
	//		GetMainCameraActor()->GetTransform().SetLocalPosition(CurCameraPos);
	//	}
	//}

	
}
