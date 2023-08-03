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

	inline void SetDamageType(DamageTextureType _DamageType)
	{
		DamageType_ = _DamageType;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void DamageNumberRender(float4 _Pos, std::vector<GameEngineTextureRenderer*>& _Vector);
private:
	Monster* Monster_;
	DamageTextureType DamageType_;

	int Damage_;
	float Time_;
	float4 MoveDir_;
	bool IsDamaged_;

	std::string TextureName_;
	std::vector<GameEngineTextureRenderer*> MonsterDamageNumbers_;
	std::vector<GameEngineTextureRenderer*> PlayerDamageNumbers_;
};

