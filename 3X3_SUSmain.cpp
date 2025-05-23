#include <iostream>
#include "BoardGame_Classes.h"
#include "3X3_SUS.h"

using namespace std;

int SUS() {
    int choice;
    Player<char>* players[2];
    SUS_Board<char>* B = new SUS_Board<char>();
    string player1Name, player2Name;

    cout << "Welcome to FCAI SUS Game!\n";

    
    cout << "Enter Player 1 name: ";
    cin >> player1Name;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new SUS_Player<char>(player1Name, 'S');
            break;
        case 2:
            players[0] = new SUS_Random_Player<char>('S');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new SUS_Player<char>(player2Name, 'U');
            break;
        case 2:
            players[1] = new SUS_Random_Player<char>('U');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    
    GameManager<char> sus_game(B, players);
    sus_game.run();

    
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}








