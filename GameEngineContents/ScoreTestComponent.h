#pragma once
#include <GameEngineCore/GameEngineComponent.h>

// Ό³Έν :
class ScoreTestComponent : public GameEngineComponent
{
public:
	// constrcuter destructer
	ScoreTestComponent();
	~ScoreTestComponent();

	// delete Function
	ScoreTestComponent(const ScoreTestComponent& _Other) = delete;
	ScoreTestComponent(ScoreTestComponent&& _Other) noexcept = delete;
	ScoreTestComponent& operator=(const ScoreTestComponent& _Other) = delete;
	ScoreTestComponent& operator=(ScoreTestComponent&& _Other) noexcept = delete;

protected:

private:

};

