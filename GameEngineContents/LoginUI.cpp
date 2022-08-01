#include "PreCompile.h"
#include "LoginUI.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>

LoginUI::LoginUI()
	: LoginBackUI_(nullptr)
	, LoginUI_(nullptr)
	, LogoUI_(nullptr)
{
}

LoginUI::~LoginUI()
{
}


void LoginUI::Start()
{
	LoginBackUI_ = CreateComponent<GameEngineTextureRenderer>();
	LoginBackUI_->SetTexture("LoginUI2.png");
	LoginBackUI_->GetTransform().SetLocalScale({ 365.2f, 310.2f});

	LoginUI_ = CreateComponent<GameEngineTextureRenderer>();
	LoginUI_->SetTexture("Title_new.BtLogin.normal.0.png");
	LoginUI_->GetTransform().SetLocalScale({300.f, 53.f});

	LogoUI_ = CreateComponent<GameEngineTextureRenderer>();
	LogoUI_->SetTexture("Intro1.png");
	LogoUI_->GetTransform().SetLocalScale({ 113.f * 0.7f, 131.f * 0.7f});

}

void LoginUI::Update(float _DeltaTime)
{
	float4 CamPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	LoginBackUI_->GetTransform().SetLocalPosition(float4{ CamPos.x + 5.f, CamPos.y });
	LoginUI_->GetTransform().SetLocalPosition(float4{ CamPos.x + 5.f, CamPos.y - 60.f});
	LogoUI_->GetTransform().SetLocalPosition(float4{ CamPos.x + 600.f, CamPos.y + 316.f});
}

void LoginUI::End()
{
}