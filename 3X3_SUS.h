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
#include <cctype> // for toupper()
#include <limits> // for numeric_limits

using namespace std;

// ------------------------------------ CLASS DEFINITIONS

int* ptr;

template <typename T>
class SUS_Board : public Board<T> {
    static int countP1;
    static int countP2;
    T currentplayersymbol;
    vector<int> vec;
    int n_moves;


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
    void count_SUS_S(); // Count "S-U-S" sequences in rows, columns, and diagonals
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

// ------------------------------------ IMPLEMENTATION

template <typename T>
SUS_Board<T>::SUS_Board() {
    this->rows = this->columns = 3; // Game size is 3x3
    this->board = new T*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new T[this->columns]{}; // Initialize with empty spaces
    }
    this->currentplayersymbol = 'U';
    this->n_moves = 0;
    ptr = &n_moves;
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
    if(this->n_moves==9){
        this->n_moves++;
        return 1;
    }
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == 0) {
        this->board[x][y] = toupper(mark); // Store upper case 'S' or 'U'
        this->n_moves++;
        this->switchPlayer();
        return true;
    }
    return false;
}

template <typename T>
void SUS_Board<T>::display_board() {
    if(this->n_moves==9){
        return; //
    }
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
        // البحث عن المواقع في الصف
        int foundCount = std::count(vec.begin(), vec.end(), 3 * i + 0);
        int foundCount1 = std::count(vec.begin(), vec.end(), 3 * i + 1);
        int foundCount2 = std::count(vec.begin(), vec.end(), 3 * i + 2);

        // Row check
        if (this->board[i][0] == 'S' && this->board[i][1] == 'U' && this->board[i][2] == 'S' &&
            (foundCount == 0 || foundCount1 == 0 || foundCount2 == 0 )) {
            if (foundCount == 0) vec.push_back(3 * i + 0);
            if (foundCount1 == 0) vec.push_back(3 * i + 1);
            if (foundCount2 == 0) vec.push_back(3 * i + 2);

            if (currentplayersymbol == 'S')
                ++countP1;
            else
                ++countP2;
            }

        // البحث عن المواقع في العمود
        foundCount = std::count(vec.begin(), vec.end(), i);
        foundCount1 = std::count(vec.begin(), vec.end(),  i + 3);
        foundCount2 = std::count(vec.begin(), vec.end(), i + 6);

        // Column check
        if (this->board[0][i] == 'S' && this->board[1][i] == 'U' && this->board[2][i] == 'S' &&
            (foundCount == 0 || foundCount1 == 0 || foundCount2 == 0 )) {
            if (foundCount == 0) vec.push_back(i);
            if (foundCount1 == 0) vec.push_back(i + 3);
            if (foundCount2 == 0) vec.push_back(i + 6);

            if (currentplayersymbol == 'S')
                ++countP1;
            else
                ++countP2;
            }
    }

    // Diagonal (top-left to bottom-right)
    int foundCount = std::count(vec.begin(), vec.end(), 0);
    int foundCount1 = std::count(vec.begin(), vec.end(),  4);
    int foundCount2 = std::count(vec.begin(), vec.end(), 8);

    if (this->board[0][0] == 'S' && this->board[1][1] == 'U' && this->board[2][2] == 'S' &&
        (foundCount == 0 || foundCount1 == 0 || foundCount2 == 0 )) {
        if (foundCount == 0) vec.push_back(0);
        if (foundCount1 == 0) vec.push_back(4);
        if (foundCount2 == 0) vec.push_back(8);

        if (currentplayersymbol == 'S')
            ++countP1;
        else
            ++countP2;
        }

    // Diagonal (top-right to bottom-left)
     foundCount = std::count(vec.begin(), vec.end(), 0);
     foundCount1 = std::count(vec.begin(), vec.end(),  4);
     foundCount2 = std::count(vec.begin(), vec.end(), 8);

    if (this->board[0][2] == 'S' && this->board[1][1] == 'U' && this->board[2][0] == 'S' &&
        (foundCount == 0 || foundCount1 == 0 || foundCount2 == 0 )) {
        if (foundCount == 0) vec.push_back(2);
        if (foundCount1 == 0) vec.push_back(4);
        if (foundCount2 == 0) vec.push_back(6);

        if (currentplayersymbol == 'S')
            ++countP1;
        else
            ++countP2;
        }
}

template <typename T>
bool SUS_Board<T>::is_win() {
    count_SUS_S();
     if(this->countP1 > this->countP2 && this->n_moves == 9) {
         cout << "score player 1 is :"<< countP1 << endl;
         cout << "score player 2 is :"<< countP2 << endl;
         return 1;
     }
    if(this->countP1 < this->countP2 && this->n_moves == 10) {
         cout << "score player 1 is :"<< countP1 << endl;
         cout << "score player 2 is :"<< countP2 << endl;
         return 1;
     }
        return 0;
}

template <typename T>
bool SUS_Board<T>::is_draw() {
if(countP1 == countP2 && this->n_moves == 10) {
        cout << "Player 1 score is  : " << countP1 << endl;
        cout << "Player 2 score is  : " << countP2 << endl;
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
    if( *ptr == 9) return; //
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
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

template <typename T>
void SUS_Random_Player<T>::getmove(int& x, int& y) {
    if(*ptr == 9)return; //
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif // _SUS_GAME_H
