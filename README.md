# Tic-Tac-Toe Game 

A simple two-player **Tic-Tac-Toe** (or **Noughts and Crosses**) game built using **C++**. Played via the console, it supports turn-based input, checks for win or draw conditions, and displays the board after each move.

---

##  Features

- Two-player input using names
- Player turn tracking using 'X' and 'O'
- Input validation for already-occupied cells
- Winner detection for all row, column, and diagonal combinations
- Draw detection when all cells are filled
- Clear and formatted game board display after each move

---

##  How to Run

###  Compile

Open terminal / command prompt and navigate to the project folder.

```bash
g++ code.cpp -o tictactoe
```

### ▶ Run

```bash
./tictactoe
```

---

##  Project Structure

```
Tic-Tac-Toe/
├── code.cpp       # Main game code
└── README.md      # Project description
```

---

##  Sample Gameplay

```
Enter Player Name: 
Alice
Enter Player Name:
Bob
Alice is player 1 so he will play first.
Bob is player 2 so he will play second.

    |    |   
1   | 2  | 3
--------------
    |    |   
4   | 5  | 6
--------------
    |    |   
7   | 8  | 9
--------------

Alice, Enter The Digit:
5
...

Bob Wins!
```

---

##  Possible Future Improvements

- Single-player mode with basic AI
- GUI using C++ with graphics libraries
- Score tracking across rounds
- Input sanitization for invalid/non-numeric entries

---

##  License

This project is open-source and free to use.
