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
	void SetNPCType(NPCType _NPCType);

	void SetQuestRendererPosition()
	{
		QuestRenderer_->GetTransform().SetLocalPosition({
			Renderer_->GetTransform().GetLocalPosition().x + 22.f
			, Renderer_->GetTransform().GetLocalPosition().y + 67.f});
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void CollisonCheck();

private:
	GameEngineTextureRenderer* Renderer_;
	GameEngineTextureRenderer* QuestRenderer_;
	GameEngineUIRenderer* MouseRenderer_;
	GameEngineUIRenderer* MouseAnimationRenderer_;

	GameEngineCollision* Collision_;
	GameEngineCollision* MouseCollision_;

	NPCType NPCType_;

private:
	bool IsClick_;

	QuestUI* QuestUI_;
};

