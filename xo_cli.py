from time import sleep
from xo_basics import *
# from better_minimax import minimax
from minimax_bridge import minimax


def main():
	# Each loop is a turn
	while True:
		global current_player

		# If it is O's turn
		if current_player == 'O':
			# Print the board for him to make a move
			print_board(board)
			# Take the input
			move = input(f"")
			print()
			# Convert the input 
			i, j = position[move]

		# If it is X's turn
		else:
			# Just to not make it too quick
			# sleep(.5)
			i, j = minimax(board, 'X')

		# If the chosen spot is available
		if board[i][j] == ' ':
			# Make the move
			board[i][j] = current_player

			# Check board
			status = board_status(board)

			# If the game shall end
			if status in 'XO' or status == 'tie':
				# Print board to before terminating
				print_board(board)

				# Print ending message
				if status in 'XO':
					print(f"\nPlayer {current_player} has won!")
				elif status == 'tie':
					print("\nTIE!")
					current_player = opposite_player(current_player)

				# Prepare for next game
				reset_board(board)

				# Terminate
				return 0

			else:
				# Prepare for next turn
				current_player = opposite_player(current_player)

		# If the spot isn't available
		else:
			print("Not A Valid Move ", end='')


def reset_board(board):
	for i in range(3):
		for j in range(3):
			board[i][j] = ' '

while True:
	main()
