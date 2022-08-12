#pragma once
#include "GlobalLevel.h"

class CactusLevel : public GlobalLevel
{
public:
	// constrcuter destructer
	CactusLevel();
	~CactusLevel();

	// delete Function
	CactusLevel(const CactusLevel& _Other) = delete;
	CactusLevel(CactusLevel&& _Other) noexcept = delete;
	CactusLevel& operator=(const CactusLevel& _Other) = delete;
	CactusLevel& operator=(CactusLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

	void OnEvent() override;
	void OffEvent() override;

protected:
	float4 CameraPos_;
	float4 PlayerPos_;

private:
	Player* Player_;

public:
};
