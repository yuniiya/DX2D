#pragma once
#include <GameEngineCore/GameEngineActor.h>

// ���� :
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
	void Update(float _DeltaTime) {}
	void End() {}

private:
	GameEngineUIRenderer* UIRenderer_;

};

