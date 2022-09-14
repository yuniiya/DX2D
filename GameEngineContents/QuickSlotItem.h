#pragma once
#include "InventoryItem.h"

// Ό³Έν :
class QuickSlotItem : public InventoryItem
{
public:
	// constrcuter destructer
	QuickSlotItem();
	~QuickSlotItem();

	// delete Function
	QuickSlotItem(const QuickSlotItem& _Other) = delete;
	QuickSlotItem(QuickSlotItem&& _Other) noexcept = delete;
	QuickSlotItem& operator=(const QuickSlotItem& _Other) = delete;
	QuickSlotItem& operator=(QuickSlotItem&& _Other) noexcept = delete;

public:
	void CollisionCheck() override;
	void QuickSlotCollisionCheck();
	
	inline int GetQuickSlotIndex()
	{
		return QuickSlotIndex_;
	}

	inline void SetQuickSlotIndex(int _QuickSlotIndex)
	{
		QuickSlotIndex_ = _QuickSlotIndex;
	}
protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void SlotKeyCheck();
	bool SlotKeyInputCheck();
	
private:
	int QuickSlotIndex_;
	int SlotKey_;
	InventoryItem* InventoryItem_;
};

