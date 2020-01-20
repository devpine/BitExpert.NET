/*
Notepad의 시스템 메뉴를 제어함. _ㅁX 제거 or 생성
*/
#include <Windows.h>
#include <tchar.h>

#define MAX_LOADSTRING 100
TCHAR szTitle[MAX_LOADSTRING] = _TEXT("First Sample");
TCHAR szWindowClass[MAX_LOADSTRING] = _TEXT("BIT");

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = DefWindowProc;
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
BOOL fun_modifyStylpe(HWND hwnd, LONG_PTR Add, LONG_PTR Remove, BOOL bRedraw)
{
	BOOL bFlag = FALSE;
	LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
	style |= Add;
	style &= ~Remove;
	bFlag = (BOOL)SetWindowLongPtr(hwnd, GWL_STYLE, style);
	if (bFlag && bRedraw)
		SetWindowPos(hwnd, 0, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_DRAWFRAME);
	return bFlag;

}
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInstance,
	LPTSTR lpszCmdParam, int nShowCmd)
{
	MyRegisterClass(hInst);
	HWND hwnd = InitInstacne(hInst, nShowCmd);
	if (hwnd == 0)
	{
		return FALSE;
	}
	//실시간 윈도우 객체 정보 수정
	HWND hWnd = FindWindow(_TEXT("Notepad"),0);
	fun_modifyStylpe(hWnd, WS_THICKFRAME, WS_SYSMENU, TRUE);
	//fun_modifyStylpe(hWnd, WS_SYSMENU, WS_THICKFRAME, TRUE);
	MessageBox(0, TEXT(""), TEXT(""), MB_OK);

	return 0;
}
