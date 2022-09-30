#pragma once
#include "NPC.h"

// Ό³Έν :
class Shop;
class NPC_Shop : public NPC
{
public:
	// constrcuter destructer
	NPC_Shop();
	~NPC_Shop();

	// delete Function
	NPC_Shop(const NPC_Shop& _Other) = delete;
	NPC_Shop(NPC_Shop&& _Other) noexcept = delete;
	NPC_Shop& operator=(const NPC_Shop& _Other) = delete;
	NPC_Shop& operator=(NPC_Shop&& _Other) noexcept = delete;

public:


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void ShopOnOff();

private:
	Shop* ShopUI_;


};

