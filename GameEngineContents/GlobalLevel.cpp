#include "PreCompile.h"
#include "GlobalLevel.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include "MapBackGround.h"
#include "MapStage.h"
#include "Portal.h"
#include "Player.h"
#include "Mouse.h"
#include "Inventory.h"

GlobalLevel::GlobalLevel() 
	: MapSizeX_(0.f)
	, MapSizeY_(0.f)
	, CameraPosX_(0.f)
	, CameraPosY_(0.f)
	, StageRenderer_(nullptr)
	, ColMapRenderer_(nullptr)
	, BackRenderer_(nullptr)
	, Inventory_(nullptr)
	, Mouse_(nullptr)
	, ContentsUI_(nullptr)
{
}

GlobalLevel::~GlobalLevel() 
{
}

void GlobalLevel::Start()
{
	// UI
	//Inventory_ = CreateActor<Inventory>((int)GAMEOBJGROUP::UI);
	Mouse_ = CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);
	ContentsUI_ = CreateActor<ContentsUI>((int)GAMEOBJGROUP::UI);
}

void GlobalLevel::Update(float _DeltaTime)
{

}

void GlobalLevel::LevelStartEvent()
{

}

void GlobalLevel::SetCamera()
{
	//GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	//CameraActor->GetTransform().SetLocalPosition({ 0.f, 0.f, -500.0f });
	//CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
}

void GlobalLevel::SetBackGround(const std::string& _Name)
{
	MapBackGround* BackGroundActor = CreateActor<MapBackGround>(GAMEOBJGROUP::BACKGROUND);
	BackRenderer_ = BackGroundActor->GetRenderer();

	BackRenderer_->SetTexture(_Name);
	BackRenderer_->ScaleToTexture();
	BackRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	BackRenderer_->GetTransform().SetLocalPosition(
		{ BackRenderer_->GetTransform().GetLocalPosition().x
		, BackRenderer_->GetTransform().GetLocalPosition().y
		, (int)ZOrder::BACKGROUND });
}

void GlobalLevel::SetStage(const std::string& _Name)
{
	MapStage* StageActor = CreateActor<MapStage>(GAMEOBJGROUP::STAGE);
	StageRenderer_ = StageActor->GetRenderer();

	StageRenderer_->SetTexture(_Name);
	StageRenderer_->ScaleToTexture();
	StageRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	StageRenderer_->GetTransform().SetLocalPosition(
		{ StageRenderer_->GetTransform().GetLocalPosition().x
		, StageRenderer_->GetTransform().GetLocalPosition().y
		, (int)ZOrder::STAGE });
}

void GlobalLevel::SetCollisionMap(const std::string& _Name)
{
	MapStage* ColMapActor = CreateActor<MapStage>(GAMEOBJGROUP::STAGE);
	ColMapRenderer_ = ColMapActor->GetRenderer();

	ColMapRenderer_->SetTexture(_Name);
	ColMapRenderer_->ScaleToTexture();
	ColMapRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	ColMapRenderer_->GetTransform().SetLocalPosition(
		{ ColMapRenderer_->GetTransform().GetLocalPosition().x
		, ColMapRenderer_->GetTransform().GetLocalPosition().y
		, (int)ZOrder::BACKGROUND });
}

void GlobalLevel::SetPortal(float4 _Pos)
{
	Portal* PortalActor = CreateActor<Portal>(GAMEOBJGROUP::OBJ);
	GameEngineTextureRenderer* PortalRenderer = PortalActor->GetPortalRenderer();
	
	PortalRenderer->CreateFrameAnimationFolder("Portal", FrameAnimation_DESC("Portal", 0.08f));
	PortalRenderer->ChangeFrameAnimation("Portal");
	PortalRenderer->GetTransform().SetLocalPosition({ _Pos .x, _Pos.y, (int)ZOrder::PORTAL});
	PortalRenderer->GetTransform().SetLocalScale({104.f, 142.f});
}


void GlobalLevel::CameraFix(float4 _MapSize)
{
	CameraPos_ = GetMainCameraActor()->GetTransform().GetLocalPosition();
	float4 CurCameraPos = CameraPos_;

	float CameraRectX = 1280;
	float CameraRectY = 720;

	// 왼쪽 X
	if (CameraPos_.x <= CameraRectX / 2.f)
	{
		CurCameraPos.x = (CameraRectX / 2.f) + 2.f;	// 밀어준다
		GetMainCameraActor()->GetTransform().SetLocalPosition(CurCameraPos);
	}
	// 오른쪽 X
	if (_MapSize.x - CameraRectX / 2.f <= CameraPos_.x)
	{
		CurCameraPos.x = (_MapSize.x - CameraRectX / 2.f) - 2.f;	// 밀어준다
		GetMainCameraActor()->GetTransform().SetLocalPosition(CurCameraPos);
	}
	//// 위쪽 Y
	if (-( CameraRectY / 2.f) <= CameraPos_.y)
	{
		CurCameraPos.y = -(CameraRectY / 2.f) - 2.f;	// 밀어준다
		GetMainCameraActor()->GetTransform().SetLocalPosition(CurCameraPos);
	}
	if (CameraPos_.y <= -(_MapSize.y) + (CameraRectY / 2.f))
	{
		CurCameraPos.y = -(_MapSize.y - (CameraRectY / 2.f)) + 2.f;
		GetMainCameraActor()->GetTransform().SetLocalPosition(CurCameraPos);
	}
}
