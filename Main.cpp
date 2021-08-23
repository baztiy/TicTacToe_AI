#include <iostream>
#include <vector>
#include <random>

std::vector<char> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'}; // game board

int chooseRandomNumber(double start, double end)
{
    // returns a random number in given range
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(start,end); 
    int rand_num = dist(mt);
    return rand_num; 
}

bool isTie()
{
    // Checks wether game is tied or not
    int end = 0;
    for (int i = 0; i < board.size(); i++)
    {
        if (board[i] == 'X' || board[i] == 'O')
        {
            end++;
        }
    }
    if (end == 8)
    {
        return true; 
    }
    return false;
}

void printBoard()
{
    // print a proper tictactoe board to the console
    std::cout << std::endl;
    for (int i = 0; i < 9; i++)
    {
        if (i == 2 || i == 5)
        {
            std::cout << " " << board[i] << std::endl;
            std::cout << " ---------" << std::endl;
        }
        else if (i != 8)
            std::cout << " " << board[i] << " |";
        else 
            std::cout << " " << board[i] << std::endl;
    }
    std::cout << std::endl;
}

void placeX()
{
    // handle the user input and player moves
    int num; // players position
    while (true)
    {
        std::cout << "Please enter a number from 1 to 9: ";
        std::cin >> num; // store console input as players position
        if (board[num - 1] != 'X' && board[num - 1] != 'O') //check if position is empty
        {
            board[num - 1] = 'X'; // place player at chosen position
            break;
        } else // handle invalid input
        {
            std::cout << "Please enter a valid number!" << std::endl;
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
    }
}

bool checkWin(char sym, std::vector<char> board)
{
    // check if the game has been won

    // check rows
    if (board[0] == sym && board[1] == sym && board[2] == sym)
        return true;
    if (board[3] == sym && board[4] == sym && board[5] == sym)
        return true;
    if (board[6] == sym && board[7] == sym && board[8] == sym)
        return true;

    // check cols
    if (board[0] == sym && board[3] == sym && board[6] == sym)
        return true;
    if (board[1] == sym && board[4] == sym && board[7] == sym)
        return true;
    if (board[2] == sym && board[5] == sym && board[8] == sym)
        return true;

    // check diagonals
    if (board[0] == sym && board[4] == sym && board[8] == sym)
        return true;
    if (board[2] == sym && board[4] == sym && board[6] == sym)
        return true;

    return false;
}

int placeO()
{
    /* 
    Order of Operation:
        1. If possible, win the game.
        2. If needed, block opponent from winning the game.
        3. If possible, move to center.
        4. If possible, move to random corner.
        5. Move to random edge.    
     */

    std::vector<int> corners = {0, 2, 6, 8}; // indices of corners
    std::vector<int> edges = {1, 3, 5, 7}; // indices of edges

    // checking if game can be won, if so, move to end the game
    for (int i = 0; i < 9; i++)
    {
        std::vector<char> boardCopy = board; // copy of current game board
        if (boardCopy[i] != 'X' && boardCopy[i] != 'O') // check if position is empty
        {
            boardCopy[i] = 'O';
            if (checkWin('O', boardCopy)) // check if game can be won
            {
            
                board[i] = 'O'; // move to winning position
                boardCopy.clear();
                return 0;
            }
        }
        boardCopy.clear();
    }

    // check if opponent can win, if so, move to block opponent
    for (int i = 0; i < 9; i++)
    {
        std::vector<char> boardCopy = board; // copy of current game board
        if (boardCopy[i] != 'X' && boardCopy[i] != 'O') // check if position is empty
        {
            boardCopy[i] = 'X'; 
            if (checkWin('X', boardCopy)) // check if opponent can win
            {
                    board[i] = 'O'; // block opponents winning move
                    boardCopy.clear();
                    return 0;
                
            }
        }
        boardCopy.clear();
    }

    if (board[4] != 'X' && board[4] != 'O') // move to center square is possible
    {
        board[4] = 'O';
        return 0;
    }

    for(int i = 0; i < corners.size(); i++)
    {
        int pos = corners[chooseRandomNumber(0, corners.size()-1)]; // choose a random corner
        if (board[pos] != 'X' && board[pos] != 'O') // check if randomly chosen corner is empty
        {
            board[pos] = 'O'; // move to corner
            return 0; 
        }

    }

    for (int i = 0; i < edges.size(); i++)
    {
        int pos = edges[chooseRandomNumber(0, edges.size()-1)]; // choose a random edge
        if (board[pos] != 'X' && board[pos] != 'O') // check if randomly chosen edge is empty
        {
            board[pos] = 'O'; // move to edge
            return 0;
        }
    }
    return 0;
}

int playAgain()
{
    // asks if the player wants to play again
    void startGame(); // declare startGame 
    char action;
    std::cout << "Do you want to play again (Yes/No)? " << std::endl;
    std::cin >> action; // store console input
    if (action == 'Y' || action == 'y') // handle yes
    {
        std::cin.clear();
        std::cin.ignore(100, '\n');
        board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'}; // initialize fresh game board
        startGame(); // start game
    } else if (action == 'N' || action == 'n') // handle no
    {
        std::cin.clear();
        std::cin.ignore(100, '\n');
        return 0; // exit function
    } else // handle invalid input
    {
        std::cout << "Please enter either 'Yes' or 'No'!" << std::endl; 
        std::cin.clear();
        std::cin.ignore(100, '\n');
        playAgain(); // recall playAgain
    }
    return 0;
}

void startGame()
{
    // Main game loop
    
    std::cout << "------------" << std::endl;
    printBoard();
    while (!isTie()) // Game is not tied as base case
    {
        placeX(); // Player starts

        if (checkWin('X', board)) // check if player won and respond appropriately
        {
            printBoard();
            std::cout << "X Wins!" << std::endl;
            playAgain();
            break;
        }

        placeO(); // computer move

        if (checkWin('O', board)) // check if computer won and respond appropriately
        {
            printBoard();
            std::cout << "O Wins, better luck next time!" << std::endl;
            playAgain();
            break;
        }

        printBoard(); // print board to console
    }
    if (isTie()) // safety check to make sure the game did end on a tie
    {
        std::cout << "It's a Tie!" << std::endl;
        playAgain();
    }
}

int main()
{  
    std::cout << "Welcome to TicTacToe! Press any button to start!" << std::endl; // display welcome message
    std::cin.get();

    startGame(); // start the game

    return 0;
}