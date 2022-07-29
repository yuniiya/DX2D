#include "PreCompile.h"
#include "CastleLevel.h"
#include <GameEngineCore/GEngine.h>
#include "MapBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include "Player.h"

CastleLevel::CastleLevel() 
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

	// UI
	ContentsUI* MainUI = CreateActor<ContentsUI>(GAMEOBJGROUP::UI);

	Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player_->GetTransform().SetLocalPosition({ 300.0f, -400.0f, 0.0f });
}

void CastleLevel::Update(float _DeltaTime)
{ 
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Aqua");
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
