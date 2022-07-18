#include "PreCompile.h"
#include "GameEngineCameraActor.h"

GameEngineCameraActor::GameEngineCameraActor() 
	: CameraComponent(nullptr)
{
}

GameEngineCameraActor::~GameEngineCameraActor() 
{
}

void GameEngineCameraActor::Start() 
{
	CameraComponent = CreateComponent<GameEngineCamera>();
}

void GameEngineCameraActor::Update(float _DeltaTime)
{

}

void GameEngineCameraActor::End() 
{

}
