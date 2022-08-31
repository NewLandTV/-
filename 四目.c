#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

#define CONSOLE_WIDTH 42
#define CONSOLE_HEIGHT 27
#define BOARD_WIDTH 7
#define BOARD_HEIGHT 6
#define BOARD_RED 1
#define BOARD_YELLOW 2

int board[BOARD_WIDTH * BOARD_HEIGHT] =
{
	0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0
};

void Init();
void DrawSelectNumbers();
void DrawBoard();
void SelectRed();
void SelectYellow();
void CheckWinner();
int PushInBoard(int x, int boardColor);
char GetBoardMark(int value);
void Gotoxy(int x, int y);
int Input();

int main(void)
{
	int turn;
	
	Init();
	DrawSelectNumbers();
	
	for (turn = 0; turn < BOARD_WIDTH * BOARD_HEIGHT; turn++)
	{
		DrawBoard();
		SelectRed();
		DrawBoard();
		CheckWinner();
		SelectYellow();
		DrawBoard();
		CheckWinner();
	}
	
	return 0;
}

void Init()
{
	system("title ÞÌÙÍ");
	system("mode con cols=42 lines=27");
	
	CONSOLE_CURSOR_INFO consoleCursorInfo;
	
	consoleCursorInfo.bVisible = 0;
	consoleCursorInfo.dwSize = 1;
	
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
}

void DrawSelectNumbers()
{
	int i;
	
	for (i = 1; i <= BOARD_WIDTH; i++)
	{
		Gotoxy((CONSOLE_WIDTH >> 2) + (i * 3) - 2, 2);
		printf("%d", i);
	}
}

void DrawBoard()
{
	int x;
	int y;
	
	for (y = 0; y < BOARD_HEIGHT; y++)
	{
		for (x = 0; x < BOARD_WIDTH; x++)
		{
			Gotoxy((CONSOLE_WIDTH >> 2) + (x * 3) - 1, (y * 2) + 5);
			printf("¦¢ %c¦¢", GetBoardMark(board[x + BOARD_WIDTH * y]));
			Gotoxy((CONSOLE_WIDTH >> 2) + (x * 3) - 1, (y * 2) + 6);
			printf("¦¢  ¦¢");
		}
	}
}

void SelectRed()
{
	int key;
	
	while ((key = Input()) < 49 || key > 55);
	
	if (PushInBoard(key - 50, BOARD_RED))
	{
		SelectRed();
	}
}

void SelectYellow()
{
	int key;
	
	while ((key = Input()) < 49 || key > 55);
	
	if (PushInBoard(key - 50, BOARD_YELLOW))
	{
		SelectYellow();
	}
}

void CheckWinner()
{
	int x;
	int y;
	
	for (y = 0; y < BOARD_HEIGHT; y++)
	{
		for (x = 0; x < BOARD_WIDTH; x++)
		{
			if (board[x + BOARD_WIDTH * y] == BOARD_RED && ((board[x + 1 + BOARD_WIDTH * y] == BOARD_RED && board[x + 2 + BOARD_WIDTH * y] == BOARD_RED && board[x + 3 + BOARD_WIDTH * y] == BOARD_RED) || (board[x + BOARD_WIDTH * (y + 1)] == BOARD_RED && board[x + BOARD_WIDTH * (y + 2)] == BOARD_RED && board[x + BOARD_WIDTH * (y + 3)] == BOARD_RED) || (board[x + 1 + BOARD_WIDTH * (y + 1)] == BOARD_RED && board[x + 2 + BOARD_WIDTH * (y + 2)] == BOARD_RED && board[x + 3 + BOARD_WIDTH * (y + 3)] == BOARD_RED) || (board[x - 1 + BOARD_WIDTH * (y + 1)] == BOARD_RED && board[x - 2 + BOARD_WIDTH * (y + 2)] == BOARD_RED && board[x - 3 + BOARD_WIDTH * (y + 3)] == BOARD_RED)))
			{
				Gotoxy((CONSOLE_WIDTH >> 1) - 4, 10);
				printf("Red win!");
				exit(1);
			}
			
			if (board[x + BOARD_WIDTH * y] == BOARD_YELLOW && ((board[x + 1 + BOARD_WIDTH * y] == BOARD_YELLOW && board[x + 2 + BOARD_WIDTH * y] == BOARD_YELLOW && board[x + 3 + BOARD_WIDTH * y] == BOARD_YELLOW) || (board[x + BOARD_WIDTH * (y + 1)] == BOARD_YELLOW && board[x + BOARD_WIDTH * (y + 2)] == BOARD_YELLOW && board[x + BOARD_WIDTH * (y + 3)] == BOARD_YELLOW) || (board[x + 1 + BOARD_WIDTH * (y + 1)] == BOARD_YELLOW && board[x + 2+ BOARD_WIDTH * (y + 2)] == BOARD_YELLOW && board[x + 3 + BOARD_WIDTH * (y + 3)] == BOARD_YELLOW) || (board[x - 1 + BOARD_WIDTH * (y + 1)] == BOARD_YELLOW && board[x - 2 + BOARD_WIDTH * (y + 2)] == BOARD_YELLOW && board[x - 3 + BOARD_WIDTH * (y + 3)] == BOARD_YELLOW)))
			{
				Gotoxy((CONSOLE_WIDTH >> 1) - 6, 10);
				printf("Yellow win!");
				exit(1);
			}
		}
	}
}

int PushInBoard(int x, int boardColor)
{
	int y;
	
	for (y = BOARD_HEIGHT; y > 0; x--, y--)
	{
		if (board[x + BOARD_HEIGHT * y] == 0)
		{
			board[x + BOARD_HEIGHT * y] = boardColor;
			
			return 0;
		}
	}
	
	return 1;
}

char GetBoardMark(int value)
{
	if (value == BOARD_RED)
	{
		return 'R';
	}
	
	if (value == BOARD_YELLOW)
	{
		return 'Y';
	}
	
	return ' ';
}

void Gotoxy(int x, int y)
{
	COORD position = { x, y };
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

int Input()
{
	return _kbhit() ? _getch() : -2;
}
