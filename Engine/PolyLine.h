#pragma once
#include <list>
#include "Direct3D.h"
#include "Texture.h"
#include <DirectXMath.h>
#include <string>
using namespace DirectX;
using namespace std;

class PolyLine
{
	//�R���X�^���g�o�b�t�@�[
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMFLOAT4	color = XMFLOAT4(1, 1, 1, 1);
	} cb;

	//���_���
	struct VERTEX
	{
		XMFLOAT3 position;
		XMFLOAT3 uv;
	};

	float width_;		//����
	int length_;		//����



	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@
	Texture* pTexture_;	//�摜


	list<XMFLOAT3> positions_;	//�ߋ�length_�񕪂̈ʒu

public:
	//�R���X�g���N�^
	PolyLine();


	//���݂̈ʒu���L��������
	//�����Fpos	���݂̈ʒu
	void AddPosition(XMFLOAT3 pos);

	//���[�h
	//�����FfileName	�摜�t�@�C����
	//�ߒl�F����/���s
	HRESULT Load(std::string fileName);

	//�`��
	void Draw();

	//���
	void Release();

	void SetColor(XMFLOAT4 color);

	XMFLOAT4 GetColor() { return cb.color; };

	void SetWidth(float w);
};

