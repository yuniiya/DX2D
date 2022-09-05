#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineFontRenderer;
class Mouse;
class QuestUI : public GameEngineActor
{
public:
	// constrcuter destructer
	QuestUI();
	~QuestUI();

	// delete Function
	QuestUI(const QuestUI& _Other) = delete;
	QuestUI(QuestUI&& _Other) noexcept = delete;
	QuestUI& operator=(const QuestUI& _Other) = delete;
	QuestUI& operator=(QuestUI&& _Other) noexcept = delete;

public:
	void SetNPCType(NPCType _NPCType);

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void CollisionCheck();

private:
	GameEngineFontRenderer* NPCNameFont_;

	GameEngineUIRenderer* Renderer_;
	GameEngineUIRenderer* UINPCRenderer_;
	GameEngineUIRenderer* But_;

	GameEngineCollision* ButCol_;
	GameEngineCollision* ExitCol;

	NPCType NPCType_;
};

