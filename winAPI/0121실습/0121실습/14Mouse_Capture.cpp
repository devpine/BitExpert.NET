#include <Windows.h>
#include <tchar.h>
#pragma warning(disable:4996)
/*
SetCapture()함수를 사용해서 마우스를 캡쳐할경우, 모든 마우스 메시지는
마우스를 캡쳐한 윈도우에게 전달

캡쳐 해제
-ReleaseCapture()함수 호출
-다른 윈도우가 마우스를 캡쳐
-사용자가 다른 스레드가 만든 윈도우 클릭

해제될때 캡쳐를 잃은 윈도우에 WM_CAPTURECHANGED메시지가 전달
이때 lParam에는 새롭게 마우스를 캡쳐 한 윈도우의 핸들이 들어있음.

캡쳐 종류
-Foreground Capture
 모든 윈도우에서 발생한 마우스 메시지를 받을 수 있음
-Background Capture
 동일 스레드내의 마우스 메시지만을 받을 수 있음
*/

void PrintWindowInfo(HWND hwnd)
{
	TCHAR Info[1024] = { 0 };
	TCHAR temp[256];
	RECT rcWin;
	GetClassName(hwnd, temp, 256);
	wsprintf(Info, TEXT("Window Class : %s\n"), temp);
	GetWindowText(hwnd, temp, 256);
	wsprintf(Info + wcslen(Info), TEXT("Window Caption : %s\n"), temp);
	GetWindowRect(hwnd, &rcWin);
	wsprintf(Info + wcslen(Info), TEXT("Window Position : (%d,%d)-(%d,%d)"),
		rcWin.left, rcWin.top, rcWin.right, rcWin.bottom);
	MessageBox(0, Info, TEXT("Window Info"), MB_OK);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		SetCapture(hwnd); // 캡쳐 시작
		return 0;
	case WM_LBUTTONUP:
		if (GetCapture() == hwnd)
		{
			ReleaseCapture(); // 캡쳐 종료
			POINT pt;
			GetCursorPos(&pt); 
			HWND hwndDest = WindowFromPoint(pt);
			PrintWindowInfo(hwndDest); 
		}
		return 0;
	case WM_MOUSEMOVE:
	{
		short xPos, yPos;
		TCHAR temp[256];
		xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);
		wsprintf(temp, TEXT("Cursor Position : (%d, %d)"), xPos, yPos);
		SetWindowText(hwnd, temp);//temp에 담긴 string을 캡션으로 설정
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