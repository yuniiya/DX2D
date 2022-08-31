#include "PreCompile.h"
#include "NPC.h"
#include "Enums.h"

NPC::NPC() 
	: Renderer_(nullptr)
	, Collision_(nullptr)
	, NPCType_(NPCType::MAX)
{
}

NPC::~NPC() 
{
}

void NPC::Start()
{
	GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::NPC});

	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->ScaleToTexture();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale({ Renderer_->GetTransform().GetLocalScale() });

	switch (NPCType_)
	{
	case NPCType::NPC_Ariant:
	{
		Renderer_->SetTexture("NPC_Ariant");
	}
		break;
	case NPCType::NPC_Entrance:
		break;
	case NPCType::NPC_Castle:
		break;
	case NPCType::MAX:
		break;
	default:
		break;
	}
}

void NPC::Update(float _DeltaTime)
{
}

