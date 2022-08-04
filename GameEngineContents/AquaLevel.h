#pragma once
#include "GlobalLevel.h"

class AquaLevel : public GlobalLevel
{
public:
	// constrcuter destructer
	AquaLevel();
	~AquaLevel();

	// delete Function
	AquaLevel(const AquaLevel& _Other) = delete;
	AquaLevel(AquaLevel&& _Other) noexcept = delete;
	AquaLevel& operator=(const AquaLevel& _Other) = delete;
	AquaLevel& operator=(AquaLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void OnEvent() override;

private:
	Player* Player_;

};

