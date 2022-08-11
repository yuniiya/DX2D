#include "PreCompile.h"
#include "TitleLevel.h"
#include "Mouse.h"
#include "Fade.h"
#include "TitleLogo.h"
#include "Fade.h"

TitleLevel::TitleLevel() 
	: Time_(0.0f)
	, SoundPlay_(true)
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Start()
{
	TitleLogo* Logo = CreateActor<TitleLogo>(GAMEOBJGROUP::UI);
}

void TitleLevel::Update(float _DeltaTime)
{
	if (true == SoundPlay_)
	{
		Time_ += GameEngineTime::GetDeltaTime();
	}

	if (Time_ >= 5.7f)
	{
		Time_ = 0.0f;
		SoundPlay_ = false;
		GameEngineSound::SoundPlayOneShot("NxLogo.mp3");
	}
}

void TitleLevel::End()
{

}

void TitleLevel::OnEvent()
{
	//Fade* FadeActor = CreateActor<Fade>(GAMEOBJGROUP::FADE);
}
