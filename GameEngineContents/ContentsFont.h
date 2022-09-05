#pragma once
#include <GameEngineCore/GameEngineFontRenderer.h>

// Ό³Έν :
class ContentsFont : public GameEngineFontRenderer
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

protected:
	void Start() override;
	void Render(float _DeltaTime) override;

private:
};

