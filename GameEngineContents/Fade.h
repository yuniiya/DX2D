#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class Fade : public GameEngineActor
{
public:
	// constrcuter destructer
	Fade();
	~Fade();

	// delete Function
	Fade(const Fade& _Other) = delete;
	Fade(Fade&& _Other) noexcept = delete;
	Fade& operator=(const Fade& _Other) = delete;
	Fade& operator=(Fade&& _Other) noexcept = delete;

public:
	void SetFadeOut();
	void SetFadeIn();
	void SetLevelChangeFade();

protected:
	float FadeTime_;
	bool FadeEnd_;

	bool FadeOut_;
	bool FadeIn_;

	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineTextureRenderer* Renderer_;

};

