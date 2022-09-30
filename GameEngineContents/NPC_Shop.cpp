#include "PreCompile.h"
#include "NPC_Shop.h"
#include "Shop.h"


NPC_Shop::NPC_Shop() 
	: ShopUI_(nullptr)
	, IsShopOn_(false)
{
}

NPC_Shop::~NPC_Shop() 
{
}

void NPC_Shop::Start()
{
	NPC::Start();
	ShopUI_ = GetLevel()->CreateActor<Shop>((int)GAMEOBJGROUP::UI);
	ShopUI_->GetTransform().SetLocalPosition({0.f, 40.f, (int)ZOrder::UI});
	ShopUI_->Off();
}

void NPC_Shop::Update(float _DeltaTime)
{
	ShopOnOff();
}

void NPC_Shop::ShopOnOff()
{
	if (false == IsShopOn_)
	{
		if (true == Collision_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MAINMOUSE, CollisionType::CT_OBB2D)
			&& true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			ShopUI_->On();
		}
	}
}

