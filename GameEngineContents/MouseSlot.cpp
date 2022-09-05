#include "PreCompile.h"
#include "MouseSlot.h"
#include "Mouse.h"

MouseSlot::MouseSlot() 
	: HoldItemRenderer_(nullptr)
	, Collision_(nullptr)
	, IsHold_(false)
{
}

MouseSlot::~MouseSlot() 
{
}

void MouseSlot::Start()
{
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::UI });
	HoldItemRenderer_ = CreateComponent<GameEngineUIRenderer>();
	HoldItemRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	HoldItemRenderer_->GetTransform().SetLocalScale({ 128.f, 128.f });
	HoldItemRenderer_->Off();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->SetUIDebugCamera();
	Collision_->GetTransform().SetLocalScale({ 24.f, 26.f });
	Collision_->ChangeOrder(GAMEOBJGROUP::SLOTUI);

	//MouseCollision_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseCol();
	//MouseRenderer_ = dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseRenderer();
}

void MouseSlot::Update(float _DeltaTime)
{
	if (nullptr == dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse())
	{
		return;
	}


	HoldItemRenderer_->GetTransform().SetLocalPosition({ 
		dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseRenderer()->GetTransform().GetLocalPosition().x - 83.f
		, dynamic_cast<GlobalLevel*>(GetLevel())->GetMouse()->GetMouseRenderer()->GetTransform().GetLocalPosition().y + 80.f });

}

