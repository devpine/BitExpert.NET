#include <Windows.h>
#include <tchar.h>
/*
아래 함수로 키보드 상태를 조사할 수 있다.
현재 메시지가 발생한 순간의 특정 키보드 상태를 조사한다.
 SHORT GetKeyState(int nVirtKey);
현재 키보드의 상태를 조사한다.
 SHORT GetAsynckKeyState(int vKey);
모든 가상 키의 상태를 얻어온다.
 BOOL GetKeyboardState( PBYTE lpKeyState)
*/

#define MBox(x) MessageBox( 0, x, TEXT(""), MB_OK)
#define IsKeyPress(vk) ( GetKeyState(vk) & 0xFF00)
#define IsKeyToggle(vk) ( GetKeyState(vk) & 0x00FF)//토글, 한번이라도 누르면



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	TCHAR temp[128];

	switch (msg) {
	case WM_KEYDOWN://GetKeyState 현재 메시지가 발생한 순간의 특정 키보드 상태 조사
		if (wParam == VK_F1 && IsKeyPress(VK_CONTROL))
		{
			MBox(TEXT("CTRL + F1"));
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