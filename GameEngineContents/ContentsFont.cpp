#include "PreCompile.h"
#include "ContentsFont.h"
#include <GameEngineCore/GameEngineFontRenderer.h>

ContentsFont::ContentsFont() 
	: FontRenderer_(nullptr)
	, Count_(1)
	, TypingTimer_(0.f)
{
}

ContentsFont::~ContentsFont() 
{
}

void ContentsFont::Start()
{
	FontRenderer_ = CreateComponent<GameEngineFontRenderer>();
	FontRenderer_->SetRenderingOrder((int)GAMEOBJGROUP::FONT);
	FontRenderer_->SetColor({ 0.0f, 0.0f, 0.0f, 1.0 });
	FontRenderer_->SetSize(13);
	FontRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);
	FontRenderer_->SetText("오, 모래그림단의 든든한 후원자께서 오셨군. 마침 기다리고 있었소. 이번에야말로 왕비의 보물을 훔칠 생각인데... 물론 당신께서도 도와주시겠지?");

	Off();
}

void ContentsFont::Update(float _DeltaTime)
{
	if (TypingTimer_ >= 0.5f)
	{
		Count_++;
		TypingTimer_ = 0.f;
	}

	TypingTimer_ += _DeltaTime;

	std::string Text = FontRenderer_->GetText();
	Text.substr(0, Count_);
}

