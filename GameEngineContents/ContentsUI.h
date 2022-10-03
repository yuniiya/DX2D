#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineUIRenderer;
class QuickSlotItem;
class ContentsUI : public GameEngineActor
{
public:

	static ContentsUI* MainUI_;

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

	inline QuickSlotItem* GetQuickSlotItem()
	{
		return QuickSlotItem_;
	}

	inline std::vector<QuickSlotItem*> GetQuickSlotItemsList()
	{
		return QuickSlotItemsList_;
	}

	inline ItemType GetItemType()
	{
		return ItemType_;
	}

	inline void SetItemType(ItemType _ItemType)
	{
		ItemType_ = _ItemType;
	}

	inline void SetQuickSlotItem(QuickSlotItem* _QuickSlotItem)
	{
		QuickSlotItem_ = _QuickSlotItem;
	}


protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void GameExit();

private:
	float4 HPBarPos_;
	float4 MPBarPos_;
	float4 ExpBarPos_;
	float4 CamPos_;

	float4 HPBarScale_;
	float4 MPBarScale_;
	float4 ExpBarScale_;

	float4 SlotPosition_;
	float4 StartPosition_;

	float CurHP_;
	float CurMP_;
	float CurExp_;

	int SlotKey_;
	int SlotKey_1;
	int SlotKey_2;
	
	bool IsExitNoticeOn_;
	bool IsExitOn_;
private:
	GameEngineUIRenderer* MainBar_;
	GameEngineUIRenderer* BarBgr_1;
	GameEngineUIRenderer* BarBgr_2;
	GameEngineUIRenderer* ExpBack_;
	GameEngineUIRenderer* QuickSlotBack_;
	GameEngineUIRenderer* QuickSlot_;
	GameEngineUIRenderer* Level_;
	GameEngineUIRenderer* ExitNotice_;
	GameEngineUIRenderer* YesButton_;
	GameEngineUIRenderer* NoButton_;

	GameEngineUIRenderer* HpBar_;
	GameEngineUIRenderer* MpBar_;
	GameEngineUIRenderer* ExpBar_;

private:
	GameEngineCollision* SlotCollision_;
	GameEngineCollision* SlotCollision_1;
	GameEngineCollision* SlotCollision_2;
	GameEngineCollision* SlotCollision_3;
	GameEngineCollision* SlotCollision_4;
	GameEngineCollision* SlotCollision_5;
	GameEngineCollision* YesCollision_;
	GameEngineCollision* NoCollision_;

	QuickSlotItem* QuickSlotItem_;
	ItemType ItemType_;


	std::vector<QuickSlotItem*> QuickSlotItemsList_;

};

