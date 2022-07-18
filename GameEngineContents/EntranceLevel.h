#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class EntranceLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	EntranceLevel();
	~EntranceLevel();

	// delete Function
	EntranceLevel(const EntranceLevel& _Other) = delete;
	EntranceLevel(EntranceLevel&& _Other) noexcept = delete;
	EntranceLevel& operator=(const EntranceLevel& _Other) = delete;
	EntranceLevel& operator=(EntranceLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

