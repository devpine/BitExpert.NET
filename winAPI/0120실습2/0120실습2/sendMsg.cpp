/*
0120실습 프로젝트의 recvMsg.cpp 파일과 사용
*/
#include <stdio.h>
#include <Windows.h>

#define WM_MYMESSAGE WM_USER+100

int main(void)
{
	HWND hwnd = FindWindow(0, TEXT("Hello"));
	
	BOOL b = PostMessage(hwnd, WM_MYMESSAGE, 10, 20);
	if (b == TRUE)
	{
		printf("전송 되었습니다.\n");
	}
	printf("프로그램을 종료합니다.\n");

	return 0;
}