/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : S3732094
 * COURSE CODE     : COSC2138
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/

 How to use the program: 
 
 Run tic-tac-n and it will show the main menu. Select an option using the keyboard - 
 enter 1, 2, or 3 and hit return to select a menu option.

 Option 1 starts a new game.
 Option 2 shows the scoreboard
 Option 3 quits the program.
 An invalid selection will request you to enter another input.

 When option 1 is select you will be prompted for three pieces of information
 1. Minimum umber of consecutive board positions required for a win;
 2. Player 1's name;
 3. Player 2's name.

 The number entered must be between 4 and 8 (inclusive). The player names must be less
 than 20 characters long. Hitting return on an empty line or Ctrl + d will take the 
 user back to the main menu from any of the above three prompts.

 The program will select a token for each player at random, as well as the playing order.
 The player with crosses will be shown in blue. The player with noughts will be shown in
 red.

 The game will then prompt users for turns until one user has achieved the minimum
 winning score. Moves are checked to make sure that they are valid. Draw conditions
 are detected.

 When option 2 is selected, a scoreboard will be shown. Press any key to return to the
 main menu.

 Known bugs: 
 While not a bug per se, the players are able to enter the same player name.
 Also note that the code is not generalisable to more than two players.

 Code attributions: 
 Code is my own with the exception of startup code provided by Paul Miller. No blocks
 or multi-line sections have been taken from external sources.

 C documentation at https://en.cppreference.com/w/c has been referred to for general
 C help. https://site.google.com/a/rmit.edu.au/programming-in-c---notes has also been
 used as a reference for C functions.

 In particular, I referred to the documentation for qsort at
 [1] www.cplusplus.com/reference/cstdlib/qsort/
 Primarily, how to declare a comparison method.

 I also referred to sample code at:
 [2] https://stackoverflow.com/questions/6105513/need-help-using-qsort-with-an-array-of-structs
 for the conversion of const void input parameters into a score structure type.

 The above two code usages are noted in the helpers.c/h source/header files where appropriate.
