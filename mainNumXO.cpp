#include <iostream>
#include "BoardGame_Classes.h"

#include "num_x_o.h"

using namespace std;

int main() {
int choice;
    Player<int>* players[2];
    NUM_X_O_Board<int>* B = new NUM_X_O_Board<int>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new NUM_X_O_Player<int>(playerXName, 1);
            break;
        case 2:
            players[0] = new NUM_X_O_Random_Player<int>(1);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new NUM_X_O_Player<int>(player2Name, 2);
            break;
        case 2:
            players[1] = new NUM_X_O_Random_Player<int>(2);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<int> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}