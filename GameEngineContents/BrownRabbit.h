#include "Monster.h"

// Ό³Έν :
class BrownRabbit : public Monster
{
public:
	// constrcuter destructer
	BrownRabbit();
	~BrownRabbit();

	// delete Function
	BrownRabbit(const BrownRabbit& _Other) = delete;
	BrownRabbit(BrownRabbit&& _Other) noexcept = delete;
	BrownRabbit& operator=(const BrownRabbit& _Other) = delete;
	BrownRabbit& operator=(BrownRabbit&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:

};

