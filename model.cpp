#define _CRT_SECURE_NO_DEPRECATE

#include "define.h"
#include <math.h>

//スタート位置座標設定


GLfloat angle_t[100];

double position_x1; //バッター
double position_y1;
double position_z1;

double position_x2; //キャッチャー
double position_y2;
double position_z2;

double position_x3;//キャッチャー
double position_y3;
double position_z3;

double position_x4; //ボール
double position_y4;
double position_z4;

double scal_x4 = 1.0; //ボールの拡大
double scal_y4 = 1.0;
double scal_z4 = 1.0;

double position_x5; //ドーム
double position_y5;
double position_z5;

double position_x6; //顔
double position_y6;
double position_z6;

double position_x7; //ばっと
double position_y7;
double position_z7;

double position_x8;  //ホームランテロップ
double position_y8;
double position_z8;

double position_x9;  //
double position_y9;
double position_z9;

double position_x10;  //
double position_y10;
double position_z10;

GLfloat vectorX, vectorY, vectorZ;
MQO_MODEL	g_mqoModel[100];		// MQOモデル

void LoadmqoModel(){
		/****************************************************************************************************************/
	/* 表示するオブジェクトの読み込み */
	g_mqoModel[2] = mqoCreateModel("meta_data/dra_yellow_batter.mqo",1.0);//バッター
	g_mqoModel[3] = mqoCreateModel("meta_data/dra_red_catch.mqo", 1.0);//キャッチャー
	g_mqoModel[4] = mqoCreateModel("meta_data/pawapuro_tousyu.mqo", 1.0);//ピッチャー
	g_mqoModel[5] = mqoCreateModel("meta_data/ball.mqo", 0.05);//ボール
	g_mqoModel[6] = mqoCreateModel("meta_data/meta/doom.mqo", 1);//ドーム
	g_mqoModel[8] = mqoCreateModel("meta_data/bat.mqo", 0.05);//バット＋腕
	g_mqoModel[9] = mqoCreateModel("meta_data/homerun.mqo", 0.3);//ホームランテロップ

		/****************************************************************************************************************/
}


void DispModel(){

	//回転・移動の基本　下から上に向かって適用される
	//PushMatrix～PopMatrixの間に書かれたものはその中でだけ適用される

	//angle および positionなどの変数の値はroute.cppの中で変化させる
	//それにより、時間がたつと徐々に移動する。

	/* オブジェクト位置の設定 */
	static float angle2 = 0.0;

	static double eye[3] = {0.0, 0.0, 0.0};
	static double eye_d[3] = {0.0 ,0.0, -1.0};
//	gluLookAt(eye[0], eye[1], eye[2], eye_d[0], eye_d[1], eye_d[2],0,1,0);	//視点位置の移動 目の位置は eye 目の向いている方向は eye_d

	static double theta;

	//視線位置・方向を変えたい場合のサンプル
	//eye[2]+=5.0;	//目の位置をz方向に5ずつ移動

	//　方向の変更
	// 　eye_d[2] = eye[2] + cos(theta);
	//	eye_d[0] = eye[0] + sin(theta);
	//theta += 0.01;

	glPushMatrix();
	
		glPushMatrix();

	//glTranslated(position_x, position_y, position_z);	//移動2
	//glRotated(angle, 0, 1, 0);		//回転2　y軸回転
	//angle += 1.0;
	//MQOモデルのコール
	//mqoCallModel(g_mqoModel[0]); //タチコマ　回転2を行った後、移動2、移動0
	//PushMatrix～PopMatrixで囲まれた中での移動回転（回転1および移動1）は行われない
		glPopMatrix();///////
	


	
				 
	//バッター
	glPushMatrix();

	glTranslated(position_x1, position_y1, position_z1);
	glRotated(angle_t[0], 0, 1, 0);		
	
	mqoCallModel(g_mqoModel[2]); 

	glPopMatrix();


	//キャッチャー
	glPushMatrix();

	glTranslated(position_x2, position_y2, position_z2);	
	glRotated(angle_t[1], 0, 1, 0);		
	

	mqoCallModel(g_mqoModel[3]); 

	glPopMatrix();

	//ピッチャー	
	glPushMatrix();

	glTranslated(position_x3, position_y3, position_z3);
	glRotated(angle_t[2], 0, 1, 0);
	mqoCallModel(g_mqoModel[4]);

	glPopMatrix();
	
	//ボール
	glPushMatrix();

	glTranslated(position_x4, position_y4, position_z4);	
	glRotated(angle_t[3], 0, 1, 0);
	glScaled(scal_x4, scal_y4, scal_z4);
	mqoCallModel(g_mqoModel[5]); 

	glPopMatrix();

	//ドーム
	glPushMatrix();
	glTranslated(position_x5, position_y5, position_z5);
	glRotated(angle_t[8], 0, 1, 0);
	glRotated(angle_t[9], 1, 0, 0);
	mqoCallModel(g_mqoModel[6]);


	glPopMatrix();
	
	//顔
	glPushMatrix();
	glTranslated(position_x6, position_y6, position_z6);
	glRotated(angle_t[4], 0, 1, 0);
	mqoCallModel(g_mqoModel[7]);
	glPopMatrix();

	//バット＋腕
	glPushMatrix();
	glTranslated(position_x7, position_y7, position_z7);
	glRotated(angle_t[5], 0, 1, 0);
	mqoCallModel(g_mqoModel[8]);
	glPopMatrix();

	//ホームランテロップ
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