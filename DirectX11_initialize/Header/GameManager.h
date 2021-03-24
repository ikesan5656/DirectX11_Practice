/**
 * @file GameManager.h
 * @brief �Q�[���Ǘ�
 * @author �r�m�J �D��
 * @date 2020/02/10
 */

#pragma once

class PolygonDraw;
class Texture2D_Draw;

class GameManager
{

private:


	PolygonDraw *m_PolygonDraw;
	Texture2D_Draw* m_Texture2D_Draw;

public:
	//�f�X�g���N�^
	~GameManager();

	//�V���O���g���C���X�^���X�̎擾
	static GameManager* GetInstance();

	void Init();
	void Uninit();
	void Update();
	void Draw();
};
