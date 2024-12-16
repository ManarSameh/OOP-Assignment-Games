#include <iostream>
#include "mainMenuBoardGames.h"
#include <limits>
using namespace std;

int main() {
    while (true) {
        cout << "\nWelcome to the Board Games Menu!" << endl;
        cout << "==================================" << endl;
        cout << "Please select a game to play or exit the program:" << endl << endl;

        cout << "1. Pyramid Tic-Tac-Toe" << endl;
        cout << "2. Four-in-a-row" << endl;
        cout << "3. 5 x 5 Tic-Tac-Toe" << endl;
        cout << "4. Word Tic-Tac-Toe" << endl;
        cout << "5. Numerical Tic-Tac-Toe" << endl;
        cout << "6. Misere Tic-Tac-Toe" << endl;
        cout << "8. Ultimate Tic-Tac-Toe" << endl;
        cout << "9. SUS" << endl;
        cout << "0. Exit" << endl;

        int gameChoice;
        cout << "Enter your choice: ";
        if (!(cin >> gameChoice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n\n";
            continue;
        }

        switch (gameChoice) {
            case 1:
                pyramidXO();
            break;
            case 2:
                connect4();
            break;
            case 3:
                XO_5x5();
            break;
            case 4:
                wordXO();
            break;
            case 5:
                numXO();
            break;
            case 6:
                Misere();
            break;
            case 8:
                UltimateXO();
            break;
            case 9:
                SUS();
            break;
            case 0:
                cout << "Exiting the program. Goodbye!\n";
            return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}