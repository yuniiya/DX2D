#pragma once
#include "GameEngineRes.h"

// 설명 : 최종 픽셀쉐이더의 출력결과를 랜더타겟에 출력할때 누가 앞이고 누가 뒤인지에 대한 처리
class GameEngineDepthStencil : public GameEngineRes<GameEngineDepthStencil>
{
public:
	// constrcuter destructer
	GameEngineDepthStencil();
	~GameEngineDepthStencil();

	// delete Function
	GameEngineDepthStencil(const GameEngineDepthStencil& _Other) = delete;
	GameEngineDepthStencil(GameEngineDepthStencil&& _Other) noexcept = delete;
	GameEngineDepthStencil& operator=(const GameEngineDepthStencil& _Other) = delete;
	GameEngineDepthStencil& operator=(GameEngineDepthStencil&& _Other) noexcept = delete;

protected:

private:

};

