#pragma once
#include "GlobalLevel.h"

class CastleLevel : public GlobalLevel
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

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	Player* Player_;
};

