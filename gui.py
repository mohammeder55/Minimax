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
        # Append the row to buttons list
        buttons.append([])
        # Iterate over row's buttons
        for j in range(3):
            # Place the empty button
            buttons[i].append(placed_button(
                i, j,
                bg=colors[" "],
                command=move_function(i, j)
            ))


# Grid's colors
colors = {
    'X': '#faa',
    'O': '#aff',
    ' ': '#ddd'
}

# Returns a button placed on (i, j)
def placed_button(i, j, bg='black', command=lambda: '', master=frame):
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

# Returns the function of the button on (i, j) of regular moves
def move_function(i, j):
    # Define the function to be returned
    def ph():
        # In order to toggle the player
        global current_player

        # Break if the spot isn't empty
        if board[i][j] != ' ': return

        # Change the button's color
        buttons[i][j].destroy()
        buttons[i][j] = placed_button(
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
                    # Give the buttons the color of the winner
                    # Further clicking resets the game 
                    buttons[k][l].destroy()
                    buttons[k][l] = placed_button(
                        k, l,
                        bg=colors[status],
                        command=reset
                    )
            return

        # If it is tie
        elif status == 'tie':
            for k in range(3):
                for l in range(3):
                    # Give the buttons the color of the winner
                    # Further clicking resets the game 
                    buttons[k][l].destroy()
                    buttons[k][l] = placed_button(
                        k, l,
                        bg=colors[board[k][l]],
                        command=reset
                    )
            # current_player = 'O'
            return

        # If the game shall be continued
        else:
            # If it is AI's turn
            if current_player == 'X':
                AI_move()

    return ph


# Resets the board and grid
def reset():
    for k in range(3):
        for l in range(3):
            board[k][l] = ' '
            buttons[k][l].destroy()
            buttons[k][l] = placed_button(
                k, l,
                bg=colors[' '],
                command=move_function(k, l)
            )

    # If AI is to begin
    if current_player == 'X':
        AI_move()


def AI_move():
    i, j = minimax(board, 'X')
    buttons[i][j].invoke()



main()
root.mainloop()
