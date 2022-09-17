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
	
	if (true == IsQuestClear_)
	{
		QuestClearUI* QuestClear_ = GetLevel()->CreateActor<QuestClearUI>();
		QuestClear_->GetRenderer()->GetTransform().SetLocalPosition({180.f, -200.f});
		
		IsQuestClear_ = false;
	}

	if (nullptr == QuestUI_)
	{
		return;
	}

	// 대화창이 꺼져있을 때만 NPC 클릭
	if (false == QuestUI_->IsUpdate())
	{
		if (true == IsQuestOngoing_)
		{
			QuestRenderer_->ChangeFrameAnimation("Quest1");
			Collision_->Off();
		}
		else if (true == IsQuestEnd_)
		{
			QuestRenderer_->Off();
			Collision_->Off();
		}
		else if (true == IsQuestClear_)
		{
			QuestRenderer_->ChangeFrameAnimation("Quest2");
			Collision_->Off();
		}
		else
		{
			Collision_->On();
		}
	}

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
