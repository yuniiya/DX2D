#pragma once
#include "GameEngineCore/GameEngineLevel.h"
#include "ContentsUI.h"

class MapBackGround;
class MapStage;
class Portal;
class GameEngineTextureRenderer;
class Player;
class ContentsUI;
class Inventory;
class Mouse;
class NPC;
class Boss;
class GlobalLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	GlobalLevel();
	~GlobalLevel();

	// delete Function
	GlobalLevel(const GlobalLevel& _Other) = delete;
	GlobalLevel(GlobalLevel&& _Other) noexcept = delete;
	GlobalLevel& operator=(const GlobalLevel& _Other) = delete;
	GlobalLevel& operator=(GlobalLevel&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {};

	void LevelStartEvent() override;

private:
	float4 CameraPos_;
	float CameraPosX_;
	float CameraPosY_;

	float MapSizeX_;
	float MapSizeY_;

	GameEngineTextureRenderer* ColMapRenderer_;
	GameEngineTextureRenderer* StageRenderer_;
	GameEngineTextureRenderer* BackRenderer_;

	GameEngineTextureRenderer* AriantSunLight_;

public:
	inline Mouse* GetMouse()
	{
		return Mouse_;
	}

	inline ContentsUI* GetContentsUI()
	{
		return ContentsUI_;
	}

	inline Inventory* GetInventory()
	{
		return Inventory_;
	}

	inline GameEngineTextureRenderer* GetCollisionMap()
	{
		return ColMapRenderer_;
	}

	inline Boss* GetBoss()
	{
		return Boss_;
	}

	inline void CollisionMapOnOff()
	{
		StageRenderer_->OnOffSwitch();
		BackRenderer_->OnOffSwitch();
	}

	void MapSizeReturn(float _X, float _Y)
	{
		MapSizeX_ = _X;
		MapSizeY_ = _Y;
	}

	void CameraFix(float4 _MapSize);

protected:
	void SetCamera();
	void SetBackGround(const std::string& _Name);
	void SetStage(const std::string& _Name);
	void SetCollisionMap(const std::string& _Name);
	void SetPortal(float4 _Pos);
	void SetAriantSunLight(float _YPos);

	Boss* Boss_;

private:
	Mouse* Mouse_;
	ContentsUI* ContentsUI_;

	Inventory* Inventory_;
	MapBackGround* BackGroundActor;
};

