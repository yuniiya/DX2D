#include "PreCompile.h"
#include "NPC_Castle.h"
#include "QuestClearUI.h"
#include "QuestUI.h"
#include "NPC_Cactus.h"

NPC_Castle::NPC_Castle() 
	: CastleCollision_(nullptr)
{
}

NPC_Castle::~NPC_Castle() 
{
}

void NPC_Castle::Start()
{
	NPC::Start();
	Collision_->Off();	// Cactus레벨 퀘스트 진행 중일 때만 Collision On

	//CastleCollision_ = CreateComponent<GameEngineCollision>();
	//CastleCollision_->GetTransform().SetLocalScale({ 80.f, 80.f });
	//CastleCollision_->ChangeOrder(GAMEOBJGROUP::NPC);
	//CastleCollision_->Off();
}

void NPC_Castle::Update(float _DeltaTime)
 {
	NPC::Update(_DeltaTime);


	if (true == Player::MainPlayer_->IsCactusQuestOngoing_)
	{
		Collision_->On();
	}
	if (true == IsQuestEnd_)
	{
 		Player::MainPlayer_->IsCastleQuestClear_ = true;

		QuestClearUI* QuestClear_ = GetLevel()->CreateActor<QuestClearUI>();
		QuestClear_->GetRenderer()->GetTransform().SetLocalPosition({ 194.f, -290.f });

		Collision_->Off();
		IsQuestClear_ = false;
		IsQuestEnd_ = false;
		Death();

		return;
	}
	//else if (QuestUI_->IsCactusQuestOngoing_ && false == IsQuestEnd_)	
	//{
	//	// Cactus퀘스트가 진행 중이고, Castle퀘스트가 완료되지 않았을 때
	//	Collision_->On();
	//}

}

