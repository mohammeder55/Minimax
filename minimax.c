#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_input(char board[3][3], char *file_name)
{
    // Open the input file in read mode
    FILE *input = fopen(file_name, "r");
    if (input == NULL) { printf("FILE CANNOT BE OPENED\n"); return; }

    char buffer[12];
    fread(buffer, sizeof(char), 11, input);
    // printf("%s\n", buffer);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = buffer[j + 4 * i];
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) { printf("INCULDE THE FILE\n"); return -1; }

    char board[3][3];
    read_input(board, argv[1]);

}
