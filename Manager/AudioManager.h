#pragma once

/// <summary>
/// �l�X�ȉ����Ǘ�����
/// </summary>
namespace AudioManager
{
	//������
	void Initialize();

	//�V�[���J�ڂ̎��̏�����
	void SceneTransitionInitialize();

	//�N���b�N��
	void ClickAudio();
	
	//�q�b�g��
	void HitAudio();

	//�v���CBGM
	void PlayBGM();

	//�^�C�g��BGM
	void TitleBGM();

	//��������
	void WinAudio();

	//��������
	void LoseAudio();

	//�W�����v��
	void JumpAudio();

	//���̉�
	void SmokeAudio();

	//���̉�
	void StarAudio();

	//�v���CBGM�X�g�b�v
	void StopPlayBGM();

	//�^�C�g��BGM
	void StopTitleBGM();
}