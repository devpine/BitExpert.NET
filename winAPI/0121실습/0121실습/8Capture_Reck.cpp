#include <Windows.h>
#include <tchar.h>
/*
Capture를 이용해 마우스 다운 무브 드래그로 원하는 곳에 반전모드로 사각형을 그리는 프로그램
GetCapture는 hwnd윈도우가 마우스 커서를 캡처하도록 해줘서 윈도우의 영역밖을 벗어나더라도 마우스가 계속 메세지를 보내준다.
ReleaseCapture함수로 캡처를 풀기 전까지 계속 보내준다.
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINTS start, end;
	static BOOL bNowDraw = FALSE;

	switch (msg) {
	case WM_LBUTTONDOWN:

		start = end = MAKEPOINTS(lParam);
		SetCapture(hwnd);//캡처 시작
		return 0;
	case WM_LBUTTONUP:
		if (GetCapture() == hwnd) 
		{
			ReleaseCapture();//캡처 종료
			//최종선은 R2_COPYPEN으로 그려야 함
			HDC hdc = GetDC(hwnd);//디폴트 그리기 모드가 R2_COPYPEN이다.
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			Rectangle(hdc, start.x, start.y, end.x, end.y);
			ReleaseDC(hwnd, hdc);
		}
		return 0;
	case WM_MOUSEMOVE:
		if (GetCapture() == hwnd) //캡처중인지 판단
		{
			POINTS pt = MAKEPOINTS(lParam);
			HDC hdc = GetDC(hwnd);
			SetROP2(hdc, R2_NOTXORPEN);// 그리기 모드 변경
			SelectObject(hdc, GetStockObject(NULL_BRUSH));
			Rectangle(hdc, start.x, start.y, end.x, end.y);//이동할때마다 초기화해줌 start = end
			Rectangle(hdc, start.x, start.y, pt.x, pt.y);// 얻어온 좌표값으로 새로 그려줌
			end = pt; // END에 이동을 완료한 포인터의 좌표값을 넘겨줌
			ReleaseDC(hwnd, hdc);
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