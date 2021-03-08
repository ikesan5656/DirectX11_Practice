/**
 * @file DX11ShaderManager.h
 * @brief �V�F�[�_�[�Ǘ�
 * @author �r�m�J �D��
 * @date 2020/02/08
 */

#pragma once
#include"DirectX11Manager.h"
#include <string>

//std�̋@�\������I�Ɏg����悤�ɂ��A�O���[�o����Ԃ��r�炳�Ȃ����@
//std��string�^
using std::string;

//�V�F�[�_�Ǘ�ID
enum class ShaderID : int
{
	VS = 0,	//���_�V�F�[�_
	PS,		//�s�N�Z���V�F�[�_

	MAX,	//�ő吔
};

 /**
 * @brief DX11�V�F�[�_�[�̊Ǘ��N���X
 * @details ���̂Ƃ���1�������݂��Ȃ����̂Ȃ̂ŃV���O���g��
 */
class DX11ShaderManager
{

private:

	//�R���X�g���N�^
	DX11ShaderManager();

	//�V�F�[�_���ۑ�
	string filename[(int)ShaderID::MAX];

public:

	//�f�X�g���N�^
	~DX11ShaderManager();
 
	//���_�V�F�[�_�쐬
	ID3D11VertexShader* CreateVertexShader(const string& filename, const string& entrypath = "", bool erorr = true);
	//�s�N�Z���V�F�[�_�쐬
	ID3D11PixelShader* CreatePixelShader(const string& filename, const string& entrypath = "", bool erorr = true);
	//inputlayout�쐬
	ID3D11InputLayout* CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elem_num, const string& filename, const string& entrypath = "");

	/*�p�C�v���C���̃Z�b�g*/
	void SetInputLayout(ID3D11InputLayout* VertexLayout);
	void SetVertexShader(ID3D11VertexShader* vs);
	void SetPixelShader(ID3D11PixelShader* ps);

	//�V���O���g���C���X�^���X�̎擾
	static DX11ShaderManager* GetInstance();
};