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
				std::string TempText1_ = Text_.substr(TempCount, 1);		// 1����Ʈ ��
				std::string TempText2_ = Text_.substr(TempCount + 1, 1);	// 2����Ʈ ��
				std::string TempText3_ = Text_.substr(TempCount + 3, 1);	// 4����Ʈ ��
				//std::string TempText4_ = Text_.substr(TempCount + 5, 1);


				if ("," == TempText1_ && " " == TempText2_)
				{
					// ���� �ڿ� ������ �ִ� -> ������ �ƴ� ���� �� + �ѱۿ��� �ٹٲ� 
					Text_.insert(TypeCount_ + 4, "\n");

					Count += 5;
					TypeCount_ += 5;
				}
				else if (" " == TempText1_)// �� ĭ �ڰ� �����̴� -> ���� �ڿ��� �ٹٲ�
				{
					Text_.insert(TypeCount_ + 1, "\n");

					Count += 2;
					TypeCount_ += 2;
				}
				else
				{
					// �о� �ü� ���� -> �ѱ� 
					// �ѱ� �ڿ� ������ �ִ� -> �ѱ� + ���麸�� �� ĭ �ڿ��� �ٹٲ�
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
				// �ٹٲ��� �� ���� ����ҰŴϱ� ũ�� + 1
				break;
			}

			// ��ü �ؽ�Ʈ���� 1����Ʈ�� �߶�´� ex) 0����Ʈ ������ ���, 0 ~ 1����Ʈ �߶����
			SubText_ = Text_.substr(Count, 1);

			// ���� -> 1����Ʈ
			if (" " == SubText_ || "," == SubText_ || "." == SubText_ || "?" == SubText_ || "!" == SubText_)
			{
				Count += 1;
			}
			else
			{
				// �ѱ�
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
	// ���� ī��Ʈ ����
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
				std::string TempText1_ = Text_.substr(TempCount, 1);		// 1����Ʈ ��
				std::string TempText2_ = Text_.substr(TempCount + 1, 1);	// 2����Ʈ ��
				std::string TempText3_ = Text_.substr(TempCount + 3, 1);	// 4����Ʈ ��
				//std::string TempText4_ = Text_.substr(TempCount + 5, 1);


				if ("," == TempText1_ && " " == TempText2_)
				{
					// ���� �ڿ� ������ �ִ� -> ������ �ƴ� ���� �� + �ѱۿ��� �ٹٲ� 
					Text_.insert(TypeCount_ + 4, "\n");

					Count += 5;
					TypeCount_ += 5;
				}
				else if (" " == TempText1_)// �� ĭ �ڰ� �����̴� -> ���� �ڿ��� �ٹٲ�
				{
					Text_.insert(TypeCount_ + 1, "\n");

					Count += 2;
					TypeCount_ += 2;
				}
				else
				{
					// �о� �ü� ���� -> �ѱ� 
					// �ѱ� �ڿ� ������ �ִ� -> �ѱ� + ���麸�� �� ĭ �ڿ��� �ٹٲ�
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
				// �ٹٲ��� �� ���� ����ҰŴϱ� ũ�� + 1
				break;
			}

			// ��ü �ؽ�Ʈ���� 1����Ʈ�� �߶�´� ex) 0����Ʈ ������ ���, 0 ~ 1����Ʈ �߶����
			SubText_ = Text_.substr(Count, 1);

			// ���� -> 1����Ʈ
			if (" " == SubText_ || "," == SubText_ || "." == SubText_ || "?" == SubText_ || "!" == SubText_)
			{
				Count += 1;
			}
			else
			{
				// �ѱ�
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
				std::string TempText1_ = Text_.substr(TempCount, 1);		// 1����Ʈ ��
				std::string TempText2_ = Text_.substr(TempCount + 1, 1);	// 2����Ʈ ��
				std::string TempText3_ = Text_.substr(TempCount + 3, 1);	// 4����Ʈ ��
				//std::string TempText4_ = Text_.substr(TempCount + 5, 1);

				
  				if ("," == TempText1_ && " " == TempText2_)
				{
					// ���� �ڿ� ������ �ִ� -> ������ �ƴ� ���� �� + �ѱۿ��� �ٹٲ� 
					Text_.insert(TypeCount_ + 4, "\n");

					Count += 5;
					TypeCount_ += 5;
				}
				else if (" " == TempText1_)// �� ĭ �ڰ� �����̴� -> ���� �ڿ��� �ٹٲ�
				{
 					Text_.insert(TypeCount_ + 1, "\n");

					Count += 2;
					TypeCount_ += 2;
				}
				else
				{
					// �о� �ü� ���� -> �ѱ� 
					// �ѱ� �ڿ� ������ �ִ� -> �ѱ� + ���麸�� �� ĭ �ڿ��� �ٹٲ�
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
				// �ٹٲ��� �� ���� ����ҰŴϱ� ũ�� + 1
				break;
			}

			// ��ü �ؽ�Ʈ���� 1����Ʈ�� �߶�´� ex) 0����Ʈ ������ ���, 0 ~ 1����Ʈ �߶����
			SubText_ = Text_.substr(Count, 1);

			// ���� -> 1����Ʈ
			if (" " == SubText_ || "," == SubText_ || "." == SubText_ || "?" == SubText_ || "!" == SubText_)
			{
				Count += 1;
			}
			else
			{
				// �ѱ�
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

