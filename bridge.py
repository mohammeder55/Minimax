import ctypes as ct
mlib = ct.CDLL("./minimax.so")

# Converts c position to py position
position = [
    (0, 0),
    (0, 1),
    (0, 2),
    (1, 0),
    (1, 1),
    (1, 2),
    (2, 0),
    (2, 1),
    (2, 2)
]


# Read board file
def file_input():
    # Open file
    with open('b', "r") as file:
        # take all characters except \n
        board = [char for char in file.read() if char != '\n']

    return ''.join(board).encode()

# Converts py board to c board
def c_board(board):
    out = ''

    # Iterate over rows
    for row in board:
        # join them into a string & append it to out
        out += ''.join(row)

    # Encode the string & return it
    return out.encode()

# Behaves like any minimax would do
def minimax(board, player):
    # Convert board to c
    b = c_board(board)

    # Conver player to c
    p = ct.c_char(player.encode())

    # Call minimax from c
    j = mlib.minimax_bridge(b, p)

    # Return py position
    return position[j]

# main()