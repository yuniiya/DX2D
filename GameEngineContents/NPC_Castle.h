#pragma once
#include "NPC.h"

// Ό³Έν :
class NPC_Castle : public NPC
{
public:
	// constrcuter destructer
	NPC_Castle();
	~NPC_Castle();

	// delete Function
	NPC_Castle(const NPC_Castle& _Other) = delete;
	NPC_Castle(NPC_Castle&& _Other) noexcept = delete;
	NPC_Castle& operator=(const NPC_Castle& _Other) = delete;
	NPC_Castle& operator=(NPC_Castle&& _Other) noexcept = delete;

public:
	inline GameEngineCollision* GetCastleCollision()
	{
		return CastleCollision_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineCollision* CastleCollision_;

};

