#include <iostream>
#include "BoardGame_Classes.h"
#include "WordTicTacToe.h"

using namespace std;

int wordXO() {
    int choice;
    Player<char>* players[2];
    auto* B = new WordTicTacToeBoard<char>("dic.txt");
    string player1Name, player2Name;

    cout << "Welcome to FCAI Word Tic-Tac-Toe Game. :)\n";

    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
        players[0] = new WordTicTacToePlayer<char>(player1Name, ' ');
        break;
        case 2:
        players[0] = new RandomWordTicTacToePlayer<char>(' ');
        break;
        default:
            cout << "Invalid choice!\n";
        return 0;
    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
        players[1] = new WordTicTacToePlayer<char>(player2Name, ' ');
        break;
        case 2:
        players[1] = new RandomWordTicTacToePlayer<char>(' ');
        break;
        default:
            cout << "Invalid choice!\n";
        return 0;
    }

    GameManager<char> word_tic_tac_toe_game(B, players);
    word_tic_tac_toe_game.run();
    if (B->is_win()) {
        string winningWord = B->get_winning_word();
        cout << "The game ends with the word \"" << winningWord << "\"!" << endl;
    }

    delete players[0];
    delete players[1];
    delete B;

    return 0;
}