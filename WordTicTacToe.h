#ifndef _WORDTICTACTOE_H
#define _WORDTICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


bool load_dictionary(const string& filename, vector<string>& dictionary) {
    ifstream file(filename);
    string word;
    while (file >> word) {
        dictionary.push_back(word);
    }
    file.close();
    return !dictionary.empty();
}

template<typename T>
class WordTicTacToeBoard : public Board<T> {
private:
    vector<string> dictionary;
    string winning_word;

public:
    WordTicTacToeBoard(const string& dic_file) {
        this->rows = 3;
        this->columns = 3;
        this->board = new char*[this->rows];
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new char[this->columns];
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = '.';
            }
        }
        this->n_moves = 0;

        if (!load_dictionary(dic_file, dictionary)) {
            cerr << "Error: Could not load dictionary from " << dic_file << endl;
            exit(1);
        }
    }

    bool update_board(int x, int y, T symbol) override {
        if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && this->board[x][y] == '.') {
            this->board[x][y] = toupper(symbol);
            this->n_moves++;
            return true;
        }
        return false;
    }

    void display_board() override {
        cout << "Current Board: " << endl;
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                cout << this->board[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool is_valid_word() {
        for (int i = 0; i < this->rows; i++) {
            string row_word = "";
            string col_word = "";
            for (int j = 0; j < this->columns; j++) {
                row_word += this->board[i][j];
                col_word += this->board[j][i];
            }
            if (find(dictionary.begin(), dictionary.end(), row_word) != dictionary.end()) {
                winning_word = row_word;
                return true;
            }
            if (find(dictionary.begin(), dictionary.end(), col_word) != dictionary.end()) {
                winning_word = col_word;
                return true;
            }
        }

        string diag1_word = "";
        string diag2_word = "";
        for (int i = 0; i < this->rows; i++) {
            diag1_word += this->board[i][i];
            diag2_word += this->board[i][this->columns - i - 1];
        }

        if (find(dictionary.begin(), dictionary.end(), diag1_word) != dictionary.end()) {
            winning_word = diag1_word;
            return true;
        }
        if (find(dictionary.begin(), dictionary.end(), diag2_word) != dictionary.end()) {
            winning_word = diag2_word;
            return true;
        }

        return false;
    }

    bool is_win() override {
        return is_valid_word();
    }

    bool is_draw() override {
        if (this->n_moves == 9 && !is_valid_word()) {
            return true;
        }
        return false;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
    string get_winning_word() const {
        return winning_word;
    }
};

template<typename T>
class WordTicTacToePlayer : public Player<T> {
public:
    WordTicTacToePlayer(string name, T symbol) : Player<T>(name, symbol) {}

    void getmove(int &x, int &y) override {
        while (true) {
            cout << "\n" << this->getname() << "'s turn! Enter your move (row and column): ";
            cin >> x >> y;
            char c ;
            cout << "Enter a letter: "<<endl ;
            cin >> c;
            this->symbol = c;

            if (x >= 0 && x < 3 && y >= 0 && y < 3) {
                break;
            } else {
                cout << "Invalid move. Please try again!" << endl;
            }
        }
    }
};

template<typename T>
class RandomWordTicTacToePlayer : public RandomPlayer<T> {
public:
    RandomWordTicTacToePlayer(T symbol) : RandomPlayer<T>(symbol) {}

    void getmove(int &x, int &y) override {
        x = rand() % 3;
        y = rand() % 3;
        this->symbol = 'A' + rand() % 26;
    }
};

#endif