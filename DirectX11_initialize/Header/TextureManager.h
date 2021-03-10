#pragma once

/*
DirectX11で使用するテクスチャーを管理するクラス
シングルトンクラスとして利用
*/
#include <d3d11.h>

class TextureManager
{
private:
public:

	~TextureManager();//シングルトンのため、コンストラクタはなし
	//シングルトンインスタンスの取得
	static TextureManager * GetInstance();
	//画像ファイルを読み込んで返す
	ID3D11ShaderResourceView* CreateTextureFromFile(const wchar_t* filename, ID3D11Device * device);

};