#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

class MapBackGround;
class CactusLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	CactusLevel();
	~CactusLevel();

	// delete Function
	CactusLevel(const CactusLevel& _Other) = delete;
	CactusLevel(CactusLevel&& _Other) noexcept = delete;
	CactusLevel& operator=(const CactusLevel& _Other) = delete;
	CactusLevel& operator=(CactusLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override;

private:
	MapBackGround* BackGround_;

};

