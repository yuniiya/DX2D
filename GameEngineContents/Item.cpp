#include "PreCompile.h"
#include "Monster.h"
#include "Item.h"
#include "Player.h"
#include "Inventory.h"

Item::Item() 
	: Renderer_(nullptr)
	, MonsterName_(MONSTERNAME::MAX)
	, IsCreate(false)
	, Time_(0.0f)
	, MoveDir_({0.f, 6.f})
	, MoveTime_(0.0f)
	, IsPick(false)
	, PickTime_(0.f)
	, SlotType_(InventorySlotType::MAX)
	//, Count_(0)
	//, Price_(100)
	//, ItemType_(ItemType::MAX)
{
	ItemState_.ItemType_ = ItemType::MAX;
	ItemState_.Count_ = 0;
	ItemState_.Price_ = 500;
}

Item::~Item() 
{
}

void Item::TimeAttackStart()
{
	IsCreate = true;
}

void Item::TimeAttackUpdate(GameEngineTextureRenderer* _Renderer)
{
	//if (ItemType::MONSTERDROP != ItemType_)
	//{
	//	return;
	//}

	UpDownMove();
	PickUpItem(_Renderer);

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
		_Renderer->GetPixelData().MulColor.a -= GameEngineTime::GetDeltaTime() * 1.8f;
		
		if (_Renderer->GetPixelData().MulColor.a < 0)
		{
			Death();
		}
	}

	if (true == IsCreate)
	{
		Time_ += GameEngineTime::GetDeltaTime();
		MoveTime_ += GameEngineTime::GetDeltaTime();
	}
}

void Item::UpDownMove()
{
	if (0.8f < MoveTime_)
	{
		if (6.f == MoveDir_.y)
		{
			MoveDir_.y = -6.f;
		}
		else if (-6.f == MoveDir_.y)
		{
			MoveDir_.y = 6.f;
		}
		
		MoveTime_ = 0.f;
	}

	GetTransform().SetWorldMove(MoveDir_ * GameEngineTime::GetDeltaTime());
}

void Item::PickUpItem(GameEngineTextureRenderer* _Renderer)
{
	if (nullptr == this)
	{
		return;
	}

	float4 PlayerPos = Player::MainPlayer_->GetPosition();

	if (30.f < abs(PlayerPos.x - GetItemPosition().x))
	{
		return;
	}

	
	if (false == IsPick)
	{
		if (true == GameEngineInput::GetInst()->IsDown("Pick"))
		{
			GameEngineSound::SoundPlayOneShot("PickUpItem.mp3");	// 플레이어쪽으로 끌려오게?
			IsPick = true;

			if (PlayerPos.x < GetItemPosition().x)		// 플레이어가 왼쪽
			{
				MoveDir_ = { -40.f, 20.f };
			}
			else if (PlayerPos.x >= GetItemPosition().x)	// 오른쪽
			{
				MoveDir_ = { 40.f, 20.f };
			}

			GetTransform().SetWorldMove(MoveDir_ * GameEngineTime::GetDeltaTime());

		}

	}
}

void Item::PickUpItemCheck(GameEngineTextureRenderer* _Renderer)
{
	// 다 주워졌다
	if (PickTime_ > 0.5f)
	{
		// ========== 습득 아이템 Inventory쪽 벡터에 넣어두기 ========== //
		//dynamic_cast<GlobalLevel*>(GetLevel())->GetInventory()->PushItem(this);
	//	ItemState_.Count_ += 1;
		Inventory::MainInventory_->PushItem(this);
	

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

void Item::Start()
{
	GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::ITEM});
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
}

void Item::Update(float _DeltaTime)
{

	PickUpItemCheck(Renderer_);
	TimeAttackUpdate(Renderer_);
	
}

void Item::RendererTypeSetting()
{
	if (nullptr == Renderer_)
	{
		return;
	}

	SlotType_ = InventorySlotType::SLOT_ETC;

	switch (MonsterName_)
	{
	case MONSTERNAME::WhiteRabbit:
	{
		Renderer_->SetTexture("Item1_Rabbit1.png");
		Renderer_->GetTransform().SetLocalScale({ 28.f, 26.f });
		SetItemType(ItemType::ITEM_WHITERABBIT);
	}
	break;
	case MONSTERNAME::BrownRabbit:
	{
		Renderer_->SetTexture("Item1_Rabbit2.png");
		Renderer_->GetTransform().SetLocalScale({ 29.f, 30.f });
		SetItemType(ItemType::ITEM_BROWNRABBIT);
	}
	break;
	case MONSTERNAME::BabyCactus:
	{
		Renderer_->SetTexture("Item_Cactus1.png");
		Renderer_->GetTransform().SetLocalScale({ 32.f, 34.f });
		SetItemType(ItemType::ITEM_CACTUS);
	}
	break;
	case MONSTERNAME::Sand:
	{
		Renderer_->SetTexture("Item_Sand1.png");
		Renderer_->GetTransform().SetLocalScale({ 33.f, 29.f });
		SetItemType(ItemType::ITEM_SAND);
	}
	break;
	case MONSTERNAME::Scorpion:
	{
		Renderer_->SetTexture("Item_Scor1.png");
		Renderer_->GetTransform().SetLocalScale({ 25.f, 27.f });
		SetItemType(ItemType::ITEM_SCOR);
	}
	break;
	case MONSTERNAME::Freezer:
	{
		Renderer_->SetTexture("Item_Freezer1.png");
		Renderer_->GetTransform().SetLocalScale({ 31.f, 31.f });
		SetItemType(ItemType::ITEM_FREEZER);
	}
	break;
	case MONSTERNAME::Sparker:
	{
		Renderer_->SetTexture("Item_Sparker1.png");
		Renderer_->GetTransform().SetLocalScale({ 28.f, 28.f });
		SetItemType(ItemType::ITEM_SPARKER);
	}
	break;
	}
}

void Item::PotionRendererTypeSetting()
{
	if (nullptr == Renderer_)
	{
		return; 
	}

	SlotType_ = InventorySlotType::SLOT_POTION;

	switch (ItemState_.ItemType_)
	{
	case ItemType::ITEM_HP300:
	{
		Renderer_->SetTexture("HP300.png");
		Renderer_->ScaleToTexture();
	}
	break;
	case ItemType::ITEM_MP300:
	{
		Renderer_->SetTexture("MP300.png");
		Renderer_->ScaleToTexture();
	}
	break;
	default:
		break;
	}
}

