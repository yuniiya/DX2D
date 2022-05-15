#include "ContentsCore.h"

#pragma comment(lib, "GameEngineBase.lib")

ContentsCore::ContentsCore()
	: GameEngineCore()
{
}

ContentsCore::~ContentsCore()
{
}

void ContentsCore::UserGameStart()
{
	// 리소스를 로드하는데.

	// 게임컨텐츠 정의
	// 이 게임에는 타이틀화면
	//            스테이지1
	//            스테이지2
}

void ContentsCore::UserGameUpdate()
{
	// 서버가 종료되었어.
	// 무조건 경고 메세지창을 띄워줘야한다.
}

void ContentsCore::UserGameEnd()
{
	int a = 0;
}