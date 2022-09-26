#include "PreCompile.h"
#include "AriantLevel.h"
#include <GameEngineCore/GEngine.h>
#include "Player.h"
#include "MapStage.h"
#include "Mouse.h"
#include "Fade.h"
#include "Item.h"
#include "Meso.h"
#include "Inventory.h"
#include "GameBgmPlayer.h"

AriantLevel::AriantLevel() 
	: Player_(nullptr)
{
}

AriantLevel::~AriantLevel() 
{
}

void AriantLevel::Start()
{
	SetCollisionMap("ColMap_Ariant.png");
	SetBackGround("Back_Ariant.png");
	SetStage("Stage_Ariant.png");

	if (nullptr == Player::MainPlayer_)
	{
		Player::MainPlayer_ = CreateActor<Player>((int)GAMEOBJGROUP::PLAYER);
		Inventory::MainInventory_ = CreateActor<Inventory>((int)GAMEOBJGROUP::UI);
		ContentsUI::MainUI_ = CreateActor<ContentsUI>((int)GAMEOBJGROUP::UI);
	}
	if (nullptr == Mouse::MainMouse_)
	{
		Mouse::MainMouse_ = CreateActor<Mouse>((int)GAMEOBJGROUP::MOUSE);
	}

	SetPortal({ 3008.f, -750.f, (int)ZOrder::PORTAL});
	SetPortal({ 3410.f, -750.f, (int)ZOrder::PORTAL });

}

void AriantLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Cactus");
	}

	if (GameEngineInput::GetInst()->IsDown("FreeCameraOnOff"))
	{
		GetMainCameraActor()->FreeCameraModeOnOff();
	}

	PlayerPos_ = Player::MainPlayer_->GetTransform().GetLocalPosition();

	if (false == GetMainCameraActor()->IsFreeCameraMode())
	{
		GetMainCameraActor()->GetTransform().SetLocalPosition({ PlayerPos_.x, PlayerPos_.y + 120.f });
	}

	CameraFix({ 5760.f, 995.f });
}

void AriantLevel::End()
{
}

void AriantLevel::LevelStartEvent()
{
	Fade* FadeActor = CreateActor<Fade>(GAMEOBJGROUP::FADE);

	if (nullptr != Player::MainPlayer_)
	{
		Player::MainPlayer_->On();
		Player::MainPlayer_->GetTransform().SetLocalPosition({ 3200.f, -600.0f, (int)ZOrder::PLAYER });
	}
	if (nullptr != ContentsUI::MainUI_)
	{
		ContentsUI::MainUI_->On();
	}

	//// ======= Å×½ºÆ® ==========

	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->SetItemType(ItemType::ITEM_MP300);
		ItemActor->PotionRendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3000.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}
	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->SetItemType(ItemType::ITEM_MP300);
		ItemActor->PotionRendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3050.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}
	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->SetItemType(ItemType::ITEM_HP300);
		ItemActor->PotionRendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3100.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}
	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->SetItemType(ItemType::ITEM_HP300);
		ItemActor->PotionRendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3150.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}
	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->MonsterName_ = MONSTERNAME::BabyCactus;
		ItemActor->RendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3200.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}

	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->MonsterName_ = MONSTERNAME::BabyCactus;
		ItemActor->RendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3250.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}

	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->MonsterName_ = MONSTERNAME::BabyCactus;
		ItemActor->RendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3280.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}

	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->MonsterName_ = MONSTERNAME::BrownRabbit;
		ItemActor->RendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3310.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}

	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->MonsterName_ = MONSTERNAME::BrownRabbit;
		ItemActor->RendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3340.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}
	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->MonsterName_ = MONSTERNAME::BrownRabbit;
		ItemActor->RendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3370.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}
	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->MonsterName_ = MONSTERNAME::WhiteRabbit;
		ItemActor->RendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3400.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}
	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->MonsterName_ = MONSTERNAME::Freezer;
		ItemActor->RendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3430.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}
	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->MonsterName_ = MONSTERNAME::Sparker;
		ItemActor->RendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3460.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}
	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->MonsterName_ = MONSTERNAME::Scorpion;
		ItemActor->RendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3490.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}
	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->MonsterName_ = MONSTERNAME::Sand;
		ItemActor->RendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3520.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}
	{
		Item* ItemActor = CreateActor<Item>(GAMEOBJGROUP::OBJ);
		ItemActor->MonsterName_ = MONSTERNAME::None;
		ItemActor->RendererTypeSetting();
		ItemActor->GetTransform().SetLocalPosition(float4{ 3550.f, -800.f, (int)ZOrder::ITEM });
		ItemActor->TimeAttackStart();
	}


	Meso* MesoActor = CreateActor<Meso>(GAMEOBJGROUP::OBJ);
	MesoActor->GetTransform().SetLocalPosition(float4{ 3220.f, -800.f, (int)ZOrder::ITEM });
	MesoActor->TimeAttackStart();
}

void AriantLevel::LevelEndEvent()
{
	Player::MainPlayer_->SetLevelOverOn();
	Inventory::MainInventory_->SetLevelOverOn();
	Mouse::MainMouse_->SetLevelOverOn();
}

