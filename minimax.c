#include <stdio.h>
#include <stdlib.h>

// Define move structure
typedef struct
{
    int position;
    int score;
}
move;

// Board array's size
const int BOARD_SIZE = 10;

// Prototypes
void read_input(char board[], char *file_name);
int board_status(char board[]);
int player_number(char player);
char opposite_player(char player);
int score(int status);
int minimax_bridge(char *board);

// Returns the best move's position and score
// It looks it all possible next moves and evaluate each one
//     If the the possible move finished the game, it is directly evaluated
//     If it doesn't end the game
//         it is evaluted by the best move after it if the move's player is X
//         or by the worst if the player is O

move minimax(char board[BOARD_SIZE], char player, int depth)
{
    // printf("%c\n", player);
    // BASE CASE

    // Check the given board
    int status = board_status(board);

    // If there is no possible moves
    if (status != 0)
    {
        // Return the move's score
        // No one cares about it's score
        move tmp = {.position = -1, .score = score(status)};
        return tmp;
    }

    // PRE-RECURSION

    // Initiate an array of available moves
    move avails[BOARD_SIZE - 1];
    int avail_count = 0;

    // printf("012345678\n%s|\n", board);

    // Iterate over the board
    for (int i = 0; board[i] != '\0'; i++)
    {
        // If the spot is empty
        if (board[i] == ' ')
        {
            // Append it to the availables
            avails[avail_count].position = i;
            // printf("%i", i);
            // Move to the next move in availables
            avail_count++;
        }
    }

    // printf("\n%p\n", avail);

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
        move best = {.position = -1, .score = -10};
        for (int i = 0; i < avail_count; i++)
        {
            if (avails[i].score > best.score)
            {
                best = avails[i];
            }
        }
        return best;
    }

    move worst = {.position = -1, .score = 10};
    for (int i = 0; i < avail_count; i++)
    {
        if (avails[i].score < worst.score)
        {
            worst = avails[i];
        }
    }
    return worst;
    // move tmp = {.position = -1, .score = score(status)};
    // depth++;
    // return tmp;
}


int main(void) {
    char board[10];

    read_input(board, "b");

    // printf("%s|\n", board);

    int j = minimax(board, 'X', 0).position;
    printf("%i\n", j);
}

int minimax_bridge(char *board)
{
    // printf("|%s|", board);
    return minimax(board, 'X', 0).position;
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

// Return player's number
// 1 for X
// 2 for O
int player_number(char player)
{
    if (player == 'X')
    {
        return 1;
    }
    return 2;
}

// Return board status
// 1 or 2 if X or O had won
// 0 in the game shall be continued
// -1 if it is a tie
int board_status(char board[])
{
    // Check horizontals
    for (int i = 0; i < 8; i += 3)
    {
        if (board[i] == board[i + 1] && board[i] == board[i + 2] && board[i] != ' ')
        {
            return player_number(board[i]);
        }
    }

    // Check verticals
    for (int i = 0; i < 3; i++)
    {
        if (board[i] == board[i + 3] && board[i] == board[i + 6] && board[i] != ' ')
        {
            return player_number(board[i]);
        }
    }

    // Check Diagonals
    if (board[0] == board[4] && board[0] == board[8] && board[4] != ' ')
    {
        return player_number(board[4]);
    }
    if (board[2] == board[4] && board[2] == board[6] && board[4] != ' ')
    {
        return player_number(board[4]);
    }

    // Check for empty spot
    for (int i = 0; board[i] != '\0'; i++)
    {
        if (board[i] == ' ')
        {
            return 0;
        }
    }

    return -1;
}

// Read's the board file
void read_input(char board[], char *file_name)
{
    // Open the input file in read mode
    FILE *input = fopen(file_name, "r");
    if (input == NULL) { printf("FILE CANNOT BE OPENED\n"); return; }

    char buffer[12];
    fread(buffer, sizeof(char), 11, input);
    // printf("%s|\n", buffer);

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

// Return the corresponding score of the status
int score(int status)
{
    return (-5 * status * status + 3 * status + 8) / 6;

}