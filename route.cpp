#include <windows.h>
#include <MMSystem.h>
#include "GLMetaseq.h" // メタセコイアローダ
#include "resource.h"
#include "define.h"


#pragma comment(lib, "winmm") //音用ライブラリをリンク

// 以下で自動的に動く様子を描く
// +=　の増減幅を増やすと速くなり、減らすと遅くなる
// cornerというのは曲がり角。ある条件に達したときに、
// 別の条件に変更する。

void route() {
	static int scene = 1;//仮1

	static int sound_flag = 0;
	static MCI_OPEN_PARMS mop;
	
	if(sound_flag == 0){
		mop.lpstrDeviceType="WaveAudio"; // wave形式のファイルを再生（他のファイルでもいけるらしい）
		mop.lpstrElementName = "music/skyroad.wav"; //再生するファイル名（プログラムと同じフォルダにおくこと
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD) &mop); //音の初期化
	}
	


	//ボールを動かす～バット振る
	if (scene == 1) {
		mciSendCommand(mop.wDeviceID, MCI_PLAY, 0, 0); //再生

		position_x1 = 50.0;		//バッター
		position_y1 = -100;
		position_z1 = -500;
		angle_t[0] = 180;

		position_x2 = 0.0;		//キャッチャー
		position_y2 = -100;
		position_z2 = -550;
		angle_t[1] = -90;

		position_x3 = 0.0;		//ピッチャー
		position_y3 = 500;
		position_z3 = 100;

		position_x4 = 0.0;		//ボール
		position_y4 = -80;
		position_z4 = 0;
		angle_t[3] -= 10;

		scal_x4 = 1.0;			//ボールの拡大
		scal_y4 = 1.0;
		scal_z4 = 1.0;

		position_x5 = 0;		//ドーム
		position_y5 = -500;
		position_z5 = -2300;
		angle_t[8] = 180;

		/*
		position_x6 = 50;      //顔
		position_y6 = 50;
		position_z6 = 500;
		angle_t[4] = -135;
		*/

		position_x7 = 50;      	//バット＋腕
		position_y7 = -80;
		position_z7 = -500;
		angle_t[5] = -70;


		position_x8;           //ホームランテロップ
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
	//打つ
	if (scene == 2) {
		position_z4 -= 10;		//ボール

		if (position_z4 < -450) {
			angle_t[5] += 30;	//バット＋腕
			angle_t[0] += 30;  //バッター
		}


		if (position_z4 == -530)
			scene++;
	}

	//打ってからのポジション変更
	if (scene == 3) {
		position_x1 = -100;		//バッター
		position_y1 = -100;
		position_z1 = -100;
		angle_t[0] = 90;

		position_x2 = 0;		//キャッチャー
		position_y2 = -120;
		position_z2 = -50;
		angle_t[1] = 90;

		position_x3 = 0;		//ピッチャー
		position_y3 = -100;
		position_z3 = -2000;
		angle_t[2] = -90;

		position_x4 = 0;		//ボール
		position_y4 = -50;
		position_z4 = -200;
		angle_t[3] = 90;

		scal_x4 = 1.0;			//ボールの拡大
		scal_y4 = 1.0;
		scal_z4 = 1.0;

		position_x7 = -100;		//バット+腕
		position_y7 = -1000;
		position_z7 = -100;

		position_x5 = 0;		//ドーム
		position_y5 = -500;
		position_z5 = -500;
		angle_t[8] = 0;

		scene++;
	}
	//バッター視点でボールが飛んでいく～視界から消えるまで
	if (scene == 4) {
		position_x1 += 10;			//バッター
		position_z1 -= 10;
		angle_t[0] = 30;			//ベースに走る

		position_z4 -= 10;
		position_y4 += 10;
		angle_t[3] -= 10;			//ボール回転（保留）


		if (position_y4 == 500)		//振り向く
			angle_t[2] = 90;

		if (position_y4 == 600)		//シーン変更
			scene++;
	}

	//ボールが天井に飛んでいく
	if (scene == 5) {

		position_x1 = -1500;		//バッター
		position_y1 = -100;
		position_z1 = 1900;
		angle_t[0] = -45;

		position_x2 = 0;		//キャッチャー
		position_y2 = -100;
		position_z2 = -500;
		angle_t[1] = -90;

		position_x3 = 0;		//ピッチャー
		position_y3 = -130;
		position_z3 = 800;
		angle_t[2] = -90;

		position_x4 = -5;		//ボール
		position_y4 = 0;
		position_z4 = -5;

		scal_x4 = 0.1;			//ボールの拡大
		scal_y4 = 0.1;
		scal_z4 = 0.1;

		position_x5 = 0;		//ドーム
		position_y5 = -500;
		position_z5 = -1500;
		angle_t[8] = -180;
		
		scene++;

	}

	//天井に到達するまで
	if (scene == 6) {


		position_x5 = 0;		//ドーム移動
		position_y5 -= 25;
		position_z5 -= 80;

		position_x1 += 10;		//バッター
		position_y1 -= 25;
		position_z1 -= 70;

		position_y2 -= 25;     //キャッチャー
		position_z2 -= 80;

		position_y3 -= 25;//ピッチャー
		position_z3 -= 80;

		if (position_y5 < -2500) 
			scene++;

		}
	
	//ボールがバックスクリーンに向かう

	if (scene == 7) {

		position_x1 = -100;		//バッター
		position_y1 = -5000;
		position_z1 = -100;
		angle_t[0] = 90;

		position_x2 = 0;		//キャッチャー
		position_y2 = -5020;
		position_z2 = -50;
		angle_t[1] = 90;

		position_x3 = 0;		//ピッチャー
		position_y3 = -5000;
		position_z3 = 800;

		position_x4 = -5;		//ボール
		position_y4 = 0;
		position_z4 = -5;

		position_x5 = 0;		//ドーム
		position_y5 = -5000;
		position_z5 = 2500;
		angle_t[8] = 0;

		scene++;

	}

	//バックスクリーンにボールが入るまで
	if (scene == 8) {
		position_x5 = 0;		//ドーム移動
		position_y5 += 50;
		position_z5 += 180;

		if (position_y5 > -1500) {
			scene++;
		}
	}
	//三塁目線からホームイン
	if (scene == 9) {

		position_x2 = 0.0;		//キャッチャー
		position_y2 = -100;
		position_z2 = -800;
		angle_t[1] = -90;

		position_x3 = -1000;		//ピッチャー
		position_y3 = -100;
		position_z3 = -1500;
		angle_t[2] = -50;

		position_x4 = -5;		//ボール
		position_y4 = -5000;
		position_z4 = -5;

		position_x5 = 0;		//ドーム
		position_y5 = -500;
		position_z5 = -4000;
		angle_t[8] = 135;

		position_x7 = 50;      //バット
		position_y7 = -1000;
		position_z7 = -500;

		scene++;
	}

	//ランナーが動く
	if (scene == 10) {
		position_z2 += 6;
		position_z3 += 25;
		position_z5 += 30;

		if (position_z5 > -330) 
			scene++;

	}
	//ピッチャー目線のホームイン
	if (scene == 11) {

		position_x1 = 200.0;		//バッター
		position_y1 = -100;
		position_z1 = -250;
		angle_t[0] = 90;

		position_x2 = 0.0;		//キャッチャー
		position_y2 = -100;
		position_z2 = -550;
		angle_t[1] = -90;

		position_x3 = 0.0;		//ピッチャー
		position_y3 = 500;
		position_z3 = 100;


		position_x5 = 0;		//ドーム
		position_y5 = -500;
		position_z5 = -2300;
		angle_t[8] = 180;


		position_x7 = 50;      //バット+腕
		position_y7 = -1000;
		position_z7 = -500;
		angle_t[5] = -70;

		scene++;
	}

	//キャッチャー飛んでいく
	if (scene == 12) {
		position_x1 -= 13.0;		//バッター
      //position_y1 = -100;
		position_z1 += -10;

		if (position_x1 < 0) {
			position_x2 -= 10.0;		//キャッチャー
			position_y2 += 5;
			position_z2 += 0;
			angle_t[1] += 30;
		}

		if (position_x1 < -500) 
			scene++;
	}
	
	//ラスト
	if (scene == 13) {
		position_x1 = -100;		//バッター
		position_y1 = -100;
		position_z1 = -600;
		angle_t[0] = -90;

		position_x2 = 100;		//キャッチャー
		position_y2 = -100;
		position_z2 = -600;
		angle_t[1] = -90;

		position_x3 = 0;		//ピッチャー
		position_y3 = -100;
		position_z3 = -2000;
		angle_t[2] = -90;

		position_x5 = 0;		//ドーム
		position_y5 = -500;
		position_z5 = -1000;
		angle_t[8] = 0;
		
		position_x8 = -400;		//ホームランテロップ
		position_y8 = 300;
		position_z8 = -2000;
		//angle_t[6] += 10;
		
		//ホームランが向かってくる
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
