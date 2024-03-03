#ifndef UNICODE 
#define UNICODE
#endif


#include <Windows.h>
LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMSg,WPARAM wParam , LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance,
                    HINSTANCE hprevInstance 
                    ,PWSTR pCmdLine
                    ,int nCmdShow)
{
    // register the window class 
    const wchar_t CLASS_NAME[] = L"simp";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window

    HWND hwnd = CreateWindowEx(
        0,           //optional window style 
        CLASS_NAME,     // window class
        L"First Window",
        WS_OVERLAPPEDWINDOW,     // window style

        // size and position
        CW_USEDEFAULT , CW_USEDEFAULT , CW_USEDEFAULT , CW_USEDEFAULT ,

        NULL,    //PARent window
        NULL,   // Menu 
        hInstance,   // Instance handle       
        NULL     // ADDTIONAL application data 
    );

    if (hwnd == NULL){
        return 0;
    }

    ShowWindow(hwnd,nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }


    return 0;
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg){
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd,&ps);

            FillRect(hdc,&ps.rcPaint,(HBRUSH) (COLOR_WINDOW + 1));
            EndPaint(hwnd,&ps);
        }
        return 0;
    }
    return DefWindowProc(hwnd,uMsg, wParam,lParam);
}