#include "PreCompile.h"
#include "NPC_Entrance.h"
#include "Inventory.h"
#include "InventoryItem.h"
#include "Item.h"
#include "QuestClearUI.h"

NPC_Entrance::NPC_Entrance() 
{
}

NPC_Entrance::~NPC_Entrance() 
{
}

void NPC_Entrance::Start()
{
	NPC::Start();
}

void NPC_Entrance::Update(float _DeltaTime)
{
	NPC::Update(_DeltaTime);

	// �ձ� ���� �ڰ��� ȹ�� & 2000�޼� ����
	if (true == IsQuestClear_ || true == IsQuestEnd_)
	{
		Player::MainPlayer_->UsePlayerMeso(2000);
		int PlayerMeso_ = Player::MainPlayer_->GetPlayerMeso();
		Inventory::MainInventory_->GetMesoFontRenderer()->SetText(std::to_string(PlayerMeso_));

		//if (true == IsQuestEnd_)
		//{
		//	Collision_->Off();
		//}

		QuestClearUI* QuestClear_ = GetLevel()->CreateActor<QuestClearUI>();
		QuestClear_->GetRenderer()->GetTransform().SetLocalPosition({ 194.f, -290.f });


		Item* ItemActor = GetLevel()->CreateActor<Item>(GAMEOBJGROUP::ITEM);
		ItemActor->MonsterName_ = MONSTERNAME::None;
		ItemActor->RendererTypeSetting();
		Inventory::MainInventory_->PushItem(ItemActor);

		IsQuestClear_ = false;
		IsQuestEnd_ = false;


	}


}

