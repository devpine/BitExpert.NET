#include <Windows.h>
#include <tchar.h>
/*
현재 지역 시간을 구한다.
 void GetLocalTime( LPSYSTEMTIME lpSystemTime )
세계 표준 시간(UTC)를 구한다.
 void GetSystemTime( LPSYSTEMTIME lpSystemTime )

 또한 아래 함수들을 사용하면 SYSTEMTIME 구조체를 문자열로 변환 할 수 있다.
int GetTimeFormatEx( LCID Locale, DWORD dwFlags, CONST SYSTEMTIME *lpTime,
 LPCTSTR lpFormat, LPTSTR lpTimeStr, int cchTime, NULL );
int GetDateFormatEx( LCID Locale, DWORD dwFlags, CONST SYSTEMTIME *lpDate,
 LPCTSTR lpFormat, LPTSTR lpDateStr, int cchDate);
*/


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	TCHAR temp[128];

	switch (msg) {
	case WM_LBUTTONDOWN:
	{
		SYSTEMTIME st;
		GetSystemTime(&st); // 세계 표준 시간(UTC)를 구함
		TCHAR buf[50];
		GetDateFormatEx(LOCALE_NAME_USER_DEFAULT, 0, &st, TEXT("yyyy년 M월 d일"), buf, 50,NULL); 
		//최신버전 윈도우에선 Ex를 지향, buf다음의 정수는 buf사이즈와 맞춰줌
		SetWindowText(hwnd, buf);
	}
	return 0;
	case WM_RBUTTONDOWN:
	{
		SYSTEMTIME st;
		GetLocalTime(&st);// 현재 지역 시간을 구함
		TCHAR buf[50];
		GetTimeFormatEx(LOCALE_NAME_USER_DEFAULT, 0, &st, TEXT("tt h시 m분 s초"), buf, 50);
		SetWindowText(hwnd, buf);
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
	wc.hIcon = LoadIcon(0, IDI_APPLICATION);
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