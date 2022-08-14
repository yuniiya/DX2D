#include "Monster.h"

// Ό³Έν :
class Freezer : public Monster
{
public:
	// constrcuter destructer
	Freezer();
	~Freezer();

	// delete Function
	Freezer(const Freezer& _Other) = delete;
	Freezer(Freezer&& _Other) noexcept = delete;
	Freezer& operator=(const Freezer& _Other) = delete;
	Freezer& operator=(Freezer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void BindAttackEffectEndCheck(const FrameAnimation_DESC& _Info) override;

private:

};

