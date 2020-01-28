#include <Windows.h>
#include <tchar.h>
#include "resource.h"

/*
가상키를 이용한 KEY_DOWN제어
*/

static POINTS pt = { 0, 0 };//100,100의 위치에서 시작
static TCHAR buf[50];
char ns[18][21];
int nStage ;
int nx, ny;
int nMove;

#define MAXSTAGE 3
#define MBox(x) MessageBox( 0, x, TEXT(""), MB_OK)

char arStage[MAXSTAGE][18][21] = {

	{
	 "####################",
	 "####################",
	 "####################",
	 "#####   ############",
	 "#####O  ############",
	 "#####  O############",
	 "###  O O ###########",
	 "### # ## ###########",
	 "#   # ## #####  ..##",
	 "# O  O   @      ..##",
	 "##### ### # ##  ..##",
	 "#####     ##########",
	 "####################",
	 "####################",
	 "####################",
	 "####################",
	 "####################",
	 "####################"
	 },

	 {
	 "####################",
	 "####################",
	 "####################",
	 "####################",
	 "####..  #     ######",
	 "####..  # O  O  ####",
	 "####..  #O####  ####",
	 "####..    @ ##  ####",
	 "####..  # #  O #####",
	 "######### ##O O ####",
	 "###### O  O O O ####",
	 "######    #     ####",
	 "####################",
	 "####################",
	 "####################",
	 "####################",
	 "####################",
	 "####################"
	 },

	 {
	 "####################",
	 "####################",
	 "####################",
	 "####################",
	 "##########     @####",
	 "########## O#O #####",
	 "########## O  O#####",
	 "###########O O #####",
	 "########## O # #####",
	 "##....  ## O  O  ###",
	 "###...    O  O   ###",
	 "##....  ############",
	 "####################",
	 "####################",
	 "####################",
	 "####################",
	 "####################",
	 "####################"
	 },

};

void DrawScreen(HDC hdc, POINTS pt)
{
	HDC memDC = CreateCompatibleDC(hdc);
	
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (ns[i][j] == '#')
			{
				HBITMAP hBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_WALL));//resource
				BITMAP bm;
				GetObject(hBitmap, sizeof(bm), &bm);
				SelectObject(memDC, hBitmap);
				BitBlt(hdc, pt.x, pt.y, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);	
				DeleteObject(hBitmap);
				
			}
			else if (ns[i][j] == 'O')
			{
				HBITMAP hBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BOX));//resource
				BITMAP bm;
				GetObject(hBitmap, sizeof(bm), &bm);
				SelectObject(memDC, hBitmap);
				BitBlt(hdc, pt.x, pt.y, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);
				DeleteObject(hBitmap);
			}
			else if (ns[i][j] == '@')
			{
				HBITMAP hBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_ACTOR));//resource
				BITMAP bm;
				GetObject(hBitmap, sizeof(bm), &bm);
				SelectObject(memDC, hBitmap);
				BitBlt(hdc, pt.x, pt.y, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);				
				DeleteObject(hBitmap);
				
			}
			else if (ns[i][j] == '.')
			{
				HBITMAP hBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_GOAL));//resource
				BITMAP bm;
				GetObject(hBitmap, sizeof(bm), &bm);
				SelectObject(memDC, hBitmap);
				BitBlt(hdc, pt.x, pt.y, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);
				DeleteObject(hBitmap);
			}
			else {
				HBITMAP hBitmap = LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_EMPTY));//resource
				BITMAP bm;
				GetObject(hBitmap, sizeof(bm), &bm);
				SelectObject(memDC, hBitmap);
				BitBlt(hdc, pt.x, pt.y, bm.bmWidth, bm.bmHeight, memDC, 0, 0, SRCCOPY);
				DeleteObject(hBitmap);
			}

			pt.x += 32;
		}
		pt.y += 32;
		pt.x = 0;
	}
	DeleteDC(memDC);
	wsprintf(buf, TEXT("SOKOBAN"));
	TextOut(hdc, 650, 24, buf,lstrlen(buf));
	wsprintf(buf, TEXT("Q:종료, R:다시 시작"));
	TextOut(hdc, 650, 48, buf, lstrlen(buf));
	wsprintf(buf, TEXT("N:다음, P:이전"));
	TextOut(hdc, 650, 72, buf, lstrlen(buf));
	wsprintf(buf, TEXT("스테이지 : %d"), nStage+1);
	TextOut(hdc, 650, 96, buf, lstrlen(buf));
	wsprintf(buf, TEXT("이동 회수 : %d"), nMove);
	TextOut(hdc, 650, 120, buf, lstrlen(buf));
	

}
void InitStage(HWND hwnd)
{
		nMove = 0;
		memcpy(ns, arStage[nStage], sizeof(ns));
		for (int y = 0; y < 18; y++) {
			for (int x = 0; x < 20; x++) {
				if (ns[y][x] == '@') {
					nx = x;
					ny = y;
				}
			}
		}
		InvalidateRect(hwnd, NULL, TRUE);
}

BOOL TestEnd()
{
	int x, y;
	for (y = 0; y < 18; y++) {
		for (x = 0; x < 20; x++) {
			if (arStage[nStage][y][x] == '.' && ns[y][x] != 'O') {
				return FALSE;
			}
		}
	}
	return TRUE;
}

void Move(WPARAM wParam,HWND hwnd)
{
	int dx = 0, dy = 0;
	switch (wParam) {
	case VK_LEFT:
	{
		dx = -1;
	}break;
	case VK_RIGHT:
	{
		dx = 1;
	} break;
	case VK_UP:
	{
		dy = -1;
	} break;
	case VK_DOWN:
	{
		dy = 1;
	} break;
	}

	if (ns[ny + dy][nx + dx] != '#') {
		if (ns[ny + dy][nx + dx] == 'O') {
			if (ns[ny + dy * 2][nx + dx * 2] == ' ' || ns[ny + dy * 2][nx + dx * 2] == '.') {
				if (arStage[nStage][ny + dy][nx + dx] == '.') {
					ns[ny + dy][nx + dx] = '.';
				}
				else {
					ns[ny + dy][nx + dx] = ' ';
				}
				ns[ny + dy * 2][nx + dx * 2] = 'O';

			}
			else {
				return;
			}
		}
		if (arStage[nStage][ny][nx] == '.')
			ns[ny][nx] = arStage[nStage][ny][nx];
		else
			ns[ny][nx] = ' ';

		nx += dx;
		ny += dy;

		ns[ny][nx] = '@';
		nMove++;

		InvalidateRect(hwnd, NULL, FALSE);

		TCHAR buf2[100];
		if (TestEnd()) {
			wsprintf(buf2, TEXT("%d 스테이지를 풀었습니다. 다음 스테이지로 이동합니다."), nStage + 1);
			MBox(buf2);
			if (nStage < MAXSTAGE - 1) {
				nStage++;
			}
			InitStage(hwnd);
		}
	}
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	switch (msg) {
	case WM_KEYDOWN: {
		Move(wParam, hwnd);
		switch (wParam)
		{
		
		case 'R':
		{
			InitStage(hwnd);
		}break;
		case 'N':
		{
			if (nStage < MAXSTAGE - 1) {
				nStage++;
				InitStage(hwnd);
			}
		}break;
		case 'P':
		{
			if (nStage > 0) {
				nStage--;
				InitStage(hwnd);
			}
		}break;
		case 'Q':
		{
			exit(0);
		}
		}
	}
	return 0;
	case WM_PAINT: {

		PAINTSTRUCT ps;
		hdc = BeginPaint(hwnd, &ps);
		DrawScreen(hdc, pt);
		EndPaint(hwnd, &ps);
	}
	return 0;
	case WM_CREATE: {
		nStage = 0;
		InitStage(hwnd);
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


