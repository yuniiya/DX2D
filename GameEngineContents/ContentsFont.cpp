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
	// ���� ī��Ʈ ����
	TypeCount_ = _Count;
	std::string RenderingText = _Text.substr(0, TypeCount_);
	FontRenderer_->SetText(RenderingText);
}

void ContentsFont::SetNPCDialog(NPCType _NPCType)
{
	switch (_NPCType)
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
	case NPCType::MAX:
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
	if (TypingTimer_ > 0.1f)
	{
		for (int Count = TypeCount_; Count < Text_.size(); )
		{
		/*	if (TypeCount_ == 10)
			{
				std::string Line = "/n";
				Text_.insert(Count, Line);
			}*/

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

