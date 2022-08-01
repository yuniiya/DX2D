#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class SelectUI : public GameEngineActor
{
public:
	// constrcuter destructer
	SelectUI();
	~SelectUI();

	// delete Function
	SelectUI(const SelectUI& _Other) = delete;
	SelectUI(SelectUI&& _Other) noexcept = delete;
	SelectUI& operator=(const SelectUI& _Other) = delete;
	SelectUI& operator=(SelectUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	GameEngineTextureRenderer* PrevButton_;
	GameEngineTextureRenderer* GameStartButton_;
	GameEngineTextureRenderer* InfoUI_;
	GameEngineTextureRenderer* PlayerObjUI_;
	GameEngineTextureRenderer* Player_;
	GameEngineTextureRenderer* PlayerMouseOverEfect_;
	GameEngineTextureRenderer* PlayerSelectEffect_;
	GameEngineTextureRenderer* NullPlayer_;
	GameEngineTextureRenderer* NullEffect_;

};

