#include "PreCompile.h"
#include "SelectUI.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>

SelectUI::SelectUI() 
	: PrevButton_(nullptr)
	, InfoUI_(nullptr)
	, PlayerObjUI_(nullptr)
	, Player_(nullptr)
	, PlayerSelectEffect_(nullptr)
	, PlayerMouseOverEfect_(nullptr)
	, NullPlayer1_(nullptr)
	, NullEffect1_(nullptr)
	, GameStartButton_(nullptr)
	, PrevButtonCol_(nullptr)
	, PlayerCol_(nullptr)
	, GameStartButtonCol_(nullptr)
	, GameStart(false)
	, Time_(0.0f)
	, NullPlayer2_(nullptr)
	, NullPlayer3_(nullptr)
	, NullPlayer4_(nullptr)
	, NullEffect2_(nullptr)
	, NullEffect3_(nullptr)
	, NullEffect4_(nullptr)
	, NullPlayer5_(nullptr)
	, NullEffect5_(nullptr)
{
}

SelectUI::~SelectUI() 
{
}

void SelectUI::Start()
{
	float4 CamPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	PlayerObjUI_ = CreateComponent<GameEngineTextureRenderer>();
	PlayerObjUI_->SetTexture("CharSelect.HoYoung.0.png");
	PlayerObjUI_->GetTransform().SetLocalScale({115.f, 128.f});

	{
		PlayerMouseOverEfect_ = CreateComponent<GameEngineTextureRenderer>();
		PlayerMouseOverEfect_->GetTransform().SetLocalScale({ 184.f, 168.f, 1.f });
		PlayerMouseOverEfect_->CreateFrameAnimationFolder("CharMouseOver", FrameAnimation_DESC("CharMouseOver", 0.15f));

		PlayerMouseOverEfect_->ChangeFrameAnimation("CharMouseOver");
		PlayerMouseOverEfect_->Off();
	}

	{
		Player_ = CreateComponent<GameEngineTextureRenderer>();
		Player_->GetTransform().SetLocalScale({ 80.f, 96.f, 1.f });
		Player_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Player_Idle", 0.5f));
		Player_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Player_Move", 0.2f));
		Player_->GetTransform().PixLocalNegativeX();

		Player_->ChangeFrameAnimation("Idle");

		PlayerCol_ = CreateComponent<GameEngineCollision>();
		PlayerCol_->GetTransform().SetLocalScale({ 80.f, 96.f, 1.f });
		PlayerCol_->GetTransform().SetLocalPosition({ CamPos.x - 405.f, CamPos.y + 80.f });
		PlayerCol_->ChangeOrder(GAMEOBJGROUP::UI);
	}

	{
		PlayerSelectEffect_ = CreateComponent<GameEngineTextureRenderer>();
		PlayerSelectEffect_->GetTransform().SetLocalScale({ 49.f, 205.f, 1.f });
		PlayerSelectEffect_->CreateFrameAnimationFolder("CharSelect", FrameAnimation_DESC("CharSelect", 0.12f));
		PlayerSelectEffect_->ChangeFrameAnimation("CharSelect");
		PlayerSelectEffect_->Off();
	}

	{
		InfoUI_ = CreateComponent<GameEngineTextureRenderer>();
		InfoUI_->SetTexture("CharSelect.charInfo1.png");
		InfoUI_->GetTransform().SetLocalScale({ 194.f * 1.2f, 272.f * 1.2f });
		InfoUI_->Off();
	}

	{
		GameStartButton_ = CreateComponent<GameEngineTextureRenderer>();
		GameStartButton_->SetTexture("GameStartBut.png");
		GameStartButton_->GetTransform().SetLocalScale({ 140.f * 1.2f, 52.f * 1.2f });
		GameStartButton_->Off();

		GameStartButtonCol_ = CreateComponent<GameEngineCollision>();
		GameStartButtonCol_->GetTransform().SetLocalScale({ 140.f * 1.2f, 52.f * 1.2f });
		GameStartButtonCol_->GetTransform().SetLocalPosition({ CamPos.x + 500.f, CamPos.y - 190.f });
		GameStartButtonCol_->ChangeOrder(GAMEOBJGROUP::UI);
	}

	{
		PrevButton_ = CreateComponent<GameEngineTextureRenderer>();
		PrevButton_->SetTexture("Common.BtPreview.normal.0.png");
		PrevButton_->GetTransform().SetLocalScale({ 81.f * 1.2f, 34.f * 1.2f });

		PrevButtonCol_ = CreateComponent<GameEngineCollision>();
		PrevButtonCol_->GetTransform().SetLocalScale({ 81.f * 1.2f, 34.f * 1.2f });
		PrevButtonCol_->GetTransform().SetLocalPosition({ CamPos.x - 592.f, CamPos.y - 235.f });
		PrevButtonCol_->ChangeOrder(GAMEOBJGROUP::UI);
	}
	
	{
		NullPlayer1_ = CreateComponent<GameEngineTextureRenderer>();
		NullPlayer1_->SetTexture("NullChar.png");
		NullPlayer1_->ScaleToTexture();

		NullPlayer2_ = CreateComponent<GameEngineTextureRenderer>();
		NullPlayer2_->SetTexture("NullChar.png");
		NullPlayer2_->ScaleToTexture();

		NullPlayer3_ = CreateComponent<GameEngineTextureRenderer>();
		NullPlayer3_->SetTexture("NullChar.png");
		NullPlayer3_->ScaleToTexture();

		NullPlayer4_ = CreateComponent<GameEngineTextureRenderer>();
		NullPlayer4_->SetTexture("NullChar.png");
		NullPlayer4_->ScaleToTexture();
		NullPlayer4_->GetTransform().PixLocalNegativeX();

		NullPlayer5_ = CreateComponent<GameEngineTextureRenderer>();
		NullPlayer5_->SetTexture("NullChar.png");
		NullPlayer5_->ScaleToTexture();
		NullPlayer5_->GetTransform().PixLocalNegativeX();



		NullEffect1_ = CreateComponent<GameEngineTextureRenderer>();
		NullEffect1_->GetTransform().SetLocalScale({ 62.f, 9.f, 1.f });
		NullEffect1_->CreateFrameAnimationFolder("NullCharEffect", FrameAnimation_DESC("NullCharEffect", 0.13f));
		NullEffect1_->ChangeFrameAnimation("NullCharEffect");

		NullEffect2_ = CreateComponent<GameEngineTextureRenderer>();
		NullEffect2_->GetTransform().SetLocalScale({ 62.f, 9.f, 1.f });
		NullEffect2_->CreateFrameAnimationFolder("NullCharEffect", FrameAnimation_DESC("NullCharEffect", 0.13f));
		NullEffect2_->ChangeFrameAnimation("NullCharEffect");

		NullEffect3_ = CreateComponent<GameEngineTextureRenderer>();
		NullEffect3_->GetTransform().SetLocalScale({ 62.f, 9.f, 1.f });
		NullEffect3_->CreateFrameAnimationFolder("NullCharEffect", FrameAnimation_DESC("NullCharEffect", 0.13f));
		NullEffect3_->ChangeFrameAnimation("NullCharEffect");

		NullEffect4_ = CreateComponent<GameEngineTextureRenderer>();
		NullEffect4_->GetTransform().SetLocalScale({ 62.f, 9.f, 1.f });
		NullEffect4_->CreateFrameAnimationFolder("NullCharEffect", FrameAnimation_DESC("NullCharEffect", 0.13f));
		NullEffect4_->ChangeFrameAnimation("NullCharEffect");

		NullEffect5_ = CreateComponent<GameEngineTextureRenderer>();
		NullEffect5_->GetTransform().SetLocalScale({ 62.f, 9.f, 1.f });
		NullEffect5_->CreateFrameAnimationFolder("NullCharEffect", FrameAnimation_DESC("NullCharEffect", 0.13f));
		NullEffect5_->ChangeFrameAnimation("NullCharEffect");
	}

	PlayerObjUI_->GetTransform().SetLocalPosition({ CamPos.x - 455.f, CamPos.y + 100.f });
	Player_->GetTransform().SetLocalPosition({ CamPos.x - 425.f, CamPos.y + 83.f });
	InfoUI_->GetTransform().SetLocalPosition({ CamPos.x + 500.f, CamPos.y - 70.f });
	GameStartButton_->GetTransform().SetLocalPosition({ CamPos.x + 500.f, CamPos.y - 165.f });
	PlayerMouseOverEfect_->GetTransform().SetLocalPosition({ CamPos.x - 425.f, CamPos.y + 119.f });
	PlayerSelectEffect_->GetTransform().SetLocalPosition({ CamPos.x - 425.f, CamPos.y + 125.f });
	PrevButton_->GetTransform().SetLocalPosition({ CamPos.x - 592.f, CamPos.y - 235.f });

	NullPlayer1_->GetTransform().SetLocalPosition({ CamPos.x - 295.f, CamPos.y + 75.f });
	NullPlayer2_->GetTransform().SetLocalPosition({ CamPos.x - 165.f, CamPos.y + 75.f });
	NullPlayer3_->GetTransform().SetLocalPosition({ CamPos.x - 35.f, CamPos.y + 75.f });
	NullPlayer4_->GetTransform().SetLocalPosition({ CamPos.x + 95.f, CamPos.y + 75.f });
	NullPlayer5_->GetTransform().SetLocalPosition({ CamPos.x + 225.f, CamPos.y + 75.f });

	NullEffect1_->GetTransform().SetLocalPosition({ CamPos.x - 295.f, CamPos.y + 40.f });
	NullEffect2_->GetTransform().SetLocalPosition({ CamPos.x - 165.f, CamPos.y + 40.f });
	NullEffect3_->GetTransform().SetLocalPosition({ CamPos.x - 35.f, CamPos.y + 40.f });
	NullEffect4_->GetTransform().SetLocalPosition({ CamPos.x + 95.f, CamPos.y + 40.f });
	NullEffect5_->GetTransform().SetLocalPosition({ CamPos.x + 225.f, CamPos.y + 40.f });
}

void SelectUI::Update(float _DeltaTime)
{
	CollisionCheck();
}

void SelectUI::End()
{
}

bool SelectUI::MouseCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

void SelectUI::CollisionCheck()
{
	if (true == GameStart)
	{
		Time_ += GameEngineTime::GetDeltaTime();
	}

	if (Time_ >= 0.7f)
	{
		GEngine::ChangeLevel("Ariant");
	}


	if (true == PlayerCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D,
		std::bind(&SelectUI::MouseCollisionCheck, this, std::placeholders::_1, std::placeholders::_2)
	))
	{
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			GameEngineSound::SoundPlayOneShot("CharSelect.mp3");

			Player_->ChangeFrameAnimation("Move");

			InfoUI_->On();
			GameStartButton_->On();
			PlayerMouseOverEfect_->On();
			PlayerSelectEffect_->On();
		}
	}
	else
	{
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			if (true == GameStart)
			{
				return;
			}

			Player_->ChangeFrameAnimation("Idle");

			InfoUI_->Off();
			GameStartButton_->Off();
			PlayerMouseOverEfect_->Off();
			PlayerSelectEffect_->Off();
		}
	}

	if (true == GameStartButtonCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D,
		std::bind(&SelectUI::MouseCollisionCheck, this, std::placeholders::_1, std::placeholders::_2)
	))
	{
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			GameEngineSound::SoundPlayOneShot("GameIn.mp3");

			GameStartButton_->SetTexture("GameStartBut_Pressed.png");
			GameStart = true;
		}
		else
		{
			GameStartButton_->SetTexture("GameStartBut_Mouse.png");

		}
	}
	else
	{
		GameStartButton_->SetTexture("GameStartBut.png");
	}

	if (true == PrevButtonCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D,
		std::bind(&SelectUI::MouseCollisionCheck, this, std::placeholders::_1, std::placeholders::_2)
	))
	{
		if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		{
			PrevButton_->SetTexture("Common.BtPreview.pressed.0.png");

			GameEngineSound::SoundPlayOneShot("ScrollUp.mp3");

			GEngine::ChangeLevel("Login");
		}
		else
		{
			PrevButton_->SetTexture("Common.BtPreview.mouseOver.0.png");

		}
	}
	else
	{
		PrevButton_->SetTexture("Common.BtPreview.normal.0.png");
	}
}
