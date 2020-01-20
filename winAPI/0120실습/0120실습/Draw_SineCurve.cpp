/*
창의 좌표값을 따와 사인 곡선을 그려준다. = 창의 크기에 따라 유동적
*/

#include <Windows.h>
#include <tchar.h>
#include <math.h>
#define NUM 1000
#define TWOPI (2 * 3.14159)
#define MAX_LOADSTRING 100
#define WM_MYMESSAGE WM_USER+100

TCHAR szTitle[MAX_LOADSTRING] = _TEXT("Hello"); // 제목 표시줄
TCHAR szWindowClass[MAX_LOADSTRING] = _TEXT("Hello"); //기본 창 클래스

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int cxClient, cyClient;
	HDC hdc;
	int i;
	PAINTSTRUCT ps;
	POINT apt[NUM];
	switch (message) {
	case WM_SIZE:
		cxClient = LOWORD(lParam);//창의 가로값을 받아옴
		cyClient = HIWORD(lParam);//창의 세로값을 받아옴
		InvalidateRect(hwnd, NULL, TRUE);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		MoveToEx(hdc, 0, cyClient / 2, NULL);// 창의 세로높이의 절반만큼, 가로길이의 0에서부터
		LineTo(hdc, cxClient, cyClient / 2); // 선을 그려줌
		for (i = 0; i < NUM; i++)
		{
			apt[i].x = i * cxClient / NUM; //x 좌표값 저장
			apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI*i / NUM))); //y좌표값 저장
		}
		Polyline(hdc, apt, NUM);//다각선을 표현해줌
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc; // 만들어준 WndProc를 넣어줌
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = 0;
	return RegisterClassEx(&wcex);
}

HWND InitInstacne(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd) {
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev,
	LPTSTR lpCmdLine, int nShowCmd)
{
	MyRegisterClass(hInst);
	HWND hwnd = InitInstacne(hInst, nShowCmd);
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}