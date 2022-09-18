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
	Collision_->Off();	// Cactus���� ����Ʈ ���� ���� ���� Collision On

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
	//	// Cactus����Ʈ�� ���� ���̰�, Castle����Ʈ�� �Ϸ���� �ʾ��� ��
	//	Collision_->On();
	//}

}

