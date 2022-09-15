#include "PreCompile.h"
#include "ContentsFont.h"
#include <GameEngineCore/GameEngineFontRenderer.h>

ContentsFont::ContentsFont() 
	: FontRenderer_(nullptr)
	, TypeCount_(0)
	, TypingTimer_(0.f)
	, IsTypingEnd_(false)
	, NPCType_(NPCType::MAX)
	, IsLineChange_(false)
{
}

ContentsFont::~ContentsFont() 
{
}

void ContentsFont::TextRender(const std::string& _Text, int _Count, const std::string& _Font)
{
	// ���� ī��Ʈ ����
	TypeCount_ = _Count;
	std::string RenderingText = _Text.substr(0, TypeCount_);
	FontRenderer_->SetText(RenderingText);
}

void ContentsFont::SetNPCDialog(NPCType _NPCType)
{
	NPCType_ = _NPCType;

	switch (NPCType_)
	{
	case NPCType::NPC_Ariant:
	{
		Text_ = "��, �𷡱׸����� ����� �Ŀ��ڲ��� ���̱�. ��ħ ��ٸ��� �־���. �̹����߸��� �պ��� ������ ��ĥ �����ε�... ���� ��Ų����� �����ֽð���?";
	}
		break;
	case NPCType::NPC_Entrance:
	{
		Text_ = "����, ��? �� ���� ���� ����Ÿ���? �� ���� �ƹ��� �� �� �ִ� ���� �ƴϾ�! �Ƹ���Ʈ�� ��ź���� ��ô� ���̶��! ��? ������ ���� �ʹٰ�? �� ���� �ܺ��� ���谡�� ��� �ϰ� �鿩������� �ž�? ���� �ȵ�! ������...";
	}
		break;
	case NPCType::NPC_Castle:
	{
		Text_ = "���ɽ����� ������ ���� �պ��� ������ �ϳ� ���´�.";
	}
		break;
	default:
		break;
	}
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
	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		//// Ÿ������ �� �� ���� ���¿��� Ű�� ������ ��ü�� ���
		//if (false == IsTypingEnd_)
		//{
		//	TextRender(Text_, TypeCount_);
		//	IsTypingEnd_ = true;
		//}
		//else
		//{
		//	// Ÿ������ �� ���� ���¿��� Ű�� ������ ���� ������ �̵�
		//	IsTypingEnd_ = false;
		//}
	}

	if (TypingTimer_ > 0.05f)
	{
		for (int Count = TypeCount_; Count < Text_.size(); )
		{
			int TempCount = TypeCount_;
			if (TempCount != 0 && TempCount % 56 == 0)
			{
				std::string TempText1_ = Text_.substr(TempCount, 1);
				std::string TempText2_ = Text_.substr(TempCount + 2, 1);
				std::string TempText3_ = Text_.substr(TempCount + 4, 1);
				std::string TempText4_ = Text_.substr(TempCount + 5, 1);

				// �� ĭ �ڰ� �����̴� -> ���� �ڿ��� �ٹٲ�
				if (" " == TempText1_)
				{
					Text_.insert(TypeCount_ + 1, "\n");
				}
				else if(" " == TempText2_)
				{
					// �� ���� �ڰ� �����̴�
					Text_.insert(TypeCount_ + 3, "\n");					
				}
				else if (" " == TempText3_)
				{
					// �� ���� �ڰ� �����̴�
					Text_.insert(TypeCount_ + 5, "\n");
				}
				else
				{
					// �� ĭ �ڰ� ������ �ƴϴ� -> �ٷ� �ٹٲ�
					Text_.insert(TypeCount_, "\n");
				}

				// �ٹٲ��� �� ���� ����ҰŴϱ� ũ�� + 1
				TypeCount_ += 1;
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

