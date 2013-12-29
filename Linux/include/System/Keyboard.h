#ifndef __KBD_H__
#define __KBD_H__



#define kbdReturnKey		linefeedChr
#define kbdTabKey			tabChr
#define kbdBackspaceKey	backspaceChr
#define kbdShiftKey		2
#define kbdCapsKey		1
#define kbdNoKey			-1


typedef enum 
	{
	kbdAlpha = 0, 
	kbdNumbersAndPunc = 1, 
	kbdAccent = 2,
	kbdDefault = 0xff		// based on graffiti mode (usually alphaKeyboard)
	} KeyboardType;

#endif // __KBD_H__
