#include "PreCompile.h"
#include "MapBackGround.h"
#include <GameEngineCore/GameEngineTextureRenderer.h>

MapBackGround::MapBackGround() 
{
}

MapBackGround::~MapBackGround() 
{
}

void MapBackGround::Start()
{
	MapBackGroundRender_ = CreateComponent<GameEngineTextureRenderer>();
	MapBackGroundRender_->SetPivot(PIVOTMODE::LEFTTOP);
}

void MapBackGround::Render()
{
}

void MapBackGround::Update()
{
}
