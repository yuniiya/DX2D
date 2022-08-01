#include "PreCompile.h"
#include "ContentsUI.h"

ContentsUI::ContentsUI() 
	: UIRenderer_(nullptr)
	, MainBarRenderer_(nullptr)
{
}

ContentsUI::~ContentsUI() 
{
}

void ContentsUI::Start()
{
	//UIRenderer_ = CreateComponent<GameEngineUIRenderer>();
	//UIRenderer_->GetTransform().SetLocalPosition({ 100.f, 100.f, 0.f });
	//UIRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	//UIRenderer_->GetTransform().SetLocalScale({500.f, 300.f});

	//{
	//	GameEngineUIRenderer* UIRenderer_ = CreateComponent<GameEngineUIRenderer>();
	//	UIRenderer_->GetTransform().SetLocalPosition(float4{ 200.f, -500.f, 1.f });
	//	UIRenderer_->SetPivot(PIVOTMODE::LEFTTOP);
	//	UIRenderer_->GetTransform().SetLocalScale(float4{ 204.f, 70.f, 1.f });
	//}


	MainBarRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MainBarRenderer_->SetTexture("mainBar.png");
	MainBarRenderer_->ScaleToTexture();
}

void ContentsUI::Update(float _DeltaTime)
{
	//UIRenderer_->GetTransform().SetLocalPosition({ 300.f, -100.f, 1.f });


	float4 CamPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();
	MainBarRenderer_->GetTransform().SetLocalPosition(float4{ CamPos.x, CamPos.y - 315.f});
}

void ContentsUI::SetMainUI()
{
	//UIRenderer_->SetTexture("mainBar.png");
	//UIRenderer_->ScaleToTexture();

}
