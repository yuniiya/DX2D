#include "PreCompile.h"
#include "QuestClearUI.h"

QuestClearUI::QuestClearUI() 
	: Renderer_(nullptr)
	, IsClearSoundOn_(true)
	, AlertTime_(0.f)
{
}

QuestClearUI::~QuestClearUI() 
{
}

void QuestClearUI::Start()
{
	GetTransform().SetLocalPosition({0.f, 0.f, (int)ZOrder::UI});

	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetTexture("QuestClear.png");
	Renderer_->GetTransform().SetLocalScale({209.f * 0.9f, 52.f * 0.9f});
	Renderer_->GetTransform().SetLocalPosition({ 180.f, -300.f });
	Renderer_->Off();
}

void QuestClearUI::Update(float _DeltaTime)
{
	if (true == IsClearSoundOn_)
	{
		GameEngineSound::SoundPlayOneShot("QuestClear.mp3");
		IsClearSoundOn_ = false;
		Renderer_->On();
	}
	//if (AlertTime_ > 2.f)
	//{
	//	Renderer_->GetPixelData().MulColor -= GameEngineTime::GetDeltaTime() * 1.8f;

	//	if (Renderer_->GetPixelData().MulColor.a < 0)
	//	{
	//		AlertTime_ = 0.f;
	//		Death();
	//	}
	//}
}

