# Tic Tac Toe AI with Minimax Algorithm

This is my implementation of tic tac toe AI, in which I implemented the AI in C and implemented game logic and GUI in python. I used Tkinter module for the GUI and ctypes to link C code to python.

## Detail conserning the algorithm

First things first, minimax algorithm is a search alogrithm that, for a given tic tac toe board, traces all possible moves searching for the best scenario move. The algorithm uses the following ranks by the following scheme:

- If the move ends the game:
    - 1 if the AI is wins
    - 0 if the it results in a tie
    - -1 if the opponents wins

- Else:
    - The algorithm goes over all possible next moves and pickes the one with maximum score if AI is the one assumed to make that move, and pickes the one with minimum score if the opponent is the one assumed to make the that move

So, in a nutshell, it starts by going through all the possible move tha AI can make, and looks through all possible move recursively looking for the best case scenario in which both players are using the optimal strategy.

## Implementation details

- **minimax.c, Makefile, b**: I decided to implement the algorithm in C, as it is more efficient than python. Thus the need for a Makefile, to make compilation easier, and b (stands for board) to help me test the algorithm without hardcoding board configurations and having to recompile it each time just to change the board.

- **bridge.py**: This is the translation layer between C and Python, it takes python variables as input, converts it to C variable, and passes it to C code to handle it. Then it recieves the output of the algorithm and returns it as an output.

- **basics.py**: Basic functions needed for the game flow.

- **gui.py, cli.py**: Those are the implementation of game logic and user interface.

## Side notes

Some flaws in my code that I am aware of:
- I have two implementations of the function returning board status, one in C and the other in Python. That is mainly because I, at the beginning, didn't have in mind that I'll implement the algorithm in C, thus I wrote it twice, and I'm too lazy to implement a python interface to the function written in C.
- I have all my C code stashed in a single file and I should have splitted it intp several files.
- The C main function and read_input are both used only for debugging, thus not required in the compiled shared library and should be thrown in a seperate file.
- I should have the game go to next game after an amount of time, instead of waiting for the player to click a spot.
- The game should not declare winner immediatly after the AI has won. Instead, it should wait a bit so that the user can grasp what is happening.
