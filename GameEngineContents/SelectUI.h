#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Mouse;
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

	bool MouseCollisionCheck(GameEngineCollision* _This, GameEngineCollision* _Other);
	void CollisionCheck();

	bool SoundPlay;
	bool AlreadyPlay;
	bool GameStart;

	float Time_;

private:
	GameEngineTextureRenderer* PrevButton_;
	GameEngineTextureRenderer* GameStartButton_;
	GameEngineTextureRenderer* InfoUI_;
	GameEngineTextureRenderer* PlayerObjUI_;
	GameEngineTextureRenderer* Player_;
	GameEngineTextureRenderer* PlayerMouseOverEfect_;
	GameEngineTextureRenderer* PlayerSelectEffect_;

	GameEngineTextureRenderer* NullPlayer1_;
	GameEngineTextureRenderer* NullPlayer2_;
	GameEngineTextureRenderer* NullPlayer3_;
	GameEngineTextureRenderer* NullPlayer4_;
	GameEngineTextureRenderer* NullPlayer5_;

	GameEngineTextureRenderer* NullEffect1_;
	GameEngineTextureRenderer* NullEffect2_;
	GameEngineTextureRenderer* NullEffect3_;
	GameEngineTextureRenderer* NullEffect4_;
	GameEngineTextureRenderer* NullEffect5_;

	GameEngineCollision* PrevButtonCol_;
	GameEngineCollision* GameStartButtonCol_;
	GameEngineCollision* PlayerCol_;

};

