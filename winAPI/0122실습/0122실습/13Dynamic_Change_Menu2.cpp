#include <Windows.h>
#include <tchar.h>
#include "resource.h"
/*
왼쪽 클릭으로 "추가메뉴"라는 메뉴를 생성하고 서브메뉴에 BBB를 추가한다
오른쪽 클릭으로 특정 메뉴를 삭제한다.
*/

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HMENU hMenu = 0;
	
	
	switch (msg) {
	case WM_LBUTTONDOWN:
	{
		HMENU h = GetMenu(hwnd);
		HMENU sub = CreateMenu();
		// 메뉴 추가
		AppendMenu(h, MF_POPUP, (UINT)sub, TEXT("추가메뉴")); // sub ==> ID값..
		AppendMenu(sub, MF_STRING, (UINT)h, TEXT("BBB"));

		//HMENU h1 = GetMenu(hwnd);
		//AppendMenu(h1, MF_SEPARATOR, 5002, TEXT(""));
		// 메뉴바에 직접 추가한 경우에는 반드시 메뉴바를 다시 그려야 한다.
		DrawMenuBar(hwnd); 
	}
	return 0;

	case WM_RBUTTONDOWN:
	{
		HMENU h = GetMenu(hwnd);
		int n = GetMenuItemCount(h);//메뉴의 갯수를 받아옴
		if(n >2)
		RemoveMenu(h, n-1, MF_BYPOSITION);//MF_BYPOSITION = 메뉴의 순서대로
		//RemoveMenu(h, (UINT)h, MF_BYCOMMAND);//새로 생성된 메뉴의 sub메뉴만 삭제

		//HMENU hSub = GetSubMenu(h, 0);
		//RemoveMenu(hSub, ID_MENU1_TEST2, MF_BYCOMMAND); // 선택한 메뉴 삭제
		DrawMenuBar(hwnd);
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