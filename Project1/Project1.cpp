// Project1.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Project1.h"
#include "windowsx.h"

#define MAX_COUNT 1000

int g_is_clicked = 0;
int g_x[MAX_COUNT] = { 0, }, g_y[MAX_COUNT] = { 0, };
int g_count = 0;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_DESTROY) PostQuitMessage(0);
	else if (uMsg == WM_PAINT) {
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);

		if(g_count > 0)	MoveToEx(h_dc, g_x[0], g_y[0], NULL);		// MoveTo의 중복호출을 막는다.
		for (int i = 1; i < g_count; i++) {
			LineTo(h_dc, g_x[i], g_y[i]);
		}

		EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_LBUTTONDOWN) {
		g_is_clicked = 1;
		g_x[g_count] = GET_X_LPARAM(lParam);//
		g_y[g_count] = GET_Y_LPARAM(lParam);
		g_count++;

	}
	else if (uMsg == WM_LBUTTONUP) {
		g_is_clicked = 0;
	}
	else if (uMsg == WM_MOUSEMOVE) {
		if (g_is_clicked == 1 && g_count <= MAX_COUNT) {

			HDC h_dc = GetDC(hWnd);

			MoveToEx(h_dc, g_x[g_count-1], g_y[g_count-1], NULL);
			g_x[g_count] = GET_X_LPARAM(lParam);//
			g_y[g_count] = GET_Y_LPARAM(lParam);
			LineTo(h_dc, g_x[g_count], g_y[g_count]);
			g_count++;


			ReleaseDC(hWnd, h_dc);
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"tipssoft";
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"www.tipssoft.com",
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}