#include "PreCompile.h"
#include "LoginLevel.h"
#include "LoginUI.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineWindow.h>
#include "MapBackGround.h"
#include "Enums.h"

LoginLevel::LoginLevel()
{
}

LoginLevel::~LoginLevel()
{
}


void LoginLevel::Start()
{
	SetCamera();

	MapBackGround* BackGround_ = CreateActor<MapBackGround>(GAMEOBJGROUP::BACKGROUND);
	GameEngineTextureRenderer* BackGroundRenderer_ = BackGround_->GetRenderer();

	//BackGroundRenderer_->SetTexture("Login.png");
	BackGroundRenderer_->GetTransform().SetLocalScale(GameEngineWindow::GetScale());
}

void LoginLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Ariant");
	}
}

void LoginLevel::End()
{
}