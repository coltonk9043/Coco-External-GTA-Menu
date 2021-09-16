// Coco-External.cpp : Defines the entry point for the application.

#include "Main.h"

// Global Variables:
HINSTANCE hInst;                                // Current Window Instance
WCHAR szTitle[100] = L"Coco External";          // The title bar text
RECT rect = { 0, 0, 1920, 1080 };                 // Current Window Size

Gui* gui;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    gui = new Gui();
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow)) return FALSE;
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COCOEXTERNAL));
    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
           int i = gui->UpdateAndDraw();
           if (i == 0) ExitProcess(0);;
           SleepEx(32.66, false); // 16.33 milliseconds = 60fps
    }
    return (int) msg.wParam;
}

// Registers the class window.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COCOEXTERNAL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(0,0,0));
    wcex.lpszMenuName   = szTitle;
    wcex.lpszClassName  = szTitle;
    wcex.hIconSm        = 0;

    return RegisterClassExW(&wcex);
}

//   FUNCTION: InitInstance(HINSTANCE, int)
//   PURPOSE: Saves instance handle and creates main window
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, szTitle, szTitle, WS_EX_TOPMOST | WS_POPUP,
      0, 0, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);
   if (!hWnd) return FALSE;

   SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 225, LWA_COLORKEY | LWA_ALPHA);
   gui->Init(hWnd);
   ShowWindow(hWnd, nCmdShow);
   return TRUE;
}

// Process messages to the main window.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void setXPosition(int x) {


}
