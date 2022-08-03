#include "PreCompile.h"
#include "LoginUI.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include "Mouse.h"
#include "Fade.h"

LoginUI::LoginUI()
	: LoginBackUI_(nullptr)
	, LoginUI_(nullptr)
	, LogoUI_(nullptr)
	, SoundPlay(false)
	, AlreadyPlay(false)
	, MapleID_(nullptr)
	, IDArea_(nullptr)
	, PWArea(nullptr)
	, IDAreaCol_(nullptr)
	, PWAreaCol_(nullptr)
	, LoginCol_(nullptr)
{
}

LoginUI::~LoginUI()
{
}


void LoginUI::Start()
{
	float4 CamPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	LoginBackUI_ = CreateComponent<GameEngineTextureRenderer>();
	LoginBackUI_->SetTexture("LoginUI3.png");
	LoginBackUI_->GetTransform().SetLocalScale({ 365.2f, 310.2f});

	{
		LoginUI_ = CreateComponent<GameEngineTextureRenderer>();
		LoginUI_->SetTexture("Title_new.BtLogin.normal.0.png");
		LoginUI_->GetTransform().SetLocalScale({ 278.f * 1.1f, 53.f * 1.1f });

		LoginCol_ = CreateComponent<GameEngineCollision>();
		LoginCol_->GetTransform().SetLocalScale({ 300.f, 53.f });
		LoginCol_->GetTransform().SetLocalPosition(float4{ CamPos.x + 5.f, CamPos.y - 60.f });
		LoginCol_->ChangeOrder(GAMEOBJGROUP::UI);
	}


	LogoUI_ = CreateComponent<GameEngineTextureRenderer>();
	LogoUI_->SetTexture("Intro1.png");
	LogoUI_->GetTransform().SetLocalScale({ 113.f * 0.7f, 131.f * 0.7f});

	MapleID_ = CreateComponent<GameEngineTextureRenderer>();
	MapleID_->SetTexture("Title_new.Tab.enabled.0.png");
	MapleID_->GetTransform().SetLocalScale({ 139.f * 1.1f, 32.f * 1.1f});

	{
		IDArea_ = CreateComponent<GameEngineTextureRenderer>();
		IDArea_->SetTexture("Title_new.mapleID2.png");
		IDArea_->GetTransform().SetLocalScale({ 201.f, 45.f });
		IDArea_->Off();

		IDAreaCol_ = CreateComponent<GameEngineCollision>();
		IDAreaCol_->GetTransform().SetLocalScale({ 201.f * 0.8f, 45.f * 0.8f});
		IDAreaCol_->GetTransform().SetLocalPosition(float4{ CamPos.x - 40.f, CamPos.y + 64.f });
		IDAreaCol_->ChangeOrder(GAMEOBJGROUP::UI);
	}

	{
		PWArea = CreateComponent<GameEngineTextureRenderer>();
		PWArea->SetTexture("Title_new.PW2.png");
		PWArea->GetTransform().SetLocalScale({ 201.f, 45.f });
		PWArea->Off();

		PWAreaCol_ = CreateComponent<GameEngineCollision>();
		PWAreaCol_->GetTransform().SetLocalScale({ 201.f * 0.8f, 45.f * 0.8f });
		PWAreaCol_->GetTransform().SetLocalPosition(float4{ CamPos.x - 40.f, CamPos.y + 5.f });
		PWAreaCol_->ChangeOrder(GAMEOBJGROUP::UI);
	}

}

void LoginUI::Update(float _DeltaTime)
{
	float4 CamPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();
	//GetLevel()->GetMainCameraActorTransform().SetLocalPosition({ CamPos.x - 100.f, CamPos.y});	//, CamPos.y + GameEngineWindow::GetScale().y / 2.f 

	LoginBackUI_->GetTransform().SetLocalPosition(float4{ CamPos.x + 5.f, CamPos.y });
	LoginUI_->GetTransform().SetLocalPosition(float4{ CamPos.x + 5.f, CamPos.y - 60.f });
	LogoUI_->GetTransform().SetLocalPosition(float4{ CamPos.x + 600.f, CamPos.y + 316.f });
	MapleID_->GetTransform().SetLocalPosition(float4{ CamPos.x - 72.f, CamPos.y + 98.f });

	IDArea_->GetTransform().SetLocalPosition(float4{ CamPos.x - 45.f, CamPos.y + 57.f });
	PWArea->GetTransform().SetLocalPosition(float4{ CamPos.x - 45.f, CamPos.y + 5.f });

	CollisionCheck();

	//if (true == SoundPlay)
	//{
	//	GameEngineSound::SoundPlayOneShot("BtMouseOver.mp3");
	//	AlreadyPlay = true;
	//}

}

void LoginUI::End()
{
}

bool LoginUI::MouseCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	
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
	if (true == LoginCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D,
		std::bind(&LoginUI::MouseCollisionCheck, this, std::placeholders::_1, std::placeholders::_2)
	))
	{
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			Fade* FadeActor = GetLevel()->CreateActor<Fade>(GAMEOBJGROUP::FADE);
			LoginUI_->SetTexture("Title_new.BtLogin.pressed.0.png");

			GameEngineSound::SoundPlayOneShot("ScrollUp.mp3");
			GEngine::ChangeLevel("Select");

		}
		else if (true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
		{
			LoginUI_->SetTexture("Title_new.BtLogin.mouseOver.0.png");
		}
		else
		{
			LoginUI_->SetTexture("Title_new.BtLogin.mouseOver.0.png");
		}

	}
	else
	{
		LoginUI_->SetTexture("Title_new.BtLogin.normal.0.png");
	}


	if (true == IDAreaCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D,
		std::bind(&LoginUI::MouseCollisionCheck, this, std::placeholders::_1, std::placeholders::_2)
	))
	{
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			IDArea_->On();
		}
	
	}

	else
	{
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			IDArea_->Off();
		}
	}
	if (true == PWAreaCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D,
		std::bind(&LoginUI::MouseCollisionCheck, this, std::placeholders::_1, std::placeholders::_2)
	))
	{
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			PWArea->On();
		}

	}
	else
	{
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			PWArea->Off();
		}
	}

}
