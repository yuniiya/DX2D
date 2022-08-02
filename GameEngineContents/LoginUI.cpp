#include "PreCompile.h"
#include "LoginUI.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include "Mouse.h"

LoginUI::LoginUI()
	: LoginBackUI_(nullptr)
	, LoginUI_(nullptr)
	, LogoUI_(nullptr)
	, SoundPlay(false)
	, AlreadyPlay(false)
{
}

LoginUI::~LoginUI()
{
}


void LoginUI::Start()
{
	float4 CamPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	LoginBackUI_ = CreateComponent<GameEngineTextureRenderer>();
	LoginBackUI_->SetTexture("LoginUI2.png");
	LoginBackUI_->GetTransform().SetLocalScale({ 365.2f, 310.2f});

	LoginUI_ = CreateComponent<GameEngineTextureRenderer>();
	LoginUI_->SetTexture("Title_new.BtLogin.normal.0.png");
	LoginUI_->GetTransform().SetLocalScale({300.f, 53.f});

	LoginCol_ = CreateComponent<GameEngineCollision>();
	LoginCol_->GetTransform().SetLocalScale({ 300.f, 53.f });
	LoginCol_->GetTransform().SetLocalPosition(float4{ CamPos.x + 5.f, CamPos.y - 60.f });
	LoginCol_->ChangeOrder(GAMEOBJGROUP::UI);

	LogoUI_ = CreateComponent<GameEngineTextureRenderer>();
	LogoUI_->SetTexture("Intro1.png");
	LogoUI_->GetTransform().SetLocalScale({ 113.f * 0.7f, 131.f * 0.7f});

}

void LoginUI::Update(float _DeltaTime)
{
	float4 CamPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();
	//GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ CamPos.x - 100.f, CamPos.y});	//, CamPos.y + GameEngineWindow::GetScale().y / 2.f 

	LoginBackUI_->GetTransform().SetLocalPosition(float4{ CamPos.x + 5.f, CamPos.y });
	LoginUI_->GetTransform().SetLocalPosition(float4{ CamPos.x + 5.f, CamPos.y - 60.f });
	LogoUI_->GetTransform().SetLocalPosition(float4{ CamPos.x + 600.f, CamPos.y + 316.f });

	CollisionCheck();

	if (true == SoundPlay)
	{
		GameEngineSound::SoundPlayOneShot("BtMouseOver.mp3");
		AlreadyPlay = true;
	}

}

void LoginUI::End()
{
}

bool LoginUI::MouseCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if(true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		LoginUI_->SetTexture("Title_new.BtLogin.pressed.0.png");
	}
	else if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
	{
		LoginUI_->SetTexture("Title_new.BtLogin.mouseOver.0.png");
	}
	else
	{
		LoginUI_->SetTexture("Title_new.BtLogin.mouseOver.0.png");
	}

	if (true == AlreadyPlay)
	{
		SoundPlay = false;
	}
	else
	{// 이전에 재생이 안됐었다
		SoundPlay = true;
	}

	return true;
}

void LoginUI::CollisionCheck()
{
	if (false == LoginCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D,
		std::bind(&LoginUI::MouseCollisionCheck, this, std::placeholders::_1, std::placeholders::_2)
	))
	{
		LoginUI_->SetTexture("Title_new.BtLogin.normal.0.png");
	}
}
