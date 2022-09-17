#include "PreCompile.h"
#include "NPC_Castle.h"
#include "QuestClearUI.h"
#include "QuestUI.h"

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
	if (true == IsQuestClear_ || true == IsQuestEnd_)
	{
		QuestClearUI* QuestClear_ = GetLevel()->CreateActor<QuestClearUI>();
		QuestClear_->GetRenderer()->GetTransform().SetLocalPosition({ 194.f, -290.f });

		Collision_->Off();
		IsQuestClear_ = false;
		IsQuestEnd_ = false;

		return;
	}
}

