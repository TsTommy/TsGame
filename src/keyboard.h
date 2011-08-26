#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

class keyboard
{
public:
	void on_frame();

private:
	Uint8* keys_;
};

#endif //KEYBOARD_H_INCLUDED
