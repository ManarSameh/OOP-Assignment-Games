#ifndef _5X5X_O_H
#define _5X5X_O_H

#include "BoardGame_Classes.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cctype> // for toupper()
#include <limits> // for numeric_limits

using namespace std;

// ------------------------------------ CLASS DEFINITIONS

template <typename T>
class X_O_Board : public Board<T> {
public:
    X_O_Board();
    ~X_O_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    void display_winner(); 

    

private:
    int count_n_in_a_row(T symbol, int n);
};

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class X_O_Random_Player : public RandomPlayer<T> {
public:
    X_O_Random_Player(T symbol);
    void getmove(int& x, int& y) override;
};

// ------------------------------------ IMPLEMENTATION

template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 5;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns]{};
    }
    this->n_moves = 0;
}

template <typename T>
X_O_Board<T>::~X_O_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->board[x][y] = toupper(mark);
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << (this->board[i][j] ? this->board[i][j] : '.') << " |";
        }
        cout << "\n" << string(this->columns * 12, '-');
    }
    cout << endl;
}

template <typename T>
int X_O_Board<T>::count_n_in_a_row(T symbol, int n) {
    int count = 0;

    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - n; j++) {
            // Row check
            bool row_win = true;
            for (int k = 0; k < n; k++) {
                if (this->board[i][j + k] != symbol) {
                    row_win = false;
                    break;
                }
            }
            if (row_win) count++;

            // Column check
            bool col_win = true;
            for (int k = 0; k < n; k++) {
                if (this->board[j + k][i] != symbol) {
                    col_win = false;
                    break;
                }
            }
            if (col_win) count++;
        }
    }

    // Check diagonals
    for (int i = 0; i <= this->rows - n; i++) {
        for (int j = 0; j <= this->columns - n; j++) {
            // Diagonal (top-left to bottom-right)
            bool diag1_win = true;
            for (int k = 0; k < n; k++) {
                if (this->board[i + k][j + k] != symbol) {
                    diag1_win = false;
                    break;
                }
            }
            if (diag1_win) count++;

            // Diagonal (top-right to bottom-left)
            bool diag2_win = true;
            for (int k = 0; k < n; k++) {
                if (this->board[i + k][j + n - 1 - k] != symbol) {
                    diag2_win = false;
                    break;
                }
            }
            if (diag2_win) count++;
        }
    }

    return count;
}

template <typename T>
bool X_O_Board<T>::is_win() {
    return count_n_in_a_row('X', 3) > 0 || count_n_in_a_row('O', 3) > 0;
}

template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == this->rows * this->columns) && !is_win();
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    // Ends when all 24 moves are made or someone wins
    return (this->n_moves == 24);
}

template <typename T>
void X_O_Board<T>::display_winner() {
    int x_count = count_n_in_a_row('X', 3);
    int o_count = count_n_in_a_row('O', 3);

    cout << "\nFinal Results:\n";
    cout << "Player X has " << x_count << " three-in-a-rows.\n";
    cout << "Player O has " << o_count << " three-in-a-rows.\n";

    if (x_count > o_count) {
        cout << "Player X wins!\n";
    } else if (o_count > x_count) {
        cout << "Player O wins!\n";
    } else {
        cout << "It's a tie!\n";
    }
}


template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    while (true) {
        cout << "\nPlease enter your move (x y): ";
        if (cin >> x >> y && x >= 0 && x < 5 && y >= 0 && y < 5) {
            break;
        } else {
            cout << "Invalid input. Please enter valid coordinates within the range (0-4).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif // _5X5X_O_H




