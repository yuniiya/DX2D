#include "PreCompile.h"
#include "FadeIn.h"

FadeIn::FadeIn() 
{
}

FadeIn::~FadeIn() 
{
}

void FadeIn::Start()
{
	float4 CampPos = GetLevel()->GetMainCameraActor()->GetTransform().GetLocalPosition();

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture("FadeOut.png");
	Renderer_->ScaleToTexture();
	Renderer_->GetTransform().SetLocalPosition(CampPos);

	Renderer_->GetPixelData().MulColor.a = 1;
}

void FadeIn::Update(float _DeltaTime)
{
	float4 CamPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	Renderer_->GetTransform().SetLocalPosition(float4{ CamPos.x, CamPos.y });

	Renderer_->GetPixelData().MulColor.a -= _DeltaTime;

	//if (0 >= Renderer_->GetColorData().MulColor.a)
	//{
	//	Renderer_->GetColorData().MulColor.a = 0;
	//}

}

