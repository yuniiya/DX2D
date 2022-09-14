#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineFontRenderer;
class ContentsFont : public GameEngineActor
{
public:
	// constrcuter destructer
	ContentsFont();
	~ContentsFont();

	// delete Function
	ContentsFont(const ContentsFont& _Other) = delete;
	ContentsFont(ContentsFont&& _Other) noexcept = delete;
	ContentsFont& operator=(const ContentsFont& _Other) = delete;
	ContentsFont& operator=(ContentsFont&& _Other) noexcept = delete;

public:
	inline GameEngineFontRenderer* GetFontRenderer()
	{
		return FontRenderer_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineFontRenderer* FontRenderer_;

	int Count_;
	float TypingTimer_;
};

