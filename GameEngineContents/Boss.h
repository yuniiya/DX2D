#pragma once
#include "Monster.h"

enum class BossType
{
	NORMAL,
	BLUE,
	RED,

	MAX,
};

enum class BossState
{
	Idle,
	Move,
	Damaged,
	Die,
	Transform,
	Regen,
	
	// Normal
	Attack_A,
	Attack_B,
	Attack_C,

	// Blue
	BLUE_Attack,

	// Red
	RED_AttackA,
	RED_AttackB,
	RED_Tel,
	RED_TelRegen,

	MAX,
};

class Boss : public Monster
{
public:
	// constrcuter destructer
	Boss();
	~Boss();

	// delete Function
	Boss(const Boss& _Other) = delete;
	Boss(Boss&& _Other) noexcept = delete;
	Boss& operator=(const Boss& _Other) = delete;
	Boss& operator=(Boss&& _Other) noexcept = delete;

public:
	inline void SetBossType(BossType _CurType)
	{
		CurType_ = _CurType;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	inline float4 GetPlayerPosition()
	{
		return Player::MainPlayer_->GetPosition();
	}
	inline float4 GetPosition()
	{
		return GetTransform().GetLocalPosition();
	}


	void ChangeState(BossState _State);
	void MonsterStateUpdate() override;
	void Hit() override;
	void DirChange() override;
	void Attack() override;
	void CollisonCheck() override;

protected:
	// Start
	void IdleStart() override;
	void MoveStart() override;
	void DamagedStart() override;
	void DieStart() override;
	void AttackAStart();	// 내려치기
	void AttackBStart();	// 찌르기 
	void AttackCStart();	// 모자 떨구기
	void TransformStart();	// 노멀 -> 다른 보스
	void RegenStart();		// 다른 보스 -> 노멀
	
	void BlueAttackStart();	

	void RedAttackAStart();			// 한 번 내려치기
	void RedAttackBStart();			// TeleRegen 후 세 번 내려치기	
	void RedTeleportStart();	
	void RedTeleportRegenStart();	// 플레이어 자리에 나타나기


	// Update
	void IdleUpdate() override;
	void MoveUpdate() override;
	void DamagedUpdate() override;
	void DieUpdate() override;
	void AttackAUpdate();
	void AttackBUpdate();
	void AttackCUpdate();
	void TransformUpdate();
	void RegenUpdate();

	void BlueAttackUpdate();

	void RedAttackAUpdate();			// 한 번 내려치기
	void RedAttackBUpdate();			// TeleRegen 후 세 번 내려치기	
	void RedTeleportUpdate();
	void RedTeleportRegenUpdate();	// 플레이어 자리에 나타나기

	void BindBossDieEnd(const FrameAnimation_DESC& _Info);
	void BindBossAttackStart(const FrameAnimation_DESC& _Info);
	void BindBossAttackEnd(const FrameAnimation_DESC& _Info);
	void BindBossDamagedEnd(const FrameAnimation_DESC& _Info);

private:
	GameEngineCollision* AttackACollision_;
	GameEngineCollision* AttackBCollision_;

private:
	BossType CurType_;
	BossState CurState_;
	float4 PlayerPos_;
	float4 Position_;
};

