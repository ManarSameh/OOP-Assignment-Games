#ifndef ULTIMATE_XO_H
#define ULTIMATE_XO_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


template <typename T>
class X_O_Board {
private:
    T board[3][3];
    int moves;
public:
    X_O_Board();
    bool update_board(int x, int y, T symbol);
    T get_cell(int x, int y) const;
    bool is_win() const;
    bool is_draw() const;
    void display_board() const;
    bool is_full() const;
};


template <typename T>
class UltimateXO_Board {
private:
    X_O_Board<T> subBoards[3][3];
    T mainBoard[3][3];
    int moves;
public:
    UltimateXO_Board();
    bool update_board(int subX, int subY, int x, int y, T symbol);
    void display_board();
    bool is_win();
    bool is_draw();
    bool game_is_over();
};


template <typename T>
class UltimateXO_Player {
protected:
    string name;
    T symbol;
public:
    UltimateXO_Player(string name, T symbol);
    string get_name() const;
    T get_symbol() const;
    virtual void getmove(int& subX, int& subY, int& x, int& y);
};

template <typename T>
class UltimateXO_Random_Player : public UltimateXO_Player<T> {
public:
    UltimateXO_Random_Player(T symbol);
    void getmove(int& subX, int& subY, int& x, int& y) override;
};


template <typename T>
X_O_Board<T>::X_O_Board() : moves(0) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = 0;
        }
    }
}

template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T symbol) {
    if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != 0) {
        return false;
    }
    board[x][y] = symbol;
    moves++;
    return true;
}

template <typename T>
T X_O_Board<T>::get_cell(int x, int y) const {
    return board[x][y];
}

template <typename T>
bool X_O_Board<T>::is_win() const {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0) ||
            (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 0)) {
            return true;
        }
    }
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0)) {
        return true;
    }
    return false;
}

template <typename T>
bool X_O_Board<T>::is_draw() const {
    return (moves == 9 && !is_win());
}

template <typename T>
void X_O_Board<T>::display_board() const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << (board[i][j] == 0 ? '.' : board[i][j]) << " ";
        }
        cout << endl;
    }
}

template <typename T>
bool X_O_Board<T>::is_full() const {
    return moves == 9;
}


template <typename T>
UltimateXO_Board<T>::UltimateXO_Board() : moves(0) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mainBoard[i][j] = 0;
        }
    }
}

template <typename T>
bool UltimateXO_Board<T>::update_board(int subX, int subY, int x, int y, T symbol) {
    if (mainBoard[subX][subY] != 0) {
        return false;
    }
    if (subBoards[subX][subY].update_board(x, y, symbol)) {
        moves++;
        if (subBoards[subX][subY].is_win()) {
            mainBoard[subX][subY] = symbol;
        }
        return true;
    }
    return false;
}

template <typename T>
void UltimateXO_Board<T>::display_board() {
    for (int subX = 0; subX < 3; subX++) {
        for (int row = 0; row < 3; row++) {
            for (int subY = 0; subY < 3; subY++) {
                for (int col = 0; col < 3; col++) {
                    cout << subBoards[subX][subY].get_cell(row, col) << " ";
                }
                cout << " | ";
            }
            cout << endl;
        }
        cout << "-----------------------------" << endl;
    }
}

template <typename T>
bool UltimateXO_Board<T>::is_win() {
    for (int i = 0; i < 3; i++) {
        if ((mainBoard[i][0] == mainBoard[i][1] && mainBoard[i][1] == mainBoard[i][2] && mainBoard[i][0] != 0) ||
            (mainBoard[0][i] == mainBoard[1][i] && mainBoard[1][i] == mainBoard[2][i] && mainBoard[0][i] != 0)) {
            return true;
        }
    }
    if ((mainBoard[0][0] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][2] && mainBoard[0][0] != 0) ||
        (mainBoard[0][2] == mainBoard[1][1] && mainBoard[1][1] == mainBoard[2][0] && mainBoard[0][2] != 0)) {
        return true;
    }
    return false;
}

template <typename T>
bool UltimateXO_Board<T>::is_draw() {
    return (moves == 81 && !is_win());
}

template <typename T>
bool UltimateXO_Board<T>::game_is_over() {
    return is_win() || is_draw();
}


template <typename T>
UltimateXO_Player<T>::UltimateXO_Player(string name, T symbol) : name(name), symbol(symbol) {}

template <typename T>
string UltimateXO_Player<T>::get_name() const {
    return name;
}

template <typename T>
T UltimateXO_Player<T>::get_symbol() const {
    return symbol;
}

template <typename T>
void UltimateXO_Player<T>::getmove(int& subX, int& subY, int& x, int& y) {
    cout << "Enter sub-board and cell coordinates (subX subY x y):";
    cin >> subX >> subY >> x >> y;
}

template <typename T>
UltimateXO_Random_Player<T>::UltimateXO_Random_Player(T symbol) : UltimateXO_Player<T>("Random Player", symbol) {
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void UltimateXO_Random_Player<T>::getmove(int& subX, int& subY, int& x, int& y) {
    subX = rand() % 3;
    subY = rand() % 3;
    x = rand() % 3;
    y = rand() % 3;
}

#endif