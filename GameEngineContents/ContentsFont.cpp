#include "PreCompile.h"
#include "ContentsFont.h"
#include <GameEngineCore/GameEngineFontRenderer.h>

ContentsFont::ContentsFont() 
	: FontRenderer_(nullptr)
	, TypeCount_(0)
	, TypingTimer_(0.f)
	, IsTypingEnd_(false)
	, NPCType_(NPCType::MAX)

{
}

ContentsFont::~ContentsFont() 
{
}

void ContentsFont::TextRenderingUpdate()
{
	if (TypingTimer_ >= 0.05f)
	{
		for (int Count = TypeCount_; Count < Text_.size(); )
		{
			int TempCount = TypeCount_;
			if (TempCount != 0 && TempCount % 56 == 0)
			{
				std::string TempText1_ = Text_.substr(TempCount, 1);
				std::string TempText2_ = Text_.substr(TempCount + 2, 1);
				std::string TempText3_ = Text_.substr(TempCount + 4, 1);
				//std::string TempText4_ = Text_.substr(TempCount + 5, 1);

				// 한 칸 뒤가 공백이다 -> 공백 뒤에서 줄바꿈
				if (" " == TempText1_)
				{
					Text_.insert(TypeCount_ + 1, "\n");
				}
				else if (" " == TempText2_)
				{
					// 한 글자 뒤가 공백이다
					Text_.insert(TypeCount_ + 3, "\n");
				}
				else if (" " == TempText3_)
				{
					// 두 글자 뒤가 공백이다
					Text_.insert(TypeCount_ + 5, "\n");
				}
				else
				{
					// 한 칸 뒤가 공백이 아니다 -> 바로 줄바꿈
					Text_.insert(TypeCount_, "\n");
				}

				// 줄바꿈한 곳 까지 출력할거니까 크기 + 1
				TypeCount_ += 1;
				break;
			}

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
}

void ContentsFont::TextRender(const std::string& _Text, int _Count, const std::string& _Font)
{
	// 누적 카운트 저장
	TypeCount_ = _Count;
	std::string RenderingText = _Text.substr(0, TypeCount_);
	FontRenderer_->SetText(RenderingText);
}

void ContentsFont::SetText(const std::string& _Text)
{
	Text_ = _Text;
}


void ContentsFont::Start()
{ 
	FontRenderer_ = CreateComponent<GameEngineFontRenderer>();
	FontRenderer_->SetRenderingOrder((int)GAMEOBJGROUP::FONT);
	FontRenderer_->SetColor({ 0.0f, 0.0f, 0.0f, 1.0 });
	FontRenderer_->SetSize(13);
	FontRenderer_->ChangeCamera(CAMERAORDER::UICAMERA);

	Off();
}

void ContentsFont::Update(float _DeltaTime)
{
	if (TypingTimer_ >= 0.05f)
	{
		for (int Count = TypeCount_; Count < Text_.size(); )
		{
 			int TempCount = TypeCount_;
			ChangeLineCount_ = 56;
			if (TempCount != 0 && TempCount % ChangeLineCount_ == 0)
			{
	
 				std::string TempText1_ = Text_.substr(TempCount, 1);
				std::string TempText2_ = Text_.substr(TempCount + 2, 1);
				std::string TempText3_ = Text_.substr(TempCount + 4, 1);
				//std::string TempText4_ = Text_.substr(TempCount + 5, 1);

				// 한 칸 뒤가 공백이다 -> 공백 뒤에서 줄바꿈
				if (" " == TempText1_)
				{
					Text_.insert(TypeCount_ + 1, "\n");
				}
				else if (" " == TempText2_)
				{
					// 한 글자 뒤가 공백이다
					Text_.insert(TypeCount_ + 3, "\n");
				}
				else if (" " == TempText3_)
				{
					// 두 글자 뒤가 공백이다
					Text_.insert(TypeCount_ + 5, "\n");
				}
				else
				{
					// 한 칸 뒤가 공백이 아니다 -> 바로 줄바꿈
					Text_.insert(TypeCount_, "\n");
				}

				// 줄바꿈한 곳 까지 출력할거니까 크기 + 1
				TypeCount_ += 1;
				break;
			}

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

