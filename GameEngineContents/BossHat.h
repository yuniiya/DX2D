#pragma once
#include "GlobalActor.h"

class GameEngineTextureRenderer;
class BossHat : public GlobalActor
{
public:
	// constrcuter destructer
	BossHat();
	~BossHat();

	// delete Function
	BossHat(const BossHat& _Other) = delete;
	BossHat(BossHat&& _Other) noexcept = delete;
	BossHat& operator=(const BossHat& _Other) = delete;
	BossHat& operator=(BossHat&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineTextureRenderer* HitRenderer_;

	GameEngineCollision* Collision_;

};

