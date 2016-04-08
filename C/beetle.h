/* declare procedures */
long FAR PASCAL WndProc( HWND, unsigned, WPARAM, LPARAM); //HWND, unsigned, WORD, LONG
long FAR PASCAL ChildWndProc( HWND, unsigned, WPARAM, LPARAM); //HWND, unsigned, WORD, LONG
long FAR PASCAL DicePushWndProc( HWND, unsigned, WPARAM, LPARAM); //HWND, unsigned, WORD, LONG
int PASCAL WinMain( HINSTANCE, HINSTANCE, LPSTR, int);

void newgame();
void OkMsgBox( char *, const char *, ...);
void DrawTextBox( HWND, short, short, const char *f, ...);
void DrawBitmap( HDC, short, short, char  *, DWORD);

/* EOF */