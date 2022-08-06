#include "Monster.h"

// Ό³Έν :
class WhiteRabbit : public Monster
{
public:
	// constrcuter destructer
	WhiteRabbit();
	~WhiteRabbit();

	// delete Function
	WhiteRabbit(const WhiteRabbit& _Other) = delete;
	WhiteRabbit(WhiteRabbit&& _Other) noexcept = delete;
	WhiteRabbit& operator=(const WhiteRabbit& _Other) = delete;
	WhiteRabbit& operator=(WhiteRabbit&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:

};

