#include "PreCompile.h"
#include "CastleLevel.h"
#include <GameEngineCore/GEngine.h>
#include "MapBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "Player.h"
#include "Mouse.h"

CastleLevel::CastleLevel() 
	: Player_(nullptr)
{
}

CastleLevel::~CastleLevel() 
{
}

void CastleLevel::Start()
{
	SetCollisionMap("ColMap_Castle.png");
	SetBackGround("Back_Castle2.png");
	SetStage("Stage_Castle3.png");

	Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player_->GetTransform().SetLocalPosition({ 300.0f, -400.0f});

	SetPortal({ 273.f, -495.f, 0.0f });

	// UI
	ContentsUI* MainUI = CreateActor<ContentsUI>(GAMEOBJGROUP::UI);
	CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);
}

void CastleLevel::Update(float _DeltaTime)
{ 
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Aqua");
	}
	if (GameEngineInput::GetInst()->IsDown("FreeCameraOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	float4 PlayerPos = Player_->GetTransform().GetLocalPosition();
	float4 CameraPos = GetMainCameraActor()->GetTransform().GetLocalPosition();

	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->GetTransform().SetLocalPosition({ PlayerPos.x, CameraPos.y + 100.f});
	}

	CameraFix({ 1745.f, 730.f });
}

void CastleLevel::End()
{
}
