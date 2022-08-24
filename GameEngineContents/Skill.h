#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class GameEngineCollision;
class Skill : public GameEngineActor
{
public:
	// constrcuter destructer
	Skill();
	~Skill();

	// delete Function
	Skill(const Skill& _Other) = delete;
	Skill(Skill&& _Other) noexcept = delete;
	Skill& operator=(const Skill& _Other) = delete;
	Skill& operator=(Skill&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineTextureRenderer* Renderer_;

	GameEngineCollision* Collision_;
};

