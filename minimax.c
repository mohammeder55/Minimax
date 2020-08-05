#include <stdio.h>
#include <stdlib.h>

void read_input(char board[], char *file_name);
int board_status(char board[]);
int compose_status(char player, int positions[]);


int main(int argc, char *argv[]) {
    if (argc != 2) { printf("INCULDE THE FILE\n"); return -1; }

    char board[10];
    read_input(board, argv[1]);

    int status = board_status(board);
    printf("%04i\n", status);

}

int compose_status(char player, int positions[])
{
    int player_number;

    if (player == '-')
    {
        return -1;
    }
    else if (player == '|')
    {
        return 0;
    }
    
    else
    {
        if (player == 'X')
        {
            player_number = 1;
        }
        else if (player == 'O')
        {
            player_number = 2;
        }

        return 1000 * positions[0]
            + 100 * positions[1]
            + 10 * positions[2]
            + player_number;
    }
}

int board_status(char board[])
{
    // Check horizontals
    for (int i = 0; i < 8; i += 3)
    {
        if (board[i] == board[i + 1] && board[i] == board[i + 2] && board[i] != ' ')
        {
            printf("%c %i %i %i\n", board[i], i, i + 1, i + 2);
            int positions[3] = {i, i + 1, i + 2};
            return compose_status(board[i], positions);
        }
    }

    // Check verticals
    for (int i = 0; i < 3; i++)
    {
        if (board[i] == board[i + 3] && board[i] == board[i + 6] && board[i] != ' ')
        {
            printf("%c %i %i %i\n", board[i], i, i + 3, i + 6);

            int positions[3] = {i, i + 3, i + 6};
            return compose_status(board[i], positions);
        }
    }

    // Check Diagonals
    if (board[0] == board[4] && board[0] == board[8] && board[4] != ' ')
    {
        printf("%c 0 4 8\n", board[4]);

        int positions[3] = {0, 4, 8};
        return compose_status(board[4], positions);
    }
    if (board[2] == board[4] && board[2] == board[6] && board[4] != ' ')
    {
        printf("%c 2 4 6\n", board[4]);

        int positions[3] = {2, 4, 6};
        return compose_status(board[4], positions);
    }

    int positions[3] = {0, 0, 0};

    // Check for empty spot
    for (int i = 0; board[i] != '\0'; i++)
    {
        if (board[i] == ' ')
        {
            printf("continue\n");

            return compose_status('|', positions);
        }
    }

    printf("tie\n");
    return compose_status('-', positions);
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
