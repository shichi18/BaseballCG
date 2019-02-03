#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "GLMetaseq.h" // メタセコイアローダ

double mag_pos[3];// global definition for magnetic sensor

//////////////////////////////////////////////

extern GLfloat angle; 					// 角度

//　常にy軸周りに回転
//GLfloat vectorX = 0.0;					// ｘベクトル
//GLfloat vectorY = 1.0;					// ｙベクトル
//GLfloat vectorZ = 0.0;					// ｚベクトル

//////////////////////////////////////////////
/* オブジェクトの位置設定関数 */
extern double position_x, position_y, position_z;

void InitGL();
void MaterialCreate();
void LightCreate();
void DispModel();
void LoadmqoModel();

void InitGL(){
	mqoInit();
	glClearColor(0.3f, 0.3f, 0.3f, 0.3f);  
	LightCreate();
	glEnable(GL_TEXTURE_2D);
	LoadmqoModel();



	MaterialCreate();

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	 glFrontFace(GL_CW);
	// glCullFace(GL_BACK);  // default
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_FLAT);
}

void Display(void)
{
	double offset = 0.0;
	double zNear = 0.2;
	double zFar = 1000000.0;
	double P = 8.0;
	double W = 300.0;
	double H = 225.0;
	double D = 160.0;

	//立体ディスプレイ用パラメータ
	GLdouble k = 0.5 * zNear / D;
	GLdouble f = P * k;
	GLdouble w = W * k;
	GLdouble h = H * k;

	/****************************************************************************************************************/
	// Draw the image for the left eye.
	/****************************************************************************************************************/
	glDrawBuffer(GL_BACK_LEFT);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Setup the projection for the left eye
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	//立体ディスプレイ用設定
	glFrustum(-w+f, w+f, -h, h, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(P * 0.5 + offset, 0.0, 0.0);
//	glTranslated(P * 0.5 + offset, 0.0, -D);

	DispModel();

	/****************************************************************************************************************/
	// Draw the image for the right eye.
	/****************************************************************************************************************/
	glDrawBuffer(GL_BACK_RIGHT);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//立体ディスプレイ用設定
	glFrustum(-w-f, w-f, -h, h, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(P * 0.5 + offset, 0.0, 0.0);
//	glTranslated(P * 0.5 + offset, 0.0, -D);
	DispModel();
}


void MaterialCreate(void)
{
GLfloat ambientGold[]  = {0.1f, 0.05f, 0.0f, 1.0f};
GLfloat diffuseGold[]  = {0.65f, 0.55f, 0.15f, 1.0f};
GLfloat specularGold[] = {0.85f, 0.75f, 0.45f, 1.0f};

GLfloat ambientSilver[]  = {0.1f, 0.1f, 0.1f, 1.0f};
GLfloat diffuseSilver[]  = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat specularSilver[] = {0.9f, 0.9f, 0.9f, 1.0f};

GLfloat shininess = 100.0f;

glMaterialfv(GL_FRONT, GL_AMBIENT, ambientGold);
glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseGold);
glMaterialfv(GL_FRONT, GL_SPECULAR, specularGold);
glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}


// Create directional light（環境の光の色の設定）
void LightCreate(void) 
{
GLfloat light0_ambient[]  = {1.0f, 1.0f, 1.0f, 1.0f}; //環境光　Red Green Blue 透明度
GLfloat light0_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f}; //散乱反射光
GLfloat light0_specular[] = {1.0f, 1.0f, 1.0f, 1.0f}; //鏡面反射光
GLfloat light0_position[] = {-5.0f, 5.0f, 5.0f, 1.0f};

GLfloat light1_ambient[]  = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat light1_diffuse[]  = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat light1_specular[] = {0.5f, 0.5f, 0.5f, 1.0f};
GLfloat light1_position[] = {5.0f, 0.0f, 0.0f, 1.0f};

glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

glLightfv(GL_LIGHT1, GL_AMBIENT, light0_ambient);
glLightfv(GL_LIGHT1, GL_DIFFUSE, light0_diffuse);
glLightfv(GL_LIGHT1, GL_SPECULAR, light0_specular);
glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

glEnable(GL_LIGHTING);

glEnable(GL_LIGHT0);
glEnable(GL_LIGHT1);
}

void EndMeta(){
		mqoCleanup();
}