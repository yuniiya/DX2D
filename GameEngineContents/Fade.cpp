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
	// 레벨 체인지 
	if (true == FadeEnd_)	// 밝아진다
	{
		Renderer_->GetColorData().MulColor.a -= GameEngineTime::GetDeltaTime() *0.9f;
	}

	if (false == FadeEnd_)
	{
		Renderer_->GetColorData().MulColor.a += GameEngineTime::GetDeltaTime() * 0.9f;	// 어두워진다

		if (Renderer_->GetColorData().MulColor.a >= 1)
		{
			FadeEnd_ = true;
		}
	}

}

void Fade::Start()
{
	float4 CampPos = GetLevel()->GetMainCameraActor()->GetTransform().GetLocalPosition();

	Renderer_ = CreateComponent<GameEngineTextureRenderer>();
	Renderer_->SetTexture("FadeOut.png");
	Renderer_->ScaleToTexture();
	Renderer_->GetTransform().SetLocalPosition(CampPos);

	Renderer_->GetColorData().MulColor.a = 0;
}

void Fade::Update(float _DeltaTime)
{
	float4 CamPos = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	Renderer_->GetTransform().SetLocalPosition(float4{ CamPos.x, CamPos.y});

	if (true == FadeOut_)
	{
		Renderer_->GetColorData().MulColor.a += _DeltaTime * 0.7f;
	}

	if (true == FadeIn_)
	{
		Renderer_->GetColorData().MulColor.a -= _DeltaTime * 0.7f;
	}

	SetLevelChangeFade();
}

