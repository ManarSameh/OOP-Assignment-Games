#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

template <typename T>
class X_O_Board : public Board<T> {
public:
    X_O_Board();
    bool update_board(int x, int y, T mark);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player(string name, T symbol);
    void getmove(int& x, int& y);
};

template <typename T>
class X_O_Random_Player : public RandomPlayer<T> {
public:
    X_O_Random_Player(T symbol);
    void getmove(int& x, int& y);
};

bool winner_flag = false;


template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    if (winner_flag) {
        return true;
    }
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->board[x][y] = toupper(mark);
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void X_O_Board<T>::display_board() {
    if (winner_flag) {
        return;
    }

    cout << "\n";
    for (int i = 0; i < this->rows; i++) {
        cout << "| ";
        for (int j = 0; j < this->columns; j++) {
            cout << (this->board[i][j] == 0 ? ' ' : this->board[i][j]) << " | ";
        }
        cout << "\n";
    }
    cout << endl;
}

template <typename T>
bool X_O_Board<T>::is_win() {
    if (winner_flag) {
        return true;
    }


    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            winner_flag = true;
            
        }
    }


    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        winner_flag = true;
        
    }

    return false;
}

template <typename T>
bool X_O_Board<T>::is_draw() {

    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player<T>::getmove(int& x, int& y) {
    if (winner_flag) {
        return;
    }
    cout << "Enter your move (row and column): ";
    cin >> x >> y;
}

template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void X_O_Random_Player<T>::getmove(int& x, int& y) {
    if (winner_flag) {
        return;
    }
    x = rand() % 3;
    y = rand() % 3;
}

#endif