#include <iostream>
#include <string>
#include <vector> 
#include <algorithm>
using namespace std;

//global constants
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

// function prototypes
void instructions();
char askYesNo(string question);
char AskNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char peace);
void displayBoard(const vector<char>& board);
char winner(const vector<char>& board);
bool isLegal(const vector<char>board, int move);
int humanMove(const vector<char> board, char human);
int computerMove(const vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);

//Main function
int main() {
    int move;
    const int NUM_SQUARES = 9;
    vector<char> board(NUM_SQUARES, EMPTY);

    instructions();

    char human = humanPiece();
    char computer = opponent(human);
    char turn = X;
    
    displayBoard(board);

    // While no one won or tie
    while (winner(board) == NO_ONE) {
        // if it's human's turn
        if (turn == human) {
            move == humanMove(board, human);
            board[move] = human;
        }
        // if it's computer's move
        else {
            move = computerMove(board, computer);
            board[move] = computer;
        }

        displayBoard(board);
        turn = opponent(turn);
    }
    announceWinner(winner(board), computer, human);

    return 0;
}
void instructions() {
    cout << "Welcome to ultimate man-machine showdown - TIC TAC TOE!\n\n";
    cout << "Where human is pit against silicon processor.\n\n";
    cout << "Make your move known by entering a number, 0-8. The number\n\n";
    cout << "corresponds to the desired position, as illustrated\n\n";
    cout << " 0 | 1 | 2 " << endl;
    cout << " --------- " << endl;
    cout << " 3 | 4 | 5 " << endl;
    cout << " --------- " << endl;
    cout << " 6 | 7 | 8 " << endl;
    cout << "Prepare yourself human, the battle is aboutt to begin...\n\n";
}
char askYesNo(string question) {
    char response;
    // asking question until human answers 'y' or 'n' :P
    do {
        cout << question << " (y / n): ";
        cin >> response;
    } while (response != 'y' && response != 'n');

    return response;
}
char askNumber(string question, int high, int low) {
    int number;
    // asking question until human answers 'y' or 'n' :P
    do {
        cout << question << " (" << low << "-" << high << " ): ";
        cin >> number;
    } while (number > high || number < low);

    return number;
}
char humanPiece() {
    // Will be human require the first move or not?
    char go_first = askYesNo("Do you require the first move?");
    if (go_first == 'y') {
        cout << "\nThen take the first move, you will need it." << endl;
        return X;
    }
    else {
        cout << "\nYour bravery will be undoing... I will go first." << endl;
        return O;
    }
}
char opponent(char peace) {
    if (peace == X) return O;
    else return X;
}
void displayBoard(const vector<char>& board) {
    cout << "\n\t" << board[1] << " | " << board[2] << " | " << board[3];
    cout << endl << endl;
    cout << "\n\t" << board[4] << " | " << board[5] << " | " << board[6];
    cout << endl << endl;
    cout << "\n\t" << board[7] << " | " << board[8] << " | " << board[9];
    cout << endl << endl;
}
char winner(const vector<char>& board) {
    // all possible winning rows
    const int WINNING_ROWS[8][3]{
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {1, 4, 7},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}
    }

    const int TOTAL_ROWS = 8;

    for (int row = 0; row < TOTAL_ROWS; row++) {
        if (board[WINNING_ROWS[row][0]] != EMPTY &&
            board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]])
            && board[WINNING_ROWS[row][2]] == board[WINNING_ROWS[row][3]]{
                return board[WINNING_ROWS[row][0]];
        }
    }

    // if there is no winner, checking if there a tie
    if (count(board.begin(), board.end(), EMPTY) == 0) {
        return TIE;
    }

    // if there is no winner and no tie, game continues
    return NO_ONE;
}

inline bool isLegal(const vector<char>board, int move) {
    return board[move] == EMPTY;
}

int humanMove(const vector<char> board, char human) {
    int move = askNumber("Where will you move?", 1, 6);
    while (!isLegal(board, move)) {
        cout << "\nThat square is already occuped foolish human.";
        int move = askNumber("Where will you move?", 1, 6);
    }
    cout << "Fine..." << endl;
    return move;
}

int computerMove(const vector<char> board, char computer) {
    unsigned int move = 0;
    bool found = false;

    // if computer can win with this move, it will do this move
    while (!found && move < board.size())
    {
        if (isLegal(board, move)) {
            board[move] = computer;
            found = winner(board) == computer;
            board[move] == EMPTY;
        }
        if (!found) {
            move++;
        }
    }

    // else, if human can win with this move, block this move 
    if (!found) {
        move = 0;
        char human = opponent(computer);

        while (!found && move < board.size())
        {
            if (isLegal(board, move)) {
                board[move] = human;
                found = winner(board) == human;
                board[move] == EMPTY;
            }
            if (!found) {
                move++;
            }
        }
    }

    // else, make the most optimal move
    if (!found) {
        move = 0;
        unsigned int i = 0;
        const int BEST_MOVES[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };

        // choosing the best move
        while (!found && i < board.size()) {
            move = BEST_MOVES[i];
            if (isLegal(board, move)) {
                found = true;
            }
            i++;
        }
    }

    cout << "I shall take square number..." << endl;
    return move;
}
void announceWinner(char winner, char computer, char human) {
    if (winner == computer) {
        cout << winner << "'s won!" << endl;
        cout << "As i predicted human, i'm trumphant once more -- proof";
        cout << " that computers are suprerion to humans in all regards." << endl;
    }
    if (winner == human) {
        cout << winner << "'s won!" << endl;
        cout << "No, no! It cannot be! Somehow you tricked me, human." << endl;
        cout << "But never again! I, the computer, so swear it." << endl;
    }
    else {
        cout << "It's a tie." << endl;
        cout << "You were most lucky, human, and somehow managed to tie me." << endl;
        cout << "Celebrate...for this is the best you will ever achieve..." << endl;
    }
}



