#ifndef __CLIPBOARD_H__
#define __CLIPBOARD_H__

// Clipboard standard formats
enum clipboardFormats { clipboardText, clipboardInk, clipboardBitmap };

typedef enum clipboardFormats ClipboardFormatType;

typedef struct {
	VoidHand		item;
	Word			length;
} ClipboardItem;


#endif // __CLIPBOARD_H__
