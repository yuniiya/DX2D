#pragma once
//#include <GameEngineCore/GameEngineActor.h>
#include "Item.h"

class GameEngineTextureRenderer;
class Meso : public Item
{
public:
	// constrcuter destructer
	Meso();
	~Meso();

	// delete Function
	Meso(const Meso& _Other) = delete;
	Meso(Meso&& _Other) noexcept = delete;
	Meso& operator=(const Meso& _Other) = delete;
	Meso& operator=(Meso&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;

	int Random_;
	float MesoAmount_;

};

