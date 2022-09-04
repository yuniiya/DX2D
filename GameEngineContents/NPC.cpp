#include "PreCompile.h"
#include "NPC.h"
#include "Enums.h"
#include "Mouse.h"
#include "QuestUI.h"

NPC::NPC() 
	: Renderer_(nullptr)
	, QuestRenderer_(nullptr)
	, Collision_(nullptr)
	, NPCType_(NPCType::MAX)
	, IsClick_(false)
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
	case NPCType::NPC_Ariant:
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

	//MouseCollision_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseCol();
	//MouseRenderer_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseRenderer();
	//MouseAnimationRenderer_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseAnimationRenderer();
}

void NPC::Update(float _DeltaTime)
{
	CollisonCheck();
}

void NPC::CollisonCheck()
{
	if (true == Collision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	{


		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			//QuestUI* Quest_ = GetLevel()->CreateActor<QuestUI>((int)GAMEOBJGROUP::UI);
		}
	}
}

