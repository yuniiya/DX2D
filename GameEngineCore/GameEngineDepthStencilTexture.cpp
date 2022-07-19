#include "PreCompile.h"
#include "GameEngineDepthStencilTexture.h"

GameEngineDepthStencilTexture::GameEngineDepthStencilTexture() 
{
}

GameEngineDepthStencilTexture::~GameEngineDepthStencilTexture() 
{
}


GameEngineDepthStencilTexture* GameEngineDepthStencilTexture::Create(const float4 _Scale)
{
	GameEngineDepthStencilTexture* Res = CreateResUnName();
	Res->CreateDepthTexture(_Scale);
	return Res;
}

void GameEngineDepthStencilTexture::CreateDepthTexture(const float4 _Scale)
{
	//Buffer->TextureCreate;
}