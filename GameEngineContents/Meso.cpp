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
	ChangeState(ItemMoveState::Drop);

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
	Item::Update(_DeltaTime);
}

void Meso::PickUpItemCheck(GameEngineTextureRenderer* _Renderer, float _DeltaTime)
{
	if (_Renderer->GetPixelData().MulColor.a <= 0)
	{
		_Renderer->GetPixelData().MulColor.a = 0;
	}

	// �� �ֿ�����
	if (PickTime_ > 0.5f)
	{
		Player::MainPlayer_->AddPlayerMeso(GetMesoAmount());

		PlayerMeso_ = Player::MainPlayer_->GetPlayerMeso();
		Inventory::MainInventory_->GetContentsFontMeso()->GetNormalFontRenderer()->SetText(std::to_string(PlayerMeso_));
		Inventory::MainInventory_->GetContentsFontMeso()->SetComma();

		Death();	// ����

		PickTime_ = 0.f;
		IsPick = false;
	}
	if (true == IsPick)
	{
		PickTime_ += _DeltaTime;
		_Renderer->GetPixelData().MulColor.a -= _DeltaTime * 2.f;
	}
}

void Meso::TimeAttackUpdate(GameEngineTextureRenderer* _Renderer, float _DeltaTime)
{
	PickUpItem(_Renderer, _DeltaTime);

	if (nullptr == _Renderer)
	{
		return;
	}

	if (true == IsPick)
	{
		return;
	}

	if (Time_ > 15.f)
	{
		_Renderer->GetPixelData().MulColor.a -= _DeltaTime * 1.8f;

		if (_Renderer->GetPixelData().MulColor.a < 0)
		{
			Time_ = 0.f;
			_Renderer->GetPixelData().MulColor.a = 0;
			Death();
		}
	}
}

void Meso::DropStart()
{
	Item::DropStart();
}

void Meso::FloatStart()
{
	Item::FloatStart();
}

void Meso::DropUpdate(float _DeltaTime)
{
	// ��� �ð� üũ
	DropTime_ += _DeltaTime;
	// �ȼ� üũ ��� ���� ������� ���� ü����
	if (true == IsGround)
	{
		MoveDir_ = 0.f;
		ChangeState(ItemMoveState::Float);
		return;
	}
	GetTransform().SetWorldMove(MoveDir_ * _DeltaTime);
	// ó�� ��������� ��, ���� �̵��ߴٰ� 0.8�� �� �Ʒ��� �ٿ�
	if (DropTime_ > 0.4f)
	{
		MoveDir_.y -= 15.f;
		StagePixelCheck();
	}
}

void Meso::FloatUpdate(float _DeltaTime)
{
	UpDownMove(_DeltaTime);
	PickUpItemCheck(Renderer_, _DeltaTime);
	TimeAttackUpdate(Renderer_, _DeltaTime);

}

