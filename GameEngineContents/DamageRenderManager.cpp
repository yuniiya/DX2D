#include "PreCompile.h"
#include "DamageRenderManager.h"
#include "DamageNumber.h"

DamageRenderManager* DamageRenderManager::DamageMgr_ = nullptr;
DamageRenderManager::DamageRenderManager()
	: MonsterTexName_("RedDamage1_0")
	, PlayerTexName_("VioletDamage1_0")

{
}

DamageRenderManager::~DamageRenderManager()
{
}

void DamageRenderManager::Start()
{
	Init();
}

void DamageRenderManager::Update(float _DeltaTime)
{
}

void DamageRenderManager::Init()
{
	std::string Name = "";

	for (int i = 0; i < 10; i++)
	{
		GameEngineTextureRenderer* MRenderer = CreateComponent<GameEngineTextureRenderer>();
		Name = MonsterTexName_ + std::to_string(i) + ".png";
		MRenderer->SetTexture(Name);
		MRenderer->ScaleToTexture();
		Storage_MonsterDmgRenderers_.push_back(MRenderer);

		GameEngineTextureRenderer* PRenderer = CreateComponent<GameEngineTextureRenderer>();
		Name = PlayerTexName_ + std::to_string(i) + ".png";
		PRenderer->SetTexture(Name);
		PRenderer->ScaleToTexture();
		Storage_PlayerDmgRenderers_.push_back(PRenderer);
	}
}

GameEngineTexture* DamageRenderManager::GetDamageTexture(DamageTextureType _DamageType, int _Index)
{
	if (true == Storage_MonsterDmgRenderers_.empty()
		|| true == Storage_PlayerDmgRenderers_.empty())
	{
		return nullptr;
	}

	
	switch (_DamageType)
	{
	case DamageTextureType::Player:
		return Storage_PlayerDmgRenderers_[_Index]->GetCurTexture();
		break;
	case DamageTextureType::Monster:
		return Storage_MonsterDmgRenderers_[_Index]->GetCurTexture();
		break;
	}

	return nullptr;
}

DamageNumber* DamageRenderManager::GetDamageNumActor()
{
	DamageNum_ = GetLevel()->CreateActor<DamageNumber>();

	return DamageNum_;
}
