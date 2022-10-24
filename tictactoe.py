
# The board used for tic-tac-toe
board = [[" ", " ", " "],
         [" ", " ", " "],
         [" ", " ", " "]]

# Given a symbol check if that symbol has won tic-tac-toe
def winning_condition(board, sym):

    winner_found = False
    # check rows
    for i in range(len(board)):
        if(board[i][0] == board[i][1] and board[i][0] == board[i][2] and board[i][0] == sym):
            winner_found = True

    # check columns
    for i in range(len(board)):
        if(board[0][i] == board[1][i] and board[0][i] == board[2][i] and board[0][i] == sym):
            winner_found = True

    # check diagonals
    if(board[0][0] == board[1][1] and board[0][0] == board[2][2] and board[0][0] == sym):
         winner_found = True

    if(board[2][0] == board[1][1] and board[2][0] == board[0][2] and board[2][0] == sym):
         winner_found = True
    
    return winner_found

# Place a piece on the board (Prompt user until input is valid)
def place_piece(board, sym):
    piece_placed = False

    # Continue to ask for input until a piece is in a valid location
    while(not piece_placed):
        x = int(input("Type x coordinate "))
        y = int(input("Type y coordinate "))


        if x > 2 or x < 0 or y > 2 or y < 0: # Check index out of bounds
            print("Invalid index. Try again.")
        elif(board[x][y] == " "): # Check if empty spot
            piece_placed = True
            board[x][y] = sym
        else:
            print(board[x][y], "is currently at this index. Try again.")

# Print the board a new line for each row
def print_board(board):
    for i in range(len(board)):
        print(board[i])

# Check if the board is full
def is_board_filled(board):
    for i in range(len(board)):
        for j in range(len(board[i])):
            if(board[i][j] == " "):
                return False
    
    return True

# Variable that stores if any player has won
player_won = False

# Variable that stores if a board has been filled
board_filled = False

# Possible symbols
sym = ["O", "X"]
player = 0

# Main game loop, continue until the game is over
while(not player_won and not board_filled):
    print_board(board)
    
    player = (player + 1) % 2

    print(sym[player], " player turn.")

    place_piece(board, sym[player])

    player_won = winning_condition(board, sym[player])

    board_filled = is_board_filled(board)

    print()


print_board(board)
if(player_won):
    print(sym[player], "won the game!")
elif(board_filled):
    print("Game Over! Tie!")

    
    