#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int main(int argc, char *argv[]) {
    if (argc != 2) { printf("INCULDE THE FILE\n"); return -1; }

    char board[10];
    read_input(board, argv[1]);

    // printf("%s", board);

}
