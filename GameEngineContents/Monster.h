#pragma once
#include "GlobalActor.h"

enum class MONSTERSTATE
{
	IDLE,
	MOVE,
	ATTACK,
	DAMAGED,
	DIE,

	MAX,
};

enum class MONSTERNAME
{
	Rabbit,
	BabyCactus,
	Sand,
	Freezer,
	Sparker,
	Boss,

	MAX,
};

enum class MONSTERTYPE
{
	DEFAULT,
	ATTACK,

	MAX,
};

class Player;
class Monster : public GlobalActor
{
public:
	// constrcuter destructer
	Monster();
	~Monster();

	// delete Function
	Monster(const Monster& _Other) = delete;
	Monster(Monster&& _Other) noexcept = delete;
	Monster& operator=(const Monster& _Other) = delete;
	Monster& operator=(Monster&& _Other) noexcept = delete;

public:
	inline int GetHP()
	{
		return HP_;
	}

	inline float GetAtk()
	{
		return Atk_;
	}

	inline MONSTERSTATE GetCurState()
	{
		return CurState_;
	}

	inline void SetHP(int _HP)
	{
		HP_ = _HP;
	}

	inline void SetSpeed(float _Speed)
	{
		Speed_ = _Speed;
	}

	inline void SetAtk(float _Atk)
	{
		Atk_ = _Atk;
	}

	inline void SetPixelCheckPos(float _LeftRightPos, float _BottomPos)
	{
		LeftRightPos_ = _LeftRightPos;
		BottomPos_ = _BottomPos;
	}

	inline void SetMonsterName(MONSTERNAME _MonsterName)
	{
		MonsterName_ = _MonsterName;
	}

	inline void SetMonsterType(MONSTERTYPE _MonsterType)
	{
		MonsterType_ = _MonsterType;
	}

	inline void SetMonsterDir(ACTORDIR _Dir)
	{
		SetDir(_Dir);
	}

	inline void SetChangeTime(int _IdleTime, int _MoveTime)
	{
		IdleTime_ = _IdleTime;
		MoveTime_ = _MoveTime;
	}

	void TakeDamage(int _Damage);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	virtual void ChangeState(MONSTERSTATE _State);
	virtual void MonsterStateUpdate();

	virtual void Hit();
	virtual void DirChange();

	bool MonsterCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	virtual void CollisonCheck();

private:
	int HP_;
	float Atk_;
	float Speed_;
	float Time_; 

	int IdleTime_;
	int MoveTime_;

	float BottomPos_;
	float LeftRightPos_;
	float4 DownPower_;

	MONSTERSTATE CurState_;
	MONSTERNAME MonsterName_;
	MONSTERTYPE MonsterType_;
	ACTORDIR MonsterDir_;

protected:
	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;

	virtual void IdleStart();
	virtual void MoveStart();
	virtual void DamagedStart();
	virtual void AttackStart();
	virtual void DieStart();

	virtual void IdleUpdate();
	virtual void MoveUpdate();
	virtual void DamagedUpdate();
	virtual void AttackUpdate();
	virtual void DieUpdate();
};

