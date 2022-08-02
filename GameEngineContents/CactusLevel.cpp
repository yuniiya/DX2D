#include "PreCompile.h"
#include "CactusLevel.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include "Player.h"
#include "Mouse.h"

CactusLevel::CactusLevel() 
{
}

CactusLevel::~CactusLevel() 
{
}

void CactusLevel::Start()
{
	SetCollisionMap("ColMap_Cactus2.png");
	SetBackGround("Back_Cactus.png");
	SetStage("Stage_Cactus.png");


	Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player_->GetTransform().SetLocalPosition({ 1200.0f, -600.0f, 0.0f });

	SetPortal({ 111.f, -776.f, 0.0f });
	SetPortal({ 1864.f, -776.f, 0.0f });

	// UI
	ContentsUI* MainUI = CreateActor<ContentsUI>(GAMEOBJGROUP::UI);
	CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);

}

void CactusLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Desert");
	}
	if (GameEngineInput::GetInst()->IsDown("FreeCameraOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	PlayerPos_ = Player_->GetTransform().GetLocalPosition();

	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->GetTransform().SetLocalPosition({ PlayerPos_.x, PlayerPos_.y + 120.f });
	}

	CameraFix({ 2060.f, 1030.f });
}

void CactusLevel::End()
{
}
