#include "PreCompile.h"
#include "QuestUI.h"

QuestUI::QuestUI() 
	: Renderer_(nullptr)
	, ExitCol(nullptr)
{
}

QuestUI::~QuestUI() 
{
}

void QuestUI::Start()
{
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::UI });

	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetTexture("DialogUI.png");
	Renderer_->GetTransform().SetLocalScale({751.f * 0.8f, 276.f * 0.8f});
}

void QuestUI::Update(float _DeltaTime)
{
	CollisionCheck();

	if (nullptr == this)
	{
		return;
	}
	if (true == GameEngineInput::GetInst()->IsDown("Exit"))
	{
		Death();
	}
}

void QuestUI::CollisionCheck()
{
	if (nullptr == this)
	{
		return;
	}


}
