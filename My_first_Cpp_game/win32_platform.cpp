/* LIBRARY */
#include "utils.h"
#include "variables.h"
#include <windows.h>
#include "RenderState.h"
#include "renderer.h"
#include "platformCommon.h"
#include "game.h"

/* MACROS */
#define MAKEINTRESOURCEW(i) ((LPWSTR)((ULONG_PTR)((WORD)(i))))
#define processButton(b, vk)\
case vk : {\
	input.buttons[b].changed = isDown != input.buttons[b].isDown; \
	input.buttons[b].isDown = isDown; \
}	break;

/*WARNING: carefull whenever you change this variable*/
//=======================//
bool running = true;
//=====================//
	

/*
Description: This callback function is the way window use to pass messages down to us. Whenever sonething happens to window like receives user input, close window, changing the size or minimize, ... the window will receive a message for this callback function.
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
			VirtualFree(renderState.memory, 0, MEM_RELEASE);
			running = false;
			renderState.memory = nullptr;
		} break;

		case WM_SIZE: 
		{
			RECT rect;
			GetClientRect(hwnd, &rect);
			renderState.width = rect.right - rect.left;
			renderState.height = rect.bottom - rect.top;

			int bufferSize = renderState.height * renderState.width * sizeof(unsigned int);
			// Dynamically allocate memory for bufferMemory
			if (renderState.memory)
				VirtualFree(renderState.memory, 0, MEM_RELEASE);
			renderState.memory = VirtualAlloc(0, bufferSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			renderState.bitmapInfo.bmiHeader.biSize = sizeof(renderState.bitmapInfo.bmiHeader);
			renderState.bitmapInfo.bmiHeader.biWidth = renderState.width;
			renderState.bitmapInfo.bmiHeader.biHeight = renderState.height;
			renderState.bitmapInfo.bmiHeader.biPlanes = 1;
			renderState.bitmapInfo.bmiHeader.biBitCount = 32;
			renderState.bitmapInfo.bmiHeader.biCompression = BI_RGB;

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
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{	
	
	// Create window class
	WNDCLASS windowClass = {};
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpszClassName = L"Game Window Class";
	windowClass.lpfnWndProc = windowCallBack;
	windowClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE("IDI_ICON1"));

	// Register class
	RegisterClass(&windowClass);

	// Create Window
	HWND window = CreateWindow(windowClass.lpszClassName, L"2048", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	// Array of input
	Input input = {};

	// Manipulate frame per second
	double deltaTime = 0.0166667f; // 60 FPS
	LARGE_INTEGER frameBeginTime;
	QueryPerformanceCounter(&frameBeginTime);
	double performanceFrequency;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performanceFrequency = (double)perf.QuadPart;
	}
	
	// initialize Game class
	__init__();

	// Main loop of the game
	while (running)
	{
		// Input (Keyboard, mouse, ..)
		MSG message;

		// When start a new frame, restart these buttons.
		for (int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			switch (message.message) 
			{
				case WM_KEYUP:
				case WM_KEYDOWN: 
				{
					u32 vkCode = (u32)message.wParam;
					bool isDown = ((message.lParam & (1 << 31)) == 0);
				
					switch (vkCode)
					{
						processButton(BUTTON_UP, VK_UP);
						processButton(BUTTON_DOWN, VK_DOWN);
						processButton(BUTTON_LEFT, VK_LEFT);
						processButton(BUTTON_RIGHT, VK_RIGHT);
						processButton(BUTTON_ENTER, VK_RETURN);
					}
				}
				default: 
				{
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
			}
			
		}

		// Simulate
		stimulateGame(&input, deltaTime);

		// Render
		StretchDIBits(hdc, 0, 0, renderState.width, renderState.height, 0, 0, renderState.width, renderState.height, renderState.memory, &renderState.bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

		LARGE_INTEGER frameEndTime;
		QueryPerformanceCounter(&frameEndTime);
		deltaTime = (double)(frameBeginTime.QuadPart - frameEndTime.QuadPart) / performanceFrequency;
		frameBeginTime = frameEndTime;
	}


}