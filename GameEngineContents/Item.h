#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class Item : public GameEngineActor
{
public:
	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

public:
	virtual void TimeAttackStart();
	virtual void TimeAttackUpdate(GameEngineTextureRenderer* _Renderer);
	virtual void UpDownMove();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	bool IsCreate;

	float Time_;
	float MoveTime_;
	float4 MoveDir_;

public:
	MONSTERNAME MonsterName_;

private:
	GameEngineTextureRenderer* Renderer_;


};

