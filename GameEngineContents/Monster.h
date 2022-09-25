#pragma once
#include "GlobalActor.h"

enum class MONSTERSTATE
{
	IDLE,
	MOVE,
	CHASE,
	ATTACK,
	DAMAGED,
	DIE,

	MAX,
};

enum class MONSTERNAME
{
	WhiteRabbit,
	BrownRabbit,
	BabyCactus,
	Sand,
	Scorpion,
	Freezer,
	Sparker,
	Boss,
	None,

	MAX,
};

enum class MONSTERTYPE
{
	DEFAULT,
	ATTACK,

	MAX,
};

class Player;
class Item;
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
	inline float4 GetPosition()
	{
		return GetTransform().GetLocalPosition();
	}

	inline float GetHP()
	{
		return HP_;
	}

	inline float GetMaxHP()
	{
		return MaxHP_;
	}

	inline float GetAtk()
	{
		return Atk_;
	}

	inline int GetDamage()
	{
		return Damage_;
	}

	inline MONSTERNAME GetMonsterName()
	{
		return MonsterName_;
	}

	inline MONSTERSTATE GetCurState()
	{
		return CurState_;
	}

	void SetHP(float _HP)
	{
		HP_ = _HP;
	}

	void SetMaxHP(float _MaxHP)
	{
		MaxHP_ = _MaxHP;
	}

	inline void SetSpeed(float _Speed)
	{
		Speed_ = _Speed;
	}

	inline void SetAtk(float _Atk)
	{
		Atk_ = _Atk;
	}

	inline void SetPixelCheckPos(int _LeftRightPos, int _BottomPos)
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

	inline void SetChangeTime(float _IdleTime, float _MoveTime)
	{
		IdleTime_ = _IdleTime;
		MoveTime_ = _MoveTime;
	}

	void TakeDamage(int _Damage);
	void CollisionPositionUpdate();
	void EffectPositionUpdate();


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	virtual void ChangeState(MONSTERSTATE _State);
	virtual void MonsterStateUpdate();

	virtual void Hit();
	virtual void DirChange();
	virtual void Attack();
	virtual void CurDirCheck(float4 _PlayerPos, float4 _MonsterPos, float _MinPos);

	virtual bool MonsterCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	virtual void CollisonCheck();

	void BindMonsterDeathCheck(const FrameAnimation_DESC& _Info);
	void BindAttackStartCheck(const FrameAnimation_DESC& _Info);
	void BindAttackEndCheck(const FrameAnimation_DESC& _Info);
	virtual void BindAttackEffectEndCheck(const FrameAnimation_DESC& _Info) {};



protected:
	float HP_;
	float MaxHP_;
	int Damage_;
	float Atk_;
	float Speed_;
	float Time_;

	float IdleTime_;
	float MoveTime_;
	float DamageTime_;
	float DirChangeTime_;
	float ChaseTime_;
	float CanAttTime_;
	float AttEndTime_;

	int BottomPos_;
	int LeftRightPos_;
	float4 DownPower_;

	float4 MoveDir_;
	float4 PlayerPos_;
	float4 MonsterPos_;
	float4 PrevPos_;

	MONSTERSTATE CurState_;
	MONSTERSTATE PrevState_;
	MONSTERNAME MonsterName_;
	MONSTERTYPE MonsterType_;
	ACTORDIR MonsterDir_;

	bool SoundPlay_;
	bool IsDie();
	bool IsHit;
	bool IsAttack;
	bool IsAttackEnd;
	bool IsRight;

protected:
	GameEngineTextureRenderer* Renderer_;
	GameEngineCollision* Collision_;

	GameEngineCollision* SparkerAttCol_;
	GameEngineCollision* FreezerAttCol_;

	GameEngineTextureRenderer* SparkerAttEffect_;
	GameEngineTextureRenderer* FreezerAttEffect_;

	virtual void IdleStart();
	virtual void MoveStart();
	virtual void ChaseStart();
	virtual void DamagedStart();
	virtual void AttackStart();
	virtual void DieStart();

	virtual void IdleUpdate();
	virtual void MoveUpdate();
	virtual void ChaseUpdate();
	virtual void DamagedUpdate();
	virtual void AttackUpdate();
	virtual void DieUpdate();
};

