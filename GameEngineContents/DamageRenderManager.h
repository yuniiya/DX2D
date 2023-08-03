#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineTextureRenderer;
class DamageNumber;
class DamageRenderManager : public GameEngineActor
{
public:
	static DamageRenderManager* DamageMgr_;

	// constrcuter destructer
	DamageRenderManager();
	~DamageRenderManager();

	// delete Function
	DamageRenderManager(const DamageRenderManager& _Other) = delete;
	DamageRenderManager(DamageRenderManager&& _Other) noexcept = delete;
	DamageRenderManager& operator=(const DamageRenderManager& _Other) = delete;
	DamageRenderManager& operator=(DamageRenderManager&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

public:
	void Init();
	GameEngineTexture* GetDamageTexture(DamageTextureType _DamageType, int _Index);
	DamageNumber* GetDamageNumActor();

private:
	std::string MonsterTexName_;
	std::string PlayerTexName_;

	std::vector<GameEngineTextureRenderer*> Storage_MonsterDmgRenderers_;
	std::vector<GameEngineTextureRenderer*> Storage_PlayerDmgRenderers_;

	DamageNumber* DamageNum_;

};

