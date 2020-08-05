#include <stdio.h>
#include <stdlib.h>

// Define
typedef struct
{
    int position;
    int score;
}
move;

const int BOARD_SIZE = 10;

void read_input(char board[], char *file_name);
int board_status(char board[]);
int player_number(char player);
char opposite_player(char player);
int score(int status);


move minimax(char board[BOARD_SIZE], char player)
{
    int status = board_status(board);

    if (status != 0)
    {
        move tmp = {.position = -1, .score = score(status)};
        return tmp;
    }

    printf("%c\n", player);
    move tmp = {.position = -100, .score = -100};
    return tmp;
}

int main(int argc, char *argv[]) {
    if (argc != 2) { printf("INCULDE THE FILE\n"); return -1; }

    char board[10];
    read_input(board, argv[1]);

    int j = minimax(board, 'X').score;
    printf("%i\n", j);
}

char opposite_player(char player)
{
    if (player == 'X')
    {
        return 'O';
    }
    return 'X';
}

int player_number(char player)
{
    if (player == 'X')
    {
        return 1;
    }
    return 2;
}

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

void read_input(char board[], char *file_name)
{
    // Open the input file in read mode
    FILE *input = fopen(file_name, "r");
    if (input == NULL) { printf("FILE CANNOT BE OPENED\n"); return; }

    char buffer[12];
    fread(buffer, sizeof(char), 11, input);
    // printf("%s\n", buffer);

    int j = 0;
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] != '\n')
        {
            board[j] = buffer[i];
            j++;
        }
    }
    board[9] = '\0';
}

int score(int status)
{
    return (-5 * status * status + 3 * status + 8) / 6;

}