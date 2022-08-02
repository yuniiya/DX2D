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
#include "GameEngineContents/SelectLevel.h"
#include "GameEngineContents/TitleLevel.h"



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
		Dir.Move("Map");
		Dir.Move("BossLevel");
		Dir.Move("Stage_Boss");

		GameEngineFolderTexture::Load(Dir.GetFullPath());

		//std::vector<GameEngineDirectory> Folder = Dir.GetRecursiveAllDirectory();

		//for (GameEngineDirectory Dir : Folder)
		//{
		//	GameEngineFolderTexture::Load(Dir.GetFullPath());
		//}
	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Player");

		std::vector<GameEngineDirectory> Folder = Dir.GetRecursiveAllDirectory();

		for (GameEngineDirectory Dir : Folder)
		{
			GameEngineFolderTexture::Load(Dir.GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Map");

		std::vector<GameEngineDirectory> Folder = Dir.GetRecursiveAllDirectory();

		for (auto& TmpDir : Folder)
		{
			std::vector<GameEngineFile> File = TmpDir.GetAllFile();

			for (size_t i = 0; i < File.size(); i++)
			{
				GameEngineTexture::Load(File[i].GetFullPath());
			}
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");

		std::vector<GameEngineDirectory> Folder = Dir.GetRecursiveAllDirectory();

		for (GameEngineDirectory Dir : Folder)
		{
			GameEngineFolderTexture::Load(Dir.GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Obj");

		std::vector<GameEngineDirectory> Folder = Dir.GetRecursiveAllDirectory();

		for (GameEngineDirectory Dir : Folder)
		{
			GameEngineFolderTexture::Load(Dir.GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("UIAnimation");

		std::vector<GameEngineDirectory> Folder = Dir.GetRecursiveAllDirectory();

		for (GameEngineDirectory Dir : Folder)
		{
			GameEngineFolderTexture::Load(Dir.GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("AbillityUI");

		std::vector<GameEngineFile> File = Dir.GetAllFile();

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("BottomUI");

		std::vector<GameEngineFile> File = Dir.GetAllFile();

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("BossUI");

		std::vector<GameEngineFile> File = Dir.GetAllFile();

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("Cursor");

		std::vector<GameEngineFile> File = Dir.GetAllFile();

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("DieUI");

		std::vector<GameEngineFile> File = Dir.GetAllFile();

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("InventoryUI");

		std::vector<GameEngineFile> File = Dir.GetAllFile();

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("LoginUI");

		std::vector<GameEngineFile> File = Dir.GetAllFile();

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("ShopUI");

		std::vector<GameEngineFile> File = Dir.GetAllFile();

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("SkillIcon");

		std::vector<GameEngineFile> File = Dir.GetAllFile();

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	// »ç¿îµå
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Sound");
		Dir.Move("Effect");

		std::vector<GameEngineFile> File = Dir.GetAllFile();

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineSound::LoadRessource(File[i].GetFullPath());
		}
	}



	if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", 'P');
		//GameEngineInput::GetInst()->CreateKey("CameraLeft", VK_NUMPAD1);
		//GameEngineInput::GetInst()->CreateKey("CameraRight", VK_NUMPAD3);
		//GameEngineInput::GetInst()->CreateKey("CameraUp", VK_NUMPAD5);
		//GameEngineInput::GetInst()->CreateKey("CameraDown", VK_NUMPAD2);

		GameEngineInput::GetInst()->CreateKey("FreeCameraOnOff", VK_OEM_4);		// [
		GameEngineInput::GetInst()->CreateKey("DebugModeOnOff", VK_OEM_6);			// ]
	}


	//CreateLevel<TitleLevel>("Title");
	CreateLevel<LoginLevel>("Login");
	CreateLevel<SelectLevel>("Select");
	CreateLevel<AriantLevel>("Ariant");
	CreateLevel<EntranceLevel>("Entrance");
	CreateLevel<CastleLevel>("Castle");
	CreateLevel<CactusLevel>("Cactus");
	CreateLevel<DesertLevel>("Desert");
	CreateLevel<AquaLevel>("Aqua");
	CreateLevel<BossLevel>("Boss");
	//CreateLevel<EndingLevel>("End");

	ChangeLevel("Ariant");

	//GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);


}

void ContentsCore::Update(float _DeltaTime)
{
}

void ContentsCore::End()
{
	int a = 0;
}