// WinThread.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "cthread.h"


class Thread :public CThread
{
protected:
	virtual void Run(LPVOID lpParameter=0);
};

LRESULT CALLBACK WindowProcedure(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);


void Thread::Run(LPVOID lpParameter)
{
	WNDCLASSEX wndEx = {0};

	wndEx.cbClsExtra = 0;
	wndEx.cbSize = sizeof(WNDCLASSEX);
	wndEx.cbWndExtra = 0;
	wndEx.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
	wndEx.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndEx.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndEx.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wndEx.hInstance = GetModuleHandle(NULL);
	wndEx.lpfnWndProc = WindowProcedure;//
	wndEx.lpszClassName = (LPCTSTR)this->lpParameter;
	wndEx.lpszMenuName = NULL;
	wndEx.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;

	//Register class of the window
	if (!RegisterClassEx(&wndEx))
	{
		return;
	}

	HWND hWnd = CreateWindow(wndEx.lpszClassName,
		                     L"Basic-Thread-Management",
		                     WS_OVERLAPPEDWINDOW,
		                     200,200,800,600,
		                     HWND_DESKTOP,
		                     NULL,
		                     wndEx.hInstance,
		                     NULL);

	UpdateWindow(hWnd);
	ShowWindow(hWnd,SW_SHOW);

	MSG  msg = {0};
	while (GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//Un-register the class of the window
	UnregisterClass(wndEx.lpszClassName,wndEx.hInstance);
}







int main(int argc,char argv[])
{
    //std::cout << "Hello World!\n"; 

	Thread thread_0001;
	thread_0001.Create((LPVOID)L"WINDOW_0001");

	Thread thread_0002;
	thread_0002.Create((LPVOID)L"WINDOW_0002");

	thread_0001.Join();
	thread_0002.Join();
	return 0;
}


LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}

		case WM_CLOSE:
		{
			DestroyWindow(hWnd);
			break;
		}

	    default:
		{
			return DefWindowProc(hWnd,uMsg,wParam,lParam);
		}
	}

	return 0;
}