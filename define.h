#include "GLMetaseq.h" // メタセコイアローダ

// route.cpp の中で使用する位置座標
// route.cppの中で値を変更し、model.cppで変更された値で描画するという流れ。

extern double position_x1, position_y1, position_z1;
extern double position_x2, position_y2, position_z2;
extern double position_x3, position_y3, position_z3;
extern double position_x4, position_y4, position_z4;
extern double position_x5, position_y5, position_z5;
extern double position_x6, position_y6, position_z6;
extern double position_x7, position_y7, position_z7;
extern double position_x8, position_y8, position_z8;
extern double position_x9, position_y9, position_z9;
extern double position_x10, position_y10, position_z10;


extern double scal_x4, scal_y4, scal_z4;
// route.cpp の中で使用する角度
// 上記と同様、route.cppの中で値を変更し、model.cppで変更された値で描画するという流れ。
extern GLfloat angle_t[100];

extern GLfloat vectorX, vectorY, vectorZ;

//メタセコイアで作成したモデルを保存する構造体　
extern MQO_MODEL	g_mqoModel[100];		// MQOモデル