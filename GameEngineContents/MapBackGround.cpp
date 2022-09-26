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

	AriantSunLight_ = CreateComponent<GameEngineTextureRenderer>();
	AriantSunLight_->SetTexture("Ariant_SunLight.png");
	AriantSunLight_->ScaleToTexture();
	AriantSunLight_->Off();
}

void MapBackGround::Update(float _DeltaTime)
{
	if (true == AriantSunLight_->IsUpdate())
	{
		AriantSunLight_->GetTransform().SetLocalPosition({ GetLevel()->GetMainCameraActor()->GetTransform().GetLocalPosition().x, SunShineYPos_});
	}
}

