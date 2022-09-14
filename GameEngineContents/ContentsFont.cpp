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
	FontRenderer_->SetText("��, �𷡱׸����� ����� �Ŀ��ڲ��� ���̱�. ��ħ ��ٸ��� �־���. �̹����߸��� �պ��� ������ ��ĥ �����ε�... ���� ��Ų����� �����ֽð���?");

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

