
#ifndef _NUM_X_O_H
#define _NUM_X_O_H

#include "BoardGame_Classes.h"




template <typename T>
class NUM_X_O_Player : public Player<T> {
public:
    NUM_X_O_Player (string name, T symbol);
    void getmove(int& x, int& y);
    bool visted[10];

};

template <typename T>
class NUM_X_O_Random_Player : public RandomPlayer<T>{
public:
    NUM_X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
    bool visted[10];
};

template <typename T>
class NUM_X_O_Board:public Board<T> {
public:
    NUM_X_O_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};


template <typename T>
NUM_X_O_Board<T>::NUM_X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }

    this->n_moves = 0;
}

template <typename T>
bool NUM_X_O_Board<T>::update_board(int x, int y, T mark) {

    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0)) {
        this->n_moves++;
        this->board[x][y] = mark;
        return true;
    }
    return false;
}

template <typename T>
void NUM_X_O_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout  << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}


template <typename T>
bool NUM_X_O_Board<T>::is_win() {

    for (int i = 0; i < this->rows; i++) {
        if (this->board[i][0] + this->board[i][1] + this->board[i][2] == 15) {
            return true;
        }
    }
    for (int j = 0; j < this->columns; j++) {
        if (this->board[0][j] + this->board[1][j] + this->board[2][j] == 15) {
            return true;
        }
    }

    if (this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) {
        return true;
    }
    if (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15) {
        return true;
    }


    return false;
}

template <typename T>
bool NUM_X_O_Board<T>::is_draw() {
    return (this->n_moves == this->rows * this->columns);
}

template <typename T>
bool NUM_X_O_Board<T>::game_is_over() {
    return this->is_win() || this->is_draw();
}


template <typename T>
NUM_X_O_Player<T>::NUM_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {
        for(int i = 0; i < 10; i++)
    {
        this->visted[i] = false;
    }
}

template <typename T>
void NUM_X_O_Player<T>::getmove(int& x, int& y) {
    T sym;
    string defsym, defx, defy;
    do{
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin >> defx >> defy;
        cout << "Enter number" << endl;
        cin >> defsym;
        try
        {
            x = stoi(defx);
            y = stoi(defy);
            sym = stoi(defsym);
        }
        catch(exception e)
        {
            cout << "Invalid input. Please enter a numbers" << endl;
        }
    }while((!(this->symbol % 2 == sym % 2 && sym < 10)) || visted[sym]);
        this->symbol = sym;
        visted[sym] = true;
}


template <typename T>
NUM_X_O_Random_Player<T>::NUM_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void NUM_X_O_Random_Player<T>::getmove(int& x, int& y) {
    T sym;
    do 
    {    
        x = rand() % this->dimension;
        y = rand() % this->dimension;
        sym = rand() % 10;
    }while((!(this->symbol % 2 == sym % 2 && sym < 10)) || visted[sym]);
    this->symbol = sym;
    visted[sym] = true;
}


#endif