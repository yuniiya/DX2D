#include "PreCompile.h"
#include "LoginUI.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include "Mouse.h"
#include "Fade.h"
#include "TextArea.h"
#include <GameEngineCore/GameEngineFontRenderer.h>

LoginUI::LoginUI()
	: LoginBackUI_(nullptr)
	, LoginUI_(nullptr)
	, LogoUI_(nullptr)
	, SoundPlay(false)
	, MapleID_(nullptr)
	, IDArea_(nullptr)
	, PWArea(nullptr)
	, IDAreaCol_(nullptr)
	, PWAreaCol_(nullptr)
	, LoginCol_(nullptr)
	, Notice0_(nullptr)
	, Notice1_(nullptr)
	, IsCorrectID_(false)
	, IsCorrectPW_(false)
	, IsNoticeEnd0_(false)
	, IsNoticeEnd1_(false)
	, IsChageLevel_(false)
	, Time_(0.f)
{
}

LoginUI::~LoginUI()
{
}


void LoginUI::ResetLoginUI()
{
	// 레벨이 바뀌면 전체 리셋
	IDText_->ReSetText();
	PWText_->ReSetText();
	IDArea_->Off();
	PWArea->Off();
	IsNoticeEnd0_ = false;
	IsNoticeEnd1_ = false;
	IsCorrectID_ = false;
	IsCorrectPW_ = false;
	Notice0_->Off();
	Notice1_->Off();
}

void LoginUI::Start()
{
	GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::NOTICE});
	UserID_ = "yuniya";
	UserPW_ = "1111";

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
		IDAreaCol_->GetTransform().SetLocalScale({ 201.f * 0.8f, 45.f * 0.9f});
		IDAreaCol_->GetTransform().SetLocalPosition(float4{ CamPos.x - 40.f, CamPos.y + 69.f });
		IDAreaCol_->ChangeOrder(GAMEOBJGROUP::UI);
	}

	{
		PWArea = CreateComponent<GameEngineTextureRenderer>();
		PWArea->SetTexture("Title_new.PW2.png");
		PWArea->GetTransform().SetLocalScale({ 201.f, 45.f });
		PWArea->Off();

		PWAreaCol_ = CreateComponent<GameEngineCollision>();
		PWAreaCol_->GetTransform().SetLocalScale({ 201.f * 0.8f, 45.f * 0.9f });
		PWAreaCol_->GetTransform().SetLocalPosition(float4{ CamPos.x - 40.f, CamPos.y + 5.f });
		PWAreaCol_->ChangeOrder(GAMEOBJGROUP::UI);
	}
	SoundPlay = false;

	Notice0_ = CreateComponent<GameEngineUIRenderer>();
	Notice0_->SetTexture("Notice0.png");
	Notice0_->GetTransform().SetLocalScale({249.f * 1.3f, 142.f * 1.3f });
	Notice0_->ChangeCamera(CAMERAORDER::UICAMERA);
	Notice0_->GetTransform().SetLocalPosition({ CamPos.x + 5.f, CamPos.y, (int)ZOrder::NOTICE });
	Notice0_->Off();

	Notice1_ = CreateComponent<GameEngineUIRenderer>();
	Notice1_->SetTexture("Notice1.png");
	Notice1_->GetTransform().SetLocalScale({ 249.f * 1.3f, 142.f * 1.3f });
	Notice1_->ChangeCamera(CAMERAORDER::UICAMERA);
	Notice1_->GetTransform().SetLocalPosition({ CamPos.x + 5.f, CamPos.y, (int)ZOrder::NOTICE });
	Notice1_->Off();

	LoginBackUI_->GetTransform().SetLocalPosition(float4{ CamPos.x + 5.f, CamPos.y });
	LoginUI_->GetTransform().SetLocalPosition(float4{ CamPos.x + 5.f, CamPos.y - 60.f });
	LogoUI_->GetTransform().SetLocalPosition(float4{ CamPos.x + 600.f, CamPos.y + 316.f });
	MapleID_->GetTransform().SetLocalPosition(float4{ CamPos.x - 72.f, CamPos.y + 98.f });

	IDArea_->GetTransform().SetLocalPosition(float4{ CamPos.x - 45.f, CamPos.y + 57.f });
	PWArea->GetTransform().SetLocalPosition(float4{ CamPos.x - 45.f, CamPos.y + 5.f });

	IDText_ = GetLevel()->CreateActor<TextArea>();
	IDText_->TextAreaInit({ 200.0f, 23.0f }, 13);
	IDText_->GetTransform().SetLocalPosition(float4{ CamPos.x - 45.f, CamPos.y + 57.f, (int)ZOrder::FONT });
	IDText_->SetTextPosition({ 510.f, 300.f });
	IDText_->SetLoginTextType(LoginTextType::ID);

	PWText_ = GetLevel()->CreateActor<TextArea>();
	PWText_->TextAreaInit({ 200.0f, 23.0f }, 13);
	PWText_->GetTransform().SetLocalPosition(float4{ CamPos.x - 45.f, CamPos.y + 5.f, (int)ZOrder::FONT });
	PWText_->SetTextPosition({ 510.f, 340.f });
	PWText_->SetLoginTextType(LoginTextType::PW);


}

void LoginUI::Update(float _DeltaTime)
{
	if (true == IsChageLevel_)
	{
		Time_ += _DeltaTime;
	}

	if (Time_ >= 0.2f)
	{
		IsChageLevel_ = false;
		Time_ = 0.f;

		GameEngineSound::SoundPlayOneShot("ScrollUp.mp3");
		GEngine::ChangeLevel("Select");
	}

	CollisionCheck();

	if (UserID_ == IDText_->GetText())
	{
		IsCorrectID_ = true;

	}
	else
	{
		IsCorrectID_ = false;

	}

	if (UserPW_ == PWText_->GetText())
	{
		IsCorrectPW_ = true;
	}
	else
	{
		IsCorrectPW_ = false;
	}
}

void LoginUI::End()
{
}

void LoginUI::LevelStartEvent()
{
	ResetLoginUI();
}

void LoginUI::LevelEndEvent()
{
	ResetLoginUI();
}

bool LoginUI::MouseCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
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
			LoginUI_->SetTexture("Title_new.BtLogin.pressed.0.png");

			if (true == IDText_->GetText().empty() || true == PWText_->GetText().empty())
			{
				if (false == PWText_->GetText().empty())
				{
					PWText_->ReSetText();
				}
				if (false == IDText_->GetText().empty())
				{
					IDText_->ReSetText();
				}
				GameEngineSound::SoundPlayOneShot("DlgNotice.mp3");
				Notice0_->On();
			}
			else if (false == IsCorrectPW_/* || false == IsCorrectID_*/)
			{
				IDText_->ReSetText();
				PWText_->ReSetText();
				if (true == Notice0_->IsUpdate())
				{
					Notice0_->Off();
				}
				GameEngineSound::SoundPlayOneShot("DlgNotice.mp3");
				Notice1_->On();
			}
			else if (false == IsCorrectID_)
			{
				IDText_->ReSetText();
				PWText_->ReSetText();
				if (true == Notice1_->IsUpdate())
				{
					Notice1_->Off();
				}
				GameEngineSound::SoundPlayOneShot("DlgNotice.mp3");
				Notice0_->On();
			}
			
			if (true == IsCorrectID_ && true == IsCorrectPW_)
			{
				// 레벨이 바뀌면 전체 리셋
				IsChageLevel_ = true;
			}
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
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			if (true == Notice0_->IsUpdate())
			{		
				Notice0_->Off();
			}
			if (true == Notice1_->IsUpdate())
			{
				Notice1_->Off();
			}
		}
		LoginUI_->SetTexture("Title_new.BtLogin.normal.0.png");

	}


	if (true == IDAreaCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D,
		std::bind(&LoginUI::MouseCollisionCheck, this, std::placeholders::_1, std::placeholders::_2)
	))
	{
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			// 글자없는 텍스처
			IDArea_->On();
		}
	
	}

	else
	{
		// 글자있는 텍스처 -> 입력 중인 글자가 없을 때만 출력
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			// 입력된 텍스트가 없을때만 
			if (false == IDText_->IsTextOn_)
			{
				IDArea_->Off();
			}
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
			if (false == PWText_->IsTextOn_)
			{
				PWArea->Off();
			}
		}
	}

}
