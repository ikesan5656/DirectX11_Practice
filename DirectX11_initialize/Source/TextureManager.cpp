#include "TextureManager.h"
#include <locale.h>
#include <DirectXMath.h>
#include <DirectXTex.h>
#include<iostream>
//DirectXMathがDirectXのネームスペースにある
using namespace DirectX;
DirectX::TexMetadata metadata;

TextureManager::~TextureManager()
{
}

TextureManager * TextureManager::GetInstance()
{
	static TextureManager self;
	//自身を返す
	return &self;
}

ID3D11ShaderResourceView* TextureManager::CreateTextureFromFile(const wchar_t* filename, ID3D11Device * device)
{
	ID3D11ShaderResourceView* ShaderResView;

	char ms[100];
	setlocale(LC_CTYPE, "jpn");
	//wcstombs(ms, filename, 100);
	char* extension = strstr(ms, ".");

	if (extension == NULL)
		return nullptr;

	if (strcmp(extension, ".tga") == 0 || strcmp(extension, ".TGA") == 0) {
		TexMetadata meta;
		GetMetadataFromTGAFile(filename, meta);

		std::unique_ptr<ScratchImage> image(new ScratchImage);
		HRESULT hr = LoadFromTGAFile(filename, &meta, *image);
		if (FAILED(hr))
			return nullptr;
		hr = CreateShaderResourceView(device, image->GetImages(), image->GetImageCount(), meta, &ShaderResView);
		if (FAILED(hr))
			return nullptr;
		return ShaderResView;
	}
	else
	{
		TexMetadata meta;
		GetMetadataFromWICFile(filename, WIC_FLAGS::WIC_FLAGS_NONE, meta);

		std::unique_ptr<ScratchImage> image(new ScratchImage);
		HRESULT hr = LoadFromWICFile(filename, WIC_FLAGS::WIC_FLAGS_NONE, &meta, *image);
		if (FAILED(hr))
			return nullptr;
		hr = CreateShaderResourceView(device, image->GetImages(), image->GetImageCount(), meta, &ShaderResView);
		if (FAILED(hr))
			return nullptr;
		return ShaderResView;
	}
}