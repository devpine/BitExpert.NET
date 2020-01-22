#include <Windows.h>
#include <tchar.h>
#include "resource.h"
/*
LoadBitmap출력과 LoadImage출력.
p109 참고
*/

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_LBUTTONDOWN:
	{
		HDC hdc = GetDC(hwnd);
		// 화면 DC와 호환(동일색상)되는 메모리 DC를 얻음..
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1));//resource
		BITMAP bm;
		GetObject(hBitmap, sizeof(bm), &bm);
		// 메모리 DC에 비트맵 선택
		SelectObject(memDC, hBitmap);
		// 비트맵으로출력
		TextOut(memDC, 5, 5, TEXT("LoadBitmap으로 출력"), 15);
		// 메모리 DC --> 화면 DC//
		POINTS pt = MAKEPOINTS(lParam);
		BitBlt(hdc, pt.x, pt.y, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);
		// 메모리 제거
		DeleteDC(memDC);
		ReleaseDC(hwnd, hdc);
		DeleteObject(hBitmap);
	}
	return 0;
	case WM_RBUTTONDOWN:
	{
		HDC hdc = GetDC(hwnd);
		// 화면 DC와 호환(동일색상)되는 메모리 DC를 얻음..
		HDC memDC = CreateCompatibleDC(hdc);
		HBITMAP hBitmap = (HBITMAP)LoadImage(0, // 리소스에서 로드할때만 사용
			TEXT("air.bmp"), IMAGE_BITMAP,
			0, 0, // 커서, Icon load시만 사용
			LR_LOADFROMFILE);
		BITMAP bm;
		GetObject(hBitmap, sizeof(bm), &bm);
		// 메모리 DC에 비트맵 선택
		SelectObject(memDC, hBitmap);
		// 비트맵으로출력
		TextOut(memDC, 5, 5, TEXT("LoadImage로 출력"), 13);
		// 메모리 DC --> 화면 DC//
		POINTS pt = MAKEPOINTS(lParam);
		BitBlt(hdc, pt.x, pt.y, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);
		// 메모리 제거
		DeleteDC(memDC);
		ReleaseDC(hwnd, hdc);
		DeleteObject(hBitmap);
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