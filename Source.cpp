#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>
#include <Windowsx.h>
#include "Model.h"

/*!
\brief The main window class name.*/
static TCHAR szWindowClass[] = _T("win32app");
static TCHAR szTitle[] = _T("Mironova Irina group 5441");

HINSTANCE hInst;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#define PI (double)3.1415
#define IDC_BUTTON1 10001
#define IDC_EDIT2 10002
#define IDC_EDIT3 10003
#define IDC_EDIT4 10004
#define IDC_EDIT1 10000
#define SIZE 30
int f, a;
TCHAR m1[] = _T("ћасса левого шара = "); //«аголовки перед пол€ми ввода 
TCHAR m2[] = _T("ћасса правого шара = ");
TCHAR l1[] = _T("ƒлина нитей = ");
TCHAR l2[] = _T("ѕоложение шара = ");
char massa11[100];// масса левого шара
char massa22[100];// масса правого шара
char dlina11[100];// длина левого шара
char dlina22[100];// длина правого шара
int massa1;//промежуточна€ переменна€ массы левого
int massa2;//промежуточна€ переменна€ массы правого
int dlina1;//промежуточна€ длина
int dlina2;//промежуточна€ длина
int gs = 0;
int gl = 0;
WCHAR n[30];



HWND hEdit1, hEdit2, hEdit3, hEdit4;//инициализаци€ окна

/*! \brief Declaration structures
\code
TBall ball;
TOrb orb;
TLine line;
TBalls balls;
\endcode
*/
TBall ball;
TOrb orb;
TLine line;
TBalls balls;
/*! \brief Declaration functions
\code
void DoPhysics(ULONGLONG dT);
void StartGame();
\endcode
*/
void DoPhysics(ULONGLONG dT);
void StartGame();

/*! \brief WinMain function
\return msg.wParam
*/
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			_T("Call to RegisterClassEx failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}

	hInst = hInstance;

	/*!  \brief Window creation 
	\code
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	\endcode
	*/
	HWND hWnd = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, CW_USEDEFAULT,
		800, 600,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hWnd)
	{
		MessageBox(NULL,
			_T("Call to CreateWindow failed!"),
			_T("Win32 Guided Tour"),
			NULL);

		return 1;
	}
	/*! \brief Windows creation for typing
	\code
	hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("edit"), _T(" "), WS_CHILD | WS_VISIBLE,
		150, 0, 40, 20, hWnd, (HMENU)IDC_EDIT1, hInstance, NULL);
		\endcode */
	hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("edit"), _T(" "), WS_CHILD | WS_VISIBLE,
		150, 0, 40, 20, hWnd, (HMENU)IDC_EDIT1, hInstance, NULL);
	hEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("edit"), _T(" "), WS_CHILD | WS_VISIBLE,
		160, 20, 40, 20, hWnd, (HMENU)IDC_EDIT2, hInstance, NULL);
	hEdit3 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("edit"), _T(" "), WS_CHILD | WS_VISIBLE,
		115, 40, 40, 20, hWnd, (HMENU)IDC_EDIT3, hInstance, NULL);
	hEdit4 = CreateWindowEx(WS_EX_CLIENTEDGE, _T("edit"), _T(" "), WS_CHILD | WS_VISIBLE,
		135, 60, 40, 20, hWnd, (HMENU)IDC_EDIT4, hInstance, NULL);
	CreateWindowEx(0, _T("button"), _T("START"), WS_CHILD | WS_VISIBLE,
		35, 110, 80, 25, hWnd, (HMENU)IDC_BUTTON1, hInstance, NULL);
	/*!  \brief The parameters to ShowWindow explained:
	hWnd: the value returned from CreateWindow
	nCmdShow: the fourth parameter from WinMain
		\code
		ShowWindow(hWnd,
		nCmdShow);
		UpdateWindow(hWnd);
	\endcode
	*/
	ShowWindow(hWnd,
		nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	ULONGLONG prevTime = -1, curTime, dT;

	// Enter the infinite message loop
	while (TRUE)
	{
		// Check to see if any messages are waiting in the queue
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Translate the message and dispatch it to WindowProc()
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If the message is WM_QUIT, exit the while loop
		if (msg.message == WM_QUIT)
			break;
		//расчЄт времени
		curTime = GetTickCount64();
		if (prevTime == -1)
			dT = 0;
		else dT = curTime - prevTime;
		prevTime = curTime;
		DoPhysics(dT);
		InvalidateRect(hWnd, NULL, 1);
	}

	return (int)msg.wParam;
}
/*! \brief Function StartGame
\detail  Declaration of vars */
void StartGame()

{
	orb.y = ball.y = balls.y = balls.Y = line.o;
	ball.x = line.p;
	ball.X = ball.x;
	ball.Y = ball.y;
	ball.isSelected = false;
	ball.vx = 0;
	ball.vy = 0;
	balls.X = ball.x + 2 * SIZE;
	line.Nx = balls.X;
	line.Ny = 0;

	balls.x = balls.X + 2 * SIZE;
	line.nx = balls.x;
	line.ny = 0;

	orb.x = balls.x + 2 * SIZE;
	orb.X = orb.x;
	orb.Y = orb.y;
	orb.isSelected = false;
	orb.vx = 0;
	orb.vy = 0;

	line.xj = ball.x;
	line.yj = 0;
	line.r = sqrt((ball.X - line.xj)*(ball.X - line.xj) + (ball.Y - line.yj)*(ball.Y - line.yj));

	line.Xj = orb.x;
	line.Yj = 0;
	line.R = sqrt((orb.X - line.Xj)*(orb.X - line.Xj) + (orb.Y - line.Yj)*(orb.Y - line.Yj));

}
/*! \brief Function DoPhysics
\detail
The physical description of the work processes of the pendulum */
void DoPhysics(ULONGLONG dT)
{
	/*! \brief Start work */
	if (f == 1)
	{
		double dx = balls.X - ball.X;
		double dy = balls.Y - ball.Y;
		double DX = orb.X - balls.x;
		double DY = orb.Y - balls.y;

		/*!
		
		If the ball touches the adjacent,the opposite ball begins to move . 
		\code
		if (sqrt(dx*dx + dy*dy) <= SIZE * 2)
		{
		if (line.E != 0)
		{
		line.angle1 = line.grad1;
		line.angle = line.angle1;
		line.e = line.E;
		line.E = 0;
		}
		}
		\endcode
		if the leftmost ball touches the adjacent ball and if the energy is not zero,the angle of the leftmost ball passed right fielder bowl and energy leftmost ball passed right fielder bowl
		 */

		if (sqrt(dx*dx + dy*dy) <= SIZE * 2)
		{
			if (line.E != 0)
			{
				line.angle1 = line.grad1;
				line.angle = line.angle1;
				line.e = line.E;
				line.E = 0;
			}
		}
		/*! The same for rightmost ball */

		if (sqrt(DX*DX + DY*DY) <= SIZE * 2)
		{
			if (line.e != 0)
			{

				line.grad1 = line.angle1;
				line.grad = line.grad1;
				line.E = line.e;
				line.e = 0;
			}
		}
		/*! Leftmost ball \code
		ball.a = -G*ball.m / line.r * sin(line.grad); - acceleration
		ball.vx += ball.a * ((double)dT / 100);- speed
		line.grad += (ball.vx + ((double)dT / 100) * ball.a / 2)*((double)dT / 100); - the time variation of the angle
		line.Ep = line.r *G*ball.m * (1 - cos(line.grad));- energy calculation
		if ((line.Ep) > line.E)- comparing original and modified energy in the process of motion 
		{
			line.grad = (line.grad < 0 ? (-1)*line.grad : line.grad) * acos(1 - line.E / line.r / G);-	angle change
			ball.vx = 0;
		}
		ball.a = -G*ball.m / line.r * sin(line.grad);
		ball.Y = line.r*sin(PI / 2 + line.grad);- Y movement
		ball.X = line.xj + line.r*cos(PI / 2 + line.grad);- X movement
		\endcode */
		ball.a = -G*ball.m / line.r * sin(line.grad);//acceleration
		ball.vx += ball.a * ((double)dT / 100);//speed
		line.grad += (ball.vx + ((double)dT / 100) * ball.a / 2)*((double)dT / 100);//the time variation of the angle
		line.Ep = line.r *G*ball.m * (1 - cos(line.grad));//energy calculation
		if ((line.Ep) > line.E)//comparing original and modified energy in the process of motion 
		{
			line.grad = (line.grad < 0 ? (-1)*line.grad : line.grad) * acos(1 - line.E / line.r / G);//	angle change
			ball.vx = 0;
		}
		ball.a = -G*ball.m / line.r * sin(line.grad);
		ball.Y = line.r*sin(PI / 2 + line.grad);//Y movement
		ball.X = line.xj + line.r*cos(PI / 2 + line.grad);// X movement

	 /*! The same for Rightmost ball */
		orb.a = -G*orb.m / line.R * sin(line.angle);
		orb.vx += orb.a * ((double)dT / 100);
		line.angle += (orb.vx + ((double)dT / 100) * orb.a / 2)*((double)dT / 100);
		line.ep = line.R *G*orb.m* (1 - cos(line.angle));
		if ((line.ep) > line.e)
		{
			line.angle = (line.angle < 0 ? (-1)*line.angle : line.angle) * acos(1 - line.e / line.R / G);
			orb.vx = 0;
		}

		orb.a = -G*orb.m / line.R * sin(line.angle);
		orb.Y = line.R*sin(PI / 2 - line.angle);
		orb.X = line.Xj + line.R*cos(PI / 2 - line.angle);

	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	int savedDC;
	HDC backbuffDC;
	int width, height;
	HBITMAP backbuffer;
	HBRUSH hBrush;
	double xPos, yPos;
	double XPos, YPos;
	double dx, dy;
	double DX, DY;
	HPEN hPen, hOldPen;


	switch (message)
	{
		{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			/*! \brief after pushing "Start"
			\detail Reading and recording user input variables*/

		case IDC_BUTTON1:
			switch (HIWORD(wParam))
			{
			case BN_CLICKED:
				GetWindowTextA(hEdit1, massa11, 99);
				GetWindowTextA(hEdit2, massa22, 99);
				GetWindowTextA(hEdit3, dlina11, 99);
				GetWindowTextA(hEdit4, dlina22, 99);
				sscanf(massa11, "%d", &massa1);
				ball.m = massa1;
				sscanf(massa22, "%d", &massa2);
				orb.m = massa2;
				sscanf(dlina11, "%d", &dlina1);
				line.o = dlina1;
				sscanf(dlina22, "%d", &dlina2);
				line.p = dlina2;
				StartGame();
				break;
			}
			break;
		}
		break;
		/*! Mouse LeftButton:mouse position determination
		\code
			xPos = GET_X_LPARAM(lParam);
			\endcode
			*/
	case WM_LBUTTONDOWN:
		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);
		XPos = GET_X_LPARAM(lParam);
		YPos = GET_Y_LPARAM(lParam);

		dx = xPos - ball.X;
		dy = yPos - ball.Y;
		DX = XPos - orb.X;
		DY = YPos - orb.Y;

		if (sqrt(dx*dx + dy*dy) <= SIZE)
		{
			ball.isSelected = true;

		}
		if (sqrt(DX*DX + DY*DY) <= SIZE)
		{

			orb.isSelected = true;
		}
		break;
		/*! Mouse RightButton:start working pendulum*/

	case WM_RBUTTONDOWN:
		f = 1;
		break;

		InvalidateRect(hWnd, NULL, 1);

		/*! \brief Calculation of the position coordinates provided unchanging length of the thread to the left of the ball
		\code
		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);
		double x = ball.x - line.xj;
		double X = ball.X - line.xj;
		line.mx = xPos - line.xj;
		line.my = yPos - line.yj;
		line.m = sqrt(line.mx*line.mx + line.my*line.my);
		ball.X = line.xj + (line.mx*line.r) / line.m;
		ball.Y = (line.my*line.r) / line.m;
		\endcode
		*/
	case WM_MOUSEMOVE:
		if (ball.isSelected)
		{

			xPos = GET_X_LPARAM(lParam);
			yPos = GET_Y_LPARAM(lParam);
			double x = ball.x - line.xj;
			double X = ball.X - line.xj;
			line.mx = xPos - line.xj;
			line.my = yPos - line.yj;
			line.m = sqrt(line.mx*line.mx + line.my*line.my);
			ball.X = line.xj + (line.mx*line.r) / line.m;
			ball.Y = (line.my*line.r) / line.m;


		}
		if (orb.isSelected)
		{
			XPos = GET_X_LPARAM(lParam);
			YPos = GET_Y_LPARAM(lParam);
			line.Mx = XPos - line.Xj;
			line.My = YPos - line.Yj;
			line.M = sqrt(line.Mx*line.Mx + line.My*line.My);
			orb.X = line.Xj + (line.Mx*line.R) / line.M;
			orb.Y = (line.My*line.R) / line.M;
		}

		break;
		/*! \brief Calculate the deflection angle and the initial energy to the left and right balls
		\code
		ball.cosA = ((ball.x - line.xj)*(ball.X - line.xj) + ball.y*ball.Y) / ((sqrt((ball.x - line.xj)*(ball.x - line.xj) + ball.y*ball.y))*(sqrt((ball.X - line.xj)*(ball.X - line.xj) + ball.Y*ball.Y)));
		line.grad = acos(ball.cosA);
		line.grad1 = acos(ball.cosA);
		line.E = line.r * G *ball.m* (1 - cos(line.grad));
		\endcode
		*/
	case WM_LBUTTONUP:
		ball.isSelected = false;
		orb.isSelected = false;
		ball.cosA = ((ball.x - line.xj)*(ball.X - line.xj) + ball.y*ball.Y) / ((sqrt((ball.x - line.xj)*(ball.x - line.xj) + ball.y*ball.y))*(sqrt((ball.X - line.xj)*(ball.X - line.xj) + ball.Y*ball.Y)));
		line.grad = acos(ball.cosA);
		line.grad1 = acos(ball.cosA);
		line.E = line.r * G *ball.m* (1 - cos(line.grad));

		orb.cosA = ((orb.x - line.Xj)*(orb.X - line.Xj) + orb.y*orb.Y) / ((sqrt((orb.x - line.Xj)*(orb.x - line.Xj) + orb.y*orb.y))*(sqrt((orb.X - line.Xj)*(orb.X - line.Xj) + orb.Y*orb.Y)));
		line.angle = acos(orb.cosA);
		line.angle1 = acos(orb.cosA);
		line.e = line.R * G *orb.m* (1 - cos(line.angle));

		break;
		InvalidateRect(hWnd, NULL, 1);
		break;
		/*! \brief Painting
		\detailed Double buffering
		\code
			case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);
		\endcode
		*/

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		RECT rect;
		GetClientRect(hWnd, &rect);
		width = rect.right;
		height = rect.bottom;
		backbuffDC = CreateCompatibleDC(hdc);

		backbuffer = CreateCompatibleBitmap(hdc, width, height);

		savedDC = SaveDC(backbuffDC);

		SelectObject(backbuffDC, backbuffer);

		/*! Painting of Window 
		\code
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		FillRect(backbuffDC, &rect, hBrush);
		DeleteObject(hBrush);
		\endcode
		*/
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		FillRect(backbuffDC, &rect, hBrush);
		DeleteObject(hBrush);

		/*! Creating pen
		\code
			hPen = CreatePen(PS_SOLID, 3, RGB(0, 100, 100));
		hOldPen = (HPEN)SelectObject(backbuffDC, hPen);
		\endcode
		*/
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 100, 100));
		hOldPen = (HPEN)SelectObject(backbuffDC, hPen);

		/*! Painting  threads
		\code
		MoveToEx(backbuffDC, line.xj, line.yj, NULL);
		LineTo(backbuffDC, ball.X, ball.Y);
		\endcode
		*/
		MoveToEx(backbuffDC, line.xj, line.yj, NULL);
		LineTo(backbuffDC, ball.X, ball.Y);
		MoveToEx(backbuffDC, line.Nx, line.Ny, NULL);
		LineTo(backbuffDC, balls.X, balls.Y);
		MoveToEx(backbuffDC, line.nx, line.ny, NULL);
		LineTo(backbuffDC, balls.x, balls.y);
		MoveToEx(backbuffDC, line.Xj, line.Yj, NULL);
		LineTo(backbuffDC, orb.X, orb.Y);
		SelectObject(backbuffDC, hOldPen);
		DeleteObject(hPen);
		hBrush = CreateSolidBrush(RGB(159, 156, 148));
		SelectObject(backbuffDC, hBrush);
		/*!If one of the selected ball - paint its outline in red
		\code
		if ((ball.isSelected) || (orb.isSelected))
		{
			hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		}
		\endcode
		*/
		if ((ball.isSelected) || (orb.isSelected))
		{
			hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		}
		else
		{
			hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		}

		hOldPen = (HPEN)SelectObject(backbuffDC, hPen);
		/*! Painting  balls
		\code
				Ellipse(backbuffDC, ball.X - SIZE, ball.Y - SIZE, ball.X + SIZE, ball.Y + SIZE);

				\endcode
				*/
		Ellipse(backbuffDC, ball.X - SIZE, ball.Y - SIZE, ball.X + SIZE, ball.Y + SIZE);
		Ellipse(backbuffDC, orb.X - SIZE, orb.Y - SIZE, orb.X + SIZE, orb.Y + SIZE);
		Ellipse(backbuffDC, balls.X - SIZE, balls.Y - SIZE, balls.X + SIZE, balls.Y + SIZE);
		Ellipse(backbuffDC, balls.x - SIZE, balls.y - SIZE, balls.x + SIZE, balls.y + SIZE);
		SelectObject(backbuffDC, hOldPen);
		DeleteObject(hPen);

		/*! Writing text
		\code
			wsprintf(s, _T(" %s"), m1);
		TextOut(backbuffDC, 0, 0, s, wcslen(s));
		\endcode
		*/
		WCHAR s[300];
		wsprintf(s, _T(" %s"), m1);
		TextOut(backbuffDC, 0, 0, s, wcslen(s));
		wsprintf(s, _T(" %s"), m2);
		TextOut(backbuffDC, 0, 20, s, wcslen(s));
		wsprintf(s, _T(" %s"), l1);
		TextOut(backbuffDC, 0, 40, s, wcslen(s));
		wsprintf(s, _T(" %s"), l2);
		TextOut(backbuffDC, 0, 60, s, wcslen(s));
		BitBlt(hdc, 0, 0, width, height, backbuffDC, 0, 0, SRCCOPY);
		RestoreDC(backbuffDC, savedDC);
		DeleteObject(backbuffer);
		DeleteDC(backbuffDC);

		EndPaint(hWnd, &ps);
		break;
		/*! Delete window
		\code
		case WM_ERASEBKGND:
		return 1;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		\endcode*/
	case WM_ERASEBKGND:
		return 1;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
		return 0;
		}
	}
}
