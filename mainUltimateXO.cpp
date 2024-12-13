#include <iostream>
#include "BoardGame_Classes.h"
#include "UltimateXO.h"

using namespace std;

int main() {
    int choice;
    UltimateXO_Player<char>* players[2];
    UltimateXO_Board<char>* ultimateBoard = new UltimateXO_Board<char>();
    string playerXName, playerOName;

    cout << "Welcome to FCAI Ultimate X-O Game. :)\n";

    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[0] = new UltimateXO_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new UltimateXO_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player X. Exiting the game.\n";
            delete ultimateBoard;
            return 1;
    }

    cout << "Enter Player O name: ";
    cin >> playerOName;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch (choice) {
        case 1:
            players[1] = new UltimateXO_Player<char>(playerOName, 'O');
            break;
        case 2:
            players[1] = new UltimateXO_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player O. Exiting the game.\n";
            delete ultimateBoard;
            delete players[0];
            return 1;
    }

    int currentPlayer = 0;
    while (!ultimateBoard->game_is_over()) {
        ultimateBoard->display_board();
        cout << players[currentPlayer]->get_name() << "'s (" << players[currentPlayer]->get_symbol() << ") turn.\n";

        int subX, subY, x, y;
        players[currentPlayer]->getmove(subX, subY, x, y);

        if (!ultimateBoard->update_board(subX, subY, x, y, players[currentPlayer]->get_symbol())) {
            cout << "Invalid move. Try again.\n";
            continue;
        }

        if (ultimateBoard->is_win()) {
            cout << "\nCongratulations " << players[currentPlayer]->get_name() << "! You won the game!\n";
            ultimateBoard->display_board();
            break;
        }

        if (ultimateBoard->is_draw()) {
            cout << "\nIt's a draw! Well played!\n";
            ultimateBoard->display_board();
            break;
        }

        currentPlayer = 1 - currentPlayer;
    }

    delete ultimateBoard;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
