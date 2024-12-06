#ifndef _PYRAMIDXO_H
#define _PYRAMIDXO_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

template<typename T>

class PyramidBoard : public Board<T> {

public:
    PyramidBoard() {
        this->rows = 3;
        this->columns = 5;
        this->board = new char *[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                if (i == 0 && j == 2) {
                    this->board[i][j] = '.';
                }
                else if(i == 1 && j == 0 || i == 1 & j == 4){
                    this->board[i][j]= ' ';
                }
                else if(i == 1){
                    this->board[i][j]='.';
                }
                else if(i == 2){
                    this->board[i][j]='.';
                }
                else {
                    this->board[i][j]=' ';
                }
            }
        }
      this->  n_moves = 0;
    }

    bool update_board(int x, int y, T symbol) override {

        if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] != ' ' && this->board[x][y] == '.') {
            this->board[x][y] = toupper(symbol);
            this->n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                cout << this->board[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool is_win() override {

        if (this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2] && this->board[0][2] != '.') {
                return true;
            }
        if (this->board[1][1] == this->board[1][2] && this->board[1][2] == this->board[1][3] && this->board[1][1] != '.') {
            return true;
        }
        if (this->board[2][0] == this->board[2][1] && this->board[2][1] == this->board[2][2] && this->board[2][0] != '.') {
            return true;
        }
        if (this->board[2][1] == this->board[2][2] && this->board[2][2] == this->board[2][3] && this->board[2][1] != '.') {
            return true;
        }
        if (this->board[2][2] == this->board[2][3] && this->board[2][3] == this->board[2][4] && this->board[2][2] != '.') {
            return true;
        }
        if (this->board[0][2] == this->board[1][3] && this->board[1][3] == this->board[2][4] && this->board[0][2] != '.') {
            return true;
        }
        if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != '.') {
            return true;
        }
            return false;
    }

    bool is_draw() override {
        if (this->n_moves == 9 && !is_win()) {
            return true;
        }

        return false;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template<typename T>

class HumanPlayer : public Player<T> {
public:
    HumanPlayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int &x, int &y) override {
        while (true) {
            cout << "\nPlease enter your move x and y (0 to 2) separated by spaces:";
            cin >> x >> y;

            if (x >= 0 && x < 3 && y >= 0 && y < 5) {
                break;
            } else {
                cout << "Invalid move. Please try again!" << endl;
            }
        }
    }
};

template<typename T>

class RandomPyramidPlayer : public RandomPlayer<T> {
public:
    RandomPyramidPlayer(T symbol) : RandomPlayer<T>(symbol) {}


    void getmove(int &x, int &y) override {
        x = rand() % 3;
        y = rand() % 5;
    }
};

#endif