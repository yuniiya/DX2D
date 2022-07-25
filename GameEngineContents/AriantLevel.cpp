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

	SetBackGround("Back_Ariant.png");
	//SetStage("Stage_Ariant.png");
	MapStage* StageActor = CreateActor<MapStage>(GAMEOBJGROUP::STAGE);
	GameEngineTextureRenderer* StageRenderer_ = StageActor->GetRenderer();

	StageRenderer_->SetTexture("Stage_Ariant.png");
	StageRenderer_->ScaleToTexture();
	StageRenderer_->GetTransform().SetLocalPosition({ 0.f, 20.f });

	Player::MainPlayer_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
	Player::MainPlayer_->GetTransform().SetLocalPosition({ 100.0f, -250.f, 0.0f });
	//Player::MainPlayer_->GetTransform().SetWorldScale(float4(100.0f, 100.f, 100.0f));

	Player::MainPlayer_->SetMapScale(5760, 995);
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

	CameraPos_ = GetMainCameraActor()->GetTransform().GetLocalPosition();
	PlayerPos_ = Player::MainPlayer_->GetTransform().GetLocalPosition();

	GetMainCameraActor()->GetTransform().SetLocalPosition({ PlayerPos_ });

	//LimitCamera({ 5760.f, 995.f });
}

void AriantLevel::End()
{
}

void AriantLevel::BindTime()
{
}
