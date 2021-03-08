/**
 * @file GameManager.h
 * @brief ゲーム管理
 * @author 池ノ谷 優太
 * @date 2020/02/10
 */

#pragma once

class PolygonDraw;

class GameManager
{

private:

	//コンストラクタ
	GameManager();

	PolygonDraw *m_PolygonDraw;

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
