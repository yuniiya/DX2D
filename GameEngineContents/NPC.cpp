#include "PreCompile.h"
#include "NPC.h"
#include "Enums.h"
#include "Mouse.h"
#include "QuestUI.h"
#include "QuestClearUI.h"

NPC::NPC() 
	: Renderer_(nullptr)
	, QuestRenderer_(nullptr)
	, Collision_(nullptr)
	, NPCType_(NPCType::MAX)
	, IsClick_(false)
	, QuestUI_(nullptr)
	, IsQuestOngoing_(false)
	, IsQuestClear_(false)
	, IsQuestEnd_(false)
	, QuestClearRenderer_(nullptr)

{
}

NPC::~NPC() 
{
}

void NPC::SetNPCType(NPCType _NPCType)
{
	NPCType_ = _NPCType;

	switch (NPCType_)
	{
	case NPCType::NPC_Cactus:
	{
		Renderer_->SetTexture("NPC_Ariant.png");
		Renderer_->ScaleToTexture();
	}
	break;
	case NPCType::NPC_Entrance:
	{
		Renderer_->Off();
	}
	break;
	case NPCType::NPC_Castle:
	{
		Renderer_->Off();
		QuestRenderer_->Off();
	}
	break;
	}
}

void NPC::Start()
{
	GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::NPC});

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();

	QuestRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	QuestRenderer_->GetTransform().SetLocalScale({44.f, 46.f});
	QuestRenderer_->CreateFrameAnimationFolder("Quest0", FrameAnimation_DESC("Quest0", 0.18f));
	QuestRenderer_->CreateFrameAnimationFolder("Quest1", FrameAnimation_DESC("Quest1", 0.3f));
	QuestRenderer_->CreateFrameAnimationFolder("Quest2", FrameAnimation_DESC("Quest2", 0.2f));
	QuestRenderer_->ChangeFrameAnimation("Quest0");

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({80.f, 80.f});
	Collision_->ChangeOrder(GAMEOBJGROUP::NPC);
}

void NPC::Update(float _DeltaTime)
{
	CollisonCheck();
	
	if (nullptr == QuestUI_)
	{
		return;
	}

	if (true == IsQuestOngoing_ && false == IsQuestEnd_)
	{
		QuestRenderer_->ChangeFrameAnimation("Quest1");
	}
	else if (true == IsQuestEnd_)
	{
		QuestRenderer_->Off();
	}
	else if (true == IsQuestClear_ && false == IsQuestEnd_)
	{
		QuestRenderer_->ChangeFrameAnimation("Quest2");
	}

	//if (true == IsQuestClear_ || true == IsQuestEnd_)
	//{
	//	if (true == IsQuestEnd_)
	//	{
	//		Collision_->Off();
	//	}
 //		QuestClearUI* QuestClear_ = GetLevel()->CreateActor<QuestClearUI>();
	//	QuestClear_->GetRenderer()->GetTransform().SetLocalPosition({194.f, -290.f});
	//	
	//	IsQuestClear_ = false;
	//	IsQuestEnd_ = false;
	//}


}

void NPC::CollisonCheck()
{

	if (true == Collision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MAINMOUSE, CollisionType::CT_OBB2D))
	{
		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{ 
			QuestUI_ = GetLevel()->CreateActor<QuestUI>((int)GAMEOBJGROUP::UI);
			QuestUI_->SetNPC(this);
			QuestUI_->SetNPCType(NPCType_);
			Collision_->Off();
		}
	}
}
