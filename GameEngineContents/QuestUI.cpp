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
		Font_->Off();
		Death();
	}
}

void QuestUI::CollisionCheck()
{
	if (nullptr == this)
	{
		return;
	}

	//if (true == ButtonYesCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	//{
	//	ButtonYes_->SetTexture("BtOK.mouseOver.0.png");
	//	ButtonNo_->SetTexture("BtNo.normal.0.png");
	//}
	//else if(true == ButtonNoCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	//{
	//	ButtonNo_->SetTexture("BtNo.mouseOver.0.png");
	//	ButtonYes_->SetTexture("BtOK.normal.png");
	//}
	//else
	//{
	//	ButtonYes_->SetTexture("BtOK.normal.png");
	//	ButtonNo_->SetTexture("BtNo.normal.0.png");
	//}

	if (true == ButtonYesCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	{
		ButtonYes_->SetTexture("BtOK.mouseOver.0.png");
	}
	else
	{
		ButtonYes_->SetTexture("BtOK.normal.png");
	}

	if (true == ButtonNoCol_->IsCollision(CollisionType::CT_OBB2D, GAMEOBJGROUP::MOUSE, CollisionType::CT_OBB2D))
	{
		ButtonNo_->SetTexture("BtNo.mouseOver.0.png");
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
	Font_->SetNPCDialog(_NPCType);
	Font_->On();

	switch (NPCType_)
	{
	case NPCType::NPC_Ariant:
	{
		UINPCRenderer_->SetTexture("NPC1.png");
		NPCNameFont_->SetText(" 수상한 남자");
	}
		break;
	case NPCType::NPC_Entrance:
	{
		UINPCRenderer_->SetTexture("NPC2.png");
		NPCNameFont_->SetText("      티건");
	}
		break;
	case NPCType::NPC_Castle:
	{
		UINPCRenderer_->SetTexture("NPC3.png");
		NPCNameFont_->SetText("왕비의 장식장");
	}
		break;
	}

	UINPCRenderer_->ScaleToTexture();
}
