#pragma once
#include "Monster.h"

// Ό³Έν :
class BabyCactus : public Monster
{
public:
	// constrcuter destructer
	BabyCactus();
	~BabyCactus();

	// delete Function
	BabyCactus(const BabyCactus& _Other) = delete;
	BabyCactus(BabyCactus&& _Other) noexcept = delete;
	BabyCactus& operator=(const BabyCactus& _Other) = delete;
	BabyCactus& operator=(BabyCactus&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:

};

