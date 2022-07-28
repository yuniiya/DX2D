#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ContentsUI : public GameEngineActor
{
public:
	// constrcuter destructer
	ContentsUI();
	~ContentsUI();

	// delete Function
	ContentsUI(const ContentsUI& _Other) = delete;
	ContentsUI(ContentsUI&& _Other) noexcept = delete;
	ContentsUI& operator=(const ContentsUI& _Other) = delete;
	ContentsUI& operator=(ContentsUI&& _Other) noexcept = delete;

public:
	GameEngineUIRenderer* GetUIRenderer()
	{
		return UIRenderer_;
	}

	void SetMainUI();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineUIRenderer* UIRenderer_;
	GameEngineTextureRenderer* MainBarRenderer_;

};

