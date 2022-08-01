#include "PreCompile.h"
#include "LoginLevel.h"
#include "LoginUI.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "MapBackGround.h"
#include "Mouse.h"

LoginLevel::LoginLevel()
{
}

LoginLevel::~LoginLevel()
{
}


void LoginLevel::Start()
{
	MapBackGround* BackGround_ = CreateActor<MapBackGround>(GAMEOBJGROUP::BACKGROUND);
	GameEngineTextureRenderer* BackGroundRenderer_ = BackGround_->GetRenderer();

	BackGroundRenderer_->SetTexture("LoginBackground.png");
	BackGroundRenderer_->GetTransform().SetLocalScale(GameEngineWindow::GetScale());

	LoginUI* UIActor = CreateActor<LoginUI>(GAMEOBJGROUP::UI);
	CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);

	ShowCursor(false);
}

void LoginLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Select");
	}
	if (GameEngineInput::GetInst()->IsDown("FreeCameraOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}
}

void LoginLevel::End()
{
}