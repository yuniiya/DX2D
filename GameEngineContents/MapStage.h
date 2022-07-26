#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class MapStage : public GameEngineActor
{
public:
	// constrcuter destructer
	MapStage();
	~MapStage();

	// delete Function
	MapStage(const MapStage& _Other) = delete;
	MapStage(MapStage&& _Other) noexcept = delete;
	MapStage& operator=(const MapStage& _Other) = delete;
	MapStage& operator=(MapStage&& _Other) noexcept = delete;

private:
	void Start();
	void Update(float _DeltaTime) override {};
	void End() override {};

	GameEngineTextureRenderer* MapStageRender_;

public:
	GameEngineTextureRenderer* GetRenderer()
	{
		return	MapStageRender_;
	}
};

