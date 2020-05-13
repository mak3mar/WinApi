#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include <random>

int winWidth = 490;
int winHeight = 510;
int x = 100;
int y = 100;
int R = 255, G = 255, B = 0;
unsigned int step = 50;
unsigned int random = 0;

WNDCLASS wc;
int r = 154, g = 205, b = 50;

HBRUSH color_of_window = CreateSolidBrush(RGB(r, g, b));

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain(HINSTANCE This,
	HINSTANCE Prev,
	LPTSTR cmd,
	int mode) {
	HWND hWnd;
	MSG msg;

	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = color_of_window;

	if (!RegisterClass(&wc)) return 0;

	hWnd = CreateWindow(WinName,
		_T("Windows"),
		WS_OVERLAPPEDWINDOW,
		x,
		y,
		winWidth,
		winHeight,
		HWND_DESKTOP,
		NULL,
		This,
		NULL);

	ShowWindow(hWnd, mode);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	
	switch (message) {
	case WM_PAINT:
	{
		HDC hdc;
		HBRUSH brush;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);
		brush = CreateSolidBrush(RGB(R, G, B));
		SelectObject(hdc, brush);
		Pie(hdc, winWidth/2 - step - random, winHeight/2 - step - random, 
			winWidth / 2 + step + random, winHeight / 2 + step + random, 100, 0, 100, 0);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_LBUTTONUP:
		random = 10 + rand() % 100;
		R = rand() % 256;
		G = rand() % 256;
		B = rand() % 256;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_RBUTTONUP:
		random = 0;
		step = 50;
		R = 255;
		G = 255;
		B = 0;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
