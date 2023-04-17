#include "PreCompile.h"
#include "Mouse.h"
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "Inventory.h"
#include "MouseSlot.h"
#include "Item.h"
#include "QuickSlotItem.h"
#include "Player.h"
#include "ContentsUI.h"
#include "ContentsFont.h"

Mouse* Mouse::MainMouse_ = nullptr;

Mouse::Mouse() 
	: UIMouseCol_(nullptr)
	, MouseRenderer_(nullptr)
	, ClickSoundOn_(false)
	, MouseAnimationRenderer_(nullptr)
	, MouseOverSoundOn_(false)
	, MainCameraMouseCol_ (nullptr)
	, MouseSlot_(nullptr)
{
}

Mouse::~Mouse() 
{
}

void Mouse::GetCurPos()
{
	UICameraCurPos_ = GetLevel()->GetUICamera()->GetMouseWorldPosition();
	MainCameraCurPos_ = GetLevel()->GetMainCamera()->GetMouseWorldPosition();




	/*UICameraCurPos_.x = GetLevel()->GetUICamera()->GetMouseWorldPosition().x;
	UICameraCurPos_.y = GetLevel()->GetUICamera()->GetMouseWorldPosition().y;

	MainCameraCurPos_.x = GetLevel()->GetMainCamera()->GetMouseWorldPosition().x;
	MainCameraCurPos_.y = GetLevel()->GetMainCamera()->GetMouseWorldPosition().y;*/

	std::string CurLevel = GetLevel()->GetNameCopy();
}

void Mouse::Start()
{
	GetCurPos();
	GetTransform().SetLocalPosition({ UICameraCurPos_.x, UICameraCurPos_.y, (int)ZOrder::MOUSE });

	UIMouseCol_ = CreateComponent<GameEngineCollision>("MouseCol");
	UIMouseCol_->SetUIDebugCamera();
	UIMouseCol_->GetTransform().SetLocalPosition({ UICameraCurPos_.x,UICameraCurPos_.y + 10.f });
	UIMouseCol_->GetTransform().SetLocalScale({ 20.f, 20.f });
	UIMouseCol_->ChangeOrder(GAMEOBJGROUP::MOUSE); 

	MainCameraMouseCol_ = CreateComponent<GameEngineCollision>("MouseCol");
	MainCameraMouseCol_->SetDebugCamera(CAMERAORDER::MAINCAMERA);
	MainCameraMouseCol_->SetDebugSetting(CollisionType::CT_OBB2D, float4{ 0.f, 0.f, 1.f, 1.f });
	MainCameraMouseCol_->GetTransform().SetLocalPosition({ MainCameraCurPos_.x, MainCameraCurPos_.y + 10.f });
	MainCameraMouseCol_->GetTransform().SetLocalScale({ 20.f, 20.f });
	MainCameraMouseCol_->ChangeOrder((int)GAMEOBJGROUP::MAINMOUSE);

	MouseRenderer_ = CreateComponent<GameEngineUIRenderer>();
	MouseRenderer_->SetTexture("Cursor_Idle.png");
	MouseRenderer_->GetTransform().SetLocalScale({ 24.f * 1.2f, 28.f * 1.2f });
	MouseRenderer_->SetRenderingOrder((int)GAMEOBJGROUP::MOUSE);
	MouseRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);

	MouseAnimationRenderer_ = CreateComponent<GameEngineUIRenderer>();
	MouseAnimationRenderer_->SetRenderingOrder((int)GAMEOBJGROUP::MOUSE);
	MouseAnimationRenderer_->CreateFrameAnimationFolder("Cursor_MouseOver", FrameAnimation_DESC("Cursor_MouseOver", 0.55f));
	MouseAnimationRenderer_->CreateFrameAnimationFolder("Cursor_Hold", FrameAnimation_DESC("Cursor_Hold", 0.3f));
	MouseAnimationRenderer_->GetTransform().SetLocalScale({ 30.f * 1.1f, 30.f * 1.1f });
	MouseAnimationRenderer_->ChangeFrameAnimation("Cursor_MouseOver");
	MouseAnimationRenderer_->SetRenderingOrder((int)GAMEOBJGROUP::MOUSE);
	MouseAnimationRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);
	MouseAnimationRenderer_->Off();

	MouseSlot_ = GetLevel()->CreateActor<MouseSlot>();

	if (false == GameEngineInput::GetInst()->IsKey("LeftMouse"))
	{
		GameEngineInput::GetInst()->CreateKey("LeftMouse", VK_LBUTTON);
		GameEngineInput::GetInst()->CreateKey("RightMouse", VK_RBUTTON);
	}


}

void Mouse::Update(float _DeltaTime)
{
	GetCurPos();
	UIMouseCol_->GetTransform().SetLocalPosition({ UICameraCurPos_.x,UICameraCurPos_.y + 10.f, (int)ZOrder::MOUSE });
	MouseRenderer_->GetTransform().SetLocalPosition({ UICameraCurPos_.x,UICameraCurPos_.y, (int)ZOrder::MOUSE });
	MouseAnimationRenderer_->GetTransform().SetLocalPosition({ UICameraCurPos_.x,UICameraCurPos_.y, (int)ZOrder::MOUSE });

	MainCameraMouseCol_->GetTransform().SetLocalPosition({ MainCameraCurPos_.x, MainCameraCurPos_.y + 10.f });


	// 아이템을 잡은 상태가 아닐때만 일반 애니메이션
	if (true == MouseSlot_->IsHold_)
	{
		return;
	}

	// 아이템을 잡은 마우스가 인벤토리 외부와 충돌
	if (true == MouseSlot_->IsDoneHolding_
		&& false == UIMouseCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::INVENTORY, CollisionType::CT_OBB2D))
	{
		if (nullptr == MouseSlot_->GetInventoryItem())
		{
			return;
		}

		// 퀵슬롯과 충돌했을 경우
		if (true == UIMouseCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::QUICKSLOT, CollisionType::CT_OBB2D)
			&& InventorySlotType::SLOT_POTION == MouseSlot_->GetInventoryItem()->GetInventorySlotType())
		{
			MouseRenderer_->SetTexture("Cursor_Idle.png");
			MouseRenderer_->GetTransform().SetLocalScale({ 24.f * 1.2f, 28.f * 1.2f });
			MouseSlot_->IsDoneHolding_ = false;

			//ContentsUI* ContentsUI_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetContentsUI();
			for (size_t i = 0; i < ContentsUI::MainUI_->GetQuickSlotItemsList().size(); i++)
			{
				if (true == ContentsUI::MainUI_->GetQuickSlotItemsList()[i]->GetCollision()->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
				{
					ContentsUI::MainUI_->GetQuickSlotItemsList()[i]->CollisionCheck();
					ContentsUI::MainUI_->GetQuickSlotItemsList()[i]->SetQuickSlotIndex((int)i);

					break;
				}
			}
			
			return;
		}

		if (nullptr != MouseSlot_->GetQuickSlotItem())
		{
			return;
		}
		// 아이템 버리기 
		MouseSlot_->IsDoneHolding_ = false;
	
		Item* ItemActor = GetLevel()->CreateActor<Item>(GAMEOBJGROUP::ITEM);
		if (InventorySlotType::SLOT_ETC == MouseSlot_->GetInventoryItem()->GetInventorySlotType())
		{
			ItemActor->MonsterName_ = MouseSlot_->GetInventoryItem()->GetMonsterName();
			ItemActor->RendererTypeSetting();
		}
		else if (InventorySlotType::SLOT_POTION == MouseSlot_->GetInventoryItem()->GetInventorySlotType())
		{
			ItemActor->SetItemType(MouseSlot_->GetInventoryItem()->GetItemType());
			ItemActor->PotionRendererTypeSetting();
		}
		ItemActor->GetTransform().SetLocalPosition({ Player::MainPlayer_->GetPosition().x - 12.f, Player::MainPlayer_->GetPosition().y - 17.f, (int)ZOrder::ITEM});
		ItemActor->TimeAttackStart();

		MouseSlot_->GetInventoryItem()->SetCount(MouseSlot_->GetInventoryItem()->GetCount() - 1);
		MouseSlot_->GetInventoryItem()->GetContensFont()->GetNormalFontRenderer()->SetText(std::to_string(MouseSlot_->GetInventoryItem()->GetCount()));
		
		// 2) 퀵슬롯에 버리는 아이템 타입과 같은 아이템이 있는지 검사
		for (size_t i = 0; i < ContentsUI::MainUI_->GetQuickSlotItemsList().size(); i++)
		{
			if (MouseSlot_->GetInventoryItem()->GetItemType() == ContentsUI::MainUI_->GetQuickSlotItemsList()[i]->GetItemType())
			{
				ContentsUI::MainUI_->GetQuickSlotItemsList()[i]->SetCount(ContentsUI::MainUI_->GetQuickSlotItemsList()[i]->GetCount() - 1);
				break;
			}
		}
		if (MouseSlot_->GetInventoryItem()->GetCount() <= 0)
		{
			// 1) 인벤토리에 버리는 아이템 타입과 같은 아이템이 있는지 검사
			if (InventorySlotType::SLOT_POTION == MouseSlot_->GetInventoryItem()->GetInventorySlotType())
			{
				for (size_t i = 0; i < Inventory::MainInventory_->GetInventoryListPotion().size(); i++)
				{
					if (MouseSlot_->GetInventoryItem()->GetItemType() == Inventory::MainInventory_->GetInventoryListPotion()[i]->GetItemType())
					{
						Inventory::MainInventory_->GetInventoryListPotion()[i]->SetItemType(ItemType::MAX);
						Inventory::MainInventory_->GetInventoryListPotion()[i]->GetContensFont()->GetNormalFontRenderer()->Off();

						break;
					}
				}
			}
			else if (InventorySlotType::SLOT_ETC == MouseSlot_->GetInventoryItem()->GetInventorySlotType())
			{
				for (size_t i = 0; i < Inventory::MainInventory_->GetInventoryListEtc().size(); i++)
				{
					if (MouseSlot_->GetInventoryItem()->GetItemType() == Inventory::MainInventory_->GetInventoryListEtc()[i]->GetItemType())
					{
						Inventory::MainInventory_->GetInventoryListEtc()[i]->SetItemType(ItemType::MAX);
						Inventory::MainInventory_->GetInventoryListEtc()[i]->GetContensFont()->GetNormalFontRenderer()->Off();

						break;
					}
				}
			}

			// 2) 퀵슬롯에 버리는 아이템 타입과 같은 아이템이 있는지 검사
			for (size_t i = 0; i < ContentsUI::MainUI_->GetQuickSlotItemsList().size(); i++)
			{
				if (MouseSlot_->GetInventoryItem()->GetItemType() == ContentsUI::MainUI_->GetQuickSlotItemsList()[i]->GetItemType())
				{
					ContentsUI::MainUI_->GetQuickSlotItemsList()[i]->SetItemType(ItemType::MAX);
					ContentsUI::MainUI_->GetQuickSlotItemsList()[i]->GetContensFont()->GetNormalFontRenderer()->Off();

					break;
				}
			}

			MouseSlot_->GetInventoryItem()->SetItemType(ItemType::MAX);
			MouseSlot_->GetInventoryItem()->SetMonsterName(MONSTERNAME::MAX);
			MouseSlot_->GetInventoryItem()->SetInventorySlotType(InventorySlotType::MAX);
			MouseSlot_->GetInventoryItem()->GetContensFont()->GetNormalFontRenderer()->Off();
			MouseSlot_->SetInventoryItem(nullptr);
		}
	}
	
 	if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
	{
		ClickSoundOn_ = true;
	}

	if (true == GameEngineInput::GetInst()->IsPress("LeftMouse"))
	{
		MouseRenderer_->SetTexture("Cursor_Click.png");
		MouseRenderer_->GetTransform().SetLocalScale({ 25.f * 1.2f, 23.f * 1.2f });
	}
	else if(true == GameEngineInput::GetInst()->IsUp("LeftMouse"))
	{
		MouseRenderer_->SetTexture("Cursor_Idle.png");
		MouseRenderer_->GetTransform().SetLocalScale({ 24.f * 1.2f, 28.f * 1.2f });
	}
	if (true == ClickSoundOn_)
	{
		GameEngineSound::SoundPlayOneShot("BtMouseClick.mp3");
		ClickSoundOn_ = false;
	}

	CollisionCheck();
}

bool Mouse::MouseCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	MouseAnimationRenderer_->On();
	MouseAnimationRenderer_->ChangeFrameAnimation("Cursor_MouseOver");
	MouseRenderer_->Off();

	if (true == MouseOverSoundOn_)
	{
		GameEngineSound::SoundPlayOneShot("BtMouseOver.mp3");
		MouseOverSoundOn_ = false;
	}

	return true;
}

void Mouse::CollisionCheck()
{
	if (true == UIMouseCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::UI, CollisionType::CT_OBB2D,
		std::bind(&Mouse::MouseCollisionCheck, this, std::placeholders::_1, std::placeholders::_2))
		&& true == MouseOverSoundOn_)
	{
		MouseOverSoundOn_ = false;
	}
	else
	{
		MouseAnimationRenderer_->Off();
		MouseRenderer_->On();
	}

	if (true == MainCameraMouseCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::NPC, CollisionType::CT_OBB2D))
	{
		MouseAnimationRenderer_->On();
		MouseAnimationRenderer_->ChangeFrameAnimation("Cursor_MouseOver");
		MouseRenderer_->Off();
	}
	else
	{
		MouseAnimationRenderer_->Off();
		MouseRenderer_->On();
	}

	if (false == UIMouseCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::UI, CollisionType::CT_OBB2D,
		std::bind(&Mouse::MouseCollisionCheck, this, std::placeholders::_1, std::placeholders::_2)))
	{
		MouseOverSoundOn_ = true;
	}

	// 인벤토리 아이템과 충돌 시
	//if (true == MouseCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::SLOTUI, CollisionType::CT_OBB2D))
	//{
	//	MouseAnimationRenderer_->On();
	//	MouseAnimationRenderer_->ChangeFrameAnimation("Cursor_Hold");
	//	MouseRenderer_->Off();
	//}
}