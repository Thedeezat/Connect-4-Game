#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 6
#define COLS 7

//*************** Division of Features added ***********//
//   1. Hadiza: Player, modes
//   2. Ustaz: Game board, win
//   3. Mariam: lose, tie, restart
//*****************************************************//

void pickGameMode(char[][COLS]);
int computerMove(char[][COLS]);
void playGame(char[][COLS], char);
void playerVsComputer();
void playerVsPlayer();
void fillBoard(char[][COLS]);
void printGameBoard(char[][COLS]);
int validMove(char[][COLS], int);
void makeMove(char[][COLS], int, char);
int checkWin(char[][COLS], char);
int checkLoss(char[][COLS], char);
int checkDraw(char[][COLS]);
void restartGame(char boardMatrix[][COLS]);
void endGame();

// Main function (Declared the board variable)
int main()
{
    // Board variable
    char boardMatrix[ROWS][COLS] = {
        {'A', 'B', 'C', 'D', 'E', 'F', 'G'},
        {'.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.'}};

    // Print Game Mode (User picks mode either playerVsPlayer or Vs PlayerComputer);
    pickGameMode(boardMatrix);

    return 0;
}

//********* Pick Mode ***********//
void pickGameMode(char boardMatrix[][COLS])
{
    // Game Title
    printf("Connect Four Game for Robotic-Based Neurorehabilitation\n");

    // Game manual
    printf("************** Game Manual **************** \n");
    printf("\tEnter letter 'r' to restart \n");

    // Game starts
    printf("\nPress Enter to Start Game  🚀 ");
    getchar();

    // Choose Game Mode
    printf("\nChoose Game Mode:\n");
    printf("1: [👤 VS 🤖]\n");
    printf("2: [👤 vs 👤]\n");
    printf("Pick Mode: ");

    int pickMode;
    scanf("%d", &pickMode);

    if (pickMode == 1)
    {
        playerVsComputer();
    }
    else if (pickMode == 2)
    {
        playerVsPlayer();
    }
    else
    {
        // Output incase of error(If the user click a mode that is not 1 or 2)
        printf("Invalid game mode. Please try again.\n");
        pickGameMode(boardMatrix);
    }
}

//********* Play Random Move for VsComputer ***********//
int computerMove(char boardMatrix[][COLS])
{
    int moveColumn;
    srand(time(NULL));
    while (1)
    {
        // Random number generator using current time
        moveColumn = rand() % COLS;
        // So each time the program runs, a different sequence of random numbers is generated
        if (validMove(boardMatrix, moveColumn))
            break;
    }
    return moveColumn;
}
//********* Play Game ***********//
void playGame(char boardMatrix[][COLS], char player)
{
    // While loop to iterate through the board
    while (1)
    {
        printGameBoard(boardMatrix);

        if (player == '1')
        {
            printf("\nPlayer %c[👤], enter a column(A-G): ", player);

            // store the column letter entered by the player
            char playPosition;
            scanf(" %c", &playPosition);

            if (playPosition == 'r')
            {
                restartGame(boardMatrix);
                return;
            }
            else
            {
                if (playPosition >= 'a' && playPosition <= 'z')
                {
                    // converts the lowercase letter to uppercase by subtracting
                    // 32 from its ASCII value.
                    playPosition -= 32;
                }
                // calculates the column index from the uppercase letter
                int moveColumn = playPosition - 'A';

                if (validMove(boardMatrix, moveColumn))
                {
                    makeMove(boardMatrix, moveColumn, player);

                    if (checkWin(boardMatrix, player))
                    {
                        printGameBoard(boardMatrix);
                        printf("Player %c[👤] wins! Congratulations!\n", player);
                        endGame();
                        break;
                    }

                    player = (player == '1') ? '2' : '1'; // switches the player turn
                }
                else
                {
                    printf("\nInvalid move. Please try again.\n");
                }
            }
        }
        else if (player == '2') // computer player's turn
        {
            int moveColumn = computerMove(boardMatrix);
            printf("\nComputer[🤖] selects column(A-G) %c\n", moveColumn + 'A');
            makeMove(boardMatrix, moveColumn, player);
            if (checkWin(boardMatrix, player))
            {
                printGameBoard(boardMatrix);
                printf("Computer [🤖] wins!\n");
                endGame();
                break;
            }

            player = (player == '1') ? '2' : '1'; // switches the player turn
        }
    }
}
//********* Fill the Game board ***********//
void fillBoard(char boardMatrix[][COLS])
{
    for (int i = 1; i < ROWS; i++) // loop that iterates over the rows
    {
        for (int j = 0; j < COLS; j++) // nested loop that iterates over the columns
        {
            boardMatrix[i][j] = '.'; //  initializing the board with empty positions
        }
    }
}
void restartGame(char boardMatrix[][COLS])
{
    char player = '1';      // player's turn
    fillBoard(boardMatrix); // reset the game board by filling it with empty positions
    playGame(boardMatrix, player);
}

//********* Print the Game board ***********//
void printGameBoard(char boardMatrix[][COLS])
{
    printf("\n");
    char temp = 'A'; // used to generate column labels for the game board
    for (int j = 0; j < COLS; j++)
    {
        boardMatrix[0][j] = temp++; // iterates using the ASCII sequence
        printf("%c ", boardMatrix[0][j]);
    }

    printf("\n");

    for (int i = 1; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            // prints the current state of the game board
            printf("%c ", boardMatrix[i][j]);
        }
        printf("\n");
    }
}

//********* Play Against Computer ***********//
void playerVsComputer()
{
    char boardMatrix[ROWS][COLS];
    // initialize the game board with the first state, empty slots
    fillBoard(boardMatrix);
    // the current player who will make the first move
    char player = '1';

    printf("Connect Four - Player[👤] vs Computer[🤖]\n");
    printf("------------------------------------------\n");

    // running the main game loop and letting the computer get a turn
    playGame(boardMatrix, player);
}

//********* Play Against Another Player ***********//
void playerVsPlayer()
{
    char boardMatrix[ROWS][COLS];
    fillBoard(boardMatrix);
    char player = '1';

    printf("Connect Four - Player[👤] vs Player[👤]\n");
    printf("---------------------------------------\n");

    while (1)
    {
        printGameBoard(boardMatrix);

        printf("\nPlayer %c[👤], enter a column(A-G): ", player);

        char playPosition;
        scanf(" %c", &playPosition);

        if (playPosition == 'r') // inputting the letter 'r' will restart the game at any point
        {
            restartGame(boardMatrix);
            return;
        }

        else
        {
            if (playPosition >= 'a' && playPosition <= 'z')
            {
                playPosition -= 32; // ASCII numerical condition
            }
            // converts the entered position to the corresponding column index
            int moveColumn = playPosition - 'A';

            if (validMove(boardMatrix, moveColumn))
            {
                makeMove(boardMatrix, moveColumn, player);

                if (checkWin(boardMatrix, player))
                {
                    printGameBoard(boardMatrix);
                    printf("Player %c [👤] wins! Congratulations!\n", player);
                    endGame();
                    break;
                }
                //  toggling between two players in a game. If the current player
                //  is '1', it switches the player to '2'. If the current player is '2',
                //  it switches it back to '1'.
                player = (player == '1') ? '2' : '1';
            }
            else
            {
                // if the letter input was ouside of range
                printf("\nInvalid move. Please try again.\n");
            }
        }
    }
}

// checks if the input is in the range and if the cell is empty
int validMove(char boardMatrix[][COLS], int col)
{
    // checks if the input is in the range and if the cell is empty
    return (col >= 0 && col < COLS && boardMatrix[1][col] == '.');
}

//****** Make moves in the Game board ********//
void makeMove(char boardMatrix[][COLS], int col, char player)
{
    // checks if the cell is empty to put the input in the player

    for (int i = ROWS - 1; i > 1; i--)
    {
        if (boardMatrix[i][col] == '.')
        {
            boardMatrix[i][col] = player;
            break;
        }
    }
}

//****** Check Win in the Game board ********//
int checkWin(char boardMatrix[][COLS], char player)
{
    // Check for a horizontal win
    for (int i = 1; i < ROWS; i++)
    {
        // if 4 cells are filled out by the same player horizontally, they win
        for (int j = 0; j <= COLS - 4; j++)
        {
            if (boardMatrix[i][j] == player && boardMatrix[i][j + 1] == player &&
                boardMatrix[i][j + 2] == player && boardMatrix[i][j + 3] == player)
            {
                return 1;
            }
        }
    }

    // Check for a vertical win
    for (int i = 1; i <= ROWS - 4; i++)
    {
        // if 4 cells are filled out by the same player vertically, they win

        for (int j = 0; j < COLS; j++)
        {
            if (boardMatrix[i][j] == player && boardMatrix[i + 1][j] == player &&
                boardMatrix[i + 2][j] == player && boardMatrix[i + 3][j] == player)
            {
                return 1;
            }
        }
    }

    // Check for a diagonal win (ascending)
    for (int i = 1; i <= ROWS - 4; i++)
    {
        // if 4 cells are filled up to down diagonally by the same player, they win

        for (int j = 0; j <= COLS - 4; j++)
        {
            if (boardMatrix[i][j] == player && boardMatrix[i + 1][j + 1] == player &&
                boardMatrix[i + 2][j + 2] == player && boardMatrix[i + 3][j + 3] == player)
            {
                return 1;
            }
        }
    }

    // Check for a diagonal win (descending)
    for (int i = 1; i <= ROWS - 4; i++)
    {
        // if 4 cells are filled down to up diagonally by the same player, they win
        for (int j = COLS - 1; j >= 3; j--)
        {
            if (boardMatrix[i][j] == player && boardMatrix[i + 1][j - 1] == player &&
                boardMatrix[i + 2][j - 2] == player && boardMatrix[i + 3][j - 3] == player)
            {
                return 1;
            }
        }
    }

    return 0;
}

//****** Check Loss in the Game board ********//
int checkLoss(char boardMatrix[][COLS], char player)
{
    // returns the result of the checkwin() function
    return checkWin(boardMatrix, (player == '1') ? '2' : '1');
}

//****** Check Draw in the Game board ********//
int checkDraw(char boardMatrix[][COLS])
{
    for (int i = 1; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (boardMatrix[i][j] == '.')
            {
                // Game is not a draw, as there are still empty cells in the board
                return 0;
            }
        }
    }
    // Game is a draw, all cells are full
    return 1;
}

//************ End Game **************//

void endGame()
{
    printf("\nGame over!\n");
    printf("\n");
}