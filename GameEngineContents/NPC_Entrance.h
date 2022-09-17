#pragma once
#include "NPC.h"

// Ό³Έν :
class NPC_Entrance : public NPC
{
public:
	// constrcuter destructer
	NPC_Entrance();
	~NPC_Entrance();

	// delete Function
	NPC_Entrance(const NPC_Entrance& _Other) = delete;
	NPC_Entrance(NPC_Entrance&& _Other) noexcept = delete;
	NPC_Entrance& operator=(const NPC_Entrance& _Other) = delete;
	NPC_Entrance& operator=(NPC_Entrance&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:

};

