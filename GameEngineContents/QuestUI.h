#pragma once
#include <GameEngineCore/GameEngineActor.h>

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

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void CollisionCheck();

private:
	GameEngineUIRenderer* Renderer_;
	GameEngineUIRenderer* But_;

	GameEngineCollision* ButCol_;
	GameEngineCollision* ExitCol;
};

