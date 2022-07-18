#include "PreCompile.h"
#include "LoginLevel.h"
#include "LoginUI.h"
#include "Enums.h"
#include <GameEngineCore/GEngine.h>
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>

LoginLevel::LoginLevel()
{
}

LoginLevel::~LoginLevel()
{
}


void LoginLevel::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", 'P');
	}

	// 카메라를 먼저 만들어서 세계를 볼 준비를 하고
	GameEngineCameraActor* CameraActor = CreateActor<GameEngineCameraActor>();
	CameraActor->GetTransform().SetLocalPosition({0.0f, 0.0f, -100.0f});
	CameraActor->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::Orthographic);
	// [1][0][0][0]
	// [0][1][0][0]
	// [0][0][1][0] 앞을 보고 있다.
	// [0][0][-100][0] 뒤로 물러나서

	// 세상에 보일 오브젝트들을 만들어서
	CreateActor<LoginUI>(GameObjectGroup::UI);
	// [800][0][0][0]
	// [0][400][0][0]
	// [0][0][1][0] 앞을 보고 있다.
	// [0][200][0][0] 뒤로 물러나서

}

void LoginLevel::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GEngine::ChangeLevel("Play");
	}
}

void LoginLevel::End()
{
}