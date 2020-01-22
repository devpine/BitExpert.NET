#include <Windows.h>
#include <tchar.h>
#include "resource.h"
/*
Menu1은 CheckMenuItem으로 눌렀을때 체크되며
Menu2는 EnableMenuItem으로 비활성화 상태가 된다
*/

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int submenu1 = ID_MENU1_TEST1;//디폴트 값
	static int submenu2 = ID_MENU2_TEST1;

	switch (msg) {
		// PopUp 메뉴가 펼쳐지기 직전 체크
	case WM_INITMENUPOPUP: { //체크와 비활성화
		// HMENU hMenu = GetMenu(hwnd);
		HMENU hMenu = (HMENU)wParam;
		CheckMenuItem(hMenu, ID_MENU1_TEST1,
			submenu1 == ID_MENU1_TEST1 ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_MENU1_TEST2,
			submenu1 == ID_MENU1_TEST2 ? MF_CHECKED : MF_UNCHECKED);
		CheckMenuItem(hMenu, ID_MENU1_TEST3,
			submenu1 == ID_MENU1_TEST3 ? MF_CHECKED : MF_UNCHECKED);
		EnableMenuItem(hMenu, ID_MENU2_TEST1,
			submenu2 == ID_MENU2_TEST1 ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, ID_MENU2_TEST2,
			submenu2 == ID_MENU2_TEST2 ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, ID_MENU2_TEST3,
			submenu2 == ID_MENU2_TEST3 ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, ID_MENU2_TEST4,
			submenu2 == ID_MENU2_TEST4 ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, ID_MENU2_TEST5,
			submenu2 == ID_MENU2_TEST5 ? MF_GRAYED : MF_ENABLED);
		EnableMenuItem(hMenu, ID_MENU2_TEST6,
			submenu2 == ID_MENU2_TEST6 ? MF_GRAYED : MF_ENABLED);
	}
						 return 0;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) // ID 조사
		{//메뉴가 눌러질 경우 수행
		case ID_MENU1_TEST1: SetWindowText(hwnd, TEXT("ID_MENU1_TEST1"));
			submenu1 = ID_MENU1_TEST1; break;
		case ID_MENU1_TEST2: SetWindowText(hwnd, TEXT("ID_MENU1_TEST2"));
			submenu1 = ID_MENU1_TEST2; break;
		case ID_MENU1_TEST3: SetWindowText(hwnd, TEXT("ID_MENU1_TEST3"));
			submenu1 = ID_MENU1_TEST3; break;
		case ID_MENU2_TEST1: SetWindowText(hwnd, TEXT("ID_MENU2_TEST1"));
			submenu2 = ID_MENU2_TEST1; break;
		case ID_MENU2_TEST2: SetWindowText(hwnd, TEXT("ID_MENU2_TEST2"));
			submenu2 = ID_MENU2_TEST2; break;
		case ID_MENU2_TEST3: SetWindowText(hwnd, TEXT("ID_MENU2_TEST3"));
			submenu2 = ID_MENU2_TEST3; break;
		case ID_MENU2_TEST4: SetWindowText(hwnd, TEXT("ID_MENU2_TEST4"));
			submenu2 = ID_MENU2_TEST4; break;
		case ID_MENU2_TEST5: SetWindowText(hwnd, TEXT("ID_MENU2_TEST5"));
			submenu2 = ID_MENU2_TEST5; break;
		case ID_MENU2_TEST6: SetWindowText(hwnd, TEXT("ID_MENU2_TEST6"));
			submenu2 = ID_MENU2_TEST6; break;
		}
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
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //메뉴 추가
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