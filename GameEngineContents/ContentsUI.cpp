#include "PreCompile.h"
#include "ContentsUI.h"

ContentsUI::ContentsUI() 
	: UIRenderer_(nullptr)
{
}

ContentsUI::~ContentsUI() 
{
}

void ContentsUI::Start()
{
	UIRenderer_ = CreateComponent<GameEngineUIRenderer>();
	UIRenderer_->GetTransform().SetLocalPosition(float4{ 200.f, -500.f, 1.f });
	UIRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
//	UIRenderer_->GetTransform().SetLocalScale(float4{204.f, 70.f, 1.f});

	//{
	//	GameEngineUIRenderer* UIRenderer_ = CreateComponent<GameEngineUIRenderer>();
	//	UIRenderer_->GetTransform().SetLocalPosition(float4{ 200.f, -500.f, 1.f });
	//	UIRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	//	UIRenderer_->GetTransform().SetLocalScale(float4{ 204.f, 70.f, 1.f });
	//}

}

void ContentsUI::SetMainUI()
{
	UIRenderer_->SetTexture("mainBar.png");
	UIRenderer_->ScaleToTexture();

}
