#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
class CastleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	CastleLevel();
	~CastleLevel();

	// delete Function
	CastleLevel(const CastleLevel& _Other) = delete;
	CastleLevel(CastleLevel&& _Other) noexcept = delete;
	CastleLevel& operator=(const CastleLevel& _Other) = delete;
	CastleLevel& operator=(CastleLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:

};

