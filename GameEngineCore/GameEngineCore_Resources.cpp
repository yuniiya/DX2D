#include "PreCompile.h"
#include "GameEngineCore.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineLevel.h"
#include "GameEngineVertexs.h"
#include "GameEngineConstantBuffer.h"
#include <math.h>


// Resources Header
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineFolderTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineDepthStencilTexture.h"
#include "GameEngineDepthStencil.h"
#include "GameEngineFont.h"

#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRasterizer.h"
#include "GameEngineBlend.h"
#include "GameEngineRenderingPipeLine.h"

void EngineInputLayOut() 
{
	// 점 1개
	// float4 Postion0
	// float4 Postion1
	// float4 Postion2
	// float4 Postion3
	// float4 Postion4
	// float4 Postion5
	// float4 Postion6

	GameEngineVertex::LayOut.AddInputLayOut("POSITION", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT); // 16
	GameEngineVertex::LayOut.AddInputLayOut("TEXCOORD", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT); // 32
	GameEngineVertex::LayOut.AddInputLayOut("COLOR", DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT); // 48
}

void EngineSubSetting()
{
	{
		D3D11_BLEND_DESC Desc = { 0 };

		// 낮
		Desc.AlphaToCoverageEnable = FALSE;
		Desc.IndependentBlendEnable = FALSE;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		//         배경색

		//           src                                         dest
		// 색깔공식  float4(1.0f, 0.0f, 0.0f, 0.5f) * 소스팩터 + float4(0.0f, 0.0f, 1.0f, 0.5f) * 원본팩터

		//        = float4(1.0f, 0.0f, 1.0f, 1.0f);
		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		// 색깔공식  float4(0.0f, 0.0f, 0.0f, 0.0f) * float4(0.0f, 0.0f, 0.0f) + float4(0.0f, 0.0f, 1.0f, 1.0f) * 원본팩터
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		// float4(0.0f, 0.0f, 1.0f, 1.0f)* (0.5f, 0.5f, 0.5f)
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

		// 알파쪽만 따로 처리하는 옵션
		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;


		GameEngineBlend::Create("AlphaBlend", Desc);
	}

	{
		D3D11_RASTERIZER_DESC Desc = {};

		Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

		// 
		Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		GameEngineRasterizer::Create("EngineRasterizer", Desc);
	}
	{
		D3D11_DEPTH_STENCIL_DESC Desc = {0};

		Desc.DepthEnable = true;
		Desc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		Desc.StencilEnable = false;
		GameEngineDepthStencil::Create("EngineBaseDepth", Desc);

		
	}
	
}

void EngineTextureLoad() 
{
	{
		D3D11_SAMPLER_DESC Desc = {D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT};
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("EngineSamplerPoint", Desc);
	}

	{
		D3D11_SAMPLER_DESC Desc = { D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR };
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		Desc.MipLODBias = 0.0f;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MinLOD = -FLT_MAX;
		Desc.MaxLOD = FLT_MAX;

		GameEngineSampler::Create("EngineSamplerLinear", Desc);
	}

	GameEngineDirectory Dir;

	Dir.MoveParentToExitsChildDirectory("GameEngineResources");
	Dir.Move("GameEngineResources");
	Dir.Move("Texture");

	std::vector<GameEngineFile> Shaders = Dir.GetAllFile();

	for (size_t i = 0; i < Shaders.size(); i++)
	{
		GameEngineTexture::Load(Shaders[i].GetFullPath());
	}
}

void ShaderCompile()
{
	GameEngineDirectory Dir;

	Dir.MoveParentToExitsChildDirectory("GameEngineResources");
	Dir.Move("GameEngineResources");
	Dir.Move("GameEngineShader");

	std::vector<GameEngineFile> Shaders = Dir.GetAllFile("hlsl");

	for (size_t i = 0; i < Shaders.size(); i++)
	{
		GameEngineShader::AutoCompile(Shaders[i].GetFullPath());
	}
}



void EngineRenderingPipeLine()
{
	{
		GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("Color");
		NewPipe->SetVertexShader("Color.hlsl");
		NewPipe->SetPixelShader("Color.hlsl");
	}

	{
		GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("Texture");
		NewPipe->SetVertexShader("Texture.hlsl");
		NewPipe->SetPixelShader("Texture.hlsl");
	}

	{
		GameEngineRenderingPipeLine* NewPipe = GameEngineRenderingPipeLine::Create("TextureAtlas");
		NewPipe->SetVertexShader("TextureAtlas.hlsl");
		NewPipe->SetPixelShader("TextureAtlas.hlsl");
	}
}

void EngineMesh() 
{

	{
		std::vector<GameEngineVertex> Vertex;
		Vertex.push_back({ float4(-0.5f, 0.5f), float4(0.0f, 0.0f)}); // 왼쪽 위
		Vertex.push_back({ float4(0.5f, 0.5f), float4(1.0f, 0.0f)});  // 오른쪽 위점
		Vertex.push_back({ float4(0.5f, -0.5f), float4(1.0f, 1.0f) }); // 오른쪽 아래점
		Vertex.push_back({ float4(-0.5f, -0.5f), float4(0.0f, 1.0f) }); // 왼쪽 아래점
		GameEngineVertexBuffer::Create("Rect", Vertex);
	}


	{
		std::vector<int> Index;

		// 첫번째 삼각형
		// 디폴트 생성자로 인자를 뒤에 추가해주는 요소 추가 함수.
		Index.resize(6);

		// 첫번째
		Index[0] = 0;
		Index[1] = 1;
		Index[2] = 2;

		// 두번째
		Index[3] = 0;
		Index[4] = 2;
		Index[5] = 3;

		GameEngineIndexBuffer::Create("Rect", Index);
	}

	{
		std::vector<GameEngineVertex> Vertex;
		Vertex.resize(24);
		// 앞면
		Vertex[0] = { float4(-0.5f, 0.5f, 0.5f) };
		Vertex[1] = { float4(0.5f, 0.5f, 0.5f) };
		Vertex[2] = { float4(0.5f, -0.5f, 0.5f) };
		Vertex[3] = { float4(-0.5f, -0.5f, 0.5f) };

		// 뒷면
		Vertex[4] = {float4::VectorRotationToDegreeXAxis(Vertex[0].POSITION, 180.f)};
		Vertex[5] = {float4::VectorRotationToDegreeXAxis(Vertex[1].POSITION, 180.f)};
		Vertex[6] = {float4::VectorRotationToDegreeXAxis(Vertex[2].POSITION, 180.f)};
		Vertex[7] = {float4::VectorRotationToDegreeXAxis(Vertex[3].POSITION, 180.f)};

		// 왼쪽
		Vertex[8] = {float4::VectorRotationToDegreeYAxis(Vertex[0].POSITION, -90.f) };
		Vertex[9] = {float4::VectorRotationToDegreeYAxis(Vertex[1].POSITION, -90.f) };
		Vertex[11] = { float4::VectorRotationToDegreeYAxis(Vertex[3].POSITION, -90.f) };
		Vertex[10] ={ float4::VectorRotationToDegreeYAxis(Vertex[2].POSITION, -90.f) };

		// 오른쪽
		Vertex[12] = {float4::VectorRotationToDegreeYAxis(Vertex[0].POSITION, 90.f)};
		Vertex[13] = {float4::VectorRotationToDegreeYAxis(Vertex[1].POSITION, 90.f)};
		Vertex[14] = {float4::VectorRotationToDegreeYAxis(Vertex[2].POSITION, 90.f)};
		Vertex[15] = {float4::VectorRotationToDegreeYAxis(Vertex[3].POSITION, 90.f)};

		// 위
		Vertex[16] = {float4::VectorRotationToDegreeXAxis(Vertex[0].POSITION, -90.f)};
		Vertex[17] = {float4::VectorRotationToDegreeXAxis(Vertex[1].POSITION, -90.f)};
		Vertex[18] = {float4::VectorRotationToDegreeXAxis(Vertex[2].POSITION, -90.f)};
		Vertex[19] = { float4::VectorRotationToDegreeXAxis(Vertex[3].POSITION, -90.f) };

		// 아래
		Vertex[20] = {float4::VectorRotationToDegreeXAxis(Vertex[0].POSITION, 90.f)};
		Vertex[21] = {float4::VectorRotationToDegreeXAxis(Vertex[1].POSITION, 90.f)};
		Vertex[22] = {float4::VectorRotationToDegreeXAxis(Vertex[2].POSITION, 90.f)};
		Vertex[23] = { float4::VectorRotationToDegreeXAxis(Vertex[3].POSITION, 90.f) };


		GameEngineVertexBuffer::Create("Box", Vertex);
	}

	{
		std::vector<int> Index;
		Index.resize(36);
		for (int i = 0; i < 6; i++)
		{
			Index[0 + i * 6] = 0 + 4 * i;
			Index[1 + i * 6] = 1 + 4 * i;
			Index[2 + i * 6] = 2 + 4 * i;
			Index[3 + i * 6] = 0 + 4 * i;
			Index[4 + i * 6] = 2 + 4 * i;
			Index[5 + i * 6] = 3 + 4 * i;
		}

		GameEngineIndexBuffer::Create("Box", Index);
	}

	GameEngineFont::Load("돋움");
}

void GameEngineCore::EngineResourcesInitialize()
{
	// 사각형 박스 에러용 텍스처 등등
	// 엔진수준에서 기본적으로 지원줘야 한다고 생각하는
	// 리소스들을 이니셜라이즈하는 단계
	EngineTextureLoad();
	EngineInputLayOut();
	EngineMesh();
	EngineSubSetting();
	ShaderCompile();

	EngineRenderingPipeLine();

	// 쉐이더 로드

}


void GameEngineCore::EngineResourcesDestroy()
{
	GameEngineRenderingPipeLine::ResourcesDestroy();

	GameEnginePixelShader::ResourcesDestroy();
	GameEngineVertexShader::ResourcesDestroy();

	GameEngineVertexBuffer::ResourcesDestroy();
	GameEngineIndexBuffer::ResourcesDestroy();
	GameEngineRenderTarget::ResourcesDestroy();
	GameEngineTexture::ResourcesDestroy();
	GameEngineDepthStencil::ResourcesDestroy();
	GameEngineDepthStencilTexture::ResourcesDestroy();
	GameEngineFolderTexture::ResourcesDestroy();
	GameEngineSampler::ResourcesDestroy();
	GameEngineRasterizer::ResourcesDestroy();
	GameEngineBlend::ResourcesDestroy();
	GameEngineConstantBuffer::ResourcesDestroy();
	GameEngineSound::ResourcesDestroy();
	GameEngineFont::ResourcesDestroy();

	GameEngineDevice::Destroy();
}