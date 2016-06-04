// Win32ProjectFinal.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Win32ProjectFinal.h"

#define MAX_LOADSTRING 100
#define IDM_BUTON1 110
#define IDM_BUTON2 120
#define IDM_GATA1 130
#define IDM_GATA2 140
#define IDM_FLOYD 150
#define INF 30000
#define N 7

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
char *v[7] = { "ACASA","BISERICA", "MALL","POLITIE","PRIMARIE","SCOALA","TRIBUNAL" };
int dist[N][N];
int graph[N][N] = { { 0,   INF,  20, 10, INF, INF, INF },
				  { INF,   0,  INF, 15, 7, INF, 9 },
				  { INF,   INF,  0, INF, 12, 6, INF },
				  { 10,   15,  INF, 0, INF, INF, 8 },
				  { INF,   7,  12, INF, 0, INF, INF },
				  { INF,   INF,  6, INF, INF, 0, 5 },
				  { INF,   9,  INF, 8, INF, 5, 0 },
};

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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECTFINAL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECTFINAL));

    MSG msg;

    // Main message loop:
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECTFINAL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(180, 180, 180));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECTFINAL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, (WCHAR*)"Calculatorul de drumuri DLV", WS_OVERLAPPEDWINDOW | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
      CW_USEDEFAULT, 0, 900, 700, NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//


void GamePaint(HDC hDC)
{
	MoveToEx(hDC, 120, 10, NULL);
	LineTo(hDC, 120, 230);
	LineTo(hDC, 305, 130);
	LineTo(hDC, 350, 240);
	MoveToEx(hDC, 315, 10, NULL);
	LineTo(hDC, 315, 130);
	MoveToEx(hDC, 500, 130, NULL);
	LineTo(hDC, 500, 230);
	LineTo(hDC, 380, 250);
	LineTo(hDC, 110, 230);
	MoveToEx(hDC, 300, 10, NULL);
	LineTo(hDC, 500, 150);
	LineTo(hDC, 150, 10);
	
}
void floydWarshall(int graph[N][N])
{
	int  i, j, k;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			dist[i][j] = graph[i][j];
		}
	}
	for (k = 0; k < N; k++)
	{
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND text1, text2;
	HWND buton1, buton2;
	HWND gata1, gata2,floyd;
	int flag = 0;
    switch (message)
    {
	case WM_CREATE: 
	{
		//create the LHS edit box
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("ACASA"), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP, 80, 10, 80, 25, hWnd, (HMENU)IDM_LHS, GetModuleHandle(NULL), NULL);

		//create the RHS edit box
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("PRIMARIE"), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP, 275, 10, 80, 25, hWnd, (HMENU)IDM_RHS, GetModuleHandle(NULL), NULL);

		//create the Result edit box
		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("POLITIE"), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP, 80, 230, 80, 25, hWnd, (HMENU)IDM_RESULT, GetModuleHandle(NULL), NULL);

		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("BISERICA"), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP, 290, 130, 80, 25, hWnd, (HMENU)IDM_RESULT, GetModuleHandle(NULL), NULL);

		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("MALL"), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP, 460, 130, 80, 25, hWnd, (HMENU)IDM_RESULT, GetModuleHandle(NULL), NULL);

        CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("SCOALA"), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP, 460, 230, 80, 25, hWnd, (HMENU)IDM_RESULT, GetModuleHandle(NULL), NULL);

		CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT("TRIBUNAL"), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP, 300, 230, 80, 25, hWnd, (HMENU)IDM_RESULT, GetModuleHandle(NULL), NULL);

		text1 = CreateWindow("STATIC", "Va rog sa introduceti nodul de plecare:", WS_VISIBLE | WS_CHILD | WS_BORDER, 80, 350, 300, 30, hWnd, NULL, NULL, NULL);

		text2 = CreateWindow("STATIC", "Va rog sa introduceti nodul de sosire:", WS_VISIBLE | WS_CHILD | WS_BORDER, 80, 450, 300, 30, hWnd, NULL, NULL, NULL);

		buton1 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 380, 350, 100, 30, hWnd, (HMENU)IDM_BUTON1, GetModuleHandle(NULL), NULL);

		buton2 = CreateWindow("EDIT", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 380, 450, 100, 30, hWnd, (HMENU)IDM_BUTON2, GetModuleHandle(NULL), NULL);

		gata1 = CreateWindow("BUTTON", "GATA", WS_BORDER | WS_CHILD | WS_VISIBLE, 300, 400, 80, 30, hWnd, (HMENU)IDM_GATA1, GetModuleHandle(NULL), NULL);

		gata2 = CreateWindow("BUTTON", "GATA", WS_BORDER | WS_CHILD | WS_VISIBLE, 300, 500, 80, 30, hWnd, (HMENU)IDM_GATA2, GetModuleHandle(NULL), NULL);

		floyd = CreateWindow("BUTTON", "CALCULEAZA", WS_BORDER | WS_CHILD | WS_VISIBLE, 500, 350, 100,30, hWnd, (HMENU)IDM_FLOYD, GetModuleHandle(NULL), NULL);
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
			int lungime1 = GetWindowTextLength(GetDlgItem(hWnd, IDM_BUTON1));
			int lungime2 = GetWindowTextLength(GetDlgItem(hWnd, IDM_BUTON2));
			static char buffer1[100], buffer2[100];
			GetDlgItemText(hWnd, IDM_BUTON1, buffer1, lungime1 + 1);
			GetDlgItemText(hWnd, IDM_BUTON2, buffer2, lungime2 + 1);
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDM_GATA1:
				GetDlgItemText(hWnd, IDM_BUTON1, buffer1, lungime1 + 1);
				for (int i = 0;i < 7;i++)
				{	
					if (strcmp(buffer1, v[i]) != 0)
					{
						flag = 1;
					}
					else
					{
						flag = 0;
						break;
					}
				}
				if (flag==1)
				{
				MessageBox(hWnd, "", "Nod inexistent! Introduceti un alt nod!", MB_OK);
				}
				break;
			case IDM_GATA2:
				GetDlgItemText(hWnd, IDM_BUTON2, buffer2, lungime2 + 1);
				for (int i = 0;i < 7;i++)
				{
					if (strcmp(buffer2, v[i]) != 0)
					{
						flag = 1;
					}
					else
					{
						flag = 0;
						break;
					}
				}
				if (flag == 1)
				{
					MessageBox(hWnd, "", "Nod inexistent! Introduceti un alt nod!", MB_OK);
				}
				break;
			case IDM_FLOYD:
			{
				int nod1, nod2;
				floydWarshall(graph);
				for (int i = 0;i < 7;i++)
				{
					if (strcmp(buffer1, v[i]) == 0)
					{
						nod1 = i;
					}
					if (strcmp(buffer2, v[i]) == 0)
					{
						nod2 = i;
					}
				}
				char raspuns[100] = { "Costul minim dintre cele doua obiective este:" };
				char *aux=nullptr;
				aux=_itoa(dist[nod1][nod2], (char*)malloc(10*sizeof(char)), 10);
				strcat(raspuns, aux);
				MessageBox(hWnd, raspuns, "REZULTAT", MB_OK);
				break;
			}
			break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hDC = BeginPaint(hWnd, &ps);
			GamePaint(hDC);
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

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
