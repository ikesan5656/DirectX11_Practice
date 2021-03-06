/**
 * @file GameManager.h
 * @brief ゲーム管理
 * @author 池ノ谷 優太
 * @date 2020/02/10
 */

#pragma once

class PolygonDraw;
class Texture2D_Draw;
class Polygon3D;
class MeshField;

class GameManager
{

private:


	PolygonDraw *m_PolygonDraw;
	Texture2D_Draw* m_Texture2D_Draw;
	Polygon3D* m_Polygon3D;
	MeshField* m_MeshField;

public:
	//デストラクタ
	~GameManager();

	//シングルトンインスタンスの取得
	static GameManager* GetInstance();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};
