/**
 * @file TicTacToe.h
 * @brief Declaration of the TicTacToe class, a concrete implementation of the Game interface.
 */

#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <Game.h>
#include <iostream>


constexpr int BOARD_SIZE = 3; ///< The size of the Tic-Tac-Toe board.

/**
 * @class TicTacToe
 * @brief A class representing a Tic-Tac-Toe game.
 *
 * This class provides the game logic for Tic-Tac-Toe, including displaying the board,
 * making moves, undoing moves, and evaluating the game state. It extends the abstract `Game` class.
 */
class TicTacToe final : public Game {
private:
    int board[BOARD_SIZE][BOARD_SIZE]; ///< The Tic-Tac-Toe game board.
    int currentPlayer; ///< The ID of the current player (PLAYER or AI).

public:
    /**
     * @brief Constructs a TicTacToe game instance.
     * @param userIsStarting A boolean indicating if the user is the starting player.
     */
    explicit TicTacToe(bool userIsStarting = true);

    /**
     * @brief Gets the current player in the game.
     * @return An integer representing the current player (AI or PLAYER).
     */
    [[nodiscard]] int getCurrentPlayer() const override;

    /**
     * @brief Displays the current state of the Tic-Tac-Toe board.
     */
    void display() const override;

    /**
     * @brief Checks if the game is in a terminal state (win, lose, or draw).
     * @return true if the game is over, false otherwise.
     */
    [[nodiscard]] bool isTerminal() const override;

    /**
     * @brief Gets all the available moves on the current board.
     * @return A vector of integers representing the indices of empty cells.
     */
    [[nodiscard]] std::vector<int> getAvailableMoves() const override;

   /**
   * @brief Makes a move at the specified position.
   * @param cellIndex The index of the cell where the move will be made.
   */
    void makeMove(int cellIndex) override;

    /**
    * @brief Undoes the move at the specified position.
    * @param cellIndex The index of the cell to be cleared.
    */
    void undoMove(int cellIndex) override;

    /**
    * @brief Evaluates the current board state to calculate a score.
    * @return A score representing the evaluation of the board:
    *         10 for an AI win, -10 for a player win, 0 for a draw or ongoing game.
    */
    [[nodiscard]] int evaluate() const override;

    /**
    * @brief Determines the winner of the game.
    * @return 1 if the player wins, -1 if the AI wins, 0 if there is no winner.
    */
    [[nodiscard]] int getWinner() const override;

    /**
    * @brief Validates the player's input to ensure it is a valid move.
    * @param input The input position provided by the player.
    * @return true if the input is valid, false otherwise.
    */
    [[nodiscard]] bool checkInput(int input) const override;

    /**
    * @brief Asks the player for their input.
    * @return The index of the cell chosen by the player.
    */
    [[nodiscard]] int askInput() const override;
};



#endif //TICTACTOE_H
