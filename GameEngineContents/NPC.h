#pragma once
#include "GameEngineCore/GameEngineActor.h"

class GameEngineCollision;
class QuestUI;
class NPC : public GameEngineActor
{
public:
	// constrcuter destructer
	NPC();
	~NPC();

	// delete Function
	NPC(const NPC& _Other) = delete;
	NPC(NPC&& _Other) noexcept = delete;
	NPC& operator=(const NPC& _Other) = delete;
	NPC& operator=(NPC&& _Other) noexcept = delete;

public:
	inline GameEngineTextureRenderer* GetRenderer()
	{
		return Renderer_;
	}

	inline GameEngineCollision* GetCollision()
	{
		return Collision_;
	}

	void SetNPCType(NPCType _NPCType);

	void SetQuestRendererPosition()
	{
		QuestRenderer_->GetTransform().SetLocalPosition({
			Renderer_->GetTransform().GetLocalPosition().x + 22.f
			, Renderer_->GetTransform().GetLocalPosition().y + 67.f});
	}

	bool IsQuestOngoing_;
	bool IsQuestClear_;
	bool IsQuestEnd_;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void CollisonCheck();

	GameEngineCollision* Collision_;
	QuestUI* QuestUI_;

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineTextureRenderer* QuestRenderer_;
	GameEngineUIRenderer* QuestClearRenderer_;

	NPCType NPCType_;


private:
	bool IsClick_;
};

