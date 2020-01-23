#include <Windows.h>
#include <tchar.h>

#define IDC_BUTTON 1
#define IDC_EDIT 2
#define IDC_LISTBOX 3
HWND hBtn, hEdit, hListBox; //윈도우 핸들

/*
[윈도우 클래스]					[컨트롤]
	button					버튼, 체크, 라디오
	static					텍스트
	scrollbar				스크롤 바
	edit					에디트
	listbox					리스트 박스
	combobox				콤보 박스
*/

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	switch (msg) {
	case WM_CREATE:
		hEdit = CreateWindow(TEXT("Edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 10, 90, 20, hwnd, (HMENU)IDC_EDIT, 0, 0);
		hBtn = CreateWindow(TEXT("button"), TEXT("Push"),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 40, 90, 20, hwnd, (HMENU)IDC_BUTTON, 0, 0);
		hListBox = CreateWindow(TEXT("listbox"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			150, 10, 90, 90, hwnd, (HMENU)IDC_LISTBOX, 0, 0);
		// Edit가 입력 받는 글자 갯수를 제한한다.- 메세지를 보낸다.
		SendMessage(hEdit, EM_LIMITTEXT, 5, 0);
		// ListBox 에 항목을 추가한다.
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("AAAA"));
		SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)TEXT("BBBB"));
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) // ID 조사.
		{
		case IDC_EDIT: // EditBox 가 보낸경우
			if (HIWORD(wParam) == EN_CHANGE) //통지 코드 조사.
			{
				TCHAR s[256];
				GetWindowText(hEdit, s, 256); // Edit 에서 값을 얻는다.
				SetWindowText(hwnd, s); // 부모 윈도우의 캡션을 변경한다.
			}
			break;
		case IDC_BUTTON:
			if (HIWORD(wParam) == BN_CLICKED) // 버튼을 누를때 나오는 통지 코드
			{
				TCHAR s[256];
				GetWindowText(hEdit, s, sizeof(s));
				SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)s);
			}
			break;
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