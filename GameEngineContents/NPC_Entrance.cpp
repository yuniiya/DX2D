#include "PreCompile.h"
#include "NPC_Entrance.h"
#include "Inventory.h"
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "Item.h"
#include "QuestClearUI.h"
#include "QuestUI.h"
#include "ContentsFont.h"

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

	// ¿Õ±Ã ÃâÀÔ ÀÚ°ÝÁõ È¹µæ & 2000¸Þ¼Ò °¨¼Ò
	if (true == IsQuestEnd_)
	{
		Collision_->Off();
		IsQuestClear_ = false;
		IsQuestEnd_ = false;

		Player::MainPlayer_->IsEntranceQuestClear_ = true;
		Player::MainPlayer_->UsePlayerMeso(2000);
		int PlayerMeso_ = Player::MainPlayer_->GetPlayerMeso();
		Inventory::MainInventory_->GetContentsFontMeso()->GetNoramlFontRenderer()->SetText(std::to_string(PlayerMeso_));
		Inventory::MainInventory_->GetContentsFontMeso()->SetComma();

		QuestClearUI* QuestClear_ = GetLevel()->CreateActor<QuestClearUI>();
		QuestClear_->GetRenderer()->GetTransform().SetLocalPosition({ 194.f, -290.f });


		Item* ItemActor = GetLevel()->CreateActor<Item>(GAMEOBJGROUP::ITEM);
		ItemActor->MonsterName_ = MONSTERNAME::None;
		ItemActor->RendererTypeSetting();
		Inventory::MainInventory_->PushItem(ItemActor);
	}
	
	if (nullptr == QuestUI_)
	{
		return;
	}
	// ´ëÈ­Ã¢ÀÌ ²¨Á®ÀÖÀ» °æ¿ì ÄÝ¸®Àü On
	//if (false == QuestUI_->IsUpdate())
	//{
	//	Collision_->On();
	//}


}

