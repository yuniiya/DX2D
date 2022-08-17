#include "PreCompile.h"
#include "ContentsUI.h"
#include "Player.h"

ContentsUI::ContentsUI() 
	: MainBar_(nullptr)
	, ExpBack_(nullptr)
	, QuickSlot_(nullptr)
	, QuickSlotBack_(nullptr)
	, HpBar_(nullptr)
	, MpBar_(nullptr)
	, ExpBar_(nullptr)
	, CurHP_(0)
	, CurMP_(0)
	, CurExp_(0)
{
}

ContentsUI::~ContentsUI() 
{
}

bool ContentsUI::MouseCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

void ContentsUI::CollisionCheck()
{
}

void ContentsUI::MainBarSizeUpdate()
{
	CurHP_ = Player::MainPlayer_->GetHP();
	CurMP_ = Player::MainPlayer_->GetMP();
	CurExp_ = Player::MainPlayer_->GetExp();

	switch (CurHP_)
	{
	case 90:
	{	
		HpBar_->GetTransform().SetLocalScale({ HpBar_->GetTransform().GetLocalScale().x * 0.9f, HpBar_->GetTransform().GetLocalScale().y });
		HpBar_->SetPivot(PIVOTMODE::LEFTTOP);
	}
	break;
	default:
		break;
	}

	float4 Size = HpBar_->GetTransform().GetLocalScale();
}

void ContentsUI::Start()
{
	HpBar_ = CreateComponent<GameEngineTextureRenderer>();
	HpBar_->SetTexture("HP.png");
	HpBar_->ScaleToTexture();

	MpBar_ = CreateComponent<GameEngineTextureRenderer>();
	MpBar_->SetTexture("MP.png");
	MpBar_->ScaleToTexture();

	MainBar_ = CreateComponent<GameEngineTextureRenderer>();
	MainBar_->SetTexture("mainBar2.png");
	MainBar_->ScaleToTexture();

	ExpBack_ = CreateComponent<GameEngineTextureRenderer>();
	ExpBack_->SetTexture("ExpBarBack.png");
	ExpBack_->GetTransform().SetLocalScale({ 1280.f, 16.f });

	ExpBar_ = CreateComponent<GameEngineTextureRenderer>();
	ExpBar_->SetTexture("ExpBar.png");
	ExpBar_->GetTransform().SetLocalScale({ 1272.f, 12.5f });
	ExpPos_ = ExpBar_->GetTransform().GetLocalScale();

	//ExpBar_->GetTransform().SetLocalScale({ ExpPos_.x * 0.7f, ExpPos_.y });

	QuickSlotBack_ = CreateComponent<GameEngineTextureRenderer>();
	QuickSlotBack_->SetTexture("QuickSlotBack.png");
	QuickSlotBack_->ScaleToTexture();

	QuickSlot_ = CreateComponent<GameEngineTextureRenderer>();
	QuickSlot_->SetTexture("QuickSlot.png");
	QuickSlot_->ScaleToTexture();
}

void ContentsUI::Update(float _DeltaTime)
{
	float4 CamPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	HpBar_->GetTransform().SetLocalPosition(float4{ CamPos.x + 10.5f, CamPos.y - 308.f });
	MpBar_->GetTransform().SetLocalPosition(float4{ CamPos.x + 10.5f, CamPos.y - 325.f });

	MainBar_->GetTransform().SetLocalPosition(float4{ CamPos.x, CamPos.y - 308.f });
	QuickSlotBack_->GetTransform().SetLocalPosition(float4{ CamPos.x + 465.f, CamPos.y - 308.f });
	QuickSlot_->GetTransform().SetLocalPosition(float4{ CamPos.x + 465.f, CamPos.y - 308.f });
	ExpBack_->GetTransform().SetLocalPosition(float4{ CamPos.x + 2.f, CamPos.y - 352.f });
	ExpBar_->GetTransform().SetLocalPosition(float4{ CamPos.x + 1.f , CamPos.y - 352.5f });

	MainBarSizeUpdate();

}

