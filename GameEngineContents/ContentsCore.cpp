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
#include "GameEngineContents/TestLevel.h"
#include "GameBgmPlayer.h"
#include "KeyboardClass.h"



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
		Dir.Move("Intro");


		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Map");
		Dir.Move("BossLevel");
		Dir.Move("Stage_Boss");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
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
		Dir.Move("Player_BlueHat");

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
		Dir.Move("Player_RedHat");

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
		Dir.Move("Monster");
		Dir.Move("Boss");

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
		Dir.Move("Skill");

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
		Dir.Move("Object");

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
		Dir.Move("Object");
		Dir.Move("NPC");

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
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("UI");
		Dir.Move("Quest");

		std::vector<GameEngineFile> File = Dir.GetAllFile();

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineTexture::Load(File[i].GetFullPath());
		}
	}

	// 사운드
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

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Sound");
		Dir.Move("Bgm");

		std::vector<GameEngineFile> File = Dir.GetAllFile();

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineSound::LoadRessource(File[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Sound");
		Dir.Move("Skill");

		std::vector<GameEngineFile> File = Dir.GetAllFile();

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineSound::LoadRessource(File[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Sound");
		Dir.Move("MonsterEffect");

		std::vector<GameEngineFile> File = Dir.GetAllFile();

		for (size_t i = 0; i < File.size(); i++)
		{
			GameEngineSound::LoadRessource(File[i].GetFullPath());
		}
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Sound");
		Dir.Move("MonsterEffect");
		Dir.Move("Boss");

		std::vector<GameEngineDirectory> Folder = Dir.GetRecursiveAllDirectory();

		for (auto& TmpDir : Folder)
		{
			std::vector<GameEngineFile> File = TmpDir.GetAllFile();

			for (size_t i = 0; i < File.size(); i++)
			{
				GameEngineSound::LoadRessource(File[i].GetFullPath());
			}
		}
	}

	// 몬스터
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Rabbit2_Idle");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Rabbit2_Walk");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}


	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Rabbit2_Hit");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Rabbit2_Die");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

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

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Sparker_Idle");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Sparker_Walk");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Sparker_Hit");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Sparker_Die");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Sparker_Eff");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Sparker_Att");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Freezer_Idle");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Freezer_Walk");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Freezer_Hit");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Freezer_Die");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Freezer_Eff");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Freezer_Att");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Scol_Idle");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Scol_Walk");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Scol_Hit");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Monster");
		Dir.Move("Scol_Die");

		GameEngineFolderTexture::Load(Dir.GetFullPath());
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExitsChildDirectory("Resources");
		Dir.Move("Resources");
		Dir.Move("Texture");
		Dir.Move("Test");

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
		Dir.Move("Item");
		Dir.Move("NormalItem");

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
		Dir.Move("Item");
		Dir.Move("Meso");

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
		Dir.Move("Item");
		Dir.Move("InvenItem");


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
		Dir.Move("DamageNumber");

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
		Dir.Move("MapAnimation");

		std::vector<GameEngineDirectory> Folder = Dir.GetRecursiveAllDirectory();

		for (GameEngineDirectory Dir : Folder)
		{
			GameEngineFolderTexture::Load(Dir.GetFullPath());
		}
	}

	GameEngineTexture::Cut("Item2.png", 5, 4);

	if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", 'P');
		//GameEngineInput::GetInst()->CreateKey("CameraLeft", VK_NUMPAD1);
		//GameEngineInput::GetInst()->CreateKey("CameraRight", VK_NUMPAD3);
		//GameEngineInput::GetInst()->CreateKey("CameraUp", VK_NUMPAD5);
		//GameEngineInput::GetInst()->CreateKey("CameraDown", VK_NUMPAD2);

		GameEngineInput::GetInst()->CreateKey("FreeCameraOnOff", VK_OEM_4);		// [
		GameEngineInput::GetInst()->CreateKey("DebugModeOnOff", VK_OEM_6);			// ]
		GameEngineInput::GetInst()->CreateKey("Exit", VK_ESCAPE);
		GameEngineInput::GetInst()->CreateKey("Next", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("DialogExit", VK_TAB);
	}

	CreateLevel<TitleLevel>("Title");
	CreateLevel<LoginLevel>("Login");
	CreateLevel<SelectLevel>("Select");
	CreateLevel<AriantLevel>("Ariant");
	CreateLevel<EntranceLevel>("Entrance");
	CreateLevel<CastleLevel>("Castle");
	CreateLevel<CactusLevel>("Cactus");
	CreateLevel<DesertLevel>("Desert");
	CreateLevel<AquaLevel>("Aqua");
	CreateLevel<BossLevel>("Boss");
	CreateLevel<TestLevel>("Test");
	//CreateLevel<EndingLevel>("End");

	ChangeLevel("Title");

	GameEngineGUI::CreateGUIWindow<GameEngineStatusWindow>("EngineStatus", nullptr);


}

void ContentsCore::Update(float _DeltaTime)
{
}

void ContentsCore::End()
{
	GameBgmPlayer::BgmPlay_->Destroy();
	KeyboardClass::Destory();
}