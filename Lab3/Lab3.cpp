// Lab3.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "Lab3.h"
#include <time.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


BOOL CALLBACK    GreenColor(HWND);
BOOL CALLBACK    OrangeColor(HWND);
BOOL CALLBACK    RedColor(HWND);
BOOL CALLBACK    AutoColor(HWND);

COLORREF green = RGB(0, 255, 0);
COLORREF orange = RGB(255, 165, 0);
COLORREF red = RGB(255, 0, 0);
size_t randcolor = 0;
size_t m_green = 0;
size_t m_orange = 0;
size_t m_red = 0;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB3));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        srand(time(0));
        SetTimer(hWnd, 1, 500, NULL);
    case WM_TIMER:
    {
        HDC hdc = GetDC(hWnd);
        if (randcolor) {
            size_t randomcolor = rand() % 90;
            if (randomcolor < 30) {
                GreenColor(hWnd);
            }
            if (randomcolor > 30 && randomcolor < 60) {
                OrangeColor(hWnd);
            }
            if (randomcolor > 60 && randomcolor < 90) {
                RedColor(hWnd);
            }
            TextOut(hdc, 10, 40, _T("Автоматическое изменение цвета включено!"), 41);
        }
    }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_G:
                randcolor = 0;
                DialogBox(hInst, MAKEINTRESOURCE(IDM_G), hWnd, DLGPROC(GreenColor(hWnd)), 0);
                break;
            case IDM_O:
                randcolor = 0;
                DialogBox(hInst, MAKEINTRESOURCE(IDM_O), hWnd, DLGPROC(OrangeColor(hWnd)), 0);
                break;
            case IDM_R:
                randcolor = 0;
                DialogBox(hInst, MAKEINTRESOURCE(IDM_R), hWnd, DLGPROC(RedColor(hWnd)), 0);
                break;
            case IDM_auto:
                DialogBox(hInst, MAKEINTRESOURCE(IDM_auto), hWnd, DLGPROC(AutoColor(hWnd)), 0);
                break;  
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

BOOL CALLBACK GreenColor(HWND hWnd) {
    RECT rc;
    HDC hdc = GetDC(hWnd);
    GetClientRect(hWnd, &rc);
    COLORREF green = RGB(0,255,0);
    SetDCBrushColor(hdc, green);
    FillRect(hdc, &rc, (HBRUSH)GetStockObject(DC_BRUSH));
    TextOut(hdc, 10, 10, _T("Зеленый цвет активен!"), 22);
    return 0;
}

BOOL CALLBACK OrangeColor(HWND hWnd) {
    RECT rc;
    HDC hdc = GetDC(hWnd);
    GetClientRect(hWnd, &rc);
    SetDCBrushColor(hdc, orange);
    FillRect(hdc, &rc, (HBRUSH)GetStockObject(DC_BRUSH));
    TextOut(hdc, 10, 10, _T("Ораньжевый цвет активен!"), 25);
    return 0;
}

BOOL CALLBACK RedColor(HWND hWnd) {
    RECT rc;
    HDC hdc = GetDC(hWnd);
    GetClientRect(hWnd, &rc);
    SetDCBrushColor(hdc, red);
    FillRect(hdc, &rc, (HBRUSH)GetStockObject(DC_BRUSH));
    TextOut(hdc, 10, 10, _T("Красный цвет активен!"), 22);
    return 0;
}

BOOL CALLBACK AutoColor(HWND hWnd) {
    if (randcolor) {
        randcolor = 0;
    }
    else {
        randcolor = 1;
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
BOOL CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
