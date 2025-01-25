/**
 * @file SticksGame.cpp
 * @brief Implementation of the Sticks Game logic.
 */

#include "SticksGame.h"

/**
 * @brief Gets the current player in the game.
 * @return An integer representing the current player (AI or PLAYER).
 */
int SticksGame::getCurrentPlayer() const
{
    return currentPlayer;
}

/**
 * @brief Displays the current state of the Sticks Game.
 */
void SticksGame::display() const
{
    std::cout << "Remaining sticks: " << remainingSticks << "\n";
    for (int i = 0; i < remainingSticks; ++i)
    {
        std::cout << "| ";
    }
    std::cout << "\n\n";
}

/**
 * @brief Checks if the game is in a terminal state.
 * @return true if the game is over (no sticks remaining), false otherwise.
 */
bool SticksGame::isTerminal() const
{
    return remainingSticks <= 0;
}

/**
 * @brief Gets all the valid moves available in the current game state.
 * @return A vector of integers representing the number of sticks that can be removed (1, 2, or 3).
 */
std::vector<int> SticksGame::getAvailableMoves() const
{
    std::vector<int> moves;
    for (int numSticks = 1; numSticks <= 3 && numSticks <= remainingSticks; ++numSticks)
    {
        moves.emplace_back(numSticks); // Use numSticks as the number of sticks to remove
    }
    return moves;
}

/**
 * @brief Makes a move by removing a specified number of sticks.
 * @param numSticks The number of sticks to remove.
 */
void SticksGame::makeMove(const int numSticks)
{
    remainingSticks -= numSticks;
    currentPlayer = (currentPlayer == PLAYER) ? AI : PLAYER; // Switch turns
}

/**
 * @brief Undoes a move by restoring the specified number of sticks.
 * @param numSticks The number of sticks to restore.
 */
void SticksGame::undoMove(const int numSticks)
{
    remainingSticks += numSticks;
    currentPlayer = (currentPlayer == PLAYER) ? AI : PLAYER; // Switch turns back
}

/**
 * @brief Evaluates the current game state to calculate a score.
 * @return A score based on the evaluation:
 *         -10 if the current player loses, 10 if the current player wins, 0 otherwise.
 */
int SticksGame::evaluate() const
{
    if (remainingSticks == 0) return (currentPlayer == PLAYER) ? -10 : 10;
    return 0;
}

/**
 * @brief Determines the winner of the game.
 * @return The winner of the game:
 *         - PLAYER if the player wins,
 *         - AI if the AI wins,
 *         - 0 if there is no winner yet.
 */
int SticksGame::getWinner() const
{
    if (remainingSticks == 0) return (currentPlayer == PLAYER) ? PLAYER : AI;
    return 0;
}

/**
 * @brief Checks if the player's input is valid.
 * @param input The number of sticks the player wants to pick.
 * @return true if the input is valid (1-3 sticks and within remaining sticks), false otherwise.
 */
bool SticksGame::checkInput(const int input) const
{
    return input >= 1 && input <= 3 && input <= remainingSticks;
}

/**
 * @brief Prompts the player to input the number of sticks they want to pick.
 * @return The number of sticks the player chooses to pick.
 */
int SticksGame::askInput() const
{
    int x;
    std::cout << "Enter the number of sticks you want to pick\n";
    std::cin >> x;
    return x;
}
