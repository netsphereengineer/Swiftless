#include "main.h"  
#include "opengl_3.h"  

OpenGLContext openglContext; // Our OpenGL Context class  

bool running = true; // Whether or not the application is currently running  

HINSTANCE hInstance; // The HINSTANCE of this application  
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Standard window callback

/**
WndProc is a standard method used in Win32 programming for handling Window messages. Here we
handle our window resizing and tell our OpenGLContext the new window size.
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_SIZE: // If our window is resizing  
		{
			openglContext.reshapeWindow(LOWORD(lParam), HIWORD(lParam)); // Send the new window size to our OpenGLContext  
			break;
		}

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

bool createWindow(LPCWSTR title, int width, int height) {
	WNDCLASS windowClass;
	HWND hWnd;
	DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

	hInstance = GetModuleHandle(NULL);

	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc = (WNDPROC)WndProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = title;

	if (!RegisterClass(&windowClass)) {
		return false;
	}

	hWnd = CreateWindowEx(dwExStyle, title, title, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, width, height, NULL, NULL, hInstance, NULL);

	openglContext.create30Context(hWnd); // Create our OpenGL context on the given window we just created  

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	return true;
}


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR    lpCmdLine,
	int       nCmdShow) {
	MSG msg;

	/**
	The following 6 lines of code do conversion between char arrays and LPCWSTR variables
	which are used in the Windows API.
	*/
	char *orig = "OpenGL 3 Project"; // Our windows title  
	size_t origsize = strlen(orig) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, orig, _TRUNCATE);


	createWindow(wcstring, 500, 500); // Create our OpenGL window  

	openglContext.setupScene(); // Setup our OpenGL scene 

	/**
	This is our main loop, it continues for as long as running is true
	*/
	while (running)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { // If we have a message to process, process it  
			if (msg.message == WM_QUIT) {
				running = false; // Set running to false if we have a message to quit  
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else { // If we don't have a message to process  
			openglContext.renderScene(); // Render our scene (which also handles swapping of buffers)  
		}
	}

	return (int)msg.wParam;
}