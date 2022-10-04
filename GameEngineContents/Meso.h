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

public:
	inline int GetMesoAmount()
	{
		return MesoAmount_;
	}

	inline void SetMesoAmount(int _MesoAmount)
	{
		MesoAmount_ = _MesoAmount;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void PickUpItemCheck(GameEngineTextureRenderer* _Renderer, float _DeltaTime) override;
	void TimeAttackUpdate(GameEngineTextureRenderer* _Renderer, float _DeltaTime) override;

	virtual void DropStart() override;
	virtual void FloatStart() override;
	virtual void DropUpdate(float _DeltaTime) override;
	virtual void FloatUpdate(float _DeltaTime) override;

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;

	int Random_;
	int MesoAmount_;

	int PlayerMeso_;
};

