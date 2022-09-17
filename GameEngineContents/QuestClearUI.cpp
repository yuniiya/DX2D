#include "PreCompile.h"
#include "QuestClearUI.h"

QuestClearUI::QuestClearUI() 
	: Renderer_(nullptr)
	, IsClearSoundOn_(true)
	, Time_(0.f)
	, IsQuestEnd_(false)
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
	Renderer_->GetTransform().SetLocalScale({209.f * 0.85f, 52.f * 0.85f});;
	Renderer_->GetPixelData().MulColor.a = 0;
}

void QuestClearUI::Update(float _DeltaTime)
{
	if (true == IsClearSoundOn_)
	{
		GameEngineSound::SoundPlayOneShot("QuestClear.mp3");
		IsClearSoundOn_ = false;
	}
	if (false == IsQuestEnd_)
	{
		Renderer_->GetPixelData().MulColor.a += _DeltaTime * 1.3f;

		if (1 <= Renderer_->GetPixelData().MulColor.a)
		{
			Time_ += _DeltaTime;
			Renderer_->GetPixelData().MulColor.a = 1;

			if (Time_ > 5.f)
			{
				Time_ = 0.f;
				IsQuestEnd_ = true;
				Death();
			}
			
		}
	}
}

