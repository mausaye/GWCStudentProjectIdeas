# This function takes in a string and a list of guessed characters
# It returns a string that shows the blanks and correct characters guessed
def check_char(str, list_guessed):

    # initally result is blank
    res = "";
    for c in str:
        # if guessed character is in the string, append it
        if c in list_guessed:
            res += c 
        else:
            # otherwise the player has not guessed it yet, append underscore
            res += "_"
    return res

# A function that prompts the user for an input character
# It appends the guess to the input list
def input_character(list_guessed):
    c = input("Input a character ")

    # BONUS: check if input is only one character -- if not just take first character
    if len(c) > 1:
        c = c[0]
        print("Input only one character, took first char entered")
    
    # BONUS: make all inputs lowercase
    c = c.lower()

    # add the guess to the llist
    list_guessed.append(c)

# Checks to see if there are any underscores in the list -- if so then player has not won yet
# If no underscores left, the player has won!
def winning_condition(str):
    for c in str:
        if c == "_":
            return False

    return True


"""
Prompt to start the game
"""
print("Hangman / Guess the word!")
word = "programming"

# Characters the player has guessed
char_guessed = []

# Variables to check winning condition
guessed_all_characters = False
num_incorrect_guesses = 0;

# Loop until the player has guessed all characters or run out of guesses
while((not guessed_all_characters) and (not num_incorrect_guesses >= 5)):
    # Check previous guessed string
    prev = check_char(word, char_guessed)

    # Ask the user to input a character
    input_character(char_guessed)

    # New string after the player has guessed
    current = check_char(word, char_guessed)

    # Prints the characters already guessed
    print("Current Guesses", char_guessed)
    
    # Prints the current string of characters and underscores
    print(current)
    
    # Check if the previous string and the current string are the same
    # If they are that means the player did not guess a character correctly thus, increase the incorrect guesses
    if prev == current:
        num_incorrect_guesses = num_incorrect_guesses + 1

    # Prints the number of tries the player has left
    print("Number of tries left", 5 - num_incorrect_guesses)

    # Updates to check if the player has won yet
    guessed_all_characters = winning_condition(current)


# Prints out whether the player has won or lost
if guessed_all_characters:
    print("You win! The word was " + word)
else:
    print("You lose! The word was " + word)


