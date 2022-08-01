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
	, NullPlayer_(nullptr)
	, NullEffect_(nullptr)
	, GameStartButton_(nullptr)
{
}

SelectUI::~SelectUI() 
{
}

void SelectUI::Start()
{
	PlayerObjUI_ = CreateComponent<GameEngineTextureRenderer>();
	PlayerObjUI_->SetTexture("CharSelect.HoYoung.0.png");
	PlayerObjUI_->GetTransform().SetLocalScale({115.f, 128.f});

	{
		Player_ = CreateComponent<GameEngineTextureRenderer>();
		Player_->GetTransform().SetLocalScale({ 80.f, 96.f, 1.f });
		Player_->CreateFrameAnimationFolder("Idle", FrameAnimation_DESC("Player_Idle", 0.5f));
		Player_->CreateFrameAnimationFolder("Move", FrameAnimation_DESC("Player_Move", 0.2f));
		Player_->GetTransform().PixLocalNegativeX();

		Player_->ChangeFrameAnimation("Idle");
	}

	InfoUI_ = CreateComponent<GameEngineTextureRenderer>();
	InfoUI_->SetTexture("CharSelect.charInfo1.png");
	InfoUI_->GetTransform().SetLocalScale({ 194.f * 1.5f, 272.f * 1.5f });

	GameStartButton_ = CreateComponent<GameEngineTextureRenderer>();
	GameStartButton_->SetTexture("GameStartBut.png");
	GameStartButton_->GetTransform().SetLocalScale({ 140.f * 1.5f, 52.f * 1.5f });
}

void SelectUI::Update(float _DeltaTime)
{
	float4 CamPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	PlayerObjUI_->GetTransform().SetLocalPosition({ CamPos.x - 435.f, CamPos .y + 100.f});
	Player_->GetTransform().SetLocalPosition({ CamPos.x - 405.f, CamPos.y + 80.f });
	InfoUI_->GetTransform().SetLocalPosition({ CamPos.x + 500.f, CamPos.y - 70.f });
	GameStartButton_->GetTransform().SetLocalPosition({ CamPos.x + 500.f, CamPos.y - 190.f });

}

void SelectUI::End()
{
}
