#include "Main.h"

/*
OpenGLContext is a class designed to store all of your OpenGL functions and keep them
out of the way of your application logic. Here we have the ability to create an OpenGL
context on a given window and then render to that window.
*/

class OpenGLContext {
public:
	OpenGLContext(void); // Default constructor
	OpenGLContext(HWND hwnd); // Constructor for creating our context given a hwnd
	~OpenGLContext(void); // Destructor for cleaning up our application
	bool create30Context(HWND hwnd); // Creation of our OpenGl 3.x context
	void setupScene(void); // All scene information can be setup here
	void reshapeWindow(int w, int h); // method to get our window width and heigh on reshape
	void renderScene(void); // Render scene (display method from previous OpenGl tutorials)
private:
	int windowWidth; // Store the width of our window
	int windowHeight; // Store the height of our window
protected:
	HGLRC hrc; // Rendering context
	HDC hdc; // Device context
	HWND hwnd; // Window identified
};