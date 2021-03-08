/**
 * @file DX11ShaderManager.h
 * @brief シェーダー管理
 * @author 池ノ谷 優太
 * @date 2020/02/08
 */

#pragma once
#include"DirectX11Manager.h"
#include <string>

//stdの機能を限定的に使えるようにし、グローバル空間を荒らさない方法
//stdのstring型
using std::string;

//シェーダ管理ID
enum class ShaderID : int
{
	VS = 0,	//頂点シェーダ
	PS,		//ピクセルシェーダ

	MAX,	//最大数
};

 /**
 * @brief DX11シェーダーの管理クラス
 * @details 今のところ1つしか存在しないものなのでシングルトン
 */
class DX11ShaderManager
{

private:

	//コンストラクタ
	DX11ShaderManager();

	//シェーダ名保存
	string filename[(int)ShaderID::MAX];

public:

	//デストラクタ
	~DX11ShaderManager();
 
	//頂点シェーダ作成
	ID3D11VertexShader* CreateVertexShader(const string& filename, const string& entrypath = "", bool erorr = true);
	//ピクセルシェーダ作成
	ID3D11PixelShader* CreatePixelShader(const string& filename, const string& entrypath = "", bool erorr = true);
	//inputlayout作成
	ID3D11InputLayout* CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elem_num, const string& filename, const string& entrypath = "");

	/*パイプラインのセット*/
	void SetInputLayout(ID3D11InputLayout* VertexLayout);
	void SetVertexShader(ID3D11VertexShader* vs);
	void SetPixelShader(ID3D11PixelShader* ps);

	//シングルトンインスタンスの取得
	static DX11ShaderManager* GetInstance();
};