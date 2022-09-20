#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class Monster;
class DamageNumber : public GameEngineActor
{
public:
	// constrcuter destructer
	DamageNumber();
	~DamageNumber();

	// delete Function
	DamageNumber(const DamageNumber& _Other) = delete;
	DamageNumber(DamageNumber&& _Other) noexcept = delete;
	DamageNumber& operator=(const DamageNumber& _Other) = delete;
	DamageNumber& operator=(DamageNumber&& _Other) noexcept = delete;

public:
	void SetDamage(int _Damage);

	inline void SetMonster(Monster* _Monster)
	{
		Monster_ = _Monster;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void DamageNumberRender();
	void DamageNumberUpdate(GameEngineTextureRenderer* _Renderer);

private:
	Monster* Monster_;

	int Damage_;
	float Time_;
	float4 MoveDir_;
	bool IsDamaged_;

	std::string TextureName_;
	std::vector<GameEngineTextureRenderer*> DamageNumbers_;
};

