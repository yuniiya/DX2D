#include "PreCompile.h"
#include "LoginLevel.h"
#include "LoginUI.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "MapBackGround.h"
#include "Mouse.h"
#include "Fade.h"
#include "GameBgmPlayer.h"

LoginLevel::LoginLevel()
{
}

LoginLevel::~LoginLevel()
{
}


void LoginLevel::Start()
{
	{
		MapBackGround* BackGroundActor = CreateActor<MapBackGround>(GAMEOBJGROUP::BACKGROUND);
		GameEngineTextureRenderer* BackGroundRenderer_ = BackGroundActor->GetRenderer();

		BackGroundRenderer_->SetTexture("LoginBackground.png");
		BackGroundRenderer_->GetTransform().SetLocalScale(GameEngineWindow::GetScale());
		BackGroundRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
		BackGroundRenderer_->GetTransform().SetLocalPosition({
			  BackGroundRenderer_->GetTransform().GetLocalPosition().x - GameEngineWindow::GetScale().x / 2.f
			, BackGroundRenderer_->GetTransform().GetLocalPosition().y + GameEngineWindow::GetScale().y / 2.f
			, (int)ZOrder::BACKGROUND });
	}
	//{
	//	MapBackGround* BackGround_ = CreateActor<MapBackGround>(GAMEOBJGROUP::BACKGROUND);
	//	GameEngineTextureRenderer* BackGroundRenderer_ = BackGround_->GetRenderer();

	//	BackGroundRenderer_->SetTexture("LoginBackground.png");
	//	BackGroundRenderer_->GetTransform().SetLocalScale(GameEngineWindow::GetScale());
	//}


	LoginUI_ = CreateActor<LoginUI>(GAMEOBJGROUP::UI);

	if (nullptr == Mouse::MainMouse_)
	{
		CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);
	}

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

void LoginLevel::LevelStartEvent()
{
	GameBgmPlayer::BgmPlay_->ChangeBgm("Title.mp3");
	Fade* FadeActor = CreateActor<Fade>(GAMEOBJGROUP::FADE);
	if (nullptr != Player::MainPlayer_)
	{
		Player::MainPlayer_->Off();
	}

	if (nullptr != ContentsUI::MainUI_)
	{
		ContentsUI::MainUI_->Off();
	}
}

void LoginLevel::LevelEndEvent()
{
}
