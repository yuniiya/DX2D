#pragma once
#include "Monster.h"

// Ό³Έν :
class Boss : public Monster
{
public:
	// constrcuter destructer
	Boss();
	~Boss();

	// delete Function
	Boss(const Boss& _Other) = delete;
	Boss(Boss&& _Other) noexcept = delete;
	Boss& operator=(const Boss& _Other) = delete;
	Boss& operator=(Boss&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:

};

