#include "PreCompile.h"
#include "NPC_Cactus.h"
#include "QuestClearUI.h"
#include "QuestUI.h"

NPC_Cactus::NPC_Cactus()
{
}

NPC_Cactus::~NPC_Cactus()
{
}

void NPC_Cactus::Start()
{
	NPC::Start();
}

void NPC_Cactus::Update(float _DeltaTime)
{
	NPC::Update(_DeltaTime);

	if (true == Player::MainPlayer_->IsCactusQuestEnd_)
	{
		Collision_->Off();
		return;
	}
	else if (true == IsQuestEnd_ && true == IsQuestClear_)
	{
		QuestClearUI* QuestClear_ = GetLevel()->CreateActor<QuestClearUI>();
		QuestClear_->GetRenderer()->GetTransform().SetLocalPosition({ 194.f, -290.f });

		Collision_->Off();
		IsQuestClear_ = false;
		IsQuestEnd_ = false;

		return;
	}

	if (true == Player::MainPlayer_->IsCastleQuestClear_)
	{
		IsQuestOngoing_ = false;
		IsQuestClear_ = true;
		Player::MainPlayer_->IsCactusQuestClear_ = true;
		Collision_->On();
	}
	else if (true == IsQuestOngoing_ && false == Player::MainPlayer_->IsCastleQuestClear_)
	{
		Player::MainPlayer_->IsCactusQuestOngoing_ = true;
  		Collision_->Off();
	}   

}

