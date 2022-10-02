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

void Item::TimeAttackUpdate(GameEngineTextureRenderer* _Renderer)
{
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
			Time_ = 0.f;
			_Renderer->GetPixelData().MulColor.a = 0;
			Death();
		}
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
			if (100.f < abs(PlayerPos.y - GetItemPosition().y))
			{
				return;
			}

			GameEngineSound::SoundPlayOneShot("PickUpItem.mp3");	// �÷��̾������� ��������?
			IsPick = true;

			if (PlayerPos.x < GetItemPosition().x)		// �÷��̾ ����
			{
				MoveDir_ = { -40.f, 20.f };
			}
			else if (PlayerPos.x >= GetItemPosition().x)	// ������
			{
				MoveDir_ = { 40.f, 20.f };
			}

			GetTransform().SetWorldMove(MoveDir_ * GameEngineTime::GetDeltaTime());

		}

	}
}

void Item::PickUpItemCheck(GameEngineTextureRenderer* _Renderer)
{
	if (_Renderer->GetPixelData().MulColor.a < 0)
	{
		_Renderer->GetPixelData().MulColor.a = 0;
	}

	// �� �ֿ�����
	if (PickTime_ > 0.4f)
	{
		// ========== ���� ������ Inventory�� ���Ϳ� �־�α� ========== //
		Inventory::MainInventory_->PushItem(this);

		PickTime_ = 0.f;
		IsPick = false;
	
		Death();
	}
	if (true == IsPick)
	{
		PickTime_ += GameEngineTime::GetDeltaTime();
		_Renderer->GetPixelData().MulColor.a -= GameEngineTime::GetDeltaTime() * 3.f;
	}
}

void Item::ItemDrop()
{
	MoveDir_.y = 220.f;
	// ���� �̵��ߴٰ� 0.8�� �� �Ʒ��� �ٿ�
	if (DropTime_ > 0.5f)
	{
		IsCreate = false;
		MoveDir_.y = -100.f; 
	}
	GetTransform().SetWorldMove(MoveDir_ * GameEngineTime::GetDeltaTime());
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

void Item::ItemStateUpdate()
{
	switch (CurState_)
	{
	case ItemMoveState::Drop:
		DropUpdate();
		break;
	case ItemMoveState::Float:
		FloatUpdate();
		break;
	}
}

void Item::DropStart()
{
	MoveDir_.y = 210.f;
}

void Item::FloatStart()
{
	IsCreate = false;	// ó�� ��������� �ƴϴ�
	DropTime_ = 0.f;
	MoveDir_.y = 6.f;
}

void Item::DropUpdate()
{
	// ��� �ð� üũ
	DropTime_ += GameEngineTime::GetDeltaTime();
	// �ȼ� üũ ��� ���� ������� ���� ü����
	if (true == IsGround)
	{
		MoveDir_ = 0.f;
		ChangeState(ItemMoveState::Float);
		return;
	}

	GetTransform().SetAddWorldRotation({ 0.f, 0.f, GameEngineTime::GetDeltaTime() * 1500.f });
	GetTransform().SetWorldMove(MoveDir_ * GameEngineTime::GetDeltaTime());
	// ó�� ��������� ��, ���� �̵��ߴٰ� 0.8�� �� �Ʒ��� �ٿ�
	if (DropTime_ > 0.4f)
	{
		MoveDir_.y -= 15.f;
		StagePixelCheck();
	}
	
}

void Item::FloatUpdate()
{
	UpDownMove();
 	PickUpItemCheck(Renderer_);
	TimeAttackUpdate(Renderer_);
}

void Item::Start()
{
	GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::ITEM});
	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	ChangeState(ItemMoveState::Drop);
}

void Item::Update(float _DeltaTime)
{
	ItemStateUpdate();

	if (true == IsGround)
	{
		// ���� ���� ���º��� �Ҹ� �ð� & �����̴� �ð��� ���
		Time_ += GameEngineTime::GetDeltaTime();
		MoveTime_ += GameEngineTime::GetDeltaTime();
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
		MsgBoxAssert("�浹���� �������� �ʾҽ��ϴ�");
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

	// ���� ��Ҵ�
	if (true == LeftColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })
		|| true == RightColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })
		|| true == DownColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })
		|| true == UpColor.CompareInt4D(float4{ 0.f, 0.f, 0.f, 1.f })
		)
	{
		IsGround = true;
		// ȸ�� Stop + ������ ó�� ���� �ڸ��� ����
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

	