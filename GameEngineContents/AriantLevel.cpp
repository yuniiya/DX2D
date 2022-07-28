#include "PreCompile.h"
#include "AriantLevel.h"
#include <GameEngineCore/GEngine.h>
#include "Player.h"
#include "MapStage.h"


AriantLevel::AriantLevel() 
{
}

AriantLevel::~AriantLevel() 
{
}

void AriantLevel::Start()
{
	SetCamera();
	SetCollisionMap("ColMap_Ariant.png");
	SetBackGround("Back_Ariant.png");
	SetStage("Stage_Ariant.png");
//	UIRenderer_->CreateComponent<GameEngineUIRenderer>();
	
	//UIActor_ = CreateActor<ContentsUI>(GAMEOBJGROUP::UI);
	//UIActor_->SetMainUI();

	{
		ContentsUI* UIActor = CreateActor<ContentsUI>(GAMEOBJGROUP::UI);
		UIActor->SetMainUI();
		//GameEngineUIRenderer* UIRenderer = UIActor->GetUIRenderer();

/*		UIRenderer->SetTexture("mainBar.png");
		UIRenderer->SetPivot(PIVOTMODE::LEFTTOP);
		UIRenderer->GetTransform().SetLocalPosition(float4{ 500.f, -500.f, 0.f });
		UIRenderer->ScaleToTexture()*/;
	}

	float4 Pos = GetUICameraActorTransform().GetLocalPosition() + float4{ 0.f, 300.f };
	GetUICameraActorTransform().SetLocalPosition(Pos);

	Player_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player_->GetTransform().SetLocalPosition({ 200.f, -600.0f, 0.0f });
}

void AriantLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Cactus");
	}

	if (GameEngineInput::GetInst()->IsDown("FreeCameraOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	

	//CameraPos_ = GetMainCameraActor()->GetTransform().GetLocalPosition();
	PlayerPos_ = Player_->GetTransform().GetLocalPosition();

	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->GetTransform().SetLocalPosition({ PlayerPos_.x, PlayerPos_.y + 120.f });
	}

	CameraFix({ 5760.f, 995.f });
}

void AriantLevel::End()
{
	//Player_->GetTransform().SetLocalPosition(float4::ZERO);
}

