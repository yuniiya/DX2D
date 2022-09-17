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

	if (true == IsQuestEnd_)
	{
		QuestClearUI* QuestClear_ = GetLevel()->CreateActor<QuestClearUI>();
		QuestClear_->GetRenderer()->GetTransform().SetLocalPosition({ 194.f, -290.f });

		Collision_->Off();
		IsQuestClear_ = false;
		IsQuestEnd_ = false;

		return;
	}

	if (nullptr == QuestUI_)
	{
		return;
	}
	// 대화창이 꺼져있을 경우 콜리전 On
	if (false == QuestUI_->IsUpdate())
	{
		Collision_->On();
	}
}

