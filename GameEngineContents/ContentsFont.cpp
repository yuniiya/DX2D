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
	// 누적 카운트 저장
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
		Text_ = "오, 모래그림단의 든든한 후원자께서 오셨군. 마침 기다리고 있었소. 이번에야말로 왕비의 보물을 훔칠 생각인데... 물론 당신께서도 도와주시겠지?";
	}
		break;
	case NPCType::NPC_Entrance:
	{
		Text_ = "뭐야, 넌? 왜 궁전 앞을 기웃거리지? 이 곳은 아무나 들어갈 수 있는 곳이 아니야! 아리안트의 술탄께서 계시는 곳이라고! 뭐? 궁전에 들어가고 싶다고? 너 같은 외부의 모험가를 어떻게 믿고 들여보내라는 거야? 절대 안돼! 하지만...";
	}
		break;
	case NPCType::NPC_Castle:
	{
		Text_ = "조심스럽게 서랍을 열어 왕비의 반지를 하나 꺼냈다.";
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
		//// 타이핑이 다 안 끝난 상태에서 키를 누르면 전체를 출력
		//if (false == IsTypingEnd_)
		//{
		//	TextRender(Text_, TypeCount_);
		//	IsTypingEnd_ = true;
		//}
		//else
		//{
		//	// 타이핑이 다 끝난 상태에서 키를 누르면 다음 장으로 이동
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

				// 한 칸 뒤가 공백이다 -> 공백 뒤에서 줄바꿈
				if (" " == TempText1_)
				{
					Text_.insert(TypeCount_ + 1, "\n");
				}
				else if(" " == TempText2_)
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

