#include <Windows.h>
#include <tchar.h>
#include "resource.h"
void PrintTime(const SYSTEMTIME* pst, HDC hdc, int y)
{
	TCHAR date[256] = { 0 };
	TCHAR time[256] = { 0 };
	GetDateFormat(LOCALE_USER_DEFAULT, 0, pst, TEXT("yyyy년 M월d일"), date, 256);
	GetTimeFormat(LOCALE_USER_DEFAULT, 0, pst, TEXT("tt h시 m분 s초"), time, 256);
	TextOut(hdc, 10, y + 10, date, wcslen(date));
	TextOut(hdc, 10, y + 30, time, wcslen(time));
}

BOOL PrintFileTime(HANDLE hFile, HDC hdc)
{
	FILETIME ftCreate, ftAccess, ftWrite;//생성,접근,변경시간을 담을 FILETIME
	SYSTEMTIME stUTCCreate, stLocalCreate, stUTCAccess, stLocalAccess, stUTCWrite, stLocalWrite;
	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite)) return FALSE;
	FileTimeToSystemTime(&ftWrite, &stUTCCreate);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTCCreate, &stLocalCreate);
	FileTimeToSystemTime(&ftAccess, &stUTCAccess);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTCAccess, &stLocalAccess);
	FileTimeToSystemTime(&ftWrite, &stUTCWrite);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTCWrite, &stLocalWrite);
	//Creation Time
	PrintTime(&stLocalCreate, hdc, 0);
	//Last-Access Time :
	PrintTime(&stLocalAccess, hdc, 50);
	//"Last-Write Time :
	PrintTime(&stLocalWrite, hdc, 100);
	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	TCHAR temp[128];

	switch (msg) {
	case WM_LBUTTONDOWN:
	{
		HANDLE hFile = CreateFile(TEXT("C:\\Windows\\system32\\calc.exe"),
			GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL, 0);
		HDC hdc = GetDC(hwnd);
		PrintFileTime(hFile, hdc);
		ReleaseDC(hwnd, hdc);
	}
	return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hwnd, msg, wParam, lParam));
}
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev,
	LPTSTR lpCmdLine, int nShowCmd)
{
	//1. 윈도우 클래스 만들기
	WNDCLASS wc;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
	wc.hInstance = hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("First");
	wc.lpszMenuName = 0;
	wc.style = 0;

	//2. 등록(레지스트리에)
	RegisterClass(&wc);

	//3. 윈도우 창 만들기
	HWND hwnd = CreateWindowEx(0,//WS_EX_TOPMOST
		TEXT("first"),			//클래스 명
		TEXT("Hello"),			// 캡션바 내용
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, // 초기위치
		0, 0, //부모 윈도우 핸들, 메뉴 핸들
		hInst, // WinMain의 1번째 파라미터(exe주소)
		0); // 생성 인자

	//4. 윈도우 보여주기
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	//5.Message
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}