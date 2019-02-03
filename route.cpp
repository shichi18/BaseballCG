#include <windows.h>
#include <MMSystem.h>
#include "GLMetaseq.h" // ���^�Z�R�C�A���[�_
#include "resource.h"
#include "define.h"


#pragma comment(lib, "winmm") //���p���C�u�����������N

// �ȉ��Ŏ����I�ɓ����l�q��`��
// +=�@�̑������𑝂₷�Ƒ����Ȃ�A���炷�ƒx���Ȃ�
// corner�Ƃ����̂͋Ȃ���p�B��������ɒB�����Ƃ��ɁA
// �ʂ̏����ɕύX����B

void route() {
	static int scene = 1;//��1

	static int sound_flag = 0;
	static MCI_OPEN_PARMS mop;
	
	if(sound_flag == 0){
		mop.lpstrDeviceType="WaveAudio"; // wave�`���̃t�@�C�����Đ��i���̃t�@�C���ł�������炵���j
		mop.lpstrElementName = "music/skyroad.wav"; //�Đ�����t�@�C�����i�v���O�����Ɠ����t�H���_�ɂ�������
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD) &mop); //���̏�����
	}
	


	//�{�[���𓮂����`�o�b�g�U��
	if (scene == 1) {
		mciSendCommand(mop.wDeviceID, MCI_PLAY, 0, 0); //�Đ�

		position_x1 = 50.0;		//�o�b�^�[
		position_y1 = -100;
		position_z1 = -500;
		angle_t[0] = 180;

		position_x2 = 0.0;		//�L���b�`���[
		position_y2 = -100;
		position_z2 = -550;
		angle_t[1] = -90;

		position_x3 = 0.0;		//�s�b�`���[
		position_y3 = 500;
		position_z3 = 100;

		position_x4 = 0.0;		//�{�[��
		position_y4 = -80;
		position_z4 = 0;
		angle_t[3] -= 10;

		scal_x4 = 1.0;			//�{�[���̊g��
		scal_y4 = 1.0;
		scal_z4 = 1.0;

		position_x5 = 0;		//�h�[��
		position_y5 = -500;
		position_z5 = -2300;
		angle_t[8] = 180;

		/*
		position_x6 = 50;      //��
		position_y6 = 50;
		position_z6 = 500;
		angle_t[4] = -135;
		*/

		position_x7 = 50;      	//�o�b�g�{�r
		position_y7 = -80;
		position_z7 = -500;
		angle_t[5] = -70;


		position_x8;           //�z�[�������e���b�v
		position_y8;
		position_z8;

		/*
		position_x9;			//
		position_y9;
		position_z9;

		position_x10;			//
		position_y10;
		position_z10;
		*/

		scene++;
	}
	//�ł�
	if (scene == 2) {
		position_z4 -= 10;		//�{�[��

		if (position_z4 < -450) {
			angle_t[5] += 30;	//�o�b�g�{�r
			angle_t[0] += 30;  //�o�b�^�[
		}


		if (position_z4 == -530)
			scene++;
	}

	//�ł��Ă���̃|�W�V�����ύX
	if (scene == 3) {
		position_x1 = -100;		//�o�b�^�[
		position_y1 = -100;
		position_z1 = -100;
		angle_t[0] = 90;

		position_x2 = 0;		//�L���b�`���[
		position_y2 = -120;
		position_z2 = -50;
		angle_t[1] = 90;

		position_x3 = 0;		//�s�b�`���[
		position_y3 = -100;
		position_z3 = -2000;
		angle_t[2] = -90;

		position_x4 = 0;		//�{�[��
		position_y4 = -50;
		position_z4 = -200;
		angle_t[3] = 90;

		scal_x4 = 1.0;			//�{�[���̊g��
		scal_y4 = 1.0;
		scal_z4 = 1.0;

		position_x7 = -100;		//�o�b�g+�r
		position_y7 = -1000;
		position_z7 = -100;

		position_x5 = 0;		//�h�[��
		position_y5 = -500;
		position_z5 = -500;
		angle_t[8] = 0;

		scene++;
	}
	//�o�b�^�[���_�Ń{�[�������ł����`���E���������܂�
	if (scene == 4) {
		position_x1 += 10;			//�o�b�^�[
		position_z1 -= 10;
		angle_t[0] = 30;			//�x�[�X�ɑ���

		position_z4 -= 10;
		position_y4 += 10;
		angle_t[3] -= 10;			//�{�[����]�i�ۗ��j


		if (position_y4 == 500)		//�U�����
			angle_t[2] = 90;

		if (position_y4 == 600)		//�V�[���ύX
			scene++;
	}

	//�{�[�����V��ɔ��ł���
	if (scene == 5) {

		position_x1 = -1500;		//�o�b�^�[
		position_y1 = -100;
		position_z1 = 1900;
		angle_t[0] = -45;

		position_x2 = 0;		//�L���b�`���[
		position_y2 = -100;
		position_z2 = -500;
		angle_t[1] = -90;

		position_x3 = 0;		//�s�b�`���[
		position_y3 = -130;
		position_z3 = 800;
		angle_t[2] = -90;

		position_x4 = -5;		//�{�[��
		position_y4 = 0;
		position_z4 = -5;

		scal_x4 = 0.1;			//�{�[���̊g��
		scal_y4 = 0.1;
		scal_z4 = 0.1;

		position_x5 = 0;		//�h�[��
		position_y5 = -500;
		position_z5 = -1500;
		angle_t[8] = -180;
		
		scene++;

	}

	//�V��ɓ��B����܂�
	if (scene == 6) {


		position_x5 = 0;		//�h�[���ړ�
		position_y5 -= 25;
		position_z5 -= 80;

		position_x1 += 10;		//�o�b�^�[
		position_y1 -= 25;
		position_z1 -= 70;

		position_y2 -= 25;     //�L���b�`���[
		position_z2 -= 80;

		position_y3 -= 25;//�s�b�`���[
		position_z3 -= 80;

		if (position_y5 < -2500) 
			scene++;

		}
	
	//�{�[�����o�b�N�X�N���[���Ɍ�����

	if (scene == 7) {

		position_x1 = -100;		//�o�b�^�[
		position_y1 = -5000;
		position_z1 = -100;
		angle_t[0] = 90;

		position_x2 = 0;		//�L���b�`���[
		position_y2 = -5020;
		position_z2 = -50;
		angle_t[1] = 90;

		position_x3 = 0;		//�s�b�`���[
		position_y3 = -5000;
		position_z3 = 800;

		position_x4 = -5;		//�{�[��
		position_y4 = 0;
		position_z4 = -5;

		position_x5 = 0;		//�h�[��
		position_y5 = -5000;
		position_z5 = 2500;
		angle_t[8] = 0;

		scene++;

	}

	//�o�b�N�X�N���[���Ƀ{�[��������܂�
	if (scene == 8) {
		position_x5 = 0;		//�h�[���ړ�
		position_y5 += 50;
		position_z5 += 180;

		if (position_y5 > -1500) {
			scene++;
		}
	}
	//�O�ۖڐ�����z�[���C��
	if (scene == 9) {

		position_x2 = 0.0;		//�L���b�`���[
		position_y2 = -100;
		position_z2 = -800;
		angle_t[1] = -90;

		position_x3 = -1000;		//�s�b�`���[
		position_y3 = -100;
		position_z3 = -1500;
		angle_t[2] = -50;

		position_x4 = -5;		//�{�[��
		position_y4 = -5000;
		position_z4 = -5;

		position_x5 = 0;		//�h�[��
		position_y5 = -500;
		position_z5 = -4000;
		angle_t[8] = 135;

		position_x7 = 50;      //�o�b�g
		position_y7 = -1000;
		position_z7 = -500;

		scene++;
	}

	//�����i�[������
	if (scene == 10) {
		position_z2 += 6;
		position_z3 += 25;
		position_z5 += 30;

		if (position_z5 > -330) 
			scene++;

	}
	//�s�b�`���[�ڐ��̃z�[���C��
	if (scene == 11) {

		position_x1 = 200.0;		//�o�b�^�[
		position_y1 = -100;
		position_z1 = -250;
		angle_t[0] = 90;

		position_x2 = 0.0;		//�L���b�`���[
		position_y2 = -100;
		position_z2 = -550;
		angle_t[1] = -90;

		position_x3 = 0.0;		//�s�b�`���[
		position_y3 = 500;
		position_z3 = 100;


		position_x5 = 0;		//�h�[��
		position_y5 = -500;
		position_z5 = -2300;
		angle_t[8] = 180;


		position_x7 = 50;      //�o�b�g+�r
		position_y7 = -1000;
		position_z7 = -500;
		angle_t[5] = -70;

		scene++;
	}

	//�L���b�`���[���ł���
	if (scene == 12) {
		position_x1 -= 13.0;		//�o�b�^�[
      //position_y1 = -100;
		position_z1 += -10;

		if (position_x1 < 0) {
			position_x2 -= 10.0;		//�L���b�`���[
			position_y2 += 5;
			position_z2 += 0;
			angle_t[1] += 30;
		}

		if (position_x1 < -500) 
			scene++;
	}
	
	//���X�g
	if (scene == 13) {
		position_x1 = -100;		//�o�b�^�[
		position_y1 = -100;
		position_z1 = -600;
		angle_t[0] = -90;

		position_x2 = 100;		//�L���b�`���[
		position_y2 = -100;
		position_z2 = -600;
		angle_t[1] = -90;

		position_x3 = 0;		//�s�b�`���[
		position_y3 = -100;
		position_z3 = -2000;
		angle_t[2] = -90;

		position_x5 = 0;		//�h�[��
		position_y5 = -500;
		position_z5 = -1000;
		angle_t[8] = 0;
		
		position_x8 = -400;		//�z�[�������e���b�v
		position_y8 = 300;
		position_z8 = -2000;
		//angle_t[6] += 10;
		
		//�z�[���������������Ă���
		scene++;
	}
	if (scene == 14) {
		position_y8 -= 5;
		position_z8 += 30;
	}

}


void mouse() {

}


void keyboard(int command) {


}
