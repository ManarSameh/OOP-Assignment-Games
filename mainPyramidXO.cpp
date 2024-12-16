#include <iostream>
#include "BoardGame_Classes.h"
#include "PyramidXO.h"

using namespace std;

int pyramidXO() {
    int choice;
    Player<char>* players[2];
    auto* B = new PyramidBoard<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI Pyramid X-O Game. :)\n";

    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new HumanPlayer(playerXName, 'X');
        break;
        case 2:
            players[0] = new RandomPyramidPlayer('X');
        break;
        default:
            cout << "Invalid choice for Player X. Exiting the game.\n";
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
            players[1] = new HumanPlayer(player2Name, 'O');
        break;
        case 2:
            players[1] = new RandomPyramidPlayer('O');
        break;
        default:
            cout << "Invalid choice for Player O. Exiting the game.\n";
        return 1;
    }

    GameManager<char> pyramid_x_o_game(B, players);
    pyramid_x_o_game.run();

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}