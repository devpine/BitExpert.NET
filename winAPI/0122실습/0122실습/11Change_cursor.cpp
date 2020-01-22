#include <Windows.h>
#include <tchar.h>
#include "resource.h"
/*
윈도우 클래스에서 esource icon을 불러와 호출하고, 왼쪽 클릭으로 Resource icon을 불러오는 프로그램
*/


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HCURSOR h1 = LoadCursorFromFile(TEXT("C:\\windows\\cursors\\size1_i.cur"));
	static HCURSOR h2 = LoadCursorFromFile(TEXT("C:\\windows\\cursors\\size1_il.cur"));
	static RECT rc = { 100,100,300,300 }; // 클라이언트 좌표.

	switch (msg)
	{
	case WM_SETCURSOR:
	{
		int code = LOWORD(lParam); // hit test code가 들어 있다.
		POINT pt;
		GetCursorPos(&pt); // 현재 커서의 위치(스크린 좌표)
		ScreenToClient(hwnd, &pt); // 스크린 좌표를 클라이 언트 좌표로..
		// 클라이언트 안에서도 특정위치에서는 다른 커서를 사용하는 방법.
		if (code == HTCLIENT && PtInRect(&rc, pt))
		{
			SetCursor(LoadCursor(0, IDC_ARROW));
			return TRUE;
		}
		//그외의 Client에서는 DefWindowProc이 변경해 줄것이다.!!!!!
		//----------------------------------------------------------
		if (code == HTLEFT || code == HTRIGHT)
		{
			SetCursor(h2);
			return TRUE; // 커서를 변경한 경우 TRUE 리턴
		}
		else if (code == HTTOP || code == HTBOTTOM)
		{
			SetCursor(h1);
			return TRUE;
		}
	}
	// 내가 변경하지 않은 다른 부분을 변경하기 위해 아래 함수로
	// 반드시 보내야 한다.
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
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