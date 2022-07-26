#pragma once
#include "GameEngineCore/GameEngineActor.h"
#include "Enums.h"

class GameEngineCollision;
class GlobalActor : public GameEngineActor
{
public:
	// constrcuter destructer
	GlobalActor();
	~GlobalActor();

	// delete Function
	GlobalActor(const GlobalActor& _Other) = delete;
	GlobalActor(GlobalActor&& _Other) noexcept = delete;
	GlobalActor& operator=(const GlobalActor& _Other) = delete;
	GlobalActor& operator=(GlobalActor&& _Other) noexcept = delete;

protected:
	void Start() override {};
	void Update(float _DeltaTime) override;
	void End() override {};

protected:
	bool PixelCollisionMapUpdate(GlobalActor* _Actor);

private:
	GameEngineTexture* MapTexture_;
	GlobalActor* Actor_;
};

