#include "PreCompile.h"
#include "QuestUI.h"
#include <GameEngineCore/GameEngineFontRenderer.h>
#include "ContentsFont.h"

QuestUI::QuestUI() 
	: Renderer_(nullptr)
	, ExitCol(nullptr)
	, UINPCRenderer_(nullptr)
	, NPCNameFont_(nullptr)
{
}

QuestUI::~QuestUI() 
{
}

void QuestUI::Start()
{
	GetTransform().SetLocalPosition({ 0.f, 0.f, (int)ZOrder::UI });

	Renderer_ = CreateComponent<GameEngineUIRenderer>();
	Renderer_->SetTexture("DialogUI.png");
	Renderer_->GetTransform().SetLocalScale({751.f * 0.8f, 276.f * 0.8f});

	UINPCRenderer_ = CreateComponent<GameEngineUIRenderer>();
	UINPCRenderer_->GetTransform().SetLocalPosition({ Renderer_->GetTransform().GetLocalPosition().x - 210.f
		, Renderer_->GetTransform().GetLocalPosition().y + 30.f});

	NPCNameFont_ = CreateComponent<GameEngineFontRenderer>();
	NPCNameFont_->SetRenderingOrder((int)GAMEOBJGROUP::FONT);
	NPCNameFont_->SetColor({ 1.0f, 1.0f, 1.0f, 1.0 });
	NPCNameFont_->SetSize(13);
	NPCNameFont_->ChangeCamera(CAMERAORDER::UICAMERA);
	NPCNameFont_->SetScreenPostion({ UINPCRenderer_->GetTransform().GetLocalPosition().x + 600.f
		, -UINPCRenderer_->GetTransform().GetLocalPosition().y + 404.f});
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
