#ifndef INPUTCLASS_H_INCLUDED
#define INPUTCLASS_H_INCLUDED

class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

private:
	bool m_keys[256];
};

#endif // INPUTCLASS_H_INCLUDED
