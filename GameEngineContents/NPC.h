#pragma once
#include "GameEngineCore/GameEngineActor.h"


// Ό³Έν :
class NPC : public GameEngineActor
{
public:
	// constrcuter destructer
	NPC();
	~NPC();

	// delete Function
	NPC(const NPC& _Other) = delete;
	NPC(NPC&& _Other) noexcept = delete;
	NPC& operator=(const NPC& _Other) = delete;
	NPC& operator=(NPC&& _Other) noexcept = delete;

public:
	void SetNPCType(NPCType _NPCType)
	{
		NPCType_ = _NPCType;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;

	NPCType NPCType_;

};

