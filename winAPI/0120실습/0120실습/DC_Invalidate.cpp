#include <Windows.h>
#include <tchar.h>

#define MAX_LOADSTRING 100
#define WM_MYMESSAGE WM_USER+100

TCHAR szTitle[MAX_LOADSTRING] = _TEXT("Hello"); // 제목 표시줄
TCHAR szWindowClass[MAX_LOADSTRING] = _TEXT("Hello"); //기본 창 클래스

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_LBUTTONDOWN: // 사각형을 그림
	{
		HDC hdc = GetDC(hwnd);
		Rectangle(hdc, 120, 10, 210, 100);
		ReleaseDC(hwnd, hdc);
	}
		return 0;
	case WM_RBUTTONDOWN: // 사각형을 지움
	{
		RECT r = { 120,10,210,100 };
		InvalidateRect(hwnd, &r, TRUE);
	}
	return 0;
	/*
	BeginPaint
	-DC를 만들고 UpdateRegion을 DC의 Cliping 영역으로 지정
	-무효화 영역을 지우기 위해 WM_ERASEBKGND 메시지 전송
	-PAINTSTRUCT 구조체를 채움
	-Caret이 있을 경우 그리기 전에 Hide하고 EndPaint()에서 Show한다.
	-무효화 영역을 유효화 한다.
	*/
	case WM_PAINT: 
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		Rectangle(hdc, 10, 10, 100, 100);
		EndPaint(hwnd, &ps);
	}
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