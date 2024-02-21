#include <iostream>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

fstream file;        //Creating File 

struct Player        //Declaring structure for both players
{
	string name;
	char symbol;
};

// This function will display board

void displayBoard(char board[3][3])     
{
	for (int i = 0; i < 3; i++)
	{
		cout << "\t";
		for (int j = 0; j < 3; j++)
		{
			cout << board[i][j] << "  ";
		}
		cout << endl;
	}
}

//This function will replace specific cell number with symbols 

void replacing(char board[3][3], char symbol, char cellno)  
{
    for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (cellno == board[i][j])
			{
				board[i][j] = symbol;
			}
		}
	}
	displayBoard(board);    //Calling display function after replacing cell number with symbol
}

//This function will ask user whether he wants to play single mode or VS mode

int modeOfGame()
{
	int mode;
	cout << "Do you want play player VS computer mode or forfeit:" << endl;
	cout << "Press 1 for player VS computer mode: " << endl;
	cout << "Press 2 to forfeit:" << endl;
	cin >> mode;
	 if  (mode == 1)
	 {
		 return mode;
	 }
	 else if (mode == 2)
	 {
		 return mode;
	 }
	 else {
		 cout << "Invalid choice\n";
		 cout << "Enter Again: ";
		 cin >> mode;
		 return mode;
	 }
}

//This function will check that user has entered the accurate cell

int validCellNo(char board[3][3], char cellNo, Player player) 
{  
	int row, col;
	row = ceil((double)(cellNo - '0') / 3) - 1;
	col = (int)((cellNo - '0') % 3) - 1;
	if (col == -1) {
		col = 2;
	}
	if (board[row][col] != cellNo) 
	{
			cout << "------------- Value has already entered in this cell-------------\n";
			return 1;
	}
	else 
	{
		replacing(board, player.symbol, cellNo);  //Calling function
		return 0;
	}
}

//This Function generates random number from 1 to 9

int randomNumberGenerator()
{
	srand(time(0));
	int randomNumber = 1 + rand() % 9;
	return randomNumber;
}

int validCellNoForComputer(char board[3][3], char cellNo, Player player)
{
	int row, col;
	row = ceil((double)(cellNo - '0') / 3) - 1;
	col = (int)((cellNo - '0') % 3) - 1;
	if (col == -1) 
	{
		col = 2;
	}
	if (board[row][col] != cellNo)
	{
		return 1;
	}
	else
	{
		cout << "Computer's turn: " << randomNumberGenerator() << endl;
		replacing(board, player.symbol, cellNo);  //Calling function
		return 0;
	}
}

//This function will check which playerr wins the game or game is tied

int checkWin(char board[3][3], char cellNo, Player player, int &count) 
{  
	if (board[0][0] == player.symbol && board[1][0] == player.symbol && board[2][0] == player.symbol)
	{
		cout << "----------------" << player.name << " Won----------------" << endl;
		file << "----------------" << player.name << " Won---------------- " << endl;                   //writing data in file
		
		return -1;
	}
	else if (board[0][0] == player.symbol && board[0][1] == player.symbol && board[0][2] == player.symbol)
	{
		cout << "----------------" << player.name << " Won----------------" << endl;
	    file << "----------------" << player.name << " Won---------------- " << endl;                      //writing data in file   
		
		return -1;
	}
	else if (board[1][0] == player.symbol && board[1][1] == player.symbol && board[1][2] == player.symbol)
	{
		cout << "----------------" << player.name << " Won----------------" << endl;
		file << "----------------" << player.name << " Won----------------" << endl;                      //writing data in file
		
		return -1;
	}
	else if (board[2][0] == player.symbol && board[2][1] == player.symbol && board[2][2] == player.symbol)
	{
		cout << "----------------" << player.name << " Won----------------" << endl;
		file << "----------------" << player.name << " Won----------------" << endl;                      //writing data in file 
		
		return -1;
	}
	else if (board[0][1] == player.symbol && board[1][1] == player.symbol && board[2][1] == player.symbol)
	{
		cout << "----------------" << player.name << " Won----------------" << endl;
		file << "----------------" << player.name << " Won----------------"  << endl;                      //writing data in file
		
		return -1;
	}
	else if (board[0][2] == player.symbol && board[1][2] == player.symbol && board[2][2] == player.symbol)
	{
		cout << "----------------" << player.name << " Won----------------" << endl;
		file << "----------------" << player.name << " Won----------------" << endl;                      //writing data in file
		return -1;
	}
	else if (board[2][0] == player.symbol && board[1][1] == player.symbol && board[0][2] == player.symbol)
	{
		cout << "----------------" << player.name << " Won----------------" << endl;
		file << "----------------" << player.name << " Won----------------" << endl;                      //writing data in file
		
		return -1; 
	}
	else if (board[0][0] == player.symbol && board[1][1] == player.symbol && board[2][2] == player.symbol)
	{
		cout << "----------------" << player.name << " Won----------------" << endl;
		file << "----------------" << player.name << " Won----------------" << endl;                      //writing data in file
		
		return -1;
	}
	else if (count == 9)
	{
		cout << "----------------Game is tied----------------"<<endl;
		file << "----------------Game is tied----------------" << endl;                                                                //writing data in file
		return count;
	}
	return 0;
}

//This is function for player vs computer mode

int playerVSComputermode(char board[3][3])
{
	Player player, computer;
	computer.name = "Computer";                                           //Initializing structure for computer
	computer.symbol = 'o';
	char cellNo, randomCellNo;
	int count = 0, win = 1, randomNumber;
	cin.ignore();
	cout << "Enter your name: ";
	getline(cin, player.name);
	file << player.name;
	cout << "Enter symbol: ";
	cin >> player.symbol;
	if (player.symbol == 'o')
	{
		cout << "Enter symbol again it is reserved for computer: ";
		cin >> player.symbol;
	}
	file << " VS Computer\n ";
	cout << "\n--------------------------Let's Play game--------------------------" << endl << endl;
	displayBoard(board);
	bool flag = true;
	int flagForPlayer = 1, flagForComputer = 1;
	while (flag)
	{
		flagForPlayer = 1;
		flagForComputer = 1;
		while (flagForPlayer == 1 && flag) 
		{
			cout << player.name << " enter your cell number: ";
			cin >> cellNo;
			flagForPlayer = validCellNo(board, cellNo, player);                //calling function
			win = checkWin(board, cellNo, player, count);                      //calling function and call by reference is used in count

			if (win == -1)
			{
				flag = false;
			}
		}
		if (count == 8 && flag)
		{
			count++;
			if (count == 9) 
			{
				flag = false;
				checkWin(board, cellNo, player, count);                          //calling function
			}
		}
		while (flagForComputer == 1 && flag)
		{
			randomNumber = randomNumberGenerator();
			randomCellNo = ('0' + randomNumber);
			flagForComputer = validCellNoForComputer(board, randomCellNo, computer);
			win = checkWin(board, randomCellNo, computer, count);                //calling function 
			if (win == -1)
			{
				flag = false;
			}
		}
		count += 2;
	}
	return 0;
}

//This function is for player vs player mode



//It is function where we call the player vs computer mode

int ticTacToe(char board[3][3])
{
	int mode = modeOfGame();
    if (mode == 1)
	{
		playerVSComputermode(board);          //calling function
		return 0;
	}
	else if (mode == 2)
	{
		return 0;
	}
}

// Main function

int main()
{
	file.open("TicTacToe.txt", ios::app);                              //Opening file in append mode
	string choice;
	bool flag=true;
	while (flag)
	{
		char board[3][3] = { {'1','2','3'},{'4','5','6'},{'7','8','9'} };
		ticTacToe(board);                                                  //calling funon
		cout << "Do you want to play again.  ";
		cout << "Enter yes to play again and NO to exit: ";
		cin >> choice;
		{
			if (choice == "no" || choice == "NO" || choice == "No")
			{
				flag = false;
			}
			else if (choice == "yes" || choice == "YES" || choice == "Yes")
			{
				flag = true;
			}
			else {
				flag = false;
			}
		}
	}
	file.close();                                                      //closing file
	return 0;
}
