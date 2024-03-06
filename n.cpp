#include <Windows.h>
#include <iostream>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void AddMenu(HWND hWnd);

HMENU hMenu;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"FIRST CLASS";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(0, CLASS_NAME, L"HELLO WORLD", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    if (hwnd == NULL){
        std::wcout << L"Failed to initialize handle " << std::endl;
        return -1;
    }
    ShowWindow(hwnd, nCmdShow);
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        AddMenu(hWnd);
        break;
    case WM_COMMAND:
        switch(wParam){
            case 1:
                MessageBeep(MB_OK);
                break;
            case 2:
                PostQuitMessage(0);
                return 0;
        }
        break;
    case WM_DESTROY:
        MessageBeep(MB_DEFBUTTON1);
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
        EndPaint(hWnd, &ps);
    }
        return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void AddMenu(HWND hWnd){
    hMenu = CreateMenu();
    AppendMenu(hMenu, MF_STRING, 1, L"File");
    AppendMenu(hMenu, MF_STRING, 2, L"EXIT");

    SetMenu(hWnd, hMenu);
}
