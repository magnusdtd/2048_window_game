#include <windows.h>

/*WARNING: carefull whenever you change this variable*/
//=======================//
bool running = true;
void* bufferMemory;
int bufferWidth;
int bufferHeight;
BITMAPINFO bufferBitmapInfo;
//=====================//

/*
	Description: This callback function is the way window use to pass messages down to us.
	Whenever sonething happens to window like receives user input, close window, changing the size or minimize, ... the window will receive a message for this callback function.
Parameters:
	1. hwnd - type: HWND
	It is a handle to the window.
	2. uMsg - type: UINT
	It is the message code; for example, the WM_SIZE message indicates the window was resized.
	3. wParam and lParam
	Its contain additional data that pertains to the message. The exact meaning depends on the message code.
Return value:
	An integer value that your program returns to Windows - type: LRESULT
*/
LRESULT CALLBACK windowCallBack(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (uMsg) 
	{
		case WM_CLOSE:
		case WM_DESTROY: 
		{	
			running = false;
		} break;

		case WM_SIZE: 
		{
			RECT rect;
			GetClientRect(hwnd, &rect);
			bufferHeight = rect.bottom - rect.top;
			bufferWidth = rect.right - rect.left;

			int bufferSize = bufferHeight * bufferWidth * sizeof(unsigned int);
			// Dynamically allocate memory for bufferMemory
			if (bufferMemory)
				VirtualFree(bufferMemory, 0, MEM_RELEASE);
			bufferMemory = VirtualAlloc(0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			bufferBitmapInfo.bmiHeader.biSize = sizeof(bufferBitmapInfo.bmiHeader);
			bufferBitmapInfo.
			typedef struct tagBITMAPINFOHEADER {
				DWORD biSize;
				LONG  biWidth;
				LONG  biHeight;
				WORD  biPlanes;
				WORD  biBitCount;
				DWORD biCompression;
				DWORD biSizeImage;
				LONG  biXPelsPerMeter;
				LONG  biYPelsPerMeter;
				DWORD biClrUsed;
				DWORD biClrImportant;
			} BITMAPINFOHEADER, * LPBITMAPINFOHEADER, * PBITMAPINFOHEADER;
		} break;

		default: 
		{
			// This function performs the default action for the message, which varies by message type.
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
	return result;
}

// Main window
/* Parameters:
	1. hInstance - type: HINSTANCE
		A handle to the current instance of the application.
	2. hPrevInstance - type: HINSTANCE
		A handle to the previous instance of the application. This parameter is always NULL.
	3. lpCmdLine - type: LPSTR
		The command line for the application, excluding the program name.
	4. nShowCmd - type: int
		Controls how the window is to be shown.
Return value:
	If the function succeeds, terminating when it receives a WM_QUIT message, it should return the exit value contained in that message's wParam parameter. If the function terminates before entering the message loop, it should return zero.
*/
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	// Create window class
	WNDCLASS windowClass = {};
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpszClassName = L"Game Window Class";
	windowClass.lpfnWndProc = windowCallBack;

	// Register class
	RegisterClass(&windowClass);

	// Create Window
	HWND window = CreateWindow(windowClass.lpszClassName, L"First game!", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);


	// Main loop of the game
	while (running)
	{
		// Input (Keyboard, mouse, ..)
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		// Simulate


		// Render
		StretchDIBits(hdc, 0, 0, bufferWidth, bufferHeight, 0, 0, bufferWidth, bufferHeight, bufferMemory);
	}
}