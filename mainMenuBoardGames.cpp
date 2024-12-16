#include <iostream>
#include "mainMenuBoardGames.h"
using namespace std;


int main() {
     cout << "Welcome to the Board Games Menu!" << endl;
    cout << "Please select a game to play:" << endl;

    cout << "1. Pyramic Tic-Tac-Toe" << endl;
    cout << "2. Four-in-a-row" << endl;
    cout << "3. 5 x 5 Tic-Tac-Toe" << endl;
    cout << "4. Word Tic-Tac-Toe" << endl;
    cout << "5. Numerical Tic-Tac-Toe" << endl;
    cout << "6. Misere Tic-Tac-Toe" << endl;
    cout << "7. Ultimate Tic-Tac-Toe" << endl;
    cout << "8. SUS" << endl;

    int gameChoice;
    cin >> gameChoice;

    switch (gameChoice) {
        case 1:
            return pyramidXO();
        case 2:
            return connect4();
        case 3:
            return XO_5x5();
        case 4:
            return wordXO();
        case 5:
            return numXO();
        case 6:
            return Misere();
        case 7:
            return UltimateXO();
        case 8:
            return SUS();
        default:
            cout << "Invalid choice! Exiting the program.\n";
            return 1;
    }
}
