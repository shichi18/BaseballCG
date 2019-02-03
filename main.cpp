/* ##### INCLUDES 	*/
#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "resource.h"

#include "define.h"

/****************************************************************************************************************/
/* マウスのドラッグ操作に使用する関数 */
double dragAngleX = 0.0;			// ドラッグ開始位置での回転角
double dragAngleY = 0.0;			// ドラッグ開始位置での回転角
//////////////////////////////////////////////////////
//GLfloat angle;

/* 視点方向設定関数 */
double VectorX = 1.0;
double VectorY = 1.0;

/* マウス移動量に使用する関数 */
double offsetX = 0.0;
double offsetY = 0.0;

const double Bias_trans = 5.0;
//const double Bias_rotate = 100.0;


void route();
void keyboard(int);

/****************************************************************************************************************/

/* ##### VARIABLES */

char szAppName[]  = "Stereo View";
char szAppTitle[] = "Stereo View";  

HINSTANCE hInstMain;
HACCEL    hAccel;

static HDC   hdc   = NULL;
static HGLRC hglrc = NULL;

char szMessage[2048];
char szInfo[256];

GLboolean bStereo = GL_FALSE;

BOOL bLButtonDown = FALSE;
BOOL bRButtonDown = FALSE;

BOOL bRotation = TRUE; 

int nWidth;
int nHeight;
float aspectViewport = 1.0f;

POINT ptLast;
POINT ptCurrent;

double length = 20.0;

UINT      uiTimer = 0;
GLfloat   angleX = 0.0f;
GLfloat   angleY = 0.0f;
GLfloat   angleZ = 0.0f;
GLfloat   translateZ = 0.0f;
GLfloat   incZ = 0.005f;



/* #################### PROTOTYPES 	*/

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

void Init(void);
void Reshape(int width, int height);
void Display(void);
void Lists(void);
void InitGL(void);
void EndMeta(void);

void CommandHandler(HWND hwnd, int command);


/* #################### FUNCTIONS 	*/

int CALLBACK WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;

	if (!hPrevInstance)
	{
		/* Other instances of app running? */
		if (!InitApplication(hInstance))
		{
			/* Initialize shared things */
			return (FALSE);     /* Exits if unable to initialize */
		}
	}
	/* Perform initializations that apply to a specific instance */
	if (!InitInstance(hInstance, nCmdShow))
	{
		return (FALSE);
	}
	hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	/* Acquire and dispatch messages until a WM_QUIT message is received. */
	while (GetMessage(&msg,     /* message structure */
		NULL,     /* handle of window receiving the message */
		0,        /* lowest message to examine */
		0))       /* highest message to examine */
	{
		if (!TranslateAccelerator(msg.hwnd, hAccel, &msg))
		{
			TranslateMessage(&msg);   /* Translates virtual key codes */
			DispatchMessage(&msg);    /* Dispatches message to window */
		}
	}
	return (msg.wParam);    /* Returns the value from PostQuitMessage */
}


BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASS  wc;
	/*	Fill in window class structure with parameters that describe the
	main window.*/
	wc.style         = CS_HREDRAW | CS_VREDRAW;       /* Class style(s). */
	wc.lpfnWndProc   = (WNDPROC) WndProc;             /* Window Procedure */
	wc.cbClsExtra    = 0;                             /* No per-class extra data. */
	wc.cbWndExtra    = 0;                             /* No per-window extra data. */
	wc.hInstance     = hInstance;                     /* Owner of this class */
	wc.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2)); /* Icon */
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);   /* Cursor */
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);   /* Default color */
	wc.lpszMenuName  = NULL; // MAKEINTRESOURCE(IDR_MENU1);    /* No Menu */
	wc.lpszClassName = szAppName;                     /* Name to register as */
	/* Register the window class and return success/failure code. */
	return (RegisterClass(&wc));
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND  hwnd;   /* Main window handle. */
	/* Save the instance handle in static variable, which will be used in */
	/* many subsequence calls from this application to Windows. */
	hInstMain = hInstance; /* Store instance handle in our global variable */
	/* Create a main window for this application instance. */
	hwnd = CreateWindow(szAppName,            /* See RegisterClass() call.   */
		szAppTitle,           /* Text for window title bar.  */
//		WS_POPUP | WS_MAXIMIZE, /* Window style.     */
		WS_OVERLAPPEDWINDOW | WS_MAXIMIZE,
		CW_USEDEFAULT ,
		0,
		CW_USEDEFAULT,
		0,
		NULL,                 /* Overlapped windows have no parent.     */
		NULL,                 /* Use the window class menu.             */
		hInstance,            /* This instance owns this window.        */
		NULL);                /* We don't use any data in our WM_CREATE */

	/* If window could not be created, return "failure" */
	if (!hwnd)
	{
		return (FALSE);
	}

	/* Make the window visible; update its client area; and return "success" */
	//ShowWindow(hwnd, nCmdShow); /* Show the window */
	//  ShowWindow(hwnd, SW_HIDE); /* Show the window */
	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);         /* Sends WM_PAINT message */

	return (TRUE);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	PIXELFORMATDESCRIPTOR pfd;
	int                   iPixelFormat;

	switch (uMessage)
	{
	case WM_CREATE:
		ShowCursor(FALSE);		// Hide mouse cursor


		hdc = GetDC(hwnd);
		pfd.nSize           = sizeof(PIXELFORMATDESCRIPTOR); 
		pfd.nVersion        = 1; 
		pfd.dwFlags         = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER 
#ifndef HOLLYWOOD_SQUARES
			| PFD_STEREO
#endif
			;
		pfd.iPixelType      = PFD_TYPE_RGBA; 
		pfd.cColorBits      = 24; 
		pfd.cRedBits        = 0; 
		pfd.cRedShift       = 0; 
		pfd.cGreenBits      = 0; 
		pfd.cGreenShift     = 0; 
		pfd.cBlueBits       = 0; 
		pfd.cBlueShift      = 0; 
		pfd.cAlphaBits      = 0;
		pfd.cAlphaShift     = 0; 
		pfd.cAccumBits      = 0; 
		pfd.cAccumRedBits   = 0; 
		pfd.cAccumGreenBits = 0; 
		pfd.cAccumBlueBits  = 0; 
		pfd.cAccumAlphaBits = 0; 
		pfd.cDepthBits      = 24; 
		pfd.cStencilBits    = 0; 
		pfd.cAuxBuffers     = 0; 
		pfd.iLayerType      = PFD_MAIN_PLANE;
		pfd.bReserved       = 0; 
		pfd.dwLayerMask     = 0;
		pfd.dwVisibleMask   = 0; 
		pfd.dwDamageMask    = 0;

		iPixelFormat = ChoosePixelFormat(hdc, &pfd);

		if (iPixelFormat != 0)
		{
			// get the actual settings of the pixelformat if they should be evaluated further.
			// DescribePixelformat(hdc, iPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
			// e.g. look if the PFD_STEREO bit is really set!

			if (SetPixelFormat(hdc, iPixelFormat, &pfd))
			{
				hglrc = wglCreateContext(hdc);
				if (hglrc != NULL)
				{
					if (wglMakeCurrent(hdc, hglrc))
					{
						/* ======================================================================== */
						// OPENGL DRIVER QUERY START
						wsprintf(szMessage,  // one '\n' removed by Akka, extensions string removed too
							"Current OpenGL Driver:\n%s\n%s\n%s\n",
							glGetString(GL_VENDOR),
							glGetString(GL_RENDERER),
							glGetString(GL_VERSION)
							//                       glGetString(GL_EXTENSIONS)
							);
						glGetBooleanv(GL_STEREO, &bStereo); // query stereo support!
						if (!bStereo)
						{
							strcat(szMessage, "\nGL_STEREO equals GL_FALSE\n");  // text changed by akka
						}
						else
						{
							strcat(szMessage, "\nGL_STEREO equals GL_TRUE\n");   // text changed by akka
						}

						// logic changed around eliminating 'else' block by Akka
						if (strstr(szMessage, "ELSA") == NULL)
						{
							// Messages changed by Akka
							//              strcat(szMessage, "\nAttention! No ELSA OpenGL driver running!\n");
							//                strcat(szMessage, "\nNo Elsa driver is currently active\n");

						} 
						MessageBox(GetFocus(), szMessage, szAppTitle, MB_SYSTEMMODAL | MB_OK | MB_ICONEXCLAMATION);

						// OPENGL DRIVER QUERY END
						/* ======================================================================== */
						// OPENGL INITIALIZATION
						InitGL();
						// wglMakeCurrent(hdc, NULL);
					}
					else
					{
						wsprintf(szMessage, "wglMakeCurrent returned FALSE.\nGetlastError() == %ld\n", GetLastError());
						MessageBox(GetFocus(), szMessage, szAppTitle, MB_SYSTEMMODAL | MB_OK | MB_ICONSTOP);
					}
				}
				else
				{
					wsprintf(szMessage, "wglCreateContext returned NULL.\nGetlastError() == %ld\n", GetLastError());
					MessageBox(GetFocus(), szMessage, szAppTitle, MB_SYSTEMMODAL | MB_OK | MB_ICONSTOP);
				}
			}
			else
			{
				wsprintf(szMessage, "SetPixelFormat returned FALSE.\nGetlastError() == %ld\n", GetLastError());
				MessageBox(GetFocus(), szMessage, szAppTitle, MB_SYSTEMMODAL | MB_OK | MB_ICONSTOP);
			}
		}
		else
		{
			wsprintf(szMessage, "ChoosePixelFormat returned 0.\nGetlastError() == %ld\n", GetLastError());
			MessageBox(GetFocus(), szMessage, szAppTitle, MB_SYSTEMMODAL | MB_OK | MB_ICONSTOP);
		}
		uiTimer = SetTimer(hwnd, 1, 40, NULL);
		return 0;

	case WM_ERASEBKGND:
		// Important! Prevents GDI from clearing the window client area.
		return 1;

	case WM_SIZE:
		nWidth  = LOWORD(lParam); // width of client area 
		nHeight = HIWORD(lParam); // height of client area 
		glViewport(0, 0, nWidth, nHeight);
		if (nHeight > 0)
		{
			aspectViewport = (float) nWidth / (float) nHeight;
		}
		else
		{
			aspectViewport = 1.0f;
		}
		return 0;

	case WM_PAINT:
		// New method with static HDC doesn't make use of BeginPaint()-EndPaint()
		// (This would have been very bad style under Windows 3.1
		//  where only 5 HDC were available at a time.)
		Display();
		SwapBuffers(hdc);
		ValidateRect(hwnd, NULL); // Validate the update region of the whole window.
		return 0;

	case WM_LBUTTONDOWN:
		bLButtonDown = TRUE;
		ptLast.x = (long) ((signed short) (lParam & 0xFFFF));
		ptLast.y = (long) lParam >> 16;
		SetCapture(hwnd);
		return 0;

	case WM_RBUTTONDOWN:
		bRButtonDown = TRUE;
		return 0;

	case WM_LBUTTONUP:
		bLButtonDown = FALSE;
		ptLast = ptCurrent;
		ReleaseCapture();
		return 0;

	case WM_RBUTTONUP:
		bRButtonDown = FALSE;
		return 0;

	case WM_MOUSEMOVE: //マウスが移動したときに実行される．
		
		//現在のマウスポインタの位置（2次元）
		ptCurrent.x = (long) ((signed short) (lParam & 0xFFFF)); 
		ptCurrent.y = (long) lParam >> 16;

		//前回のマウス位置との差でどの方向に移動・回転させるか決める	
		offsetX = -ptLast.x + ptCurrent.x;
		offsetY = ptLast.y - ptCurrent.y;

		if (bLButtonDown)
		{			
			InvalidateRect(hwnd, NULL, FALSE);
			ptLast = ptCurrent;
			//position_x += offsetX/Bias_trans;
			//position_z += offsetY/Bias_trans;
			offsetX = 0;
			offsetY = 0;
		}

		if (bRButtonDown){
			/*
			if(offsetX > 0.0)
				angle += 2.0;
			else
				angle -= 2.0;
				*/
			InvalidateRect(hwnd, NULL, FALSE);
			ptLast = ptCurrent;
		}
		return 0;

	case WM_TIMER:
		route();

	case WM_COMMAND:
		{
			int command;

			command = LOWORD(wParam);
			if (command == IDCANCEL)
			{
				PostMessage(hwnd, WM_DESTROY, 0, 0L);
			}
			else
			{
				CommandHandler(hwnd, command);
			}
			InvalidateRect(hwnd, NULL, FALSE);
		}
		return 0;

	case WM_DESTROY:  /* message: window being destroyed */
		if (hglrc != NULL)
		{
			if (hdc != NULL)
			{
				/* ======================================================================== */
				// OPENGL DE-INITIALIZATION START

				// Delete DisplayLists etc. here
				glDeleteLists(1, 1);
				// OPENGL DE-INITIALIZATION END
				/* ======================================================================== */
				wglMakeCurrent(hdc, NULL);
				ReleaseDC(hwnd, hdc);
			}
			wglDeleteContext(hglrc);
		}
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, uMessage, wParam, lParam));
}


void CommandHandler(HWND hwnd, int command) //キーボード操作の設定
{
	keyboard(command);

	switch (command)
	{
	case CMD_KEY_1:
		glEnable(GL_CULL_FACE);
		break;

	case CMD_KEY_2:
		glDisable(GL_CULL_FACE);
		break;

	case CMD_KEY_RETURN:
		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case CMD_KEY_ESCAPE:
		EndMeta();
		PostMessage(hwnd, WM_DESTROY, 0, 0L);
		break;

	case CMD_KEY_q:
		EndMeta();
		exit(0);
		break;

	case CMD_KEY_SPACE:
		bRotation = !bRotation;
		break;
	}
}