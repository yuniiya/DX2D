#include "PreCompile.h"
#include "LoginUI.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>

LoginUI::LoginUI()
	: TimeAngle(0.0f)
{
}

LoginUI::~LoginUI()
{
}

GameEngineRenderer* RendererTest = nullptr;

void LoginUI::Start()
{
	// 1280 720
	// GetTransform().SetLocalPosition({ 0, 200, 0 });

}

void LoginUI::Update(float _DeltaTime)
{
	//TimeAngle += _DeltaTime * 20.0f;

	//GetTransform().SetLocalRotation({ 0.0f , 0.0f, TimeAngle });
	//RendererTest->GetTransform().SetLocalRotation({ TimeAngle , TimeAngle, TimeAngle });
}

void LoginUI::End()
{
	int a = 0;
}