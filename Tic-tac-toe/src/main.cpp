#include <iostream>
#include <cstring>
#include <cstdlib>
#include <time.h>
using namespace std;
char matrice[3][3] = { {'1','2','3'}, {'4', '5', '6'}, {'7', '8', '9'} };
void Startgame();
void SinglePlayer();
void TwoPlayers();
void Display();
int CheckWin();
void Bot();
int minimax(int maxplayer);
int main()
{
	Startgame();
	return 0;
}
void Startgame()
{
	char a;
	bool ok = false;
	while (ok == false)
	{
		cout << "Enter 1 to play against the Bot; \n Enter 2 to play with a friend \n Input:";
		cin >> a;
		if (a == '1')
		{
			system("cls");
			SinglePlayer();
			ok = true;
		}
		else if (a == '2')
		{
			system("cls");
			TwoPlayers();
			ok = true;
		}
		else
			cout << "Enter a real value:";

	}
}
void SinglePlayer()
{
	system("cls");
	bool ok1 = false;
	int diff;
	while (ok1 == false)
	{
		cout << "Select difficulty(from 1 to 3, from the easiest to the hardest): ";
		cin >> diff;
		if (diff >= 1 && diff <= 3)
		{
			ok1 = true;
		}
		else
			cout << "\nEnter a real value!\n";
	}
	while (CheckWin() == 10)
	{
		Display();
		int x = -1, ok = 0;
		while (ok == 0)
		{
			cout << "Enter a position(playing as X): ";
			cin >> x;
			if (matrice[(x - 1) / 3][(x - 1) % 3] >= '1' && matrice[(x - 1) / 3][(x - 1) % 3] <= '9')
			{
				matrice[(x - 1) / 3][(x - 1) % 3] = 'X';
				ok = 1;
			}
			else
				cout << "Enter a real value!\n";
		}
		if (CheckWin() == 10)
		{
			srand((unsigned)time(0));
			if (diff == 3)
				Bot();
			if (diff == 2)
				if (rand() % 100 < 50)
					Bot();
				else
				{
					while (diff == 2)
					{
						int a = rand() % 3, b = rand() % 3;
						if (matrice[a][b] >= '1' && matrice[a][b] <= '9')
						{
							matrice[a][b] = 'O';
							break;
						}
					}
				}
			if (diff == 1)
				if (rand() % 100 < 25)
					Bot();
				else
				{
					while (diff == 1)
					{
						int a = rand() % 3, b = rand() % 3;
						if (matrice[a][b] >= '1' && matrice[a][b] <= '9')
						{
							matrice[a][b] = 'O';
							break;
						}
					}
				}
		}
		if (CheckWin() == -1)
		{
			Display();
			cout << "You won!";
		}
		if (CheckWin() == 0)
		{
			Display();
			cout << "Tie!";
		}
		if (CheckWin() == 1)
		{
			Display();
			cout << "Bot won!";
		}
	}
}
void Bot()
{
	int x = 0, y = 0, maxim = -1000;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (matrice[i][j] >= '1' && matrice[i][j] <= '9')
			{
				char aux = matrice[i][j];
				matrice[i][j] = 'O';
				int rez = minimax(0);
				if (maxim < rez)
				{
					maxim = rez;
					x = i;
					y = j;
				}
				matrice[i][j] = aux;
			}
	matrice[x][y] = 'O';
}
int minimax(int maxplayer)
{
	if (CheckWin() != 10)
		return CheckWin();
	if (maxplayer)
	{
		int maxeval = -1000;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (matrice[i][j] >= '1' && matrice[i][j] <= '9')
				{
					char aux = matrice[i][j];
					matrice[i][j] = 'O';
					int rez = minimax(0);
					maxeval = max(rez, maxeval);
					matrice[i][j] = aux;
				}
		return maxeval;
	}
	else
	{
		int mineval = 1000;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (matrice[i][j] >= '1' && matrice[i][j] <= '9')
				{
					char aux = matrice[i][j];
					matrice[i][j] = 'X';
					int rez = minimax(1);
					mineval = min(rez, mineval);
					matrice[i][j] = aux;
				}
		return mineval;
	}
}
void Display()
{
	system("cls");
	cout << matrice[0][0] << " | " << matrice[0][1] << " | " << matrice[0][2] << endl;
	cout << "---------" << endl;
	cout << matrice[1][0] << " | " << matrice[1][1] << " | " << matrice[1][2] << endl;
	cout << "---------" << endl;
	cout << matrice[2][0] << " | " << matrice[2][1] << " | " << matrice[2][2] << endl;
}
int CheckWin()
{
	for (int i = 0; i < 3; i++)
	{
		if (matrice[i][0] == matrice[i][1] && matrice[i][0] == matrice[i][2])
			if (matrice[i][0] == 'X')
				return -1;
			else
				return 1;
		if (matrice[0][i] == matrice[1][i] && matrice[0][i] == matrice[2][i])
			if (matrice[0][i] == 'X')
				return -1;
			else
				return 1;
	}
	if (matrice[0][0] == matrice[1][1] && matrice[0][0] == matrice[2][2])
		if (matrice[0][0] == 'X')
			return -1;
		else
			return 1;
	if (matrice[0][2] == matrice[1][1] && matrice[0][2] == matrice[2][0])
		if (matrice[0][2] == 'X')
			return -1;
		else
			return 1;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (matrice[i][j] >= '1' && matrice[i][j] <= '9')
				return 10;
	return 0;
}
void TwoPlayers()
{
	string nm1, nm2;
	cout << "First player name: "; cin >> nm1;
	cout << "Second player name : "; cin >> nm2;
	while (CheckWin() == 10)
	{
		Display();
		int x = -1, ok = 0;
		while (ok == 0)
		{
			cout << nm1 << " enter a position(playing as X): ";
			cin >> x;
			if (matrice[(x - 1) / 3][(x - 1) % 3] >= '1' && matrice[(x - 1) / 3][(x - 1) % 3] <= '9')
				ok = 1;
			else
				cout << "Enter a real value!\n";
		}
		matrice[(x - 1) / 3][(x - 1) % 3] = 'X';
		if (CheckWin() == -1)
		{
			Display();
			cout << nm1 << " won!";
		}
		if (CheckWin() == 0)
		{
			Display();
			cout << "Tie!";
		}
		if (CheckWin() == 1)
		{
			Display();
			cout << nm2 << " won!";
		}
		if (CheckWin() == 10)
		{
			Display();
			ok = 0;
			while (ok == 0)
			{
				cout << nm2 << " enter a position (playing as O): ";
				cin >> x;
				if (matrice[(x - 1) / 3][(x - 1) % 3] >= '1' && matrice[(x - 1) / 3][(x - 1) % 3] <= '9')
					ok = 1;
				else
					cout << "Enter a real value!\n";
			}
			matrice[(x - 1) / 3][(x - 1) % 3] = 'O';
			if (CheckWin() == -1)
			{
				Display();
				cout << nm1 << " won!";
			}
			if (CheckWin() == 0)
			{
				Display();
				cout << "Tie!";
			}
			if (CheckWin() == 1)
			{
				Display();
				cout << nm2 << " won!";
			}
		}
	}
}