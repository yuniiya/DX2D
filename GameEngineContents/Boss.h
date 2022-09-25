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
	BLUE_Damaged,
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
	inline float4 GetPosition()
	{
		return GetTransform().GetLocalPosition();
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	inline float4 GetPlayerPosition()
	{
		return Player::MainPlayer_->GetPosition();
	}

	inline void SetBossSkill(BossAttackType _CurBossSkill)
	{
		CurBossSkill_ = _CurBossSkill;
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
	void TransformStart();	// ��� -> �ٸ� ����
	void RegenStart();		// �ٸ� ���� -> ���
	void AttackAStart();	// ����ġ��
	void AttackBStart();	// ��� 
	void AttackCStart();	// ���� ������
	
	void BlueAttackStart();	
	void BlueDamagedStart();
	void RedAttackAStart();			// �� �� ����ġ��
	void RedAttackBStart();			// TeleRegen �� �� �� ����ġ��	
	void RedTeleportStart();	
	void RedTeleportRegenStart();	// �÷��̾� �ڸ��� ��Ÿ����


	// Update
	void IdleUpdate() override;
	void MoveUpdate() override;
	void DamagedUpdate() override;
	void DieUpdate() override;
	void TransformUpdate();
	void RegenUpdate();
	void AttackAUpdate();
	void AttackBUpdate();
	void AttackCUpdate();

	void BlueAttackUpdate();
	void BlueDamagedUpdate();
	void RedAttackAUpdate();			// �� �� ����ġ��
	void RedAttackBUpdate();			// TeleRegen �� �� �� ����ġ��	
	void RedTeleportUpdate();
	void RedTeleportRegenUpdate();	// �÷��̾� �ڸ��� ��Ÿ����

	void BindBossAttackStart(const FrameAnimation_DESC& _Info);
	void BindBossAttackFrame(const FrameAnimation_DESC& _Info);
	void BindBossAttackEnd(const FrameAnimation_DESC& _Info);
	void BindBossDamagedEnd(const FrameAnimation_DESC& _Info);
	void BindBossTransformFrame(const FrameAnimation_DESC& _Info);
	void BindBossTransformEnd(const FrameAnimation_DESC& _Info);
	void BindBossRegenEnd(const FrameAnimation_DESC& _Info);
	void BindRedBossTelEnd(const FrameAnimation_DESC& _Info);
	void BindRedBossTelRegenEnd(const FrameAnimation_DESC& _Info);
	void BindBossDieFrame(const FrameAnimation_DESC& _Info);
	void BindBossDieEnd(const FrameAnimation_DESC& _Info);

private:
	GameEngineCollision* AttackACollision_;		// ��� A : 2�ʰ� �����¿� ���� �ٲ�
	GameEngineCollision* AttackBCollision_;		// ��� B : �˹�, 3�� ����
	GameEngineCollision* BlueAttackACollision_;	// ��� A : ��ų ���� 
	GameEngineCollision* RedAttackACollision_;	// ���� A : �� �� ����ġ��, ���ο�
	GameEngineCollision* RedAttackBCollision_;	// ���� B : �� �� ����

private:
	BossType CurType_;
	BossState CurState_;
	BossAttackType CurBossSkill_;
	float4 PlayerPos_;
	float4 Position_;

	bool BossTypeChange_;
	bool IsTeleport_;
	bool IsTeleportStart_;
	bool IsChase_;

	float CreateHatTime_; 
	float TypeChangeTime_;
	float TransformTime_;
	float TeleportTime_;
	float ChaseTime_;
	float Speed_;
	float BlueSpeed_;
	float RandomTime_;
	int Random_;
};

