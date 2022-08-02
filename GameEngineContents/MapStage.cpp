#include "PreCompile.h"
#include "MapStage.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>

MapStage::MapStage() 
	: MapStageRender_(nullptr)
{
}

MapStage::~MapStage() 
{
}

void MapStage::Start()
{
	MapStageRender_ = CreateComponent<GameEngineTextureRenderer>();
	MapStageRender_->SetPivot(PIVOTMODE::LEFTTOP);
}

