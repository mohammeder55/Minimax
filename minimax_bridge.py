import ctypes as ct

# Read board file
board = ''
with open("b", "r") as file:
    for char in file.read():
        if char != '\n': board += char


# print(f" 012345678 \n|{board}|")


def minimax():
    mlib = ct.CDLL("./minimax.so")

    # cboard = ct.c_wchar_p(board)
    j = mlib.minimax_bridge(board.encode())

    print(j)
# print(chr(
#     mlib.opposite_player(ct.c_char(b"O"))
# ))

minimax()