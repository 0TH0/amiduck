#pragma once
#include <DirectXMath.h>
#include <assert.h>
#include <vector>
#include <string>
#include "Fbx.h"
#include "Transform.h"
#include "Alpha.h"

//-----------------------------------------------------------
//3D���f���iFBX�t�@�C���j���Ǘ�����
//-----------------------------------------------------------
namespace Model
{
	//���f�����
	struct ModelData
	{
		//�t�@�C����
		std::string fileName;

		//���[�h�������f���f�[�^�̃A�h���X
		Fbx*		pFbx;

		Alpha		Alpha;

		//�ǂ̃V�F�[�_���g����
		Direct3D::SHADER_TYPE  shaderType;

		//�s��
		Transform 	transform;

		//�A�j���[�V�����̃t���[��
		float nowFrame, animSpeed;
		int startFrame, endFrame;

		float uvScroll;

		//�A�E�g���C���`�悷�邩
		bool isOutLineDraw;

		//������
		ModelData() : pFbx(nullptr), nowFrame(0), startFrame(0), endFrame(0), animSpeed(0),shaderType(Direct3D::SHADER_3D),uvScroll(0),isOutLineDraw(false)
		{
		}

		//�A�j���[�V�����̃t���[�������Z�b�g
		//�����FstartFrame	�J�n�t���[��
		//�����FendFrame	�I���t���[��
		//�����FanimSpeed	�A�j���[�V�������x
		void SetAnimFrame(int start, int end, float speed)
		{
			nowFrame = (float)start;
			startFrame = start;
			endFrame = end;
			animSpeed = speed;
		}
	};


	//������
	void Initialize();

	//���f�������[�h
	//�����FfileName�@�t�@�C����
	//�ߒl�F���̃��f���f�[�^�Ɋ��蓖�Ă�ꂽ�ԍ�
	int Load(std::string fileName);

	//�`��
	//�����Fhandle	�`�悵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void Draw(int handle, FLOAT alpha = 1);

	//�C�ӂ̃��f�����J��
	//�����Fhandle	�J�����������f���̔ԍ�
	void Release(int handle);

	//�S�Ẵ��f�������
	//�i�V�[�����؂�ւ��Ƃ��͕K�����s�j
	void AllRelease();

	//�A�j���[�V�����̃t���[�������Z�b�g
	//�����Fhandle		�ݒ肵�������f���̔ԍ�
	//�����FstartFrame	�J�n�t���[��
	//�����FendFrame	�I���t���[��
	//�����FanimSpeed	�A�j���[�V�������x
	void SetAnimFrame(int handle, int startFrame, int endFrame, float animSpeed);

	//���݂̃A�j���[�V�����̃t���[�����擾
	int GetAnimFrame(int handle);

	//�C�ӂ̃{�[���̈ʒu���擾
	//�����Fhandle		���ׂ������f���̔ԍ�
	//�����FboneName	���ׂ����{�[���̖��O
	//�ߒl�F�{�[���̈ʒu�i���[���h���W�j
	XMFLOAT3 GetBonePosition(int handle, std::string boneName);

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetTransform(int handle, Transform& transform);

	XMFLOAT3 GetPosition(int handle);

	//���[���h�s��̎擾
	//�����Fhandle	�m�肽�����f���̔ԍ�
	//�ߒl�F���[���h�s��
	XMMATRIX GetMatrix(int handle);

	//���C�L���X�g�i���C���΂��ē����蔻��j�@��������
	//�����Fhandle	���肵�������f���̔ԍ�
	//�����Fdata	�K�v�Ȃ��̂��܂Ƃ߂��f�[�^
	void RayCast(int handle, RayCastData *data);

	void SetSahder(int handle, Direct3D::SHADER_TYPE shaderType = Direct3D::SHADER_3D);

	void SetUvScroll(int handle, float scroll);

	void SetOutLineDrawFlag(int handle, bool flag);

	void FlashModel(int handle, int frameMove_ = 5);

	void SetIsFlash(int handle, bool IsFlash = 1);

	void SetColor(int handle, XMFLOAT4 diffuse);
};