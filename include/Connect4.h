/**
 * @file Connect4.h
 * @brief Declaration of the Connect 4 game class.
 */

#ifndef CONNECT4_H
#define CONNECT4_H

#include <Game.h>
#include <iostream>
#include <vector>

constexpr int BOARD_LENGTH = 7; ///< The number of columns in the Connect 4 board.
constexpr int BOARD_HEIGHT = 6; ///< The number of rows in the Connect 4 board.

/**
 * @class Connect4
 * @brief Represents the Connect 4 game and its logic.
 *
 * This class handles the state of the Connect 4 game board, player actions,
 * and game evaluation, including determining valid moves and checking for a winner.
 */
class Connect4 final : public Game{
private:
    int board[BOARD_HEIGHT][BOARD_LENGTH]; ///< 2D array representing the Connect 4 board.
    int currentPlayer = 1; ///< The current player (1 for PLAYER, -1 for AI).

public:
    /**
     * @brief Default constructor.
     *
     * Initializes the Connect 4 board with empty cells.
     * @param userIsStarting A boolean indicating if the user is the starting player.
     */
    explicit Connect4(const bool userIsStarting = true) : board(), currentPlayer(userIsStarting ? PLAYER : AI) {}

    /**
     * @brief Gets the current player in the game.
     * @return An integer representing the current player (AI or PLAYER).
     */
    [[nodiscard]] int getCurrentPlayer() const override;

    /**
     * @brief Displays the current state of the Connect 4 board.
     *
     * The board is displayed with X for the player, O for the AI, and . for empty cells.
     * Column numbers are displayed below the board for reference.
     */
    void display() const override;

    /**
     * @brief Checks if the game is in a terminal state.
     *
     * A terminal state occurs when there is a winner or no more moves are available.
     * @return true if the game is over, false otherwise.
     */
    [[nodiscard]] bool isTerminal() const override;

    /**
     * @brief Gets all valid moves (columns) in the current game state.
     *
     * A valid move is any column that is not full.
     * @return A vector of integers representing the indices of available columns.
     */
    [[nodiscard]] std::vector<int> getAvailableMoves() const override;

    /**
     * @brief Makes a move in the specified column.
     *
     * The move is applied to the lowest available row in the column.
     * @param col The index of the column where the move is made.
     */
    void makeMove(int col) override;

    /**
     * @brief Undoes the last move made in the specified column.
     *
     * The topmost occupied row in the column is cleared.
     * @param col The index of the column to undo the move.
     */
    void undoMove(int col) override;

    /**
     * @brief Evaluates the current board state.
     *
     * @return 10 if the AI wins, -10 if the player wins, 0 otherwise.
     */
    [[nodiscard]] int evaluate() const override;

    /**
     * @brief Determines the winner of the game.
     *
     * Checks for four consecutive identical markers in any direction (horizontal, vertical, diagonal).
     * @return The marker of the winner (PLAYER or AI), or 0 if there is no winner.
     */
    [[nodiscard]] int getWinner() const override;

    /**
     * @brief Checks if the player's input column is valid.
     *
     * A valid column is one that exists and is not full.
     * @param col The index of the column to check.
     * @return true if the input is valid, false otherwise.
     */
    [[nodiscard]] bool checkInput(int col) const override;

    /**
     * @brief Prompts the player for their input.
     *
     * @return The index of the column chosen by the player.
     */
    [[nodiscard]] int askInput() const override;
};



#endif //CONNECT4_H
