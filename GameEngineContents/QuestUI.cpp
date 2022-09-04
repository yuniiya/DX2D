#include "PreCompile.h"
#include "QuestUI.h"

QuestUI::QuestUI() 
	: Renderer_(nullptr)
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
	Renderer_->ScaleToTexture();
	Renderer_->GetTransform().SetLocalPosition({GameEngineWindow::GetScale().x / 2.f, GameEngineWindow::GetScale().y / 2.f });
	Renderer_->Off();
}

void QuestUI::Update(float _DeltaTime)
{
}

void QuestUI::CollisionCheck()
{
	
}
