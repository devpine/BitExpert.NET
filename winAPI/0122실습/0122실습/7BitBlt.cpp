#include <Windows.h>
#include <tchar.h>
/*
BOOL BitBlt(HDC hdcDest, // handle to destination DC
int nXDest, // x-coord of destination upper-left corner
int nYDest, // y-coord of destination upper-left corner
int nWidth, // width of destination rectangle
int nHeight, // height of destination rectangle
HDC hdcSrc, // handle to source DC
int nXSrc, // x-coordinate of source upper-left corner
int nYSrc, // y-coordinate of source upper-left corner
DWORD dwRop // raster operation code );

비디오 메모리의 특정 영역에 있는 Data를 다른 영역으로 옮길때 사용
*/


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdcDisplay, hdcClient;
	static int cxClient, cyClient;


	switch (msg) {
	case WM_MOVE:
		InvalidateRect(hwnd, 0, TRUE);
		return 0;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_ERASEBKGND:
		return TRUE;
	case WM_PAINT:
		hdcDisplay = CreateDC(TEXT("DISPLAY"), 0, 0, 0); // 바탕화면 DC
		hdcClient = BeginPaint(hwnd, &ps); // 클라이언트 DC
		BitBlt(hdcClient, 0, 0, cxClient, cyClient, //2개의 DC는 반드시 호환 되어야한다(Compatible,색상면(plane)과 픽셀당 비트(bpp)가 동일)
			hdcDisplay, 0, 0, SRCCOPY);//바탕화면 0,0부터 클라이언트의 x,y까지 복사함
		DeleteDC(hdcDisplay);
		EndPaint(hwnd, &ps);
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