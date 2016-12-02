#ifndef INPUTCLASS_H
#define INPUTCLASS_H

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

static const int MOUSE_LEFT = 0;
static const int MOUSE_RIGHT = 1;

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	bool IsEscapePressed();
	void GetMouseLocation(int&, int&);
	void GetMouselXY(int&, int&);
	bool IsKeyPressed(int);
	bool IsMouseButtonPressed(int);
	bool IsMouseMoved();

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;
	DIMOUSESTATE m_mouseLastState;

	int m_screenWidth, m_screenHeight;
	int m_mouseX, m_mouseY;
};

#endif // INPUTCLASS_H
