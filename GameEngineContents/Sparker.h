#include "Monster.h"

// Ό³Έν :
class Sparker : public Monster
{
public:
	// constrcuter destructer
	Sparker();
	~Sparker();

	// delete Function
	Sparker(const Sparker& _Other) = delete;
	Sparker(Sparker&& _Other) noexcept = delete;
	Sparker& operator=(const Sparker& _Other) = delete;
	Sparker& operator=(Sparker&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:

};

