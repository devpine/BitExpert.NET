/*
윈도우 프로그램 이름이 "OOO"인것의 핸들을 얻어옴
*/

#include<Windows.h>
#include <tchar.h>
int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd = FindWindow(0, _TEXT("계산기")); // FindWindow = 윈도우의 핸들을 얻어오는 함수

	if (hwnd == 0)
	{
		MessageBox(0, _TEXT("계산기 핸들을 얻을 수 없습니다."),
			_TEXT("알림"), MB_OK | MB_ICONERROR);
		return 0;
	}
	else{
		TCHAR temp[20];
		wsprintf(temp, _TEXT("계산기 핸들 : %d"), hwnd);
		MessageBox(0, temp, _TEXT("알림"), MB_OK);
	}
	return 0;
}