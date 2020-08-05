#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_input(char board[], char *file_name);
int board_status(char board[]);
int compose_status(char player, int positions[]);


int main(int argc, char *argv[]) {
    if (argc != 2) { printf("INCULDE THE FILE\n"); return -1; }

    char board[10];
    read_input(board, argv[1]);

    board_status(board);

    // printf("%s", board);

}

int compose_status(char player, int positions[])
{
    
}

int board_status(char board[])
{
    // Check horizontals
    for (int i = 0; i < 8; i += 3)
    {
        if (board[i] == board[i + 1] && board[i] == board[i + 2] && board[i] != ' ')
        {
            printf("%c %i %i %i\n", board[i], i, i + 1, i + 2);
        }
    }

    // Check verticals
    for (int i = 0; i < 3; i++)
    {
        if (board[i] == board[i + 3] && board[i] == board[i + 6] && board[i] != ' ')
        {
            printf("%c %i %i %i\n", board[i], i, i + 3, i + 6);
        }
    }

    // Check Diagonals
    if (board[0] == board[4] && board[0] == board[8] && board[4] != ' ')
    {
        printf("%c 0 4 8\n", board[4]);
    }
    if (board[2] == board[4] && board[2] == board[6] && board[4] != ' ')
    {
        printf("%c 2 4 6\n", board[4]);
    }

    // Check for tie
    for (int i = 0; board[i] != '\0'; i++)
    {
        if (board[i] == ' ')
        {
            printf("continue\n");
            return 0;
        }
    }

    printf("tie\n");

    return 0;
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
