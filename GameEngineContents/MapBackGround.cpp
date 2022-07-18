#include "PreCompile.h"
#include "MapBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
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
}

void MapBackGround::Render()
{
}

void MapBackGround::Update()
{
}
