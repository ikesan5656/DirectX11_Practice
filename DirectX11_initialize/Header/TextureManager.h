#pragma once

/*
DirectX11�Ŏg�p����e�N�X�`���[���Ǘ�����N���X
�V���O���g���N���X�Ƃ��ė��p
*/
#include <d3d11.h>

class TextureManager
{
private:
public:

	~TextureManager();//�V���O���g���̂��߁A�R���X�g���N�^�͂Ȃ�
	//�V���O���g���C���X�^���X�̎擾
	static TextureManager * GetInstance();
	//�摜�t�@�C����ǂݍ���ŕԂ�
	ID3D11ShaderResourceView* CreateTextureFromFile(const wchar_t* filename, ID3D11Device * device);

};