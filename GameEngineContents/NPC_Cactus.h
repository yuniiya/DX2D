#pragma once
#include "NPC.h"

// Ό³Έν :
class NPC_Cactus : public NPC
{
public:
	// constrcuter destructer
	NPC_Cactus();
	~NPC_Cactus();

	// delete Function
	NPC_Cactus(const NPC_Cactus& _Other) = delete;
	NPC_Cactus(NPC_Cactus&& _Other) noexcept = delete;
	NPC_Cactus& operator=(const NPC_Cactus& _Other) = delete;
	NPC_Cactus& operator=(NPC_Cactus&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:

};

