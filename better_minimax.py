from xo_basics import *
from random import randint

scores = {
    'X': 1,
    'tie': 0,
    'O': -1
}

# Takes the player
# Returns the best move for the current board, in case the given player was X
# Returns the worst move for the current board, in case the given player was Y
# Returns a dictionary containing the position and the score
# the X is by always the maximising player
def minimax(board, player):
    # Check if the game is already finished
    status = board_status(board)

    # If the game is over a.k.a. not none
    if status != 'none':
        # Return the board's score
        return {
            "position": None,
            "score": scores[status]
        }

    # Make a record of availabe spots
    availables = []
    for i in range(3):
        for j in range(3):
            if board[i][j] == ' ':
                availables.append({
                    "position": (i, j)
                })

    # Iterate over available move by indecies
    for k in range(len(availables)):
        # Upack the position
        i, j = availables[k]['position']

        # Make the move
        board[i][j] = player
        # Return best/worst move and take its score
        move = minimax(board, opposite_player(player))
        score = move['score']
        # Undo the move
        board[i][j] = ' '

        # write score to its move in availables
        availables[k]['score'] = score

    # If we are maximizing
    if player == 'X':
        # A list of best moves, all of equal score
        # Get the worst best move to begin with
        bests = [{"position": -1, "score": -10}]

        # Iterate over availabe moves
        for move in availables:
            # If the move's score is greater than the best's
            if move["score"] > bests[0]["score"]:
                # The best move is that move only
                bests = [move]
            # If the move's score is equal to the best move
            elif move["score"] == bests[0]["score"]:
                # Add it to bests
                bests.append(move)

        # Pick a random move of the bests
        rnd = randint(0, len(bests) - 1)

        # Return the best move
        return bests[rnd]

    else:
        # A list of worst moves, all of equal score
        # Get the best worst move to begin with
        worsts = [{"index": -1, "score": 10}]

        # Iterate over availabe moves
        for move in availables:
            # If the move's score is less than the worst's
            if move["score"] < worsts[0]["score"]:
                # The worst move is only that move
                worsts = [move]
            # If the move's score is equal to the worst's
            if move["score"] == worsts[0]["score"]:
                # Add it to worsts
                worsts.append(move)
            
        rnd = randint(0, len(worsts) - 1)

        # Return the worst move
        return worsts[rnd]
