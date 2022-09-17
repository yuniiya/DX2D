#include "PreCompile.h"
#include "QuickSlotItem.h"
#include "MouseSlot.h"
#include "Mouse.h"
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "Inventory.h"

QuickSlotItem::QuickSlotItem() 
	: QuickSlotIndex_(0)
	, SlotKey_(0)
{
}

QuickSlotItem::~QuickSlotItem() 
{
}

void QuickSlotItem::Start()
{
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::UI });
	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetPivot(PIVOTMODE::LEFTTOP);
	Renderer_->GetTransform().SetLocalScale({ 128.f, 128.f });
	Renderer_->Off();

	ItemCountFont_ = CreateComponent<GameEngineFontRenderer>();
	ItemCountFont_->SetRenderingOrder((int)GAMEOBJGROUP::FONT);
	ItemCountFont_->SetText(std::to_string(ItemState_.Count_));
	ItemCountFont_->SetColor({ 0.0f, 0.0f, 0.0f, 1.0 });
	ItemCountFont_->SetSize(17);
	ItemCountFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	ItemCountFont_->Off();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->SetUIDebugCamera();
	Collision_->GetTransform().SetLocalScale({ 23.f, 28.f });
	Collision_->ChangeOrder((int)GAMEOBJGROUP::QUICKSLOT);

	Collision_->GetTransform().SetLocalPosition(
		{ Renderer_->GetTransform().GetLocalPosition().x + 73.f
		, Renderer_->GetTransform().GetLocalPosition().y - 76.f });

	//MouseCollision_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseCol();
	//MouseRenderer_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseRenderer();
	//MouseAnimationRenderer_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseAnimationRenderer();
	//MouseSlotRenderer_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseSlot()->GetRenderer();
	//MouseSlot_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseSlot();

	SetLevelOverOn();
}

void QuickSlotItem::Update(float _DeltaTime)
{
	if (GetCount() <= 0)
	{
		SetItemType(ItemType::MAX);
		SetCount(0);
		ItemCountFont_->Off();
	}

	ItemCountFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	// �������� ����
	if (true == GameEngineInput::GetInst()->IsUp("LeftMouse") && true == IsHold_)
	{
		GameEngineSound::SoundPlayOneShot("DragEnd.mp3");
		//dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseSlot()->IsHold_ = false;
		//dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseSlot()->IsDoneHolding_ = true;

		Mouse::MainMouse_->GetMouseSlot()->IsHold_ = false;
		Mouse::MainMouse_->GetMouseSlot()->IsDoneHolding_ = true;
		IsHold_ = false;
		MouseSlotRenderer_->Off();
	}
	if (true == DragStartSound_)
	{
		DragStartSound_ = false;
		GameEngineSound::SoundPlayOneShot("DragStart.mp3");
	}

	// ������ �����۳��� �浹 üũ 
	QuickSlotCollisionCheck();
	SlotKeyCheck();
}

void QuickSlotItem::LevelEndEvent()
{
	ItemCountFont_->ChangeCamera(CAMERAORDER::UICAMERA);
}

void QuickSlotItem::SlotKeyCheck()
{
	if (false == SlotKeyInputCheck())
	{
		return;
	}

	if (ItemType_ == ItemType::MAX)
	{
		return;
	}


	if (true == GameEngineInput::GetInst()->IsDown("1")
		&& ItemType_ == ItemType::ITEM_HP300)
	{
		GameEngineSound::SoundPlayOneShot("ItemUse.mp3");
		InventoryItem_->SetCount(InventoryItem_->GetCount()- 1);
		Player::MainPlayer_->AddHP(5.f);
	}
	else if (true == GameEngineInput::GetInst()->IsDown("2")
		&& ItemType_ == ItemType::ITEM_MP300)
	{
		GameEngineSound::SoundPlayOneShot("ItemUse.mp3");
		InventoryItem_->SetCount(InventoryItem_->GetCount() - 1);
		Player::MainPlayer_->AddMP(5.f);
	}

	SetCount(InventoryItem_->GetCount());

	if (GetCount() <= 0)
	{
		SetItemType(ItemType::MAX);
		ItemCountFont_->Off();
	}


}

bool QuickSlotItem::SlotKeyInputCheck()
{
	//if (true == GameEngineInput::GetInst()->IsDown(std::to_string(SlotKey_)))
	//{
	//	return true;
	//}
	//return false;

	if (true == GameEngineInput::GetInst()->IsDown("1")
		|| true == GameEngineInput::GetInst()->IsDown("2"))
	{
		return true;
	}
	return false;
}

void QuickSlotItem::CollisionCheck()
{
	MouseCollision_ = Mouse::MainMouse_->GetMouseCol();
	MouseRenderer_ = Mouse::MainMouse_->GetMouseRenderer();
	MouseAnimationRenderer_ = Mouse::MainMouse_->GetMouseAnimationRenderer();
	MouseSlotRenderer_ = Mouse::MainMouse_->GetMouseSlot()->GetRenderer();
	MouseSlot_ = Mouse::MainMouse_->GetMouseSlot();

	// �κ��丮 �������� ���������� �Ű��� �� 
	if (true == GameEngineInput::GetInst()->IsUp("LeftMouse") &&
		MouseSlot_->GetInventoryItem() != nullptr)
	{
		if (true == Collision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
		{
			// ���� �������̴�
			if (GetItemType() == MouseSlot_->GetInventoryItem()->GetItemType())
			{
				return;

			}	// 6-2) �� ĭ�̴�
			else if (GetItemType() == ItemType::MAX)
			{
				MouseSlot_->GetInventoryItem()->SetSlotIndex(GetQuickSlotIndex());
				// �� ĭ�� ������ ī��Ʈ ���� ������ ī��Ʈ�� ����
				SetCount(MouseSlot_->GetInventoryItem()->GetCount());
				//ItemCountFontUpdate();

				// ��ĭ�� ��Ʈ ������ ��ġ ����
				ItemCountFont_->SetScreenPostion({ GetTransform().GetLocalPosition().x + 700.f, -GetTransform().GetLocalPosition().y + 440.f });

				// �� ĭ�� ������ Ÿ�� ���� ������ Ÿ������ ����
				SetItemType(MouseSlot_->GetInventoryItem()->GetItemType());
				// �κ��丮 ĭ �������� ���� �״��
				InventoryItem_ = MouseSlot_->GetInventoryItem();

			} // 6-3) �ٸ� �������� �̹� �ִ�	-> ü����
			else if (GetItemType() != MouseSlot_->GetInventoryItem()->GetItemType() && GetItemType() != ItemType::MAX)
			{
				MouseSlot_->GetInventoryItem()->SetSlotIndex(GetQuickSlotIndex());
				SetItemType(MouseSlot_->GetInventoryItem()->GetItemType());
				SetCount(MouseSlot_->GetInventoryItem()->GetCount());
				InventoryItem_ = MouseSlot_->GetInventoryItem();
				//ItemCountFontUpdate();
			}
		}
	}

}

void QuickSlotItem::QuickSlotCollisionCheck()
{
	//if (nullptr == MouseSlot_)
	//{
	//	return;
	//}

	//MouseCollision_ = Mouse::MainMouse_->GetMouseCol();
	//MouseRenderer_ = Mouse::MainMouse_->GetMouseRenderer();
	//MouseAnimationRenderer_ = Mouse::MainMouse_->GetMouseAnimationRenderer();
	//MouseSlotRenderer_ = Mouse::MainMouse_->GetMouseSlot()->GetRenderer();
	//MouseSlot_ = Mouse::MainMouse_->GetMouseSlot();

	if(true == Collision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	{
		// ������ ���콺 Ŭ�� �� �����Կ��� ������ ���� 
		if (true == GameEngineInput::GetInst()->IsDown("RightMouse"))
		{
			IsSlot_ = false;
			SetItemType(ItemType::MAX);
			SetCount(0);
			ItemCountFont_->Off();
		}

		//if (true == GameEngineInput::GetInst()->IsUp("LeftMouse") &&
		//	MouseSlot_->GetQuickSlotItem() != nullptr)
		//{
		//	// ���� ĭ�̴�
		//	if (GetItemType() == MouseSlot_->GetQuickSlotItem()->GetItemType())
		//	{		
		//		InventoryItem_ = nullptr;
		//		InventoryItem_ = MouseSlot_->GetQuickSlotItem();
		//		MouseSlot_->GetQuickSlotItem()->SetItemType(ItemType::MAX);
		//		MouseSlot_->GetQuickSlotItem()->SetCount(0);
		//		MouseSlot_->GetQuickSlotItem()->GetFontRenderer()->Off();
		//		//MouseSlot_->SetQuickSlotItem(nullptr);
		//		return;
		//	}
		//	// 6-2) �� ĭ�̴�
		//	else if (GetItemType() == ItemType::MAX)
		//	{
		//		InventoryItem_ = nullptr;
		//		InventoryItem_ = MouseSlot_->GetQuickSlotItem();
		//		MouseSlot_->GetQuickSlotItem()->SetQuickSlotIndex(GetQuickSlotIndex());
		//		// �� ĭ�� ������ ī��Ʈ ���� ������ ī��Ʈ�� ����
		//		SetCount(MouseSlot_->GetQuickSlotItem()->GetCount());
		//		//ItemCountFontUpdate();

		//		// ��ĭ�� ��Ʈ ������ ��ġ ����
		//		ItemCountFont_->SetScreenPostion({ GetTransform().GetLocalPosition().x + 700.f, -GetTransform().GetLocalPosition().y + 440.f });

		//		// �� ĭ�� ������ Ÿ�� ���� ������ Ÿ������ ����
		//		SetItemType(MouseSlot_->GetQuickSlotItem()->GetItemType());

		//		MouseSlot_->GetQuickSlotItem()->SetItemType(ItemType::MAX);
		//		// ���� ��Ʈ ����
		//		MouseSlot_->GetQuickSlotItem()->SetCount(0);
		//		MouseSlot_->GetQuickSlotItem()->GetFontRenderer()->Off();
		//		// ���� ������ null�� �����
		//		//MouseSlot_->SetQuickSlotItem(nullptr);
		//	} // 6-3) �ٸ� �������� �̹� �ִ�	-> ���� �����
		//	else if (GetItemType() != MouseSlot_->GetQuickSlotItem()->GetItemType() && GetItemType() != ItemType::MAX)
		//	{

		//		return;
		//	}


		//	IsSlot_ = false;
		//}

		//if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		//{
		//	IsSlot_ = true;
		//	// �� ĭ�� �ƴ� ���� �Ʒ��� ����
		//	if (ItemType::MAX == ItemType_)
		//	{
		//		return;
		//	}

		//	// �������� �̹� ���� ���� -> ����
		//	if (true == IsHold_
		//		|| true == MouseSlot_->IsHold_)
		//	{
		//		return;
		//	}
		//	if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		//	{
		//		DragStartSound_ = true;
		//	}
		//	// 1) ���콺�� ���� �������� ����, �������� Ŭ�� ���� ��->������ �������� ���� ���������� ����
		//	if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
		//	{
		//		MouseSlot_->IsHold_ = true;
		//		IsHold_ = true;
		//		MouseAnimationRenderer_->Off();
		//		MouseRenderer_->On();
		//		MouseRenderer_->SetTexture("Cursor_Hold.png");
		//		MouseRenderer_->GetTransform().SetLocalScale({ 27.f * 1.2f, 29.f * 1.2f });

		//		MouseSlotRenderer_->SetTexture("Item2.png", Index_);
		//		MouseSlotRenderer_->On();

		//		// 2) ������ ������ = ���� ���콺�� ���� ������ (������ ��� �ִ´�)
		//		MouseSlot_->SetQuickSlotItem(this);

		//	}
		//}
	
	}
}

