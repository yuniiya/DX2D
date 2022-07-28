#pragma once
#include "GlobalLevel.h"

class EntranceLevel : public GlobalLevel
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
	Player* Player_;

};

