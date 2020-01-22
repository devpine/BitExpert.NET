#include <Windows.h>
#include <tchar.h>
/*
BitBlt()함수는 크기를 늘이거나 줄일 수는 없음. 복사하면서 이미지의 크기를 늘리거나 줄
이려는 경우는 StretchBlt를 사용한다.
BOOL StretchBlt( HDC hdcDest, // handle to destination DC
int nXOriginDest, // x-coord of destination upper-left corner
int nYOriginDest, // y-coord of destination upper-left corner
int nWidthDest, // width of destination rectangle
int nHeightDest, // height of destination rectangle
HDC hdcSrc, // handle to source DC
int nXOriginSrc, // x-coord of source upper-left corner
int nYOriginSrc, // y-coord of source upper-left corner
int nWidthSrc, // width of source rectangle
int nHeightSrc, // height of source rectangle
DWORD dwRop // raster operation code );

왼쪽클릭한 상태로 화면밖에 마우스 포인터가 가리키는 바탕화면을 확대시켜주는 프로그램 
*/

HDC hdcDisplay, hdcClient;
static int cxClient, cyClient;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		return 0;
	case WM_LBUTTONDOWN:
		SetCapture(hwnd);//윈도우 창 바깥 영역의 마우스 메시지를 받기위해 캡쳐
		return 0;
	case WM_LBUTTONUP:
		if (GetCapture() == hwnd)
			ReleaseCapture();//캡쳐 종료
		return 0;
	case WM_MOUSEMOVE:
		if (GetCapture() == hwnd)
		{
			POINT pt;
			GetCursorPos(&pt);
			hdcDisplay = CreateDC(TEXT("DISPLAY"), 0, 0, 0);
			hdcClient = GetDC(hwnd);
			StretchBlt(hdcClient, 0, 0, cxClient, cyClient,//복사 대상과 복사원이 모두 폭과 높이를 가짐
				hdcDisplay, pt.x, pt.y, 100, 100, SRCCOPY);//복사원의 지정한 영역이 복사대상의 지정한 영역을 크기만큼 확대되어 출력
			DeleteDC(hdcDisplay);
			ReleaseDC(hwnd, hdcClient);
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