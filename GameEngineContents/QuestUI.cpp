#include "PreCompile.h"
#include "QuestUI.h"
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "ContentsFont.h"

QuestUI::QuestUI() 
	: Renderer_(nullptr)
	, ExitCol(nullptr)
	, UINPCRenderer_(nullptr)
	, NPCNameFont_(nullptr)
	, ButtonYes_(nullptr)
	, ButtonNo_(nullptr)
	, ButtonYesCol_(nullptr)
	, ButtonNoCol_(nullptr)
	, Font_(nullptr)
	, NPCType_(NPCType::MAX)
	, DialogCount_(0)
{
}

QuestUI::~QuestUI() 
{
}

void QuestUI::Start()
{
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::UI });

	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetTexture("DialogUI2.png");
	Renderer_->GetTransform().SetLocalScale({ 751.f * 0.8f, 276.f * 0.8f });

	UINPCRenderer_ = CreateComponent<GameEngineUIRenderer>();
	UINPCRenderer_->GetTransform().SetLocalPosition({ Renderer_->GetTransform().GetLocalPosition().x - 210.f
		, Renderer_->GetTransform().GetLocalPosition().y + 30.f });

	NPCNameFont_ = CreateComponent<GameEngineFontRenderer>();
	NPCNameFont_->SetRenderingOrder((int)GAMEOBJGROUP::FONT);
	NPCNameFont_->SetColor({ 1.0f, 1.0f, 1.0f, 1.0 });
	NPCNameFont_->SetSize(13);
	NPCNameFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	NPCNameFont_->SetScreenPostion({ UINPCRenderer_->GetTransform().GetLocalPosition().x + 600.f
		, -UINPCRenderer_->GetTransform().GetLocalPosition().y + 404.f });

	// 버튼
	ButtonYes_ = CreateComponent<GameEngineUIRenderer>();
	ButtonYes_->SetTexture("BtOK.normal.png");
	ButtonYes_->ScaleToTexture();
	ButtonYes_->GetTransform().SetLocalPosition({ Renderer_->GetTransform().GetLocalPosition().x + 200.f
		, Renderer_->GetTransform().GetLocalPosition().y - 93.f });

	ButtonNo_ = CreateComponent<GameEngineUIRenderer>();
	ButtonNo_->SetTexture("BtNo.normal.0.png");
	ButtonNo_->ScaleToTexture();
	ButtonNo_->GetTransform().SetLocalPosition({ Renderer_->GetTransform().GetLocalPosition().x + 265.f
	, Renderer_->GetTransform().GetLocalPosition().y - 93.f });

	ButtonYesCol_ = CreateComponent<GameEngineCollision>("ButtonYesCol");
	ButtonYesCol_->SetUIDebugCamera();
	ButtonYesCol_->GetTransform().SetLocalPosition(ButtonYes_->GetTransform().GetLocalPosition());
	ButtonYesCol_->GetTransform().SetLocalScale({ ButtonYes_->GetTransform().GetLocalScale().x / 2.f
		, ButtonYes_->GetTransform().GetLocalScale().y});
	ButtonYesCol_->ChangeOrder(GAMEOBJGROUP::UI);

	ButtonNoCol_ = CreateComponent<GameEngineCollision>("ButtonNoCol");
	ButtonNoCol_->SetUIDebugCamera();
	ButtonNoCol_->GetTransform().SetLocalPosition(ButtonNo_->GetTransform().GetLocalPosition());
	ButtonNoCol_->GetTransform().SetLocalScale({ ButtonNo_->GetTransform().GetLocalScale().x / 2.f
		, ButtonNo_->GetTransform().GetLocalScale().y });
	ButtonNoCol_->ChangeOrder(GAMEOBJGROUP::UI);

	ButtonOff();

	// Ariant
	TextSetting("오, 모래그림단의 든든한 후원자께서 오셨군. 마침 기다리고 있었소. 이번에야말로 왕비의 보물을 훔칠 생각인데... 물론 당신께서도 도와주시겠지?", NPCType::NPC_Ariant);
	//Str_ = "왕비의 장식장";
	TextSetting("하하하! 역시! 그럴 줄 알았소. 해야 할 일은 왕비의 장식장에서 왕비의 보물을 훔쳐오는 것이라오. 궁전 가장 깊은 곳, 왕의 옆 쪽에 있는 장식장까지 가는 것이 물론 쉽지 않은 일이지만 모래그림단을 위한 일이잖소? 당신이라면 해낼 거라고 믿소.후후후....", NPCType::NPC_Ariant);
	TextSetting("보석을 새로 들여놓은지 얼마 되지 않아서 궁 안은 경비가 삼엄하오. 최대한 조심스럽게 장식장으로 가서 보물을 찾아오시오. 그럼 기대하겠소.", NPCType::NPC_Ariant);

	// Entrance
	TextSetting("뭐야, 넌? 왜 궁전 앞을 기웃거리지? 이 곳은 아무나 들어갈 수 있는 곳이 아니야! 아리안트의 술탄께서 계시는 곳이라고! 뭐? 궁전에 들어가고 싶다고? 너 같은 외부의 모험가를 어떻게 믿고 들여보내라는 거야? 절대 안돼! 하지만...", NPCType::NPC_Entrance);
	TextSetting("궁전에 꼭 들어가고 싶다면, 들어가게 해줄 수도 있지. 네가 술탄에게 충성한다는 표시를 보인다면, 뭐 들여보내 줄 수도 있어. 어떻게 하면 되냐고? 험험. 그거야 간단하지. 2000메소만 내. 아리안트와 술탄을 위한 충성의 표시로 말이야.", NPCType::NPC_Entrance);
	TextSetting("이히힛, 좋아. 넌 확실히 술탄에게 충성하는 사람이군. 무척 믿음이 가는걸? 그럼 너에게 이 궁전 출입 자격증을 줄게. 이것만 있으면 왕궁 어디든지 갈 수 있을거야. 감사하게 생각하라고.", NPCType::NPC_Entrance);

	// Castle
	TextSetting("조심스럽게 서랍을 열어 왕비의 반지를 하나 꺼냈다.", NPCType::NPC_Castle);
}

void QuestUI::Update(float _DeltaTime)
{
	CollisionCheck();

	if (nullptr == this)
	{
		return;
	}

	if (true == GameEngineInput::GetInst()->IsDown("Exit"))
	{
		DialogCount_ = 0;
		Font_->Off();
		Death();
	}

	// 다음 장으로 넘긴다
	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		ChangeToNextDialog();
	}
}

void QuestUI::CollisionCheck()
{
	if (nullptr == this)
	{
		return;
	}

	if (true == ButtonYesCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	{
		ButtonYes_->SetTexture("BtOK.mouseOver.0.png");

		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			ChangeToNextDialog();
		}
	}
	else
	{
		ButtonYes_->SetTexture("BtOK.normal.png");
	}

	if (true == ButtonNoCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	{
		ButtonNo_->SetTexture("BtNo.mouseOver.0.png");

		if (true == GameEngineInput::GetInst()->IsDown("LeftMouse"))
		{
			ResetDialog();
		}
	}
	else
	{
		ButtonNo_->SetTexture("BtNo.normal.0.png");
	}

}

void QuestUI::SetNPCType(NPCType _NPCType)
{
	NPCType_ = _NPCType;

	Font_ = GetLevel()->CreateActor<ContentsFont>();
	Font_->GetFontRenderer()->SetScreenPostion({ Renderer_->GetTransform().GetLocalPosition().x + 540.f, 
		Renderer_->GetTransform().GetLocalPosition().y + 300.f});
	Font_->On();

	switch (NPCType_)
	{
	case NPCType::NPC_Ariant:
	{
		UINPCRenderer_->SetTexture("NPC1.png");
		NPCNameFont_->SetText(" 수상한 남자");
		Font_->SetText(AriantDialogList_[DialogCount_]);
		ButtonOn();
	}
		break;
	case NPCType::NPC_Entrance:
	{
		UINPCRenderer_->SetTexture("NPC2.png");
		NPCNameFont_->SetText("      티건");
		Font_->SetText(EntranceDialogList_[DialogCount_]);
	}
		break;
	case NPCType::NPC_Castle:
	{
		UINPCRenderer_->SetTexture("NPC3.png");
		NPCNameFont_->SetText("왕비의 장식장");
		Font_->SetText(CastleDialogList_[DialogCount_]);
	}
		break;
	}

	UINPCRenderer_->ScaleToTexture();

}


// 텍스트를 만들어서 각 NPC타입에 맞는 벡터에 넣어주는 함수
void QuestUI::TextSetting(const std::string& _Text, NPCType _NPCType)
{
	std::string Text = _Text;

	switch (_NPCType)
	{
	case NPCType::NPC_Ariant:
	{
		AriantDialogList_.push_back(Text);
	}
	break;
	case NPCType::NPC_Entrance:
	{
		EntranceDialogList_.push_back(Text);
	}
	break;
	case NPCType::NPC_Castle:
	{
		CastleDialogList_.push_back(Text);
	}
	break;
	default:
		break;
	}
}

void QuestUI::ResetDialog()
{
	DialogCount_ = 0;
	Font_->Off();
	Death();
}

void QuestUI::ButtonOn()
{
	ButtonYes_->On();
	ButtonYesCol_->On();
	ButtonNo_->On();
	ButtonNoCol_->On();
}

void QuestUI::ButtonOff()
{
	ButtonYes_->Off();
	ButtonYesCol_->Off();
	ButtonNo_->Off();
	ButtonNoCol_->Off();
}

void QuestUI::ChangeToNextDialog()
{
	Font_->ResetType();
	Font_->ResetByteCount();
	DialogCount_ += 1;

	switch (NPCType_)
	{
	case NPCType::NPC_Ariant:
	{
		if (DialogCount_ == 1)			// 2장
		{
			ButtonOff();
		}
		else if (DialogCount_ == 3)		// 3장
		{
			ResetDialog();
			return;
		}

		Font_->SetText(AriantDialogList_[DialogCount_]);
	}
	break;
	case NPCType::NPC_Entrance:
	{
		if (DialogCount_ == 1)
		{
			ButtonOn();
		}
		else if (DialogCount_ == 2)
		{
			ButtonOff();
		}
		else if (DialogCount_ == 3)
		{
			ResetDialog();
			return;
		}

		Font_->SetText(EntranceDialogList_[DialogCount_]);
	}
	break;
	case NPCType::NPC_Castle:
	{
		ResetDialog();
		return;
	}
	break;
	default:
		break;
	}
}
