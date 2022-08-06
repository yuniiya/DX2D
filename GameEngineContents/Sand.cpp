#include "PreCompile.h"
#include "Sand.h"

Sand::Sand()
{
}

Sand::~Sand()
{
}

void Sand::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Sand_Idle");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Sand_Walk");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Sand_Hit");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Sand_Die");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}
}

void Sand::Update(float _DeltaTime)
{
}

