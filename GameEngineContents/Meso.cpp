#include "PreCompile.h"
#include "Meso.h"
#include <GameEngineBase/GameEngineRandom.h>
#include "GameEngineCore/GameEngineFontRenderer.h"
#include "Inventory.h"
#include "ContentsFont.h"

Meso::Meso() 
	: Random_(0)
	, MesoAmount_(0)
	, Renderer_(nullptr)
	, Collision_(nullptr)
	, PlayerMeso_(Player::MainPlayer_->GetPlayerMeso())
{
}

Meso::~Meso() 
{
}

void Meso::Start()
{

	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::ITEM });
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->GetTransform().SetLocalScale({ 33.f, 33.f });	// MesoB

	Renderer_->CreateFrameAnimationFolder("MesoA", FrameAnimation_DESC("MesoA", 0.1f));
	Renderer_->CreateFrameAnimationFolder("MesoB", FrameAnimation_DESC("MesoB", 0.16f));
	Renderer_->CreateFrameAnimationFolder("MesoC", FrameAnimation_DESC("MesoC", 0.16f));
	Renderer_->ChangeFrameAnimation("MesoA");

	Random_ = GameEngineRandom::MainRandom.RandomInt(0, 2);

	switch (Random_)
	{
	case 0:
	{
		Renderer_->ChangeFrameAnimation("MesoA");
		Renderer_->GetTransform().SetLocalScale({ 25.f, 24.f });
		SetMesoAmount(50);
	}
	break;
	case 1:
	{
		Renderer_->ChangeFrameAnimation("MesoB");
		Renderer_->GetTransform().SetLocalScale({ 33.f, 33.f });
		SetMesoAmount(500);
	}
	break;
	case 2:
	{
		Renderer_->ChangeFrameAnimation("MesoC");
		Renderer_->GetTransform().SetLocalScale({ 32.f, 31.f });
		SetMesoAmount(5000);
	}
	break;
	}
}

void Meso::Update(float _DeltaTime)
{
	TimeAttackUpdate(Renderer_);
	PickUpItemCheck(Renderer_);
}

void Meso::PickUpItemCheck(GameEngineTextureRenderer* _Renderer)
{
	// 다 주워졌다
	if (PickTime_ > 0.5f)
	{
		Player::MainPlayer_->AddPlayerMeso(GetMesoAmount());

		PlayerMeso_ = Player::MainPlayer_->GetPlayerMeso();
		Inventory::MainInventory_->GetContentsFontMeso()->GetNoramlFontRenderer()->SetText(std::to_string(PlayerMeso_));
		Inventory::MainInventory_->GetContentsFontMeso()->SetComma();

		Death();	// 저장
		_Renderer->GetPixelData().MulColor.a = 0;

		PickTime_ = 0.f;
		IsPick = false;
	}
	if (true == IsPick)
	{
		PickTime_ += GameEngineTime::GetDeltaTime();
		_Renderer->GetPixelData().MulColor.a -= GameEngineTime::GetDeltaTime() * 3.f;
	}
}

