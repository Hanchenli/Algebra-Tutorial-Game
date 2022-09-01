#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

extern void RecalculateSpeedX_Y(void);
extern void KeyAction(unsigned char key, int x, int y);
extern void SpecialKeyAction(int key, int x, int y);

#endif //_KEYBOARD_H_