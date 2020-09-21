// Board statuses:
// Unfinished: 2
// X: 1
// Tie: 0
// O: -1
// 
// Board scores:
// X: 1
// Tie: 0
// O: -1

#include <stdio.h>
// #include <stdlib.h>

// Define move structure
typedef struct
{
    int position;
    int score;
}
move;

// Prototypes
void read_input(char board[], char *file_name);
int board_status(char *board);
int status(char player);
char opposite_player(char player);
int minimax_bridge(char *board, char player);

move minimax(char board[], char player, int depth)
{
    // BASE CASE

    // Lookup the status
    int s = board_status(board);

    // If the game is finshied
    if (s != 2)
    {
        // Return the move's score
        // Score does not matter
        move tmp = {.position = -1, .score = s};
        return tmp;
    }

    // PRE-RECURSION

    // Initiate an array of available moves
    move avails[9];
    int avail_count = 0;

    // Iterate over the board
    for (int i = 0; board[i] != '\0'; i++)
    {
        // If the spot is empty
        if (board[i] == ' ')
        {
            // Append it to the availables
            avails[avail_count].position = i;

            // Move to the next move in availables
            avail_count++;
        }
    }

    // RECURSION

    for (int i = 0; i < avail_count; i++)
    {
        int p = avails[i].position;

        board[p] = player;
        int score = minimax(board, opposite_player(player), depth + 1).score;
        board[p] = ' ';

        // printf("%i -> %i\n", score, p);

        avails[i].score = score;
    }

    if (player == 'X')
    {
        move best = {.position = -10, .score = -10};
        for (int i = 0; i < avail_count; i++)
        {
            if (avails[i].score > best.score)
            {
                best = avails[i];
            }
        }
        return best;
    }

    move worst = {.position = -10, .score = 10};
    for (int i = 0; i < avail_count; i++)
    {
        if (avails[i].score < worst.score)
        {
            worst = avails[i];
        }
    }
    return worst;
}


int main(void) {
    char board[10];

    read_input(board, "b");

    printf("%s|\n", board);

    int j = minimax(board, 'X', 0).position;
    printf("%i\n", j);
}

int minimax_bridge(char *board, char player)
{
    return minimax(board, player, 0).position;
}

// Return the opposite player
char opposite_player(char player)
{
    if (player == 'X')
    {
        return 'O';
    }
    return 'X';
}

// Return letter score
int status(char player)
{
    if (player == 'X')
    {
        return 1;
    }
    return -1;
}

int board_status(char *board)
{
    // Check horizontals
    for (int i = 0; i < 8; i += 3)
    {
        if (board[i] == board[i + 1] && board[i] == board[i + 2] && board[i] != ' ')
        {
            return status(board[i]);
        }
    }

    // Check verticals
    for (int i = 0; i < 3; i++)
    {
        if (board[i] == board[i + 3] && board[i] == board[i + 6] && board[i] != ' ')
        {
            return status(board[i]);
        }
    }

    // Check Diagonals
    if (board[0] == board[4] && board[0] == board[8] && board[4] != ' ')
    {
        return status(board[4]);
    }
    if (board[2] == board[4] && board[2] == board[6] && board[4] != ' ')
    {
        return status(board[4]);
    }

    // Check for empty spot
    for (int i = 0; board[i] != '\0'; i++)
    {
        if (board[i] == ' ')
        {
            return 2;
        }
    }

    return 0;
}

// Read's the board file
void read_input(char board[], char *file_name)
{
    // Open the input file in read mode
    FILE *input = fopen(file_name, "r");
    if (input == NULL) { printf("FILE CANNOT BE OPENED\n"); return; }

    char buffer[12];
    fread(buffer, sizeof(char), 11, input);

    // Iterate over buffer's characters
    for (int i = 0, j = 0; buffer[i] != '\0'; i++)
    {
        // If the character is line feed
        if (buffer[i] != '\n')
        {
            // Append it to the board
            board[j] = buffer[i];
            // Move to the next character in board
            j++;
        }
    }

    // Terminate the board
    board[9] = '\0';
}
