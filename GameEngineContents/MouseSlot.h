#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>

class GameEngineCollision;
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

	bool IsHold_;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineUIRenderer* HoldItemRenderer_;

	GameEngineCollision* Collision_;

	// ¸¶¿ì½º
	GameEngineUIRenderer* MouseRenderer_;
	GameEngineCollision* MouseCollision_;
};

