# Final Project Proposal

## Group Members:

Joy Herman, Raechel Calungsod
       
# Intentions:

Our project is a multiplayer text-based trivia game, where players compete for points as they answer questions of a chosen topic.
    
# Intended usage:

Multiple users will be able to play a text-based multiplayer trivia game through the terminal. The first player to start the game is player 1, and everyone following receives a number according to the order of joining. After the players compile and run the program, text on the screen (the “game host”) will welcome the users and explain game instructions. The host will display a number of question topics (ex. History, Science, Math) for player 1 to choose from. Player 1 enters a topic, and the host will start asking questions of this topic in rounds. Player 1 has the chance to type in the answer first, but the opportunity is passed to player 2 if they get it wrong, then player 3, and so on. Whoever answers correctly first gets the point, and the game continues until a player types in “end game” or until all questions of the topic are answered. The player with the most points is awarded as the winner.
  
# Technical Details:

Topics covered in class:

Forking
- Each player is a separate process. The main process will fork to allow
multiple players to join and play simultaneously (on different terminal windows).

Working with files 
- Questions and answers will be held on files, one file per topic. 
- Questions will follow with a colon before the answer, and each Q&A set will be separated by a line break.
- Formatting: “What is 5+5? : 10”, “What is the capital of the Philippines? : Manila”

Allocating memory
- Memory will be allocated to store player names, scores, and question/answer text.

Shared memory
- The current question player scores will be tracked with shared memory to keep each process synchronized. 

Pipes
- Pipes will allow the host (main process) and players (child processes) to communicate by sending and receiving questions and answers.

Semaphores
- Similar to lab 13, semaphores will be used to control access to the shared memory. Only one player will be allowed to answer a question at a time.


Responsibilities:
- Writing the question and answer files: both Raechel and Joy
- Writing the host program to control the game (start/end), switch player turns, offer topics, read questions, calculate winners and display scores: Raechel
- Writing the player program to handle player answers and send to the host: Joy
- Semaphores and simultaneous access to the program, correct turn timing: both Raechel and Joy
- makefile: Joy
- Testing, debugging, and video for final presentation: both Raechel and Joy

  
Data structures:
ADD-ON (tentative): Use linked lists to manage players. If one leaves, the rest of the game will continue on normally without them.
    
# Intended pacing:
Jan 6 (Mon): Spend some time writing question and answer files, at least 4 topics. Begin coding the game base.
Jan 8 (Weds): Complete host and player basic setup, ensure they can communicate
Jan 10 (Fri): Complete question and answer files
Jan 13 (Mon): Shared memory and scoring system works
Jan 15 (Wednesday): Develop player turns
Jan 17 (Friday): Full game testing, ensure everything works properly
Jan 19 (Sunday): Continued debugging, any add-ons
Jan 20 (Monday): Go on Zoom, film a video for the final presentation
Jan 21: (Tues) all projects due. Final commits 8am including links to presentation.

