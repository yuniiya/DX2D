#include "PreCompile.h"
#include "QuestUI.h"
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "ContentsFont.h"
#include "NPC.h"
#include "NPC_Cactus.h"

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
	, IsQuestOngoing_(false)
	, IsQuestClear_(false)
	, IsQuestEnd_(false)

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

	// ��ư
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
		, ButtonYes_->GetTransform().GetLocalScale().y });
	ButtonYesCol_->ChangeOrder(GAMEOBJGROUP::UI);

	ButtonNoCol_ = CreateComponent<GameEngineCollision>("ButtonNoCol");
	ButtonNoCol_->SetUIDebugCamera();
	ButtonNoCol_->GetTransform().SetLocalPosition(ButtonNo_->GetTransform().GetLocalPosition());
	ButtonNoCol_->GetTransform().SetLocalScale({ ButtonNo_->GetTransform().GetLocalScale().x / 2.f
		, ButtonNo_->GetTransform().GetLocalScale().y });
	ButtonNoCol_->ChangeOrder(GAMEOBJGROUP::UI);

	ButtonOff();

	// Ariant
	TextSetting("��, �𷡱׸����� ����� �Ŀ��ڲ��� ���̱�. ��ħ ��ٸ��� �־���. �̹����߸��� �պ��� ������ ��ĥ �����ε�... ���� ��Ų����� �����ֽð���?", NPCType::NPC_Cactus);
	TextSetting("������! ����! �׷� �� �˾Ҽ�. �ؾ� �� ���� �պ��� ����忡�� �պ��� ������ ���Ŀ��� ���̶��. ���� ���� ���� ��, ���� �� �ʿ� �ִ� �������� ���� ���� ���� ���� ���� �������� �𷡱׸����� ���� �����ݼ�? ����̶�� �س� �Ŷ�� �ϼ�.������....", NPCType::NPC_Cactus);
	TextSetting("������ ���� �鿩������ �� ���� �ʾƼ� �� ���� ��� ����Ͽ�. �ִ��� ���ɽ����� ��������� ���� ������ ã�ƿ��ÿ�. �׷� ����ϰڼ�.", NPCType::NPC_Cactus);
	TextSetting("����ÿ�! �պ��� ������ �������̼�? ����, ����~ �̰� �ٷ� �պ� ���� �� �� �����α�. ������... �ȸ� ���� �� �ǰھ�.", NPCType::NPC_Cactus);
	TextSetting("��� ���п� ��������...�ƴ�, �� �׸����� ���� ���� ���� ����ǰ� �ִٷ�. ���� ����. ������... �����ε� ��� �����ֱ� �ٶ��.", NPCType::NPC_Cactus);

	// Entrance
	TextSetting("����, ��? �� ���� ���� ����Ÿ���? �� ���� �ƹ��� �� �� �ִ� ���� �ƴϾ�! �Ƹ���Ʈ�� ��ź���� ��ô� ���̶��! ��? ������ ���� �ʹٰ�? �� ���� �ܺ��� ���谡�� ��� �ϰ� �鿩������� �ž�? ���� �ȵ�! ������...", NPCType::NPC_Entrance);
	TextSetting("������ �� ���� �ʹٸ�, ���� ���� ���� ����. �װ� ��ź���� �漺�Ѵٴ� ǥ�ø� ���δٸ�, �� �鿩���� �� ���� �־�. ��� �ϸ� �ǳİ�? ����. �װž� ��������. 2000�޼Ҹ� ��. �Ƹ���Ʈ�� ��ź�� ���� �漺�� ǥ�÷� ���̾�.", NPCType::NPC_Entrance);
	TextSetting("������, ����. �� Ȯ���� ��ź���� �漺�ϴ� ����̱�. ��ô ������ ���°�? �׷� �ʿ��� �� ���� ���� �ڰ����� �ٰ�. �̰͸� ������ �ձ� ������ �� �� �����ž�. �����ϰ� �����϶��.", NPCType::NPC_Entrance);

	// Castle
	TextSetting("���ɽ����� ������ ���� �պ��� ������ �ϳ� ���´�.", NPCType::NPC_Castle);
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

	// ���� ������ �ѱ��
	if (true == GameEngineInput::GetInst()->IsDown("SpaceBar"))
	{
		if (NPCType_ == NPCType::NPC_Castle)
		{
			NPC_->IsQuestEnd_ = true;			// Ŭ�� �� ����Ʈ �ٷ� End
			// Cactus����Ʈ Clear
		}
   		if (true == Font_->IsTypingEnd_)
		{
			switch (NPCType_)
			{
			case NPCType::NPC_Cactus:
			{
				NPC_->IsQuestOngoing_ = true;

				if (5 == DialogCount_)
				{
					NPC_->IsQuestClear_ = true;
				}
			}
			break;
			case NPCType::NPC_Entrance:
			{
				if (1 == DialogCount_)
				{
					NPC_->IsQuestOngoing_ = true;
				}
				else if (1 == DialogCount_)
				{
					NPC_->IsQuestClear_ = true;
				}
			}
			break;
			default:
				break;
			}

			Font_->IsTypingEnd_ = false;
			ChangeToNextDialog();
		}
		else
		{
			Font_->ResetTimer();
		}

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
			switch (NPCType_)
			{
			case NPCType::NPC_Cactus:
			{
				NPC_->IsQuestOngoing_ = true;
			}
				break;
			case NPCType::NPC_Entrance:
			{
				NPC_->IsQuestClear_ = true;
				NPC_->IsQuestEnd_ = true;
			}
				break;
			default:
				break;
			}

			if (true == Font_->IsTypingEnd_)
			{
				Font_->IsTypingEnd_ = false;
			}
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
	case NPCType::NPC_Cactus:
	{
		UINPCRenderer_->SetTexture("NPC1.png");
		NPCNameFont_->SetText(" ������ ����");
		Font_->SetText(AriantDialogList_[DialogCount_]);
		ButtonOn();
	}
		break;
	case NPCType::NPC_Entrance:
	{
		UINPCRenderer_->SetTexture("NPC2.png");
		NPCNameFont_->SetText("      Ƽ��");
		Font_->SetText(EntranceDialogList_[DialogCount_]);
	}
		break;
	case NPCType::NPC_Castle:
	{
		UINPCRenderer_->SetTexture("NPC3.png");
		NPCNameFont_->SetText("�պ��� �����");
		Font_->SetText(CastleDialogList_[DialogCount_]);
	}
		break;
	}

	UINPCRenderer_->ScaleToTexture();

}


// �ؽ�Ʈ�� ���� �� NPCŸ�Կ� �´� ���Ϳ� �־��ִ� �Լ�
void QuestUI::TextSetting(const std::string& _Text, NPCType _NPCType)
{
	std::string Text = _Text;

	//if (NpcTexts.end() == NpcTexts.find(_NPCType))
	//{
	//	NpcTexts.insert(std::make_pair(_NPCType, std::vector<std::string>()));
	//}

	switch (_NPCType)
	{
	case NPCType::NPC_Cactus:
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

	switch (NPCType_)
	{
	case NPCType::NPC_Cactus:
	{
		// ����Ʈ �̿Ϸ� �� ���� X
		if (false == NPC_->IsQuestClear_ )
		{
			if (DialogCount_ == 4)
			{
				return;
			}
		}
	
		DialogCount_ += 1;

		if (DialogCount_ == 1)			// 2��
		{
			ButtonOff();
		}
		else if (DialogCount_ == 3)		// 3�忡�� �� �� �� �Ѿ�� �� -> 3���� ���� ���·� Off
		{
			Font_->Off();
			Death();
			return;
		}
		else if (DialogCount_ == 5)
		{
			ResetDialog();
			NPC_->IsQuestEnd_ = true;
			return;
		}

		Font_->SetText(AriantDialogList_[DialogCount_]);
	}
	break;
	case NPCType::NPC_Entrance:
	{
		DialogCount_ += 1;

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

	//for (auto iter = NpcTexts.begin(); iter != NpcTexts.end(); iter++)
	//{
	//	if (NPCType::NPC_Cactus == iter->first)
	//	{
	//		// ����Ʈ �̿Ϸ� �� ���� X
	//		if (false == NPC_->IsQuestClear_)
	//		{
	//			if (DialogCount_ == 4)
	//			{
	//				return;
	//			}
	//		}

	//		DialogCount_ += 1;

	//		if (DialogCount_ == 1)			// 2��
	//		{
	//			ButtonOff();
	//		}
	//		else if (DialogCount_ == 3)		// 3�忡�� �� �� �� �Ѿ�� �� -> 3���� ���� ���·� Off
	//		{
	//			Font_->Off();
	//			Death();
	//			return;
	//		}
	//		else if (DialogCount_ == 5)
	//		{
	//			ResetDialog();
	//			NPC_->IsQuestEnd_ = true;
	//			return;
	//		}
	//	}
	//	else if (NPCType::NPC_Entrance == iter->first)
	//	{
	//		DialogCount_ += 1;

	//		if (DialogCount_ == 1)
	//		{
	//			ButtonOn();
	//		}
	//		else if (DialogCount_ == 2)
	//		{
	//			ButtonOff();
	//		}
	//		else if (DialogCount_ == 3)
	//		{
	//			ResetDialog();
	//			return;
	//		}
	//	}
	//	else if (NPCType::NPC_Castle == iter->first)
	//	{
	//		DialogCount_ += 1;

	//		if (DialogCount_ == 1)
	//		{
	//			ButtonOn();
	//		}
	//		else if (DialogCount_ == 2)
	//		{
	//			ButtonOff();
	//		}
	//		else if (DialogCount_ == 3)
	//		{
	//			ResetDialog();
	//			return;
	//		}
	//	}

	//	Font_->SetText(iter->second[DialogCount_]);
	//}

}

