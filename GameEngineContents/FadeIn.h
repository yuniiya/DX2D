#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class FadeIn : public GameEngineActor
{
public:
	// constrcuter destructer
	FadeIn();
	~FadeIn();

	// delete Function
	FadeIn(const FadeIn& _Other) = delete;
	FadeIn(FadeIn&& _Other) noexcept = delete;
	FadeIn& operator=(const FadeIn& _Other) = delete;
	FadeIn& operator=(FadeIn&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineTextureRenderer* Renderer_;

};

