#include<bits/stdc++.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

using namespace std;

int board[4][4];

void welcome()
{
	cout<<"\t\t\t\t\t\t\t2048";
	cout<<"\n\t\t\t\t\t\t      WELCOME!";
	cout<<"\n\t\t\t\t\t     Press any key to continue...";
	getch();
}

int random()
{
	unsigned int sd;
	time_t t;
	sd = (unsigned)(time(&t));
	srand(sd);
	return (rand() % 16);	
}

void initBoard()
{
	for(int i=0; i<4; ++i)
		for(int j=0; j<4; ++j)
			board[i][j] = 1;
}

void pntBoard()
{
	cout<<"\nPrinting board:\n";
	for(int i=0; i<4; ++i)
	{
		for(int j=0; j<4; ++j)
			if(board[i][j] == 1)
				cout<<"_ ";
			else
				cout<<board[i][j]<<" ";
		cout<<endl;
	}	
}

bool putInBoard(int r)
{
	//cout<<r;
	int column = r%4, row = r/4;
	if(board[row][column] != 1)
		return false;
	
	board[row][column] = 2;
	return true;
}

void shiftPieces(int n)
{
	int column = n%4, row = n/4, val_n = board[row][column];
	int val_up, val_down, val_left, val_right;
	
	switch(column)
	{
		case 0:
			val_left = 0;
			val_right = board[row][column+1];
			break;
		case 1:
		case 2:
			val_left = board[row][column-1];
			val_right = board[row][column+1];
			break;
		case 3:
			val_left = board[row][column-1];
			val_right = 0;
			break;
	}
	
	switch(row)
	{
		case 0:
			val_up = 0;
			val_down = board[row+1][column];
			break;
		case 1:
		case 2:
			val_up = board[row-1][column];
			val_down = board[row+1][column];
			break;
		case 3:
			val_up = board[row-1][column];
			val_down = 0;
			break;
	}
	
	if(val_n == val_up && val_n%2 == 0)
	{
		board[row][column] *= 2;
		board[row-1][column] = 1;
	}
	if(val_n == val_down && val_n%2 == 0)
	{
		board[row+1][column] *= 2;
		board[row][column] = 1;		
	}
	if(val_n == val_left && val_n%2 == 0)
	{
		board[row][column] *= 2;
		board[row][column] = 1;
	}
	if(val_n == val_right && val_n%2 == 0)
	{
		board[row][column+1] *= 2;
		board[row][column] = 1;
	}	
}

int checkResult(int r)
{
	for(int i=0; i<4; ++i)
		for(int j=0; j<4; ++j)
			if(board[i][j] == 2048)
				return 5;
				
	for(int i=0; i<16; ++i)
		shiftPieces(i);
		
	for(int i=0; i<4; ++i)
		for(int j=0; j<4; ++j)
			if(board[i][j] == 2048)
				return 5;
		
	for(int i=0; i<4; ++i)
		for(int j=0; j<4; ++j)
		{		
			if(board[i][j] ==  1)
				return 1;
		}
	
	return 0;
}

int main()
{
	welcome();
	initBoard();
	int result, steps = 0, r;
	do
	{	
		r = random();
		if(putInBoard(r))
		{
			++steps;
			pntBoard();
			result = checkResult(r);
			if(result == 5)
				break;
			cout<<"Press any key to continue...";
			getch();
			cout<<endl;
		}
	}
	while(result);
	
	if(result)
		cout<<"\n\n\n\n\n\t\t\t\t\t\t\tWON!";
	else
		cout<<"\n\n\n\n\n\t\t\t\t\t\t\tTIE!";
	pntBoard();
	cout<<"\nNo. of steps required to complete the game: "<<steps<<endl;
	getch();
	return 0;
}

