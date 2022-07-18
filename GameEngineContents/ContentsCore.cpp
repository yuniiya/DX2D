#include "PreCompile.h"
#include "ContentsCore.h"
#include "GameEngineContents/LoginLevel.h"
#include "GameEngineContents/AriantLevel.h"
#include "GameEngineContents/EntranceLevel.h"
#include "GameEngineContents/CastleLevel.h"
#include "GameEngineContents/CactusLevel.h"
#include "GameEngineContents/DesertLevel.h"
#include "GameEngineContents/AquaLevel.h"
#include "GameEngineContents/BossLevel.h"



#pragma comment(lib, "GameEngineBase.lib")

ContentsCore::ContentsCore() 
	: GameEngineCore()
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Login");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Map");
		Dir.Move("CactusLevel");

		std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

		for (size_t i = 0; i < Shaders.size(); i++)
		{
			GameEngineTexture::Load(Shaders[i].GetFullPath());
		}
	}




	if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", 'P');
	}

	CreateLevel<LoginLevel>("Title");;
	CreateLevel<AriantLevel>("Ariant");
	CreateLevel<EntranceLevel>("Entrance");
	CreateLevel<CastleLevel>("Castle");
	CreateLevel<CactusLevel>("Cactus");
	CreateLevel<DesertLevel>("Desert");
	CreateLevel<AquaLevel>("Aqua");
	CreateLevel<BossLevel>("Boss");
	//CreateLevel<EndingLevel>("End");

	ChangeLevel("Title");

}

void ContentsCore::Update(float _DeltaTime)
{

	
}

void ContentsCore::End()
{
	int a = 0;
}