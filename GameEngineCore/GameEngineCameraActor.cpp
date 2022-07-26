#include "PreCompile.h"
#include "GameEngineCameraActor.h"
#include <GameEngineBase/GameEngineInput.h>

GameEngineCameraActor::GameEngineCameraActor()
	: CameraComponent(nullptr)
	, RotSpeed(180.0f)
	, Speed(1000.0f)
	, FreeCameraMode(false)
{
}

GameEngineCameraActor::~GameEngineCameraActor() 
{
}

void GameEngineCameraActor::Start() 
{
	CameraComponent = CreateComponent<GameEngineCamera>();

	if (false == GameEngineInput::GetInst()->IsKey("CamMoveForward"))
	{
		GameEngineInput::GetInst()->CreateKey("CamMoveForward", VK_NUMPAD9);	// ������ ���� �е�
		GameEngineInput::GetInst()->CreateKey("CamMoveBack", VK_NUMPAD7);
		GameEngineInput::GetInst()->CreateKey("CamMoveUp", VK_NUMPAD8);
		GameEngineInput::GetInst()->CreateKey("CamMoveDown", VK_NUMPAD5);
		GameEngineInput::GetInst()->CreateKey("CamMoveLeft", VK_NUMPAD4);
		GameEngineInput::GetInst()->CreateKey("CamMoveRight", VK_NUMPAD6);

		GameEngineInput::GetInst()->CreateKey("CamMoveBoost", VK_NUMPAD1);
		GameEngineInput::GetInst()->CreateKey("CamRot", VK_NUMPAD3);
	}

}

void GameEngineCameraActor::Update(float _DeltaTime)
{
	if (false == FreeCameraMode)
	{
		return;
	}

	float MoveSpeed = Speed;

	if (GameEngineInput::GetInst()->IsPress("CamMoveBoost"))
	{
		MoveSpeed *= 3.0f;
	}

	if (GameEngineInput::GetInst()->IsPress("CamMoveForward"))
	{
		GetTransform().SetWorldForwardMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPress("CamMoveBack"))
	{
		GetTransform().SetWorldBackMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPress("CamMoveUp"))
	{
		GetTransform().SetWorldUpMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPress("CamMoveDown"))
	{
		GetTransform().SetWorldDownMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPress("CamMoveLeft"))
	{
		GetTransform().SetWorldLeftMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPress("CamMoveRight"))
	{
		GetTransform().SetWorldRightMove(MoveSpeed, _DeltaTime);
	}

	if (GameEngineInput::GetInst()->IsPress("CamRot"))
	{
		float4 MouseDir = CameraComponent->GetMouseWorldDir();
		float4 RotMouseDir;
		RotMouseDir.x = -MouseDir.y;
		RotMouseDir.y = MouseDir.x;

		GetTransform().SetAddWorldRotation(RotMouseDir * RotSpeed);
	}
}

void GameEngineCameraActor::End() 
{

}


void GameEngineCameraActor::FreeCameraModeOnOff()
{
	FreeCameraMode = !FreeCameraMode;

	if (true == FreeCameraMode)
	{
		PrevMode = CameraComponent->GetProjectionMode();
		CameraComponent->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);
		OriginTrans.Copy(GetTransform());
	}
	else 
	{
		CameraComponent->SetProjectionMode(PrevMode);
		GetTransform().Copy(OriginTrans);
	}
}