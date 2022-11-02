#include <Windows.h>

#pragma comment(lib, "GameEngineBase.lib")
#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

#include <GameEngineContents/ContentsCore.h>
#include <GameEngineBase/GameEngineMath.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow){
	//new int();

	//_CrtSetBreakAlloc(62612);

	GameEngineCore::Start<ContentsCore>();

	return 0;
}

