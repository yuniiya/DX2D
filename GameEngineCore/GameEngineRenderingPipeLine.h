#pragma once
#include "GameEngineRes.h"


// 설명 :
class GameEngineInputLayOut;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineIndexBuffer;
class GameEngineRasterizer;
class GameEnginePixelShader;
class GameEngineDepthStencil;
class GameEngineBlend;
class GameEngineRenderingPipeLine : public GameEngineRes<GameEngineRenderingPipeLine>
{
public:
	static GameEngineRenderingPipeLine* Create(const std::string& _Name);

public:
	// constrcuter destructer
	GameEngineRenderingPipeLine();
	~GameEngineRenderingPipeLine();

	// delete Function
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _Other) noexcept = delete;
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _Other) = delete;
	GameEngineRenderingPipeLine& operator=(GameEngineRenderingPipeLine&& _Other) noexcept = delete;

	// void SetInputAssembler1InputLayOutSetting(const std::string& _Name);

	void SetInputAssembler1VertexBuffer(const std::string& _Name);

	void SetVertexShader(const std::string& _Name);

	void SetInputAssembler2IndexBuffer(const std::string& _Name);

	void SetRasterizer(const std::string& _Name);

	void SetPixelShader(const std::string& _Name);

	void SetOutputMergerBlend(const std::string& _Name);

	void SetOutputMergerDepthStencil(const std::string& _Name);

	void Rendering();

	inline GameEngineVertexShader* GetVertexShader() 
	{
		return VertexShader;
	}

	inline GameEnginePixelShader* GetPixelShader()
	{
		return PixelShader;
	}

protected:

	
private:
	GameEngineInputLayOut* InputLayOut; // 인풋어셈블러1 세팅
	GameEngineVertexBuffer* VertexBuffer; // 인풋어셈블러1 세팅

	// HLSL이라는 다른 언어를 사용하는 단계에요.
	// HLSL은 그래픽카드에 특정 데이터에 대한 처리 단계를 우리가 직접 작성해서
	// 그래픽카드에 올려줄수 있는 겁니다.

	// 정점을 이렇게 처리해.
	GameEngineVertexShader* VertexShader; // 버텍스쉐이더 세팅

	GameEngineIndexBuffer* IndexBuffer; // 인풋어셈블러2 세팅

	D3D11_PRIMITIVE_TOPOLOGY Topology;// 인풋어셈블러2 세팅

	GameEngineRasterizer* Rasterizer; // 레스터라이저 세팅

	// 픽셀을 이렇게 처리해.
	GameEnginePixelShader* PixelShader; // 픽셀쉐이더 세팅

	GameEngineDepthStencil* DepthStencil; // 아웃풋머저 누가 앞인지 세팅 

	GameEngineBlend* Blend; // 아웃풋머저 색상통합 세팅 



	// 아웃풋 머저중 랜더타겟세팅은 이미 해놨다.
	// 디바이스의 백버퍼를 사용해서 만든 랜터타겟이 매번 세팅되고 있다.
	// 거기에 그려라.

	// 내가 세팅해준다.

	// 아래쪽 함수들의 실행
	void InputAssembler1VertexBufferSetting();

	void VertexShaderSetting();

	void InputAssembler2IndexBufferSetting();

	void RasterizerSetting();

	void PixelShaderSetting();

	void OutputMergerBlendSetting();

	void OutputMergerDepthStencilSetting();

	void Draw();

};


