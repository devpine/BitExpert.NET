#include <Windows.h>
#include <tchar.h>
/*----------------------------------------------------------
GDI오브젝트		핸들타입		설명				디폴트
------------------------------------------------------------
펜				HPEN			선을 그릴때 사용	검정색의 가는 실선
브러쉬			HBRUSH			면을 채울 때 사용	흰색
폰트			HFONT			문자 출력에 사용	시스템 글꼴
비트맵			HBITMAP			비트맵 이미지		x
팔레트			HPALETTE		팔레트				x
리전			HRGN			화면상의 영역		x
------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		/*
		HS_FDIAGONAL(우하향 줄무늬)			HS_CROSS(바둑판 모양)
		HS_DIAGCROSS(좌우하향 줄무늬)		HS_BDIAGONAL(좌하향 줄무늬)
		HS_HORIZONTAL(수평선)				HS_VERTICAL(수직선)
		*/
		HBRUSH brush = CreateHatchBrush(HS_CROSS, RGB(255, 0, 0)); // hatch는 색상 뿐 아니라 무늬를 지정함
		//HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0)); soild는 단순히 색만 채워줌
		HBRUSH old = (HBRUSH)SelectObject(hdc, brush);
		Rectangle(hdc, 10, 10, 100, 100);
		DeleteObject(SelectObject(hdc, old));
		EndPaint(hwnd, &ps);
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