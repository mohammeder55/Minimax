board = [
	[' ', ' ', ' '],
	[' ', ' ', ' '],
	[' ', ' ', ' ']
]
position = {
	'7': (0, 0),
	'8': (0, 1),
	'9': (0, 2),
	'4': (1, 0),
	'5': (1, 1),
	'6': (1, 2),
	'1': (2, 0),
	'2': (2, 1),
	'3': (2, 2)
}
current_player = 'O'

# returns tie or winner's letter or none
def board_status(board):
	# diagonals
	for i, j in [(2, 0), (0, 2)]:
		if board[0][i] == board[1][1] == board[2][j] != ' ':
			return board[1][1]

	# rows
	for i in range(3):
		if board[i][0] == board[i][1] == board[i][2] != ' ':
			return board[i][0]

	# columns
	for i in range(3):
		if board[0][i] == board[1][i] == board[2][i] != ' ':
			return board[0][i]

	# check if any spot is empty
	for row in board:
		for spot in row:
			if spot == ' ': return "none"

	return 'tie'

def print_board(board):
	for row in board:
		print('|'.join(row))

# returns the opposite player
def opposite_player(player):
	if player == 'X':
		return 'O'
	else:
		return 'X'

