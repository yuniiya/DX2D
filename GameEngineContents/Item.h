#pragma once
#include <GameEngineCore/GameEngineActor.h>

struct ItemState
{
	ItemType ItemType_;
	int Count_;
	int Price_;
};

enum class ItemMoveState
{
	Drop,
	Float,

	MAX,
};

class GameEngineTextureRenderer;
class Item : public GameEngineActor
{
	friend Inventory;

public:
	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

public:
	virtual void TimeAttackStart();

	inline virtual float4 GetItemPosition()
	{
		return GetTransform().GetLocalPosition();
	}

	inline ItemType GetItemType()
	{
		return ItemState_.ItemType_;
	}

	inline InventorySlotType GetSlotType()
	{
		return SlotType_;
	}

	inline int GetCount()
	{
		return ItemState_.Count_;
	}

	inline int GetPrice()
	{
		return ItemState_.Price_;
	}

	inline GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer_;
	}

	inline void SetItemType(ItemType _ItemType)
	{
		ItemState_.ItemType_ = _ItemType;
	}

	inline void SetSlotType(InventorySlotType _SlotType)
	{
		SlotType_ = _SlotType;
	}

	inline void SetMonsterName(MONSTERNAME _MonsterName)
	{
		MonsterName_ = _MonsterName;
	}

	void RendererTypeSetting();
	void PotionRendererTypeSetting();

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	GameEngineTexture* GetCurMapTexture();
	virtual bool StagePixelCheck();

	virtual void TimeAttackUpdate(GameEngineTextureRenderer* _Renderer, float _DeltaTime);
	virtual void UpDownMove(float _DeltaTime);
	virtual void PickUpItem(GameEngineTextureRenderer* _Renderer, float _DeltaTime);
	virtual void PickUpItemCheck(GameEngineTextureRenderer* _Renderer, float _DeltaTime);
	virtual void ItemDrop(float _DeltaTime);

	virtual void ChangeState(ItemMoveState _State);
	virtual void ItemStateUpdate(float _DeltaTime);

	virtual void DropStart();
	virtual void FloatStart();
	virtual void DropUpdate(float _DeltaTime);
	virtual void FloatUpdate(float _DeltaTime);

protected:
	bool IsCreate;
	bool IsPick;
	bool IsGround;

	float DropTime_;
	float Time_;
	float MoveTime_;
	float PickTime_;
	float4 MoveDir_;
	float4 CreatePosition_;

	std::string CurLevelName_;
	ItemMoveState CurState_;

public:
	MONSTERNAME MonsterName_;
	ItemState ItemState_;
	InventorySlotType SlotType_;

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineTexture* MapTexture_;


//	GameEngineCollision* Collision_;

};

