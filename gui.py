import tkinter as tk
from basics import *
from time import sleep
from bridge import minimax

# Initailizing
root = tk.Tk()

# 3x3 List storing the buttons
buttons = []

# Buttons' frame
frame = tk.Frame(root)

def main():
    # Place a Frame that take the whole window
    frame.place(relwidth=1, relheight=1)

    # Iterate over rows
    for i in range(3):

        # Append row to buttons list
        buttons.append([])

        # Iterate over row's buttons
        for j in range(3):
            # Place the empty button
            buttons[i].append(
                place_button(
                    i, j,
                    bg=colors[" "],
                    command=move_function(i, j)
                )
            )


# Grid's colors
colors = {
    'X': '#faa',
    'O': '#aff',
    ' ': '#ddd'
}

# Returns a button placed on (i, j)
def place_button(i, j, bg='black', command=lambda: '', master=frame):
    # Make the button
    out = tk.Button(
        master,
        text=' ',
        command=command,
        bg=bg
    )
    # Place the button
    out.place(rely=i/3, relx=j/3, relwidth=1/3, relheight=1/3)
    # Return the button
    return out

# Returns a function that makes a move at (i, j)
def move_function(i, j):

    # Define the function to be returned
    def tmp():
        """
            1. Checks if the spot is empty
            2. Makes the move
            3. Check if the game had finished, and behave accordingly
        """

        # To allow toggling the player
        global current_player

        # Exit if the spot isn't empty
        if board[i][j] != ' ': return

        # Change button's color
        buttons[i][j].destroy()
        buttons[i][j] = place_button(
            i, j,
            bg=colors[current_player],
            command=move_function(i, j)
        )

        # Change the board variable
        board[i][j] = current_player

        # Toggle player
        current_player = opposite_player(current_player)

        # Check status
        status = board_status(board)

        # If someone won
        if status in 'XO':
            # Iterate over all buttons
            for k in range(3):
                for l in range(3):
                    # Alter the button
                    buttons[k][l].destroy()
                    buttons[k][l] = place_button(
                        k, l,
                        # Don't change colors
                        bg=colors[status],
                        # Further clicking resets the game 
                        command=reset
                    )

        # If it is a tie
        elif status == 'tie':
            for k in range(3):
                for l in range(3):
                    # Give the buttons the color of the winner
                    # Further clicking resets the game 
                    buttons[k][l].destroy()
                    buttons[k][l] = place_button(
                        k, l,
                        bg=colors[board[k][l]],
                        command=reset
                    )

        # If the game shall be continued
        else:
            # If it is AI's turn, make a move
            if current_player == 'X': AI_move()

    return tmp


# Resets the board and grid
def reset():
    for k in range(3):
        for l in range(3):
            board[k][l] = ' '
            buttons[k][l].destroy()
            buttons[k][l] = place_button(
                k, l,
                bg=colors[' '],
                command=move_function(k, l)
            )

    # Let AI make a move if it is his turn
    if current_player == 'X': AI_move()


def AI_move():
    i, j = minimax(board, 'X')
    sleep(.1)
    buttons[i][j].invoke()



main()
root.mainloop()
