#ifndef _SUS_GAME_H
#define _SUS_GAME_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits>

using namespace std;


template <typename T>
class SUS_Board : public Board<T> {
     static int countP1;
     static int countP2;
     T currentplayersymbol;
     vector<int>vec;
public:
    void  switchPlayer(){
        if(currentplayersymbol == 'S')
        currentplayersymbol = 'U';
        else
        currentplayersymbol = 'S';

    }
    SUS_Board();
    ~SUS_Board();
    bool update_board(int x, int y, T symbol) override;
    void display_board() override;
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;

private:
    void count_SUS_S();
};
template<typename T>
int SUS_Board<T>::countP1 = 0;

template<typename T>
int SUS_Board<T>::countP2 = 0;

template <typename T>
class SUS_Player : public Player<T> {
public:
    SUS_Player(string name, T symbol);
    void getmove(int& x, int& y) override;
};

template <typename T>
class SUS_Random_Player : public RandomPlayer<T> {
public:
    SUS_Random_Player(T symbol);
    void getmove(int& x, int& y) override;
};


template <typename T>
SUS_Board<T>::SUS_Board() {
    this->rows = this->columns = 3;
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns]{};
    }
    this->currentplayersymbol = 'S';
    this->n_moves = 0;
}

template <typename T>
SUS_Board<T>::~SUS_Board() {
    for (int i = 0; i < this->rows; i++) {
        delete[] this->board[i];
    }
    delete[] this->board;
}

template <typename T>
bool SUS_Board<T>::update_board(int x, int y, T mark) {
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->board[x][y] = toupper(mark);
        this->n_moves++;
        return true;
    }
    return false;
}

template <typename T>
void SUS_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << (this->board[i][j] ? this->board[i][j] : '.') << " |";
        }
        cout << "\n" << string(this->columns * 4, '-');
    }
    cout << endl;
}

template <typename T>
void SUS_Board<T>::count_SUS_S() {

    for (int i = 0; i < this->rows; i++) {
    
    auto it1 = std::find(vec.begin(), vec.end(), 3 * i + 0);
    auto it2 = std::find(vec.begin(), vec.end(), 3 * i + 1);
    auto it3 = std::find(vec.begin(), vec.end(), 3 * i + 2);

    
    if (this->board[i][0] == 'S' && this->board[i][1] == 'U' && this->board[i][2] == 'S' &&
        (it1 == vec.end() && it2 == vec.end() && it3 == vec.end())) {
        if (it1 == vec.end()) vec.push_back(3 * i + 0);
        if (it2 == vec.end()) vec.push_back(3 * i + 1);
        if (it3 == vec.end()) vec.push_back(3 * i + 2);

        if (currentplayersymbol == 'S')
            ++countP1;
        else
            ++countP2;
    }

    
    it1 = std::find(vec.begin(), vec.end(), i);
    it2 = std::find(vec.begin(), vec.end(), i + 3);
    it3 = std::find(vec.begin(), vec.end(), i + 6);


    if (this->board[0][i] == 'S' && this->board[1][i] == 'U' && this->board[2][i] == 'S' &&
        (it1 == vec.end() && it2 == vec.end() && it3 == vec.end())) {
        if (it1 == vec.end()) vec.push_back(i);
        if (it2 == vec.end()) vec.push_back(i + 3);
        if (it3 == vec.end()) vec.push_back(i + 6);

        if (currentplayersymbol == 'S')
            ++countP1;
        else
            ++countP2;
    }
}

auto it1 = std::find(vec.begin(), vec.end(), 0);
auto it2 = std::find(vec.begin(), vec.end(), 4);
auto it3 = std::find(vec.begin(), vec.end(), 8);

if (this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S' &&
    (it1 == vec.end() && it2 == vec.end() && it3 == vec.end())) {
    if (it1 == vec.end()) vec.push_back(0);
    if (it2 == vec.end()) vec.push_back(4);
    if (it3 == vec.end()) vec.push_back(8);

    if (currentplayersymbol == 'S')
        ++countP1;
    else
        ++countP2;
}

it1 = std::find(vec.begin(), vec.end(), 2);
it2 = std::find(vec.begin(), vec.end(), 4);
it3 = std::find(vec.begin(), vec.end(), 6);

if (this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S' &&
    (it1 == vec.end() && it2 == vec.end() && it3 == vec.end())) {
    if (it1 == vec.end()) vec.push_back(2);
    if (it2 == vec.end()) vec.push_back(4);
    if (it3 == vec.end()) vec.push_back(6);

    if (currentplayersymbol == 'S')
        ++countP1;
    else
        ++countP2;
}

this->switchPlayer();

}

template <typename T>
bool SUS_Board<T>::is_win() {
    count_SUS_S();
     if(this->countP1 > this->countP2 && this->n_moves == 9) {
         cout << "score player 1 is :"<< countP1 << endl;
         cout << "score player 2 is :"<< countP2 << endl;
         return 1;
     }if(this->countP1 < this->countP2 && this->n_moves == 9) {
         cout << "score player 1 is :"<< countP1 << endl;
         cout << "score player 2 is :"<< countP2 << endl;
         return 1;
     }
        return 0;
}

template <typename T>
bool SUS_Board<T>::is_draw() {
    if((this->n_moves == 9)  && !is_win()){
        cout << "score player 1 is :"<< countP1 << endl;
        cout << "score player 2 is :"<< countP2 << endl;
        return 1;
    }
    return 0;
}

template <typename T>
bool SUS_Board<T>::game_is_over() {
    return is_draw() || is_win();
}

template <typename T>
SUS_Player<T>::SUS_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void SUS_Player<T>::getmove(int& x, int& y) {
    while (true) {
        cout << "\nPlease enter your move (x y): ";
        if (cin >> x >> y && x >= 0 && x < 3 && y >= 0 && y < 3) {
            break;
        } else {
            cout << "Invalid input. Please enter valid coordinates within the range (0-2).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

template <typename T>
SUS_Random_Player<T>::SUS_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif