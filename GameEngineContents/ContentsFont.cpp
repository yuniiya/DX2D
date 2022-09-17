#include "PreCompile.h"
#include "ContentsFont.h"
#include <GameEngineCore/GameEngineFontRenderer.h>

ContentsFont::ContentsFont() 
	: FontRenderer_(nullptr)
	, TypeCount_(0)
	, TypingTimer_(0.f)
	, IsTypingEnd_(false)
	, NPCType_(NPCType::MAX)
	, LineChangeCount_(0)
	, ByteCount_(0)
	, ZeroTimer_(0.0f)
{
}

ContentsFont::~ContentsFont() 
{
}

void ContentsFont::TextRenderingUpdate()
{
	if (TypingTimer_ > 0.05f)
	{
		ByteCount_ += 1;

		for (int Count = TypeCount_; Count < Text_.size(); )
		{
			int TempCount = TypeCount_;
			if (ByteCount_ != 0 && ByteCount_ % 34 == 0)
			{
				std::string TempText1_ = Text_.substr(TempCount, 1);		// 1바이트 뒤
				std::string TempText2_ = Text_.substr(TempCount + 1, 1);	// 2바이트 뒤
				std::string TempText3_ = Text_.substr(TempCount + 3, 1);	// 4바이트 뒤
				//std::string TempText4_ = Text_.substr(TempCount + 5, 1);


				if ("," == TempText1_ && " " == TempText2_)
				{
					// 반점 뒤에 공백이 있다 -> 반점이 아닌 공백 뒤 + 한글에서 줄바꿈 
					Text_.insert(TypeCount_ + 4, "\n");

					Count += 5;
					TypeCount_ += 5;
				}
				else if (" " == TempText1_)// 한 칸 뒤가 공백이다 -> 공백 뒤에서 줄바꿈
				{
					Text_.insert(TypeCount_ + 1, "\n");

					Count += 2;
					TypeCount_ += 2;
				}
				else
				{
					// 읽어 올수 없다 -> 한글 
					// 한글 뒤에 공백이 있다 -> 한글 + 공백보다 한 칸 뒤에서 줄바꿈
					if (" " == TempText3_)
					{
						Text_.insert(TypeCount_ + 4, "\n");

						Count += 5;
						TypeCount_ += 5;
					}
					else
					{
						Text_.insert(TypeCount_ + 2, "\n");

						Count += 2;
						TypeCount_ += 2;
					}

				}

				ByteCount_ = 0;
				// 줄바꿈한 곳 까지 출력할거니까 크기 + 1
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
	if (TypingTimer_ > ZeroTimer_ && true == IsTypingEnd_)
	{
		ByteCount_ += 1; 

		for (int Count = TypeCount_; Count < Text_.size(); )
		{
			int TempCount = TypeCount_;
			if (ByteCount_ != 0 && ByteCount_ % 34 == 0)
			{
				std::string TempText1_ = Text_.substr(TempCount, 1);		// 1바이트 뒤
				std::string TempText2_ = Text_.substr(TempCount + 1, 1);	// 2바이트 뒤
				std::string TempText3_ = Text_.substr(TempCount + 3, 1);	// 4바이트 뒤
				//std::string TempText4_ = Text_.substr(TempCount + 5, 1);


				if ("," == TempText1_ && " " == TempText2_)
				{
					// 반점 뒤에 공백이 있다 -> 반점이 아닌 공백 뒤 + 한글에서 줄바꿈 
					Text_.insert(TypeCount_ + 4, "\n");

					Count += 5;
					TypeCount_ += 5;
				}
				else if (" " == TempText1_)// 한 칸 뒤가 공백이다 -> 공백 뒤에서 줄바꿈
				{
					Text_.insert(TypeCount_ + 1, "\n");

					Count += 2;
					TypeCount_ += 2;
				}
				else
				{
					// 읽어 올수 없다 -> 한글 
					// 한글 뒤에 공백이 있다 -> 한글 + 공백보다 한 칸 뒤에서 줄바꿈
					if (" " == TempText3_)
					{
						Text_.insert(TypeCount_ + 4, "\n");

						Count += 5;
						TypeCount_ += 5;
					}
					else
					{
						Text_.insert(TypeCount_ + 2, "\n");

						Count += 2;
						TypeCount_ += 2;
					}

				}

				ByteCount_ = 0;
				// 줄바꿈한 곳 까지 출력할거니까 크기 + 1
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
		//IsTypingEnd_ = false;
	}

	if (TypingTimer_ > 0.03f && true != IsTypingEnd_)
	{
		ByteCount_ += 1;

		for (int Count = TypeCount_; Count < Text_.size(); )
		{
			int TempCount = TypeCount_;
			if (ByteCount_ != 0 && ByteCount_ % 34 == 0)
			{
				std::string TempText1_ = Text_.substr(TempCount, 1);		// 1바이트 뒤
				std::string TempText2_ = Text_.substr(TempCount + 1, 1);	// 2바이트 뒤
				std::string TempText3_ = Text_.substr(TempCount + 3, 1);	// 4바이트 뒤
				//std::string TempText4_ = Text_.substr(TempCount + 5, 1);

				
  				if ("," == TempText1_ && " " == TempText2_)
				{
					// 반점 뒤에 공백이 있다 -> 반점이 아닌 공백 뒤 + 한글에서 줄바꿈 
					Text_.insert(TypeCount_ + 4, "\n");

					Count += 5;
					TypeCount_ += 5;
				}
				else if (" " == TempText1_)// 한 칸 뒤가 공백이다 -> 공백 뒤에서 줄바꿈
				{
 					Text_.insert(TypeCount_ + 1, "\n");

					Count += 2;
					TypeCount_ += 2;
				}
				else
				{
					// 읽어 올수 없다 -> 한글 
					// 한글 뒤에 공백이 있다 -> 한글 + 공백보다 한 칸 뒤에서 줄바꿈
					if (" " == TempText3_)
					{
						Text_.insert(TypeCount_ + 4, "\n");

						Count += 5;
						TypeCount_ += 5;
					}
					else
					{
						Text_.insert(TypeCount_ + 2, "\n");

						Count += 2;
						TypeCount_ += 2;
					}
			
				}

				ByteCount_ = 0;
				// 줄바꿈한 곳 까지 출력할거니까 크기 + 1
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

