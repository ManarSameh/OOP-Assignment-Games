#include <iostream>
#include "BoardGame_Classes.h"
#include "5X5X_O.h"


using namespace std;

int main() {
    int choice;
    Player<char>* players[2];
    X_O_Board<char>* B = new X_O_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game (5x5 variation). :)\n";

    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new X_O_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new X_O_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }


    cout << "Enter Player O name: ";
    cin >> player2Name;
    cout << "Choose Player O type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new X_O_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new X_O_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    cout << "\nGame Start!\n";
    int current_player = 0;
    while (!B->game_is_over()) {
        B->display_board();
        int x, y;
        cout << players[current_player]->getname() << "'s turn (" 
             << players[current_player]->getsymbol() << ").\n";
        players[current_player]->getmove(x, y);

        if (B->update_board(x, y, players[current_player]->getsymbol())) {
            current_player = (current_player + 1) % 2;
        } else {
            cout << "Invalid move! Try again.\n";
        }
    }


    B->display_board();
    B->display_winner();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}
