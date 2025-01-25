/**
* @file SticksGame.h
 * @brief Definition of the SticksGame class, implementing the game logic for a stick-picking game.
 */

#ifndef STICKSGAME_H
#define STICKSGAME_H

#include <Game.h>
#include <iostream>
#include <vector>

constexpr int STICKS_NUMBER = 21; ///< The initial number of sticks on the board.

/**
 * @class SticksGame
 * @brief Represents a stick-picking game where players alternate removing 1-3 sticks until none remain.
 *
 * This class is a concrete implementation of the abstract `Game` class. It handles the game's rules,
 * state transitions, and evaluation logic.
 */
class SticksGame final : public Game{
private:
    int currentPlayer; ///< The current player (PLAYER or AI).
    int remainingSticks; ///< The number of sticks remaining in the game.

public:
    /**
     * @brief Constructs a SticksGame instance.
     * @param userIsStarting Determines whether the user starts the game. Defaults to `true`.
     */
    explicit SticksGame(const bool userIsStarting = true)
        : currentPlayer(userIsStarting ? PLAYER : AI), remainingSticks(STICKS_NUMBER) {}

    /**
     * @brief Gets the current player in the game.
     * @return An integer representing the current player (AI or PLAYER).
     */
    [[nodiscard]] int getCurrentPlayer() const override;

    /**
     * @brief Displays the current state of the Sticks Game.
     */
    void display() const override;

    /**
     * @brief Checks if the game is in a terminal state.
     * @return true if the game is over (no sticks remaining), false otherwise.
     */
    [[nodiscard]] bool isTerminal() const override;

    /**
     * @brief Gets all the valid moves available in the current game state.
     * @return A vector of integers representing the number of sticks that can be removed (1, 2, or 3).
     */
    [[nodiscard]] std::vector<int> getAvailableMoves() const override;

    /**
     * @brief Makes a move by removing a specified number of sticks.
     * @param numSticks The number of sticks to remove.
     */
    void makeMove(int numSticks) override;

    /**
     * @brief Undoes a move by restoring the specified number of sticks.
     * @param numSticks The number of sticks to restore.
     */
    void undoMove(int numSticks) override;

    /**
     * @brief Evaluates the current game state to calculate a score.
     * @return A score based on the evaluation:
     *         -10 if the current player loses, 10 if the current player wins, 0 otherwise.
     */
    [[nodiscard]] int evaluate() const override;

    /**
     * @brief Determines the winner of the game.
     * @return The winner of the game:
     *         - PLAYER if the player wins,
     *         - AI if the AI wins,
     *         - 0 if there is no winner yet.
     */
    [[nodiscard]] int getWinner() const override;

    /**
     * @brief Checks if the player's input is valid.
     * @param input The number of sticks the player wants to pick.
     * @return true if the input is valid (1-3 sticks and within remaining sticks), false otherwise.
     */
    [[nodiscard]] bool checkInput(int input) const override;

    /**
     * @brief Prompts the player to input the number of sticks they want to pick.
     * @return The number of sticks the player chooses to pick.
     */
    [[nodiscard]] int askInput() const override;
};



#endif //STICKSGAME_H
