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
	, MapTexture_(nullptr)
	, IsGround(false)
	, CurState_(ItemMoveState::MAX)
	, DropTime_(0.f)
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
	CreatePosition_ = GetTransform().GetWorldPosition();
	IsCreate = true;
}

void Item::TimeAttackUpdate(GameEngineTextureRenderer* _Renderer, float _DeltaTime)
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

void Item::UpDownMove(float _DeltaTime)
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

	GetTransform().SetWorldMove(MoveDir_ * _DeltaTime);
}

void Item::PickUpItem(GameEngineTextureRenderer* _Renderer, float _DeltaTime)
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
			if (100.f < abs(PlayerPos.y - GetItemPosition().y))
			{
				return;
			}

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

			GetTransform().SetWorldMove(MoveDir_ * _DeltaTime);

		}

	}
}

void Item::PickUpItemCheck(GameEngineTextureRenderer* _Renderer, float _DeltaTime)
{
	if (_Renderer->GetPixelData().MulColor.a <= 0)
	{
		_Renderer->GetPixelData().MulColor.a = 0;
	}

	// 다 주워졌다
	if (PickTime_ > 0.4f)
	{
		// ========== 습득 아이템 Inventory쪽 벡터에 넣어두기 ========== //

		Inventory::MainInventory_->PushItem(this);

		PickTime_ = 0.f;
		IsPick = false;
	
		Death();
	}
	if (true == IsPick)
	{
		PickTime_ += _DeltaTime;
		_Renderer->GetPixelData().MulColor.a -= _DeltaTime * 2.f;
	}
}

void Item::ItemDrop(float _DeltaTime)
{
	MoveDir_.y = 220.f;
	// 위로 이동했다가 0.8초 후 아래로 다운
	if (DropTime_ > 0.5f)
	{
		IsCreate = false;
		MoveDir_.y = -100.f; 
	}
	GetTransform().SetWorldMove(MoveDir_ * _DeltaTime);
}

void Item::ChangeState(ItemMoveState _State)
{
	if (CurState_ != _State)
	{
		switch (_State)
		{
		case ItemMoveState::Drop:
			DropStart();
			break;
		case ItemMoveState::Float:
			FloatStart();
			break;
		}
	}

	CurState_ = _State;
}

void Item::ItemStateUpdate(float _DeltaTime)
{
	switch (CurState_)
	{
	case ItemMoveState::Drop:
		DropUpdate(_DeltaTime);
		break;
	case ItemMoveState::Float:
		FloatUpdate(_DeltaTime);
		break;
	}
}

void Item::DropStart()
{
	MoveDir_.y = 800.f;
}

void Item::FloatStart()
{
	IsCreate = false;	// 처음 만들어진게 아니다
	DropTime_ = 0.f;
	MoveDir_.y = 6.f;
}

void Item::DropUpdate(float _DeltaTime)
{
	// 드롭 시간 체크
	DropTime_ += _DeltaTime;
	// 픽셀 체크 결과 땅에 닿았으면 상태 체인지
	if (true == IsGround)
	{
		MoveDir_ = 0.f;
		DropTime_ = 0.f;
		ChangeState(ItemMoveState::Float);
		return;
	}

	GetTransform().SetAddWorldRotation({ 0.f, 0.f, _DeltaTime * 1500.f });
	GetTransform().SetWorldMove(MoveDir_ * _DeltaTime);
	// 처음 만들어졌을 때, 위로 이동했다가 0.8초 후 아래로 다운

	MoveDir_.y -= 3000.f * _DeltaTime;

	if (DropTime_ > 0.3f)
	{
		StagePixelCheck();
	}

}

void Item::FloatUpdate(float _DeltaTime)
{
	UpDownMove(_DeltaTime);
 	PickUpItemCheck(Renderer_, _DeltaTime);
	TimeAttackUpdate(Renderer_, _DeltaTime);
}

void Item::Start()
{
	GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::ITEM});
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	ChangeState(ItemMoveState::Drop);
}

void Item::Update(float _DeltaTime)
{
	ItemStateUpdate(_DeltaTime);

	if (true == IsGround)
	{
		// 땅에 닿은 상태부터 소멸 시간 & 움직이는 시간을 잰다
		Time_ += _DeltaTime;
		MoveTime_ += _DeltaTime;
	}
}

GameEngineTexture* Item::GetCurMapTexture()
{
	if (CurLevelName_ != "TITLE"
		&& CurLevelName_ != "LOGIN"
		&& CurLevelName_ != "SELECT")
	{
		MapTexture_ = GetLevel<GlobalLevel>()->GetCollisionMap()->GetCurTexture();
	}

	if (nullptr == MapTexture_)
	{
		MsgBoxAssert("충돌맵이 설정되지 않았습니다");
	}

	return MapTexture_;
}

bool Item::StagePixelCheck()
{
	float4 Pos = 0.0f;
	GetCurMapTexture();

	float4 LeftColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix() - 18, GetTransform().GetWorldPosition().iy() );
	float4 RightColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix() + 18, GetTransform().GetWorldPosition().iy());
	float4 DownColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy() - 18);
	float4 UpColor = MapTexture_->GetPixelToFloat4(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy() + 18);

	// 땅에 닿았다
	if (true == LeftColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })
		|| true == RightColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })
		|| true == DownColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })
		|| true == UpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })
		|| true == LeftColor.CompareInt4D(float4{ 1.f, 0.f, 0.f, 1.f })
		|| true == RightColor.CompareInt4D(float4{ 1.f, 0.f, 0.f, 1.f })
		|| true == DownColor.CompareInt4D(float4{ 1.f, 0.f, 0.f, 1.f })
		|| true == UpColor.CompareInt4D(float4{ 1.f, 0.f, 0.f, 1.f })
		)
	{
		IsGround = true;
		// 회전 Stop + 포지션 처음 생성 자리로 고정
		GetTransform().SetWorldRotation({0.f, 0.f, 0.f});
		GetTransform().SetWorldPosition(CreatePosition_);
	}

	return true;
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
	case MONSTERNAME::None:
	{
		Renderer_->SetTexture("QuestItem1.png");
		Renderer_->GetTransform().SetLocalScale({ 29.f, 30.f });
		SetItemType(ItemType::ITEM_QUEST);
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
	case ItemType::ITEM_HP2000:
	{
		Renderer_->SetTexture("HP2000_1.png");
		Renderer_->ScaleToTexture();
	}
	break;
	case ItemType::ITEM_HP4000:
	{
		Renderer_->SetTexture("HP4000.png");
		Renderer_->ScaleToTexture();
	}
	break;
	case ItemType::ITEM_HP5000:
	{
		Renderer_->SetTexture("HP5000.png");
		Renderer_->ScaleToTexture();
	}
	break;
	case ItemType::ITEM_MP100:
	{
		Renderer_->SetTexture("MP100_1.png");
		Renderer_->ScaleToTexture();
	}
	break;
	case ItemType::ITEM_MP300:
	{
		Renderer_->SetTexture("MP300.png");
		Renderer_->ScaleToTexture();
	}
	break;
	case ItemType::ITEM_MP2000:
	{
		Renderer_->SetTexture("MP2000_1.png");
		Renderer_->ScaleToTexture();
	}
	break;
	case ItemType::ITEM_MP4000:
	{
		Renderer_->SetTexture("MP4000.png");
		Renderer_->ScaleToTexture();
	}
	break;
	case ItemType::ITEM_MP5000:
	{
		Renderer_->SetTexture("MP5000.png");
		Renderer_->ScaleToTexture();
	}
	break;
	default:
		break;
	}
	

}

	