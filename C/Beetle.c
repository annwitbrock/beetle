/* BEETLE.C -- 	Ann's beetle game program.
		Opens the windows */

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

/* define the window style */
#define WS_ANNWINSTYLE 	WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | \
			WS_THICKFRAME | WS_MINIMIZEBOX


#define WS_ANNCHILDSTYLE 	WS_CHILD | WS_VISIBLE
			
/* define size parameters */

#define W_BEETLE_XSIZE 210 
#define W_BEETLE_YSIZE 210
#define DICE_SIZE 40 
#define BEETLE_MARGIN (DICE_SIZE + 20)
#define X_POS (W_BEETLE_XSIZE + BEETLE_MARGIN)


/* make a brush colour (for backgrounds) */
#define PINK_BRUSH	RGB(255,193,255)
#define BLUE_BRUSH	RGB(0,0,255)
#define RED_BRUSH	RGB(255,0,0)
#define GREEN_BRUSH	RGB(0,255,0)
#define YELLOW_BRUSH	RGB(255,255,0)
#define MAGENTA_BRUSH	RGB(255,0,255)
#define CYAN_BRUSH	RGB(0,255,255)

/* declare procedures */

long FAR PASCAL WndProc(HWND, unsigned, WORD, LONG);
long FAR PASCAL ChildWndProc(HWND, unsigned, WORD, LONG);
long FAR PASCAL DicePushWndProc(HWND, unsigned, WORD, LONG);
void newgame();

/* define and initialise array of info on each player's game */

#define NPLAYS 2

struct Play{
short	Throw;
int	Cnt[7];
int	BCnt[7];
char	*bmParts[7];
HWND	hPlayer[7]; 
HWND	hDice, hPic;
} Player[2] = {
{1,
{0,1,2,1,2,6,1},
{0,0,0,0,0,0,0},
{"BLEGS1","HEAD1","EYES1","MOUTH1","ANTENN1","LEGS1","BODY1"},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
NULL,NULL},
{1,
{0,1,2,1,2,6,1},
{0,0,0,0,0,0,0},
{"BLEGS2","HEAD2","EYES2","MOUTH2","ANTENN2","LEGS2","BODY2"},
{NULL,NULL,NULL,NULL,NULL,NULL,NULL},
NULL,NULL}
};

/* global variable declarations and initialisation */

short	nTurn;

char 	szChildClass [] = "Beetle_Child";
char 	szDiceBtnClass [] = "Dice_Button";
char	*bmDice[] = {"DICE1","DICE2","DICE3","DICE4","DICE5","DICE6"};
char	*bmDiceBack = "DICEBACK";

HANDLE	hInst;

/****************************
*
*	WINMAIN
*
****************************/
int PASCAL WinMain(hInstance, hPrevInstance, lpszCmdLine, nCmdShow)
	HANDLE	hInstance, hPrevInstance;
	LPSTR	lpszCmdLine;
	int	nCmdShow;
{
static char 	szAppName [] = "beetle";
HWND		hWnd;
MSG		msg;
WNDCLASS	wndclass;

	if (hPrevInstance) return FALSE;
	/* parent window */
	wndclass.style 		= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc 	= WndProc;
	wndclass.cbClsExtra 	= 0;
	wndclass.cbWndExtra 	= 0;
	wndclass.hInstance 	= hInstance;
	wndclass.hIcon 		= LoadIcon(NULL, szAppName);
	wndclass.hCursor 	= LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground 	= GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName 	= NULL;
	wndclass.lpszClassName 	= szAppName;

	if(!RegisterClass(&wndclass))
		return FALSE;

	hInst = hInstance;

	/* child window */
	wndclass.lpfnWndProc 	= ChildWndProc;
	wndclass.cbWndExtra 	= 0;
	wndclass.hIcon 		= NULL;
	wndclass.lpszClassName 	= szChildClass;

	if(!RegisterClass(&wndclass))
		return FALSE;
	
	/* button */
	wndclass.lpfnWndProc 	= DicePushWndProc;
	wndclass.cbWndExtra 	= 0;
	wndclass.hIcon 		= NULL;
	wndclass.lpszClassName 	= szDiceBtnClass;

	if(!RegisterClass(&wndclass))
		return FALSE;
	


	/* (Main) Window Creation */

	/* MAIN Window */
	hWnd = CreateWindow (
		szAppName,			/* w class name */
		"BEETLE",			/* w caption 	*/
		WS_ANNWINSTYLE,			/* w style (def above) 	*/
		0,					/* init x pos 	*/
		0,					/* init y pos 	*/
		2 * X_POS + BEETLE_MARGIN,		/* init xsize 	*/
		W_BEETLE_YSIZE + 2 * BEETLE_MARGIN, /* init y size 	*/
		NULL,				/* parent w handle 	*/
		NULL,				/* w menu handle 	*/
		hInstance,			/* prog inst handle 	*/
		NULL);				/* create params	*/

	/* initialise a single game (for all players) */
	newgame();

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	

	while(GetMessage(&msg, NULL, 0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

/*
*	NEWGAME	:	Initialises global: nTurn; and 
*			Player[i] fields: Throw, Cnt[], BCnt[].
*			Call this BEFORE Show and Update Window.
*			Seeds the Random Number Generator.
*/
void newgame()
{
	int i;
	nTurn = 0;		/* Player 1 to start */
	for(i = 0; i <= 1; i++)
	{
	Player[i].Throw = 1;	/* anything but 6 ! */

/* What's left to get */
	Player[i].Cnt[0] = 0;
	Player[i].Cnt[1] = 1;	/* head */
	Player[i].Cnt[2] = 2;	/* eyes */
	Player[i].Cnt[3] = 1;	/* mouth */
	Player[i].Cnt[4] = 2;	/* antennae */
	Player[i].Cnt[5] = 6;	/* legs */
	Player[i].Cnt[6] = 1;	/* body */

/* What's already got */
	Player[i].BCnt[0] = 0;
	Player[i].BCnt[1] = 0;	/* head */
	Player[i].BCnt[2] = 0;	/* eyes */
	Player[i].BCnt[3] = 0;	/* mouth */
	Player[i].BCnt[4] = 0;	/* antennae */
	Player[i].BCnt[5] = 0;	/* legs */
	Player[i].BCnt[6] = 0;	/* body */

	}

	srand(LOWORD(GetCurrentTime()));
}


/*
*	OKMSGBOX
*/
void OkMsgBox(szCaption, szFormat)
	char *szCaption, *szFormat;
{
	char	szBuffer[256];
	char	*pArgs;

	pArgs = (char *) &szFormat + sizeof szFormat;
	vsprintf(szBuffer, szFormat, pArgs);
	MessageBox(NULL, szBuffer, szCaption, MB_OK);
}


/*
*	DRAWTEXTBOX
*/
void DrawTextBox(hWnd, xStart,yStart, szFormat)
	HWND hWnd;
	short xStart,yStart;
	char *szFormat;
{

	char	szBuffer[256];
	char	*pArgs;
	HDC	hDC;

	pArgs = (char *) &szFormat + sizeof szFormat;

	hDC = GetDC(hWnd);
		
	TextOut(hDC, xStart, yStart, szBuffer, 
		vsprintf(szBuffer, szFormat, pArgs));

	ReleaseDC(hWnd,hDC);
	ValidateRect(hWnd,NULL);

}


/*
*	DRAWBITMAP
*/
void DrawBitMap(hDC, xStart, yStart, bmID, dwROP)
	HDC	hDC;
	short	xStart, yStart;
	char	*bmID;
	DWORD	dwROP;
{
	BITMAP	bm;
	HDC	hMemDC;
	POINT	pt;
	HBITMAP	hBitmap;
	PAINTSTRUCT	ps;
	RECT	rect;

	hBitmap = LoadBitmap(hInst, bmID);

	hMemDC = CreateCompatibleDC(hDC);
	SelectObject(hMemDC,hBitmap);
	SetMapMode(hMemDC, GetMapMode (hDC));

	GetObject(hBitmap, sizeof (BITMAP), (LPSTR) &bm);
	pt.x = bm.bmWidth;
	pt.y = bm.bmHeight;
	DPtoLP(hDC,&pt,1);

	BitBlt(hDC, xStart, yStart, pt.x, pt.y, hMemDC, 0, 0, dwROP);

	DeleteDC(hMemDC);
	DeleteObject(hBitmap);
		
}


/*
*	WNDPROC
*/
long FAR PASCAL WndProc(hWnd, iMessage, wParam, lParam)
	HWND	hWnd;
	unsigned iMessage;
	WORD wParam;
	LONG lParam;
{
short	xBlock,yBlock, x, y, index;
int toss, i;

	switch	(iMessage)
	{
	case WM_CREATE:
		xBlock = max(50, LOWORD(lParam)/7);
		yBlock = max(50, HIWORD(lParam)/4);

		for (x = 0; x < 3; x++)
			for (y = 0; y < 2; y++)
			{
			Player[0].hPlayer[(y * 3) + x + 1] = CreateWindow
			(szChildClass, NULL,
			WS_ANNCHILDSTYLE,
				x * xBlock, (2 + y) * yBlock,
				xBlock, yBlock,
			hWnd, y * 3 + x + 1,
			hInst, NULL);
			
			Player[1].hPlayer[(y * 3) + x + 1] = CreateWindow
			(szChildClass, NULL,
			WS_ANNCHILDSTYLE,
				(4 + x) * xBlock,
				(2 + y) * yBlock,
				xBlock, yBlock,
			hWnd, y * 3 + x + 9,
			hInst, NULL);

			}
		Player[0].hDice = CreateWindow
		(szDiceBtnClass,"Dice1",
		WS_ANNCHILDSTYLE | BS_PUSHBUTTON,
		2 * xBlock + (xBlock - DICE_SIZE) / 2, yBlock - DICE_SIZE / 2,
		DICE_SIZE,DICE_SIZE,
		hWnd, 7 ,
		hInst,NULL);

		Player[1].hDice = CreateWindow
		(szDiceBtnClass,"Dice2",
		WS_ANNCHILDSTYLE | BS_PUSHBUTTON,
		4 * xBlock + (xBlock - DICE_SIZE) / 2, yBlock - DICE_SIZE / 2,
		DICE_SIZE,DICE_SIZE,
		hWnd, 15 ,
		hInst,NULL);


		Player[0].hPic = CreateWindow
		(szChildClass,NULL,
		WS_ANNCHILDSTYLE,
		0, 0,
		2 * xBlock,2 * yBlock,
		hWnd, 8 ,
		hInst,NULL);

		Player[1].hPic = CreateWindow
		(szChildClass,NULL,
		WS_ANNCHILDSTYLE,
		5 * xBlock, 0,
		2 * xBlock,2 * yBlock,
		hWnd, 16,
		hInst,NULL);

		break;

	case WM_SIZE:
		xBlock = max(50, LOWORD(lParam)/7);
		yBlock = max(50, HIWORD(lParam)/4);

		for (x = 0; x < 3; x++)
			for (y = 0; y < 2; y++)
			{
				MoveWindow(Player[0].hPlayer[(y * 3) + x + 1],	
				x * xBlock, (2 + y) * yBlock,
				xBlock,yBlock,TRUE);

				MoveWindow(Player[1].hPlayer[(y * 3) + x + 1],	
				(4 + x) * xBlock,
				(2 + y) * yBlock,
				xBlock,yBlock,TRUE);
			}
		MoveWindow(Player[0].hDice,	
		2 * xBlock + (xBlock - DICE_SIZE) / 2, yBlock - DICE_SIZE / 2,
		DICE_SIZE,DICE_SIZE,TRUE);

		MoveWindow(Player[1].hDice,	
		4 * xBlock + (xBlock - DICE_SIZE) / 2, yBlock - DICE_SIZE / 2,
		DICE_SIZE,DICE_SIZE,TRUE);

		MoveWindow(Player[0].hPic,	
		0, 0,
		2 * xBlock,2 * yBlock,TRUE);

		MoveWindow(Player[1].hPic,	
		5 * xBlock, 0,
		2 * xBlock,2 * yBlock,TRUE);
		
		break;
		
	case WM_COMMAND:
		toss = rand()%6 + 1;
		if (LOWORD(lParam) != Player[nTurn].hDice)
			MessageBeep(0);
		else 
		{
			index = nTurn;
			Player[index].Throw = toss;
			if (Player[index].Cnt[toss] < 1) nTurn = (nTurn + 1) % NPLAYS;
			else
			switch (toss)
			{
			case 6:
				if (Player[index].Cnt[6] > 0)
				{
					Player[index].Cnt[6]-- ;
					Player[index].BCnt[6]++ ;
			InvalidateRect(Player[index].hPlayer[toss],NULL,TRUE);
			InvalidateRect(Player[index].hPic,NULL,FALSE);
				}
				nTurn = (nTurn + 1) % NPLAYS;
				break;
			case 1:
				if ((	Player[index].Cnt[6] < 1) && 
					(Player[index].Cnt[1] > 0))
				{
					Player[index].Cnt[1]-- ;
					Player[index].BCnt[1]++ ;
			InvalidateRect(Player[index].hPlayer[toss],NULL,TRUE);
			InvalidateRect(Player[index].hPic,NULL,FALSE);
				}
				nTurn = (nTurn + 1) % NPLAYS;
				break;
			default:
				if (	(Player[index].Cnt[6] < 1) && 
					(Player[index].Cnt[1] < 1))
				{
					if (Player[index].Cnt[toss] > 0)
					{
						Player[index].Cnt[toss]-- ;
						Player[index].BCnt[toss]++ ;
			InvalidateRect(Player[index].hPlayer[toss],NULL,TRUE);
			InvalidateRect(Player[index].hPic,NULL,FALSE);
					}
				}
				else nTurn = (nTurn + 1) % NPLAYS;
			}
			InvalidateRect(Player[index].hDice,NULL,TRUE);

			for(i = 2;((Player[index].Cnt[i] < 1) && (i < 6)); i++);
			if (i >= 6)
				OkMsgBox( "Winner", "Player %d",index + 1);
		}
		break;

	case WM_LBUTTONDOWN:
		MessageBeep(0);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default: return DefWindowProc(hWnd, iMessage, wParam, lParam);
	}
return 0L;
}


/*
*	CHILDWNDPROC
*/
long FAR PASCAL ChildWndProc(hWnd, iMessage, wParam, lParam)
	HWND	hWnd;
	unsigned iMessage;
	WORD wParam;
	LONG lParam;
{
short 	i,j,xpos,ypos,index;
HDC	hDC;
PAINTSTRUCT	ps;
RECT	rect;

	switch (iMessage)
	{

	case WM_LBUTTONDOWN:
		MessageBeep(0);
		break;

	case WM_PAINT:
		hDC = BeginPaint(hWnd,&ps);
		GetClientRect(hWnd,&rect);
		Rectangle(hDC,0,0,rect.right,rect.bottom);	
		for(i = 1; i <= 6; i++)
		{
			if (hWnd == Player[0].hPlayer[i])
			{
				for (j = 1; j <= Player[0].Cnt[i]; j++)
				DrawBitmap(hDC,((j - 1) * 10) + 5,5, Player[0].bmParts[i],SRCAND);
				DrawTextBox(hWnd, 5, 40, "%d :%d",i,Player[0].Cnt[i]);
				EndPaint(hWnd,&ps);
				break;
			}
			if (hWnd == Player[1].hPlayer[i])
			{
				for (j = 1; j <= Player[1].Cnt[i]; j++)
				DrawBitmap(hDC,((j -1) * 10) + 5,5,  Player[1].bmParts[i],SRCAND);
				DrawTextBox(hWnd, 5, 40, "%d :%d",i,Player[1].Cnt[i]);
				EndPaint(hWnd,&ps);
				break;
			}
		}	
		for (index = 0; 
		    ((hWnd != Player[index].hPic) && (index <= NPLAYS));
		    index++);
		
		if (hWnd == Player[index].hPic)
		{
			if(Player[index].BCnt[5] > 0)
			{
				for(j = 1; j <= Player[index].BCnt[5]; j++)
				{
					if (j <= 3)
					DrawBitmap(	hDC, 
					30 + (j * 8) - 16,
					48 - 3,
					Player[index].bmParts[0], SRCAND);

					else
					DrawBitmap(	hDC, 
					30 + ((j - 3) * 8),
					48,
					Player[index].bmParts[5], SRCAND);
				}
			}

			if(Player[index].BCnt[6] > 0)
			DrawBitmap(hDC, 40,40,Player[index].bmParts[6],SRCAND);

			if(Player[index].BCnt[1] > 0)
			DrawBitmap(hDC, 75,40,Player[index].bmParts[1],SRCAND);
			
			if(Player[index].BCnt[2] > 0)
			{
				for(j = 1; j <= Player[index].BCnt[2]; j++)
			DrawBitmap(hDC, 81, 66 - (j * 6),Player[index].bmParts[2],SRCAND);
			}		

			if(Player[index].BCnt[3] > 0)
			DrawBitmap(hDC, 85, 40,Player[index].bmParts[3],SRCAND);

			if(Player[index].BCnt[4] > 0)
			{
				for(j = 1; j <= Player[index].BCnt[4]; j++)
			DrawBitmap(hDC, 75 - (j * 2) , 38 + (j * 5),Player[index].bmParts[4],SRCAND);
			}


			DrawTextBox(Player[index].hPic, 10, 120, 
				"%d %d %d %d %d %d", 
				Player[index].BCnt[1],Player[index].BCnt[2],
				Player[index].BCnt[3],Player[index].BCnt[4],
				Player[index].BCnt[5],Player[index].BCnt[6]);
		}

		EndPaint(hWnd,&ps);
		break;

	default:
		return DefWindowProc(hWnd, iMessage, wParam, lParam);
	}

return 0L;
}


/*
*	DICEPUSHWNDPROC
*/
long FAR PASCAL DicePushWndProc(hWnd, iMessage, wParam, lParam)
	HWND	hWnd;
	unsigned iMessage;
	WORD wParam;
	LONG lParam;
{
char	szText[7];
HBRUSH	hBrush;
HDC	hDC;
PAINTSTRUCT	ps;
RECT	rect;
HBITMAP	hBitmap;

	switch (iMessage)
	{

	case WM_PAINT:
		hDC = BeginPaint(hWnd,&ps);
		DrawBitmap(hDC,0,0,  (hWnd == Player[0].hDice) ? 
			bmDice[Player[0].Throw - 1] : bmDice[Player[1].Throw -1],SRCCOPY);
		EndPaint(hWnd,&ps);
		break;

	case WM_LBUTTONUP:
		SendMessage(GetParent (hWnd), WM_COMMAND,
			GetWindowWord(hWnd,GWW_ID),(LONG)hWnd);
		break;

	default:
		return DefWindowProc(hWnd, iMessage, wParam, lParam);
	}
return 0L;
}

/* EOF */
