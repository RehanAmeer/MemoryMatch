Memory Match Game (C++ Console Version)
A Memory Matching Game built using C++, featuring:
•	Dynamic board generation
•	Pair matching logic
•	Save & load game system
•	High score storage using binary files
•	Clean ASCII-based interface
•	No advanced OOP — only fundamental C++ concepts
This project is perfect for PF (Programming Fundamentals) and can later be extended into OOP easily.
Features
1. Dynamic Board Sizes
•	Users can choose even sizes up to 6
•	Board becomes N × N (e.g., input 4 → 4×4 board)
•	Board auto-fills with letter pairs (A, B, C…).
2. Shuffle System
•	Cards are randomized every game using rand ()
•	Ensures a unique board every time.
3. Reveal & Match Logic
•	Players select two positions by row & column
•	Cards temporarily reveal
•	If matched → they stay revealed
•	If not → flip back
•	Move count increases each round.
4. Save Game
•	Game can be saved in match.txt
•	Saves:
    board size
    move count
    card layout
    revealed/unrevealed state
 5. Load Game
•	When starting, user can continue previous saved game
•	Restores:
    board
    moves
    matched pairs
    current progress
6. Win Detection
•	Game ends when all cards are revealed
•	Displays:
    Congratulations message
    Total moves
7. High Score System
•	Saves final game results in score.bin
•	Stores:
    board size
    number of moves
•	Can view all previously completed game results.
How to Play
1.	Run the program
2.	Choose Start Game
3.	Select board size (2, 4, 6)
4.	Enter two positions:
5.	row col
6.	Cards flip:
    If matched → stay open
    If not → flip back after message
7.	Game ends when all pairs are found
8.	Player can save final score
9.	High scores can be viewed from the menu
Saving & Loading
Save
At any point choosing -1 -1 prompts:
Do you want to save game before exit (y/n):
Load
At the game start:
Do you want to play saved game (y/n):
If match.txt exists, game resumes where you left.
Concepts
•	File Handling (Binary & Text)
•	Dynamic Memory 
•	Loops, Conditionals, Functions
•	Uses Arrays
•	Multiple Functions
•	Proper input validation
•	ASCII-based UI