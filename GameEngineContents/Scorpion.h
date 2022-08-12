#pragma once
#include "Monster.h"

// Ό³Έν :
class Scorpion : public Monster
{
public:
	// constrcuter destructer
	Scorpion();
	~Scorpion();

	// delete Function
	Scorpion(const Scorpion& _Other) = delete;
	Scorpion(Scorpion&& _Other) noexcept = delete;
	Scorpion& operator=(const Scorpion& _Other) = delete;
	Scorpion& operator=(Scorpion&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:

};

