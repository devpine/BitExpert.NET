#include <Windows.h>
#include <tchar.h>
/*
마우스 다운, 무브, 업으로 원하는 위치에 반전모드로 선을 그리는 프로그램
화면 밖을 벗어나면 그리기가 중지됨.
70페이지
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static POINTS start, end;
	static BOOL bNowDraw = FALSE;

	switch (msg) {
	case WM_LBUTTONDOWN:
	{
		start = MAKEPOINTS(lParam);//lParam에 좌표가 들어옴, MAKEPOINTS를 써서 좌표를 넣어줌
		end = start;
		bNowDraw = TRUE; // 그리기 모드 TRUE
	}
	return 0;
	case WM_MOUSEMOVE:
	{
		if (bNowDraw) // 그리기 모드가 TRUE일때
		{
			HDC hdc = GetDC(hwnd);
			SetROP2(hdc, R2_NOT);//R2_NOT = 원래의 그림을 반전시킨다, 이걸 지정해줘야 움직이는 동안 선이 보임
			MoveToEx(hdc, start.x, start.y, NULL);
			LineTo(hdc, end.x, end.y); //  end와 start의 좌표가 같아서 지워짐

			//위의 코드로 인해 움직일때 마다 지워짐


			end = MAKEPOINTS(lParam); // end에 현재 마우스 좌표값을 넣어줌
			MoveToEx(hdc, start.x, start.y, NULL);//start값은 마우스 왼클릭 누른좌표 고정
			LineTo(hdc, end.x, end.y);//움직인 거리만큼 새로 그려줌
			ReleaseDC(hwnd, hdc);
		}
	}
	return 0;
	case WM_LBUTTONUP:
	{
		bNowDraw = FALSE;//그리기 종료
		HDC hdc = GetDC(hwnd);
		MoveToEx(hdc, start.x, start.y, NULL);
		LineTo(hdc, end.x, end.y);//선의 위치를 확정하여 그려줌
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