#define _CRT_SECURE_NO_DEPRECATE

#include "define.h"
#include <math.h>

//�X�^�[�g�ʒu���W�ݒ�


GLfloat angle_t[100];

double position_x1; //�o�b�^�[
double position_y1;
double position_z1;

double position_x2; //�L���b�`���[
double position_y2;
double position_z2;

double position_x3;//�L���b�`���[
double position_y3;
double position_z3;

double position_x4; //�{�[��
double position_y4;
double position_z4;

double scal_x4 = 1.0; //�{�[���̊g��
double scal_y4 = 1.0;
double scal_z4 = 1.0;

double position_x5; //�h�[��
double position_y5;
double position_z5;

double position_x6; //��
double position_y6;
double position_z6;

double position_x7; //�΂���
double position_y7;
double position_z7;

double position_x8;  //�z�[�������e���b�v
double position_y8;
double position_z8;

double position_x9;  //
double position_y9;
double position_z9;

double position_x10;  //
double position_y10;
double position_z10;

GLfloat vectorX, vectorY, vectorZ;
MQO_MODEL	g_mqoModel[100];		// MQO���f��

void LoadmqoModel(){
		/****************************************************************************************************************/
	/* �\������I�u�W�F�N�g�̓ǂݍ��� */
	g_mqoModel[2] = mqoCreateModel("meta_data/dra_yellow_batter.mqo",1.0);//�o�b�^�[
	g_mqoModel[3] = mqoCreateModel("meta_data/dra_red_catch.mqo", 1.0);//�L���b�`���[
	g_mqoModel[4] = mqoCreateModel("meta_data/pawapuro_tousyu.mqo", 1.0);//�s�b�`���[
	g_mqoModel[5] = mqoCreateModel("meta_data/ball.mqo", 0.05);//�{�[��
	g_mqoModel[6] = mqoCreateModel("meta_data/meta/doom.mqo", 1);//�h�[��
	g_mqoModel[8] = mqoCreateModel("meta_data/bat.mqo", 0.05);//�o�b�g�{�r
	g_mqoModel[9] = mqoCreateModel("meta_data/homerun.mqo", 0.3);//�z�[�������e���b�v

		/****************************************************************************************************************/
}


void DispModel(){

	//��]�E�ړ��̊�{�@�������Ɍ������ēK�p�����
	//PushMatrix�`PopMatrix�̊Ԃɏ����ꂽ���̂͂��̒��ł����K�p�����

	//angle ����� position�Ȃǂ̕ϐ��̒l��route.cpp�̒��ŕω�������
	//����ɂ��A���Ԃ����Ə��X�Ɉړ�����B

	/* �I�u�W�F�N�g�ʒu�̐ݒ� */
	static float angle2 = 0.0;

	static double eye[3] = {0.0, 0.0, 0.0};
	static double eye_d[3] = {0.0 ,0.0, -1.0};
//	gluLookAt(eye[0], eye[1], eye[2], eye_d[0], eye_d[1], eye_d[2],0,1,0);	//���_�ʒu�̈ړ� �ڂ̈ʒu�� eye �ڂ̌����Ă�������� eye_d

	static double theta;

	//�����ʒu�E������ς������ꍇ�̃T���v��
	//eye[2]+=5.0;	//�ڂ̈ʒu��z������5���ړ�

	//�@�����̕ύX
	// �@eye_d[2] = eye[2] + cos(theta);
	//	eye_d[0] = eye[0] + sin(theta);
	//theta += 0.01;

	glPushMatrix();
	
		glPushMatrix();

	//glTranslated(position_x, position_y, position_z);	//�ړ�2
	//glRotated(angle, 0, 1, 0);		//��]2�@y����]
	//angle += 1.0;
	//MQO���f���̃R�[��
	//mqoCallModel(g_mqoModel[0]); //�^�`�R�}�@��]2���s������A�ړ�2�A�ړ�0
	//PushMatrix�`PopMatrix�ň͂܂ꂽ���ł̈ړ���]�i��]1����шړ�1�j�͍s���Ȃ�
		glPopMatrix();///////
	


	
				 
	//�o�b�^�[
	glPushMatrix();

	glTranslated(position_x1, position_y1, position_z1);
	glRotated(angle_t[0], 0, 1, 0);		
	
	mqoCallModel(g_mqoModel[2]); 

	glPopMatrix();


	//�L���b�`���[
	glPushMatrix();

	glTranslated(position_x2, position_y2, position_z2);	
	glRotated(angle_t[1], 0, 1, 0);		
	

	mqoCallModel(g_mqoModel[3]); 

	glPopMatrix();

	//�s�b�`���[	
	glPushMatrix();

	glTranslated(position_x3, position_y3, position_z3);
	glRotated(angle_t[2], 0, 1, 0);
	mqoCallModel(g_mqoModel[4]);

	glPopMatrix();
	
	//�{�[��
	glPushMatrix();

	glTranslated(position_x4, position_y4, position_z4);	
	glRotated(angle_t[3], 0, 1, 0);
	glScaled(scal_x4, scal_y4, scal_z4);
	mqoCallModel(g_mqoModel[5]); 

	glPopMatrix();

	//�h�[��
	glPushMatrix();
	glTranslated(position_x5, position_y5, position_z5);
	glRotated(angle_t[8], 0, 1, 0);
	glRotated(angle_t[9], 1, 0, 0);
	mqoCallModel(g_mqoModel[6]);


	glPopMatrix();
	
	//��
	glPushMatrix();
	glTranslated(position_x6, position_y6, position_z6);
	glRotated(angle_t[4], 0, 1, 0);
	mqoCallModel(g_mqoModel[7]);
	glPopMatrix();

	//�o�b�g�{�r
	glPushMatrix();
	glTranslated(position_x7, position_y7, position_z7);
	glRotated(angle_t[5], 0, 1, 0);
	mqoCallModel(g_mqoModel[8]);
	glPopMatrix();

	//�z�[�������e���b�v
	glPushMatrix();
	glTranslated(position_x8, position_y8, position_z8);
	glRotated(angle_t[6], 0, 1, 0);
	mqoCallModel(g_mqoModel[9]);
	glPopMatrix();

	//
	glPushMatrix();
	glTranslated(position_x9, position_y9, position_z9);
	glRotated(angle_t[7], 0, 1, 0);
	
	mqoCallModel(g_mqoModel[10]);
	glPopMatrix();

	


	glPopMatrix();
}