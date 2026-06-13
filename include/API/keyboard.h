#ifndef __KEYBOARD9__
#define __KEYBOARD9__

#include "API/API.h"

#define KEYBOARDBUTTONS 39

extern API_Entity* keyboardWindow;
extern API_Entity* keyboardButton[KEYBOARDBUTTONS];
extern char* keyboardString;
extern int keyboardCursor, keyboardStrlen;
extern API_drawfunction keyboardReturn;


void setupKeyboard(char* string, u8 stringlen, API_drawfunction r);
void keyboardButtonPressed(API_Entity *e);
void showKeyboard();
void hideKeyboard();
void lockKeyboard();
void initKeyboard(u8 t);
void appearKeyboard(u8 t);
void disappearKeyboard(u8 t);

#endif
