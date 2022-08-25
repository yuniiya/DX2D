#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class ContentsUI : public GameEngineActor
{
public:
	static ContentsUI* MainUI;

	// constrcuter destructer
	ContentsUI();
	~ContentsUI();

	// delete Function
	ContentsUI(const ContentsUI& _Other) = delete;
	ContentsUI(ContentsUI&& _Other) noexcept = delete;
	ContentsUI& operator=(const ContentsUI& _Other) = delete;
	ContentsUI& operator=(ContentsUI&& _Other) noexcept = delete;

public:
	void HPBarUpdate(float _CurHP, float _MaxHP);
	void MPBarUpdate(float _CurMP, float _MaxMP);
	void ExpBarUpdate(float _CurExp, float _MaxExp);
	void MainBarScaleUpdate();
	void LevelImageUpdate();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	float4 HPBarPos_;
	float4 MPBarPos_;
	float4 ExpBarPos_;
	float4 CamPos_;

	float4 HPBarScale_;
	float4 MPBarScale_;
	float4 ExpBarScale_;

	float4 SlotPosition_;

	float CurHP_;
	float CurMP_;
	float CurExp_;
	
private:
	GameEngineTextureRenderer* MainBar_;
	GameEngineTextureRenderer* ExpBack_;
	GameEngineTextureRenderer* QuickSlotBack_;
	GameEngineTextureRenderer* QuickSlot_;
	GameEngineTextureRenderer* Level_;

	GameEngineTextureRenderer* HpBar_;
	GameEngineTextureRenderer* MpBar_;
	GameEngineTextureRenderer* ExpBar_;

private:
	GameEngineCollision* SlotCollision_1;
	GameEngineCollision* SlotCollision_2;
	GameEngineCollision* SlotCollision_3;
	GameEngineCollision* SlotCollision_4;
	GameEngineCollision* SlotCollision_5;

};

