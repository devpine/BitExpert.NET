/*
0120실습2 프로젝트의 sendMsg.cpp 파일과 사용
recvMsg실행 -> sendMsg 실행 
sendMsg에서 정수 10, 20을 넘겨줌
recvMsg에서 받아와서 처리
*/

#include <Windows.h>
#include <tchar.h>

#define MAX_LOADSTRING 100
#define WM_MYMESSAGE WM_USER+100

TCHAR szTitle[MAX_LOADSTRING] = _TEXT("Hello"); // 제목 표시줄
TCHAR szWindowClass[MAX_LOADSTRING] = _TEXT("Hello"); //기본 창 클래스

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_MYMESSAGE:
	{
		TCHAR buf[20];
		wsprintf(buf, TEXT("%d+%d=%d"), wParam, lParam, wParam + lParam);
		MessageBox(hwnd, buf, TEXT(""), MB_OK);
		return wParam + lParam;
	}
	case WM_LBUTTONDOWN:
		SendMessage(hwnd, WM_MYMESSAGE, 10, 20);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
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