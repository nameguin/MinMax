/**
 * @file main.cpp
 * @brief A program to play various games (Tic-Tac-Toe, Connect 4, Sticks game) with AI using the MinMax algorithm.
 */

#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include <random>

#include "Game.h"
#include "Connect4.h"
#include "SticksGame.h"
#include "TicTacToe.h"

using namespace std;

/**
 * @brief MinMax algorithm to calculate the optimal score for the current game state.
 *
 * @param game Reference to the current game object.
 * @param depth The current depth of the recursive search.
 * @param isMaximizing Boolean flag to indicate whether the current player is maximizing or minimizing the score.
 * @return int The best score for the current player.
 */
int minMax(Game &game, const int depth, const bool isMaximizing)
{
    int maxDepth = 999999;
    if (dynamic_cast<Connect4*>(&game))
    {
        // Limit the recursion depth to avoid excessive computation.
        // A depth of 6 is chosen as a balance between performance and decision quality.
        maxDepth = 6;
    }
    if (depth >= maxDepth || game.isTerminal())
    {
        return game.evaluate(); // Return the evaluation of the current state.
    }

    // Initialize the best score based on whether we are maximizing or minimizing.
    int bestScore = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

    // Loop through all available moves.
    for (const auto move : game.getAvailableMoves())
    {
        game.makeMove(move); // Apply the move.

        // Recursively call MinMax for the next depth and toggle the maximizing flag.
        int score = minMax(game, depth + 1, !isMaximizing);

        // Undo the move to restore the game state.
        game.undoMove(move);

        // Update the best score based on whether we are maximizing or minimizing.
        bestScore = isMaximizing ? std::max(bestScore, score) : std::min(bestScore, score);
    }

    return bestScore;
}

/**
 * @brief Determines the best move for the AI using the MinMax algorithm.
 *
 * @param game Reference to the current game object.
 * @return int The index of the best move for the AI.
 */
int getBestMove(Game &game)
{
    int bestScore = std::numeric_limits<int>::min();
    int bestMove = -1;

    for (const auto move : game.getAvailableMoves())
    {
        game.makeMove(move); // Apply the move.

        // Evaluate the move using the MinMax algorithm, starting at depth 0.
        const int score = minMax(game, 0, false);
        game.undoMove(move); // Undo the move to restore the game state.

        // If the score for this move is better than the current best score, update bestScore and bestMove.
        if (score > bestScore)
        {
            bestScore = score;
            bestMove = move;
        }
    }

    return bestMove;
}

/**
 * @brief Main function to run the game program.
 *
 * The user is prompted to choose a game, and the program alternates turns between the player and the AI
 * until the game reaches a terminal state. The final result is displayed to the user.
 *
 * @return int Exit status of the program.
 */
int main()
{
    unique_ptr<Game> game;

    // Initialize the random number generator
    std::random_device rd;
    std::mt19937 gen(rd()); // Using Mersenne Twister
    std::uniform_int_distribution<> dist(0, 1); // Distribution to generate 0 or 1

    while(true)
    {
        cout << "Choose a game:\n";
        cout << "1. Tic-Tac-Toe\n";
        cout << "2. Connect 4\n";
        cout << "3. Sticks game\n";
        cout << "4. Quit\n";

        int choice;
        cin >> choice;

        // Generate a random boolean
        bool isUserStarting = dist(gen);

        switch (choice)
        {
            case 1:
                game = make_unique<TicTacToe>(isUserStarting);
                break;
            case 2:
                game = make_unique<Connect4>(isUserStarting);
                break;
            case 3:
                game = make_unique<SticksGame>(isUserStarting);
                break;
            case 4:
                cout << "Quiting game.\n";
                return 0;

            default:
                cout << "Invalid choice.\n";
                return 0;
        }

        cout << "Welcome to the game!\n";

        while (!game->isTerminal())
        {
            game->display();

            // Player's turn
            if(game->getCurrentPlayer() == game->PLAYER)
            {
                int input;
                do
                {
                    input = game->askInput();
                }
                while (!game->checkInput(input));

                game->makeMove(input);
                if (game->isTerminal()) break;
            }
            // AI's turn
            else
            {
                const int bestMove = getBestMove(*game);
                game->makeMove(bestMove);
            }
        }

        game->display();
        const int winner = game->getWinner();
        if (winner == game->PLAYER) cout << "You win!\n\n";
        else if (winner == game->AI) cout << "AI wins!\n\n";
        else cout << "It's a draw!\n\n";
    }
}
