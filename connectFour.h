
#ifndef _CONNECTFOUR_H
#define _CONNECTFOUR_H

#include "BoardGame_Classes.h"


template <typename T>
class connectFour : public Board<T> {
public:
    connectFour ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};


template <typename T>
class connect4_Player : public Player<T> {
public:
    connect4_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class connect4_Random_Player : public RandomPlayer<T>{
public:
    connect4_Random_Player (T symbol);
    void getmove(int& x, int &y) ;
};


//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for connectFour
template <typename T>
connectFour<T>::connectFour() {
    this->rows = 6;
    this->columns = 7;
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
bool connectFour<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(y < 0 || y >= this->columns)) {
        while(x < 5 && this->board[x + 1][y] == 0 )
        {
            x++;
        }
        if(x == 0 && (this->board[x][y] != 0))
        {
            return false;
        }
        this->n_moves++;
        this->board[x][y] = toupper(mark);
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void connectFour<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if(this->board[i][j] == 0)
            {
                cout << setw(2) << '-' << " |";
            }
            else{
            cout << setw(2) << this->board[i][j] << " |";
            }
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool connectFour<T>::is_win() {
    // Check rows
    for (int row = 0; row < this->rows; ++row) {
        for (int col = 0; col < this->columns - 3; ++col) {
            if (this->board[row][col] == this->board[row][col + 1] &&
                this->board[row][col + 1] == this->board[row][col + 2] &&
                this->board[row][col + 2] == this->board[row][col + 3] &&
                this->board[row][col + 3] != 0)
                return true;
        }
    }
    // Check columns
    for (int col = 0; col < this->columns; ++col) {
        for (int row = 0; row < this->rows - 3; ++row) {
            if (this->board[row][col] == this->board[row + 1][col] &&
                this->board[row + 1][col] == this->board[row + 2][col] &&
                this->board[row + 2][col] == this->board[row + 3][col] &&
                this->board[row + 3][col]!= 0)
                return true;
        }
    }
    // Check diagonals
    for (int row = 0; row < this->rows - 3; ++row) {
        for (int col = 0; col < this->columns - 3; ++col) {
            if (this->board[row][col] == this->board[row + 1][col + 1] &&
                this->board[row + 1][col + 1] == this->board[row + 2][col + 2] &&
                this->board[row + 2][col + 2] == this->board[row + 3][col + 3] &&
                this->board[row + 3][col + 3]!= 0)
                return true;
        }
    }

    return false;
}

// Return true if 42 moves are done and no winner
template <typename T>
bool connectFour<T>::is_draw() {
    return this->n_moves == (this->rows * this->columns);
}

// Return true if game is over
template <typename T>
bool connectFour<T>::game_is_over() {
    return this->is_win() || this->is_draw();
}



//--------------------------------------- PLAYERS

template <typename T>
connect4_Player<T>::connect4_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void connect4_Player<T>::getmove(int& x, int& y) {
    cout << "Enter your column" << endl;
    string defy;
    while(true)
    {
    cin >> defy;
    try
    {
        y = stoi(defy);
        break;

    }
    catch(const exception& e)
    {
        cout << "Invalid input. Please enter a valid column number." << endl;
    }
    }
    x = 0;
}

template <typename T>
connect4_Random_Player<T>::connect4_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0))); 
}

template <typename T>
void connect4_Random_Player<T>::getmove(int& x, int& y) {
    x = 0;
    y = rand() % this->dimension;
}

#endif
