#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

const char g_szClassName[] = "snakeWindowClass";

struct node {
    int xVal;
    int yVal;
    struct node *next;
 };
 struct node *head = NULL;
 struct node *current = NULL;

 void insertFirst(int xVal, int yVal){

    //create a link
    struct node *lk = (struct node*) malloc(sizeof(struct node));
    lk->xVal = xVal;
    lk->yVal = yVal;
 
    // point it to old first node
    lk->next = head;
 
    //point first to new first node
    head = lk;
 };

 void insertLast(int xVal, int yVal){

    //create a link
    struct node *lk = (struct node*) malloc(sizeof(struct node));
    lk->xVal = xVal;
    lk->yVal = yVal;
    struct node *linkedlist = head;
 
    // point it to old first node
    while(linkedlist->next != NULL)
       linkedlist = linkedlist->next;
 
    //point first to new first node
    linkedlist->next = lk;
 };

 void deleteFirst(){
    head = head->next;
 };

 void deleteLast(){
    struct node *linkedlist = head;
    while (linkedlist->next->next != NULL)
       linkedlist = linkedlist->next;
    linkedlist->next = NULL;
 };

 
 
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

HWND hwnd;

void drawBorder() 
{
    HDC screen = GetDC(hwnd);
    HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
    SelectObject(screen, blueBrush);
    Rectangle(screen, 0, 0, 300, 300);
    HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(screen, whiteBrush);
    Rectangle(screen, 25, 25, 275, 275);
    // Rectangle(screen, 0, 0, 300, 25);
    // Rectangle(screen, 275, 25, 300, 275);
    // Rectangle(screen, 0, 24, 26, 276);
    // Rectangle(screen, 0, 274, 300, 300);
};

void drawSnakeSeg(int x, int y)
{
    HDC screen = GetDC(hwnd);
    HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
    SelectObject(screen, yellowBrush);
    Rectangle(screen, x, y, x+25, y+25);
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    insertFirst(1,1);
    WNDCLASSEX wc;
    
    MSG Msg;

    wc.cbSize           = sizeof(WNDCLASSEX);
    wc.style            = 0;
    wc.lpfnWndProc      = WndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    =(HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = g_szClassName;
    wc.hIconSm          = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Snake",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 325, 345,
        NULL, NULL, hInstance, NULL
    );

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation failed", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    //FreeConsole();
    

    ShowWindow(hwnd, nCmdShow);
    drawBorder();
    drawSnakeSeg(head->xVal*25, head->yVal*25);
    //drawSnakeSeg(atoi(coords[1].xVal)*25, atoi(coords[1].yVal)*25);
    UpdateWindow(hwnd);

    

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
        if (GetAsyncKeyState(37) < 0)
            {
                fputs("left", stdout);
            };
        if (GetAsyncKeyState(38) < 0)
            {
                fputs("up", stdout);
            };
        if (GetAsyncKeyState(39) < 0)
            {
                fputs("right", stdout);
            };
        if (GetAsyncKeyState(40) < 0)
            {
                fputs("down", stdout);
            };
    }
    return Msg.wParam;

    // while (1) {
        
    //     if (GetAsyncKeyState(37) < 0)
    //         {
    //             fputs("left", stdout);
    //         };
    //     if (GetAsyncKeyState(38) < 0)
    //         {
    //             fputs("up", stdout);
    //         };
    //     if (GetAsyncKeyState(39) < 0)
    //         {
    //             fputs("right", stdout);
    //         };
    //     if (GetAsyncKeyState(40) < 0)
    //         {
    //             fputs("down", stdout);
    //         };
    //     UpdateWindow(hwnd);
    //     SetFocus(hwnd);
              
    //     //printf("key: \n" );
    //     Sleep(1000);
    // };
};
