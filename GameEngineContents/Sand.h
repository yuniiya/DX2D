#include "Monster.h"

// Ό³Έν :
class Sand : public Monster
{
public:
	// constrcuter destructer
	Sand();
	~Sand();

	// delete Function
	Sand(const Sand& _Other) = delete;
	Sand(Sand&& _Other) noexcept = delete;
	Sand& operator=(const Sand& _Other) = delete;
	Sand& operator=(Sand&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:

};

