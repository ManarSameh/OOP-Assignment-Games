#include <iostream>
#include "BoardGame_Classes.h"
#include "PyramidXO.h"
#include "connectFour.h"
#include "5X5X_O.h"
#include "WordTicTacToe.h"
#include "num_x_o.h"
#include "3x3X_OMisere.h"
#include "UltimateXO.h"
#include "3X3_SUS.h"

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
        case 1: {
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

            break;
        }
        case 2: {
            int choice;
            Player<char>* players[2];
            connectFour<char>* B = new connectFour<char>();
            string playerXName, player2Name;

            cout << "Welcome to FCAI X-O Game. :)\n";

            cout << "Enter Player X name: ";
            cin >> playerXName;
            cout << "Choose Player X type:\n";
            cout << "1. Human\n";
            cout << "2. Random Computer\n";
            cin >> choice;

            switch(choice) {
                case 1:
                    players[0] = new connect4_Player<char>(playerXName, 'X');
                break;
                case 2:
                    players[0] = new connect4_Random_Player<char>('X');
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
                    players[1] = new connect4_Player<char>(player2Name, 'O');
                break;
                case 2:
                    players[1] = new connect4_Random_Player<char>('O');
                break;
                default:
                    cout << "Invalid choice for Player 2. Exiting the game.\n";
                return 1;
            }

            GameManager<char> x_o_game(B, players);
            x_o_game.run();

            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

            break;
        }
        case 3: {
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
            break;
        }
        case 4: {
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

            break;
        }
        case 5: {
            int choice;
            Player<int>* players[2];
            NUM_X_O_Board<int>* B = new NUM_X_O_Board<int>();
            string playerXName, player2Name;

            cout << "Welcome to FCAI X-O Game. :)\n";

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

            GameManager<int> x_o_game(B, players);
            x_o_game.run();


            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

            break;
        }
        case 6: {
            int choice;
            Player<char>* players[2];
            X_O_Board<char>* B = new X_O_Board<char>();
            string playerXName, player2Name;

            cout << "Welcome to FCAI X-O Game. :)\n";

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


            cout << "Enter Player 2 name: ";
            cin >> player2Name;
            cout << "Choose Player 2 type:\n";
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


            GameManager<char> x_o_game(B, players);
            x_o_game.run();

            delete B;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }

            break;
        }
        case 7: {
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
            break;
        }
        case 8: {
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
            break;
        }
    }





}