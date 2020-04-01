
// Comentario de cabecera

// This is a Sodoku Solver. Exercice focus on Recursion

#include <iostream>
#include <vector>

std::vector<std::vector<int>> solveSudoku(std::vector<std::vector<int>>& board);
bool checkNumber(int x, int y, int n, std::vector<std::vector<int>>& board);
void printSudoku(std::vector<std::vector<int>>& board);

int main()
{
                                         // (0,0)
    std::vector<std::vector<int>> board = { {0,0,0,  2,6,0,  7,0,1},
                                            {6,8,0,  0,7,0,  0,9,0},
                                            {1,9,0,  0,0,4,  5,0,0},

                                            {8,2,0,  1,0,0,  0,4,0},
                                            {0,0,4,  6,0,2,  9,0,0},
                                            {0,5,0,  0,0,3,  0,2,8},

                                            {0,0,9,  3,0,0,  0,7,4},
                                            {0,4,0,  0,5,0,  0,0,6},
                                            {7,0,3,  0,1,8,  0,0,0},
    };                                                      // (9,9)  

    std::cout << std::endl << std::endl;
    printSudoku(board);
    board = solveSudoku(board);
    std::cout << "                      --------------------------" << std::endl;
    printSudoku(board);
    std::cout << std::endl << std::endl;

    return 0;
}

// Create function that recives an y position, x position and a number
// between 1-9 (both included) and returns true or false wherter that number
// in that position is valid. Which will mean that the number inserted doesn not 
// apear in that row and column
bool checkNumber(int _x, int _y, int n, std::vector<std::vector<int>>& board)
{                                         
    if (board[_y][_x] != 0) return false;

    // Loop through the x position in all rows
    for (int y = 0; y < board.size(); ++y)
    {
        if (board[y][_x] == n)
            return false;
    }
    // Loop throught the y position row
    for (int x = 0; x < board[_y].size(); ++x)
    {
        if (board[_y][x] == n)
            return false;
    }

    // Check the box
    int x0 = (int)((_x / 3) * 3);
    int y0 = (int)((_y / 3) * 3);

    for (int y = y0; y < y0 + 3; ++y)
    {
        for (int x = x0; x < x0 + 3; ++x)
        {
            if (board[y][x] == n)
                return false;
        }
    }
    return true;
}

// Comprobar las posiciones que son 0, en estas posiciones tendremos que añadir un número
// Los números van del 0 al 9
std::vector<std::vector<int>> solveSudoku(std::vector<std::vector<int>>& board)
{
    //std::vector<std::vector<int>> board2;

    int posibleNumbersInPosition[9];
    int posibleNumbersCount = 0;

    for (int y = 0; y < board.size(); ++y)
    {
        //std::cout << std::endl << y << std::endl;
        for (int x = 0; x < board[y].size(); ++x)
        {
          //  std::cout << x;
            if (board[y][x] == 0)
            {
                for(int number = 1; number < 10; ++number)
                {
                    if (checkNumber(x, y, number, board))
                    {
                        posibleNumbersInPosition[posibleNumbersCount] = number;
                        ++posibleNumbersCount;
                    }
                }
                if (posibleNumbersCount == 1 && posibleNumbersInPosition[0] != 0)
                {
                    board[y][x] = posibleNumbersInPosition[0];
                    board = solveSudoku(board);
                  
                }
                // Reset data
                posibleNumbersCount = 0;
                for (int i = 0; i < 9; ++i) posibleNumbersInPosition[i] = 0;
            }
        }
    } 
    return board;
}

void printSudoku(std::vector<std::vector<int>>& board)
{
    for (int i = 0; i < board.size(); ++i)
    {
        std::cout << "                       ";
        for (int j = 0; j < board[i].size(); ++j)
        {
            if (j == 3 || j == 6)
                std::cout << "  ";

            std::cout << " " <<  board[i][j];

        }
        if (i == 2 || i == 5)
            std::cout << std::endl;

        std::cout << std::endl;
    }
}

