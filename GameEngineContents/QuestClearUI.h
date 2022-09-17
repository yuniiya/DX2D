#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class QuestClearUI : public GameEngineActor
{
public:
	// constrcuter destructer
	QuestClearUI();
	~QuestClearUI();

	// delete Function
	QuestClearUI(const QuestClearUI& _Other) = delete;
	QuestClearUI(QuestClearUI&& _Other) noexcept = delete;
	QuestClearUI& operator=(const QuestClearUI& _Other) = delete;
	QuestClearUI& operator=(QuestClearUI&& _Other) noexcept = delete;

public:
	inline GameEngineUIRenderer* GetRenderer()
	{
		return Renderer_;
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

private:
	GameEngineUIRenderer* Renderer_;

	bool IsClearSoundOn_;
	float AlertTime_;
};

