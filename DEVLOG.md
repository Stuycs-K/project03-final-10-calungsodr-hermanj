# Dev Log:

This document must be updated daily by EACH group member.

## RAECHEL CALUNGSOD

### 2024-01-06 - Began host and player files
Spent 30 minutes of class time starting the host and player files. Wrote 
extended comments for the intended usage of the host file, began writing
function headers and planning out how the code will work.

### 2024-01-07 - Semaphores and text files
Spent 40 minutes in classs starting access with semaphores and writing
question/answer files. Worked with joy on modifying headers for 
organization in the host file.

Spent 40 minutes at home writing more of the host.c file, reorganizing
semaphore work and creating separate functions. I also left comments
regarding how to move forward.

### 2024-01-08 - Semaphores and signals
Spent 40 minutes in classs creating separate semaphore.c and semaphone.h
files. Added signals for graceful exiting. Tested and cleaned up comments.

Spent an hour at home writing the main function for the host file. Fixed
up some signal handling.

### 2024-01-09 - Logic and testing
Spent 20 minutes with Joy in class testing and updating code to make sure
we had the logic correct.

Spent 40 minutes at home writing out comments/pseudocode for the player
file, removed unnecessary semaphores

### 2024-01-10 - Rewriting host and player
Spent 25 minutes testing and discussing new directions for our code in
class. Adjusted

Spent 2 hours at home rewriting code to fit new strategy (no semaphores,
introduce structs, change the order of the code, base logic off of lab
15's handshake). The setup now works correctly.

### 2024-01-13 - Testing and question sending
Spent 40 minutes in class testing with Joy. Updated text files and made 
the point system printer.

Spent 30 minutes at home fixing some signal handling and other errors,
fixing some of the question cycling process.

### 2024-01-14 - Resolving issues
Spent 40 minutes finding and fixing issues with Joy. Fixed question
loop error and figured out exiting with a typed "end" command.

Spent 1 hour at home continuing to test and debug. Rewrote the
function that's used to find a question to fix another error where 
the game would not quit when the question bank is depleted. Improved
host sighandling to communicate with player (to be fixed further).

### 2024-01-15 - Resolving issues
Spent 40 minutes in class handling more errors and fixing up bugs,
determining how to restructure incorrect home with Joy.

Spent 1 hour at home rewriting the code so that the players array is 
dynamically allocated (players can choose how many people are going
to play), attempted to allow for a player to be removed without 
stopping the game.

### 2024-01-16 - Memory allocation
Spent 40 minutes in class testing and resolving issues with git 
branches. Fixed faulty code and cut down on comments.

Spent 40 minutes at home continuing to cut down comments and fix
inconsistencies with formatting. Added additional locations
for memory allocation and removed the code used to allow a 
player to leave mid-game (not feasible because of the 
host-player setup).

### 2024-01-17 - Documentation and testing
Spent 20 mintues in class writing the README and identifying
errors (prompting user for topic doesn't loop as it should,
there is a new error with ending the game).

Spent 30 minutes at home successfully fixing the mistakes 
identified today in class. 




# ------------------------------------------------- #

## JOY HERMAN 

### 2024-01-06 - Wrote basic makefile
Spent a rough 30 minutes at home writing the makefile and pushing to my 
own branch

### 2024-01-07 - Host.c: reading from text file
Spent 40 minutes in class starting to read from file. Worked with raechel
on modifying headers for organization in the host file.

Spent 50 minutes at home editing the host file to fit with my function
to read and parse the file.

### 2024-01-08 - reading from file and reading user input
Spent 40 minutes in class working with Raechel to reorganize our work,
tested with lab computer, merged our work together, started to work on
reading the user's answer.

Spent 50 minutes at home trying to get the function to return the string
properly to check the user's answers.

### 2024-01-09 - Logic, testing, and pipes
Spent 20 minutes with Raehcel explaining code, getting on the same page,
and fixing merge conflicts.

Spent 30 minutes at home adding pipes to the player files.

### 2024-01-10 - merging
Spent class time merging and planning on weekend work

### 2024-01-13 - pipes
Spent an hour of consecutive frees making the pipes connect properly,
making sure the host and player are on the same page.

Spent class time testing with Raechel and fixing pipes.

Spent 40 minutes at home trying to figure out how our code broke, 
added print statements to find where the piping messed up, changed 
a bit of the player.c so that the player know if they got the 
question right or wrong.

### 2024-01-14 - game end and looping
Spent an hour of consecutive frees fixing the loops and trying to get 
the player to exit when the host exits.

Spent class time identifying issues and distributing tasks to finish

Spent an 50 minutes at home testing and adding print statements to 
check where our code didn't exit properly. Also made the answers case 
insensitive and added some instructions

### 2024-01-15 - game end and question sending
Spent 30 minutes of free trying to find why the question doesnt send
sometimes now.

Spent class time finding bugs and working on them

### 2024-01-16 - code
Spent 50 minutes at home and some of free to make sure our code is on
the same page because somehow it wasn't in class. 

Spent class time trying to figure out why my code didn't run the same as 
Raechel's computer and found out that it's just me and my laptop

Spent 40 minutes at home adding a science topic and adding into the readme
