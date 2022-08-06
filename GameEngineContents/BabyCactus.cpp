#include "PreCompile.h"
#include "BabyCactus.h"

BabyCactus::BabyCactus() 
{
}

BabyCactus::~BabyCactus() 
{
}

void BabyCactus::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Cactus_Idle");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Cactus_Walk");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Cactus_Hit");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Cactus_Die");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}


}

void BabyCactus::Update(float _DeltaTime)
{
}

