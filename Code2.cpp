#include <iostream>
#include <vector>
#include <limits>  // for numeric_limits
#include <chrono>  // for timer
#include <thread>  // for sleep_for
#include <cstdlib> // for rand
#include <ctime>   // for time (seed rand)
using namespace std;

class TicTacToe {
private:
    char board[3][3];
    char currentToken;
    string player1, player2;
    bool singlePlayerMode;
    bool gameOver;
    int movesCount;
    int scoreX, scoreO;
    vector<pair<int,int>> moveHistory; // for undo
    int moveTimeLimit; // seconds per move

public:
    TicTacToe() {
        resetBoard();
        currentToken = 'X';
        scoreX = 0;
        scoreO = 0;
        movesCount = 0;
        singlePlayerMode = false;
        gameOver = false;
        moveTimeLimit = 10; // 10 seconds per move
        srand(time(0)); // seed random for AI moves
    }

    void resetBoard() {
        char ch = '1';
        for (int i=0; i<3; i++){
            for (int j=0; j<3; j++){
                board[i][j] = ch++;
            }
        }
        movesCount = 0;
        moveHistory.clear();
        gameOver = false;
        currentToken = 'X';
    }

    void displayBoard() {
        cout << "\n";
        for (int i=0; i<3; i++){
            cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << "\n";
            if(i != 2) cout << "---|---|---\n";
        }
        cout << "\n";
    }

    bool checkWin() {
        // Rows, columns, diagonals
        for(int i=0; i<3; i++){
            if(board[i][0] == currentToken && board[i][1] == currentToken && board[i][2] == currentToken) return true;
            if(board[0][i] == currentToken && board[1][i] == currentToken && board[2][i] == currentToken) return true;
        }
        if(board[0][0] == currentToken && board[1][1] == currentToken && board[2][2] == currentToken) return true;
        if(board[0][2] == currentToken && board[1][1] == currentToken && board[2][0] == currentToken) return true;

        return false;
    }

    bool checkDraw() {
        return movesCount >= 9;
    }

    void switchPlayer() {
        currentToken = (currentToken == 'X') ? 'O' : 'X';
    }

    void getPlayerNames() {
        cout << "Enter Player 1 name (X): ";
        getline(cin, player1);
        cout << "Do you want to play single player mode? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore(); // flush newline
        if(choice == 'y' || choice == 'Y') {
            singlePlayerMode = true;
            player2 = "Computer";
        } else {
            singlePlayerMode = false;
            cout << "Enter Player 2 name (O): ";
            getline(cin, player2);
        }
    }

    bool validateMove(int move) {
        if(move < 1 || move > 9) return false;
        int r = (move - 1) / 3;
        int c = (move - 1) % 3;
        if(board[r][c] == 'X' || board[r][c] == 'O') return false;
        return true;
    }

    void undoMove() {
        if(moveHistory.empty()) {
            cout << "No moves to undo.\n";
            return;
        }
        pair<int,int> lastMove = moveHistory.back();
        moveHistory.pop_back();
        board[lastMove.first][lastMove.second] = '1' + lastMove.first*3 + lastMove.second;
        movesCount--;
        switchPlayer();
        cout << "Last move undone. Current board:\n";
        displayBoard();
    }

    void playerMove() {
        int move;
        bool valid = false;
        auto start = chrono::steady_clock::now();

        while(!valid) {
            cout << (currentToken == 'X' ? player1 : player2) << "'s turn (" << currentToken << "). Enter your move (1-9) or 0 to undo: ";

            // Timer implementation
            while(!cin.rdbuf()->in_avail()) {
                auto now = chrono::steady_clock::now();
                auto elapsed = chrono::duration_cast<chrono::seconds>(now - start).count();
                if(elapsed >= moveTimeLimit){
                    cout << "\nTime limit exceeded! Move skipped.\n";
                    switchPlayer();
                    return;
                }
                this_thread::sleep_for(chrono::milliseconds(100));
            }

            cin >> move;

            if(move == 0) {
                undoMove();
                return;
            }

            if(cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            if(validateMove(move)) {
                valid = true;
            } else {
                cout << "Invalid move, cell occupied or out of range.\n";
            }
        }
        int r = (move - 1) / 3;
        int c = (move - 1) % 3;
        board[r][c] = currentToken;
        moveHistory.push_back({r, c});
        movesCount++;
    }

    void computerMove() {
        cout << "Computer's turn (" << currentToken << "). Thinking...\n";
        // Simple AI: pick random empty cell
        vector<int> emptyCells;
        for(int i=0; i<9; i++){
            int r = i/3, c = i%3;
            if(board[r][c] != 'X' && board[r][c] != 'O'){
                emptyCells.push_back(i+1);
            }
        }
        if(emptyCells.empty()) return; // no move

        int choice = emptyCells[rand() % emptyCells.size()];
        int r = (choice - 1) / 3;
        int c = (choice - 1) % 3;
        board[r][c] = currentToken;
        moveHistory.push_back({r,c});
        movesCount++;
        displayBoard();
    }

    void playGame() {
        getPlayerNames();
        char playAgain = 'y';

        while(playAgain == 'y' || playAgain == 'Y') {
            resetBoard();
            displayBoard();
            gameOver = false;

            while(!gameOver) {
                if(singlePlayerMode && currentToken == 'O'){
                    computerMove();
                } else {
                    playerMove();
                }

                displayBoard();

                if(checkWin()){
                    cout << (currentToken == 'X' ? player1 : player2) << " (" << currentToken << ") wins!\n";
                    if(currentToken == 'X') scoreX++;
                    else scoreO++;
                    gameOver = true;
                } else if(checkDraw()){
                    cout << "It's a draw!\n";
                    gameOver = true;
                } else {
                    switchPlayer();
                }
            }

            cout << "Scores:\n" << player1 << " (X): " << scoreX << "\n" << player2 << " (O): " << scoreO << "\n";

            cout << "Play again? (y/n): ";
            cin >> playAgain;
            cin.ignore(); // flush newline
        }

        cout << "Thanks for playing! Final scores:\n" << player1 << " (X): " << scoreX << "\n" << player2 << " (O): " << scoreO << "\n";
    }
};

int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}
