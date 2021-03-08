/**
 * @file GameManager.h
 * @brief �Q�[���Ǘ�
 * @author �r�m�J �D��
 * @date 2020/02/10
 */

#pragma once

class PolygonDraw;

class GameManager
{

private:

	//�R���X�g���N�^
	GameManager();

	PolygonDraw *m_PolygonDraw;

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
