#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineRes.h"

#include "../GameEngineCore/ThirdParty/inc/DirectXTex.h"

#pragma comment(lib, "DirectXTex.lib")

// 설명 : 
class GameEngineTexture : public GameEngineRes<GameEngineTexture>
{
public:
	GameEngineTexture();
	~GameEngineTexture();

	// delete Function
	GameEngineTexture(const GameEngineTexture& _Other) = delete;
	GameEngineTexture(GameEngineTexture&& _Other) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture& _Other) = delete;
	GameEngineTexture& operator=(GameEngineTexture&& _Other) noexcept = delete;

	static GameEngineTexture* Load(const std::string& _Path) 
	{
		return Load(_Path, GameEnginePath::GetFileName(_Path));
	}

	static GameEngineTexture* Load(const std::string& _Path, const std::string& _Name);

	// static
	static GameEngineTexture* Create(const std::string& _Name, ID3D11Texture2D* _Texture);
	static GameEngineTexture* Create(ID3D11Texture2D* _Texture);

	// static void Cut("Boss_Left.bmp", 5, 7);
	static void Cut(const std::string& _Name, UINT _X, UINT _Y);

	// Member
	ID3D11RenderTargetView* CreateRenderTargetView();

	void VSSetting(int _BindPoint);
	void PSSetting(int _BindPoint);

	float4 GetFrameData(UINT _Index) 
	{
		if (true == CutData.empty())
		{
			MsgBoxAssertString(GetNameCopy() + " 자르지 않은 텍스처를 사용하려고 했습니다.");
		}

		if (CutData.size() <= _Index)
		{
			MsgBoxAssertString(GetNameCopy() + " 프레임 범위를 초과했습니다.");
		}

		return CutData[_Index];
	}

	void TextureLoad(const std::string& _Path);

	float4 GetScale() 
	{
		return { static_cast<float>(Metadata.width), static_cast<float>(Metadata.height) };
	}

	void TextureCreate(const D3D11_TEXTURE2D_DESC& _Desc);

protected:

private:
	ID3D11Texture2D* Texture2D;
	ID3D11RenderTargetView* RenderTargetView;
	ID3D11ShaderResourceView* ShaderResourceView;

	DirectX::TexMetadata Metadata;
	DirectX::ScratchImage Image;

	D3D11_TEXTURE2D_DESC Desc;
	// 이녀석은 텍스처를 통해서 
	// ID3D11RenderTargetView* Render;

	std::vector<float4> CutData;

	void Cut(UINT _X, UINT _Y);
};

