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
	Renderer_->GetColorData().MulColor.a = 0;	// ��ο�����

	FadeOut_ = true;
}

void Fade::SetFadeIn()
{
	Renderer_->GetColorData().MulColor.a = 1;	// �������

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
	Renderer_->ScaleToTexture();
	Renderer_->GetTransform().SetLocalPosition(CampPos);

	Renderer_->GetColorData().MulColor.a = 0;

	FadeEnd_ = false;
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

	if (false == FadeEnd_)
	{
		Renderer_->GetColorData().MulColor.a += _DeltaTime * 1.f;	// ��ο�����

		if (1 <= Renderer_->GetColorData().MulColor.a)
		{
			FadeEnd_ = true;
		}
	}

	// ���� ü���� 
	if (true == FadeEnd_)	// �������
	{
		Renderer_->GetColorData().MulColor.a -= _DeltaTime * 1.f;

		if (0 >= Renderer_->GetColorData().MulColor.a)
		{
			Renderer_->GetColorData().MulColor.a = 0;
			FadeEnd_ = true;
		}
	}
}

