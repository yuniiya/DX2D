#include "PreCompile.h"
#include "ContentsFont.h"
#include <GameEngineCore/GameEngineFontRenderer.h>

ContentsFont::ContentsFont() 
	: FontRenderer_(nullptr)
	, TypeCount_(0)
	, TypingTimer_(0.f)
	, IsTypingEnd_(false)
{
}

ContentsFont::~ContentsFont() 
{
}

void ContentsFont::TextRender(const std::string& _Text, int _Count, const std::string& _Font)
{
	// 누적 카운트 저장
	TypeCount_ = _Count;
	std::string RenderingText = _Text.substr(0, TypeCount_);
	FontRenderer_->SetText(RenderingText);
}

void ContentsFont::Start()
{
	FontRenderer_ = CreateComponent<GameEngineFontRenderer>();
	FontRenderer_->SetRenderingOrder((int)GAMEOBJGROUP::FONT);
	FontRenderer_->SetColor({ 0.0f, 0.0f, 0.0f, 1.0 });
	FontRenderer_->SetSize(13);
	FontRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);
	Text_ = "오, 모래그림단의 든든한 후원자께서 오셨군. 마침 기다리고 있었소. 이번에야말로 왕비의 보물을 훔칠 생각인데... 물론 당신께서도 도와주시겠지?";
	
	Off();
}

void ContentsFont::Update(float _DeltaTime)
{
	if (TypingTimer_ > 0.4f)
	{
		for (int Count = TypeCount_; Count < Text_.size(); )
		{
			// 전체 텍스트에서 1바이트씩 잘라온다 ex) 0바이트 시작일 경우, 0 ~ 1바이트 잘라오기
			SubText_ = Text_.substr(Count, 1);
			 
			// 띄어쓰기 -> 1바이트
			if (" " == SubText_ || "," == SubText_ || "." == SubText_ || "?" == SubText_ || "!" == SubText_)
			{
				Count += 1;
			}
			else
			{
				// 한글
				Count += 2;
			}

			TypeCount_ = Count;
			break;

		}

		TextRender(Text_, TypeCount_);
		TypingTimer_ = 0.0f;
	}



	TypingTimer_ += _DeltaTime;
}

