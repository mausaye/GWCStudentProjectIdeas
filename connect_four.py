# check if a user of symbol s wins
def winning_condition(board, s):
    # we do the -3 since a connection of 4 starting past a certain index cannot exist
    # rows
    for i in range(len(board)):
        for j in range(len(board[i]) -3):
            if board[i][j] == s and board[i][j + 1] == s and board[i][j + 2] == s and board[i][j + 3] == s:
                return True
            
    # col
    for i in range(len(board) - 3):
        for j in range(len(board[i])):
            if board[i][j] == s and board[i + 1][j] == s and board[i + 2][j] == s and board[i + 3][j] == s:
                return True


    # dia up right
    for i in range(len(board) - 3):
        for j in range(len(board[i]) - 3):
            if board[i][j] == s and board[i + 1][j + 1] == s and board[i + 2][j + 2] == s and board[i + 3][j + 3] == s:
                return True


    # dia down right
    for i in range(len(board) - 3):
        for j in range(len(board[i]) - 3):
            if board[i][j] == s and board[i - 1][j + 1] == s and board[i - 2][j + 2] == s and board[i - 3][j + 3] == s:
                return True

    return False

# ask user for input
def user_input(board, s):
    column = int(input("Pick a column: "))

    # ask user for input
    while(column < 0 or column > 7):
        column = int(input("Invalid input. Pick a column between 0 - 7: "))
    
    # find next lowest placement of piece
    lowest_row = len(board) - 1
    while(lowest_row >= 0 and board[lowest_row][column] != " "):
        lowest_row = lowest_row - 1
    
    # validity check
    if(lowest_row >= 0):
        board[lowest_row][column] = s
    
    #return if piece was placed
    return lowest_row >= 0

# check if the board is full
def board_full(board):
    for i in range(len(board)):
        for j in range(len(board[i])):
            if board[i][j] == " ":
                return False

    return True

# prints the board
def print_board(board):
     for i in range(len(board)):
            print(board[i])

board = [[" ", " ", " ", " ", " ", " ", " ", " "],
         [" ", " ", " ", " ", " ", " ", " ", " "],
         [" ", " ", " ", " ", " ", " ", " ", " "],
         [" ", " ", " ", " ", " ", " ", " ", " "],
         [" ", " ", " ", " ", " ", " ", " ", " "],
         [" ", " ", " ", " ", " ", " ", " ", " "],
         [" ", " ", " ", " ", " ", " ", " ", " "],
         [" ", " ", " ", " ", " ", " ", " ", " "]]

players = ["r", "y"]
turn = 0
win = False
print("Connect 4!")
while(not board_full(board) and not win):
    turn = (turn + 1) % 2

    # check if a piece was put
    while(not user_input(board, players[turn])):
        pass

    print_board(board)
    
    # check if someone won
    win = winning_condition(board, players[turn])

if not board_full(board):
    print(players[turn], "Wins!!")
else:
    print("Tie")

