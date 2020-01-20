/*
작업 표시줄을 감추거나 보이게함
*/
#include <Windows.h>
#include <tchar.h>

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nShowCmd)
{
	HWND hWnd = FindWindow(TEXT("Shell_TrayWnd"), 0);
	if (IsWindowVisible(hWnd)) 
		ShowWindow(hWnd, SW_HIDE); // 작업표시줄 감춤
	else
		ShowWindow(hWnd, SW_SHOW); // 작업표시줄 보임
	return 0;
}