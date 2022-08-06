#include "PreCompile.h"
#include "WhiteRabbit.h"

WhiteRabbit::WhiteRabbit() 
{
}

WhiteRabbit::~WhiteRabbit() 
{
}

void WhiteRabbit::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Rabbit1_Idle");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Rabbit1_Walk");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Rabbit1_Hit");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Rabbit1_Die");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}
}

void WhiteRabbit::Update(float _DeltaTime)
{
}

