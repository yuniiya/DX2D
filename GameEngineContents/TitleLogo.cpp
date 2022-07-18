#include "PreCompile.h"
#include "TitleLogo.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>

TitleLogo::TitleLogo() 
	: TimeAngle(0.0f)
{
}

TitleLogo::~TitleLogo() 
{
}

GameEngineRenderer* RendererTest = nullptr;

void TitleLogo::Start() 
{
	// 1280 720
	GetTransform().SetLocalPosition({ 0, 200, 0 });

	{
		GameEngineRenderer* RendererTest = CreateComponent<GameEngineDefaultRenderer>();
		RendererTest->GetTransform().SetLocalScale({ 800, 400, 0 });
	}

	TimeAngle = 0.0f;
}

void TitleLogo::Update(float _DeltaTime) 
{
	//TimeAngle += _DeltaTime * 20.0f;

	//GetTransform().SetLocalRotation({ 0.0f , 0.0f, TimeAngle });
	//RendererTest->GetTransform().SetLocalRotation({ TimeAngle , TimeAngle, TimeAngle });
}

void TitleLogo::End() 
{
	int a = 0;
}