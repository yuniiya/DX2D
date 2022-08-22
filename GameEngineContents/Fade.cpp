#include "PreCompile.h"
#include "Fade.h"

Fade::Fade() 
	: FadeTime_(0.0f)
	, FadeEnd_(false)
	, FadeOut_(false)
	, FadeIn_(false)
{
}

Fade::~Fade() 
{
}

void Fade::SetFadeOut()
{
	Renderer_->GetColorData().MulColor.a = 0;	// 어두워진다

	FadeOut_ = true;
}

void Fade::SetFadeIn()
{
	Renderer_->GetColorData().MulColor.a = 1;	// 밝아진다

	FadeIn_ = true;
}

void Fade::SetLevelChangeFade()
{

}

void Fade::Start()
{
	float4 CampPos = GetLevel()->GetMainCameraActor()->GetTransform().GetLocalPosition();

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture("FadeOut.png");
	Renderer_->GetTransform().SetLocalScale({5000.f, 5000.f});
	Renderer_->GetTransform().SetLocalPosition(CampPos);

	Renderer_->GetColorData().MulColor.a = 1.f;

	FadeEnd_ = false;
}

void Fade::Update(float _DeltaTime)
{
	float4 CamPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	Renderer_->GetTransform().SetLocalPosition(float4{ CamPos.x, CamPos.y});

	//if (true == FadeOut_)
	//{
	//	Renderer_->GetColorData().MulColor.a += _DeltaTime * 0.7f;
	//}

	//if (true == FadeIn_)
	//{
	//	Renderer_->GetColorData().MulColor.a -= _DeltaTime * 0.7f;
	//}

	//Renderer_->GetColorData().MulColor.a -= _DeltaTime;


	if (false == FadeEnd_)
	{
		Renderer_->GetColorData().MulColor.a -= _DeltaTime * 1.8f;	// 어두워진다

		if (0 >= Renderer_->GetColorData().MulColor.a)
		{
			Renderer_->GetColorData().MulColor.a = 0;
			FadeEnd_ = true;
		}
	}

	// 레벨 체인지 
	//if (true == FadeEnd_)	// 밝아진다
	//{
	//	Renderer_->GetColorData().MulColor.a -= _DeltaTime * 1.f;

	//	if (0 >= Renderer_->GetColorData().MulColor.a)
	//	{
	//		Renderer_->GetColorData().MulColor.a = 0;
	//	}
	//}
}

