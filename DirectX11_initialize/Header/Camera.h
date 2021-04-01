#pragma once
#include <DirectXMath.h>
using namespace DirectX;

/**
* @brief カメラクラス
* @details DX11で使用するカメラを管理するクラス
*/

/*
定数バッファはそれぞれのオブジェクトクラスで作成、セットする
*/

class Camera 
{

	private:
		//世界の行列
		XMMATRIX m_worldMatrix;
		//カメラの位置
		XMVECTOR m_eye;
		//カメラの注視点の位置
		XMVECTOR m_focus;
		//ワールド座標の上向きのベクトル
		XMVECTOR m_up;
		//ビューマトリクス
		XMMATRIX m_viewMatrix;

		float m_fov;
		float m_aspect;
		float m_nearZ;
		float m_farZ;
		//プロジェクションマトリクス
		XMMATRIX m_projMatrix;

	public:
		//シングルトンインスタンスの取得
		static Camera* GetInstance();
		void Init();
		void Uninit();
		void Update();
		void Draw();

		//ここから下はゲッター
		XMMATRIX GetWorldMatrix();
		XMMATRIX GetViewMatrix();
		XMMATRIX GetProjMatrix();


};