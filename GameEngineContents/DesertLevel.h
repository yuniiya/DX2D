#pragma once
#include "GlobalLevel.h"

class DesertLevel : public GlobalLevel
{
public:
	// constrcuter destructer
	DesertLevel();
	~DesertLevel();

	// delete Function
	DesertLevel(const DesertLevel& _Other) = delete;
	DesertLevel(DesertLevel&& _Other) noexcept = delete;
	DesertLevel& operator=(const DesertLevel& _Other) = delete;
	DesertLevel& operator=(DesertLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	Player* Player_;
};

