#include <Windows.h>
#include <tchar.h>
#pragma warning(disable:4996)
/*
맵핑모드를 사용해 화면상이 아닌 실제 치수 단위로 변환 가능
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_LBUTTONDOWN:
	{
		BOOL bPresent = GetSystemMetrics(SM_MOUSEPRESENT);//마우스가 존재하면 0이 아닌 값 리턴
		BOOL bWheel = GetSystemMetrics(SM_MOUSEWHEELPRESENT);//마우스 휠이 존재하면 0이 아닌 값 리턴
		int nBtn = GetSystemMetrics(SM_CMOUSEBUTTONS);//마우스 버튼의 개수 리턴
		int scx = GetSystemMetrics(SM_CXSCREEN); // 현재 창 해상도의 X축 길이
		int scy = GetSystemMetrics(SM_CYSCREEN); // 현재 창 해상도의 Y축 길이
		TCHAR info[128];
		wsprintf(info, _TEXT("%s %s is installed. (%d Buttons)\n"),
			(bWheel ? _TEXT("Wheel") : _TEXT("")),
			(bPresent ? _TEXT("Mouse") : _TEXT("No Mouse")), nBtn);
		TCHAR temp[64];
		wsprintf(temp, _TEXT("\nScreen Resolution : %d * %d"), scx, scy);
		wcscat(info, temp);
		MessageBox(NULL, info, TEXT(""), MB_OK);
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