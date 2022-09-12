#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>

class GameEngineCollision;
class InventoryItem;
class MouseSlot : public GameEngineActor
{
public:
	// constrcuter destructer
	MouseSlot();
	~MouseSlot();

	// delete Function
	MouseSlot(const MouseSlot& _Other) = delete;
	MouseSlot(MouseSlot&& _Other) noexcept = delete;
	MouseSlot& operator=(const MouseSlot& _Other) = delete;
	MouseSlot& operator=(MouseSlot&& _Other) noexcept = delete;

public:
	inline GameEngineUIRenderer* GetRenderer()
	{
		return HoldItemRenderer_;
	}

	inline void SetInventoryItem(InventoryItem* _CurInventoryItem)
	{
		CurInventoryItem_ = _CurInventoryItem;
	}

	inline InventoryItem* GetInventoryItem()
	{
		return CurInventoryItem_;
	}

	bool IsHold_;
	bool IsDoneHolding_;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineUIRenderer* HoldItemRenderer_;
	GameEngineCollision* Collision_;

	// ¸¶¿ì½º
	//GameEngineUIRenderer* MouseRenderer_;
	//GameEngineCollision* MouseCollision_;

	InventoryItem* CurInventoryItem_;
};

