#pragma once
#include "GameEngineCore/GameEngineLevel.h"

class MapBackGround;
class MapStage;
class GameEngineTextureRenderer;
class GlobalLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	GlobalLevel();
	~GlobalLevel();

	// delete Function
	GlobalLevel(const GlobalLevel& _Other) = delete;
	GlobalLevel(GlobalLevel&& _Other) noexcept = delete;
	GlobalLevel& operator=(const GlobalLevel& _Other) = delete;
	GlobalLevel& operator=(GlobalLevel&& _Other) noexcept = delete;

protected:
	void Start() override {};
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineCameraActor* CameraActor_;

	float4 CameraPos_;
	float CameraPosX_;
	float CameraPosY_;

	float MapSizeX_;
	float MapSizeY_;

public:
	GameEngineCameraActor* GetCameraActor()
	{
		return CameraActor_;
	}

	void MapSizeReturn(float _X, float _Y)
	{
		MapSizeX_ = _X;
		MapSizeY_ = _Y;
	}

	void LimitCamera(float4 _MapSize);

protected:
	void SetCamera();
	void SetBackGround(const std::string& _Name);
	void SetStage(const std::string& _Name);

};

